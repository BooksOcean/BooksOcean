/****************************************************************************
** Meta object code from reading C++ file 'student_index.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../student_index.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'student_index.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_student_index_t {
    QByteArrayData data[8];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_student_index_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_student_index_t qt_meta_stringdata_student_index = {
    {
QT_MOC_LITERAL(0, 0, 13), // "student_index"
QT_MOC_LITERAL(1, 14, 11), // "ClickButton"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "OnBtnClicked"
QT_MOC_LITERAL(4, 40, 2), // "id"
QT_MOC_LITERAL(5, 43, 21), // "OnBtnRecommendClicked"
QT_MOC_LITERAL(6, 65, 18), // "OnBtnClickedCancel"
QT_MOC_LITERAL(7, 84, 10) // "UpdateSlot"

    },
    "student_index\0ClickButton\0\0OnBtnClicked\0"
    "id\0OnBtnRecommendClicked\0OnBtnClickedCancel\0"
    "UpdateSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_student_index[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    1,   40,    2, 0x0a /* Public */,
       5,    1,   43,    2, 0x0a /* Public */,
       6,    1,   46,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,

       0        // eod
};

void student_index::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        student_index *_t = static_cast<student_index *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ClickButton(); break;
        case 1: _t->OnBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->OnBtnRecommendClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->OnBtnClickedCancel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->UpdateSlot(); break;
        default: ;
        }
    }
}

const QMetaObject student_index::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_student_index.data,
      qt_meta_data_student_index,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *student_index::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *student_index::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_student_index.stringdata0))
        return static_cast<void*>(const_cast< student_index*>(this));
    return QWidget::qt_metacast(_clname);
}

int student_index::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE