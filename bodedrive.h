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
#include <QString>

// 1. 用户输入的扫频参数结构体
struct SweepParams {
    QString startFreq; // 例如 "10kHz" 或 "10000"
    QString stopFreq;  // 例如 "10MHz" 或 "10000000"
    int points;        // 扫频点数，例如 201
    QString sweepType; // "LIN" (线性) 或 "LOG" (对数)
    QString bandwidth; // 接收机带宽，例如 "300Hz"
};

// 2. 测量结果返回的结构体
struct MeasureResult {
    bool success;
    QString message;
    QVector<double> frequencies; // 频率数组
    QVector<double> magnitudes;  // 幅值数组 (欧姆)
    QVector<double> phases;      // 相位数组 (度)
};

class BodeDrive
{
public:
    BodeDrive();
    ~BodeDrive();
    enum class CalMode {
        Open,
        Short,
        Load
    };

    bool connectVisa(const QString& ip);
    bool startScpiRunner(const std::wstring& cmd, PROCESS_INFORMATION& pi);
    void sendCommand(ViSession vi, const QString& cmd);
    void disconnectVisa();
    //void sendCommand(ViSession vi, const std::string& cmd);
    QString queryIDN();
    //QString queryCommand(ViSession vi, const std::string& cmd);
    bool isConnected() const;
    QString queryCommand(const std::string& cmd);
    std::vector<float> parseResults(const std::string& data);
    QString bodeCalibration(ViSession vi, CalMode mode);
    QString bodeCalibrationCom(ViSession vi);
    MeasureResult performMeasurement(ViSession vi, SweepParams params);
private:

    ViSession rm = VI_NULL;
    ViSession vi = VI_NULL;
    PROCESS_INFORMATION scpiProcess{};
};
