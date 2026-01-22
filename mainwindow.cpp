#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime> // 必须引入这个
#include <QFile> // 必须引入这个
#include <QMenu>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QProcess>

//编写public函数MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. 初始化驱动对象，实例化对象？
    rigol = new RigolDriver(this);

   connect(rigol, &RigolDriver::sigLog, this, [=](QString msg){
        this->appendLog(msg,1); });

    //设置日志框允许自定义右键菜单
    ui->textBrowserLog->setContextMenuPolicy(Qt::CustomContextMenu);

    //连接“请求弹出菜单”的信号到我们的槽函数
    connect(ui->textBrowserLog, &QWidget::customContextMenuRequested,
            this, &MainWindow::on_logContextMenu);

}

//析构函数
MainWindow::~MainWindow()
{
    delete ui;
    // rigol 对象会随父对象自动析构，也会自动断开连接
}

// /////////////////////////////////////////日志管理////////////////////////////

//日志生成方法
void MainWindow::appendLog(const QString &msg, int level)
{
    // --- 1. 处理界面显示 (UI Logic) ---
    QString color = (level == 2) ? "red" : (level == 1 ? "orange" : "black");
    QString levelStr = (level == 2) ? "[ERROR]" : (level == 1 ? "[WARN]" : "[INFO]");

    QDateTime current = QDateTime::currentDateTime();
    QString timeStr = current.toString("[yyyy-MM-dd hh:mm:ss]");
    QString plainText = QString("%1 %2 %3").arg(timeStr, levelStr, msg);
    QString htmlText = QString("<font color='%1'>%2</font>").arg(color, plainText);

    ui->textBrowserLog->append(htmlText);

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


// 连接按钮
void MainWindow::on_btnConnect_clicked()
{
    // 获取输入框里的 VISA 地址
    // 实际地址建议去 NI MAX 软件里复制，例如 "USB0::0x1AB1::..."
    QString addr = ui->lineEditDGAddress->text();

    if(rigol->connectDevice(addr)) {
        ui->btnConnect1_2->setText("已连接");
        ui->btnConnect1_2->setEnabled(false);
    }
}

//设置幅度按钮
void MainWindow::on_btnSetAmp_clicked()
{
    double vpp = ui->doubleSpinBox->value();
    rigol->setAmplitude(vpp);
}
// 设置频率按钮
void MainWindow::on_btnSetFreq_clicked()
{
    // 获取 SpinBox 里的数值
    double freq = ui->doubleSpinBoxFreq->value();
    rigol->setFrequency(freq);
}

// 输出开关按钮 (Checkable Button)
void MainWindow::on_btnOutput_toggled(bool checked)
{
    rigol->setOutputState(checked);

    if(checked) {
        ui->btnOutput->setText("Output: ON");
        ui->btnOutput->setStyleSheet("background-color: green; color: white;");
    } else {
        ui->btnOutput->setText("Output: OFF");
        ui->btnOutput->setStyleSheet("");
    }
}
