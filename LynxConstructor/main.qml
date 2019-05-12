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
    title: qsTr("Lynx Constructor")
    // color: "darkslategray"

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

    Text
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



    Row
    {
        id: row1
        leftPadding: 20
        bottomPadding: 20
        topPadding: 20
        spacing: 10

        TextField
        {
            id: textField_structName
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

    }

    ScrollView
    {
        id: scrollView
        height: 230
        width: 420
        anchors.top: row1.bottom

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
        ListElement { indexIn: 0; enumIndexIn: 0; showCrossIn: false  }
    }

    Component
    {
        id: listItemDelegate
        ElementListItem
        {
            index: indexIn
            enumIndex: enumIndexIn
            showCross: showCrossIn

            function reorder(fromIndex, toIndex)
            {
                var i
                for(i = fromIndex; i <= toIndex; i++)
                {
                    listModel.setProperty(i, "indexIn", i)
//                    if(i < listModel.count - 1)
//                        listModel.setProperty(i, "showCrossIn", false )
//                    else
//                        listModel.setProperty(i, "showCrossIn", true )
                }
            }

            onAcceptedEnter:
            {
                // listModel.setProperty(listModel.count - 1, "showCrossIn", false )
                listModel.append({ indexIn: listModel.count, enumIndexIn: _currentEnumIndex, showCrossIn: true })
                if(listModel.count == 2)
                    listModel.setProperty(0, "showCrossIn", true )
                // scrollView.flickableItem.contentY = 5
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


//    Item
//    {
//        id: memberList

//        ListModel
//        {
//            id: listModel
//            // ListElement { data: memberDelegate }
//        }

//        Component
//        {
//            id: memberDelegate


//            Item
//            {
//                id: memberItem

//                // property int dragOffset: 0
//                property string dragDropKey: "key1"
//                property int originalX
//                property int originalY

//                width: 400
//                height: 50

//                Column
//                {
//                    id: column1
//                    height: parent.height
//                    width: parent.width
//                    spacing: 2

//                    DropArea
//                    {
//                        id: dropTarget
//                        property alias dropProxy: dropTarget

//                        width: parent.width
//                        height: 5

//                        keys: [dragDropKey]

//                        Rectangle
//                        {
//                            id: dropRect
//                            anchors.fill: parent
//                            color: mainWindow.color

//                            states: State
//                            {
//                                when: dropTarget.containsDrag
//                                PropertyChanges
//                                {
//                                    target: dropRect
//                                    color: "steelblue"
//                                }
//                            }

//                        }



//                        Component.onCompleted: console.log(dropTarget)
//                    }

//                    Row
//                    {
//                        id: row1
//                        spacing: 5
//                        height: parent.height - dropTarget.height
//                        width: parent.width

//                        MouseArea
//                        {
//                            id: dragArea
//                            height: parent.height
//                            width: height

//                            drag.target: dragRect
//                            drag.axis: Drag.YAxis

//                            onPressed:
//                            {
//                                originalX = dragRect.x
//                                originalY = dragRect.y
//                            }

//                            onReleased:
//                            {
//                                // parent = dragDropRect.Drag.target !== null ? dragDropRect.Drag.target : row1
//                                if(dragRect.Drag.target !== null)
//                                {
//                                    console.log(dragRect.Drag.target)
//                                }

//                                dragRect.x = originalX
//                                dragRect.y = originalY
//                                // parent = originalParent
//                            }

//                            Rectangle
//                            {
//                                id: dragRect
//                                height: parent.height
//                                width: height
//                                // anchors.verticalCenter: parent.verticalCenter
//                                color: "steelblue"


//                                Drag.keys: [dragDropKey]
//                                Drag.active: dragArea.drag.active
//                                Drag.hotSpot.y: height/2
//                                Drag.hotSpot.x: width/2

//                                states: State
//                                {
//                                    when: dragArea.drag.active
//                                    PropertyChanges { target: dragRect; z: 100; }
//                                }

//                                Text
//                                {
//                                    id: indexText
//                                    anchors.fill: parent
//                                    anchors.centerIn: parent
//                                    verticalAlignment: Text.AlignVCenter
//                                    horizontalAlignment: Text.AlignHCenter
//                                    text: info.index
//                                    font.pointSize: 12
//                                }

//                            }
//                        }

//                        TextField
//                        {
//                            width: 200
//                            height: parent.height
//                            // anchors.verticalCenter: parent.verticalCenter
//                            text: info.text
//                            color: info.color
//                            placeholderText: qsTr("Element Name")
//                            selectByMouse: true
//                            onTextChanged:
//                            {
//                                info.setText(text);
//                                backEnd.setMemberName(info.text, info.valid(), info.index)
//                            }
//                            onAccepted:
//                            {
//                                listModel.append(memberDelegate)
//                                removeButton.visible = false
//                                // listView.currentIndex = listModel.count
//                            }
//                            onFocusChanged:
//                            {
//                                // indexText.text += "1"
//                                if(((listModel.count - 1) == info.index) && listModel.count > 1)
//                                {
//                                    removeButton.visible = true
//                                }
//                            }

//                            Component.onCompleted: focus = true
//                        }

//                        ComboBox
//                        {
//                            id: typeId
//                            width: 100
//                            height: parent.height
//                            // anchors.verticalCenter: parent.verticalCenter
//                            model: enumList
//                            onActivated: backEnd.setMemberType(currentText, info.index)
//                            Component.onCompleted: backEnd.setMemberType(currentText, info.index)
//                        }

//                        Button
//                        {
//                            id: removeButton
//                            height: 20
//                            width: 20
//                            anchors.verticalCenter: parent.verticalCenter

//                            Loader
//                            {
//                                id: crossImage
//                                sourceComponent: crossSquare
//                                anchors.fill: parent
//                            }

//                            onClicked:
//                            {
//                                if(listModel.count > 1)
//                                {
//                                    listModel.remove(info.index)
//                                    backEnd.removeMember(info.index)
//                                }

//                            }

//                            Component.onCompleted:
//                            {
//                                if(listModel.count == 1)
//                                {
//                                    visible = false
//                                }
//                            }
//                        }
//                    }
//                }

//                TextHandler
//                {
//                    id: info
//                    Component.onCompleted:
//                    {
//                        setIndex(listModel.count - 1)
//                    }
//                }
//            }
//        }

//        ScrollView
//        {
//            id: scrollView
//            x: 21
//            y: 76
//            width: 400
//            height: 264

//            ListView
//            {
//                id: listView
//                parent: scrollView
//                anchors.fill: parent
//                model: listModel
//                delegate: memberDelegate
//                // spacing: 5
//                Component.onCompleted: listModel.append(memberDelegate)

//            }
//        }

//    }

//    Canvas {
//        id: mycanvas
//        width: 100
//        height: 200
//        onPaint: {
//            var ctx = getContext("2d");
//            ctx.fillStyle = Qt.rgba(1, 0, 0, 1);
//            ctx.fillRect(0, 0, width, height);
//        }
//    Component
//    {
//        id: crossSquare

//        Canvas
//        {
//            width: parent.parent.width
//            height: parent.parent.height
//            property int thickness: (width + height)/20

//            onPaint:
//            {
//                var ctx = getContext("2d")
//                ctx.fillStyle = "red" // Qt.rgba(1, 0, 0, 1);
//                ctx.fillRect(0, 0, width, height)
//                // ctx.fillStyle = mainWindow.color
//                ctx.fillRect(thickness, thickness, width - 2*thickness, height - 2*thickness)
//                ctx.lineWidth = thickness
//                ctx.strokeStyle = mainWindow.color
//                ctx.moveTo(thickness,thickness)
//                ctx.lineTo(width - thickness, height - thickness)
//                ctx.moveTo(thickness, height - thickness)
//                ctx.lineTo(width - thickness, thickness)
//                ctx.stroke()
//            }
//        }
//    }

//    ListModel
//    {
//        id: enumList
//        ListElement { text: qsTr("Int8") }
//        ListElement { text: qsTr("Uint8") }
//        ListElement { text: qsTr("Int16") }
//        ListElement { text: qsTr("Uint16") }
//        ListElement { text: qsTr("Int32") }
//        ListElement { text: qsTr("Uint32") }
//        ListElement { text: qsTr("Int64") }
//        ListElement { text: qsTr("Uint64") }
//        ListElement { text: qsTr("Float") }
//        ListElement { text: qsTr("Double") }
//    }

}
