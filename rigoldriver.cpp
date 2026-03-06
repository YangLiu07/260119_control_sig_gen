//操作信号源的方法
#include "rigoldriver.h"
RigolDriver::RigolDriver(QObject *parent) : QObject(parent)
{
    m_rm = VI_NULL;
    m_instr = VI_NULL;
    m_connected = false;
}

RigolDriver::~RigolDriver()
{
    disconnectDevice();
}

bool RigolDriver::connectDevice(QString resourceName)
{
    ViStatus status;

    // 1. 打开默认资源管理器 (如果尚未打开)
    if (m_rm == VI_NULL) {
        status = viOpenDefaultRM(&m_rm);
        if (!checkStatus(status, "打开资源管理器")) return false;
    }

    // 2. 打开具体设备
    // 注意：visa.h 需要 char*，所以我们要把 QString 转换
    QByteArray resBytes = resourceName.toLatin1();
    status = viOpen(m_rm, resBytes.data(), VI_NULL, VI_NULL, &m_instr);

    if (checkStatus(status, "连接设备 " + resourceName)) {
        m_connected = true;

        // 3. 设置超时时间 (例如 5000ms)，防止仪器没反应卡死软件
        viSetAttribute(m_instr, VI_ATTR_TMO_VALUE, 5000);

        // 4. 发送个 *IDN? 确认一下身份
        QString idn = queryCmd("*IDN?");
        emit sigLog("设备已连接: " + idn);
        return true;
    }
    return false;
}

void RigolDriver::disconnectDevice()
{
    if (m_instr != VI_NULL) {
        viClose(m_instr);
        m_instr = VI_NULL;
    }
    if (m_rm != VI_NULL) {
        viClose(m_rm);
        m_rm = VI_NULL;
    }
    m_connected = false;
    emit sigLog("连接已断开");
}

bool RigolDriver::sendCmd(QString scpi)
{
    if (!m_connected) return false;

    // SCPI 规范建议以换行符结尾

    //调试语句
    qDebug() << "SCPI SEND:" << scpi;

    QString cmdWithEnd = scpi + "\n";
    QByteArray cmdBytes = cmdWithEnd.toLatin1();
    ViUInt32 retCount = 0;

    // 调用 viWrite
    ViStatus status = viWrite(m_instr,
                              (ViBuf)cmdBytes.data(),
                              (ViUInt32)cmdBytes.size(),
                              &retCount);

    return checkStatus(status, "发送指令: " + scpi);
}

QString RigolDriver::queryCmd(QString scpi)
{
    if (!sendCmd(scpi)) return "";

    // 准备缓冲区
    const int BUF_SIZE = 256;
    ViChar buffer[BUF_SIZE];
    ViUInt32 retCount = 0;

    // 调用 viRead
    ViStatus status = viRead(m_instr, (ViBuf)buffer, BUF_SIZE, &retCount);

    if (checkStatus(status, "读取数据")) {
        // 截断字符串，确保安全
        if (retCount < BUF_SIZE) buffer[retCount] = 0;
        return QString::fromLatin1(buffer).trimmed(); // 去除回车换行
    }
    return "";
}

//查找visa地址scanDevices
QString RigolDriver::findRigolGen()
{
    ViStatus status;
    ViFindList findList;
    ViUInt32 retCount = 0;
    ViChar desc[VI_FIND_BUFLEN];
    QString targetAddress = "";

    // 1. 确保资源管理器已打开
    if (m_rm == VI_NULL) {
        viOpenDefaultRM(&m_rm);
    }

    // 2. 搜索所有普源 (0x1AB1) 的 USB 仪器
    // 过滤器含义：USB 接口 + 普源厂家ID + 任意型号 + 任意序列号TCPIP0::169.254.96.21::INSTR
    QByteArray filter =  "TCPIP?*::INSTR";

    status = viFindRsrc(m_rm, filter.data(), &findList, &retCount, desc);

    if (status < VI_SUCCESS || retCount == 0) {
        return ""; // 没搜到任何普源设备
    }

    // 3. 逐个“握手”确认身份
    for (ViUInt32 i = 0; i < retCount; i++) {
        QString currentAddr = QString::fromLatin1(desc);
        ViSession tempSession;

        // 尝试打开该设备
        status = viOpen(m_rm, desc, VI_NULL, 500, &tempSession); // 500ms 短超时
        if (status >= VI_SUCCESS) {
            // 发送 *IDN?
            char idnBuffer[256];
            memset(idnBuffer, 0, sizeof(idnBuffer));
            ViUInt32 readCount;
            viWrite(tempSession, (ViBuf)"*IDN?\n", 6, &readCount);
            viRead(tempSession, (ViBuf)idnBuffer, 256, &readCount);

            QString idnResult = QString::fromLatin1(idnBuffer).toUpper();

            // 关键判断：必须包含 RIGOL 和 DG
            if (idnResult.contains("Rigol") && idnResult.contains("DG")) {
                targetAddress = currentAddr;
                viClose(tempSession);
                break; // 找到了，退出循环
            }
            viClose(tempSession);
        }

        // 找下一个
        viFindNext(findList, desc);
    }

    viClose(findList);
    return targetAddress;
}


// ---------------- 业务逻辑封装 -----------------------

void RigolDriver::setFrequency(double kHz)
{
    // 普源命令: :SOURce1:FREQuency <val>
    sendCmd(QString(":SOUR1:FREQ %1").arg(kHz*1000)); //转换为kHz
}

void RigolDriver::setAmplitude(double vpp)
{
    // 普源命令: :SOURce1:VOLTage <val>
    sendCmd(QString(":SOUR1:VOLT %1").arg(vpp));
}

void RigolDriver::setWaveform(QString type)
{
    // 普源命令: :SOURce1:FUNCtion <shape>
    sendCmd(QString(":SOUR1:FUNC %1").arg(type));
}

void RigolDriver::setOutputState(bool on)
{
    // 普源命令: :OUTPut1:STATe ON/OFF
    QString state = on ? "ON" : "OFF";
    sendCmd(QString(":OUTP1 %1").arg(state));
}

bool RigolDriver::checkStatus(ViStatus status, QString actionName)
{
    if (status < VI_SUCCESS) {
        emit sigLog(QString("错误 [%1]: code=0x%2").arg(actionName).arg(status, 0, 16));
        return false;
    }
    return true;
}


// //////////////////////////对信号源进行扫频参数配置///////////////////////////////////
void RigolDriver::setSweep(double startFreq,
                           double stopFreq,
                           double amplitude,
                           double sweepTime,
                           int stepCount)
{
    sendCmd(":SOUR1:FUNC SIN");
    sendCmd(":SOUR1:VOLT " + QString::number(amplitude));
    sendCmd(":SOUR1:SWE:STAT ON");
    sendCmd(":SOUR1:FREQ:STAR " + QString::number(startFreq*1000));
    sendCmd(":SOUR1:FREQ:STOP " + QString::number(stopFreq*1000));
    sendCmd(":SOUR1:SWE:TIME " + QString::number(sweepTime));
    sendCmd(":SOUR1:SWE:STEP " + QString::number(stepCount));
}

void RigolDriver::setArbWave(QString filePath,
                             double sampleRate,
                             double amplitude)
{
    sendCmd(":SOUR1:VOLT " + QString::number(amplitude));
    // 切换ARB模式
    sendCmd(":SOUR1:FUNC ARB");

    // 设置采样率
    // sendCmd(QString(":SOUR1:ARB:SRAT %1").arg(sampleRate));

    // 设置幅度
    // sendCmd(QString(":SOUR1:VOLT %1").arg(amplitude));

    // 载入波形
    // sendCmd(QString(":MMEM:LOAD \"%1\"").arg(filePath));

    // // 打开输出
    // sendCmd(":OUTP1 ON");
}

