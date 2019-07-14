import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import backendclass 1.0
// import texthandlerclass 1.0
import QtQuick.Dialogs 1.2
// import validcondition 1.0
// import Qt.labs.platform



Window
{

    id: mainWindow

    property string themeColorMain: "steelblue"
    property string themeColorBackgnd: "white"

    visible: true
    width: 640
    height: 480
    title: qsTr("Lynx Constructor")
    color: themeColorBackgnd

    BackEnd
    {
        id: backEnd
        onSetStructIdQml:
        {
            // console .log(typeList.get(i).text);
            structInfo.addStructMember(listModel.get(i).textIn, listModel.get(i).enumTextIn, typeList.get(listModel.get(i).enumIndexIn).text, listModel.get(i).validIn)
        }
        onSetStructNameQml:
        {
            structName.setText(text)
        }
        onAddStructItemQml:
        {
            listModel.append({ indexIn: listModel.count, enumIndexIn: typeIndex, textIn: text, showCrossIn: listModel.count > 0})

            backEnd.setMemberName(text, true, listModel.count - 1);

            if(listModel.count == 2)
                listModel.setProperty(0, "showCrossIn", true )
        }
        onResetStructItemList: listModel.clear()
        onSetStructItemTypeQml:
        {
            listModel.setProperty(index, "enumIndexIn", typeIndex)
        }

    }

    Row
    {
        id: row1
        leftPadding: 20
        bottomPadding: 20
        topPadding: 20
        spacing: 10

        MyTextField
        {
            id: textField_structName
            text: structName.text
            color: structName.color
            borderColor: themeColorMain
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

        MyTextField
        {
            id: textField_structId
            width: 70
            color: structId.color
            borderColor: themeColorMain
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

    }

    ScrollView
    {
        id: scrollView
        width: 420
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: row1.bottom
        anchors.bottom: outputBox.top
        anchors.bottomMargin: 50

        ListView
        {
            id: listView
            parent: scrollView
            anchors.fill: parent
            leftMargin: 20
            model: listModel
            delegate: listItemDelegate
        }


    }

    ListModel
    {
        id: listModel
        ListElement { indexIn: 0; enumIndexIn: 0; textIn: ""; showCrossIn: false  }
    }

    Component
    {
        id: listItemDelegate
        ElementListItem
        {
            index: indexIn
            enumIndex: enumIndexIn
            showCross: showCrossIn
            themeColor: themeColorMain
            memberText: textIn

            function reorder(fromIndex, toIndex)
            {
                var i
                for(i = fromIndex; i <= toIndex; i++)
                {
                    listModel.setProperty(i, "indexIn", i)
                }
            }

            onAcceptedEnter:
            {
                listModel.append({ indexIn: listModel.count, enumIndexIn: _currentEnumIndex, textIn: "", showCrossIn: true })

                if(listModel.count == 2)
                    listModel.setProperty(0, "showCrossIn", true )
            }
            onTextChanged: backEnd.setMemberName(_text, _valid, _index)
            onEnumChanged: backEnd.setMemberType(_text, _index)
            onRemoveButtonClicked:
            {
                listModel.remove(_index)
                backEnd.removeMember(_index)
                reorder(_index, listModel.count - 1)

                if(listModel.count == 1)
                    listModel.setProperty(0, "showCrossIn", false )
            }
            onDropped:
            {
                if(_dragIndex > _dropindex)
                {
                    listModel.move(_dragIndex, _dropindex, 1)
                    backEnd.moveMember(_dragIndex, _dropindex)
                    reorder(_dropindex, _dragIndex)
                }
                else if(_dropindex > _dragIndex)
                {
                    listModel.move(_dragIndex, _dropindex - 1, 1)
                    backEnd.moveMember(_dragIndex, _dropindex - 1)
                    reorder(_dragIndex, _dropindex - 1)
                }
                else
                    return



            }
        }
    }

    Text
    {
        id: outputBox

        property string borderColor: themeColorMain

        width: mainWindow.width - bottomRow.margin*2
        height: 45

        anchors.bottom: bottomRow.top
        anchors.left: bottomRow.left
        anchors.bottomMargin: 10

        text: backEnd.outputText
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        Rectangle
        {
            anchors.fill: parent
            color: "transparent"
            border.width: 1
            border.color: parent.borderColor
            radius: width > height ? height/5 : width/5
        }
    }

    Row
    {
        id: bottomRow
        property int margin: 20
        property string buttonColor: themeColorMain

        x: margin
        y: mainWindow.height - height - margin
        spacing: 10

        MyButton
        {
            // width: 130
            text: qsTr("Save")
            color: bottomRow.buttonColor
            onClicked: backEnd.buttonSaveClicked()
        }

        MyButton
        {
            // width: 130
            text: qsTr("Select Folder")
            color: bottomRow.buttonColor
            onClicked: backEnd.buttonBrowseClicked()
        }

        MyButton
        {
            text: qsTr("Open")
            color: bottomRow.buttonColor
            onClicked:
            {
                openPathDialog.visible = true
            }
        }
    }

    MyButton
    {
        height: bottomRow.height
        anchors.top: bottomRow.top
        x: mainWindow.width - width - bottomRow.margin
        text: qsTr("Exit")
        color: mainWindow.themeColorMain
        onClicked: Qt.quit()
    }


    FileDialog
    {
        id: savePathDialog
        title: qsTr("Please choose a folder")
        folder: "D:/QT projects/LynxConstructor/testFolder"
        selectFolder: true
        onAccepted:
        {
            backEnd.savePathSelected(fileUrl)
            backEnd.setSaveFileDialog(false)
            close()
        }
        onRejected:
        {
            backEnd.setSaveFileDialog(false)
            close()
        }

        visible: backEnd.saveFileDialog
    }

    FileDialog
    {
        id: openPathDialog
        title: qsTr("Please choose a file")
        folder: "D:/QT projects/LynxConstructor/testFolder"
        nameFilters: { "C/C++ header files (*.h)" }
        onAccepted:
        {
            visible = false
            // backEnd.setOutputText("You selected: " + openPathDialog.fileUrl)
            backEnd.openPathSelected(openPathDialog.fileUrl)
            close()
        }
        onRejected:
        {
            visible = false
            backEnd.setOutputText("You canceled")
            close()
        }

        visible: false
    }

    ListModel
    {
        id: typeList
        ListElement { text: qsTr("int8_t") }
        ListElement { text: qsTr("uint8_t") }
        ListElement { text: qsTr("int16_t") }
        ListElement { text: qsTr("uint16_t") }
        ListElement { text: qsTr("int32_t") }
        ListElement { text: qsTr("uint32_t") }
        ListElement { text: qsTr("int64_t") }
        ListElement { text: qsTr("uint64_t") }
        ListElement { text: qsTr("float") }
        ListElement { text: qsTr("double") }
    }

}
