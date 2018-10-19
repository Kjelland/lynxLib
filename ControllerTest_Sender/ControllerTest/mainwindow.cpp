#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controllerstruct.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    seconds = 0;

    LynxID lynxID;
    lynxID.deviceID = LYNX_DEVICE_ID;
    lynxID.structID = LYNX_CONTROLLER_ID;

    lynxController.init(initParamsController, lynxID);

    ui->setupUi(this);

    targetAddress = QHostAddress("192.168.20.14");
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(11000);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));
    timer->start(17);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete udpSocket;
    delete timer;
}

static void mapXboxController(LynxStructure* targetStruct, XINPUT_GAMEPAD* source)
{
    /*
    joy_LX,
    joy_LY,
    joy_RX,
    joy_RY,
    trigger_L,
    trigger_R,
    buttons,
    */

    targetStruct->setData<int16_t>(joy_LX, source->sThumbLX);
    targetStruct->setData<int16_t>(joy_LY, source->sThumbLY);
    targetStruct->setData<int16_t>(joy_RX, source->sThumbRX);
    targetStruct->setData<int16_t>(joy_RY, source->sThumbRY);
    targetStruct->setData<int8_t>(trigger_L, source->bLeftTrigger);
    targetStruct->setData<int8_t>(trigger_R, source->bRightTrigger);
    targetStruct->setData<uint32_t>(buttons, source->wButtons);
}

void MainWindow::timerTick()
{
    DWORD dwResult;
    for(DWORD i = 0; i < XUSER_MAX_COUNT; i++)
    {
         dwResult = XInputGetState(i, &controllerState);
        if(dwResult == ERROR_SUCCESS)
        {
            break;
        }
    }

    if(dwResult == ERROR_SUCCESS)
    {
        mapXboxController(&lynxController, &controllerState.Gamepad);
        ui->testLabel->setText(QString::number(controllerState.Gamepad.sThumbLX));

        int length = lynxController.toBuffer(dataBufferOut);
        udpSocket->writeDatagram(dataBufferOut, length, targetAddress, 11000);
    }


}


