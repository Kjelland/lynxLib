#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
#ifdef LYNX_DEBUG
    out(stdout),
#endif //LYNX_DEBUG
    ui(new Ui::MainWindow),
    lynxHandler(DEVICE_ID, DEVICE_NAME)
    // uartHandler(4, 9600)
{
#ifdef LYNX_DEBUG
    out << "Starting";
#endif //LYNX_DEBUG



    lynxController = lynxHandler.addStructure(CONTROLLER_STRUCT, 1, &controllerDefinition);
    lynxController2 = lynxHandler.addStructure(CONTROLLER_STRUCT, 2, &controllerDefinition);

    // if(!uartHandler.open(4, 9600))
    //    ui->Headline->setText("Could not open port");

    connect(xInputTimer, SIGNAL(timeout()), this, SLOT(processXinput()));
    connect(uartTimer, SIGNAL(timeout()), this, SLOT(runUart()));

    // connect(ui->comboBox_portSelector, SIGNAL(actvated()), this, SLOT(portSelector_click()));

    xInputTimer->start(gamepadUpdate);
    uartTimer->start(1);

    ui->setupUi(this);

    ui->comboBox_portSelector->addItem("...Search...");

    ui->controllerSelector->addItem("Controller 1");
    ui->controllerSelector->addItem("Controller 2");
    ui->controllerSelector->addItem("Controller 3");
    ui->controllerSelector->addItem("Controller 4");
}

MainWindow::~MainWindow()
{
    delete xInputTimer;
    delete uartTimer;
    delete ui;
}

void MainWindow::processXinput()
{
    ui->label_errorCounter->setText(QString::number(uartHandler.errorCount()));

    controllerSelection = DWORD(ui->controllerSelector->currentIndex());

    for(DWORD i = 0; i < XUSER_MAX_COUNT; i++)
    {
        ZeroMemory( &(xInputController[i].controllerState), sizeof(XINPUT_STATE) );

        xInputController[i].connectionState = XInputGetState(i, &(xInputController[i].controllerState));

        if(xInputController[i].connectionState == ERROR_SUCCESS)
        {
            if(batteryTimer == 0)
            {
                XInputGetBatteryInformation(i, BATTERY_DEVTYPE_GAMEPAD, &(xInputController[i].controllerBattery));
            }
        }
        else
        {
            if (batteryTimer == 0)
            {
                ZeroMemory(&(xInputController[i].controllerBattery), sizeof(XINPUT_BATTERY_INFORMATION));
            }
        }
    }


    if(batteryTimer == 0)
        mapBatteryText(xInputController[controllerSelection].controllerBattery, ui->batteryType_label, ui->batteryLevel_label);

    mapXinputToLynx(xInputController[controllerSelection].controllerState.Gamepad, lynxHandler,  lynxController);

    if(xInputController[controllerSelection].connectionState == ERROR_SUCCESS)
    {
        uartHandler.send(lynxHandler, lynxController);
    }

    batteryTimer++;
    if((batteryTimer > batteryUpdate) || (controllerSelection != controllerSelection_Last))
        batteryTimer = 0;

    controllerSelection_Last = controllerSelection;
    // ui->centerText->setText(QString::number(batteryTimer));

}

void MainWindow::runUart()
{
    if(uartHandler.opened())
    {
        uartHandler.update(this->lynxHandler, this->lynxController2 );

        if(uartHandler.newData())
        {
            mapControllerText(
                        lynxHandler.getData<int16_t>(lynxController2, joy_LX),
                        lynxHandler.getData<int16_t>(lynxController2, joy_LY),
                        lynxHandler.getData<uint8_t>(lynxController2, trigger_L),
                        lynxHandler.getBit(lynxController2, buttons, XINPUT_GAMEPAD_LEFT_SHOULDER),
                        ui->label_leftJoyX,
                        ui->label_leftJoyY,
                        ui->label_leftTrigger,
                        ui->label_leftB
                        );

            mapControllerText(
                        lynxHandler.getData<int16_t>(lynxController2, joy_RX),
                        lynxHandler.getData<int16_t>(lynxController2, joy_RY),
                        lynxHandler.getData<uint8_t>(lynxController2, trigger_R),
                        lynxHandler.getBit(lynxController2, buttons, XINPUT_GAMEPAD_RIGHT_SHOULDER),
                        ui->label_rightJoyX,
                        ui->label_rightJoyY,
                        ui->label_rightTrigger,
                        ui->label_rightB
                        );
#ifdef LYNX_DEBUG
        out << "----Start of data----" << endl;
        for(int i = 0; i < DATABUFFER_SIZE; i++)
        {
            out << QString::number(uartHandler.bufferAt(i)) << endl;
        }
        out << "----End of data----" << endl;
#endif //LYNX_DEBUG
        }
    }
}

void MainWindow::mapBatteryText(const XINPUT_BATTERY_INFORMATION& batteryInfo, QLabel* typeLabel, QLabel* levelLabel)
{
    switch(batteryInfo.BatteryType)
    {
    case BATTERY_TYPE_DISCONNECTED:
        typeLabel->setText("Disconnected");
        break;
    case BATTERY_TYPE_WIRED:
        typeLabel->setText("Wired");
        break;
    case BATTERY_TYPE_ALKALINE:
        typeLabel->setText("Alkaline");
        break;
    case BATTERY_TYPE_NIMH:
        typeLabel->setText("NIMH");
        break;
    case BATTERY_TYPE_UNKNOWN:
        typeLabel->setText("Unknown");
        break;
    default:
        typeLabel->setText("Error");
        break;
    }

    switch(batteryInfo.BatteryLevel)
    {
    case BATTERY_LEVEL_EMPTY:
        levelLabel->setText("Empty");
        break;
    case BATTERY_LEVEL_LOW:
        levelLabel->setText("Low");
        break;
    case BATTERY_LEVEL_MEDIUM:
        levelLabel->setText("Medium");
        break;
    case BATTERY_LEVEL_FULL:
        levelLabel->setText("Full");
        break;
    default:
        levelLabel->setText("Error");
        break;
    }
}

void MainWindow::mapControllerText(SHORT xVal, SHORT yVal, BYTE trigVal, bool buttonVal, QLabel* xLabel, QLabel* yLabel, QLabel* triggerLabel, QLabel* buttonLabel)
{
    xLabel->setText(QString::number(xVal));
    yLabel->setText(QString::number(yVal));
    triggerLabel->setText(QString::number(trigVal));
    if(buttonVal)
    {
        buttonLabel->setText("ON");
    }
    else
    {
        buttonLabel->setText("OFF");
    }
}

void MainWindow::mapXinputToLynx(XINPUT_GAMEPAD& controller, LynxHandler& lynxHandler, const LynxID& lynxID)
{
    lynxHandler.setData(lynxID, joy_LX, controller.sThumbLX);
    lynxHandler.setData(lynxID, joy_LY, controller.sThumbLY);
    lynxHandler.setData(lynxID, joy_RX, controller.sThumbRX);
    lynxHandler.setData(lynxID, joy_RY, controller.sThumbRY);
    lynxHandler.setData(lynxID, trigger_L, controller.bLeftTrigger);
    lynxHandler.setData(lynxID, trigger_R, controller.bRightTrigger);
    lynxHandler.setData(lynxID, buttons, controller.wButtons);

    /*
    enum ControllerContents
    {
        joy_LX,
        joy_LY,
        joy_RX,
        joy_RY,
        trigger_L,
        trigger_R,
        buttons,
        endOfList
    };
    */
}



void MainWindow::on_comboBox_portSelector_activated(int index)
{
    if(index == _portSelectorIndex)
    {
        ui->comboBox_portSelector->clear();

        _serialPortInfo = QSerialPortInfo::availablePorts();

        for(int i = 0; i < _serialPortInfo.count(); i++)
        {
            ui->comboBox_portSelector->addItem(_serialPortInfo.at(i).description() + QString(" - ") + _serialPortInfo.at(i).portName());
        }

        // serialPortInfo.at(0).

        _portSelectorIndex = _serialPortInfo.count();
        ui->comboBox_portSelector->addItem("...Search...");
    }
}

void MainWindow::on_pushButton_connectPort_clicked()
{
    if(!uartHandler.opened())
    {
        _serialPortInfo = QSerialPortInfo::availablePorts();

        int portCount = _serialPortInfo.count();
        int selectedIndex = ui->comboBox_portSelector->currentIndex();

        if(portCount <= selectedIndex)
            return;

        if(!uartHandler.open(_serialPortInfo.at(selectedIndex), 9600))
            return;

        ui->pushButton_connectPort->setText("Disconnect");
    }
    else
    {
        uartHandler.close();
        ui->pushButton_connectPort->setText("Connect");
    }
}
