/****************************************************************************
** Meta object code from reading C++ file 'admin_searchbook.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../admin_searchbook.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'admin_searchbook.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_admin_searchbook_t {
    QByteArrayData data[8];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_admin_searchbook_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_admin_searchbook_t qt_meta_stringdata_admin_searchbook = {
    {
QT_MOC_LITERAL(0, 0, 16), // "admin_searchbook"
QT_MOC_LITERAL(1, 17, 12), // "OnBtnClicked"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 2), // "id"
QT_MOC_LITERAL(4, 34, 18), // "OnBtnClickedDelete"
QT_MOC_LITERAL(5, 53, 12), // "radioBtnSlot"
QT_MOC_LITERAL(6, 66, 17), // "radioBtnSlotOther"
QT_MOC_LITERAL(7, 84, 8) // "UpdateUI"

    },
    "admin_searchbook\0OnBtnClicked\0\0id\0"
    "OnBtnClickedDelete\0radioBtnSlot\0"
    "radioBtnSlotOther\0UpdateUI"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_admin_searchbook[] = {

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
       1,    1,   39,    2, 0x0a /* Public */,
       4,    1,   42,    2, 0x0a /* Public */,
       5,    0,   45,    2, 0x0a /* Public */,
       6,    0,   46,    2, 0x0a /* Public */,
       7,    1,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void admin_searchbook::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        admin_searchbook *_t = static_cast<admin_searchbook *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->OnBtnClickedDelete((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->radioBtnSlot(); break;
        case 3: _t->radioBtnSlotOther(); break;
        case 4: _t->UpdateUI((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject admin_searchbook::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_admin_searchbook.data,
      qt_meta_data_admin_searchbook,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *admin_searchbook::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *admin_searchbook::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_admin_searchbook.stringdata0))
        return static_cast<void*>(const_cast< admin_searchbook*>(this));
    return QWidget::qt_metacast(_clname);
}

int admin_searchbook::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
