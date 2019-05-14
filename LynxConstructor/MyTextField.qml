import QtQuick 2.10
import QtQuick.Controls 2.3

TextField
{
    property string borderColor: "grey"
    property string backgroundColor: "transparent"

    implicitHeight: 45
    implicitWidth: 200

    hoverEnabled: true

    background:
        Rectangle
        {
            id: rect
            anchors.fill: parent
            color: backgroundColor
            border.width: parent.hovered ? 2:1
            border.color: borderColor
            radius: width > height ? height/5 : width/5
        }

    onActiveFocusChanged:
    {
        if(activeFocus || (text != ""))
        {
            rect.color = Qt.lighter(backgroundColor, 1.06)
        }
        else
        {
            rect.color = backgroundColor
        }
    }
}
