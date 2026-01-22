QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    rigoldriver.cpp

HEADERS += \
    mainwindow.h \
    rigoldriver.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# =============================================================
# NI-VISA 库配置 (必选)
# =============================================================

# 1. 包含头文件的路径 (这里存放着 visa.h)
# 通常在 C:\Program Files\IVI Foundation\VISA\Win64\Include
# 或者 C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Include

# //更换电脑需要修改路径
INCLUDEPATH += "C:/Program Files/IVI Foundation/VISA/Win64/Include"

# 2. 链接库文件 (这里存放着 visa32.lib / visa64.lib)
# 注意：即使是 64位系统，核心库名称通常也叫 -lvisa32，或者是 -lvisa64
# 请去您的 C盘 对应的目录下确认一下 lib 文件名

# //更换电脑需要修改路径
LIBS += -L"C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc" -lvisa64

# 如果编译报错找不到库，请尝试换成 32位的路径：
# LIBS += -L"C:/Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc" -lvisa32
