#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
// #include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include "LynxStructure.h"
#include "UartHandler.h"
#include "teststruct.h"
#include "arduinoteststruct.h"

#include <QDebug>

using namespace LynxLib;

#define DEVICE_NAME "Teo's PC"
#define DEVICE_ID 1

#define QT_MEMBER_DEF(type, name) \
    Q_PROPERTY(type name MEMBER _##name NOTIFY name##Changed) \
    private: \
    type _##name; \
    void set_##name(type input) { if(input == _##name) return; _##name = input; emit name##Changed(); }

#define QT_MEMBER_DEF_READONLY(type, name) \
    Q_PROPERTY(type name READ name NOTIFY name##Changed) \
    public: \
    type name() { return _##name; } \
    private: \
    type _##name; \
    void set_##name(type input) { if(input == _##name) return; _##name = input; emit name##Changed(); }

#define QT_LYNX_MEMBER_DEF(type, name, lynxID, lynxType, lynxName) \
    private: \
    Q_PROPERTY(type name READ name WRITE set_##name NOTIFY name##Changed) \
    void set_##name(type input) { if(input == static_cast<type>(_lynxHandler.getData<lynxType>(lynxID, lynxName))) return; \
    _lynxHandler.setData(lynxID, lynxName, static_cast<lynxType>(input)); emit name##Changed(); } \
    public: \
    type name() { return static_cast<type>(_lynxHandler.getData<lynxType>(lynxID, lynxName)); }

#define QT_LYNX_WRAPPER_DEF(type, name, wrapperName, lynxType, lynxName) \
    private: \
    Q_PROPERTY(type name READ name WRITE set_##name NOTIFY name##Changed) \
    void set_##name(type input) { if(input == static_cast<type>(wrapperName.var_##lynxName)) return; \
    wrapperName.var_##lynxName = static_cast<lynxType>(input); emit name##Changed(); } \
    public: \
    type name() { return static_cast<type>(wrapperName.var_##lynxName); }


class PortList : public QObject
{
    Q_OBJECT

    // Q_PROPERTY(const QString* getIndex(int index) READ getIndex(int index))
    Q_PROPERTY(int count READ count)

public:
    explicit PortList(QObject *parent = nullptr);

    QList<QString> _list;

    int count () { return _list.count(); }

signals:

public slots:
    QString getIndex(int index) { return _list.at(index); }

};

class BackEnd : public QObject
{
    Q_OBJECT

    // QT_LYNX_MEMBER_DEF(int, int8_var, _sendID, int8_t, test_int8)
    QT_LYNX_WRAPPER_DEF(int, int8_var, _sendData, int8_t, test_int8)
    QT_LYNX_WRAPPER_DEF(int, uint8_var, _sendData, uint8_t, test_uint8)
    QT_LYNX_WRAPPER_DEF(int, int16_var, _sendData, int16_t, test_int16)
    QT_LYNX_WRAPPER_DEF(int, uint16_var, _sendData, uint16_t, test_uint16)
    QT_LYNX_WRAPPER_DEF(int, int32_var, _sendData, int32_t, test_int32)
    QT_LYNX_WRAPPER_DEF(unsigned int, uint32_var, _sendData, uint32_t, test_uint32)
    QT_LYNX_WRAPPER_DEF(double, int64_var, _sendData, int64_t, test_int64)
    QT_LYNX_WRAPPER_DEF(double, uint64_var, _sendData, uint64_t, test_uint64)
    QT_LYNX_WRAPPER_DEF(float, float_var, _sendData, float, test_float)
    QT_LYNX_WRAPPER_DEF(double, double_var, _sendData, double, test_double)

    QT_LYNX_WRAPPER_DEF(int, mode_var, _modeStruct, uint8_t, mode)

    QT_MEMBER_DEF_READONLY(int, int8_returnVar)
    QT_MEMBER_DEF_READONLY(int, uint8_returnVar)
    QT_MEMBER_DEF_READONLY(int, int16_returnVar)
    QT_MEMBER_DEF_READONLY(int, uint16_returnVar)
    QT_MEMBER_DEF_READONLY(int, int32_returnVar)
    QT_MEMBER_DEF_READONLY(unsigned int, uint32_returnVar)
    QT_MEMBER_DEF_READONLY(double, int64_returnVar)
    QT_MEMBER_DEF_READONLY(double, uint64_returnVar)
    QT_MEMBER_DEF_READONLY(float, float_returnVar)
    QT_MEMBER_DEF_READONLY(double, double_returnVar)

    QT_MEMBER_DEF(int, errorCounter)
    QT_MEMBER_DEF(bool, portConnected)

    LynxID _sendID;
    LynxID _receiveID;
    LynxID _modeID;
    LynxHandler _lynxHandler;
    UartHandler _uartHandler;

    TestWrapper _sendData;
    TestWrapper _receiveData;
    ArduinoTestWrapper _modeStruct;


    QTimer _portListUpdateTimer;
    PortList _portList;
    QList<QSerialPortInfo> _portInfoList;
    int _baudRate = 9600;

    void dataSent(const LynxID& id, int index);

public:
    enum E_SendMode
    {
        E_Single,
        E_All
    };

    Q_ENUM(E_SendMode)

    enum E_TestContents_QML
    {
        Test_int8 = 0,
        Test_uint8,
        Test_int16,
        Test_uint16,
        Test_int32,
        Test_uint32,
        Test_int64,
        Test_uint64,
        Test_float,
        Test_double,
        All_Variables = -1
    };

    Q_ENUM(E_TestContents_QML)

    QT_MEMBER_DEF(E_SendMode, sendMode)

public:
    explicit BackEnd(QObject *parent = nullptr);

signals:
    void int8_varChanged();
    void uint8_varChanged();
    void int16_varChanged();
    void uint16_varChanged();
    void int32_varChanged();
    void uint32_varChanged();
    void int64_varChanged();
    void uint64_varChanged();
    void float_varChanged();
    void double_varChanged();

    void mode_varChanged();

    void int8_returnVarChanged();
    void uint8_returnVarChanged();
    void int16_returnVarChanged();
    void uint16_returnVarChanged();
    void int32_returnVarChanged();
    void uint32_returnVarChanged();
    void int64_returnVarChanged();
    void uint64_returnVarChanged();
    void float_returnVarChanged();
    void double_returnVarChanged();

    void sendModeChanged();
    void errorCounterChanged();
    void portConnectedChanged();

    void portListUpdated(PortList* list);

    void receivedString(const QString & str);

public slots:
    void varUpdated(E_TestContents_QML);
    // void float_varUpdated();

    void connectToPort(int index);

    void onNewData(const LynxLib::LynxID& id, int index);

    void sendString(const QString& str);

    void sendAll();

    void changeMode(int desiredMode);

private slots:
    void portListUpdate();

};

#endif // BACKEND_H
