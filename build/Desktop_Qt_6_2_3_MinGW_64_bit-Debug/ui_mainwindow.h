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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
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
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_25;
    QLineEdit *lineEditDGAddress;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_26;
    QLineEdit *lineEditMRAddress;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_27;
    QLineEdit *lineEditHangCheAddress;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_28;
    QLineEdit *lineEditFilterAmpAddress;
    QLabel *label_29;
    QLineEdit *lineEditFilterAmpPort;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSelfTest;
    QSpacerItem *horizontalSpacer_2;
    QLabel *led_gen_2;
    QLabel *led_car_2;
    QLabel *led_MR6000_2;
    QFrame *line;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_12;
    QVBoxLayout *verticalLayout_11;
    QComboBox *comboBox_selectWaweMode_2;
    QStackedWidget *stackedWidget_2;
    QWidget *page_3;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *editSweepFreqStart;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *editSweepFreqEnd;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_15;
    QLabel *labelAmp;
    QSpacerItem *horizontalSpacer_9;
    QDoubleSpinBox *spinSweepAmp;
    QLabel *labelAmpUnit;
    QHBoxLayout *horizontalLayout_16;
    QLabel *labelSweepTime;
    QSpacerItem *horizontalSpacer_11;
    QDoubleSpinBox *spinSweepTime;
    QHBoxLayout *horizontalLayout_23;
    QLabel *labelSweepCount;
    QSpacerItem *horizontalSpacer_10;
    QSpinBox *spinSweepCount;
    QHBoxLayout *horizontalLayout_17;
    QPushButton *btnAdvanced;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnSweepConfig;
    QWidget *page_4;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_21;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_18;
    QLabel *labelWaveFile;
    QLineEdit *lineFileName;
    QPushButton *btnSelectArb;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_19;
    QLabel *labelArbSampleRate;
    QDoubleSpinBox *spinArbSampleRate;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_20;
    QLabel *labelArbAmp;
    QDoubleSpinBox *spinArbAmp;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_22;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *btnArbConfig;
    QGroupBox *groupBox_13;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_32;
    QComboBox *comboBox_9;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_33;
    QComboBox *comboBox_10;
    QLabel *label_34;
    QGroupBox *groupBox_14;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_35;
    QComboBox *comboBox_11;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_36;
    QComboBox *comboBox_12;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_37;
    QComboBox *comboBox_13;
    QHBoxLayout *horizontalLayout_13;
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
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
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
        verticalLayout_6 = new QVBoxLayout(centralwidget);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
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
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_25 = new QLabel(groupBox_11);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        horizontalLayout_4->addWidget(label_25);

        lineEditDGAddress = new QLineEdit(groupBox_11);
        lineEditDGAddress->setObjectName(QString::fromUtf8("lineEditDGAddress"));

        horizontalLayout_4->addWidget(lineEditDGAddress);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_26 = new QLabel(groupBox_11);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setAutoFillBackground(false);

        horizontalLayout_5->addWidget(label_26);

        lineEditMRAddress = new QLineEdit(groupBox_11);
        lineEditMRAddress->setObjectName(QString::fromUtf8("lineEditMRAddress"));

        horizontalLayout_5->addWidget(lineEditMRAddress);


        verticalLayout_3->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_27 = new QLabel(groupBox_11);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        horizontalLayout->addWidget(label_27);

        lineEditHangCheAddress = new QLineEdit(groupBox_11);
        lineEditHangCheAddress->setObjectName(QString::fromUtf8("lineEditHangCheAddress"));

        horizontalLayout->addWidget(lineEditHangCheAddress);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_28 = new QLabel(groupBox_11);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        horizontalLayout_2->addWidget(label_28);

        lineEditFilterAmpAddress = new QLineEdit(groupBox_11);
        lineEditFilterAmpAddress->setObjectName(QString::fromUtf8("lineEditFilterAmpAddress"));

        horizontalLayout_2->addWidget(lineEditFilterAmpAddress);

        label_29 = new QLabel(groupBox_11);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        horizontalLayout_2->addWidget(label_29);

        lineEditFilterAmpPort = new QLineEdit(groupBox_11);
        lineEditFilterAmpPort->setObjectName(QString::fromUtf8("lineEditFilterAmpPort"));

        horizontalLayout_2->addWidget(lineEditFilterAmpPort);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_6->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        btnSelfTest = new QPushButton(groupBox_11);
        btnSelfTest->setObjectName(QString::fromUtf8("btnSelfTest"));

        horizontalLayout_7->addWidget(btnSelfTest);

        horizontalSpacer_2 = new QSpacerItem(178, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout_7);


        gridLayout->addLayout(verticalLayout_4, 0, 0, 2, 1);

        led_gen_2 = new QLabel(groupBox_11);
        led_gen_2->setObjectName(QString::fromUtf8("led_gen_2"));

        gridLayout->addWidget(led_gen_2, 0, 1, 1, 1);

        led_car_2 = new QLabel(groupBox_11);
        led_car_2->setObjectName(QString::fromUtf8("led_car_2"));

        gridLayout->addWidget(led_car_2, 0, 3, 1, 1);

        led_MR6000_2 = new QLabel(groupBox_11);
        led_MR6000_2->setObjectName(QString::fromUtf8("led_MR6000_2"));

        gridLayout->addWidget(led_MR6000_2, 1, 1, 1, 1);

        line = new QFrame(groupBox_11);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 2, 0, 1, 4);


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
        verticalLayout_11 = new QVBoxLayout(groupBox_12);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        comboBox_selectWaweMode_2 = new QComboBox(groupBox_12);
        comboBox_selectWaweMode_2->addItem(QString());
        comboBox_selectWaweMode_2->addItem(QString());
        comboBox_selectWaweMode_2->setObjectName(QString::fromUtf8("comboBox_selectWaweMode_2"));

        verticalLayout_11->addWidget(comboBox_selectWaweMode_2);

        stackedWidget_2 = new QStackedWidget(groupBox_12);
        stackedWidget_2->setObjectName(QString::fromUtf8("stackedWidget_2"));
        sizePolicy.setHeightForWidth(stackedWidget_2->sizePolicy().hasHeightForWidth());
        stackedWidget_2->setSizePolicy(sizePolicy);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        layoutWidget = new QWidget(page_3);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(8, 1, 231, 241));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_14->addWidget(label_6);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_5);

        editSweepFreqStart = new QLineEdit(layoutWidget);
        editSweepFreqStart->setObjectName(QString::fromUtf8("editSweepFreqStart"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(editSweepFreqStart->sizePolicy().hasHeightForWidth());
        editSweepFreqStart->setSizePolicy(sizePolicy1);

        horizontalLayout_14->addWidget(editSweepFreqStart);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_4);

        editSweepFreqEnd = new QLineEdit(layoutWidget);
        editSweepFreqEnd->setObjectName(QString::fromUtf8("editSweepFreqEnd"));
        sizePolicy1.setHeightForWidth(editSweepFreqEnd->sizePolicy().hasHeightForWidth());
        editSweepFreqEnd->setSizePolicy(sizePolicy1);

        horizontalLayout_14->addWidget(editSweepFreqEnd);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_14->addWidget(label_10);


        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        labelAmp = new QLabel(layoutWidget);
        labelAmp->setObjectName(QString::fromUtf8("labelAmp"));

        horizontalLayout_15->addWidget(labelAmp);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_9);

        spinSweepAmp = new QDoubleSpinBox(layoutWidget);
        spinSweepAmp->setObjectName(QString::fromUtf8("spinSweepAmp"));
        spinSweepAmp->setValue(1.000000000000000);

        horizontalLayout_15->addWidget(spinSweepAmp);

        labelAmpUnit = new QLabel(layoutWidget);
        labelAmpUnit->setObjectName(QString::fromUtf8("labelAmpUnit"));

        horizontalLayout_15->addWidget(labelAmpUnit);


        verticalLayout->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        labelSweepTime = new QLabel(layoutWidget);
        labelSweepTime->setObjectName(QString::fromUtf8("labelSweepTime"));

        horizontalLayout_16->addWidget(labelSweepTime);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_11);

        spinSweepTime = new QDoubleSpinBox(layoutWidget);
        spinSweepTime->setObjectName(QString::fromUtf8("spinSweepTime"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(spinSweepTime->sizePolicy().hasHeightForWidth());
        spinSweepTime->setSizePolicy(sizePolicy2);
        spinSweepTime->setValue(1.000000000000000);

        horizontalLayout_16->addWidget(spinSweepTime);


        verticalLayout->addLayout(horizontalLayout_16);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        labelSweepCount = new QLabel(layoutWidget);
        labelSweepCount->setObjectName(QString::fromUtf8("labelSweepCount"));

        horizontalLayout_23->addWidget(labelSweepCount);

        horizontalSpacer_10 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_10);

        spinSweepCount = new QSpinBox(layoutWidget);
        spinSweepCount->setObjectName(QString::fromUtf8("spinSweepCount"));
        sizePolicy2.setHeightForWidth(spinSweepCount->sizePolicy().hasHeightForWidth());
        spinSweepCount->setSizePolicy(sizePolicy2);
        spinSweepCount->setMinimumSize(QSize(20, 0));
        spinSweepCount->setValue(10);

        horizontalLayout_23->addWidget(spinSweepCount);


        verticalLayout->addLayout(horizontalLayout_23);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        btnAdvanced = new QPushButton(layoutWidget);
        btnAdvanced->setObjectName(QString::fromUtf8("btnAdvanced"));

        horizontalLayout_17->addWidget(btnAdvanced);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_3);

        btnSweepConfig = new QPushButton(layoutWidget);
        btnSweepConfig->setObjectName(QString::fromUtf8("btnSweepConfig"));

        horizontalLayout_17->addWidget(btnSweepConfig);


        verticalLayout->addLayout(horizontalLayout_17);

        stackedWidget_2->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        gridLayout_5 = new QGridLayout(page_4);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));

        verticalLayout_7->addLayout(horizontalLayout_21);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_3);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        labelWaveFile = new QLabel(page_4);
        labelWaveFile->setObjectName(QString::fromUtf8("labelWaveFile"));

        horizontalLayout_18->addWidget(labelWaveFile);

        lineFileName = new QLineEdit(page_4);
        lineFileName->setObjectName(QString::fromUtf8("lineFileName"));
        sizePolicy.setHeightForWidth(lineFileName->sizePolicy().hasHeightForWidth());
        lineFileName->setSizePolicy(sizePolicy);
        lineFileName->setReadOnly(true);

        horizontalLayout_18->addWidget(lineFileName);

        btnSelectArb = new QPushButton(page_4);
        btnSelectArb->setObjectName(QString::fromUtf8("btnSelectArb"));
        sizePolicy.setHeightForWidth(btnSelectArb->sizePolicy().hasHeightForWidth());
        btnSelectArb->setSizePolicy(sizePolicy);

        horizontalLayout_18->addWidget(btnSelectArb);


        verticalLayout_7->addLayout(horizontalLayout_18);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_2);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        labelArbSampleRate = new QLabel(page_4);
        labelArbSampleRate->setObjectName(QString::fromUtf8("labelArbSampleRate"));

        horizontalLayout_19->addWidget(labelArbSampleRate);

        spinArbSampleRate = new QDoubleSpinBox(page_4);
        spinArbSampleRate->setObjectName(QString::fromUtf8("spinArbSampleRate"));
        sizePolicy.setHeightForWidth(spinArbSampleRate->sizePolicy().hasHeightForWidth());
        spinArbSampleRate->setSizePolicy(sizePolicy);
        spinArbSampleRate->setDecimals(0);

        horizontalLayout_19->addWidget(spinArbSampleRate);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_7);


        verticalLayout_7->addLayout(horizontalLayout_19);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        labelArbAmp = new QLabel(page_4);
        labelArbAmp->setObjectName(QString::fromUtf8("labelArbAmp"));

        horizontalLayout_20->addWidget(labelArbAmp);

        spinArbAmp = new QDoubleSpinBox(page_4);
        spinArbAmp->setObjectName(QString::fromUtf8("spinArbAmp"));
        sizePolicy.setHeightForWidth(spinArbAmp->sizePolicy().hasHeightForWidth());
        spinArbAmp->setSizePolicy(sizePolicy);

        horizontalLayout_20->addWidget(spinArbAmp);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_8);


        verticalLayout_7->addLayout(horizontalLayout_20);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_6);

        btnArbConfig = new QPushButton(page_4);
        btnArbConfig->setObjectName(QString::fromUtf8("btnArbConfig"));

        horizontalLayout_22->addWidget(btnArbConfig);


        verticalLayout_7->addLayout(horizontalLayout_22);


        gridLayout_5->addLayout(verticalLayout_7, 0, 0, 1, 1);

        stackedWidget_2->addWidget(page_4);

        verticalLayout_11->addWidget(stackedWidget_2);


        horizontalLayout_3->addWidget(groupBox_12);

        groupBox_13 = new QGroupBox(groupBox_2);
        groupBox_13->setObjectName(QString::fromUtf8("groupBox_13"));
        sizePolicy.setHeightForWidth(groupBox_13->sizePolicy().hasHeightForWidth());
        groupBox_13->setSizePolicy(sizePolicy);
        groupBox_13->setMinimumSize(QSize(0, 50));
        gridLayout_4 = new QGridLayout(groupBox_13);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_32 = new QLabel(groupBox_13);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        horizontalLayout_8->addWidget(label_32);

        comboBox_9 = new QComboBox(groupBox_13);
        comboBox_9->addItem(QString());
        comboBox_9->addItem(QString());
        comboBox_9->setObjectName(QString::fromUtf8("comboBox_9"));

        horizontalLayout_8->addWidget(comboBox_9);


        verticalLayout_9->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_33 = new QLabel(groupBox_13);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        horizontalLayout_9->addWidget(label_33);

        comboBox_10 = new QComboBox(groupBox_13);
        comboBox_10->addItem(QString());
        comboBox_10->addItem(QString());
        comboBox_10->setObjectName(QString::fromUtf8("comboBox_10"));

        horizontalLayout_9->addWidget(comboBox_10);


        verticalLayout_9->addLayout(horizontalLayout_9);

        label_34 = new QLabel(groupBox_13);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        verticalLayout_9->addWidget(label_34);


        gridLayout_4->addLayout(verticalLayout_9, 0, 0, 1, 1);


        horizontalLayout_3->addWidget(groupBox_13);

        groupBox_14 = new QGroupBox(groupBox_2);
        groupBox_14->setObjectName(QString::fromUtf8("groupBox_14"));
        sizePolicy.setHeightForWidth(groupBox_14->sizePolicy().hasHeightForWidth());
        groupBox_14->setSizePolicy(sizePolicy);
        groupBox_14->setMinimumSize(QSize(0, 50));
        gridLayout_2 = new QGridLayout(groupBox_14);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_35 = new QLabel(groupBox_14);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        horizontalLayout_10->addWidget(label_35);

        comboBox_11 = new QComboBox(groupBox_14);
        comboBox_11->addItem(QString());
        comboBox_11->addItem(QString());
        comboBox_11->setObjectName(QString::fromUtf8("comboBox_11"));

        horizontalLayout_10->addWidget(comboBox_11);


        verticalLayout_10->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_36 = new QLabel(groupBox_14);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        horizontalLayout_11->addWidget(label_36);

        comboBox_12 = new QComboBox(groupBox_14);
        comboBox_12->addItem(QString());
        comboBox_12->addItem(QString());
        comboBox_12->addItem(QString());
        comboBox_12->addItem(QString());
        comboBox_12->addItem(QString());
        comboBox_12->addItem(QString());
        comboBox_12->setObjectName(QString::fromUtf8("comboBox_12"));

        horizontalLayout_11->addWidget(comboBox_12);


        verticalLayout_10->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_37 = new QLabel(groupBox_14);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        horizontalLayout_12->addWidget(label_37);

        comboBox_13 = new QComboBox(groupBox_14);
        comboBox_13->addItem(QString());
        comboBox_13->addItem(QString());
        comboBox_13->addItem(QString());
        comboBox_13->addItem(QString());
        comboBox_13->addItem(QString());
        comboBox_13->addItem(QString());
        comboBox_13->setObjectName(QString::fromUtf8("comboBox_13"));

        horizontalLayout_12->addWidget(comboBox_13);


        verticalLayout_10->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_38 = new QLabel(groupBox_14);
        label_38->setObjectName(QString::fromUtf8("label_38"));

        horizontalLayout_13->addWidget(label_38);

        comboBox_14 = new QComboBox(groupBox_14);
        comboBox_14->addItem(QString());
        comboBox_14->addItem(QString());
        comboBox_14->addItem(QString());
        comboBox_14->addItem(QString());
        comboBox_14->addItem(QString());
        comboBox_14->addItem(QString());
        comboBox_14->setObjectName(QString::fromUtf8("comboBox_14"));

        horizontalLayout_13->addWidget(comboBox_14);


        verticalLayout_10->addLayout(horizontalLayout_13);

        btnOutput = new QPushButton(groupBox_14);
        btnOutput->setObjectName(QString::fromUtf8("btnOutput"));

        verticalLayout_10->addWidget(btnOutput);


        gridLayout_2->addLayout(verticalLayout_10, 0, 0, 1, 1);


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
        verticalLayout_5->setStretch(2, 1);

        verticalLayout_6->addLayout(verticalLayout_5);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 18));
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
        label_26->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\351\207\207\351\233\206\344\273\252VISA\345\234\260\345\235\200\357\274\232", nullptr));
        lineEditMRAddress->setText(QCoreApplication::translate("MainWindow", "TCPIP0::169.254.96.21::INSTR", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "\350\241\214\350\275\246IP\345\234\260\345\235\200\357\274\232", nullptr));
        lineEditHangCheAddress->setText(QCoreApplication::translate("MainWindow", "TCPIP0::169.254.96.21::INSTR", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "\346\273\244\346\224\276\344\270\262\345\217\243\357\274\232", nullptr));
        lineEditFilterAmpAddress->setText(QCoreApplication::translate("MainWindow", "COM11", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        lineEditFilterAmpPort->setText(QCoreApplication::translate("MainWindow", "9600", nullptr));
        btnSelfTest->setText(QCoreApplication::translate("MainWindow", "\350\207\252\346\243\200", nullptr));
        led_gen_2->setText(QString());
        led_car_2->setText(QString());
        led_MR6000_2->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\344\273\252\345\231\250\351\205\215\347\275\256", nullptr));
        groupBox_12->setTitle(QCoreApplication::translate("MainWindow", "\344\277\241\345\217\267\346\272\220", nullptr));
        comboBox_selectWaweMode_2->setItemText(0, QCoreApplication::translate("MainWindow", "\346\211\253\351\242\221/\345\215\225\351\242\221\344\277\241\345\217\267", nullptr));
        comboBox_selectWaweMode_2->setItemText(1, QCoreApplication::translate("MainWindow", "\350\207\252\345\256\232\344\271\211\344\277\241\345\217\267", nullptr));

        label_6->setText(QCoreApplication::translate("MainWindow", "\346\211\253\351\242\221\350\214\203\345\233\264\357\274\232", nullptr));
        editSweepFreqStart->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        editSweepFreqEnd->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\357\274\210kHz\357\274\211", nullptr));
        labelAmp->setText(QCoreApplication::translate("MainWindow", "\345\271\205  \345\272\246\357\274\232", nullptr));
        labelAmpUnit->setText(QCoreApplication::translate("MainWindow", "\357\274\210Vpp\357\274\211", nullptr));
        labelSweepTime->setText(QCoreApplication::translate("MainWindow", "\346\211\253\351\242\221\346\227\266\351\227\264\357\274\232", nullptr));
        labelSweepCount->setText(QCoreApplication::translate("MainWindow", "\346\255\245\350\277\233\346\225\260\357\274\232", nullptr));
        btnAdvanced->setText(QCoreApplication::translate("MainWindow", "\351\253\230\347\272\247\350\256\276\347\275\256", nullptr));
        btnSweepConfig->setText(QCoreApplication::translate("MainWindow", "\351\205\215\347\275\256", nullptr));
        labelWaveFile->setText(QCoreApplication::translate("MainWindow", "\346\263\242\345\275\242\346\226\207\344\273\266\357\274\232", nullptr));
        lineFileName->setText(QCoreApplication::translate("MainWindow", "\346\234\252\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        btnSelectArb->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        labelArbSampleRate->setText(QCoreApplication::translate("MainWindow", "\351\207\207\346\240\267\347\216\207\357\274\210kHz\357\274\211", nullptr));
        labelArbAmp->setText(QCoreApplication::translate("MainWindow", "\345\271\205 \345\272\246\357\274\210V\357\274\211", nullptr));
        btnArbConfig->setText(QCoreApplication::translate("MainWindow", "\351\205\215\347\275\256", nullptr));
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
