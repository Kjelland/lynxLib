import QtQuick 2.10
import QtQuick.Controls 2.3
import backendclass 1.0


Item
{
    id: memberItem

    property string themeColor: "grey"
    property string themeAccentColor: Qt.lighter(themeColor, 2.1)

    property int index: 0
    property int enumIndex: 0
    property string enumText: ""
    property bool showCross: false
    property string memberText: ""
    property bool valid

    property int originalX
    property int originalY
    property string dragDropKey: "key1"

    signal acceptedEnter(int _currentEnumIndex)
    signal removeButtonClicked(int _index)
    signal dropped(int _dragIndex, int _dropindex)
    // signal validChanged(bool valid)

    width: 400
    height: 50

    Column
    {
        id: column1
        height: parent.height
        width: parent.width
        spacing: 2

        DropArea
        {
            id: dropTarget
            property int dropIndex: index
            property alias dropProxy: dropTarget

            width: parent.width
            height: 5

            keys: [dragDropKey]

            Rectangle
            {
                id: dropRect
                anchors.centerIn: parent
                height: 3
                width: parent.width
                color:  "transparent"

                states: State
                {
                    when: dropTarget.containsDrag
                    PropertyChanges
                    {
                        target: dropRect
                        color: "steelblue"
                    }
                }

            }
        }

        MouseArea
        {
            id: dragArea
            height: parent.height - dropTarget.height
            width: parent.width

            drag.target: row1
            drag.axis: Drag.YAxis

            onPressed:
            {
                originalX = row1.x
                originalY = row1.y
            }

            onReleased:
            {
                if(row1.Drag.target !== null)
                {
                    dropped(index, row1.Drag.target.dropIndex)
                }

                row1.x = originalX
                row1.y = originalY
            }

            Row
            {
                id: row1
                spacing: 5
                height: parent.height - dropTarget.height
                width: parent.width

                Drag.keys: [dragDropKey]
                Drag.active: dragArea.drag.active
                Drag.hotSpot.y: height/2
                Drag.hotSpot.x: width/2

                states: State
                {
                    when: dragArea.drag.active
                    PropertyChanges { target: row1; z: 100; }
                }


                Rectangle
                {
                    id: indexRect
                    height: parent.height
                    width: height
                    color: info.indexColor
                    border.color: themeColor
                    border.width: 1
                    radius: height > width ? width/5 : height/5

                    Text
                    {
                        id: indexText
                        anchors.fill: parent
                        anchors.centerIn: parent
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        text: index
                        font.pointSize: 12
                    }


                }

                MyTextField
                {
                    width: 200
                    height: parent.height
                    text: memberText
                    color: info.color
                    borderColor: themeColor
                    backgroundColor: themeAccentColor
                    placeholderText: qsTr("Element Name")
                    selectByMouse: true
                    onTextChanged:
                    {
                        info.setText(text)
                    }
                    onAccepted:
                    {
                        acceptedEnter(typeId.currentIndex)
                    }

                    Component.onCompleted: focus = true
                }

                MyComboBox
                {
                    id: typeId
                    width: 100
                    height: parent.height
                    color: themeColor
                    model: enumList
                    currentIndex: enumIndex
                    onCurrentIndexChanged: enumIndex = currentIndex
                    onCurrentTextChanged: enumText = currentText

                }

                Button
                {
                    id: removeButton
                    height: 20
                    width: 20
                    anchors.verticalCenter: parent.verticalCenter
                    hoverEnabled: true
                    visible: showCross

                    CrossSquare
                    {
                        id: crossSquare
                        color: "red"
                        backgroundColor: "white"
                    }

                    onHoveredChanged:
                    {
                        if(hovered)
                            crossSquare.color = "salmon"
                        else
                            crossSquare.color = "red"
                    }

                    onPressedChanged:
                    {
                        if(pressed)
                            crossSquare.color = "crimson"
                        else
                            crossSquare.color = "red"
                    }

                    onClicked:
                    {
                        memberItem.removeButtonClicked(index)
                    }

                }
            }
        }
    }

    TextHandler
    {
        id: info
        onValidChanged: memberItem.valid = info.valid
        onTextChanged: memberItem.memberText = text
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


