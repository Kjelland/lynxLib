#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>

static const unsigned char qt_resource_tree[] = {
0,
0,0,0,0,2,0,0,0,6,0,0,0,1,0,0,0,
118,0,0,0,0,0,1,0,0,0,0,0,0,0,88,0,
0,0,0,0,1,0,0,0,0,0,0,0,154,0,0,0,
0,0,1,0,0,0,0,0,0,0,8,0,0,0,0,0,
1,0,0,0,0,0,0,0,188,0,0,0,0,0,1,0,
0,0,0,0,0,0,44,0,0,0,0,0,1,0,0,0,
0};
static const unsigned char qt_resource_names[] = {
0,
1,0,0,0,47,0,47,0,15,5,216,47,28,0,67,0,
114,0,111,0,115,0,115,0,83,0,113,0,117,0,97,0,
114,0,101,0,46,0,113,0,109,0,108,0,19,8,113,249,
60,0,69,0,108,0,101,0,109,0,101,0,110,0,116,0,
76,0,105,0,115,0,116,0,73,0,116,0,101,0,109,0,
46,0,113,0,109,0,108,0,12,1,250,113,92,0,77,0,
121,0,66,0,117,0,116,0,116,0,111,0,110,0,46,0,
113,0,109,0,108,0,15,1,185,30,92,0,77,0,121,0,
84,0,101,0,120,0,116,0,70,0,105,0,101,0,108,0,
100,0,46,0,113,0,109,0,108,0,14,2,39,51,124,0,
77,0,121,0,67,0,111,0,109,0,98,0,111,0,66,0,
111,0,120,0,46,0,113,0,109,0,108,0,8,8,1,90,
92,0,109,0,97,0,105,0,110,0,46,0,113,0,109,0,
108};
static const unsigned char qt_resource_empty_payout[] = { 0, 0, 0, 0, 0 };
QT_BEGIN_NAMESPACE
extern Q_CORE_EXPORT bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
QT_END_NAMESPACE
namespace QmlCacheGeneratedCode {
namespace _0x5f__main_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__MyComboBox_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__MyTextField_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__MyButton_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__ElementListItem_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__CrossSquare_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
        resourcePathToCachedUnit.insert(QStringLiteral("/main.qml"), &QmlCacheGeneratedCode::_0x5f__main_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/MyComboBox.qml"), &QmlCacheGeneratedCode::_0x5f__MyComboBox_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/MyTextField.qml"), &QmlCacheGeneratedCode::_0x5f__MyTextField_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/MyButton.qml"), &QmlCacheGeneratedCode::_0x5f__MyButton_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/ElementListItem.qml"), &QmlCacheGeneratedCode::_0x5f__ElementListItem_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/CrossSquare.qml"), &QmlCacheGeneratedCode::_0x5f__CrossSquare_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.version = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
QT_PREPEND_NAMESPACE(qRegisterResourceData)(/*version*/0x01, qt_resource_tree, qt_resource_names, qt_resource_empty_payout);
}
const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qml)() {
    ::unitRegistry();
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qml))
int QT_MANGLE_NAMESPACE(qCleanupResources_qml)() {
    return 1;
}
