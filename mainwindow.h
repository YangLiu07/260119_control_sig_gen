#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "rigoldriver.h" // 引入驱动头文件

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
// 新建类测试
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);//nullptr参数可选，可以指定不同的父亲，这是构造函数，公共的
    ~MainWindow();//这是析构函数，公共的

private slots:
    // 声明槽函数，这样 .cpp 里的函数才能对上号
    void on_btnConnect_clicked();
    void on_btnSetAmp_clicked();
    void on_btnSetFreq_clicked();
    void on_btnOutput_toggled(bool checked);
    void on_logContextMenu(const QPoint &pos); // ✨ 新增：处理右键菜单

private:
    Ui::MainWindow *ui;
    RigolDriver *rigol; // 声明驱动对象
    void appendLog(const QString &msg,int level);//私有增加日志方法；level=0黑色消息，level=1黄色警告，level=2红色错误
    void cleanOldLogs(const QString &path);

};

#endif // MAINWINDOW_H
