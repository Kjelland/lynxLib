#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// #pragma comment(lib, "XInput.lib")

#include <QMainWindow>
#include <QTimer>
#include <Windows.h>
#include <Xinput.h>
#include "LynxStructure.h"
#include <QUdpSocket>
#include <QNetworkDatagram>

#define LYNX_DEVICE_ID 0x10;
#define LYNX_CONTROLLER_ID 0x5;

using namespace LynxStructureSpace;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    char dataBufferOut[64];

    Ui::MainWindow *ui;
    QTimer *timer;
    int seconds;
    XINPUT_STATE controllerState;

    LynxStructure lynxController;

    QUdpSocket* udpSocket;
    QHostAddress targetAddress;
private slots:
    void timerTick();
signals:
};

#endif // MAINWINDOW_H
