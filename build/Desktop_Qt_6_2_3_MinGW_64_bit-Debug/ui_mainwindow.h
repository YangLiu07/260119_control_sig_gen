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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
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
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_7;
    QLabel *label_11;
    QLineEdit *lineEditDGAddress;
    QPushButton *btnConnect1_2;
    QLabel *label_12;
    QLineEdit *lineEditMRAddress_4;
    QLabel *label_13;
    QLineEdit *lineEditAddress_5;
    QLabel *led_gen;
    QLabel *led_MR6000;
    QLabel *led_car;
    QLabel *label_14;
    QLineEdit *lineEditAddress_6;
    QLabel *label_15;
    QLineEdit *lineEditAddress_7;
    QGroupBox *groupBox;
    QGroupBox *groupBox_8;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QComboBox *comboBox_selectWaweMode;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label_16;
    QDoubleSpinBox *doubleSpinBoxFreq;
    QLabel *label_2;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox;
    QDoubleSpinBox *doubleSpinBoxFreq_4;
    QPushButton *btnOutput;
    QWidget *page_2;
    QLabel *label_23;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBoxFreq_2;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_3;
    QPushButton *btnOutput_2;
    QDoubleSpinBox *doubleSpinBoxFreq_5;
    QLabel *label_3;
    QGroupBox *groupBox_9;
    QComboBox *comboBox_3;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QComboBox *comboBox_4;
    QComboBox *comboBox_7;
    QGroupBox *groupBox_10;
    QLabel *label_20;
    QComboBox *comboBox_5;
    QLabel *label_21;
    QComboBox *comboBox_6;
    QLabel *label_22;
    QGroupBox *groupBox_4;
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
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setEnabled(true);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 672, 381));
        horizontalLayout = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_7 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setMinimumSize(QSize(0, 110));
        groupBox_7->setMaximumSize(QSize(16777215, 100));
        groupBox_7->setAutoFillBackground(true);
        groupBox_7->setFlat(true);
        groupBox_7->setCheckable(false);
        label_11 = new QLabel(groupBox_7);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 20, 91, 21));
        lineEditDGAddress = new QLineEdit(groupBox_7);
        lineEditDGAddress->setObjectName(QString::fromUtf8("lineEditDGAddress"));
        lineEditDGAddress->setGeometry(QRect(130, 20, 171, 20));
        btnConnect1_2 = new QPushButton(groupBox_7);
        btnConnect1_2->setObjectName(QString::fromUtf8("btnConnect1_2"));
        btnConnect1_2->setGeometry(QRect(260, 80, 141, 21));
        label_12 = new QLabel(groupBox_7);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 50, 121, 21));
        label_12->setAutoFillBackground(false);
        lineEditMRAddress_4 = new QLineEdit(groupBox_7);
        lineEditMRAddress_4->setObjectName(QString::fromUtf8("lineEditMRAddress_4"));
        lineEditMRAddress_4->setGeometry(QRect(130, 50, 171, 20));
        label_13 = new QLabel(groupBox_7);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(360, 20, 71, 21));
        lineEditAddress_5 = new QLineEdit(groupBox_7);
        lineEditAddress_5->setObjectName(QString::fromUtf8("lineEditAddress_5"));
        lineEditAddress_5->setGeometry(QRect(430, 20, 171, 20));
        led_gen = new QLabel(groupBox_7);
        led_gen->setObjectName(QString::fromUtf8("led_gen"));
        led_gen->setGeometry(QRect(310, 20, 16, 16));
        led_MR6000 = new QLabel(groupBox_7);
        led_MR6000->setObjectName(QString::fromUtf8("led_MR6000"));
        led_MR6000->setGeometry(QRect(310, 50, 16, 16));
        led_car = new QLabel(groupBox_7);
        led_car->setObjectName(QString::fromUtf8("led_car"));
        led_car->setGeometry(QRect(600, 20, 16, 16));
        label_14 = new QLabel(groupBox_7);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(360, 50, 71, 21));
        lineEditAddress_6 = new QLineEdit(groupBox_7);
        lineEditAddress_6->setObjectName(QString::fromUtf8("lineEditAddress_6"));
        lineEditAddress_6->setGeometry(QRect(430, 50, 61, 20));
        label_15 = new QLabel(groupBox_7);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(500, 50, 41, 21));
        lineEditAddress_7 = new QLineEdit(groupBox_7);
        lineEditAddress_7->setObjectName(QString::fromUtf8("lineEditAddress_7"));
        lineEditAddress_7->setGeometry(QRect(550, 50, 61, 20));

        verticalLayout->addWidget(groupBox_7);

        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(0, 50));
        groupBox->setMaximumSize(QSize(16777215, 120));
        groupBox_8 = new QGroupBox(groupBox);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 20, 231, 101));
        groupBox_8->setMinimumSize(QSize(0, 50));
        layoutWidget = new QWidget(groupBox_8);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(-3, 10, 231, 81));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        comboBox_selectWaweMode = new QComboBox(layoutWidget);
        comboBox_selectWaweMode->addItem(QString());
        comboBox_selectWaweMode->addItem(QString());
        comboBox_selectWaweMode->setObjectName(QString::fromUtf8("comboBox_selectWaweMode"));

        verticalLayout_3->addWidget(comboBox_selectWaweMode);

        stackedWidget = new QStackedWidget(layoutWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        label_16 = new QLabel(page);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(0, 40, 51, 20));
        doubleSpinBoxFreq = new QDoubleSpinBox(page);
        doubleSpinBoxFreq->setObjectName(QString::fromUtf8("doubleSpinBoxFreq"));
        doubleSpinBoxFreq->setGeometry(QRect(60, 0, 41, 16));
        label_2 = new QLabel(page);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 0, 51, 21));
        label_4 = new QLabel(page);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 20, 31, 21));
        doubleSpinBox = new QDoubleSpinBox(page);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(60, 40, 41, 16));
        doubleSpinBoxFreq_4 = new QDoubleSpinBox(page);
        doubleSpinBoxFreq_4->setObjectName(QString::fromUtf8("doubleSpinBoxFreq_4"));
        doubleSpinBoxFreq_4->setGeometry(QRect(60, 20, 41, 16));
        btnOutput = new QPushButton(page);
        btnOutput->setObjectName(QString::fromUtf8("btnOutput"));
        btnOutput->setGeometry(QRect(140, 50, 61, 16));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        label_23 = new QLabel(page_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(7, 7, 45, 16));
        lineEdit = new QLineEdit(page_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(56, 7, 114, 16));
        lineEdit->setReadOnly(true);
        pushButton = new QPushButton(page_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(174, 7, 56, 16));
        layoutWidget1 = new QWidget(page_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(6, 21, 225, 21));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        doubleSpinBoxFreq_2 = new QDoubleSpinBox(layoutWidget1);
        doubleSpinBoxFreq_2->setObjectName(QString::fromUtf8("doubleSpinBoxFreq_2"));

        gridLayout_2->addWidget(doubleSpinBoxFreq_2, 0, 1, 1, 1);

        layoutWidget2 = new QWidget(page_2);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(6, 36, 225, 21));
        gridLayout_3 = new QGridLayout(layoutWidget2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        btnOutput_2 = new QPushButton(layoutWidget2);
        btnOutput_2->setObjectName(QString::fromUtf8("btnOutput_2"));

        gridLayout_3->addWidget(btnOutput_2, 0, 2, 1, 1);

        doubleSpinBoxFreq_5 = new QDoubleSpinBox(layoutWidget2);
        doubleSpinBoxFreq_5->setObjectName(QString::fromUtf8("doubleSpinBoxFreq_5"));

        gridLayout_3->addWidget(doubleSpinBoxFreq_5, 0, 1, 1, 1);

        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        stackedWidget->addWidget(page_2);

        verticalLayout_3->addWidget(stackedWidget);

        groupBox_9 = new QGroupBox(groupBox);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(446, 20, 216, 95));
        groupBox_9->setMinimumSize(QSize(0, 50));
        comboBox_3 = new QComboBox(groupBox_9);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(40, 15, 61, 16));
        label_17 = new QLabel(groupBox_9);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 10, 21, 21));
        label_18 = new QLabel(groupBox_9);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(10, 30, 21, 21));
        label_19 = new QLabel(groupBox_9);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(10, 50, 21, 21));
        comboBox_4 = new QComboBox(groupBox_9);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(40, 35, 61, 16));
        comboBox_7 = new QComboBox(groupBox_9);
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->setObjectName(QString::fromUtf8("comboBox_7"));
        comboBox_7->setGeometry(QRect(40, 50, 61, 16));
        groupBox_10 = new QGroupBox(groupBox);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        groupBox_10->setGeometry(QRect(241, 20, 201, 95));
        groupBox_10->setMinimumSize(QSize(0, 50));
        label_20 = new QLabel(groupBox_10);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(70, 10, 41, 21));
        comboBox_5 = new QComboBox(groupBox_10);
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));
        comboBox_5->setGeometry(QRect(120, 10, 61, 16));
        label_21 = new QLabel(groupBox_10);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(70, 30, 41, 21));
        comboBox_6 = new QComboBox(groupBox_10);
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->setObjectName(QString::fromUtf8("comboBox_6"));
        comboBox_6->setGeometry(QRect(120, 30, 61, 16));
        label_22 = new QLabel(groupBox_10);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(40, 70, 151, 21));

        verticalLayout->addWidget(groupBox);

        groupBox_4 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setEnabled(true);
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        groupBox_4->setMaximumSize(QSize(16777215, 100));
        textBrowserLog = new QTextBrowser(groupBox_4);
        textBrowserLog->setObjectName(QString::fromUtf8("textBrowserLog"));
        textBrowserLog->setGeometry(QRect(7, 18, 655, 75));
        textBrowserLog->setMinimumSize(QSize(500, 15));
        textBrowserLog->setMaximumSize(QSize(16777215, 100));

        verticalLayout->addWidget(groupBox_4);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(2, 1);

        horizontalLayout->addLayout(verticalLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

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
        QWidget::setTabOrder(scrollArea, textBrowserLog);
        QWidget::setTabOrder(textBrowserLog, comboBox_6);
        QWidget::setTabOrder(comboBox_6, comboBox_3);
        QWidget::setTabOrder(comboBox_3, comboBox_4);
        QWidget::setTabOrder(comboBox_4, comboBox_5);
        QWidget::setTabOrder(comboBox_5, lineEditDGAddress);
        QWidget::setTabOrder(lineEditDGAddress, btnConnect1_2);
        QWidget::setTabOrder(btnConnect1_2, lineEditMRAddress_4);
        QWidget::setTabOrder(lineEditMRAddress_4, lineEditAddress_5);
        QWidget::setTabOrder(lineEditAddress_5, lineEditAddress_6);
        QWidget::setTabOrder(lineEditAddress_6, lineEditAddress_7);
        QWidget::setTabOrder(lineEditAddress_7, comboBox_7);
        QWidget::setTabOrder(comboBox_7, btnOutput);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_4->menuAction());
        menubar->addAction(menu_5->menuAction());
        menu->addSeparator();

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actiondanpin->setText(QCoreApplication::translate("MainWindow", "danpin", nullptr));
        actionSWEEP->setText(QCoreApplication::translate("MainWindow", "SWEEP", nullptr));
        actionARB->setText(QCoreApplication::translate("MainWindow", "ARB", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "\344\273\252\345\231\250\350\207\252\346\243\200", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\344\277\241\345\217\267\346\272\220VISA\345\234\260\345\235\200\357\274\232", nullptr));
        lineEditDGAddress->setText(QCoreApplication::translate("MainWindow", "TCPIP0::169.254.96.21::INSTR", nullptr));
        btnConnect1_2->setText(QCoreApplication::translate("MainWindow", "\350\207\252\346\243\200", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\351\207\207\351\233\206\344\273\252VISA\345\234\260\345\235\200\357\274\232", nullptr));
        lineEditMRAddress_4->setText(QCoreApplication::translate("MainWindow", "TCPIP0::169.254.96.21::INSTR", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\350\241\214\350\275\246IP\345\234\260\345\235\200\357\274\232", nullptr));
        lineEditAddress_5->setText(QCoreApplication::translate("MainWindow", "TCPIP0::169.254.96.21::INSTR", nullptr));
        led_gen->setText(QString());
        led_MR6000->setText(QString());
        led_car->setText(QString());
        label_14->setText(QCoreApplication::translate("MainWindow", "\346\273\244\346\224\276\344\270\262\345\217\243\357\274\232", nullptr));
        lineEditAddress_6->setText(QCoreApplication::translate("MainWindow", "COM11", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        lineEditAddress_7->setText(QCoreApplication::translate("MainWindow", "9600", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\344\273\252\345\231\250\351\205\215\347\275\256", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("MainWindow", "\344\277\241\345\217\267\346\272\220", nullptr));
        comboBox_selectWaweMode->setItemText(0, QCoreApplication::translate("MainWindow", "\346\211\253\351\242\221/\345\215\225\351\242\221\344\277\241\345\217\267", nullptr));
        comboBox_selectWaweMode->setItemText(1, QCoreApplication::translate("MainWindow", "\350\207\252\345\256\232\344\271\211\344\277\241\345\217\267", nullptr));

        label_16->setText(QCoreApplication::translate("MainWindow", "\346\211\253\351\242\221\346\227\266\351\227\264\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\211\253\351\242\221\350\214\203\345\233\264\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\271\205  \345\272\246\357\274\232", nullptr));
        btnOutput->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\207\272", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "\346\263\242\345\275\242\346\226\207\344\273\266\357\274\232", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "\346\234\252\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\351\207\207\346\240\267\347\216\207\357\274\210kHz\357\274\211", nullptr));
        btnOutput_2->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\207\272", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\271\205 \345\272\246\357\274\210V\357\274\211", nullptr));
        groupBox_9->setTitle(QCoreApplication::translate("MainWindow", "\346\273\244\346\263\242\346\224\276\345\244\247\345\231\250", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "\351\200\232\351\201\223A\347\273\204", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("MainWindow", "\351\200\232\351\201\223B\347\273\204", nullptr));

        label_17->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\223\357\274\232", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "\345\242\236\347\233\212\357\274\232", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "\351\200\232\345\270\246\357\274\232", nullptr));
        comboBox_4->setItemText(0, QCoreApplication::translate("MainWindow", "10dB", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("MainWindow", "20dB", nullptr));
        comboBox_4->setItemText(2, QCoreApplication::translate("MainWindow", "30dB", nullptr));
        comboBox_4->setItemText(3, QCoreApplication::translate("MainWindow", "40dB", nullptr));
        comboBox_4->setItemText(4, QCoreApplication::translate("MainWindow", "50dB", nullptr));
        comboBox_4->setItemText(5, QCoreApplication::translate("MainWindow", "60dB", nullptr));

        comboBox_7->setItemText(0, QCoreApplication::translate("MainWindow", "10dB", nullptr));
        comboBox_7->setItemText(1, QCoreApplication::translate("MainWindow", "20dB", nullptr));
        comboBox_7->setItemText(2, QCoreApplication::translate("MainWindow", "30dB", nullptr));
        comboBox_7->setItemText(3, QCoreApplication::translate("MainWindow", "40dB", nullptr));
        comboBox_7->setItemText(4, QCoreApplication::translate("MainWindow", "50dB", nullptr));
        comboBox_7->setItemText(5, QCoreApplication::translate("MainWindow", "60dB", nullptr));

        groupBox_10->setTitle(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\351\207\207\351\233\206\344\273\252", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "\351\207\207\346\240\267\347\216\207\357\274\232", nullptr));
        comboBox_5->setItemText(0, QCoreApplication::translate("MainWindow", "\351\200\232\351\201\223A\347\273\204", nullptr));
        comboBox_5->setItemText(1, QCoreApplication::translate("MainWindow", "\351\200\232\351\201\223B\347\273\204", nullptr));

        label_21->setText(QCoreApplication::translate("MainWindow", "\351\207\207\346\240\267\346\227\266\351\227\264\357\274\232", nullptr));
        comboBox_6->setItemText(0, QCoreApplication::translate("MainWindow", "\351\200\232\351\201\223A\347\273\204", nullptr));
        comboBox_6->setItemText(1, QCoreApplication::translate("MainWindow", "\351\200\232\351\201\223B\347\273\204", nullptr));

        label_22->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\2231->\346\240\207\345\220\254 \351\200\232\351\201\2232->\345\212\237\346\224\276\346\243\200\346\265\213\347\224\265\345\216\213", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227", nullptr));
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
