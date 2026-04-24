#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "rigoldriver.h" // 引入驱动头文件
#include"bodedrive.h"
#include <QtConcurrent>
#include <QPointer>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
// 新建类测试
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();//这是析构函数，公共的

private slots:
    // 声明槽函数，这样 .cpp 里的函数才能对上号
    // void on_btnConnect_clicked();
    // void on_btnSetAmp_clicked();
    // void on_btnSetFreq_clicked();
    // void on_btnOutput_toggled(bool checked);
    void on_logContextMenu(const QPoint &pos); // ✨ 新增：处理右键菜单
    void on_btnSelfTest_clicked(); //自检按键槽函数
    void on_btnSweepConfig_clicked();//扫频配置按键槽函数
    void on_btnArbConfig_clicked();
    void on_btnSelectArb_clicked();
    void switchPage(QWidget *page);
    void on_btnBodeVisaConnect_clicked();
    void setConnectionLed(bool isConnected);
    void on_btnDisconnect_clicked();
    void on_btnOpenCali_clicked();

    void on_btnShortCali_clicked();
    void appendLog(const QString& msg, int level);//公共增加日志方法；level=0黑色消息，level=1黄色警告，level=2红色错误
    void on_btnLoadCali_clicked();

    void on_btnStartMeasurement_clicked();
    // 处理图表点击事件的槽函数
    //void onPlotCurveClicked(QCPAbstractPlottable* plottable, int dataIndex, QMouseEvent* event);

    
    // 页面切换函数
    void initMenuConnections();// 初始化菜单连接


private:
    Ui::MainWindow *ui;
    RigolDriver *rigol; // 声明驱动对象
    BodeDrive* bode;
    QString arbFilePath;     // 保存ARB波形文件路径
    //ViSession vi;
    class ChartManager; // 前置声明
    ChartManager* chartMgr = nullptr; // 图表管理器指针
    //QCPItemTracer* tracerCond; // 电导光标 (蓝线)
    //QCPItemTracer* tracerSusp; // 电纳光标 (红线)
    //QCPItemLine* vLine;        // 垂直参考线

    void initChart();
    //nullptr参数可选，可以指定不同的父亲，这是构造函数，公共的
        // --- Cursor 1 (实时游标 - 蓝色/红色) ---
    QCPItemTracer* tracerCond;
    QCPItemTracer* tracerSusp;
    QCPItemLine* vLine;

    // --- Cursor 2 (锁定游标 - 橙色) ---
    QCPItemTracer* tracerCond2;
    QCPItemTracer* tracerSusp2;
    QCPItemLine* vLine2;

    // --- 状态标志位 ---
    bool cursor2Active = false; // 记录 Cursor 2 是否被激活
    
    void cleanOldLogs(const QString &path);
    bool checkInstrument(RigolDriver* dev, QString addr, QString name);// 仪器自检函数
    bool validateSweepConfig(double &startFreq,         //扫频信号输入检测函数
                             double &stopFreq,
                             double &amplitude,
                             double &sweepTime,
                             int &stepCount,
                             QString &errorMsg);
    bool validateArbConfig(QString &filePath,   //自定义信号输入检测函数
                           double &sampleRate,
                           double &amplitude,
                           QString &errorMsg);

    void setTestControlsEnabled(bool enabled); // 统一控制测试按钮的状态
    template<typename WorkerFunc, typename UiUpdater>
    void executeAsync(WorkerFunc worker, UiUpdater uiUpdater)
    {
        // 1. 创建安全指针。如果 MainWindow 被销毁，safeThis 会自动变成 nullptr
        QPointer<MainWindow> safeThis(this);

        // 2. 将 [=] 改为明确捕获所需变量，避免意外拷贝大对象，并将 safeThis 传进去
        QtConcurrent::run([safeThis, worker, uiUpdater]() {

            // 3. 在后台线程执行耗时操作，并拿到结果
            auto result = worker();

            // 4. 切回主线程前，检查界面是否已经被用户关掉了
            if (safeThis) {
                QMetaObject::invokeMethod(safeThis, [safeThis, uiUpdater, result]() {
                    // 5. 回到主线程后再次确认界面存活（因为排队等待执行期间也可能被关掉）
                    if (safeThis) {
                        uiUpdater(result);
                    }
                    });
            }
            });
    }

};

#endif // MAINWINDOW_H
