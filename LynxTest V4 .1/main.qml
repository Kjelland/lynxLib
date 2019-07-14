import QtQuick 2.12
import QtQuick.Window 2.12
import backend 1.0
import QtQuick.Controls 2.3
// import QtQuick.Controls.Styles 1.4

Window
{
    visible: true
    width: 1020
    height: 1000
    title: qsTr("Lynx Testing Application")

    BackEnd
    {
        id: backEnd
        int8_var: slider_int8.value_out
        uint8_var: slider_uint8.value_out
        int16_var: slider_int16.value_out
        uint16_var: slider_uint16.value_out
        int32_var: slider_int32.value_out
        uint32_var: slider_uint32.value_out
        int64_var: slider_int64.value_out
        uint64_var: slider_uint64.value_out
        float_var: slider_float.value_out
        double_var: slider_double.value_out
        sendMode: sendModeSwitch.checked ? BackEnd.E_Single : BackEnd.E_All
        onPortListUpdated:
        {
            var currentSelection = portListBox.currentText
            var currentFound = false;

//            if(currentSelection === "")
//                portListBox.currentIndex = -1

            portListModel.clear();
            for(var i = 0; i < list.count; i++)
            {
                portListModel.append( { text: list.getIndex(i) } )

                if(!currentFound && (list.getIndex(i) === currentSelection))
                {
                    portListBox.currentIndex = i;
                    currentFound = true;
                }
            }

            if(!currentFound)
            {
                portListBox.currentIndex = -1;

                if(backEnd.portConnected)
                    backEnd.connectToPort(-1);
            }
        }
        onReceivedString:
        {
            textArea1.text = str + "\r\n" + textArea1.text;
        }
    }



    Column
    {
        spacing: 10

        Row
        {
            spacing: 10

            MySlider
            {
                id: slider_int8
                name: qsTr("Int8:")
                from: -128
                to: 127
                value_in: backEnd.int8_var
                onReleased: backEnd.varUpdated(BackEnd.Test_int8)
            }

            Text
            {
                width: 50
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.int8_returnVar.toString()
                font.pixelSize: 20
            }

            MySwitch
            {
                id: sendModeSwitch
                width: 200
                anchors.verticalCenter: parent.verticalCenter
                text: checked?qsTr("Sending single"):qsTr("Sending all")
                font.pixelSize: 15
            }

            Button
            {
                id: sendAllButton
                anchors.verticalCenter: parent.verticalCenter
                enabled: !sendModeSwitch.checked
                text: qsTr("Send all")
                onClicked: backEnd.sendAll()
            }
        }

        Row
        {
            spacing: 10

            MySlider
            {
                id: slider_uint8
                name: qsTr("Uint8:")
                from: 0
                to: 255
                value_in: backEnd.uint8_var
                onReleased: backEnd.varUpdated(BackEnd.Test_uint8)
            }

            Text
            {
                width: 50
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.uint8_returnVar.toString()
                font.pixelSize: 20
            }

            ComboBox
            {
                id: portListBox
                anchors.verticalCenter: parent.verticalCenter
                width: 300
                enabled: !backEnd.portConnected
                model:
                    ListModel
                    {
                        id: portListModel
                    }
            }

            Button
            {
                anchors.verticalCenter: parent.verticalCenter
                width: 200
                enabled: (portListBox.currentIndex > -1)
                text: backEnd.portConnected ? "Disconnect" : "Connect"
                onClicked: backEnd.portConnected ? backEnd.connectToPort(-1) : backEnd.connectToPort(portListBox.currentIndex)
            }

            Text
            {
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.errorCounter.toString()
                font.pixelSize: 20
            }
        }

        Row
        {
            spacing: 10

            MySlider
            {
                id: slider_int16
                name: qsTr("int16:")
                from: -Math.pow(2,15)
                to: Math.pow(2,15) - 1
                value_in: backEnd.int16_var
                onReleased: backEnd.varUpdated(BackEnd.Test_int16)
            }

            Text
            {
                width: 50
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.int16_returnVar.toString()
                font.pixelSize: 20
            }
        }

        Row
        {
            spacing: 10

            MySlider
            {
                id: slider_uint16
                name: qsTr("Uint16:")
                from: 0
                to: Math.pow(2,16) - 1
                value_in: backEnd.uint16_var
                onReleased: backEnd.varUpdated(BackEnd.Test_uint16)
            }

            Text
            {
                width: 50
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.uint16_returnVar.toString()
                font.pixelSize: 20
            }
        }

        Row
        {
            spacing: 10

            MySlider
            {
                id: slider_int32
                name: qsTr("Int32:")
                from: -Math.pow(2,31)
                to: Math.pow(2,31) - 1
                value_in: backEnd.int32_var
                onReleased: backEnd.varUpdated(BackEnd.Test_int32)
            }

            Text
            {
                width: 50
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.int32_returnVar.toString()
                font.pixelSize: 20
            }
        }

        Row
        {
            spacing: 10

            MySlider
            {
                id: slider_uint32
                name: qsTr("Uint32:")
                from: 0
                to: Math.pow(2,32) - 1
                value_in: backEnd.uint32_var
                onReleased: backEnd.varUpdated(BackEnd.Test_uint32)
            }

            Text
            {
                width: 50
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.uint32_returnVar.toString()
                font.pixelSize: 20
            }
        }

        Row
        {
            spacing: 10

            MySlider
            {
                id: slider_int64
                name: qsTr("Int64:")
                from: -Math.pow(2,63)
                to: Math.pow(2,63) - 1000
                value_in: backEnd.int64_var
                onReleased: backEnd.varUpdated(BackEnd.Test_int64)
            }

            Text
            {
                width: 50
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.int64_returnVar.toString()
                font.pixelSize: 20
            }
        }

        Row
        {
            spacing: 10

            MySlider
            {
                id: slider_uint64
                name: qsTr("Uint64:")
                from: 0
                to: Math.pow(2,64) - 2000
                value_in: backEnd.uint64_var
                onReleased: backEnd.varUpdated(BackEnd.Test_uint64)
            }

            Text
            {
                width: 50
                anchors.verticalCenter: parent.verticalCenter
                text: backEnd.uint64_returnVar.toString()
                font.pixelSize: 20
            }
        }

        Row
        {
            spacing: 10

            MySlider
            {
                id: slider_float
                from: -1
                to: 1
                name: qsTr("Float:")
                value_in: Math.round(backEnd.float_var*1000)/1000
                onReleased: backEnd.varUpdated(BackEnd.Test_float)
            }

            Text
            {
                width: 50
                anchors.verticalCenter: parent.verticalCenter
                text: Math.round(backEnd.float_returnVar*1000)/1000
                font.pixelSize: 20
            }
        }

        Row
        {
            spacing: 10

            MySlider
            {
                id: slider_double
                from: -1
                to: 1
                name: qsTr("Double:")
                value_in: Math.round(backEnd.double_var*1000)/1000
                onReleased: backEnd.varUpdated(BackEnd.Test_double)
            }

            Text
            {
                width: 50
                anchors.verticalCenter: parent.verticalCenter
                text: Math.round(backEnd.double_returnVar*1000)/1000
                font.pixelSize: 20
            }
        }

        Row
        {
            spacing: 10

            ComboBox
            {
                width: 300
                model:
                    ListModel
                    {
                        ListElement{ text: qsTr("Respond") }
                        ListElement{ text: qsTr("Stream") }
                    }
                onCurrentIndexChanged:
                {
                    if(currentIndex > -1)
                        backEnd.changeMode(currentIndex)
                }
            }

            Column
            {
                TextField
                {
                    id: textField1
                    height: 40
                    width: 400
                    placeholderText: "Input text here"
                    font.pixelSize: 15
                    maximumLength: 254
                    onAccepted:
                    {
                        backEnd.sendString(text)
                        // textArea1.text = text + "\r\n" + textArea1.text
                        text = "";
                    }
                }
                ScrollView
                {
                    width: textField1.width
                    height: 250

                    TextArea
                    {
                        width: textField1.width
                        height: 250
                        id: textArea1
                        wrapMode: TextArea.WordWrap
                        background:
                            Rectangle
                            {
                                border.color: "lightgrey"
                                border.width: 1
                            }
                    }
                }
            }
        }
    }
}
