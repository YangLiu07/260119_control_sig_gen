#pragma once
#include <QString>
#include <visa.h>
#include <iostream>
#include <stdio.h>
#include "C:\Program Files\IVI Foundation\VISA\Win64\Include\visa.h"
#include <vector>
#include <sstream>
#include <chrono>
#include <cstdlib>
#include <windows.h>
#include <QVector>
#include <functional>

// 1. 用户输入的扫频参数结构体
struct SweepParams {
    std::string startFreq; // 例如 "10kHz" 或 "10000"
    std::string stopFreq;  // 例如 "10MHz" 或 "10000000"
    int points;        // 扫频点数，例如 201
    std::string sweepType; // "LIN" (线性) 或 "LOG" (对数)
    std::string bandwidth; // 接收机带宽，例如 "300Hz"
};

// 2. 测量结果返回的结构体
struct MeasureResult {
    bool success;
    QString message;
    std::vector<float> frequencies;
    std::vector<float> magnitudes;
    std::vector<float> phases;
};

class BodeDrive
{
public:
    using LogFunc = std::function<void(const QString&)>;
    void setLogHandler(LogFunc func) {
        m_logHandler = func;
    }
    BodeDrive();
    ~BodeDrive();
    enum class CalMode {
        Open,
        Short,
        Load
    };
    void stopScpiRunner();
    bool connectVisa(const QString& ip);
    bool startScpiRunner(const std::wstring& cmd, PROCESS_INFORMATION& pi);
    void sendCommandv2(ViSession vi, const std::string& cmd);
    void sendCommand(ViSession vi, const QString& cmd);
    void disconnect();
    //void sendCommand(ViSession vi, const std::string& cmd);
    QString queryIDN();
    //QString queryCommand(ViSession vi, const std::string& cmd);
    bool isConnected() const;
    //QString queryCommand(const std::string& cmd);
    QString queryCommand(ViSession vi, const std::string& cmd);
    QString queryCommandv3(const QString& cmd);
    //QString BodeDrive::queryCommand(ViSession vi, const QString& cmd)
    std::vector<float> parseResults(const std::string& data);
    QString bodeCalibration(ViSession vi, CalMode mode);
    QString bodeCalibrationCom(ViSession vi);
    void sendCommandData(const std::string& cmd);
    //std::string queryCommandDatav2(ViSession vi, const std::string& cmd);
    //std::string queryCommandData(ViSession vi, const std::string& cmd);
    QString checkError(ViSession vi, std::string when);
    MeasureResult performMeasurement(ViSession vi, SweepParams params);

private:
    LogFunc m_logHandler = nullptr;

    // 内部调用的日志函数
    void log(const QString& msg) {
        if (m_logHandler) m_logHandler(msg);
    }
    ViSession vi = VI_NULL;
    ViSession rm=VI_NULL;
    PROCESS_INFORMATION scpiProcess{};
    PROCESS_INFORMATION pi = { 0 }; // 保存服务器进程信息
    bool isServerRunning = false;
};
