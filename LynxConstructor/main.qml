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
    property string themeAccentColorMain: Qt.lighter(themeColorMain, 2.15)
    property string themeColorBackgnd: "white"

    visible: true
    width: 640
    height: 480
    minimumWidth: 480
    minimumHeight: 480
    title: qsTr("Lynx Constructor")
    color: themeColorBackgnd

    Rectangle
    {
        id: mainBackground
        anchors.fill: parent
        color: themeColorMain
        gradient:
            Gradient
            {
                GradientStop { position: 0 ; color: themeColorBackgnd }
                GradientStop { position: 0.8 ; color: Qt.lighter(themeColorMain, 1.8) }
                GradientStop { position: 0.9 ; color: themeColorMain }
                GradientStop { position: 1 ; color: Qt.darker(themeColorMain, 1.8) }
            }
    }

    function addMember(index, typeIndex, text)
    {
        listModel.append({ indexIn: index, enumIndexIn: typeIndex, textIn: text, showCrossIn: (listModel.count > 0) })
        if(listModel.count == 2)
            listModel.setProperty(0, "showCrossIn", true)
    }

    function populateStructInfo()
    {
        // console.log(listModel.get(0).validIn)
        structInfo.setStructName(structName.text, structName.valid)
        structInfo.setStructId(structId.text, structId.valid)

        for(var i = 0; i < listModel.count; i++)
        {
            structInfo.addStructMember(listModel.get(i).textIn, listModel.get(i).enumTextIn, listModel.get(i).validIn)
        }

    }

    StructInfo
    {
        id: structInfo
        // onClearMemberList: listModel.clear()
    }

    BackEnd
    {
        id: backEnd
        onPushStructName: structName.text = text
        onPushStructId: structId.text = text
        onPushStructMember:
        {
            addMember(listModel.count, typeIndex, text)
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
            backgroundColor: themeAccentColorMain
            placeholderText: qsTr("Struct Name")
            selectByMouse: true
            onTextChanged: structName.setText(text)

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
            backgroundColor: themeAccentColorMain
            text: structId.text
            placeholderText: qsTr("Struct ID")
            selectByMouse: true
            onTextChanged: structId.setText(text)

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
        ListElement { indexIn: 0; enumIndexIn: 0; textIn: ""; showCrossIn: false; enumTextIn: ""; validIn: false  }
    }

    Component
    {
        id: listItemDelegate

        ElementListItem
        {
            index: indexIn
            enumIndex: enumIndexIn
            showCross: showCrossIn
            memberText: textIn
            enumText:  enumTextIn
            valid: validIn
            themeColor: themeColorMain
            themeAccentColor: themeAccentColorMain

            onEnumIndexChanged: enumIndexIn = enumIndex
            onMemberTextChanged: textIn = memberText
            onEnumTextChanged: enumTextIn = enumText
            onValidChanged: validIn = valid

            function reorder(fromIndex, toIndex)
            {
                var i
                for(i = fromIndex; i <= toIndex; i++)
                {
                    listModel.setProperty(i, "indexIn", i)
                }
            }

            onAcceptedEnter: addMember(listModel.count, _currentEnumIndex, "")

            onRemoveButtonClicked:
            {
                listModel.remove(_index)
                reorder(_index, listModel.count - 1)

                if(listModel.count == 1)
                    listModel.setProperty(0, "showCrossIn", false )
            }

            onDropped:
            {
                if(_dragIndex > _dropindex)
                {
                    listModel.move(_dragIndex, _dropindex, 1)
                    reorder(_dropindex, _dragIndex)
                }
                else if(_dropindex > _dragIndex)
                {
                    listModel.move(_dragIndex, _dropindex - 1, 1)
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
            text: qsTr("Save")
            color: bottomRow.buttonColor
            enabled: backEnd.pathSelected
            onClicked:
            {
                populateStructInfo()
                backEnd.saveStruct(structInfo)
                structInfo.clear()
            }
        }

        MyButton
        {
            text: qsTr("Select Folder")
            color: bottomRow.buttonColor
            onClicked: savePathDialog.visible = true
        }

        MyButton
        {
            text: qsTr("Open")
            color: bottomRow.buttonColor
            onClicked: openPathDialog.visible = true

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
            close()
        }
        onRejected:
        {
            backEnd.outputText = "You cancelled"
            close()
        }

        visible: false
    }

    FileDialog
    {
        id: openPathDialog
        title: qsTr("Please choose a file")
        folder: "D:/QT projects/LynxConstructor/testFolder"
        nameFilters: { "C/C++ header files (*.h)" }
        onAccepted:
        {
            listModel.clear()
            structName.text = ""
            structId.text = ""

            backEnd.openPathSelected(fileUrl)

            if(listModel.count < 1)
                addMember(0, 0, "");

            close()
        }
        onRejected:
        {
            backEnd.outputText = "You cancelled"
            close()
        }

        visible: false
    }

}
