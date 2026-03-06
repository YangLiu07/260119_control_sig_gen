//#include <iostream>
//#include <stdio.h>
//#include "C:\Program Files\IVI Foundation\VISA\Win64\Include\visa.h"
//#include <cstdlib>
//#include <windows.h>
////#include <iostream>
//
//using namespace std;
//
////Sends commands to the instrument
//void sendCommand(ViSession vi, const std::string& cmd) {
//	ViUInt32 retCount;
//	viWrite(vi, (ViBuf)cmd.c_str(), cmd.size(), &retCount);
//}
//
////sends commands to the instrument
//// Reads response in a loop if response > 1kB
//// Stops when reading termination character \n
//std::string queryCommand(ViSession vi, const std::string& cmd) {
//	ViChar buffer[1024]{}; //Read 1kB every cycle
//	ViUInt32 retCount;
//	sendCommand(vi, cmd);
//	viRead(vi, (ViBuf)buffer, sizeof(buffer), &retCount);
//	string currentChars = std::string(buffer, retCount);
//	string response = currentChars;
//	while (currentChars.find('\n') == string::npos) {
//		viRead(vi, (ViBuf)buffer, sizeof(buffer), &retCount);
//		currentChars = std::string(buffer, retCount);
//		response += currentChars;
//	}
//	return response;
//}
//
//int main()
//{
//	ViConstRsrc resource_name = "TCPIP0::192.168.137.1::5025::SOCKET";
//
//	//open a visa session and
//	//enable termination character and set it to '\n'
//	//set desired timeout
//	ViSession rm, vi;
//	ViStatus status = viOpenDefaultRM(&rm);
//	status = viOpen(rm, resource_name, VI_NULL, VI_NULL, &vi);
//	viSetAttribute(vi, VI_ATTR_TERMCHAR_EN, VI_TRUE);
//	viSetAttribute(vi, VI_ATTR_TERMCHAR, '\n');
//	viSetAttribute(vi, VI_ATTR_TMO_VALUE, 4000);
//
//	//get id of the SCPI Server
//	char command[] = "*IDN?";
//	
//	string id = queryCommand(vi, command);
//	cout << "SCPI client connected to SCPI Server: " << id << endl;
//	cout << "2";
//	return 0;
//
//}

#include <iostream>
#include <string>
#include <windows.h>
#include "C:\\Program Files\\IVI Foundation\\VISA\\Win64\\Include\\visa.h"

using namespace std;

void sendCommand(ViSession vi, const std::string& cmd)
{
    ViUInt32 retCount;
    viWrite(vi, (ViBuf)cmd.c_str(), (ViUInt32)cmd.size(), &retCount);
}

string queryCommand(ViSession vi, const std::string& cmd)
{
    ViChar buffer[1024];
    ViUInt32 retCount;

    sendCommand(vi, cmd);

    string response;

    while (true)
    {
        ViStatus status = viRead(vi, (ViBuf)buffer, sizeof(buffer), &retCount);

        if (status < VI_SUCCESS)
            break;

        response.append(buffer, retCount);

        if (response.find('\n') != string::npos)
            break;
    }

    return response;
}

//bool startScpiRunner(PROCESS_INFORMATION& pi)
//{
//    STARTUPINFOW si{};
//    si.cb = sizeof(si);
//
//    wchar_t cmd[] =
//        L"D:\\software\\Omicorn\\OmicronLab.VectorNetworkAnalysis.ScpiRunner.exe -s LN919Y";
//
//    BOOL result = CreateProcessW(
//        NULL,
//        cmd,
//        NULL,
//        NULL,
//        FALSE,
//        CREATE_NEW_CONSOLE,
//        NULL,
//        NULL,
//        &si,
//        &pi);
//
//    if (!result)
//    {
//        cout << "Failed to start SCPI Runner. Error: " << GetLastError() << endl;
//        return false;
//    }
//
//    return true;
//}
bool startScpiRunner(PROCESS_INFORMATION& pi)
{
    STARTUPINFOW si{};
    si.cb = sizeof(si);

    wchar_t cmd[] =
        L"D:\\software\\Omicorn\\OmicronLab.VectorNetworkAnalysis.ScpiRunner.exe -s LN919Y";

    BOOL result = CreateProcessW(
        NULL,
        cmd,
        NULL,
        NULL,
        FALSE,
        CREATE_NO_WINDOW,   // 不创建窗口
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


bool waitForServer()
{
    ViSession rm;
    ViSession vi;

    const char* resource = "TCPIP0::127.0.0.1::5025::SOCKET";

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

int main()
{
    PROCESS_INFORMATION pi{};

    if (!startScpiRunner(pi))
        return -1;

    cout << "SCPI Runner started." << endl;
    
    if (!waitForServer())
    {
        cout << "SCPI server did not start." << endl;
        return -1;
    }

    cout << "SCPI server is ready." << endl;

    ViSession rm;
    ViSession vi;

    const char* resource = "TCPIP0::127.0.0.1::5025::SOCKET";

    if (viOpenDefaultRM(&rm) < VI_SUCCESS)
    {
        cout << "Failed to open VISA Resource Manager." << endl;
        return -1;
    }

    if (viOpen(rm, resource, VI_NULL, VI_NULL, &vi) < VI_SUCCESS)
    {
        cout << "Failed to connect to SCPI server." << endl;
        return -1;
    }

    viSetAttribute(vi, VI_ATTR_TERMCHAR_EN, VI_TRUE);
    viSetAttribute(vi, VI_ATTR_TERMCHAR, '\n');
    viSetAttribute(vi, VI_ATTR_TMO_VALUE, 5000);

    string id = queryCommand(vi, "*IDN?\n");

    cout << "Connected to SCPI server: " << id << endl;

    viClose(vi);
    viClose(rm);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

