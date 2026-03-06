#ifndef RIGOLDRIVER_H
#define RIGOLDRIVER_H

#include <QObject>
#include <QString>
#include <QDebug>

// 引入 VISA 标准头文件
#include "visa.h"

class RigolDriver : public QObject
{
    Q_OBJECT
public:
    explicit RigolDriver(QObject *parent = nullptr);//explicit是指禁止隐形转换数据类型
    ~RigolDriver();

    // --- 基础连接功能 ---
    bool connectDevice(QString resourceName); // 例如 "USB0::0x1AB1::..."
    void disconnectDevice();
    bool isConnected() const { return m_connected; }

    // --- 核心 SCPI 发送与读取 ---
    bool sendCmd(QString scpi);            // 只发送，不读回 (设置参数用)

    QString queryCmd(QString scpi);        // 发送并等待读取 (查询参数用)

    QString findRigolGen();

    void setSweep(double startFreq,        // 设置扫频参数
                               double stopFreq,
                               double amplitude,
                               double sweepTime,
                               int stepCount);

    void setArbWave(QString filePath,     //设置自定义信号参数
                    double sampleRate,
                    double amplitude);



    // --- 普源信号源专用功能封装 ---
    // 设置通道1频率
    void setFrequency(double kHz);
    // 设置通道1幅度 (Vpp)
    void setAmplitude(double vpp);
    // 设置波形 (SIN, SQU, RAMP, PULS, NOIS)
    void setWaveform(QString type);
    // 开关通道1输出
    void setOutputState(bool on);

signals:
    // 用于向界面发送日志消息
    void sigLog(QString message);

private:
    ViSession m_rm;      // Resource Manager (大管家)
    ViSession m_instr;   // Instrument Session (具体设备)
    bool m_connected;

    // 错误检查辅助函数
    bool checkStatus(ViStatus status, QString actionName);
};

#endif // RIGOLDRIVER_H
