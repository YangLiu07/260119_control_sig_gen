/**************************************************************
 * 程序名称：Bode100 SCPI 自动测量示例
 *
 * 程序功能：
 * 本程序演示如何通过 VISA 接口和 SCPI 命令控制 Bode100
 * 网络分析仪进行阻抗扫描测量。
 *
 * 程序主要流程：
 * 1 启动 SCPI Runner 服务器程序
 * 2 等待 SCPI 服务器启动完成
 * 3 通过 TCPIP VISA 建立仪器通信
 * 4 发送 SCPI 命令配置测量参数
 * 5 触发一次扫描测量
 * 6 读取测量数据
 * 7 将字符串数据解析为浮点数数组
 * 8 输出测量结果
 * 9 释放设备锁并关闭 VISA 会话
 *
 **************************************************************/

#include <iostream>
#include <stdio.h>

 // VISA头文件，用于仪器通信
#include "C:\Program Files\IVI Foundation\VISA\Win64\Include\visa.h"

#include <vector>
#include <sstream>
#include <chrono>
#include <cstdlib>
#include <windows.h>

using namespace std;


/**************************************************************
 * 函数名称：sendCommand
 *
 * 功能：
 * 向仪器发送 SCPI 控制命令
 *
 * 参数：
 * vi  - VISA 会话句柄
 * cmd - 需要发送的 SCPI 命令字符串
 *
 * 说明：
 * 该函数通过 viWrite 将 SCPI 命令发送给仪器，
 * 并在控制台打印发送的命令，便于调试。
 **************************************************************/
void sendCommand(ViSession vi, const std::string& cmd) {

	ViUInt32 retCount;

	// 通过VISA向仪器发送命令
	viWrite(vi, (ViBuf)cmd.c_str(), cmd.size(), &retCount);

	// 在控制台打印发送的命令
	cout << "SEND: " << cmd << endl;
}


/**************************************************************
 * 函数名称：startScpiRunner
 *
 * 功能：
 * 启动 SCPI Runner 服务器程序
 *
 * 参数：
 * pi - Windows 进程信息结构体
 *
 * 说明：
 * SCPI Runner 是 Omicron 提供的后台程序，
 * 用于通过 TCP/IP Socket 提供 SCPI 接口。
 *
 * 该函数通过 Windows API CreateProcess
 * 启动 SCPI Runner，并隐藏其控制台窗口。
 *
 * 返回值：
 * true  - 启动成功
 * false - 启动失败
 **************************************************************/
bool startScpiRunner(PROCESS_INFORMATION& pi)
{
	STARTUPINFOW si{};
	si.cb = sizeof(si);

	// SCPI Runner 启动命令
	wchar_t cmd[] =
		L"D:\\software\\Omicorn\\OmicronLab.VectorNetworkAnalysis.ScpiRunner.exe -s LN919Y";

	BOOL result = CreateProcessW(
		NULL,
		cmd,
		NULL,
		NULL,
		FALSE,
		CREATE_NO_WINDOW,   // 不创建窗口，在后台运行
		NULL,
		NULL,
		&si,
		&pi);

	if (!result)
	{
		cout << "Failed to start SCPI Runner. Error: " << GetLastError() << endl;
		return false;
	}

	return true;
}


/**************************************************************
 * 函数名称：waitForServer
 *
 * 功能：
 * 等待 SCPI 服务器启动完成
 *
 * 说明：
 * 程序启动 SCPI Runner 后，需要等待服务器
 * 打开 TCPIP 5025 端口才能建立连接。
 *
 * 该函数通过循环尝试连接 VISA 资源，
 * 每秒检测一次服务器是否可用。
 *
 * 最长等待时间：15秒
 *
 * 返回值：
 * true  - 服务器已经可连接
 * false - 超时仍未启动
 **************************************************************/
bool waitForServer()
{
	ViSession rm;
	ViSession vi;

	// SCPI TCP/IP VISA资源地址
	const char* resource = "TCPIP0::192.168.137.1::5025::SOCKET";

	for (int i = 0; i < 15; i++) // 最多等待15秒
	{
		if (viOpenDefaultRM(&rm) >= VI_SUCCESS)
		{
			if (viOpen(rm, resource, VI_NULL, VI_NULL, &vi) >= VI_SUCCESS)
			{
				viClose(vi);
				viClose(rm);
				return true;
			}
		}

		Sleep(1000);
		cout << "Waiting for SCPI server..." << endl;
	}

	return false;
}


/**************************************************************
 * 函数名称：queryCommand
 *
 * 功能：
 * 发送 SCPI 查询命令并读取返回数据
 *
 * 参数：
 * vi  - VISA 会话
 * cmd - 查询命令
 *
 * 说明：
 * SCPI查询命令通常以 "?" 结尾，例如：
 * *IDN?
 *
 * 返回数据可能大于1KB，因此函数采用循环读取，
 * 直到检测到终止符 '\n' 为止。
 *
 * 返回值：
 * response - 仪器返回的完整字符串
 **************************************************************/
std::string queryCommand(ViSession vi, const std::string& cmd) {

	ViChar buffer[1024]{}; // 每次读取1KB
	ViUInt32 retCount;

	sendCommand(vi, cmd);

	viRead(vi, (ViBuf)buffer, sizeof(buffer), &retCount);

	string currentChars = std::string(buffer, retCount);
	string response = currentChars;

	while (currentChars.find('\n') == string::npos)
	{
		viRead(vi, (ViBuf)buffer, sizeof(buffer), &retCount);

		currentChars = std::string(buffer, retCount);
		response += currentChars;

		cout << "QUERY: " << cmd << endl;
	}

	return response;
}


/**************************************************************
 * 函数名称：checkError
 *
 * 功能：
 * 查询 SCPI 服务器错误队列
 *
 * 参数：
 * vi   - VISA 会话
 * when - 错误发生阶段说明
 *
 * 说明：
 * SCPI标准命令:
 * :SYST:ERR?
 *
 * 用于读取仪器错误队列。
 **************************************************************/
void checkError(ViSession vi, string when) {

	string error = queryCommand(vi, ":SYST:ERR?\n");

	cout << when << endl
		<< error << endl;
}


/**************************************************************
 * 函数名称：parseResults
 *
 * 功能：
 * 将测量返回字符串解析为浮点数组
 *
 * 参数：
 * data - 仪器返回的CSV字符串
 *
 * 示例：
 * "1.0,2.3,5.6,7.8"
 *
 * 返回：
 * vector<float> 测量数据数组
 **************************************************************/
std::vector<float> parseResults(const std::string& data) {

	std::vector<float> results;

	std::istringstream ss(data);
	std::string token;

	while (getline(ss, token, ','))
	{
		results.push_back(std::stof(token));
	}

	return results;
}


/**************************************************************
 * 函数名称：main
 *
 * 程序入口函数
 *
 * 功能：
 * 实现一次完整的 Bode100 阻抗扫描测量流程，包括：
 *
 * 1 启动 SCPI Runner 服务
 * 2 等待 SCPI TCP/IP 服务就绪
 * 3 建立 VISA 通信连接
 * 4 锁定仪器设备
 * 5 初始化仪器状态
 * 6 配置频率扫描参数
 * 7 触发一次测量
 * 8 读取测量数据
 * 9 解析数据
 * 10 打印结果
 * 11 释放设备锁
 * 12 关闭 VISA 会话
 *
 * 返回值：
 * 0  - 程序执行成功
 * -1 - 启动或连接失败
 **************************************************************/
int main() {

    /******************************************************
     * 启动 SCPI Runner 服务器
     *
     * SCPI Runner 是 Omicron 提供的后台程序，
     * 用于通过 TCP/IP Socket 提供 SCPI 接口。
     *
     * 如果启动失败，程序直接退出。
     ******************************************************/
    PROCESS_INFORMATION pi{};

    if (!startScpiRunner(pi))
        return -1;

    cout << "SCPI Runner started." << endl;


    /******************************************************
     * 等待 SCPI 服务器启动完成
     *
     * SCPI Runner 启动后需要一定时间初始化
     * TCPIP 5025 端口。
     *
     * waitForServer() 函数会尝试连接服务器，
     * 最长等待15秒。
     ******************************************************/
    if (!waitForServer())
    {
        cout << "SCPI server did not start." << endl;
        return -1;
    }

    cout << "SCPI server is ready." << endl;


    /******************************************************
     * 记录测量开始时间
     *
     * 使用高精度计时器统计测量耗时。
     ******************************************************/
    auto start = chrono::high_resolution_clock::now();


    /******************************************************
     * VISA 资源地址
     *
     * TCPIP0  - TCP/IP通信接口
     * IP地址  - Bode100 SCPI服务器地址
     * 5025    - SCPI标准端口
     * SOCKET  - 使用Socket通信
     ******************************************************/
    ViConstRsrc resource_name = "TCPIP0::192.168.137.1::5025::SOCKET";


    /******************************************************
     * 测量参数设置
     ******************************************************/

    int numOfPoints = 201;     // 扫描点数
    string startfreq = "10kHz"; // 起始频率
    string stopfreq = "10MAHz"; // 结束频率
    string bandwidth = "300Hz"; // 测量带宽


    cout << "Trying to connect to Visa resource " << resource_name << "\n";


    /******************************************************
     * 建立 VISA 会话
     *
     * rm - Resource Manager 资源管理器
     * vi - 仪器会话句柄
     ******************************************************/
    ViSession rm, vi;

    // 打开默认VISA资源管理器
    ViStatus status = viOpenDefaultRM(&rm);

    // 打开指定仪器资源
    status = viOpen(rm, resource_name, VI_NULL, VI_NULL, &vi);


    /******************************************************
     * 配置 VISA 通信属性
     ******************************************************/

     // 启用终止字符检测
    viSetAttribute(vi, VI_ATTR_TERMCHAR_EN, VI_TRUE);

    // 设置终止字符为换行符 '\n'
    viSetAttribute(vi, VI_ATTR_TERMCHAR, '\n');

    // 设置通信超时时间（毫秒）
    viSetAttribute(vi, VI_ATTR_TMO_VALUE, 4000);


    /******************************************************
     * 查询 SCPI 服务器设备信息
     *
     * *IDN? 是SCPI标准命令
     ******************************************************/
    char command[] = "*IDN?";

    string id = queryCommand(vi, command);

    cout << "SCPI client connected to SCPI Server: " << id << endl;


    /******************************************************
     * 请求锁定 Bode100 仪器
     *
     * 防止其他程序同时访问设备
     ******************************************************/
    string lockOK = queryCommand(vi, ":SYST:LOCK:REQ?\n");

    cout << "lock status: " << lockOK << endl;


    /******************************************************
     * 仪器初始化
     ******************************************************/

    sendCommand(vi, "*CLS\n");  // 清除状态寄存器
    sendCommand(vi, "*RST\n");  // 重置仪器

    queryCommand(vi, "*OPC?\n"); // 等待操作完成

    sendCommand(vi, "*ESE 255\n"); // 启用错误事件寄存器

    checkError(vi, "After reset:"); // 检查错误队列


    /******************************************************
     * 配置测量类型
     *
     * Z 代表阻抗测量
     ******************************************************/
    sendCommand(vi, ":CALC:PAR:DEF Z\n");

    queryCommand(vi, "*OPC?\n");


    /******************************************************
     * 配置频率扫描参数
     ******************************************************/

    sendCommand(vi, ":SENS:FREQ:STAR " + startfreq + "\n");

    sendCommand(vi, ":SENS:FREQ:STOP " + stopfreq + "\n");

    sendCommand(vi, ":SENS:SWE:POIN " + to_string(numOfPoints) + "\n");

    sendCommand(vi, ":SENS:SWE:TYPE LOG\n");

    sendCommand(vi, ":SENS:BAND " + bandwidth + "\n");

    checkError(vi, "After freq definition:");


    /******************************************************
     * 查询预计测量时间
     ******************************************************/
    string time = queryCommand(vi, ":SENS:SWE:TIME?");

    cout << "Time needed for the Measurement: " << time << "seconds" << endl;


    /******************************************************
     * 配置触发方式
     ******************************************************/

    sendCommand(vi, ":CALC:FORM SLIN\n");

    sendCommand(vi, ":TRIG:SOUR BUS\n");

    sendCommand(vi, ":INIT\n");

    sendCommand(vi, ":TRIG:SING\n");

    checkError(vi, "after trig config: ");


    /******************************************************
     * 等待测量完成
     ******************************************************/
    string opc = queryCommand(vi, "*OPC?\n");

    cout << "opc status: " << opc << endl;


    /******************************************************
     * 读取扫描频率数据
     ******************************************************/
    string frequencies = queryCommand(vi, ":SENS:FREQ:DATA?\n");

    checkError(vi, "after freq data: ");


    /******************************************************
     * 读取测量数据
     *
     * SDAT 返回幅值和相位数据
     ******************************************************/
    string allResults = queryCommand(vi, ":CALC:DATA:SDAT?\n");

    checkError(vi, "after meas data: ");


    cout << "results: " << endl << allResults << endl;

    cout << "frequencies :" << endl << frequencies << endl;


    /******************************************************
     * 将字符串数据解析为浮点数组
     ******************************************************/
    std::vector<float> magnitude_phase = parseResults(allResults);

    std::vector<float> freqValues = parseResults(frequencies);


    /******************************************************
     * 示例：打印第一个测量点
     ******************************************************/
    cout << "Frequency: " << freqValues[0] << "Hz\t"
        << "Magnitude: " << magnitude_phase[0] << "Ohms\t"
        << "Phase: " << magnitude_phase[201] << "deg" << endl;


    /******************************************************
     * 释放设备锁
     ******************************************************/
    string relok = queryCommand(vi, ":SYST:LOCK:REL?\n");

    cout << "release status: " << relok << endl;


    /******************************************************
     * 关闭 VISA 会话
     ******************************************************/
    viClose(vi);
    viClose(rm);


    /******************************************************
     * 计算测量总耗时
     ******************************************************/
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Measurement complete. Took "
        << duration.count()
        << " milliseconds"
        << endl;


    return 0;
}
