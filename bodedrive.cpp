#include "BodeDrive.h"
#include <QStringList>
#include <iostream>
#include<QDebug>
#include <sstream>
#include <QElapsedTimer>
#include"mainwindow.h"
#include <chrono>
#include "qcustomplot.h"
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


//void BodeDrive::disconnect()
//{
//    //关闭vi会话
//    //sendCommandData(vi,"RST");
//    if (vi != VI_NULL)
//    {
//        viClose(vi);
//        vi = VI_NULL;
//    }
//
//    if (rm != VI_NULL)
//    {
//        viClose(rm);
//        rm = VI_NULL;
//    }
//
//
//
//}


void BodeDrive::disconnect()
{
    // ==========================================
    // 1. 释放仪器硬件锁与清理状态
    // ==========================================
    if (vi != VI_NULL) {
        log("正在安全释放仪器硬件控制权...");

        // 尝试释放排他锁，允许其他软件或前面板接管仪器
        // 加上 try-catch 防御，防止因为物理断线导致发指令崩溃
        try {
            // 清理错误队列
            sendCommand("*CLS\n");

            // 释放硬件锁并等待完成
            QString relStatus = queryCommand(":SYST:LOCK:REL?\n");
            if (relStatus.contains("1") || relStatus.contains("OK")) {
                log("硬件锁已成功释放。");
            }
            else {
                log("释放硬件锁超时或无响应，可能已物理断线。");
            }
        }
        catch (...) {
            log("释放硬件锁时发生异常，强制断开。");
        }

        // ==========================================
        // 2. 关闭 VISA 仪器会话句柄
        // ==========================================
        viClose(vi);
        vi = VI_NULL;
        log("VISA 仪器通信会话已关闭。");
    }

    // ==========================================
    // 3. 关闭 VISA 资源管理器句柄
    // ==========================================
    if (rm != VI_NULL) {
        viClose(rm);
        rm = VI_NULL;
        log("VISA 资源管理器已释放。");
    }

    // ==========================================
    // 4. 彻底清理系统后台进程
    // ==========================================
    // 调用你之前写好的强杀函数，确保端口 5025 被完全释放
    stopScpiRunner();

    log("=== 仪器已彻底断开连接 ===");
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
//void BodeDrive::stopScpiRunner() {
//    if (isServerRunning && pi.hProcess != NULL) {
//        // 1. 尝试关闭（如果服务器有退出机制，可以发送命令，没有的话直接强杀）
//        // TerminateProcess 是最直接清空服务器的方法
//        TerminateProcess(pi.hProcess, 0);
//
//        // 2. 必须关闭句柄，否则会造成内核资源泄漏
//        CloseHandle(pi.hProcess);
//        CloseHandle(pi.hThread);
//
//        // 3. 重置状态
//        pi = { 0 };
//        isServerRunning = false;
//        log("SCPI Server stopped and cleaned up.");
//    }
//}
void BodeDrive::stopScpiRunner()
{
    // 1. 尝试通过 Windows 句柄杀进程
    if (isServerRunning && pi.hProcess != NULL) {
        TerminateProcess(pi.hProcess, 0);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        pi = { 0 };
    }

    //防止句柄丢失导致的僵尸进程，直接按进程名系统级强杀
    //
    QString processName = "OmicronLab.VectorNetworkAnalysis.ScpiRunner.exe";
    QProcess::execute("taskkill", QStringList() << "-im" << processName << "-f");

    isServerRunning = false;
    log("SCPI 服务器已强制关闭并清理内存。");
}


//QString BodeDrive::queryCommand(const QString& cmd) {
//    // 1. 基础状态检查 (完全照搬 queryIDN)
//    if (!vi) return "Not Initialized";
//
//    ViStatus status;
//    ViUInt32 retCount;
//    // 缓冲区开大一点 (1024)，应对比 *IDN? 稍微长一点的返回值
//    char buffer[1024] = { 0 };
//
//    // 2. 预处理指令：自动补全换行符并安全转换为 C 字符串
//    QString finalCmd = cmd;
//    if (!finalCmd.endsWith('\n')) {
//        finalCmd += '\n';
//    }
//
//    // 这一步非常关键：必须用 QByteArray 中转，否则转换出的 const char* 会变成乱码
//    QByteArray ba = finalCmd.toLocal8Bit();
//    const char* cmdStr = ba.constData();
//
//    // 3. 写入指令 (模仿 queryIDN)
//    status = viWrite(vi, (ViBuf)cmdStr, (ViUInt32)ba.size(), &retCount);
//    if (status < VI_SUCCESS) {
//        // 将状态码转换为 16 进制，比如 0xBFFF000E
//        QString hexCode = QString::number(status, 16).toUpper();
//        QString errMsg = "Write Error: 0x" + hexCode;
//        log("error:" + errMsg);
//    }
//    // 4. 清空缓冲区并读取 (完全照搬 queryIDN)
//    memset(buffer, 0, sizeof(buffer));
//    status = viRead(vi, (ViBuf)buffer, sizeof(buffer) - 1, &retCount);
//
//    // 5. 提取并返回结果
//    QString result = "";
//    if (status >= VI_SUCCESS) {
//        // 将成功读到的字节转换为 QString，并用 trimmed() 去掉末尾的 \n 或空格
//        result = QString::fromLocal8Bit(buffer, retCount).trimmed();
//
//        // 如果你想在界面上看到成功的返回，可以解除下面这行的注释
//        // log("RECV: " + result); 
//    }
//    else {
//        // 如果超时或出错
//        // log("Read Error Status: " + QString::number(status, 16));
//    }
//    log("response:" + result);
//    return result;
//}


QString BodeDrive::queryCommand(const QString& cmd) {
    if (!vi) return "Not Initialized";

    ViStatus status;
    ViUInt32 retCount;

    // 1. 预处理指令
    QString finalCmd = cmd;
    if (!finalCmd.endsWith('\n')) {
        finalCmd += '\n';
    }

    QByteArray ba = finalCmd.toLocal8Bit();
    const char* cmdStr = ba.constData();

    // 2. 写入指令
    status = viWrite(vi, (ViBuf)cmdStr, (ViUInt32)ba.size(), &retCount);
    if (status < VI_SUCCESS) {
        QString hexCode = QString::number(status, 16).toUpper();
        log("Write Error: 0x" + hexCode);
        return "";
    }

    // ====================================================
    // 3. 核心修复：循环分块读取大段数据
    // ====================================================
    QByteArray responseData; // 动态扩容的字节数组，用来拼接所有数据
    char buffer[2048];       // 每次读取的块大小 (2KB)

    do {
        memset(buffer, 0, sizeof(buffer));

        // 尝试读取一块数据
        status = viRead(vi, (ViBuf)buffer, sizeof(buffer) - 1, &retCount);

        if (status >= VI_SUCCESS) {
            // 将本次读到的数据拼接到总容器中
            responseData.append(buffer, retCount);
        }

        // VI_SUCCESS_MAX_CNT 是 VISA 库的宏：表示本次读取是因为填满了缓冲区而停止的，
        // 说明仪器手里还有数据没发完，必须继续 do-while 循环。
    } while (status == VI_SUCCESS_MAX_CNT);

    // ====================================================
    // 4. 提取并返回最终结果
    // ====================================================
    QString result = "";
    if (status >= VI_SUCCESS || status == VI_SUCCESS_MAX_CNT) {
        result = QString::fromLocal8Bit(responseData).trimmed();
    }
    else {
        // 如果发生了超时或其他读取错误
        log("Read Error Status: " + QString::number(status, 16).toUpper());
    }

    // 如果日志太长会导致界面卡顿，对于长数据（比如长度大于100），可以选择不打印全文
    if (result.length() < 200) {
        log("response: " + result);
    }
    else {
        log("response: [Data too long, length=" + QString::number(result.length()) + " bytes]");
    }

    return result;
}

std::vector<float> BodeDrive::parseResults(const std::string& data)
{
    std::vector<float> results;
    std::istringstream ss(data);
    std::string token;

    while (getline(ss, token, ','))
    {
        // 去除字符串首尾的空格和换行符
        token.erase(0, token.find_first_not_of(" \t\r\n"));
        token.erase(token.find_last_not_of(" \t\r\n") + 1);

        if (token.empty()) continue; // 跳过空字符串

        try {
            // 🌟 加上 try-catch，防止解析非法字符引发闪退
            results.push_back(std::stof(token));
        }
        catch (...) {
            // 解析失败时，静默忽略当前非法数字，保证程序活下去
            continue;
        }
    }

    return results;
}

QString BodeDrive::bodeCalibration(CalMode mode)
{
    QString modeStr;
    switch (mode) {
    case CalMode::Open:  modeStr = "OPEN"; break;
    case CalMode::Short: modeStr = "SHOR"; break;
    case CalMode::Load:  modeStr = "LOAD"; break;
    }
    QString fullCmd = QString(":SENS:CORR:FULL:%1\n").arg(modeStr);
    std::string coli = fullCmd.toStdString();
    sendCommand(coli);
    QString opc = queryCommand("*OPC?\n");
    //queryCommand存在问题导致程序死锁，修改
    QString err = queryCommand("SYST:ERR?\n");
    //addLogtoGUI("信号与槽的日志显示");
    QString ss = err+opc;
    return ss;
}

void BodeDrive::sendCommand(const std::string& cmd) {

    ViUInt32 retCount;
    QString que = QString::fromStdString(cmd);
    log("send:" + que);
    // 通过VISA向仪器发送命令
    viWrite(vi, (ViBuf)cmd.c_str(), cmd.size(), &retCount);
}


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


//MeasureResult BodeDrive::performMeasurement(SweepParams params)
//{
//    //sendCommand(vi, "*RST");
//    ////checkError(vi, "checkerror:");
//    //sendCommandData(vi, ":SYST:LOCK:REL\n");
//    ////queryCommandData(vi, ":SYSTem:LOCK:OWNer?\n");
//    
//    QString lockOK = queryCommand(":SYST:LOCK:REQ? \n");
//
//    //cout << "lock status: " << lockOK << endl;
//
//    sendCommand( "*CLS\n");  // 清除状态寄存器
//    sendCommand("*RST\n");  // 重置仪器
//
//    queryCommand("*OPC?\n"); // 等待操作完成
//
//    sendCommand("*ESE 255\n"); // 启用错误事件寄存器
//
//    //checkError(vi, "After reset:"); // 检查错误队列
//
//
//    /******************************************************
//     * 配置测量类型
//     *
//     * Z 代表阻抗测量
//     ******************************************************/
//    //sendCommand(":CALC:PAR:DEF Z\n");
//
//    //queryCommand("*OPC?\n");
//
//
//    /******************************************************
//     * 配置频率扫描参数
//     ******************************************************/
//
//    sendCommand(":SENS:FREQ:STAR " + params.startFreq + "kHz\n");
//
//    sendCommand(":SENS:FREQ:STOP " + params.stopFreq + "kHz\n");
//
//    sendCommand(":SENS:SWE:POIN " + std::to_string(params.points) + "\n");
//
//    sendCommand(":SENS:SWE:TYPE LOG\n");
//
//    sendCommand(":SENS:BAND " + params.bandwidth + "\n");
//
//    //checkError("After freq definition:");
//
//
//    /******************************************************
//     * 查询预计测量时间
//     ******************************************************/
//    QString time = queryCommand(":SENS:SWE:TIME?");
//
//    //cout << "Time needed for the Measurement: " << time << "seconds" << endl;
//
//
//    /******************************************************
//     * 配置触发方式
//     ******************************************************/
//
//    sendCommand(":CALC:FORM SLIN\n");
//
//    sendCommand(":TRIG:SOUR BUS\n");
//
//    sendCommand(":INIT\n");
//
//    sendCommand(":TRIG:SING\n");
//
//    //checkError(vi, "after trig config: ");
//
//
//    /******************************************************
//     * 等待测量完成
//     ******************************************************/
//    QString opc = queryCommand("*OPC?\n");
//
//    //cout << "opc status: " << opc << endl;
//
//
//    /******************************************************
//     * 读取扫描频率数据
//     ******************************************************/
//    QString frequencies = queryCommand(":SENS:FREQ:DATA?\n");
//    queryCommand(":SYST:ERR?\n");
//
//    //checkError(vi, "after freq data: ");
//
//
//    ///******************************************************
//    // * 读取测量数据
//    // *
//    // * SDAT 返回幅值和相位数据
//    // ******************************************************/
//    QString allResults = queryCommand(":CALC:DATA:SDAT?\n");
//
//    //checkError(vi, "after meas data: ");
//
//
//    //cout << "results: " << endl << allResults << endl;
//
//    //cout << "frequencies :" << endl << frequencies << endl;
//
//
//    /******************************************************
//     * 将字符串数据解析为浮点数组
//     ******************************************************/
//    std::vector<float> magnitude_phase = parseResults(allResults.toStdString());
//
//    std::vector<float> freqValues = parseResults(frequencies.toStdString());
//
//
//    ///******************************************************
//    // * 示例：打印第一个测量点
//    // ******************************************************/
//    //std::cout << "Frequency: " << freqValues[0] << "Hz\t"
//    //    << "Magnitude: " << magnitude_phase[0] << "Ohms\t"
//    //    << "Phase: " << magnitude_phase[201] << "deg" << std::endl;
//
//
//    ///******************************************************
//    // * 释放设备锁
//    // ******************************************************/
//    QString relok = queryCommand(":SYST:LOCK:REL?\n");
//
//    ////std:: cout << "release status: " << relok << std::endl;
//
//
//    ///******************************************************
//    // * 关闭 VISA 会话
//    // ******************************************************/
//    //viClose(vi);
//    //viClose(rm);
//
//
//    ///******************************************************
//    // * 计算测量总耗时
//    // ******************************************************/
//    auto end = std::chrono::high_resolution_clock::now();
//    auto start = std::chrono::high_resolution_clock::now();
//
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//
//    std::cout << "Measurement complete. Took "
//        << duration.count()
//        << " milliseconds"
//        << std::endl;
//    MeasureResult measResult;
//    measResult.frequencies = freqValues;
//
//    //// 注意：Bode100 返回的 SDAT 数据通常是 [Mag1, Mag2... MagN, Phase1, Phase2... PhaseN]
//    //// 或者是交替的。根据示例代码，前 201 个是幅值，后 201 个是相位
//    //int numPoints = freqValues.size();
//
//    // 提取幅值部分
//    measResult.magnitudes.assign(magnitude_phase.begin(),
//        magnitude_phase.begin() + numPoints);
//
//    // 提取相位部分
//    measResult.phases.assign(magnitude_phase.begin() + numPoints,
//        magnitude_phase.end());
//    MeasureResult measResult;
//    return measResult;
//}
// 
// 
MeasureResult BodeDrive::performMeasurement(SweepParams params)
{
    MeasureResult result;
    result.success = false;

    // 使用 Qt 的高精度计时器替代 chrono，代码更简洁
    QElapsedTimer timer;
    timer.start();

    // ==========================================
    // 1. 申请仪器控制权 (对应 Python 的 lockOk)
    // ==========================================
    QString lockOK = queryCommand(":SYST:LOCK:REQ?\n");
    if (!lockOK.contains("1")) {
        result.message = "锁定仪器失败，可能被其他程序占用！";
        return result;
    }

    // ==========================================
    // 2. 清理与复位 (商业规范兜底)
    // ==========================================
    sendCommand("*CLS\n");
    sendCommand("*RST\n");
    queryCommand("*OPC?\n");

    // ==========================================
    // 3. 配置测量模式为单端口阻抗 (对应 Python)
    // ==========================================
    sendCommand(":CALC:PAR:DEF Z\n");
    sendCommand(":CALC:FORM SLIN\n"); // 线性幅值(欧姆) + 相位(度)

    // ==========================================
    // 4. 配置频率扫描参数
    // ==========================================
    // 注意：假设 params.startFreq 是纯数字字符串，需要补上单位
    sendCommand(":SENS:FREQ:STAR " + params.startFreq + "kHz\n");
    sendCommand(":SENS:FREQ:STOP " + params.stopFreq + "kHz\n");
    sendCommand(":SENS:SWE:POIN " + std::to_string(params.points) + "\n");

    // 假设 params 结构体中有 sweepType 成员，对应 Python 的 Sweep_type
    // 如果没有，你可以直接写死为 sendCommand(":SENS:SWE:TYPE LOG\n");
    sendCommand(":SENS:SWE:TYPE " + params.sweepType + "\n");
    sendCommand(":SENS:BAND " + params.bandwidth + "\n");

    // ==========================================
    // 5. 配置触发系统并开始 (对应 Python)
    // ==========================================
    sendCommand(":TRIG:SOUR BUS\n");
    sendCommand(":INIT:CONT ON\n"); // Python 中强调：让触发器保持就绪，等待单一触发
    sendCommand(":TRIG:SING\n");

    // ==========================================
    // 6. 阻塞等待测量完成
    // ==========================================
    QString opc = queryCommand("*OPC?\n");
    if (!opc.contains("1")) {
        result.message = "测量超时或未正常完成";
        queryCommand(":SYST:LOCK:REL?\n"); // 发生异常也必须解锁
        return result;
    }

    // ==========================================
    // 7. 获取原始数据
    // ==========================================
    QString allResultsStr = queryCommand(":CALC:DATA:SDAT?\n");
    QString frequenciesStr = queryCommand(":SENS:FREQ:DATA?\n");

    // ==========================================
    // 8. 解析与切割数组 (完全对标 Python 的切片逻辑)
    // ==========================================
    std::vector<float> magnitude_phase = parseResults(allResultsStr.toStdString());
    std::vector<float> freqValues = parseResults(frequenciesStr.toStdString());

    int numPoints = freqValues.size();

    // 安全校验：返回的幅值+相位总数据量必须 >= 频率点数的 2 倍
    if (numPoints > 0 && magnitude_phase.size() >= 2 * numPoints) {
        result.frequencies = freqValues;

        // 提取幅值部分 (对应 Python: magnitude_raw = allResults_list_raw[0:Number_of_measurement_points])
        result.magnitudes.assign(magnitude_phase.begin(), magnitude_phase.begin() + numPoints);

        // 提取相位部分 (对应 Python: phase_raw = allResults_list_raw[Number_of_measurement_points:len])
        result.phases.assign(magnitude_phase.begin() + numPoints, magnitude_phase.begin() + 2 * numPoints);

        result.success = true;
        result.message = QString("测量完成, 共抓取 %1 个点，耗时 %2 ms")
            .arg(numPoints).arg(timer.elapsed());
    }
    else {
        result.message = "数据解析异常：返回的数据长度与频率点数不匹配！";
    }

    // ==========================================
    // 9. 释放设备控制权 (对应 Python 的 finally)
    // ==========================================
    queryCommand(":SYST:LOCK:REL?\n");
    queryCommand("*OPC?\n"); // 等待释放动作完成

    return result;
}
// //////////////////////////////////阻抗测量函数////////////////////////////////