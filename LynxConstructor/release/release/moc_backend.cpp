/****************************************************************************
** Meta object code from reading C++ file 'backend.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../backend.h"
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
    char stringdata0[165];
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
QT_MOC_LITERAL(4, 38, 12), // "indexChanged"
QT_MOC_LITERAL(5, 51, 5), // "valid"
QT_MOC_LITERAL(6, 57, 7), // "setText"
QT_MOC_LITERAL(7, 65, 5), // "input"
QT_MOC_LITERAL(8, 71, 8), // "setColor"
QT_MOC_LITERAL(9, 80, 17), // "setValidCondition"
QT_MOC_LITERAL(10, 98, 14), // "ValidCondition"
QT_MOC_LITERAL(11, 113, 9), // "condition"
QT_MOC_LITERAL(12, 123, 8), // "setIndex"
QT_MOC_LITERAL(13, 132, 5), // "index"
QT_MOC_LITERAL(14, 138, 4), // "text"
QT_MOC_LITERAL(15, 143, 5), // "color"
QT_MOC_LITERAL(16, 149, 6), // "E_Name"
QT_MOC_LITERAL(17, 156, 8) // "E_Number"

    },
    "TextHandler\0textChanged\0\0colorChanged\0"
    "indexChanged\0valid\0setText\0input\0"
    "setColor\0setValidCondition\0ValidCondition\0"
    "condition\0setIndex\0index\0text\0color\0"
    "E_Name\0E_Number"
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
    QMetaType::Void, QMetaType::Int,   13,

 // properties: name, type, flags
      14, QMetaType::QString, 0x00495103,
      15, QMetaType::QString, 0x00495103,
      13, QMetaType::Int, 0x00495103,

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
        case 2: _t->indexChanged(); break;
        case 3: { bool _r = _t->valid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->setText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->setColor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->setValidCondition((*reinterpret_cast< ValidCondition(*)>(_a[1]))); break;
        case 7: _t->setIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TextHandler::indexChanged)) {
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
        case 2: *reinterpret_cast< int*>(_v) = _t->index(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<TextHandler *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setText(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setColor(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setIndex(*reinterpret_cast< int*>(_v)); break;
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
void TextHandler::indexChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
struct qt_meta_stringdata_BackEnd_t {
    QByteArrayData data[21];
    char stringdata0[253];
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
QT_MOC_LITERAL(3, 27, 21), // "openFileDialogChanged"
QT_MOC_LITERAL(4, 49, 17), // "buttonSaveClicked"
QT_MOC_LITERAL(5, 67, 19), // "buttonBrowseClicked"
QT_MOC_LITERAL(6, 87, 17), // "setOpenFileDialog"
QT_MOC_LITERAL(7, 105, 5), // "input"
QT_MOC_LITERAL(8, 111, 12), // "pathSelected"
QT_MOC_LITERAL(9, 124, 4), // "path"
QT_MOC_LITERAL(10, 129, 13), // "setOutputText"
QT_MOC_LITERAL(11, 143, 13), // "setStructName"
QT_MOC_LITERAL(12, 157, 4), // "name"
QT_MOC_LITERAL(13, 162, 5), // "valid"
QT_MOC_LITERAL(14, 168, 11), // "setStructId"
QT_MOC_LITERAL(15, 180, 13), // "setMemberName"
QT_MOC_LITERAL(16, 194, 5), // "index"
QT_MOC_LITERAL(17, 200, 13), // "setMemberType"
QT_MOC_LITERAL(18, 214, 12), // "removeMember"
QT_MOC_LITERAL(19, 227, 10), // "outputText"
QT_MOC_LITERAL(20, 238, 14) // "openFileDialog"

    },
    "BackEnd\0outputTextChanged\0\0"
    "openFileDialogChanged\0buttonSaveClicked\0"
    "buttonBrowseClicked\0setOpenFileDialog\0"
    "input\0pathSelected\0path\0setOutputText\0"
    "setStructName\0name\0valid\0setStructId\0"
    "setMemberName\0index\0setMemberType\0"
    "removeMember\0outputText\0openFileDialog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BackEnd[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       2,  112, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    1,   78,    2, 0x0a /* Public */,
       8,    1,   81,    2, 0x0a /* Public */,
      10,    1,   84,    2, 0x0a /* Public */,
      11,    2,   87,    2, 0x0a /* Public */,
      14,    2,   92,    2, 0x0a /* Public */,
      15,    3,   97,    2, 0x0a /* Public */,
      17,    2,  104,    2, 0x0a /* Public */,
      18,    1,  109,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   12,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   12,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Int,   12,   13,   16,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   12,   16,
    QMetaType::Void, QMetaType::Int,   16,

 // properties: name, type, flags
      19, QMetaType::QString, 0x00495103,
      20, QMetaType::Bool, 0x00495103,

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
        case 1: _t->openFileDialogChanged(); break;
        case 2: _t->buttonSaveClicked(); break;
        case 3: _t->buttonBrowseClicked(); break;
        case 4: _t->setOpenFileDialog((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->pathSelected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->setOutputText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->setStructName((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->setStructId((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 9: _t->setMemberName((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 10: _t->setMemberType((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->removeMember((*reinterpret_cast< int(*)>(_a[1]))); break;
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::openFileDialogChanged)) {
                *result = 1;
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
        case 1: *reinterpret_cast< bool*>(_v) = _t->openFileDialog(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<BackEnd *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setOutputText(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setOpenFileDialog(*reinterpret_cast< bool*>(_v)); break;
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
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
void BackEnd::openFileDialogChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
