/****************************************************************************
** Meta object code from reading C++ file 'backend.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../backend.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StructInfo_t {
    QByteArrayData data[10];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StructInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StructInfo_t qt_meta_stringdata_StructInfo = {
    {
QT_MOC_LITERAL(0, 0, 10), // "StructInfo"
QT_MOC_LITERAL(1, 11, 13), // "setStructName"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 4), // "text"
QT_MOC_LITERAL(4, 31, 5), // "valid"
QT_MOC_LITERAL(5, 37, 11), // "setStructId"
QT_MOC_LITERAL(6, 49, 15), // "addStructMember"
QT_MOC_LITERAL(7, 65, 4), // "type"
QT_MOC_LITERAL(8, 70, 6), // "type_t"
QT_MOC_LITERAL(9, 77, 5) // "clear"

    },
    "StructInfo\0setStructName\0\0text\0valid\0"
    "setStructId\0addStructMember\0type\0"
    "type_t\0clear"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StructInfo[] = {

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
       1,    2,   34,    2, 0x0a /* Public */,
       5,    2,   39,    2, 0x0a /* Public */,
       6,    4,   44,    2, 0x0a /* Public */,
       9,    0,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    3,    7,    8,    4,
    QMetaType::Void,

       0        // eod
};

void StructInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StructInfo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setStructName((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->setStructId((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->addStructMember((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 3: _t->clear(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject StructInfo::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_StructInfo.data,
    qt_meta_data_StructInfo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StructInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StructInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StructInfo.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int StructInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_TextHandler_t {
    QByteArrayData data[17];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TextHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TextHandler_t qt_meta_stringdata_TextHandler = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TextHandler"
QT_MOC_LITERAL(1, 12, 11), // "textChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "colorChanged"
QT_MOC_LITERAL(4, 38, 17), // "indexColorChanged"
QT_MOC_LITERAL(5, 56, 12), // "validChanged"
QT_MOC_LITERAL(6, 69, 7), // "setText"
QT_MOC_LITERAL(7, 77, 5), // "input"
QT_MOC_LITERAL(8, 83, 17), // "setValidCondition"
QT_MOC_LITERAL(9, 101, 14), // "ValidCondition"
QT_MOC_LITERAL(10, 116, 9), // "condition"
QT_MOC_LITERAL(11, 126, 4), // "text"
QT_MOC_LITERAL(12, 131, 5), // "color"
QT_MOC_LITERAL(13, 137, 10), // "indexColor"
QT_MOC_LITERAL(14, 148, 5), // "valid"
QT_MOC_LITERAL(15, 154, 6), // "E_Name"
QT_MOC_LITERAL(16, 161, 8) // "E_Number"

    },
    "TextHandler\0textChanged\0\0colorChanged\0"
    "indexColorChanged\0validChanged\0setText\0"
    "input\0setValidCondition\0ValidCondition\0"
    "condition\0text\0color\0indexColor\0valid\0"
    "E_Name\0E_Number"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TextHandler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       4,   54, // properties
       1,   70, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,
       5,    0,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   48,    2, 0x0a /* Public */,
       8,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

 // properties: name, type, flags
      11, QMetaType::QString, 0x00495103,
      12, QMetaType::QString, 0x00495003,
      13, QMetaType::QString, 0x00495003,
      14, QMetaType::Bool, 0x00495001,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

 // enums: name, alias, flags, count, data
       9,    9, 0x0,    2,   75,

 // enum data: key, value
      15, uint(TextHandler::E_Name),
      16, uint(TextHandler::E_Number),

       0        // eod
};

void TextHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TextHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->textChanged(); break;
        case 1: _t->colorChanged(); break;
        case 2: _t->indexColorChanged(); break;
        case 3: _t->validChanged(); break;
        case 4: _t->setText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->setValidCondition((*reinterpret_cast< ValidCondition(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TextHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TextHandler::textChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TextHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TextHandler::colorChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TextHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TextHandler::indexColorChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TextHandler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TextHandler::validChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<TextHandler *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->text(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->_color; break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->_indexColor; break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->valid(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<TextHandler *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setText(*reinterpret_cast< QString*>(_v)); break;
        case 1:
            if (_t->_color != *reinterpret_cast< QString*>(_v)) {
                _t->_color = *reinterpret_cast< QString*>(_v);
                Q_EMIT _t->colorChanged();
            }
            break;
        case 2:
            if (_t->_indexColor != *reinterpret_cast< QString*>(_v)) {
                _t->_indexColor = *reinterpret_cast< QString*>(_v);
                Q_EMIT _t->indexColorChanged();
            }
            break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject TextHandler::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_TextHandler.data,
    qt_meta_data_TextHandler,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TextHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TextHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TextHandler.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TextHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void TextHandler::textChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TextHandler::colorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TextHandler::indexColorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void TextHandler::validChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
struct qt_meta_stringdata_BackEnd_t {
    QByteArrayData data[17];
    char stringdata0[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BackEnd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BackEnd_t qt_meta_stringdata_BackEnd = {
    {
QT_MOC_LITERAL(0, 0, 7), // "BackEnd"
QT_MOC_LITERAL(1, 8, 17), // "outputTextChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 19), // "pathSelectedChanged"
QT_MOC_LITERAL(4, 47, 14), // "pushStructName"
QT_MOC_LITERAL(5, 62, 4), // "text"
QT_MOC_LITERAL(6, 67, 12), // "pushStructId"
QT_MOC_LITERAL(7, 80, 16), // "pushStructMember"
QT_MOC_LITERAL(8, 97, 9), // "typeIndex"
QT_MOC_LITERAL(9, 107, 10), // "saveStruct"
QT_MOC_LITERAL(10, 118, 11), // "StructInfo*"
QT_MOC_LITERAL(11, 130, 10), // "structInfo"
QT_MOC_LITERAL(12, 141, 16), // "savePathSelected"
QT_MOC_LITERAL(13, 158, 4), // "path"
QT_MOC_LITERAL(14, 163, 16), // "openPathSelected"
QT_MOC_LITERAL(15, 180, 10), // "outputText"
QT_MOC_LITERAL(16, 191, 12) // "pathSelected"

    },
    "BackEnd\0outputTextChanged\0\0"
    "pathSelectedChanged\0pushStructName\0"
    "text\0pushStructId\0pushStructMember\0"
    "typeIndex\0saveStruct\0StructInfo*\0"
    "structInfo\0savePathSelected\0path\0"
    "openPathSelected\0outputText\0pathSelected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BackEnd[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       2,   76, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    1,   56,    2, 0x06 /* Public */,
       6,    1,   59,    2, 0x06 /* Public */,
       7,    2,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   67,    2, 0x0a /* Public */,
      12,    1,   70,    2, 0x0a /* Public */,
      14,    1,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    5,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   13,

 // properties: name, type, flags
      15, QMetaType::QString, 0x00495003,
      16, QMetaType::Bool, 0x00495001,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void BackEnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BackEnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->outputTextChanged(); break;
        case 1: _t->pathSelectedChanged(); break;
        case 2: _t->pushStructName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->pushStructId((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->pushStructMember((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->saveStruct((*reinterpret_cast< StructInfo*(*)>(_a[1]))); break;
        case 6: _t->savePathSelected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->openPathSelected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< StructInfo* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BackEnd::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::outputTextChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::pathSelectedChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::pushStructName)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::pushStructId)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::pushStructMember)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<BackEnd *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->_outputText; break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->pathSelected(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<BackEnd *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->_outputText != *reinterpret_cast< QString*>(_v)) {
                _t->_outputText = *reinterpret_cast< QString*>(_v);
                Q_EMIT _t->outputTextChanged();
            }
            break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject BackEnd::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_BackEnd.data,
    qt_meta_data_BackEnd,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BackEnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BackEnd::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BackEnd.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BackEnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void BackEnd::outputTextChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void BackEnd::pathSelectedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void BackEnd::pushStructName(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BackEnd::pushStructId(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void BackEnd::pushStructMember(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
