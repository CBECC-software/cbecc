/****************************************************************************
** Meta object code from reading C++ file 'IdfObject_Impl.hxx'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "IdfObject_Impl.hxx"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IdfObject_Impl.hxx' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_openstudio__detail__IdfObject_Impl_t {
    QByteArrayData data[5];
    char stringdata[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_openstudio__detail__IdfObject_Impl_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_openstudio__detail__IdfObject_Impl_t qt_meta_stringdata_openstudio__detail__IdfObject_Impl = {
    {
QT_MOC_LITERAL(0, 0, 34),
QT_MOC_LITERAL(1, 35, 8),
QT_MOC_LITERAL(2, 44, 0),
QT_MOC_LITERAL(3, 45, 12),
QT_MOC_LITERAL(4, 58, 12)
    },
    "openstudio::detail::IdfObject_Impl\0"
    "onChange\0\0onNameChange\0onDataChange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_openstudio__detail__IdfObject_Impl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,
       4,    0,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void openstudio::detail::IdfObject_Impl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IdfObject_Impl *_t = static_cast<IdfObject_Impl *>(_o);
        switch (_id) {
        case 0: _t->onChange(); break;
        case 1: _t->onNameChange(); break;
        case 2: _t->onDataChange(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (IdfObject_Impl::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&IdfObject_Impl::onChange)) {
                *result = 0;
            }
        }
        {
            typedef void (IdfObject_Impl::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&IdfObject_Impl::onNameChange)) {
                *result = 1;
            }
        }
        {
            typedef void (IdfObject_Impl::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&IdfObject_Impl::onDataChange)) {
                *result = 2;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject openstudio::detail::IdfObject_Impl::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_openstudio__detail__IdfObject_Impl.data,
      qt_meta_data_openstudio__detail__IdfObject_Impl,  qt_static_metacall, 0, 0}
};


const QMetaObject *openstudio::detail::IdfObject_Impl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *openstudio::detail::IdfObject_Impl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_openstudio__detail__IdfObject_Impl.stringdata))
        return static_cast<void*>(const_cast< IdfObject_Impl*>(this));
    if (!strcmp(_clname, "std::enable_shared_from_this<IdfObject_Impl>"))
        return static_cast< std::enable_shared_from_this<IdfObject_Impl>*>(const_cast< IdfObject_Impl*>(this));
    return QObject::qt_metacast(_clname);
}

int openstudio::detail::IdfObject_Impl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void openstudio::detail::IdfObject_Impl::onChange()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void openstudio::detail::IdfObject_Impl::onNameChange()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void openstudio::detail::IdfObject_Impl::onDataChange()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
