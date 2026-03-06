#include "BodeDrive.h"
#include <QStringList>
#include <iostream>
#include<QDebug>
#include <sstream>
#include <QElapsedTimer>
#include"mainwindow.h"

BodeDrive::BodeDrive()
{

}

BodeDrive::~BodeDrive()
{
    disconnectVisa();
}


bool BodeDrive::connectVisa(const QString& ip)
{
    ViStatus status;

    QString resource = ip;
        //"TCPIP0::" + ip + "::5025::SOCKET";
  
    status = viOpenDefaultRM(&rm);

    if (status < VI_SUCCESS)
    {
        std::cout << "Open VISA Resource Manager failed\n";
        return false;
    }

    status = viOpen(
        rm,
        (ViRsrc)resource.toStdString().c_str(),
        VI_NULL,
        VI_NULL,
        &vi);

    if (status < VI_SUCCESS)
    {
        std::cout << "Open VISA session failed\n";
        return false;
    }

    // 设置通信参数
    viSetAttribute(vi, VI_ATTR_TERMCHAR_EN, VI_TRUE);
    viSetAttribute(vi, VI_ATTR_TERMCHAR, '\n');
    viSetAttribute(vi, VI_ATTR_TMO_VALUE, 4000);

    return true;
}


void BodeDrive::disconnectVisa()
{

    if (vi != VI_NULL)
    {
        viClose(vi);
        vi = VI_NULL;
    }

    if (rm != VI_NULL)
    {
        viClose(rm);
        rm = VI_NULL;
    }

}


QString BodeDrive::queryIDN()
{

    if (!isConnected())
        return "Not connected";

    ViUInt32 retCount;

    char buffer[256] = { 0 };

    const char* cmd = "*IDN?\n";

    viWrite(vi, (ViBuf)cmd, strlen(cmd), &retCount);

    viRead(vi, (ViBuf)buffer, sizeof(buffer), &retCount);

    return QString(buffer);
}


bool BodeDrive::isConnected() const
{
    return vi != VI_NULL;
}

bool BodeDrive::startScpiRunner(
    const std::wstring& command,
    PROCESS_INFORMATION& pi)
{
    STARTUPINFOW si{};
    si.cb = sizeof(si);

    std::wstring mutableCmd = command;


    BOOL result = CreateProcessW(
        NULL,
        &mutableCmd[0],
        NULL,
        NULL,
        FALSE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        &pi);

    if (!result)
    {
        qDebug() << "Failed to start SCPI Runner. Error: "
            << GetLastError();
        return false;
    }

    return true;
}

void BodeDrive::sendCommand(ViSession vi, const QString & cmd) {

    ViUInt32 retCount;
    QByteArray data = cmd.toUtf8();   // 关键转换

    viWrite(vi, (ViBuf)data.data(), data.size(), &retCount);
    // 通过VISA向仪器发送命令
    //viWrite(vi, (ViBuf)cmd.c_str(), cmd.size(), &retCount);
}


// 1. 加上 BodeDrive:: 前缀，并将返回值改为头文件中声明的 QString
//QString BodeDrive::queryCommand(ViSession vi, const std::string& cmd) {
//
//    ViChar buffer[1024]{}; // 每次读取1KB
//    ViUInt32 retCount;
//
//    // 2. 因为现在已经在 BodeDrive 类作用域内了，直接调用即可，删掉 "BodeDrive::"
//    sendCommand(vi, cmd);
//
//    viRead(vi, (ViBuf)buffer, sizeof(buffer), &retCount);
//
//    // 3. 补全缺失的 std:: 前缀
//    std::string currentChars = std::string(buffer, retCount);
//    std::string response = currentChars;
//
//    // 4. 补全 string::npos 前面的 std::
//    while (currentChars.find('\n') == std::string::npos)
//    {
//        viRead(vi, (ViBuf)buffer, sizeof(buffer), &retCount);
//
//        currentChars = std::string(buffer, retCount);
//        response += currentChars;
//
//        // 5. 补全 cout 和 endl 前面的 std::
//        std::cout << "QUERY: " << cmd << std::endl;
//    }
//
//    // 6. 将最终拼接好的 std::string 转换为头文件要求的 QString
//    return QString::fromStdString(response);
//}

// 注意：你截图1里写的是 QString ss = queryCommand，截图2返回的是 std::string。
// 我这里以返回 std::string 为例，如果你的头文件定义的是 QString，请自行修改返回值类型。

//QString BodeDrive::queryCommand(ViSession vi, const std::string& cmd) {
//
//    ViChar buffer[1024]{};
//    ViUInt32 retCount = 0;
//    QString response = "";
//
//    sendCommand(vi, cmd);
//
//    ViStatus status;
//    do {
//        // 每次读取前清空 buffer，防止脏数据干扰
//        memset(buffer, 0, sizeof(buffer));
//
//        // 留出最后一位防止字符串越界
//        status = viRead(vi, (ViBuf)buffer, sizeof(buffer) - 1, &retCount);
//      
//        // 如果读到了数据，拼接到 response 中
//        if (retCount > 0) {
//            response += QString::fromUtf8((char*)buffer, retCount);
//        }
//        else {
//            
//            response = ("仪器返回值没东西");
//        }
//
//        // 【防死锁核心】如果读取发生错误（比如超时 VI_ERROR_TMO），立刻跳出！
//        if (status < VI_SUCCESS) {
//            // qDebug() << "viRead 遇到警告或错误，状态码:" << status;
//            break;
//        }
//
//        // 【正确循环条件】只有当状态明确告诉我们 "还没读完，1024字节装不下" 时，才继续循环
//    } while (status == VI_SUCCESS_MAX_CNT);
//
//    return response;
//}

QString BodeDrive::queryCommand(const std::string& cmd)
{
    if (!isConnected())
        return "Not connected";

    ViUInt32 retCount = 0;
    char buffer[512] = { 0 };

    viWrite(vi, (ViBuf)cmd.c_str(), cmd.size(), &retCount);

    ViStatus status = viRead(vi, (ViBuf)buffer, sizeof(buffer) - 1, &retCount);

    if (status >= VI_SUCCESS && retCount > 0)
        return QString::fromUtf8(buffer, retCount);

    return "";
}

std::vector<float> BodeDrive::parseResults(const std::string& data)
{

    std::vector<float> results;

    std::istringstream ss(data);

    std::string token;

    while (getline(ss, token, ','))
    {
        results.push_back(std::stof(token));
    }

    return results;

}

QString BodeDrive::bodeCalibration(ViSession vi,CalMode mode)
{
    //sendCommand(vi,":CALC:PAR:DEF Z\n");
    ////queryCommand("*OPC?\n");
    //sendCommand(vi, ":SENS:Z:METH IAD\n");
    //QString before=queryCommand(":SENS:CORR:FULL:AVAI?\n");
    QString modeStr;
    switch (mode) {
    case CalMode::Open:  modeStr = "OPEN"; break;
    case CalMode::Short: modeStr = "SHOR"; break;
    case CalMode::Load:  modeStr = "LOAD"; break;
    }
    QString fullCmd = QString(":SENS:CORR:FULL:%1\n").arg(modeStr);
    sendCommand(vi, fullCmd);
    QString opc = queryCommand("*OPC?\n");
    //queryCommand存在问题导致程序死锁，修改
    QString err = queryCommand("SYST:ERR?\n");
    QString ss = err+opc;
    return ss;

}

QString BodeDrive::bodeCalibrationCom(ViSession vi)
{

    //int numOfPoints = 201;
    //QString startfreq = "10kHz";
    //QString stopfreq = "10MAHz";
    //QString bandwidth = "300Hz";
    //sendCommand(vi, ":SENS:FREQ:STAR" + startfreq + "\n"); //start frequency 10kHz
    //sendCommand(vi, ":SENS:FREQ:STOP" + stopfreq + "\n"); //stop frequency 10MHz
    //sendCommand(vi, ":SENS:SWE:TYPE LOG\n"); //logarithmic sweep
    //sendCommand(vi, ":SENS:BAND" + bandwidth + "\n");

    QString after3 = queryCommand(":SENS:CORR:FULL:AVAI?\n");
    QString after2 = queryCommand(":SENS:CORR:FULL:ENAB ON\n");
    QString after = queryCommand(":SENS:CORR:FULL:ACT?\n");
    
    //QString after3 = queryCommand(":SENS:CORR:FULL:AVAI?\n");
    return after +  after3;
}


// //////////////////////////////////阻抗测量函数////////////////////////////////
MeasureResult BodeDrive::performMeasurement(ViSession vi, SweepParams params)
{
    MeasureResult result;
    result.success = false;

    // 1. 申请仪器控制权 (防死锁)
    QString lockStatus = queryCommand(vi, ":SYST:LOCK:REQ?\n");
    if (!lockStatus.contains("1") && !lockStatus.toUpper().contains("OK")) {
        result.message = "获取仪器控制权失败，无法开始测量！";
        return result;
    }

    // 2. 初始化 (注意：删除了 *RST 以保护校准数据，只保留 *CLS 清除错误队列)
    sendCommand(vi, "*CLS\n");
    sendCommand(vi, "*ESE 255\n"); // 开启错误检查

    // 3. 写入用户配置的扫频参数
    sendCommand(vi, ":CALC:PAR:DEF Z\n"); // 测阻抗
    sendCommand(vi, ":SENS:FREQ:STAR " + params.startFreq.toStdString() + "\n");
    sendCommand(vi, ":SENS:FREQ:STOP " + params.stopFreq.toStdString() + "\n");
    sendCommand(vi, ":SENS:SWE:POIN " + std::to_string(params.points) + "\n");
    sendCommand(vi, ":SENS:SWE:TYPE " + params.sweepType.toStdString() + "\n");
    sendCommand(vi, ":SENS:BAND " + params.bandwidth.toStdString() + "\n");

    // 配置数据格式：线性幅值和相位 (Mag/Phase)
    sendCommand(vi, ":CALC:FORM SLIN\n");

    // 4. 触发测量
    sendCommand(vi, ":TRIG:SOUR BUS\n"); // 设置为总线触发
    sendCommand(vi, ":INIT\n");          // 初始化触发系统
    sendCommand(vi, ":TRIG:SING\n");     // 发送单次触发指令

    // 5. 【关键】延长超时时间并等待测量完成
    // 扫频点数越多、带宽越窄，耗时越长。这里设个较长的时间，比如 60 秒
    ViUInt32 originalTimeout;
    viGetAttribute(vi, VI_ATTR_TMO_VALUE, &originalTimeout);
    viSetAttribute(vi, VI_ATTR_TMO_VALUE, 60000); // 60秒超时

    QString opc = queryCommand(vi, "*OPC?\n"); // 阻塞等待仪器扫频结束

    viSetAttribute(vi, VI_ATTR_TMO_VALUE, originalTimeout); // 恢复超时时间

    if (!opc.contains("1")) {
        result.message = "测量超时或通信中断！";
        sendCommand(vi, ":SYST:LOCK:REL?\n"); // 释放锁
        return result;
    }

    // 6. 获取数据
    QString freqDataStr = queryCommand( ":SENS:FREQ:DATA?\n");
    QString measDataStr = queryCommand( ":CALC:DATA:SDAT?\n");

    // 7. 解析数据并装入 QVector
    QStringList freqList = freqDataStr.split(",", Qt::SkipEmptyParts);
    QStringList measList = measDataStr.split(",", Qt::SkipEmptyParts);

    for (const QString& f : freqList) {
        result.frequencies.append(f.toDouble());
    }

    // SCPI SDAT 返回格式通常是成对的：[幅值1, 相位1, 幅值2, 相位2 ...]
    for (int i = 0; i < measList.size() - 1; i += 2) {
        result.magnitudes.append(measList[i].toDouble());
        result.phases.append(measList[i + 1].toDouble());
    }

    // 8. 释放仪器控制权
    sendCommand(vi, ":SYST:LOCK:REL?\n");

    // 检查是否有系统错误 (SYST:ERR?) 这里略写，你可以加上之前写的 checkError 逻辑

    result.success = true;
    result.message = QString("测量完成！共获取 %1 个点的数据。").arg(result.frequencies.size());
    return result;
}

// //////////////////////////////////阻抗测量函数////////////////////////////////