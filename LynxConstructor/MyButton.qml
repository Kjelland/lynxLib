import QtQuick 2.10
import QtQuick.Controls 2.3


Button
{
    id: component
    property string color: "grey"

    text: "A button"
    implicitWidth: 100
    implicitHeight: 45
    font.bold: true
    font.pixelSize: height/4

    hoverEnabled: true
    background:
        Rectangle
        {
            id: rect
            anchors.fill: parent
            color: parent.color           
            border.width: parent.hovered ? 3 : 1
            border.color: Qt.darker(parent.color, 1.5)
            radius: height > width ? width/5 : height/5
            gradient:
                Gradient
                {
                    GradientStop { position: 0 ; color: "#FFFFFF" }
                    GradientStop { position: 0.9 ; color: component.pressed ? Qt.lighter(component.color, 1.3) : component.color }
                    GradientStop { position: 1 ; color: "#000000" }
                }
        }
}



