/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actiondanpin;
    QAction *actionSWEEP;
    QAction *actionARB;
    QAction *actioninsconfig;
    QAction *actionexpOutput;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout;
    QLabel *label_25;
    QLineEdit *lineEditDGAddress;
    QLabel *led_gen_2;
    QLabel *label_27;
    QLineEdit *lineEditHangCheAddress;
    QLabel *led_car_2;
    QLabel *label_26;
    QLineEdit *lineEditMRAddress;
    QLabel *led_MR6000_2;
    QLabel *label_28;
    QLineEdit *lineEditFilterAmpAddress;
    QLabel *label_29;
    QLineEdit *lineEditFilterAmpPort;
    QPushButton *btnSelfTest;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_12;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_7;
    QComboBox *comboBox_selectWaweMode_2;
    QStackedWidget *stackedWidget_2;
    QWidget *page_3;
    QGridLayout *gridLayout_6;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBoxFreq;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBoxAmp;
    QLabel *label_30;
    QDoubleSpinBox *doubleSpinBox_2;
    QPushButton *btnOutput_2;
    QPushButton *pushButton;
    QWidget *page_4;
    QGridLayout *gridLayout_3;
    QLabel *label_8;
    QLabel *label_9;
    QDoubleSpinBox *doubleSpinBoxFreq_7;
    QLabel *label_31;
    QPushButton *pushButton_2;
    QDoubleSpinBox *doubleSpinBoxFreq_8;
    QLineEdit *lineEdit_2;
    QGroupBox *groupBox_13;
    QGridLayout *gridLayout_4;
    QLabel *label_32;
    QComboBox *comboBox_9;
    QLabel *label_33;
    QComboBox *comboBox_10;
    QLabel *label_34;
    QGroupBox *groupBox_14;
    QFormLayout *formLayout_2;
    QLabel *label_35;
    QComboBox *comboBox_11;
    QLabel *label_36;
    QComboBox *comboBox_12;
    QLabel *label_37;
    QComboBox *comboBox_13;
    QLabel *label_38;
    QComboBox *comboBox_14;
    QPushButton *btnOutput;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_8;
    QTextBrowser *textBrowserLog;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(686, 431);
        actiondanpin = new QAction(MainWindow);
        actiondanpin->setObjectName(QString::fromUtf8("actiondanpin"));
        actionSWEEP = new QAction(MainWindow);
        actionSWEEP->setObjectName(QString::fromUtf8("actionSWEEP"));
        actionARB = new QAction(MainWindow);
        actionARB->setObjectName(QString::fromUtf8("actionARB"));
        actioninsconfig = new QAction(MainWindow);
        actioninsconfig->setObjectName(QString::fromUtf8("actioninsconfig"));
        actionexpOutput = new QAction(MainWindow);
        actionexpOutput->setObjectName(QString::fromUtf8("actionexpOutput"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        groupBox_11 = new QGroupBox(centralwidget);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_11->sizePolicy().hasHeightForWidth());
        groupBox_11->setSizePolicy(sizePolicy);
        groupBox_11->setMinimumSize(QSize(0, 100));
        groupBox_11->setMaximumSize(QSize(16777215, 16777215));
        groupBox_11->setAutoFillBackground(true);
        groupBox_11->setFlat(true);
        groupBox_11->setCheckable(false);
        gridLayout = new QGridLayout(groupBox_11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_25 = new QLabel(groupBox_11);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout->addWidget(label_25, 0, 0, 1, 1);

        lineEditDGAddress = new QLineEdit(groupBox_11);
        lineEditDGAddress->setObjectName(QString::fromUtf8("lineEditDGAddress"));

        gridLayout->addWidget(lineEditDGAddress, 0, 1, 1, 1);

        led_gen_2 = new QLabel(groupBox_11);
        led_gen_2->setObjectName(QString::fromUtf8("led_gen_2"));

        gridLayout->addWidget(led_gen_2, 0, 2, 1, 1);

        label_27 = new QLabel(groupBox_11);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout->addWidget(label_27, 0, 3, 1, 1);

        lineEditHangCheAddress = new QLineEdit(groupBox_11);
        lineEditHangCheAddress->setObjectName(QString::fromUtf8("lineEditHangCheAddress"));

        gridLayout->addWidget(lineEditHangCheAddress, 0, 4, 1, 3);

        led_car_2 = new QLabel(groupBox_11);
        led_car_2->setObjectName(QString::fromUtf8("led_car_2"));

        gridLayout->addWidget(led_car_2, 0, 7, 1, 1);

        label_26 = new QLabel(groupBox_11);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setAutoFillBackground(false);

        gridLayout->addWidget(label_26, 1, 0, 1, 1);

        lineEditMRAddress = new QLineEdit(groupBox_11);
        lineEditMRAddress->setObjectName(QString::fromUtf8("lineEditMRAddress"));

        gridLayout->addWidget(lineEditMRAddress, 1, 1, 1, 1);

        led_MR6000_2 = new QLabel(groupBox_11);
        led_MR6000_2->setObjectName(QString::fromUtf8("led_MR6000_2"));

        gridLayout->addWidget(led_MR6000_2, 1, 2, 1, 1);

        label_28 = new QLabel(groupBox_11);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout->addWidget(label_28, 1, 3, 1, 1);

        lineEditFilterAmpAddress = new QLineEdit(groupBox_11);
        lineEditFilterAmpAddress->setObjectName(QString::fromUtf8("lineEditFilterAmpAddress"));

        gridLayout->addWidget(lineEditFilterAmpAddress, 1, 4, 1, 1);

        label_29 = new QLabel(groupBox_11);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout->addWidget(label_29, 1, 5, 1, 1);

        lineEditFilterAmpPort = new QLineEdit(groupBox_11);
        lineEditFilterAmpPort->setObjectName(QString::fromUtf8("lineEditFilterAmpPort"));

        gridLayout->addWidget(lineEditFilterAmpPort, 1, 6, 1, 2);

        btnSelfTest = new QPushButton(groupBox_11);
        btnSelfTest->setObjectName(QString::fromUtf8("btnSelfTest"));

        gridLayout->addWidget(btnSelfTest, 2, 1, 1, 3);


        verticalLayout_5->addWidget(groupBox_11);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setEnabled(true);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMinimumSize(QSize(0, 120));
        groupBox_2->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBox_12 = new QGroupBox(groupBox_2);
        groupBox_12->setObjectName(QString::fromUtf8("groupBox_12"));
        sizePolicy.setHeightForWidth(groupBox_12->sizePolicy().hasHeightForWidth());
        groupBox_12->setSizePolicy(sizePolicy);
        groupBox_12->setMinimumSize(QSize(0, 50));
        verticalLayout_6 = new QVBoxLayout(groupBox_12);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        comboBox_selectWaweMode_2 = new QComboBox(groupBox_12);
        comboBox_selectWaweMode_2->addItem(QString());
        comboBox_selectWaweMode_2->addItem(QString());
        comboBox_selectWaweMode_2->setObjectName(QString::fromUtf8("comboBox_selectWaweMode_2"));

        verticalLayout_7->addWidget(comboBox_selectWaweMode_2);

        stackedWidget_2 = new QStackedWidget(groupBox_12);
        stackedWidget_2->setObjectName(QString::fromUtf8("stackedWidget_2"));
        sizePolicy.setHeightForWidth(stackedWidget_2->sizePolicy().hasHeightForWidth());
        stackedWidget_2->setSizePolicy(sizePolicy);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        gridLayout_6 = new QGridLayout(page_3);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_6 = new QLabel(page_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_6->addWidget(label_6, 0, 0, 1, 1);

        doubleSpinBoxFreq = new QDoubleSpinBox(page_3);
        doubleSpinBoxFreq->setObjectName(QString::fromUtf8("doubleSpinBoxFreq"));

        gridLayout_6->addWidget(doubleSpinBoxFreq, 0, 1, 1, 1);

        label_7 = new QLabel(page_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_6->addWidget(label_7, 1, 0, 1, 1);

        doubleSpinBoxAmp = new QDoubleSpinBox(page_3);
        doubleSpinBoxAmp->setObjectName(QString::fromUtf8("doubleSpinBoxAmp"));

        gridLayout_6->addWidget(doubleSpinBoxAmp, 1, 1, 1, 1);

        label_30 = new QLabel(page_3);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_6->addWidget(label_30, 2, 0, 1, 1);

        doubleSpinBox_2 = new QDoubleSpinBox(page_3);
        doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));

        gridLayout_6->addWidget(doubleSpinBox_2, 2, 1, 1, 1);

        btnOutput_2 = new QPushButton(page_3);
        btnOutput_2->setObjectName(QString::fromUtf8("btnOutput_2"));

        gridLayout_6->addWidget(btnOutput_2, 3, 2, 1, 1);

        pushButton = new QPushButton(page_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_6->addWidget(pushButton, 3, 0, 1, 1);

        stackedWidget_2->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        gridLayout_3 = new QGridLayout(page_4);
        gridLayout_3->setSpacing(2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_8 = new QLabel(page_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_3->addWidget(label_8, 3, 0, 1, 1);

        label_9 = new QLabel(page_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_3->addWidget(label_9, 2, 0, 1, 2);

        doubleSpinBoxFreq_7 = new QDoubleSpinBox(page_4);
        doubleSpinBoxFreq_7->setObjectName(QString::fromUtf8("doubleSpinBoxFreq_7"));
        sizePolicy.setHeightForWidth(doubleSpinBoxFreq_7->sizePolicy().hasHeightForWidth());
        doubleSpinBoxFreq_7->setSizePolicy(sizePolicy);
        doubleSpinBoxFreq_7->setDecimals(0);

        gridLayout_3->addWidget(doubleSpinBoxFreq_7, 2, 2, 1, 1);

        label_31 = new QLabel(page_4);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_3->addWidget(label_31, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(page_4);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(pushButton_2, 0, 3, 1, 1);

        doubleSpinBoxFreq_8 = new QDoubleSpinBox(page_4);
        doubleSpinBoxFreq_8->setObjectName(QString::fromUtf8("doubleSpinBoxFreq_8"));
        sizePolicy.setHeightForWidth(doubleSpinBoxFreq_8->sizePolicy().hasHeightForWidth());
        doubleSpinBoxFreq_8->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(doubleSpinBoxFreq_8, 3, 2, 1, 1);

        lineEdit_2 = new QLineEdit(page_4);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        sizePolicy.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy);
        lineEdit_2->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit_2, 0, 2, 1, 1);

        stackedWidget_2->addWidget(page_4);

        verticalLayout_7->addWidget(stackedWidget_2);


        verticalLayout_6->addLayout(verticalLayout_7);


        horizontalLayout_3->addWidget(groupBox_12);

        groupBox_13 = new QGroupBox(groupBox_2);
        groupBox_13->setObjectName(QString::fromUtf8("groupBox_13"));
        sizePolicy.setHeightForWidth(groupBox_13->sizePolicy().hasHeightForWidth());
        groupBox_13->setSizePolicy(sizePolicy);
        groupBox_13->setMinimumSize(QSize(0, 50));
        gridLayout_4 = new QGridLayout(groupBox_13);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_32 = new QLabel(groupBox_13);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout_4->addWidget(label_32, 0, 0, 1, 1);

        comboBox_9 = new QComboBox(groupBox_13);
        comboBox_9->addItem(QString());
        comboBox_9->addItem(QString());
        comboBox_9->setObjectName(QString::fromUtf8("comboBox_9"));

        gridLayout_4->addWidget(comboBox_9, 0, 1, 1, 1);

        label_33 = new QLabel(groupBox_13);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout_4->addWidget(label_33, 1, 0, 1, 1);

        comboBox_10 = new QComboBox(groupBox_13);
        comboBox_10->addItem(QString());
        comboBox_10->addItem(QString());
        comboBox_10->setObjectName(QString::fromUtf8("comboBox_10"));

        gridLayout_4->addWidget(comboBox_10, 1, 1, 1, 1);

        label_34 = new QLabel(groupBox_13);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        gridLayout_4->addWidget(label_34, 2, 0, 1, 2);


        horizontalLayout_3->addWidget(groupBox_13);

        groupBox_14 = new QGroupBox(groupBox_2);
        groupBox_14->setObjectName(QString::fromUtf8("groupBox_14"));
        sizePolicy.setHeightForWidth(groupBox_14->sizePolicy().hasHeightForWidth());
        groupBox_14->setSizePolicy(sizePolicy);
        groupBox_14->setMinimumSize(QSize(0, 50));
        formLayout_2 = new QFormLayout(groupBox_14);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_35 = new QLabel(groupBox_14);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_35);

        comboBox_11 = new QComboBox(groupBox_14);
        comboBox_11->addItem(QString());
        comboBox_11->addItem(QString());
        comboBox_11->setObjectName(QString::fromUtf8("comboBox_11"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, comboBox_11);

        label_36 = new QLabel(groupBox_14);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_36);

        comboBox_12 = new QComboBox(groupBox_14);
        comboBox_12->addItem(QString());
        comboBox_12->addItem(QString());
        comboBox_12->addItem(QString());
        comboBox_12->addItem(QString());
        comboBox_12->addItem(QString());
        comboBox_12->addItem(QString());
        comboBox_12->setObjectName(QString::fromUtf8("comboBox_12"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, comboBox_12);

        label_37 = new QLabel(groupBox_14);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_37);

        comboBox_13 = new QComboBox(groupBox_14);
        comboBox_13->addItem(QString());
        comboBox_13->addItem(QString());
        comboBox_13->addItem(QString());
        comboBox_13->addItem(QString());
        comboBox_13->addItem(QString());
        comboBox_13->addItem(QString());
        comboBox_13->setObjectName(QString::fromUtf8("comboBox_13"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, comboBox_13);

        label_38 = new QLabel(groupBox_14);
        label_38->setObjectName(QString::fromUtf8("label_38"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_38);

        comboBox_14 = new QComboBox(groupBox_14);
        comboBox_14->addItem(QString());
        comboBox_14->addItem(QString());
        comboBox_14->addItem(QString());
        comboBox_14->addItem(QString());
        comboBox_14->addItem(QString());
        comboBox_14->addItem(QString());
        comboBox_14->setObjectName(QString::fromUtf8("comboBox_14"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, comboBox_14);

        btnOutput = new QPushButton(groupBox_14);
        btnOutput->setObjectName(QString::fromUtf8("btnOutput"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, btnOutput);


        horizontalLayout_3->addWidget(groupBox_14);


        verticalLayout_5->addWidget(groupBox_2);

        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setEnabled(true);
        sizePolicy.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy);
        groupBox_5->setMaximumSize(QSize(16777215, 100));
        verticalLayout_8 = new QVBoxLayout(groupBox_5);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        textBrowserLog = new QTextBrowser(groupBox_5);
        textBrowserLog->setObjectName(QString::fromUtf8("textBrowserLog"));
        textBrowserLog->setMinimumSize(QSize(500, 15));
        textBrowserLog->setMaximumSize(QSize(16777215, 100));

        verticalLayout_8->addWidget(textBrowserLog);


        verticalLayout_5->addWidget(groupBox_5);

        verticalLayout_5->setStretch(0, 1);
        verticalLayout_5->setStretch(1, 2);
        verticalLayout_5->setStretch(2, 1);

        verticalLayout->addLayout(verticalLayout_5);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 686, 18));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menu_5 = new QMenu(menubar);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_4->menuAction());
        menubar->addAction(menu_5->menuAction());
        menu->addSeparator();
        menu->addAction(actioninsconfig);
        menu->addAction(actionexpOutput);

        retranslateUi(MainWindow);

        stackedWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actiondanpin->setText(QCoreApplication::translate("MainWindow", "danpin", nullptr));
        actionSWEEP->setText(QCoreApplication::translate("MainWindow", "SWEEP", nullptr));
        actionARB->setText(QCoreApplication::translate("MainWindow", "ARB", nullptr));
        actioninsconfig->setText(QCoreApplication::translate("MainWindow", "insconfig", nullptr));
        actionexpOutput->setText(QCoreApplication::translate("MainWindow", "expOutput", nullptr));
        groupBox_11->setTitle(QCoreApplication::translate("MainWindow", "\344\273\252\345\231\250\350\207\252\346\243\200", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "\344\277\241\345\217\267\346\272\220VISA\345\234\260\345\235\200\357\274\232", nullptr));
        lineEditDGAddress->setText(QCoreApplication::translate("MainWindow", "TCPIP0::169.254.96.21::INSTR", nullptr));
        led_gen_2->setText(QString());
        label_27->setText(QCoreApplication::translate("MainWindow", "\350\241\214\350\275\246IP\345\234\260\345\235\200\357\274\232", nullptr));
        lineEditHangCheAddress->setText(QCoreApplication::translate("MainWindow", "TCPIP0::169.254.96.21::INSTR", nullptr));
        led_car_2->setText(QString());
        label_26->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\351\207\207\351\233\206\344\273\252VISA\345\234\260\345\235\200\357\274\232", nullptr));
        lineEditMRAddress->setText(QCoreApplication::translate("MainWindow", "TCPIP0::169.254.96.21::INSTR", nullptr));
        led_MR6000_2->setText(QString());
        label_28->setText(QCoreApplication::translate("MainWindow", "\346\273\244\346\224\276\344\270\262\345\217\243\357\274\232", nullptr));
        lineEditFilterAmpAddress->setText(QCoreApplication::translate("MainWindow", "COM11", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        lineEditFilterAmpPort->setText(QCoreApplication::translate("MainWindow", "9600", nullptr));
        btnSelfTest->setText(QCoreApplication::translate("MainWindow", "\350\207\252\346\243\200", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\344\273\252\345\231\250\351\205\215\347\275\256", nullptr));
        groupBox_12->setTitle(QCoreApplication::translate("MainWindow", "\344\277\241\345\217\267\346\272\220", nullptr));
        comboBox_selectWaweMode_2->setItemText(0, QCoreApplication::translate("MainWindow", "\346\211\253\351\242\221/\345\215\225\351\242\221\344\277\241\345\217\267", nullptr));
        comboBox_selectWaweMode_2->setItemText(1, QCoreApplication::translate("MainWindow", "\350\207\252\345\256\232\344\271\211\344\277\241\345\217\267", nullptr));

        label_6->setText(QCoreApplication::translate("MainWindow", "\346\211\253\351\242\221\350\214\203\345\233\264\357\274\232", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\345\271\205  \345\272\246\357\274\232", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "\346\211\253\351\242\221\346\227\266\351\227\264\357\274\232", nullptr));
        btnOutput_2->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\207\272", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\351\253\230\347\272\247\350\256\276\347\275\256", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\345\271\205 \345\272\246\357\274\210V\357\274\211", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\351\207\207\346\240\267\347\216\207\357\274\210kHz\357\274\211", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "\346\263\242\345\275\242\346\226\207\344\273\266\357\274\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "\346\234\252\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        groupBox_13->setTitle(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\351\207\207\351\233\206\344\273\252", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "\351\207\207\346\240\267\347\216\207\357\274\232", nullptr));
        comboBox_9->setItemText(0, QCoreApplication::translate("MainWindow", "\351\200\232\351\201\223A\347\273\204", nullptr));
        comboBox_9->setItemText(1, QCoreApplication::translate("MainWindow", "\351\200\232\351\201\223B\347\273\204", nullptr));

        label_33->setText(QCoreApplication::translate("MainWindow", "\351\207\207\346\240\267\346\227\266\351\227\264\357\274\232", nullptr));
        comboBox_10->setItemText(0, QCoreApplication::translate("MainWindow", "\351\200\232\351\201\223A\347\273\204", nullptr));
        comboBox_10->setItemText(1, QCoreApplication::translate("MainWindow", "\351\200\232\351\201\223B\347\273\204", nullptr));

        label_34->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\2231->\346\240\207\345\220\254 \351\200\232\351\201\2232->\345\212\237\346\224\276\346\243\200\346\265\213\347\224\265\345\216\213", nullptr));
        groupBox_14->setTitle(QCoreApplication::translate("MainWindow", "\346\273\244\346\263\242\346\224\276\345\244\247\345\231\250", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\223\357\274\232", nullptr));
        comboBox_11->setItemText(0, QCoreApplication::translate("MainWindow", "\351\200\232\351\201\223A\347\273\204", nullptr));
        comboBox_11->setItemText(1, QCoreApplication::translate("MainWindow", "\351\200\232\351\201\223B\347\273\204", nullptr));

        label_36->setText(QCoreApplication::translate("MainWindow", "\345\242\236\347\233\212\357\274\232", nullptr));
        comboBox_12->setItemText(0, QCoreApplication::translate("MainWindow", "10dB", nullptr));
        comboBox_12->setItemText(1, QCoreApplication::translate("MainWindow", "20dB", nullptr));
        comboBox_12->setItemText(2, QCoreApplication::translate("MainWindow", "30dB", nullptr));
        comboBox_12->setItemText(3, QCoreApplication::translate("MainWindow", "40dB", nullptr));
        comboBox_12->setItemText(4, QCoreApplication::translate("MainWindow", "50dB", nullptr));
        comboBox_12->setItemText(5, QCoreApplication::translate("MainWindow", "60dB", nullptr));

        label_37->setText(QCoreApplication::translate("MainWindow", "\344\275\216\351\200\232", nullptr));
        comboBox_13->setItemText(0, QCoreApplication::translate("MainWindow", "10dB", nullptr));
        comboBox_13->setItemText(1, QCoreApplication::translate("MainWindow", "20dB", nullptr));
        comboBox_13->setItemText(2, QCoreApplication::translate("MainWindow", "30dB", nullptr));
        comboBox_13->setItemText(3, QCoreApplication::translate("MainWindow", "40dB", nullptr));
        comboBox_13->setItemText(4, QCoreApplication::translate("MainWindow", "50dB", nullptr));
        comboBox_13->setItemText(5, QCoreApplication::translate("MainWindow", "60dB", nullptr));

        label_38->setText(QCoreApplication::translate("MainWindow", "\351\253\230\351\200\232", nullptr));
        comboBox_14->setItemText(0, QCoreApplication::translate("MainWindow", "10dB", nullptr));
        comboBox_14->setItemText(1, QCoreApplication::translate("MainWindow", "20dB", nullptr));
        comboBox_14->setItemText(2, QCoreApplication::translate("MainWindow", "30dB", nullptr));
        comboBox_14->setItemText(3, QCoreApplication::translate("MainWindow", "40dB", nullptr));
        comboBox_14->setItemText(4, QCoreApplication::translate("MainWindow", "50dB", nullptr));
        comboBox_14->setItemText(5, QCoreApplication::translate("MainWindow", "60dB", nullptr));

        btnOutput->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\207\272", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\345\217\221\345\260\204\347\211\271\346\200\247\346\265\213\350\257\225", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266\347\211\271\346\200\247\346\265\213\350\257\225", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\347\251\272\351\227\264\346\214\207\345\220\221\346\200\247\346\265\213\350\257\225", nullptr));
        menu_4->setTitle(QCoreApplication::translate("MainWindow", "\351\230\273\346\212\227\347\211\271\346\200\247\346\265\213\350\257\225", nullptr));
        menu_5->setTitle(QCoreApplication::translate("MainWindow", "\351\200\232\344\277\241\346\234\272\347\224\265\350\267\257\346\235\277\346\265\213\350\257\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
