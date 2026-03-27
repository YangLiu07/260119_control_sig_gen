#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime> // 必须引入这个
#include <QFile> // 必须引入这个
#include <QMenu>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QProcess>
#include <QScrollBar>
#include <QMessageBox>
#include <QFileDialog>
#include <windows.h>
#include "bodedrive.h"
#include <QtConcurrent>





enum LogLevel //枚举类型，一组有名字的整数常量 日志等级增加代码可读性
{
    LOG_INFO = 0,
    LOG_SUCCESS,
    LOG_WARNING,
    LOG_ERROR
};

namespace DG1032Spec
{
const double MIN_FREQ = 0.001;          // kHz
const double MAX_FREQ = 30000;

const double MIN_AMP = 0.001;           // V
const double MAX_AMP = 20.0;

const double MIN_TIME = 0.001;          // s
const double MAX_TIME = 500.0;

const int MIN_STEP = 2;
const int MAX_STEP = 65535;

const double MIN_ARB_SAMPLE = 0.001;     // kSa/s
const double MAX_ARB_SAMPLE = 200000;    // kSa/s

const double MIN_ARB_AMP = 0.001;        // V
const double MAX_ARB_AMP = 10.0;         // V
}

namespace Bode100Spec
{
    const std::wstring command =
        L"D:\\software\\Omicorn\\OmicronLab.VectorNetworkAnalysis.ScpiRunner.exe -s LN919Y";

    const double MIN_FREQ = 0.01;
    const double MAX_FREQ = 40000;


}

//编写public函数MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //初始化ui界面，实例化
    ui->setupUi(this);

    // 1. 初始化驱动对象，实例化对象？
    rigol = new RigolDriver(this);

    bode = new BodeDrive();
    bode->setLogHandler([this](const QString& msg) {
        this->appendLog(msg,LOG_INFO);
        });
    //connect(bode, &BodeDrive::logAvailable, this, &MainWindow::appendLog);

    //初始化菜单连接
    initMenuConnections();

    //Qt 信号槽机制 + Lambda 表达式 将sigLog的信息传递到ui界面的日志中
   connect(rigol, &RigolDriver::sigLog, this, [=](QString msg){
        this->appendLog(msg,LOG_INFO); });

    //设置日志框允许自定义右键菜单
    ui->textBrowserLog->setContextMenuPolicy(Qt::CustomContextMenu);

    //连接“请求弹出菜单”的信号到我们的槽函数
    connect(ui->textBrowserLog, &QWidget::customContextMenuRequested,
            this, &MainWindow::on_logContextMenu);

    //切换信号源模式 扫频/自定义信号
    connect(ui->comboBox_selectWaweMode_2,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            ui->stackedWidget_2,
            &QStackedWidget::setCurrentIndex);


    // 在构造函数中对信号源频率范围进行设定
    QDoubleValidator *freqValidator = new QDoubleValidator(0.001, 30000, 6, this);
    freqValidator->setNotation(QDoubleValidator::ScientificNotation);

    ui->editSweepFreqStart->setValidator(freqValidator);
    ui->editSweepFreqEnd->setValidator(freqValidator);

}

//析构函数
MainWindow::~MainWindow()
{
    if (bode) {
        // 第一步：初始化/复位设备（发送 SCPI 命令）
        // 建议在断开前发送，因为断开后就发不了了
        bode->sendCommand(vi,"* RST\n");

        // 第二步：关闭 VISA 会话 (viClose)
        bode->disconnect();

        // 第三步：强制杀掉服务器进程并清空句柄
        bode->stopScpiRunner();

        delete bode;
        bode = nullptr;
    }
    delete ui;
}

// /////////////////////////////////////////日志管理////////////////////////////

//日志生成方法
void MainWindow::appendLog(const QString &msg, int LogLevel)
{
    // --- 1. 处理界面显示 (UI Logic) ---
    QString color = (LogLevel == 3) ? "red" : (LogLevel == 2) ? "orange" :(LogLevel == 1 ? "green" : "black");
    QString levelStr = (LogLevel == 3) ? "[ERROR]" :(LogLevel == 2) ? "[WARNING]" : (LogLevel == 1 ? "[SUCCESS]" : "[INFO]");

    QDateTime current = QDateTime::currentDateTime();
    QString timeStr = current.toString("[yyyy-MM-dd hh:mm:ss]");
    QString plainText = QString("%1 %2 %3").arg(timeStr, levelStr, msg);
    QString htmlText = QString("<font color='%1'>%2</font>").arg(color, plainText);

    ui->textBrowserLog->append(htmlText);
    ui->textBrowserLog2->append(htmlText);
    // --- 2. 处理文件写入 (File Logic) ---
    // 获取当前程序运行目录下的 Logs 文件夹（避免把根目录弄乱）
    QString logDir = QCoreApplication::applicationDirPath() + "/Logs";
    QDir dir(logDir);
    if (!dir.exists()) {
        dir.mkpath("."); // 如果 Logs 文件夹不存在，就创建它
    }

    // 生成当天的文件名，例如 "2026-01-20.log"
    QString dateStr = current.toString("yyyy-MM-dd");
    QString logFilePath = QString("%1/%2.log").arg(logDir, dateStr);

    QFile file(logFilePath);
    // 使用 Append 模式：每次写入都加在文件末尾，不覆盖旧内容
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << plainText << "\n";
        file.close();

    }

    // QScrollBar *bar = ui->textBrowserLog->verticalScrollBar();
    // bar->setValue(bar->maximum());

    // --- 3. 自动清理旧日志 (Cleanup Logic) ---
    // 为了不影响性能，我们可以加个判断：只有在每天第一次写日志，或者程序启动时清理一次
    // 这里简单起见，每次写日志都检查一下（实际上文件操作很快，影响不大）
    static bool hasCleaned = false; // 静态变量，保证程序运行期间只清理一次
    if (!hasCleaned) {
        cleanOldLogs(logDir);
        hasCleaned = true;
    }
}
//日志清理
void MainWindow::cleanOldLogs(const QString &path)
{
    QDir dir(path);
    // 只扫描 .log 文件
    dir.setNameFilters(QStringList() << "*.log");
    //以此获取文件列表：包含文件名、文件信息
    dir.setFilter(QDir::Files | QDir::NoSymLinks);

    QFileInfoList list = dir.entryInfoList();

    // 获取当前时间，计算一年前的时间点
    QDateTime now = QDateTime::currentDateTime();
    QDateTime oneYearAgo = now.addDays(-365); // 也可以用 addMonths(-12)

    foreach (QFileInfo fileInfo, list) {
        // 方法 A：按文件名里的日期判断（最准确）
        // 假设文件名格式严格为 "yyyy-MM-dd.log"
        QString fileName = fileInfo.baseName(); // 拿到 "2026-01-20"
        QDate fileDate = QDate::fromString(fileName, "yyyy-MM-dd");

        if (fileDate.isValid()) {
            if (fileDate < oneYearAgo.date()) {
                QFile::remove(fileInfo.absoluteFilePath());
                // 这里不能用 appendLog，否则会死循环递归，直接用 qDebug
                qDebug() << "已清理过期日志文件：" << fileInfo.fileName();
            }
        }

        // 方法 B：按文件“最后修改时间”判断（简单但如果有人修改了旧文件会失效）
        // if (fileInfo.lastModified() < oneYearAgo) {
        //     QFile::remove(fileInfo.absoluteFilePath());
        // }
    }
}
//日志右键查看功能
void MainWindow::on_logContextMenu(const QPoint &pos){
    // 1. 创建菜单对象
    QMenu *menu = ui->textBrowserLog->createStandardContextMenu();
    // createStandardContextMenu() 会保留默认的“复制/全选”功能，非常方便！

    menu->addSeparator(); // 加一条分割线，美观

    // 2. 添加“清空日志”动作
    QAction *actClear = menu->addAction("🗑️ 清空日志");
    connect(actClear, &QAction::triggered, this, [=](){
        ui->textBrowserLog->clear();
    });

    // 3. 添加“打开日志文件夹”动作
    // 在 on_logContextMenu 函数里修改这一行：
    QAction *actOpenDir = menu->addAction("📂 打开日志目录");
    connect(actOpenDir, &QAction::triggered, this, [=](){
        // 修改路径为 Logs 子目录
        QString logPath = QCoreApplication::applicationDirPath() + "/Logs";

        // 如果文件夹还没生成过（比如刚运行还没写日志），先创建一下，不然打开会失败
        QDir dir(logPath);
        if (!dir.exists()) dir.mkpath(".");

        QDesktopServices::openUrl(QUrl::fromLocalFile(logPath));
    });


    // 4. 在鼠标点击的位置弹出菜单
    menu->exec(ui->textBrowserLog->mapToGlobal(pos));

    // 5. 清理内存 (menu 是 new 出来的，用完要删，但在 exec() 后删是安全的)
    delete menu;
}

// /////////////////////////////////////////日志管理////////////////////////////
// ----------------------------------------------------------------------------

// ////////////////////////////////////////自检功能实现/////////////////////////////
void MainWindow::on_btnSelfTest_clicked()
{
    ui->textBrowserLog->clear();
    appendLog("===== 开始仪器自检 =====",LOG_INFO);

    bool ok1 = checkInstrument(rigol,
                             ui->lineEditDGAddress->text(),
                               "信号源");

    // ------------数采的自检代码尚未实现，缺少驱动代码-----------------
    // bool ok2 = checkInstrument(daq,
    //                            ui->lineEditMRAddress->text(),
    //                            "数据采集仪");
    bool ok2=1;

    if(ok1 && ok2)
        appendLog("===== 全部设备正常 =====",LOG_INFO);
    else
        appendLog("===== 存在异常设备 =====",LOG_WARNING);
}


// 自检函数封装
bool MainWindow::checkInstrument(RigolDriver* dev, QString addr, QString name)
{
    appendLog("检测 " + name + "...",LOG_INFO);

    if(dev->connectDevice(addr))
    {
        // QString idn = dev->sendCmd("*IDN?");
        appendLog(name + " 连接成功",LOG_SUCCESS);
        // ui->textBrowserLog->append("IDN: " + idn);
        return true;
    }
    else
    {
        appendLog(name + " 连接失败！",LOG_ERROR);
        return false;
    }
}

// ///////////////////////////////////////扫频信号配置页面逻辑实现/////////////////////////
/// \brief MainWindow::on_btnSweepConfig_clicked
/// 槽函数仅对逻辑流程进行定义，具体驱动实现与控制再次进行封装
void MainWindow::on_btnSweepConfig_clicked()
{
    double startFreq;
    double stopFreq;
    double amplitude;
    double sweepTime;
    int stepCount;

    QString errorMsg;

     rigol->sendCmd(":SOUR1:SWE:STAT ON");

    if(!validateSweepConfig(startFreq,stopFreq,amplitude,sweepTime,stepCount,errorMsg))
    {
        QMessageBox::warning(this,"输入错误",errorMsg);
        return;
    }

    rigol->setSweep(startFreq,stopFreq,amplitude,sweepTime,stepCount);

    appendLog("扫频参数配置完成",1);
}

bool MainWindow::validateSweepConfig(double &startFreq,
                                     double &stopFreq,
                                     double &amplitude,
                                     double &sweepTime,
                                     int &stepCount,
                                     QString &errorMsg)
{
    QString startStr = ui->editSweepFreqStart->text().trimmed();
    QString stopStr  = ui->editSweepFreqEnd->text().trimmed();
    QString ampStr   = ui->spinSweepAmp->text().trimmed();
    QString timeStr  = ui->spinSweepTime->text().trimmed();
    QString stepStr  = ui->spinSweepCount->text().trimmed();

    if(startStr.isEmpty() || stopStr.isEmpty()
        || ampStr.isEmpty() || timeStr.isEmpty() || stepStr.isEmpty())
    {
        errorMsg = "所有参数必须填写";
        return false;
    }

    bool ok1,ok2,ok3,ok4,ok5;

    startFreq = startStr.toDouble(&ok1);
    stopFreq  = stopStr.toDouble(&ok2);
    amplitude = ampStr.toDouble(&ok3);
    sweepTime = timeStr.toDouble(&ok4);
    stepCount = stepStr.toInt(&ok5);

    if(!ok1||!ok2||!ok3||!ok4||!ok5)
    {
        errorMsg="请输入合法数字";
        return false;
    }

    if(startFreq < DG1032Spec::MIN_FREQ || stopFreq > DG1032Spec::MAX_FREQ)
    {
        errorMsg="频率范围错误:0.001kHz - 30000kHz";
        return false;
    }

    if(startFreq > stopFreq)
    {
        errorMsg="起始频率不能大于截止频率";
        return false;
    }

    if(amplitude < DG1032Spec::MIN_AMP || amplitude > DG1032Spec::MAX_AMP)
    {
        errorMsg="幅度范围:0.001-20Vpp";
        return false;
    }

    if(sweepTime < DG1032Spec::MIN_TIME || sweepTime > DG1032Spec::MAX_TIME)
    {
        errorMsg="扫频时间范围:0.001-500s";
        return false;
    }

    if(stepCount < DG1032Spec::MIN_STEP || stepCount > DG1032Spec::MAX_STEP)
    {
        errorMsg="步进数范围:2-65535";
        return false;
    }

    return true;
}
// ///////////////////////////////////////扫频信号配置页面逻辑实现/////////////////////////
// ------------------------------------------------------------------------------------

// ///////////////////////////////////////自定义信号配置页面逻辑实现/////////////////////////
bool MainWindow::validateArbConfig(QString &filePath,
                                   double &sampleRate,
                                   double &amplitude,
                                   QString &errorMsg)
{
    filePath = ui->lineFileName->text().trimmed();
    QString rateStr = ui->spinArbSampleRate->text().trimmed();
    QString ampStr  = ui->spinArbAmp->text().trimmed();

    if(filePath.isEmpty())
    {
        errorMsg = "请选择波形文件";
        return false;
    }

    if(!filePath.endsWith(".raf", Qt::CaseInsensitive))
    {
        errorMsg = "波形文件必须为 .raf 格式";
        return false;
    }

    bool ok1, ok2;

    sampleRate = rateStr.toDouble(&ok1);
    amplitude  = ampStr.toDouble(&ok2);

    if(!ok1 || !ok2)
    {
        errorMsg = "采样率或幅度输入错误";
        return false;
    }

    if(sampleRate < DG1032Spec::MIN_ARB_SAMPLE ||
        sampleRate > DG1032Spec::MAX_ARB_SAMPLE)
    {
        errorMsg = "采样率范围: 0.001kSa/s - 200000kSa/s";
        return false;
    }

    if(amplitude < DG1032Spec::MIN_ARB_AMP ||
        amplitude > DG1032Spec::MAX_ARB_AMP)
    {
        errorMsg = "幅度范围: 0.001V - 10V";
        return false;
    }

    return true;
}

void MainWindow::on_btnSelectArb_clicked()
{
    // 1 打开文件选择框
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "选择ARB波形文件",
        "",
        "ARB File (*.raf);;All Files (*)");

    // 2 用户取消
    if(filePath.isEmpty())
    {
        appendLog("用户取消选择ARB文件",0);
        return;
    }

    // 3 检查文件是否存在
    QFileInfo fileInfo(filePath);

    if(!fileInfo.exists())
    {
        QMessageBox::warning(this,"文件错误","文件不存在");
        return;
    }

    // 4 检查文件扩展名
    if(fileInfo.suffix().toLower() != "raf")
    {
        QMessageBox::warning(this,"文件类型错误","请选择 .raf 波形文件");
        return;
    }

    // 5 保存路径（成员变量）
    arbFilePath = filePath;

    // 6 UI显示文件名
    ui->lineFileName->setText(fileInfo.fileName());

    // 7 日志
    appendLog("ARB文件加载: " + fileInfo.fileName(),1);
}


void MainWindow::on_btnArbConfig_clicked()
{
    QString filePath;
    double sampleRate;
    double amplitude;
    QString errorMsg;

    if(!validateArbConfig(filePath,sampleRate,amplitude,errorMsg))
    {
        QMessageBox::warning(this,"输入错误",errorMsg);
        return;
    }

    rigol->setArbWave(filePath,sampleRate,amplitude);

    appendLog("ARB波形配置完成",LOG_INFO);
}

// ///////////////////////////////////////自定义信号配置页面逻辑实现/////////////////////////
// ------------------------------------------------------------------------------------



// ///////////////////////////////////////菜单界面切换按钮////////////////////////////////

//将菜单与界面关联
void MainWindow::initMenuConnections()
{
    connect(ui->menuTxTest, &QMenu::triggered, this, [=](){
        switchPage(ui->pageTxTest);
    });

    connect(ui->menuRxTest, &QMenu::triggered, this, [=](){
        switchPage(ui->pageRxTest);
    });

    connect(ui->menuDITest, &QMenu::triggered, this, [=](){
        switchPage(ui->pageDITest);
    });

    connect(ui->menuImpendanceTest, &QMenu::triggered, this, [=](){
        switchPage(ui->pageImpendanceTest);
    });

    connect(ui->menuPCBTest, &QMenu::triggered, this, [=](){
        switchPage(ui->pagePCBTest);
    });
}


void MainWindow::switchPage(QWidget *page)
{
    if (!page)
        return;

    ui->stackedMenu->setCurrentWidget(page);
}

// ///////////////////////////////////////阻抗分析测试配置页面实现////////////////////////

// ///////////////////连接服务器实现/////////////////////
void MainWindow::on_btnBodeVisaConnect_clicked() 
{
    QString ip = ui->editBodeVisa->text().trimmed();

    if (ip.isEmpty())
    {
        appendLog("ERROR: IP address is empty.", LOG_ERROR);
        return;
    }

    appendLog("Starting SCPI Runner...",LOG_INFO);

    PROCESS_INFORMATION pi{};

    bool runnerOK = bode->startScpiRunner(Bode100Spec::command, pi);
    QThread::msleep(1500);
    if (!runnerOK)
    {
        appendLog("ERROR: Failed to start SCPI Runner.", LOG_ERROR);
        return;
    }
    
    appendLog("SCPI Runner started.", LOG_INFO);
    appendLog("Connecting VISA...", LOG_INFO);
    

    bool ok = bode->connectVisa(ip);

    if (!ok)
    {
        appendLog("ERROR: VISA connection failed.", LOG_ERROR);

        return;
    }
    appendLog("VISA connected.", LOG_INFO);

    QString idn = bode->queryCommandv3("*IDN?\n");
    //QString idn = bode->queryIDN();
    appendLog("Device ID: " + idn, LOG_INFO);
}
// ///////////////////连接服务器实现/////////////////////
// ------------------------------------------------------

// ///////////////////校准实现/////////////////////
void MainWindow::on_btnOpenCali_clicked()
{

    if (vi != 0) {
        // ==========================================
        // 1. 申请仪器控制权 (加锁)
        // ==========================================
        QString lockStatus = bode->queryCommand( vi,":SYST:LOCK:REQ?\n");

        // 可选：检查是否成功拿到锁（如果返回不是 1 或 OK，说明被别的软件占用了）
        if (!lockStatus.contains("1") && !lockStatus.toUpper().contains("OK")) {
            appendLog("获取仪器控制权失败，仪器可能正被官方软件占用！", LOG_ERROR);
            return; // 拿不到锁就直接退出，不要往下执行了
        }

        appendLog("成功获取仪器控制权，开始校准...", LOG_INFO);

        // ==========================================
        // 2. 执行你的正常校准流程 (你原来的代码)
        // ==========================================
        QString ope = bode->bodeCalibration(vi, BodeDrive::CalMode::Open);
        QString ope2 = bode->bodeCalibration(vi, BodeDrive::CalMode::Short);
        QString ope3 = bode->bodeCalibration(vi, BodeDrive::CalMode::Load);

        appendLog("校准指令发送完毕", LOG_INFO);
        appendLog(ope + ope2 + ope3, LOG_INFO);

        // 假设 bodeCalibrationCom 是你的应用校准/综合处理函数
        // QString com = bode->bodeCalibrationCom(vi);
        // appendLog(com, LOG_INFO);

        // ==========================================
        // 3. 释放仪器控制权 (解锁) - 【非常重要】
        // ==========================================
        QString relok = bode->queryCommand(vi, ":SYST:LOCK:REL?\n");
        appendLog("仪器控制权已释放", LOG_INFO);
        QString com=bode->bodeCalibrationCom(vi);
        appendLog(com, LOG_INFO);

    }
    else {
        appendLog("句柄无效，开路校准失败", LOG_ERROR);
    }
    //if (vi != 0) { // 简单检查句柄是否有效

    //    QString ope=bode->bodeCalibration(vi, BodeDrive::CalMode::Open);
    //    QString ope2 = bode->bodeCalibration(vi, BodeDrive::CalMode::Short);
    //    QString ope3 = bode->bodeCalibration(vi, BodeDrive::CalMode::Load);
    //    appendLog("校准成功", LOG_INFO);
    //    appendLog(ope+ope2+ope3, LOG_INFO);
    //    QString com=bode->bodeCalibrationCom(vi);
    //    appendLog(com, LOG_INFO);
    //}
    //else {
    //    appendLog("开路校准失败", LOG_ERROR);
    //}
}


void MainWindow::on_btnShortCali_clicked()
{

    if (vi != 0) { // 简单检查句柄是否有效

        QString shor = bode->bodeCalibration(vi, BodeDrive::CalMode::Short);
        appendLog("短路校准成功", LOG_INFO);
        appendLog(shor, LOG_INFO);
    }
    else {
        appendLog("短路校准失败", LOG_ERROR);
    }
}

void MainWindow::on_btnLoadCali_clicked()
{
    if (vi != 0) { // 简单检查句柄是否有效

        QString ss=bode->bodeCalibration(vi, BodeDrive::CalMode::Load);
        if (ss.trimmed().isEmpty()) {
            appendLog("ss 是空或全是空格", LOG_INFO);
        }
        appendLog("负载校准成功",LOG_INFO);
        appendLog(ss, LOG_INFO);
    }
    else {
        appendLog("负载校准失败", LOG_ERROR);
    }
    QString sss = bode->bodeCalibrationCom(vi);
    appendLog(sss, LOG_INFO);
}

// ///////////////////校准实现/////////////////////
// // ------------------------------------------------------
// ///////////////////////////////////////阻抗分析测试配置页面实现////////////////////////
void MainWindow::on_btnStartMeasurement_clicked()
{
    if (vi == 0) {
        appendLog("仪器未连接，请先连接仪器！", LOG_ERROR);
        return;
    }

    // ==========================================
    // 1. 收集 UI 上的用户参数
    // ==========================================
    SweepParams params;

    // 因为你是 SpinBox，通过 value() 获取数字，并转换为字符串发给仪器
    // 假设你的 SpinBox 单位默认是 Hz
    params.startFreq = std::to_string(ui->spinStartFreq->value());
    params.stopFreq = std::to_string(ui->spinStopFreq->value());
    params.points = ui->spinSweepPoint->value();

    // 判断扫频模式 (假设 ComboBox 第1项是线性，第2项是对数)
    if (ui->boxSweepMode->currentIndex() == 0) {
        params.sweepType = "LIN";
    }
    else {
        params.sweepType = "LOG";
    }

    params.bandwidth = "300Hz"; // 暂时写死，或者你后续也可以加一个控件

    // ==========================================
    // 2. 锁定界面按钮，防止重复点击
    // ==========================================
    ui->btnStartMeasurement->setEnabled(false);
    appendLog(QString(">>> 开始自动测量 | 范围: %1Hz - %2Hz | 点数: %3")
        .arg(QString::fromStdString(params.startFreq)).arg(QString::fromStdString(params.stopFreq)).arg(QString::number(params.points)), LOG_INFO);

    // ==========================================
    // 3. 开启子线程执行测量 (防卡死)
    // ==========================================
    QFuture<void> future = QtConcurrent::run([=]() {

        // 调用底层的测量函数
        MeasureResult result = bode->performMeasurement(vi, params);

        // ==========================================
        // 4. 切回主线程更新 UI
        // ==========================================
        QMetaObject::invokeMethod(this, [=]() {
            if (result.success) {
                appendLog("✅ " + result.message, LOG_INFO);

                // 仅作演示：打印拿到的第一个点的数据，证明数据真的抓回来了
                if (!result.frequencies.empty()) {
                    QString pointInfo = QString("样本数据 [1] -> 频率: %1 Hz, 阻抗: %2 欧姆, 相位: %3 度")
                        .arg(result.frequencies[0])
                        .arg(result.magnitudes[0])
                        .arg(result.phases[0]);
                    appendLog(pointInfo, LOG_INFO);
                }

                // 【下一步预留位置】
                // 这里拿到了完整的 result.frequencies, result.magnitudes
                // 之后你可以把这些数组丢给 QCustomPlot 画出曲线！

            }
            else {
                appendLog("❌ " + result.message, LOG_ERROR);
            }

            // 测量结束，恢复按钮点击功能
            ui->btnStartMeasurement->setEnabled(true);
            });
        });
}

// -------------------------------------------------------------------------------------------


