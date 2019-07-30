/****************************************************************************
** Meta object code from reading C++ file 'qtgui_test.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qtgui_test.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtgui_test.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QTGUI_Test_t {
    QByteArrayData data[14];
    char stringdata0[207];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QTGUI_Test_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QTGUI_Test_t qt_meta_stringdata_QTGUI_Test = {
    {
QT_MOC_LITERAL(0, 0, 10), // "QTGUI_Test"
QT_MOC_LITERAL(1, 11, 13), // "onDataChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 1), // "a"
QT_MOC_LITERAL(4, 28, 1), // "b"
QT_MOC_LITERAL(5, 30, 19), // "onCameraTypeChanged"
QT_MOC_LITERAL(6, 50, 5), // "is208"
QT_MOC_LITERAL(7, 56, 20), // "onCameraInfoReceived"
QT_MOC_LITERAL(8, 77, 23), // "on_start_button_clicked"
QT_MOC_LITERAL(9, 101, 37), // "on_start_receive_image_button..."
QT_MOC_LITERAL(10, 139, 22), // "on_stop_button_clicked"
QT_MOC_LITERAL(11, 162, 8), // "updateUi"
QT_MOC_LITERAL(12, 171, 16), // "updateCameraType"
QT_MOC_LITERAL(13, 188, 18) // "startImageInfoPipe"

    },
    "QTGUI_Test\0onDataChanged\0\0a\0b\0"
    "onCameraTypeChanged\0is208\0"
    "onCameraInfoReceived\0on_start_button_clicked\0"
    "on_start_receive_image_button_clicked\0"
    "on_stop_button_clicked\0updateUi\0"
    "updateCameraType\0startImageInfoPipe"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTGUI_Test[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       5,    1,   64,    2, 0x06 /* Public */,
       7,    0,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   68,    2, 0x08 /* Private */,
       9,    0,   69,    2, 0x08 /* Private */,
      10,    0,   70,    2, 0x08 /* Private */,
      11,    2,   71,    2, 0x08 /* Private */,
      12,    1,   76,    2, 0x08 /* Private */,
      13,    0,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,

       0        // eod
};

void QTGUI_Test::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTGUI_Test *_t = static_cast<QTGUI_Test *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onDataChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->onCameraTypeChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->onCameraInfoReceived(); break;
        case 3: _t->on_start_button_clicked(); break;
        case 4: _t->on_start_receive_image_button_clicked(); break;
        case 5: _t->on_stop_button_clicked(); break;
        case 6: _t->updateUi((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->updateCameraType((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->startImageInfoPipe(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QTGUI_Test::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QTGUI_Test::onDataChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QTGUI_Test::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QTGUI_Test::onCameraTypeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QTGUI_Test::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QTGUI_Test::onCameraInfoReceived)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QTGUI_Test::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QTGUI_Test.data,
      qt_meta_data_QTGUI_Test,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QTGUI_Test::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTGUI_Test::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QTGUI_Test.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int QTGUI_Test::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void QTGUI_Test::onDataChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QTGUI_Test::onCameraTypeChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QTGUI_Test::onCameraInfoReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
