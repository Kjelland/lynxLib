import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import backendclass 1.0
// import texthandlerclass 1.0
import QtQuick.Dialogs 1.2
// import validcondition 1.0
// import Qt.labs.platform

Window
{
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    BackEnd
    {
        id: backEnd
    }


    Button
    {
        id: button_saveFile
        x: 71
        y: 404
        text: qsTr("Save")
        onClicked: backEnd.buttonSaveClicked()
    }

    TextArea
    {
        id: textBox_test
        x: 71
        y: 373
        width: 370
        height: 25
        text: backEnd.outputText
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }



    TextField
    {
        id: textField_structName
        x: 21
        y: 9
        text: structName.text
        color: structName.color
        placeholderText: qsTr("Struct Name")
        selectByMouse: true
        onTextChanged:
        {
            structName.setText(text)
            backEnd.setStructName(structName.text, structName.valid())
        }
        TextHandler
        {
            id: structName
        }

        Component.onCompleted: structName.setValidCondition(TextHandler.E_Name)
    }

    TextField
    {
        id: textField_structId
        x: 241
        y: 9
        width: 70
        color: structId.color
        text: structId.text
        placeholderText: qsTr("Struct ID")
        selectByMouse: true
        onTextChanged:
        {
            structId.setText(text)
            backEnd.setStructId(structId.text, structId.valid())
        }

        TextHandler
        {
            id: structId
        }

        Component.onCompleted: structId.setValidCondition(TextHandler.E_Number)
    }

    FileDialog
    {
        id: savePathDialog
        title: qsTr("Please choose a folder")
        folder: "D:/QT projects/LynxConstructor/testFolder"
        selectFolder: true
        onAccepted:
        {
            backEnd.pathSelected(fileUrl)
            backEnd.setOpenFileDialog(false)
            close()
        }
        onRejected:
        {
            backEnd.setOpenFileDialog(false)
            close()
        }

        visible: backEnd.openFileDialog
    }

    Button
    {
        id: button_exit
        x: 483
        y: 404
        text: qsTr("Exit")
        onClicked: Qt.quit()
    }

    Button
    {
        id: button_browseFile
        x: 194
        y: 404
        text: qsTr("Browse")
        onClicked: backEnd.buttonBrowseClicked()
    }

    Item
    {
        id: memberList

        ListModel
        {
            id: listModel
            // ListElement { data: memberDelegate }
        }

        Component
        {
            id: memberDelegate

            Item
            {
                width: 400
                height: 45

                Row
                {
                    id: row1

                    Text
                    {
                        id: indexText
                        height: parent.parent.height
                        verticalAlignment: Text.AlignVCenter
                        Component.onCompleted: text = listView.count - 1
                    }

                    TextField
                    {
                        width: 200
                        height: parent.parent.height
                        text: info.text
                        color: info.color
                        placeholderText: qsTr("Element Name")
                        selectByMouse: true
                        onTextChanged:
                        {
                            info.setText(text);
                            backEnd.setMemberName(info.text, info.valid(), info.index)
                        }
                        onAccepted:
                        {
                            listModel.append(memberDelegate)
                            removeButton.visible = false
                            // listView.currentIndex = listModel.count
                        }
                        onFocusChanged:
                        {
                            // indexText.text += "1"
                            if(((listModel.count - 1) == info.index) && listModel.count > 1)
                            {
                                removeButton.visible = true
                            }
                        }

                        Component.onCompleted: focus = true
                    }

                    ComboBox
                    {
                        id: typeId
                        width: 100
                        height: parent.parent.height
                        model: enumList
                        onActivated: backEnd.setMemberType(currentText, info.index)
                        Component.onCompleted: backEnd.setMemberType(currentText, info.index)
                    }

                    Button
                    {
                        id: removeButton
                        height: 20
                        width: 20
                        anchors.verticalCenter: parent.verticalCenter

                        Loader
                        {
                            id: crossImage
                            sourceComponent: crossSquare
                            anchors.fill: parent
                        }

                        onClicked:
                        {
                            if(listModel.count > 1)
                            {
                                listModel.remove(info.index)
                                backEnd.removeMember(info.index)
                            }

                        }

                        Component.onCompleted:
                        {
                            if(listModel.count == 1)
                            {
                                visible = false
                            }
                        }
                    }

                    spacing: 10
                }

                TextHandler
                {
                    id: info
                    Component.onCompleted:
                    {
                        setIndex(listModel.count - 1)
                    }
                }
            }

        }

        ScrollView
        {
            id: scrollView
            x: 21
            y: 76
            width: 400
            height: 264

            ListView
            {
                id: listView
                parent: scrollView
                anchors.fill: parent
                // anchors.left: parent.left
                // anchors.top: parent.top
                // height: 264
                model: listModel
                delegate: memberDelegate

                Component.onCompleted: listModel.append(memberDelegate)

            }
        }

    }

//    Canvas {
//        id: mycanvas
//        width: 100
//        height: 200
//        onPaint: {
//            var ctx = getContext("2d");
//            ctx.fillStyle = Qt.rgba(1, 0, 0, 1);
//            ctx.fillRect(0, 0, width, height);
//        }
    Component
    {
        id: crossSquare

        Canvas
        {
            width: parent.parent.width
            height: parent.parent.height
            property int thickness: (width + height)/20

            onPaint:
            {
                var ctx = getContext("2d")
                ctx.fillStyle = "red" // Qt.rgba(1, 0, 0, 1);
                ctx.fillRect(0, 0, width, height)
                // ctx.fillStyle = mainWindow.color
                ctx.fillRect(thickness, thickness, width - 2*thickness, height - 2*thickness)
                ctx.lineWidth = thickness
                ctx.strokeStyle = mainWindow.color
                ctx.moveTo(thickness,thickness)
                ctx.lineTo(width - thickness, height - thickness)
                ctx.moveTo(thickness, height - thickness)
                ctx.lineTo(width - thickness, thickness)
                ctx.stroke()
            }
        }
    }

    ListModel
    {
        id: enumList
        ListElement { text: qsTr("Int8") }
        ListElement { text: qsTr("Uint8") }
        ListElement { text: qsTr("Int16") }
        ListElement { text: qsTr("Uint16") }
        ListElement { text: qsTr("Int32") }
        ListElement { text: qsTr("Uint32") }
        ListElement { text: qsTr("Int64") }
        ListElement { text: qsTr("Uint64") }
        ListElement { text: qsTr("Float") }
        ListElement { text: qsTr("Double") }
    }

}
