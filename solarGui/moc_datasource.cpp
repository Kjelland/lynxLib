/****************************************************************************
** Meta object code from reading C++ file 'datasource.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../datasource.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datasource.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_uiStruct_t {
    QByteArrayData data[6];
    char stringdata0[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_uiStruct_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_uiStruct_t qt_meta_stringdata_uiStruct = {
    {
QT_MOC_LITERAL(0, 0, 8), // "uiStruct"
QT_MOC_LITERAL(1, 9, 10), // "motorSpeed"
QT_MOC_LITERAL(2, 20, 11), // "motorTorque"
QT_MOC_LITERAL(3, 32, 14), // "batteryVoltage"
QT_MOC_LITERAL(4, 47, 7), // "number4"
QT_MOC_LITERAL(5, 55, 7) // "message"

    },
    "uiStruct\0motorSpeed\0motorTorque\0"
    "batteryVoltage\0number4\0message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_uiStruct[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       5,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::Int, 0x00095401,
       2, QMetaType::Int, 0x00095401,
       3, QMetaType::Int, 0x00095401,
       4, QMetaType::Int, 0x00095401,
       5, QMetaType::QString, 0x00095003,

       0        // eod
};

void uiStruct::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<uiStruct *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->m_motorSpeed; break;
        case 1: *reinterpret_cast< int*>(_v) = _t->m_motorTorque; break;
        case 2: *reinterpret_cast< int*>(_v) = _t->m_batteryVoltage; break;
        case 3: *reinterpret_cast< int*>(_v) = _t->m_number4; break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->m_message; break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<uiStruct *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 4:
            if (_t->m_message != *reinterpret_cast< QString*>(_v)) {
                _t->m_message = *reinterpret_cast< QString*>(_v);
            }
            break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject uiStruct::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_uiStruct.data,
    qt_meta_data_uiStruct,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *uiStruct::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *uiStruct::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_uiStruct.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int uiStruct::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
struct qt_meta_stringdata_DataSource_t {
    QByteArrayData data[25];
    char stringdata0[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataSource_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataSource_t qt_meta_stringdata_DataSource = {
    {
QT_MOC_LITERAL(0, 0, 10), // "DataSource"
QT_MOC_LITERAL(1, 11, 11), // "lynxUpdated"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 11), // "nameChanged"
QT_MOC_LITERAL(4, 36, 12), // "colorChanged"
QT_MOC_LITERAL(5, 49, 8), // "setCards"
QT_MOC_LITERAL(6, 58, 12), // "generateData"
QT_MOC_LITERAL(7, 71, 4), // "type"
QT_MOC_LITERAL(8, 76, 8), // "rowCount"
QT_MOC_LITERAL(9, 85, 8), // "colCount"
QT_MOC_LITERAL(10, 94, 6), // "update"
QT_MOC_LITERAL(11, 101, 16), // "QAbstractSeries*"
QT_MOC_LITERAL(12, 118, 6), // "series"
QT_MOC_LITERAL(13, 125, 7), // "runUart"
QT_MOC_LITERAL(14, 133, 12), // "readyReadUDP"
QT_MOC_LITERAL(15, 146, 9), // "timerTick"
QT_MOC_LITERAL(16, 156, 12), // "getStructure"
QT_MOC_LITERAL(17, 169, 6), // "pvVolt"
QT_MOC_LITERAL(18, 176, 9), // "pvCurrent"
QT_MOC_LITERAL(19, 186, 8), // "battVolt"
QT_MOC_LITERAL(20, 195, 11), // "battCurrent"
QT_MOC_LITERAL(21, 207, 4), // "name"
QT_MOC_LITERAL(22, 212, 5), // "color"
QT_MOC_LITERAL(23, 218, 5), // "cards"
QT_MOC_LITERAL(24, 224, 10) // "QList<int>"

    },
    "DataSource\0lynxUpdated\0\0nameChanged\0"
    "colorChanged\0setCards\0generateData\0"
    "type\0rowCount\0colCount\0update\0"
    "QAbstractSeries*\0series\0runUart\0"
    "readyReadUDP\0timerTick\0getStructure\0"
    "pvVolt\0pvCurrent\0battVolt\0battCurrent\0"
    "name\0color\0cards\0QList<int>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataSource[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       7,   82, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    0,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    3,   68,    2, 0x0a /* Public */,
      10,    1,   75,    2, 0x0a /* Public */,
      13,    0,   78,    2, 0x08 /* Private */,
      14,    0,   79,    2, 0x08 /* Private */,
      15,    0,   80,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      16,    0,   81,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::QObjectStar,

 // properties: name, type, flags
      17, QMetaType::Double, 0x00495001,
      18, QMetaType::Double, 0x00495001,
      19, QMetaType::Double, 0x00495001,
      20, QMetaType::Double, 0x00495001,
      21, QMetaType::QString, 0x00495103,
      22, QMetaType::QString, 0x00495103,
      23, 0x80000000 | 24, 0x0009510b,

 // properties: notify_signal_id
       0,
       0,
       0,
       0,
       1,
       2,
       0,

       0        // eod
};

void DataSource::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataSource *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->lynxUpdated(); break;
        case 1: _t->nameChanged(); break;
        case 2: _t->colorChanged(); break;
        case 3: _t->setCards(); break;
        case 4: _t->generateData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->update((*reinterpret_cast< QAbstractSeries*(*)>(_a[1]))); break;
        case 6: _t->runUart(); break;
        case 7: _t->readyReadUDP(); break;
        case 8: _t->timerTick(); break;
        case 9: { QObject* _r = _t->getStructure();
            if (_a[0]) *reinterpret_cast< QObject**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSeries* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DataSource::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataSource::lynxUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DataSource::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataSource::nameChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DataSource::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataSource::colorChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DataSource::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataSource::setCards)) {
                *result = 3;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<DataSource *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->pvVolt(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->pvCurrent(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->battVolt(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->battCurrent(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->name(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->color(); break;
        case 6: *reinterpret_cast< QList<int>*>(_v) = _t->cards(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<DataSource *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 4: _t->setName(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setColor(*reinterpret_cast< QString*>(_v)); break;
        case 6: _t->setCards(*reinterpret_cast< QList<int>*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject DataSource::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_DataSource.data,
    qt_meta_data_DataSource,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DataSource::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataSource::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataSource.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DataSource::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void DataSource::lynxUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DataSource::nameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DataSource::colorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DataSource::setCards()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
