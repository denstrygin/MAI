/****************************************************************************
** Meta object code from reading C++ file 'splinewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../lab7/splinewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'splinewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SplineWidget_t {
    QByteArrayData data[8];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SplineWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SplineWidget_t qt_meta_stringdata_SplineWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SplineWidget"
QT_MOC_LITERAL(1, 13, 7), // "rePaint"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 1), // "p"
QT_MOC_LITERAL(4, 24, 22), // "rePaintSubLineSettings"
QT_MOC_LITERAL(5, 47, 5), // "state"
QT_MOC_LITERAL(6, 53, 24), // "rePaintAndSetSplineWidth"
QT_MOC_LITERAL(7, 78, 5) // "width"

    },
    "SplineWidget\0rePaint\0\0p\0rePaintSubLineSettings\0"
    "state\0rePaintAndSetSplineWidth\0width"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SplineWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       1,    1,   35,    2, 0x0a /* Public */,
       4,    1,   38,    2, 0x0a /* Public */,
       6,    1,   41,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void SplineWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SplineWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rePaint(); break;
        case 1: _t->rePaint((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->rePaintSubLineSettings((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->rePaintAndSetSplineWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SplineWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SplineWidget.data,
    qt_meta_data_SplineWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SplineWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SplineWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SplineWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SplineWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
