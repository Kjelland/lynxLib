#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtimer.h>
#include <windows.h>
#include <xinput.h>
#include <qlabel.h>
#include <QTextStream>

#include "LynxStructure.h"
#include "controllerstruct.h"
#include "UartHandler.h"

#define QT_LYNX
#define DEVICE_ID 1
#define DEVICE_NAME "Teo's PC"

// #define LYNX_DEBUG

namespace Ui {
class MainWindow;
}

struct XinputController
{
    XINPUT_STATE controllerState;
    DWORD connectionState = 0;
    XINPUT_BATTERY_INFORMATION controllerBattery;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
#ifdef LYNX_DEBUG
    QTextStream out;
#endif //LYNX_DEBUG

    Ui::MainWindow *ui;
    QTimer* xInputTimer = new QTimer(this);
    int testCounter = 0;

    // bool firstRun = true;

    XinputController xInputController[XUSER_MAX_COUNT];

    int batteryTimer = 0;

    DWORD controllerSelection = 0;
    DWORD controllerSelection_Last = 0;

    void mapControllerText(SHORT xVal, SHORT yVal, BYTE trigVal, bool buttonVal, QLabel* xLabel, QLabel* yLabel, QLabel* triggerLabel, QLabel* buttonLabel);
    void mapBatteryText(const XINPUT_BATTERY_INFORMATION& batteryInfo, QLabel* typeLabel, QLabel* levelLabel);

    LynxHandler lynxHandler;
    LynxID lynxController;
    LynxID lynxController2;

    UartHandler uartHandler;
    QTimer* uartTimer = new QTimer(this);

    void mapXinputToLynx(XINPUT_GAMEPAD& controller, LynxHandler& lynxHandler, const LynxID& lynxID);

    // QTimer* comTimer = new QTimer(this);
    QTimer comTimer;

    static const int comPortUpdate = 5000;  // How often to check for com ports in ms
    static const int gamepadUpdate = 100;   // Gamepad refresh rate in ms
    static const int batteryUpdate = 50;    // Factor of gamepad refresh rate
    static const int uartUpdate = 1;        // UART refresh rate in ms

    QList<QSerialPortInfo> _serialPortInfo;
    QSerialPortInfo _selectedPort;
private slots:
    void processXinput();
    void runUart();
    // void portSelector_click();
    // void portSelector_select();
    void on_comboBox_portSelector_activated(int index);
    void on_pushButton_connectPort_clicked();
    void checkPorts();
};



#endif // MAINWINDOW_H
