import QtQuick 2.12
import QtQuick.Controls 2.3

Switch
{
    id: control
    property var checkedColor: "steelblue"
    property var uncheckedColor: "brown"

    indicator:
        Rectangle
        {
            implicitWidth: 48
            implicitHeight: 26
            x: control.leftPadding
            y: parent.height / 2 - height / 2
            radius: 13
            color: control.checked ? control.checkedColor : control.uncheckedColor
            border.color: control.checked ? control.checkedColor : "#cccccc"

            Rectangle
            {
                x: control.checked ? parent.width - width : 0
                width: 26
                height: 26
                radius: 13
                color: control.down ? "#cccccc" : "#ffffff"
                border.color: control.checked ? (control.down ? Qt.lighter(control.checkedColor) : control.checkedColor) :
                                                (control.down ? Qt.lighter(control.uncheckedColor) : control.uncheckedColor)
            }
        }
}

