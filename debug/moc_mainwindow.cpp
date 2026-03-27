/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[40];
    char stringdata0[327];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 17), // "on_logContextMenu"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 3), // "pos"
QT_MOC_LITERAL(34, 22), // "on_btnSelfTest_clicked"
QT_MOC_LITERAL(57, 25), // "on_btnSweepConfig_clicked"
QT_MOC_LITERAL(83, 23), // "on_btnArbConfig_clicked"
QT_MOC_LITERAL(107, 23), // "on_btnSelectArb_clicked"
QT_MOC_LITERAL(131, 10), // "switchPage"
QT_MOC_LITERAL(142, 8), // "QWidget*"
QT_MOC_LITERAL(151, 4), // "page"
QT_MOC_LITERAL(156, 29), // "on_btnBodeVisaConnect_clicked"
QT_MOC_LITERAL(186, 22), // "on_btnOpenCali_clicked"
QT_MOC_LITERAL(209, 23), // "on_btnShortCali_clicked"
QT_MOC_LITERAL(233, 9), // "appendLog"
QT_MOC_LITERAL(243, 3), // "msg"
QT_MOC_LITERAL(247, 5), // "level"
QT_MOC_LITERAL(253, 22), // "on_btnLoadCali_clicked"
QT_MOC_LITERAL(276, 30), // "on_btnStartMeasurement_clicked"
QT_MOC_LITERAL(307, 19) // "initMenuConnections"

    },
    "MainWindow\0on_logContextMenu\0\0pos\0"
    "on_btnSelfTest_clicked\0on_btnSweepConfig_clicked\0"
    "on_btnArbConfig_clicked\0on_btnSelectArb_clicked\0"
    "switchPage\0QWidget*\0page\0"
    "on_btnBodeVisaConnect_clicked\0"
    "on_btnOpenCali_clicked\0on_btnShortCali_clicked\0"
    "appendLog\0msg\0level\0on_btnLoadCali_clicked\0"
    "on_btnStartMeasurement_clicked\0"
    "initMenuConnections"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   92,    2, 0x08,    1 /* Private */,
       4,    0,   95,    2, 0x08,    3 /* Private */,
       5,    0,   96,    2, 0x08,    4 /* Private */,
       6,    0,   97,    2, 0x08,    5 /* Private */,
       7,    0,   98,    2, 0x08,    6 /* Private */,
       8,    1,   99,    2, 0x08,    7 /* Private */,
      11,    0,  102,    2, 0x08,    9 /* Private */,
      12,    0,  103,    2, 0x08,   10 /* Private */,
      13,    0,  104,    2, 0x08,   11 /* Private */,
      14,    2,  105,    2, 0x08,   12 /* Private */,
      17,    0,  110,    2, 0x08,   15 /* Private */,
      18,    0,  111,    2, 0x08,   16 /* Private */,
      19,    0,  112,    2, 0x08,   17 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   15,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_logContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->on_btnSelfTest_clicked(); break;
        case 2: _t->on_btnSweepConfig_clicked(); break;
        case 3: _t->on_btnArbConfig_clicked(); break;
        case 4: _t->on_btnSelectArb_clicked(); break;
        case 5: _t->switchPage((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 6: _t->on_btnBodeVisaConnect_clicked(); break;
        case 7: _t->on_btnOpenCali_clicked(); break;
        case 8: _t->on_btnShortCali_clicked(); break;
        case 9: _t->appendLog((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->on_btnLoadCali_clicked(); break;
        case 11: _t->on_btnStartMeasurement_clicked(); break;
        case 12: _t->initMenuConnections(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
