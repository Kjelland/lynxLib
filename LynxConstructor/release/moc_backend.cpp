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
struct qt_meta_stringdata_TextHandler_t {
    QByteArrayData data[18];
    char stringdata0[180];
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
QT_MOC_LITERAL(5, 56, 5), // "valid"
QT_MOC_LITERAL(6, 62, 7), // "setText"
QT_MOC_LITERAL(7, 70, 5), // "input"
QT_MOC_LITERAL(8, 76, 8), // "setColor"
QT_MOC_LITERAL(9, 85, 17), // "setValidCondition"
QT_MOC_LITERAL(10, 103, 14), // "ValidCondition"
QT_MOC_LITERAL(11, 118, 9), // "condition"
QT_MOC_LITERAL(12, 128, 13), // "setIndexColor"
QT_MOC_LITERAL(13, 142, 4), // "text"
QT_MOC_LITERAL(14, 147, 5), // "color"
QT_MOC_LITERAL(15, 153, 10), // "indexColor"
QT_MOC_LITERAL(16, 164, 6), // "E_Name"
QT_MOC_LITERAL(17, 171, 8) // "E_Number"

    },
    "TextHandler\0textChanged\0\0colorChanged\0"
    "indexColorChanged\0valid\0setText\0input\0"
    "setColor\0setValidCondition\0ValidCondition\0"
    "condition\0setIndexColor\0text\0color\0"
    "indexColor\0E_Name\0E_Number"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TextHandler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       3,   70, // properties
       1,   82, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   57,    2, 0x0a /* Public */,
       6,    1,   58,    2, 0x0a /* Public */,
       8,    1,   61,    2, 0x0a /* Public */,
       9,    1,   64,    2, 0x0a /* Public */,
      12,    1,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::QString,    7,

 // properties: name, type, flags
      13, QMetaType::QString, 0x00495103,
      14, QMetaType::QString, 0x00495103,
      15, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,

 // enums: name, alias, flags, count, data
      10,   10, 0x0,    2,   87,

 // enum data: key, value
      16, uint(TextHandler::E_Name),
      17, uint(TextHandler::E_Number),

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
        case 3: { bool _r = _t->valid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->setText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->setColor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->setValidCondition((*reinterpret_cast< ValidCondition(*)>(_a[1]))); break;
        case 7: _t->setIndexColor((*reinterpret_cast< QString(*)>(_a[1]))); break;
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
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<TextHandler *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->text(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->color(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->indexColor(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<TextHandler *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setText(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setColor(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setIndexColor(*reinterpret_cast< QString*>(_v)); break;
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
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
struct qt_meta_stringdata_BackEnd_t {
    QByteArrayData data[32];
    char stringdata0[408];
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
QT_MOC_LITERAL(3, 27, 21), // "saveFileDialogChanged"
QT_MOC_LITERAL(4, 49, 14), // "setStructIdQml"
QT_MOC_LITERAL(5, 64, 4), // "text"
QT_MOC_LITERAL(6, 69, 16), // "setStructNameQml"
QT_MOC_LITERAL(7, 86, 16), // "addStructItemQml"
QT_MOC_LITERAL(8, 103, 5), // "index"
QT_MOC_LITERAL(9, 109, 9), // "typeIndex"
QT_MOC_LITERAL(10, 119, 20), // "setStructItemTypeQml"
QT_MOC_LITERAL(11, 140, 19), // "resetStructItemList"
QT_MOC_LITERAL(12, 160, 17), // "buttonSaveClicked"
QT_MOC_LITERAL(13, 178, 19), // "buttonBrowseClicked"
QT_MOC_LITERAL(14, 198, 17), // "setSaveFileDialog"
QT_MOC_LITERAL(15, 216, 5), // "input"
QT_MOC_LITERAL(16, 222, 16), // "savePathSelected"
QT_MOC_LITERAL(17, 239, 4), // "path"
QT_MOC_LITERAL(18, 244, 16), // "openPathSelected"
QT_MOC_LITERAL(19, 261, 13), // "setOutputText"
QT_MOC_LITERAL(20, 275, 13), // "setStructName"
QT_MOC_LITERAL(21, 289, 4), // "name"
QT_MOC_LITERAL(22, 294, 5), // "valid"
QT_MOC_LITERAL(23, 300, 11), // "setStructId"
QT_MOC_LITERAL(24, 312, 13), // "setMemberName"
QT_MOC_LITERAL(25, 326, 13), // "setMemberType"
QT_MOC_LITERAL(26, 340, 12), // "removeMember"
QT_MOC_LITERAL(27, 353, 10), // "moveMember"
QT_MOC_LITERAL(28, 364, 9), // "fromIndex"
QT_MOC_LITERAL(29, 374, 7), // "toIndex"
QT_MOC_LITERAL(30, 382, 10), // "outputText"
QT_MOC_LITERAL(31, 393, 14) // "saveFileDialog"

    },
    "BackEnd\0outputTextChanged\0\0"
    "saveFileDialogChanged\0setStructIdQml\0"
    "text\0setStructNameQml\0addStructItemQml\0"
    "index\0typeIndex\0setStructItemTypeQml\0"
    "resetStructItemList\0buttonSaveClicked\0"
    "buttonBrowseClicked\0setSaveFileDialog\0"
    "input\0savePathSelected\0path\0"
    "openPathSelected\0setOutputText\0"
    "setStructName\0name\0valid\0setStructId\0"
    "setMemberName\0setMemberType\0removeMember\0"
    "moveMember\0fromIndex\0toIndex\0outputText\0"
    "saveFileDialog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BackEnd[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       2,  184, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x06 /* Public */,
       3,    0,  115,    2, 0x06 /* Public */,
       4,    1,  116,    2, 0x06 /* Public */,
       6,    1,  119,    2, 0x06 /* Public */,
       7,    3,  122,    2, 0x06 /* Public */,
       7,    2,  129,    2, 0x26 /* Public | MethodCloned */,
      10,    2,  134,    2, 0x06 /* Public */,
      11,    0,  139,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,  140,    2, 0x0a /* Public */,
      13,    0,  141,    2, 0x0a /* Public */,
      14,    1,  142,    2, 0x0a /* Public */,
      16,    1,  145,    2, 0x0a /* Public */,
      18,    1,  148,    2, 0x0a /* Public */,
      19,    1,  151,    2, 0x0a /* Public */,
      20,    2,  154,    2, 0x0a /* Public */,
      23,    2,  159,    2, 0x0a /* Public */,
      24,    3,  164,    2, 0x0a /* Public */,
      25,    2,  171,    2, 0x0a /* Public */,
      26,    1,  176,    2, 0x0a /* Public */,
      27,    2,  179,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int,    8,    5,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    8,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   21,   22,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   21,   22,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Int,   21,   22,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   21,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,

 // properties: name, type, flags
      30, QMetaType::QString, 0x00495103,
      31, QMetaType::Bool, 0x00495103,

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
        case 1: _t->saveFileDialogChanged(); break;
        case 2: _t->setStructIdQml((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->setStructNameQml((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->addStructItemQml((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->addStructItemQml((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->setStructItemTypeQml((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->resetStructItemList(); break;
        case 8: _t->buttonSaveClicked(); break;
        case 9: _t->buttonBrowseClicked(); break;
        case 10: _t->setSaveFileDialog((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->savePathSelected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->openPathSelected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->setOutputText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->setStructName((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 15: _t->setStructId((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 16: _t->setMemberName((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 17: _t->setMemberType((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 18: _t->removeMember((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->moveMember((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::saveFileDialogChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::setStructIdQml)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::setStructNameQml)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)(int , QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::addStructItemQml)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::setStructItemTypeQml)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::resetStructItemList)) {
                *result = 7;
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
        case 0: *reinterpret_cast< QString*>(_v) = _t->outputText(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->saveFileDialog(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<BackEnd *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setOutputText(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setSaveFileDialog(*reinterpret_cast< bool*>(_v)); break;
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
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
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
void BackEnd::saveFileDialogChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void BackEnd::setStructIdQml(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BackEnd::setStructNameQml(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void BackEnd::addStructItemQml(int _t1, QString _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 6
void BackEnd::setStructItemTypeQml(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void BackEnd::resetStructItemList()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
