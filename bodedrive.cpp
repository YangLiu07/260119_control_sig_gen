#include "BodeDrive.h"
#include <QStringList>
#include <iostream>
#include<QDebug>
#include <sstream>
#include <QElapsedTimer>
#include"mainwindow.h"
#include <chrono>
BodeDrive::BodeDrive()
{

}

BodeDrive::~BodeDrive()
{
    disconnect();
}

bool BodeDrive::connectVisa(const QString& ip)
{
    ViStatus status;

    QString resource = ip;
  
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


void BodeDrive::disconnect()
{
    //关闭vi会话
    //sendCommandData(vi,"RST");
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
    // 1. 基础状态检查
    if (!vi) return "Not Initialized";

    ViStatus status;
    ViUInt32 retCount;
    char buffer[256] = { 0 };

    // 2. 关键：设置短超时 (300ms-500ms)
    // 如果硬件断线，我们要让它快点报错，而不是在那儿死等
    //viSetAttribute(vi, VI_ATTR_TMO_VALUE, 500);

    //// 3. 嵌入硬件锁请求 (:SYST:LOCK:REQ?)
    //// 这是判断“真连接”的杀手锏
    //const char* lockCmd = ":SYST:LOCK:REQ?\n";
    //status = viWrite(vi, (ViBuf)lockCmd, (ViUInt32)strlen(lockCmd), &retCount);

    //// 清空缓存并读取锁定状态
    //memset(buffer, 0, sizeof(buffer));
    //status = viRead(vi, (ViBuf)buffer, sizeof(buffer) - 1, &retCount);

    //QString lockResponse = QString::fromLocal8Bit(buffer).trimmed();

    //// 如果读取失败，或者返回不是 "1" (代表锁定失败/硬件不在)
    //if (status < VI_SUCCESS || lockResponse != "1") {
    //    // 确保清除可能存在的错误队列，防止影响下次连接
    //    viWrite(vi, (ViBuf)"*CLS\n", 5, &retCount);
    //    return "Disconnected (Hardware Not Found)";
    //}

    // 4. 锁定成功，说明硬件确实在线，现在获取真正的 IDN
    const char* idnCmd = "*IDN?\n";
    viWrite(vi, (ViBuf)idnCmd, (ViUInt32)strlen(idnCmd), &retCount);

    memset(buffer, 0, sizeof(buffer));
    status = viRead(vi, (ViBuf)buffer, sizeof(buffer) - 1, &retCount);

    QString idnResult = "Unknown Device";
    if (status >= VI_SUCCESS) {
        idnResult = QString::fromLocal8Bit(buffer).trimmed();
    }

    // 5. 重要：完成检测后释放锁，否则后续测量指令可能被阻塞
    //viWrite(vi, (ViBuf)":SYST:LOCK:REL\n", 15, &retCount);

    // 6. 恢复正常的测量超时（例如 5秒），确保后续扫描不会因为超时中断
    viSetAttribute(vi, VI_ATTR_TMO_VALUE, 5000);

    return idnResult;
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
    isServerRunning = true;
    return true;
}
void BodeDrive::stopScpiRunner() {
    if (isServerRunning && pi.hProcess != NULL) {
        // 1. 尝试优雅关闭（如果服务器有退出机制，可以发送命令，没有的话直接强杀）
        // TerminateProcess 是最直接清空服务器的方法
        TerminateProcess(pi.hProcess, 0);

        // 2. 必须关闭句柄，否则会造成内核资源泄漏
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        // 3. 重置状态
        pi = { 0 };
        isServerRunning = false;
        log("SCPI Server stopped and cleaned up.");
    }
}

//void BodeDrive::sendCommand(ViSession vi, const QString & cmd) {
//
//    ViUInt32 retCount;
//    QByteArray data = cmd.toUtf8();   // 关键转换
//
//    viWrite(vi, (ViBuf)data.data(), data.size(), &retCount);
//    // 通过VISA向仪器发送命令
//    //viWrite(vi, (ViBuf)cmd.c_str(), cmd.size(), &retCount);
//}



void BodeDrive::sendCommand(ViSession vi, const QString& cmd) {
    ViUInt32 retCount;
    log("send:"+cmd);
    // 1. 将 QString 转换为 QByteArray
    // 对于 SCPI 命令，通常使用 toLocal8Bit() 或 toLatin1()
    QByteArray buffer = cmd.toLocal8Bit();



    // 2. 确保命令以换行符 \n 结尾（如果输入没有带上的话）
    if (!buffer.endsWith('\n')) {
        buffer.append('\n');
    }

    // 3. 通过 VISA 接口写入数据
    viWrite(vi, (ViBuf)buffer.constData(), (ViUInt32)buffer.size(), &retCount);
    
    // 4. 可选：调试输出
    // qDebug() << "SENT:" << cmd.trimmed();
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



//QString BodeDrive::queryCommand(ViSession vi, const QString& cmd) {
//    // 1. 将 QString 转换为 QByteArray 以便通过 VISA 发送
//    // SCPI 命令通常使用本地 8-bit 编码或 UTF-8
//    QByteArray sendData = cmd.toLocal8Bit();
//    sendCommand(vi, sendData.data());
//
//    QByteArray response;
//    ViChar buffer[1024];
//    ViUInt32 retCount;
//    ViStatus status;
//
//    // 2. 循环读取直到检测到终止符
//    // 注意：Bode100 SCPI 通常以 '\n' (LF) 结尾
//    bool finished = false;
//    while (!finished) {
//        memset(buffer, 0, sizeof(buffer));
//        status = viRead(vi, (ViBuf)buffer, sizeof(buffer) - 1, &retCount);
//
//        if (status < VI_SUCCESS) {
//            // 这里可以添加异常处理逻辑，例如 break 或抛出信号
//            break;
//        }
//
//        QByteArray chunk = QByteArray(buffer, retCount);
//        response.append(chunk);
//
//        // 检查当前块或已收到的数据中是否包含换行符
//        if (chunk.contains('\n')) {
//            finished = true;
//        }
//    }
//
//    // 3. 将结果转换为 QString 返回（自动处理编码）
//    return QString::fromLocal8Bit(response).trimmed();
//}
// 
//  
 //  官方示例
QString BodeDrive::queryCommand(ViSession vi, const std::string& cmd) {

    ViChar buffer[1024]{}; // 每次读取1KB
    ViUInt32 retCount;

    sendCommandv2(vi, cmd);

    viRead(vi, (ViBuf)buffer, sizeof(buffer), &retCount);

    std::string currentChars = std::string(buffer, retCount);
    std::string response = currentChars;

    while (currentChars.find('\n') == std::string::npos)
    {
        viRead(vi, (ViBuf)buffer, sizeof(buffer), &retCount);

        currentChars = std::string(buffer, retCount);
        response += currentChars;

        //std::cout << "QUERY: " << cmd << std::endl;
    }
    QString result = QString::fromStdString(response);
    log(result);
    return result;
}
QString BodeDrive::queryCommandv3(const QString& cmd) {
    // 1. 基础状态检查 (完全照搬 queryIDN)
    if (!vi) return "Not Initialized";

    ViStatus status;
    ViUInt32 retCount;
    // 缓冲区开大一点 (1024)，应对比 *IDN? 稍微长一点的返回值
    char buffer[1024] = { 0 };

    // 2. 预处理指令：自动补全换行符并安全转换为 C 字符串
    QString finalCmd = cmd;
    if (!finalCmd.endsWith('\n')) {
        finalCmd += '\n';
    }

    // 这一步非常关键：必须用 QByteArray 中转，否则转换出的 const char* 会变成乱码
    QByteArray ba = finalCmd.toLocal8Bit();
    const char* cmdStr = ba.constData();

    // 3. 写入指令 (模仿 queryIDN)
    status = viWrite(vi, (ViBuf)cmdStr, (ViUInt32)ba.size(), &retCount);
    if (status < VI_SUCCESS) {
        // 将状态码转换为 16 进制，比如 0xBFFF000E
        QString hexCode = QString::number(status, 16).toUpper();
        QString errMsg = "Write Error: 0x" + hexCode;
        log("error:" + errMsg);
    }
    // 4. 清空缓冲区并读取 (完全照搬 queryIDN)
    memset(buffer, 0, sizeof(buffer));
    status = viRead(vi, (ViBuf)buffer, sizeof(buffer) - 1, &retCount);

    // 5. 提取并返回结果
    QString result = "";
    if (status >= VI_SUCCESS) {
        // 将成功读到的字节转换为 QString，并用 trimmed() 去掉末尾的 \n 或空格
        result = QString::fromLocal8Bit(buffer, retCount).trimmed();

        // 如果你想在界面上看到成功的返回，可以解除下面这行的注释
        // log("RECV: " + result); 
    }
    else {
        // 如果超时或出错
        // log("Read Error Status: " + QString::number(status, 16));
    }
    log("response:" + result);
    return result;
}
void BodeDrive::sendCommandv2(ViSession vi, const std::string& cmd) {

    ViUInt32 retCount;
    log("send" + QString::fromStdString(cmd));
    // 通过VISA向仪器发送命令
    viWrite(vi, (ViBuf)cmd.c_str(), cmd.size(), &retCount);

    // 在控制台打印发送的命令
    //cout << "SEND: " << cmd << endl;
}
// BodeDrive.cpp
//QString BodeDrive::queryCommand(ViSession vi,const char& cmd) {
//    if (this->vi == VI_NULL) log("未连接ViSession");
//
//    char buffer[1024] = { 0 };
//    ViUInt32 retCount;
//    ViStatus status;
//    
//    // 3. 通过 VISA 接口写入数据
//    viWrite(vi, (ViBuf)cmd, (ViUInt32)strlen, &retCount);
//    viRead(vi, (ViBuf)buffer, sizeof(buffer), &retCount);
//
//    std::string currentChars = std::string(buffer, retCount);
//    std::string response = currentChars;
//
//    while (currentChars.find('\n') == std::string::npos)
//    {
//        viRead(vi, (ViBuf)buffer, sizeof(buffer), &retCount);
//
//        currentChars = std::string(buffer, retCount);
//        response += currentChars;
//    }
//    QString res = QString::fromStdString(response);
//    log("response:"+res);
//    return res;
//}
//老版本询问命令
//QString BodeDrive::queryCommand(const std::string& cmd)
//{
//    if (!isConnected())
//        return "Not connected";
//
//    ViUInt32 retCount = 0;
//    char buffer[512] = { 0 };
//
//    viWrite(vi, (ViBuf)cmd.c_str(), cmd.size(), &retCount);
//
//    ViStatus status = viRead(vi, (ViBuf)buffer, sizeof(buffer) - 1, &retCount);
//
//    if (status >= VI_SUCCESS && retCount > 0)
//        return QString::fromUtf8(buffer, retCount);
//
//    return "";
//}

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
    QString opc = queryCommand(vi,"*OPC?\n");
    //queryCommand存在问题导致程序死锁，修改
    QString err = queryCommand(vi,"SYST:ERR?\n");
    //addLogtoGUI("信号与槽的日志显示");
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

    QString after3 = queryCommand(vi,":SENS:CORR:FULL:AVAI?\n");
    QString after2 = queryCommand(vi,":SENS:CORR:FULL:ENAB ON\n");
    QString after = queryCommand(vi,":SENS:CORR:FULL:ACT?\n");
    
    //QString after3 = queryCommand(":SENS:CORR:FULL:AVAI?\n");
    return after +  after3;
}

void BodeDrive::sendCommandData(const std::string& cmd) {

    ViUInt32 retCount;
    QString que = QString::fromStdString(cmd);
    log("send:" + que);
    // 通过VISA向仪器发送命令
    viWrite(vi, (ViBuf)cmd.c_str(), cmd.size(), &retCount);
}
//std::string BodeDrive::queryCommandDatav2(ViSession vi, const std::string& cmd)
//{
//    memset(buffer, 0, sizeof(buffer));
//    status = viRead(vi, (ViBuf)buffer, sizeof(buffer) - 1, &retCount);
//
//    QString idnResult = "Unknown Device";
//    if (status >= VI_SUCCESS) {
//        idnResult = QString::fromLocal8Bit(buffer).trimmed();
//    }
//}

//std::string BodeDrive::queryCommandData(ViSession vi, const std::string& cmd) {
//    QString que = QString::fromStdString(cmd);
//    log("query:"+que);
//    ViChar buffer[1024]{}; // 每次读取1KB
//    ViUInt32 retCount;
//
//    sendCommandData(vi, cmd);
//
//    viRead(vi, (ViBuf)buffer, sizeof(buffer), &retCount);
//
//    std::string currentChars = std::string(buffer, retCount);
//    std::string response = currentChars;
//
//    while (currentChars.find('\n') == std::string::npos)
//    {
//        viRead(vi, (ViBuf)buffer, sizeof(buffer), &retCount);
//
//        currentChars = std::string(buffer, retCount);
//        response += currentChars;
//
//        //cout << "QUERY: " << cmd << endl;
//    }
//    QString res = QString::fromStdString(response);
//    log("response:" + res);
//    return response;
//}



// //////////////////////////////////阻抗测量函数////////////////////////////////
//MeasureResult BodeDrive::performMeasurement(ViSession vi, SweepParams params)
//{
//    MeasureResult result;
//    result.success = false;
//
//    // 1. 申请仪器控制权 (防死锁)
//    sendCommandData(vi, ":SYST:LOCK:REL\n");
//    std::string lockStatus = queryCommandData(vi, ":SYST:LOCK:REQ?\n");
//    if (!lockStatus.contains("1") && !lockStatus.toUpper().contains("OK")) {
//        result.message = "获取仪器控制权失败，无法开始测量！";
//        return result;
//    }
//
//    // 2. 初始化 (注意：删除了 *RST 以保护校准数据，只保留 *CLS 清除错误队列)
//    sendCommand(vi, "*CLS\n");
//    sendCommand(vi, "*ESE 255\n"); // 开启错误检查
//
//    // 3. 写入用户配置的扫频参数
//    sendCommand(vi, ":CALC:PAR:DEF Z\n"); // 测阻抗
//    sendCommand(vi, ":SENS:FREQ:STAR " + params.startFreq + "\n");
//    sendCommand(vi, ":SENS:FREQ:STOP " + params.stopFreq + "\n");
//    sendCommand(vi, ":SENS:SWE:POIN " + QString::number(params.points) + "\n");
//    sendCommand(vi, ":SENS:SWE:TYPE " + params.sweepType + "\n");
//    sendCommand(vi, ":SENS:BAND " + params.bandwidth + "\n");
//
//    // 配置数据格式：线性幅值和相位 (Mag/Phase)
//    sendCommand(vi, ":CALC:FORM SLIN\n");
//
//    // 4. 触发测量
//    sendCommand(vi, ":TRIG:SOUR BUS\n"); // 设置为总线触发
//    sendCommand(vi, ":INIT\n");          // 初始化触发系统
//    sendCommand(vi, ":TRIG:SING\n");     // 发送单次触发指令
//
//    // 5. 【关键】延长超时时间并等待测量完成
//    // 扫频点数越多、带宽越窄，耗时越长。这里设个较长的时间，比如 60 秒
//    ViUInt32 originalTimeout;
//    viGetAttribute(vi, VI_ATTR_TMO_VALUE, &originalTimeout);
//    viSetAttribute(vi, VI_ATTR_TMO_VALUE, 60000); // 60秒超时
//
//    QString opc = queryCommand(vi, "*OPC?\n"); // 阻塞等待仪器扫频结束
//
//    viSetAttribute(vi, VI_ATTR_TMO_VALUE, originalTimeout); // 恢复超时时间
//
//    if (!opc.contains("1")) {
//        result.message = "测量超时或通信中断！";
//        sendCommand(vi, ":SYST:LOCK:REL?\n"); // 释放锁
//        return result;
//    }
//
//    // 6. 获取数据
//    QString freqDataStr = queryCommand( vi,":SENS:FREQ:DATA?\n");
//    QString measDataStr = queryCommand( vi,":CALC:DATA:SDAT?\n");
//
//    // 7. 解析数据并装入 QVector
//    QStringList freqList = freqDataStr.split(",", Qt::SkipEmptyParts);
//    QStringList measList = measDataStr.split(",", Qt::SkipEmptyParts);
//
//    for (const QString& f : freqList) {
//        result.frequencies.append(f.toDouble());
//    }
//
//    // SCPI SDAT 返回格式通常是成对的：[幅值1, 相位1, 幅值2, 相位2 ...]
//    for (int i = 0; i < measList.size() - 1; i += 2) {
//        result.magnitudes.append(measList[i].toDouble());
//        result.phases.append(measList[i + 1].toDouble());
//    }
//
//    // 8. 释放仪器控制权
//    sendCommand(vi, ":SYST:LOCK:REL?\n");
//
//    // 检查是否有系统错误 (SYST:ERR?) 这里略写，你可以加上之前写的 checkError 逻辑
//
//    result.success = true;
//    result.message = QString("测量完成！共获取 %1 个点的数据。").arg(result.frequencies.size());
//    return result;
//}

QString BodeDrive::checkError(ViSession vi, std::string when) {
   QString error = queryCommandv3(":SYST:ERR?\n");
    //QString result = QString::fromStdString(when + error);
    log(error);
    return error;
}

MeasureResult BodeDrive::performMeasurement(ViSession vi, SweepParams params)
{
    //sendCommand(vi, "*RST");
    ////checkError(vi, "checkerror:");
    //sendCommandData(vi, ":SYST:LOCK:REL\n");
    ////queryCommandData(vi, ":SYSTem:LOCK:OWNer?\n");
    
    QString lockOK = queryCommandv3(":SYST:LOCK:REQ? \n");

    //cout << "lock status: " << lockOK << endl;

    sendCommandData( "*CLS\n");  // 清除状态寄存器
    sendCommandData("*RST\n");  // 重置仪器

    queryCommandv3("*OPC?\n"); // 等待操作完成

    sendCommandData("*ESE 255\n"); // 启用错误事件寄存器

    checkError(vi, "After reset:"); // 检查错误队列


    /******************************************************
     * 配置测量类型
     *
     * Z 代表阻抗测量
     ******************************************************/
    sendCommandData(":CALC:PAR:DEF Z\n");

    queryCommandv3("*OPC?\n");


    /******************************************************
     * 配置频率扫描参数
     ******************************************************/

    sendCommandData(":SENS:FREQ:STAR " + params.startFreq + "kHz\n");

    sendCommandData(":SENS:FREQ:STOP " + params.stopFreq + "kHz\n");

    sendCommandData(":SENS:SWE:POIN " + std::to_string(params.points) + "\n");

    sendCommandData(":SENS:SWE:TYPE LOG\n");

    sendCommandData(":SENS:BAND " + params.bandwidth + "\n");

    checkError(vi, "After freq definition:");


    /******************************************************
     * 查询预计测量时间
     ******************************************************/
    QString time = queryCommandv3(":SENS:SWE:TIME?");

    //cout << "Time needed for the Measurement: " << time << "seconds" << endl;


    /******************************************************
     * 配置触发方式
     ******************************************************/

    sendCommandData(":CALC:FORM SLIN\n");

    sendCommandData(":TRIG:SOUR BUS\n");

    sendCommandData(":INIT\n");

    sendCommandData(":TRIG:SING\n");

    checkError(vi, "after trig config: ");


    /******************************************************
     * 等待测量完成
     ******************************************************/
    QString opc = queryCommandv3("*OPC?\n");

    //cout << "opc status: " << opc << endl;


    /******************************************************
     * 读取扫描频率数据
     ******************************************************/
    //QString frequencies = queryCommandv3(":SENS:FREQ:DATA?\n");

    //checkError(vi, "after freq data: ");


    ///******************************************************
    // * 读取测量数据
    // *
    // * SDAT 返回幅值和相位数据
    // ******************************************************/
    //QString allResults = queryCommandv3(":CALC:DATA:SDAT?\n");

    //checkError(vi, "after meas data: ");


    //cout << "results: " << endl << allResults << endl;

    //cout << "frequencies :" << endl << frequencies << endl;


    /******************************************************
     * 将字符串数据解析为浮点数组
     ******************************************************/
    //std::vector<float> magnitude_phase = parseResults(allResults.toStdString());

    //std::vector<float> freqValues = parseResults(frequencies.toStdString());


    ///******************************************************
    // * 示例：打印第一个测量点
    // ******************************************************/
    //std::cout << "Frequency: " << freqValues[0] << "Hz\t"
    //    << "Magnitude: " << magnitude_phase[0] << "Ohms\t"
    //    << "Phase: " << magnitude_phase[201] << "deg" << std::endl;


    ///******************************************************
    // * 释放设备锁
    // ******************************************************/
    //QString relok = queryCommandv3(":SYST:LOCK:REL?\n");

    ////std:: cout << "release status: " << relok << std::endl;


    ///******************************************************
    // * 关闭 VISA 会话
    // ******************************************************/
    //viClose(vi);
    //viClose(rm);


    ///******************************************************
    // * 计算测量总耗时
    // ******************************************************/
    //auto end = std::chrono::high_resolution_clock::now();
    //auto start = std::chrono::high_resolution_clock::now();

    //auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    //std::cout << "Measurement complete. Took "
    //    << duration.count()
    //    << " milliseconds"
    //    << std::endl;
    //MeasureResult measResult;
    //measResult.frequencies = freqValues;

    //// 注意：Bode100 返回的 SDAT 数据通常是 [Mag1, Mag2... MagN, Phase1, Phase2... PhaseN]
    //// 或者是交替的。根据示例代码，前 201 个是幅值，后 201 个是相位
    //int numPoints = freqValues.size();

    //// 提取幅值部分
    //measResult.magnitudes.assign(magnitude_phase.begin(),
    //    magnitude_phase.begin() + numPoints);

    //// 提取相位部分
    //measResult.phases.assign(magnitude_phase.begin() + numPoints,
    //    magnitude_phase.end());
    MeasureResult measResult;
    return measResult;
}
// //////////////////////////////////阻抗测量函数////////////////////////////////