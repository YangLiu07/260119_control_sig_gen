#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime> 
#include <QFile>
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
#include "qcustomplot.h"
#include <QHeaderView> // 🌟 必须加上这个头文件来控制列宽
//#include "chartmanager.h" // 顶部引入


#include <cmath> // 用于 std::cos, std::sin 和 M_PI
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif





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
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // 初始化ui界面，实例化
    ui->setupUi(this);
    setConnectionLed(false);

    // ========================================================
    // ✨ 核心修改：调用封装好的图表初始化与游标函数
    // ========================================================
    initChart();

    rigol = new RigolDriver(this);
    bode = new BodeDrive();
    bode->setLogHandler([this](const QString& msg) {
        this->appendLog(msg, LOG_INFO);
        });
    //connect(bode, &BodeDrive::logAvailable, this, &MainWindow::appendLog);

    //初始化菜单连接
    initMenuConnections();

    //Qt 信号槽机制 + Lambda 表达式 将sigLog的信息传递到ui界面的日志中
    connect(rigol, &RigolDriver::sigLog, this, [=](QString msg) {
        this->appendLog(msg, LOG_INFO);
        });

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
    QDoubleValidator* freqValidator = new QDoubleValidator(0.001, 30000, 6, this);
    freqValidator->setNotation(QDoubleValidator::ScientificNotation);

    ui->editSweepFreqStart->setValidator(freqValidator);
    ui->editSweepFreqEnd->setValidator(freqValidator);

    // 软件启动时，默认禁用所有仪器的控制按钮，必须等连接成功才解锁
    setConnectionLed(false);
    setTestControlsEnabled(false);
} // 构造函数结束


// ✨ 新增：独立的图表与游标初始化函数
void MainWindow::initChart()
{
    // ==========================================
    // 1. 隐藏图例 (Legend)
    // ==========================================
    ui->plotAdmittance->legend->setVisible(false);

    // ========================================================
    // 2. 核心表格初始化 (保持你现有的完美外观)
    // ========================================================
    if (ui->table_Cursors) {
        ui->table_Cursors->setColumnCount(4);
        ui->table_Cursors->setRowCount(3);

        QFont tableFont = ui->table_Cursors->font();
        tableFont.setPointSize(7);
        ui->table_Cursors->setFont(tableFont);

        QStringList headers;
        headers << "游标" << "频率 (kHz)" << "电导 G (S)" << "电纳 B (S)";
        ui->table_Cursors->setHorizontalHeaderLabels(headers);

        ui->table_Cursors->verticalHeader()->setVisible(false);
        ui->table_Cursors->verticalHeader()->setDefaultSectionSize(18);
        ui->table_Cursors->horizontalHeader()->setFixedHeight(20);
        ui->table_Cursors->setFixedHeight(76);

        ui->table_Cursors->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
        ui->table_Cursors->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        ui->table_Cursors->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
        ui->table_Cursors->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

        ui->table_Cursors->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->table_Cursors->setSelectionMode(QAbstractItemView::NoSelection);

        // 填充初始空数据
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 4; ++col) {
                QTableWidgetItem* item = new QTableWidgetItem("-");
                item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
                ui->table_Cursors->setItem(row, col, item);
            }
        }

        ui->table_Cursors->item(0, 0)->setText("☑ Cursor 1");
        ui->table_Cursors->item(0, 0)->setBackground(QColor(0, 150, 0));
        ui->table_Cursors->item(0, 0)->setForeground(Qt::white);

        ui->table_Cursors->item(1, 0)->setText("☐ Cursor 2");
        ui->table_Cursors->item(1, 0)->setBackground(QColor(255, 140, 0));
        ui->table_Cursors->item(1, 0)->setForeground(Qt::white);

        ui->table_Cursors->item(2, 0)->setText("Δ (C2 - C1)");
        ui->table_Cursors->item(2, 0)->setBackground(QColor(240, 240, 240));
        ui->table_Cursors->item(2, 0)->setForeground(Qt::black);
    }

    // ==========================================
    // 3. 左右 Y 轴 与 底部 X 轴 初始化
    // ==========================================
    ui->plotAdmittance->yAxis->setLabel("电导 G (S)");
    ui->plotAdmittance->yAxis->setLabelColor(QColor(40, 110, 255));
    ui->plotAdmittance->yAxis->setTickLabelColor(QColor(40, 110, 255));
    ui->plotAdmittance->yAxis->setNumberFormat("g");
    ui->plotAdmittance->yAxis->setNumberPrecision(5);
    ui->plotAdmittance->addGraph(ui->plotAdmittance->xAxis, ui->plotAdmittance->yAxis);
    ui->plotAdmittance->graph(0)->setPen(QPen(QColor(40, 110, 255), 2));

    ui->plotAdmittance->yAxis2->setVisible(true);
    ui->plotAdmittance->yAxis2->setLabel("电纳 B (S)");
    ui->plotAdmittance->yAxis2->setLabelColor(QColor(255, 60, 60));
    ui->plotAdmittance->yAxis2->setTickLabelColor(QColor(255, 60, 60));
    ui->plotAdmittance->yAxis2->setNumberFormat("g");
    ui->plotAdmittance->yAxis2->setNumberPrecision(5);
    ui->plotAdmittance->addGraph(ui->plotAdmittance->xAxis, ui->plotAdmittance->yAxis2);
    ui->plotAdmittance->graph(1)->setPen(QPen(QColor(255, 60, 60), 2));

    ui->plotAdmittance->xAxis->setLabel("频率 (kHz)");
    ui->plotAdmittance->xAxis->setScaleType(QCPAxis::stLogarithmic);
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    ui->plotAdmittance->xAxis->setTicker(logTicker);
    ui->plotAdmittance->xAxis->setNumberFormat("eb");
    ui->plotAdmittance->xAxis->setNumberPrecision(1);
    ui->plotAdmittance->xAxis->setTickLabelRotation(30);

    // 网格与交互
    QPen gridPen(QColor(220, 220, 220), 1, Qt::SolidLine);
    QPen subGridPen(QColor(240, 240, 240), 1, Qt::DotLine);
    ui->plotAdmittance->xAxis->grid()->setPen(gridPen);
    ui->plotAdmittance->xAxis->grid()->setSubGridVisible(true);
    ui->plotAdmittance->xAxis->grid()->setSubGridPen(subGridPen);
    ui->plotAdmittance->yAxis->grid()->setPen(gridPen);
    ui->plotAdmittance->yAxis->grid()->setSubGridVisible(true);
    ui->plotAdmittance->yAxis->grid()->setSubGridPen(subGridPen);
    ui->plotAdmittance->yAxis2->grid()->setVisible(false);

    ui->plotAdmittance->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    QList<QCPAxis*> axesList;
    axesList << ui->plotAdmittance->xAxis << ui->plotAdmittance->yAxis << ui->plotAdmittance->yAxis2;
    ui->plotAdmittance->axisRect()->setRangeZoomAxes(axesList);
    ui->plotAdmittance->axisRect()->setRangeDragAxes(axesList);

    // ==========================================================
    // 4. 🌟 Cursor 1 & 2 游标对象初始化 (圆点吸附风格，彻底去杂乱)
    // ==========================================================
    // Cursor 1 (实时 - 蓝/红实心点 + 绿色虚线)
    tracerCond = new QCPItemTracer(ui->plotAdmittance);
    tracerCond->setGraph(ui->plotAdmittance->graph(0));
    tracerCond->setStyle(QCPItemTracer::tsCircle); // 改为圆点
    tracerCond->setPen(QPen(QColor(40, 110, 255)));
    tracerCond->setBrush(QBrush(QColor(40, 110, 255))); // 实心蓝
    tracerCond->setSize(7);
    tracerCond->setVisible(false);
    tracerCond->setLayer("overlay");

    tracerSusp = new QCPItemTracer(ui->plotAdmittance);
    tracerSusp->setGraph(ui->plotAdmittance->graph(1));
    tracerSusp->setStyle(QCPItemTracer::tsCircle); // 改为圆点
    tracerSusp->setPen(QPen(QColor(255, 60, 60)));
    tracerSusp->setBrush(QBrush(QColor(255, 60, 60))); // 实心红
    tracerSusp->setSize(7);
    tracerSusp->setVisible(false);
    tracerSusp->setLayer("overlay");

    vLine = new QCPItemLine(ui->plotAdmittance);
    vLine->setPen(QPen(Qt::darkGreen, 1, Qt::DashLine));
    vLine->setVisible(false);
    vLine->setLayer("overlay");

    // Cursor 2 (锁定 - 橙色实心点 + 橙色虚线)
    tracerCond2 = new QCPItemTracer(ui->plotAdmittance);
    tracerCond2->setGraph(ui->plotAdmittance->graph(0));
    tracerCond2->setStyle(QCPItemTracer::tsCircle);
    tracerCond2->setPen(QPen(QColor(255, 140, 0)));
    tracerCond2->setBrush(QBrush(QColor(255, 140, 0))); // 实心橙
    tracerCond2->setSize(7);
    tracerCond2->setVisible(false);
    tracerCond2->setLayer("overlay");

    tracerSusp2 = new QCPItemTracer(ui->plotAdmittance);
    tracerSusp2->setGraph(ui->plotAdmittance->graph(1));
    tracerSusp2->setStyle(QCPItemTracer::tsCircle);
    tracerSusp2->setPen(QPen(QColor(255, 140, 0)));
    tracerSusp2->setBrush(QBrush(QColor(255, 140, 0))); // 实心橙
    tracerSusp2->setSize(7);
    tracerSusp2->setVisible(false);
    tracerSusp2->setLayer("overlay");

    vLine2 = new QCPItemLine(ui->plotAdmittance);
    vLine2->setPen(QPen(QColor(255, 140, 0), 1, Qt::DashLine));
    vLine2->setVisible(false);
    vLine2->setLayer("overlay");

    // ==========================================
    // 5. 事件 1：鼠标移动 (🌟 修复滞后)
    // ==========================================
    connect(ui->plotAdmittance, &QCustomPlot::mouseMove, this, [=](QMouseEvent* event) {
        if (!ui->plotAdmittance || ui->plotAdmittance->graphCount() < 2) return;
        if (!ui->plotAdmittance->graph(0)->data() || ui->plotAdmittance->graph(0)->data()->isEmpty()) return;
        if (!tracerCond || !tracerSusp || !vLine) return;

        if (!ui->plotAdmittance->axisRect()->rect().contains(event->pos())) {
            tracerCond->setVisible(false);
            tracerSusp->setVisible(false);
            vLine->setVisible(false);
            ui->plotAdmittance->layer("overlay")->replot();
            return;
        }

        double x = ui->plotAdmittance->xAxis->pixelToCoord(event->pos().x());
        if (x <= 0) return;

        tracerCond->setVisible(true);
        tracerSusp->setVisible(true);
        vLine->setVisible(true);

        tracerCond->setGraphKey(x);
        tracerSusp->setGraphKey(x);

        // 🌟 核心修复1：放弃读取复杂的 position，直接用鼠标 x 坐标定位竖线！
        // 用极值 -1e10 到 1e10，保证线条不管怎么缩放都是无限长的！
        vLine->start->setCoords(x, -1e10);
        vLine->end->setCoords(x, 1e10);

        // 🌟 核心修复2：必须先重绘，让内部引擎解算出圆点的实际附着位置，再去取值！
        ui->plotAdmittance->layer("overlay")->replot();

        if (!tracerCond->position) return;

        // 写入 Cursor 1 数据
        double f1 = tracerCond->position->key();
        double c1 = tracerCond->position->value();
        double s1 = tracerSusp->position->value();

        if (ui->table_Cursors) {
            ui->table_Cursors->item(0, 1)->setText(QString::number(f1, 'f', 3));
            ui->table_Cursors->item(0, 2)->setText(QString::number(c1, 'g', 5));
            ui->table_Cursors->item(0, 3)->setText(QString::number(s1, 'g', 5));

            // 如果 C2 存在，实时跳动计算 Delta (C2 - C1)
            if (cursor2Active && tracerCond2->position) {
                double f2 = tracerCond2->position->key();
                double c2 = tracerCond2->position->value();
                double s2 = tracerSusp2->position->value();

                ui->table_Cursors->item(2, 1)->setText(QString::number(f2 - f1, 'f', 3));
                ui->table_Cursors->item(2, 2)->setText(QString::number(c2 - c1, 'g', 5));
                ui->table_Cursors->item(2, 3)->setText(QString::number(s2 - s1, 'g', 5));
            }
        }
        });

    // ==========================================
    // 6. 事件 2：左键双击 (锁定 Cursor 2)
    // ==========================================
    connect(ui->plotAdmittance, &QCustomPlot::mouseDoubleClick, this, [=](QMouseEvent* event) {
        if (event->button() == Qt::LeftButton && ui->plotAdmittance->axisRect()->rect().contains(event->pos())) {
            if (ui->plotAdmittance->graphCount() < 2 || ui->plotAdmittance->graph(0)->data()->isEmpty()) return;

            double x = ui->plotAdmittance->xAxis->pixelToCoord(event->pos().x());
            if (x <= 0) return;

            cursor2Active = true;
            tracerCond2->setVisible(true);
            tracerSusp2->setVisible(true);
            vLine2->setVisible(true);

            tracerCond2->setGraphKey(x);
            tracerSusp2->setGraphKey(x);

            // 🌟 核心修复3：直接锁定 x 坐标，消灭残留虚线！
            vLine2->start->setCoords(x, -1e10);
            vLine2->end->setCoords(x, 1e10);

            ui->plotAdmittance->layer("overlay")->replot();

            if (!tracerCond2->position) return;

            // 写入 Cursor 2 数据
            double f2 = tracerCond2->position->key();
            double c2 = tracerCond2->position->value();
            double s2 = tracerSusp2->position->value();

            if (ui->table_Cursors) {
                ui->table_Cursors->item(1, 0)->setText("☑ Cursor 2");
                ui->table_Cursors->item(1, 1)->setText(QString::number(f2, 'f', 3));
                ui->table_Cursors->item(1, 2)->setText(QString::number(c2, 'g', 5));
                ui->table_Cursors->item(1, 3)->setText(QString::number(s2, 'g', 5));

                if (tracerCond->position) {
                    double f1 = tracerCond->position->key();
                    double c1 = tracerCond->position->value();
                    double s1 = tracerSusp->position->value();
                    ui->table_Cursors->item(2, 1)->setText(QString::number(f2 - f1, 'f', 3));
                    ui->table_Cursors->item(2, 2)->setText(QString::number(c2 - c1, 'g', 5));
                    ui->table_Cursors->item(2, 3)->setText(QString::number(s2 - s1, 'g', 5));
                }
            }
        }
        });

    // ==========================================
    // 7. 事件 3：右键单击 (清除 Cursor 2)
    // ==========================================
    connect(ui->plotAdmittance, &QCustomPlot::mousePress, this, [=](QMouseEvent* event) {
        if (event->button() == Qt::RightButton && cursor2Active) {
            cursor2Active = false;
            tracerCond2->setVisible(false);
            tracerSusp2->setVisible(false);
            vLine2->setVisible(false);
            ui->plotAdmittance->layer("overlay")->replot();

            if (ui->table_Cursors) {
                ui->table_Cursors->item(1, 0)->setText("☐ Cursor 2");
                for (int i = 1; i <= 3; i++) ui->table_Cursors->item(1, i)->setText("-");
                for (int i = 1; i <= 3; i++) ui->table_Cursors->item(2, i)->setText("-");
            }
        }
        });
}

    // ... 下方保留你之前写好的 Y轴、X轴、网格线初始化的代码 ...
// 析构函数
MainWindow::~MainWindow()
{
    if (bode) {
        // 🌟 必须加上这个判断！只有在真正连接的情况下，才能发指令！
        if (bode->isConnected()) {
            bode->sendCommand("*CLS\n");
            bode->sendCommand("*RST\n");
            bode->disconnect();
        }

        bode->stopScpiRunner();

        delete bode;
        bode = nullptr;
    }
    delete ui;
}

// /////////////////////////////////////////日志管理////////////////////////////

//日志生成方法
void MainWindow::appendLog(const QString& msg, int LogLevel)
{
    // 【核心防崩溃安全锁】：如果当前不在主线程，强制排队到主线程执行
    if (QThread::currentThread() != this->thread()) {
        QMetaObject::invokeMethod(this, "appendLog", Qt::QueuedConnection,
            Q_ARG(QString, msg), Q_ARG(int, LogLevel));
        return;
    }
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

    const QString dgAddress = ui->lineEditDGAddress->text();

    // ------------数采的自检代码尚未实现，缺少驱动代码-----------------
    // bool ok2 = checkInstrument(daq,
    //                            ui->lineEditMRAddress->text(),
    //                            "数据采集仪");
    ui->btnSelfTest->setEnabled(false);

    executeAsync(
        [=]() -> bool {
            bool ok1 = checkInstrument(rigol, dgAddress, "信号源");
            bool ok2 = true;
            return ok1 && ok2;
        },
        [=](bool allOk) {
            if(allOk)
                appendLog("===== 全部设备正常 =====",LOG_INFO);
            else
                appendLog("===== 存在异常设备 =====",LOG_WARNING);

            ui->btnSelfTest->setEnabled(true);
        }
    );
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

    if(!validateSweepConfig(startFreq,stopFreq,amplitude,sweepTime,stepCount,errorMsg))
    {
        QMessageBox::warning(this,"输入错误",errorMsg);
        return;
    }

    ui->btnSweepConfig->setEnabled(false);
    appendLog("正在下发扫频参数...", LOG_INFO);

    executeAsync(
        [=]() -> QString {
            if (!rigol || !rigol->isConnected()) {
                return "ERROR:信号源未连接";
            }

            rigol->sendCmd(":SOUR1:SWE:STAT ON");
            rigol->setSweep(startFreq, stopFreq, amplitude, sweepTime, stepCount);
            return "OK";
        },
        [=](QString result) {
            if (result.startsWith("ERROR:")) {
                appendLog(result.mid(6), LOG_ERROR);
            }
            else {
                appendLog("扫频参数配置完成", LOG_SUCCESS);
            }

            ui->btnSweepConfig->setEnabled(true);
        }
    );
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

// 统一管理所有依赖仪器连接状态的按钮
void MainWindow::setTestControlsEnabled(bool enabled)
{
    ui->btnStartMeasurement->setEnabled(enabled);
    ui->btnOpenCali->setEnabled(enabled);
    ui->btnShortCali->setEnabled(enabled);
    ui->btnLoadCali->setEnabled(enabled);
    ui->btnDisconnect->setEnabled(enabled); // 断开按钮同理
    // 如果你还有其他依赖仪器连接的按钮，都可以加在这里
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

    ui->btnArbConfig->setEnabled(false);
    appendLog("正在下发 ARB 波形参数...", LOG_INFO);

    executeAsync(
        [=]() -> QString {
            if (!rigol || !rigol->isConnected()) {
                return "ERROR:信号源未连接";
            }

            rigol->setArbWave(filePath, sampleRate, amplitude);
            return "OK";
        },
        [=](QString result) {
            if (result.startsWith("ERROR:")) {
                appendLog(result.mid(6), LOG_ERROR);
            }
            else {
                appendLog("ARB波形配置完成", LOG_SUCCESS);
            }

            ui->btnArbConfig->setEnabled(true);
        }
    );
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

void MainWindow::on_btnBodeVisaConnect_clicked()
{
    QString ip = ui->editBodeVisa->text().trimmed();

    // 1. 简单的 VISA 地址格式验证 (防呆设计)
    if (ip.isEmpty()) {
        appendLog("连接失败：VISA 地址不能为空！", LOG_ERROR);
        return;
    }

    // 智能修复 VISA 地址格式
    if (!ip.toUpper().startsWith("TCPIP")) {
        if (!ip.contains("::")) {
            ip = "TCPIP0::" + ip + "::5025::SOCKET";
        }
        else {
            ip = "TCPIP0::" + ip;
        }
        ui->editBodeVisa->setText(ip); // 将修正后的标准格式写回 UI
    }

    // 2. 锁定 UI，进入挂起状态
    ui->btnBodeVisaConnect->setEnabled(false);
    setTestControlsEnabled(false);
    setConnectionLed(false);

    // 3. 启动异步框架
    executeAsync(
        // ----------------------------------------
        // 任务 A：后台耗时连接操作
        // ----------------------------------------
        [=]() -> QString {
            PROCESS_INFORMATION pi{};
            bool runnerOK = bode->startScpiRunner(Bode100Spec::command, pi);

            // 如果底层服务直接启动失败，提前拦截，不用等倒计时
            if (!runnerOK) {
                return "ERROR:启动 SCPI Runner 服务失败！请检查路径或权限。";
            }

            // ==========================================
            // 🌟 核心新增：5 秒精准倒计时日志
            // ==========================================
            for (int i = 5; i >= 0; --i) {
                QString msg = QString("正在启动 SCPI 服务并连接 VISA，请稍候...（%1s）").arg(i);

                // ⚠️ 必须安全地切回主线程更新 UI 日志，否则会导致跨线程崩溃
                QMetaObject::invokeMethod(this, [=]() {
                    appendLog(msg, LOG_INFO);
                    });

                // 留出最后一秒(0s)立刻执行后续代码，前面每次休眠 1 秒
                if (i > 0) {
                    QThread::msleep(1000);
                }
            }

            // 尝试建立 VISA 通讯
            if (!bode->connectVisa(ip)) {
                bode->stopScpiRunner();
                return "ERROR:VISA 通信建立失败！请检查网络、IP地址或仪器电源。";
            }

            // 核心防线：立刻申请硬件排他锁
            QString lockStatus = bode->queryCommand(":SYST:LOCK:REQ?\n");
            if (!lockStatus.contains("1") && !lockStatus.toUpper().contains("OK")) {
                bode->disconnect();
                bode->stopScpiRunner();
                return "ERROR:仪器被其他软件占用（锁定失败）！请先关闭官方软件。";
            }

            // 此时已经独占仪器，进行初始化复位
            QString idn = bode->queryCommand("*IDN?\n");
            bode->sendCommand("*CLS\n");
            bode->sendCommand(":CALC:PAR:DEF Z\n");
            bode->sendCommand(":SENS:Z:METH TSER\n");
            bode->queryCommand("*OPC?\n");
            QString errStatus = bode->queryCommand(":SYST:ERR?\n");

            // 初始化完释放锁
            bode->queryCommand(":SYST:LOCK:REL?\n");

            if (!errStatus.contains("0") && !errStatus.toLower().contains("no error")) {
                return "ERROR:仪器底层自检报错: " + errStatus;
            }

            return "SUCCESS:" + idn;
        },

        // ----------------------------------------
        // 任务 B：主线程 UI 更新操作
        // ----------------------------------------
        [=](QString workerResult) {

            if (workerResult.startsWith("ERROR:")) {
                QString errorMsg = workerResult.mid(6);
                appendLog("❌ " + errorMsg, LOG_ERROR);

                setConnectionLed(false);
                setTestControlsEnabled(false);

            }
            else if (workerResult.startsWith("SUCCESS:")) {
                QString idn = workerResult.mid(8);
                appendLog("✅ VISA 连接成功！硬件独占锁定测试通过。", LOG_SUCCESS);
                appendLog("设备信息: " + idn, LOG_INFO);

                setConnectionLed(true);
                setTestControlsEnabled(true); // 解锁测量的按键

            }
            else {
                appendLog("连接发生未知异常: " + workerResult, LOG_ERROR);
            }

            ui->btnBodeVisaConnect->setEnabled(true);
        }
    );
}

//#########################状态指示灯########################
void MainWindow::setConnectionLed(bool isConnected) {
    if (isConnected) {
        // 亮绿灯，带有发光阴影效果
        ui->label_LED->setStyleSheet(
            "QLabel {"
            "  background-color: #00E676;"
            "  border-radius: 8px;" // 半径是宽高的一半，变成圆形
            "  border: 1px solid #00C853;"
            "}"
        );
    }
    else {
        // 灭灯（暗红色）
        ui->label_LED->setStyleSheet(
            "QLabel {"
            "  background-color: #551A1A;"
            "  border-radius: 8px;"
            "  border: 1px solid #330000;"
            "}"
        );
    }
}


void MainWindow::on_btnDisconnect_clicked()
{
    // 1. 防呆：如果没有连接，直接返回
    if (!bode || !bode->isConnected()) {
        appendLog("当前未连接任何设备，无需断开。", LOG_WARNING);
        return;
    }

    // 2. 锁定UI，给用户视觉反馈
    ui->btnDisconnect->setEnabled(false);
    ui->btnBodeVisaConnect->setEnabled(false);
    appendLog("正在执行安全断开流程，请稍候...", LOG_INFO);

    // 3. 使用异步框架执行断开操作 (绝不卡死界面)
    executeAsync(
        [=]() -> QString {
            // 在后台线程调用我们刚写好的硬核断开函数
            bode->disconnect();
            return "OK";
        },
        [=](QString result) {
            // 4. 断开完成，切回主线程重置所有 UI 状态
            appendLog("✅ 连接已安全断开，资源已释放。", LOG_SUCCESS);

            setConnectionLed(false);       // 熄灭绿灯，亮起红灯
            setTestControlsEnabled(false); // 封印所有测量和校准按钮！

            // 恢复“连接”按钮的使能，让用户可以重新连接
            ui->btnBodeVisaConnect->setEnabled(true);
            ui->btnDisconnect->setEnabled(true);

            // (可选) 清理图表上的游标和曲线
            /*
            if (ui->plotAdmittance) {
                ui->plotAdmittance->graph(0)->data()->clear();
                ui->plotAdmittance->graph(1)->data()->clear();
                ui->plotAdmittance->layer("overlay")->replot();
                ui->plotAdmittance->replot();
            }
            if (ui->table_Cursors) {
                for(int i = 1; i <= 3; i++) ui->table_Cursors->item(0, i)->setText("-");
                for(int i = 1; i <= 3; i++) ui->table_Cursors->item(1, i)->setText("-");
                for(int i = 1; i <= 3; i++) ui->table_Cursors->item(2, i)->setText("-");
            }
            */
        }
    );
}
// //#########################状态指示灯########################
// /////////////////////////////////////////////////////////////
// ///////////////////校准实现/////////////////////
//void MainWindow::on_btnOpenCali_clicked()
//{
//
//    if (vi != 0) {
//        // ==========================================
//        // 1. 申请仪器控制权 (加锁)
//        // ==========================================
//        QString lockStatus = bode->queryCommand(":SYST:LOCK:REQ?\n");
//        // 可选：检查是否成功拿到锁（如果返回不是 1 或 OK，说明被别的软件占用了）
//        if (!lockStatus.contains("1") && !lockStatus.toUpper().contains("OK")) {
//            appendLog("获取仪器控制权失败，仪器可能正被官方软件占用！", LOG_ERROR);
//            return; // 拿不到锁就直接退出，不要往下执行了
//        }
//
//        appendLog("成功获取仪器控制权，开始校准...", LOG_INFO);
//        // ==========================================
//        // 2. 执行你的正常校准流程 (你原来的代码)
//        // ==========================================
//        QString ope = bode->bodeCalibration(BodeDrive::CalMode::Open);
//
//        appendLog("校准指令发送完毕", LOG_INFO);
//        appendLog(ope, LOG_INFO);
//        QString relok = bode->queryCommand(":SYST:LOCK:REL?\n");
//        appendLog("仪器控制权已释放", LOG_INFO);
//        //QString com=bode->bodeCalibration(vi);
//        //appendLog(com, LOG_INFO);
//
//    }
//    else {
//        appendLog("句柄无效，开路校准失败", LOG_ERROR);
//    }



void MainWindow::on_btnOpenCali_clicked()
{
    if (!bode || !bode->isConnected()) {
        appendLog("仪器未连接，无法校准！", LOG_ERROR);
        return;
    }
    // 1. [UI 线程] 禁用按钮，给出提示
    ui->btnOpenCali->setEnabled(false);
    appendLog("正在进行开路校准，仪器执行中...", LOG_INFO);

    // 2. 调用我们封装的异步神器
    executeAsync(
        // ----------------------------------------
        // 任务 A：后台耗时操作 (这里的代码都在子线程运行)
        // ----------------------------------------
        [=]() -> QString {
            bode->queryCommand(":SYST:LOCK:REQ?\n");
            QString result = bode->bodeCalibration(BodeDrive::CalMode::Open);
            bode->queryCommand(":SYST:LOCK:REL?\n");

            return result; // 把校准结果返回给下一步
        },

        // ----------------------------------------
        // 任务 B：UI 刷新操作 (这里的代码自动切回主线程)
        // ----------------------------------------
        [=](QString workerResult) {

            if (workerResult == "ERROR_DISCONNECTED") {
                appendLog("校准失败：未检测到物理设备！", LOG_ERROR);
            }
            else {
                appendLog("开路校准完成！", LOG_SUCCESS);
                appendLog("返回值: " + workerResult, LOG_INFO);
            }

            // 恢复按钮点击
            ui->btnOpenCali->setEnabled(true);
        }
    );
}//}

void MainWindow::on_btnShortCali_clicked()
{

    if (!bode || !bode->isConnected()) {
        appendLog("仪器未连接，无法校准！", LOG_ERROR);
        return;
    }

    // 1. [UI 线程] 禁用按钮，给出提示
    ui->btnShortCali->setEnabled(false);
    appendLog("正在进行短路校准，仪器执行中...", LOG_INFO);

    // 2. 调用我们封装的异步神器
    executeAsync(
        // ----------------------------------------
        // 任务 A：后台耗时操作 (这里的代码都在子线程运行)
        // ----------------------------------------
        [=]() -> QString {
            // 先检测物理掉线
            //if (!bode->checkPhysicalConnection()) {
            //    return "ERROR_DISCONNECTED"; // 返回特定错误码
            //}

            bode->queryCommand(":SYST:LOCK:REQ?\n");
            QString result = bode->bodeCalibration(BodeDrive::CalMode::Short);
            bode->queryCommand(":SYST:LOCK:REL?\n");

            return result; // 把校准结果返回给下一步
        },

        // ----------------------------------------
        // 任务 B：UI 刷新操作 (这里的代码自动切回主线程)
        // ----------------------------------------
        [=](QString workerResult) {

            if (workerResult == "ERROR_DISCONNECTED") {
                appendLog("校准失败：未检测到物理设备！", LOG_ERROR);
            }
            else {
                appendLog("短路校准完成！", LOG_SUCCESS);
                appendLog("返回值: " + workerResult, LOG_INFO);
            }

            // 恢复按钮点击
            ui->btnShortCali->setEnabled(true);
        }
    );
}

void MainWindow::on_btnLoadCali_clicked()
{
    if (!bode || !bode->isConnected()) {
        appendLog("仪器未连接，无法校准！", LOG_ERROR);
        return;
    }

    // 1. [UI 线程] 禁用按钮，给出提示
    ui->btnLoadCali->setEnabled(false);
    appendLog("正在进行负载校准，仪器执行中...", LOG_INFO);

    // 2. 调用我们封装的异步神器
    executeAsync(
        // ----------------------------------------
        // 任务 A：后台耗时操作 (这里的代码都在子线程运行)
        // ----------------------------------------
        [=]() -> QString {
            // 先检测物理掉线
            //if (!bode->checkPhysicalConnection()) {
            //    return "ERROR_DISCONNECTED"; // 返回特定错误码
            //}

            bode->queryCommand(":SYST:LOCK:REQ?\n");
            QString result = bode->bodeCalibration(BodeDrive::CalMode::Load);
            bode->queryCommand(":SYST:LOCK:REL?\n");

            return result; // 把校准结果返回给下一步
        },

        // ----------------------------------------
        // 任务 B：UI 刷新操作 (这里的代码自动切回主线程)
        // ----------------------------------------
        [=](QString workerResult) {

            if (workerResult == "ERROR_DISCONNECTED") {
                appendLog("校准失败：未检测到物理设备！", LOG_ERROR);
            }
            else {
                appendLog("开路校准完成！", LOG_SUCCESS);
                appendLog("返回值: " + workerResult, LOG_INFO);
            }

            // 恢复按钮点击
            ui->btnLoadCali->setEnabled(true);
        }
    );
}

// ///////////////////校准实现/////////////////////
// // ------------------------------------------------------
// ///////////////////////////////////////阻抗分析测试配置页面实现////////////////////////
//void MainWindow::on_btnStartMeasurement_clicked()
//{
//    if (vi == 0) {
//        appendLog("仪器未连接，请先连接仪器！", LOG_ERROR);
//        return;
//    }
//
//    // ==========================================
//    // 1. 收集 UI 上的用户参数
//    // ==========================================
//    SweepParams params;
//
//    // 因为你是 SpinBox，通过 value() 获取数字，并转换为字符串发给仪器
//    // 假设你的 SpinBox 单位默认是 Hz
//    params.startFreq = std::to_string(ui->spinStartFreq->value());
//    params.stopFreq = std::to_string(ui->spinStopFreq->value());
//    params.points = ui->spinSweepPoint->value();
//
//    // 判断扫频模式 (假设 ComboBox 第1项是线性，第2项是对数)
//    if (ui->boxSweepMode->currentIndex() == 0) {
//        params.sweepType = "LIN";
//    }
//    else {
//        params.sweepType = "LOG";
//    }
//
//    params.bandwidth = "300Hz"; // 暂时写死，或者你后续也可以加一个控件
//
//    // ==========================================
//    // 2. 锁定界面按钮，防止重复点击
//    // ==========================================
//    ui->btnStartMeasurement->setEnabled(false);
//    appendLog(QString(">>> 开始自动测量 | 范围: %1Hz - %2Hz | 点数: %3")
//        .arg(QString::fromStdString(params.startFreq)).arg(QString::fromStdString(params.stopFreq)).arg(QString::number(params.points)), LOG_INFO);
//
//    // ==========================================
//    // 3. 开启子线程执行测量 (防卡死)
//    // ==========================================
//    QFuture<void> future = QtConcurrent::run([=]() {
//
//        // 调用底层的测量函数
//        MeasureResult result = bode->performMeasurement( params);
//
//        // ==========================================
//        // 4. 切回主线程更新 UI
//        // ==========================================
//        QMetaObject::invokeMethod(this, [=]() {
//            if (result.success) {
//                appendLog("✅ " + result.message, LOG_INFO);
//
//                // 仅作演示：打印拿到的第一个点的数据，证明数据真的抓回来了
//                if (!result.frequencies.empty()) {
//                    QString pointInfo = QString("样本数据 [1] -> 频率: %1 Hz, 阻抗: %2 欧姆, 相位: %3 度")
//                        .arg(result.frequencies[0])
//                        .arg(result.magnitudes[0])
//                        .arg(result.phases[0]);
//                    appendLog(pointInfo, LOG_INFO);
//                }
//
//                // 【下一步预留位置】
//                // 这里拿到了完整的 result.frequencies, result.magnitudes
//                // 之后你可以把这些数组丢给 QCustomPlot 画出曲线！
//
//            }
//            else {
//                appendLog("❌ " + result.message, LOG_ERROR);
//            }
//
//            // 测量结束，恢复按钮点击功能
//            ui->btnStartMeasurement->setEnabled(true);
//            });
//        });
//}

void MainWindow::on_btnStartMeasurement_clicked()
{
    if (!bode || !bode->isConnected()) {
        appendLog("仪器未连接，无法校准！", LOG_ERROR);
        return;
    }

    // ==========================================
    // 1. 收集 UI 上的用户参数
    // ==========================================
    SweepParams params;

    params.startFreq = std::to_string(ui->spinStartFreq->value());
    params.stopFreq = std::to_string(ui->spinStopFreq->value());
    params.points = ui->spinSweepPoint->value();

    if (ui->boxSweepMode->currentIndex() == 0) {
        params.sweepType = "LIN";
    }
    else {
        params.sweepType = "LOG";
    }

    params.bandwidth = "300Hz"; // 此处暂时写死，后续可绑定UI控件

    // ==========================================
    // 2. 锁定界面按钮，防止重复点击
    // ==========================================
    ui->btnStartMeasurement->setEnabled(false);
    appendLog(QString(">>> 开始自动测量 | 范围: %1Hz - %2Hz | 点数: %3")
        .arg(QString::fromStdString(params.startFreq))
        .arg(QString::fromStdString(params.stopFreq))
        .arg(QString::number(params.points)), LOG_INFO);

    // ==========================================
    // 3. 开启子线程执行测量 (防卡死)
    // ==========================================
    struct MeasurementUiResult {
        MeasureResult result;
        QVector<double> xFreq;
        QVector<double> yCond;
        QVector<double> ySusp;
    };

    executeAsync(
        [=]() -> MeasurementUiResult {
            MeasurementUiResult workerResult;
            workerResult.result = bode->performMeasurement(params);

            if (!workerResult.result.success) {
                return workerResult;
            }

            size_t count = workerResult.result.frequencies.size();
            if (workerResult.result.magnitudes.size() < count) {
                count = workerResult.result.magnitudes.size();
            }
            if (workerResult.result.phases.size() < count) {
                count = workerResult.result.phases.size();
            }

            workerResult.xFreq.reserve(static_cast<int>(count));
            workerResult.yCond.reserve(static_cast<int>(count));
            workerResult.ySusp.reserve(static_cast<int>(count));

            for (size_t i = 0; i < count; ++i) {
                double f = static_cast<double>(workerResult.result.frequencies[i]) / 1000.0;
                double zMag = static_cast<double>(workerResult.result.magnitudes[i]);
                double zPhaseDeg = static_cast<double>(workerResult.result.phases[i]);

                workerResult.xFreq.push_back(f);

                if (zMag != 0.0 && !std::isnan(zMag)) {
                    double zPhaseRad = zPhaseDeg * M_PI / 180.0;
                    double G = std::cos(zPhaseRad) / zMag;
                    double B = -std::sin(zPhaseRad) / zMag;

                    if (std::isnan(G) || std::isinf(G)) G = 0.0;
                    if (std::isnan(B) || std::isinf(B)) B = 0.0;

                    workerResult.yCond.push_back(G);
                    workerResult.ySusp.push_back(B);
                }
                else {
                    workerResult.yCond.push_back(0.0);
                    workerResult.ySusp.push_back(0.0);
                }
            }

            return workerResult;
        },
        [=](MeasurementUiResult workerResult) {
            const MeasureResult& result = workerResult.result;

            if (result.success) {
                appendLog("✅ " + result.message, LOG_INFO);

                // 安全校验：确保在 UI 构造函数中已经 addGraph() 至少两次了
                if (ui->plotAdmittance->graphCount() >= 2) {
                    ui->plotAdmittance->graph(0)->setData(workerResult.xFreq, workerResult.yCond);
                    ui->plotAdmittance->graph(1)->setData(workerResult.xFreq, workerResult.ySusp);

                    ui->plotAdmittance->graph(0)->rescaleKeyAxis();
                    ui->plotAdmittance->graph(0)->rescaleValueAxis();
                    ui->plotAdmittance->graph(1)->rescaleValueAxis();

                    ui->plotAdmittance->replot();
                    appendLog("双轴导纳曲线绘制成功！", LOG_SUCCESS);
                }
                else {
                    appendLog("绘图失败：图表未正确初始化 (图层数量 < 2)", LOG_WARNING);
                }
            }
            else {
                appendLog("❌ 测量失败：" + result.message, LOG_ERROR);
            }

            ui->btnStartMeasurement->setEnabled(true);
        }
    );
}




// -------------------------------------------------------------------------------------------


