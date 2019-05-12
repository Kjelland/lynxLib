import QtQuick 2.6
import QtQuick.Controls 2.3

TextField
{
    property string borderColor: "grey"

    implicitHeight: 45
    implicitWidth: 200

    hoverEnabled: true

    background:
        Rectangle
        {
            anchors.fill: parent
            color: "transparent"
            border.width: parent.hovered ? 2:1
            border.color: borderColor
            radius: width > height ? height/5 : width/5
        }
}
