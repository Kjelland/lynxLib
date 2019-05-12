import QtQuick 2.6
import backendclass 1.0
import QtQuick.Controls 2.3

Item
{
    id: memberItem

    property int index: 0
    property int enumIndex: 0
    property string dragDropKey: "key1"
    property bool showCross: false
    property int originalX
    property int originalY

    signal acceptedEnter(int _currentEnumIndex)
    signal enumChanged(string _text, int _index)
    signal textChanged(string _text, bool _valid, int _index)
    signal removeButtonClicked(int _index)
    signal dropped(int _dragIndex, int _dropindex)

    width: 400
    height: 50

    Component.onCompleted:
    {
        // info.setIndex(index)
        // compComplete(index)
    }

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
                    // console.log("\ndragIndex: " + index, "\ndropIndex: " + row1.Drag.target.dropIndex)
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
                    color: info.indexColor // "steelblue"

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

                TextField
                {
                    width: 200
                    height: parent.height
                    text: info.text
                    color: info.color
                    placeholderText: qsTr("Element Name")
                    selectByMouse: true
                    onTextChanged:
                    {
                        info.setText(text);
                        memberItem.textChanged(info.text, info.valid(), index)
                    }
                    onAccepted:
                    {
                        // showCross = false
                        acceptedEnter(typeId.currentIndex)
                    }
                    onFocusChanged:
                    {

                    }

                    Component.onCompleted: focus = true
                }

                ComboBox
                {
                    id: typeId
                    width: 100
                    height: parent.height
                    model: enumList
                    onActivated: enumChanged(currentText, memberItem.index)
                    Component.onCompleted:
                    {
                        currentIndex = enumIndex
                        enumChanged(currentText, memberItem.index)
                    }
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

//                    onPressed: crossSquare.color = "crimson"

//                    onFocusChanged:
//                    {
//                        if(focus !== this)
//                            crossSquare.color = "red"
//                    }

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
        Component.onCompleted:
        {
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


