import QtQuick 2.12
import QtQuick.Controls 2.3

Item
{
    id: mySlider
    property string name: "name"
    property var value_out: slider.value
    property var value_in: value_out
    property var from: 0
    property var to: 1
    signal moved
    signal released(var val)
    signal pressed(var val)

    implicitHeight: 60
    implicitWidth: 300

    Row
    {
        spacing: 10
        padding: 10
        Label
        {
            anchors.verticalCenter: parent.verticalCenter
            width: 60
            text: mySlider.name
            font.pixelSize: 20
        }

        Column
        {
            Label
            {
                anchors.horizontalCenter: slider.horizontalCenter
                text: value_in
                font.pixelSize: 20
            }

            Slider
            {
                id: slider
                from: mySlider.from
                to: mySlider.to
                value: 0
                onMoved: mySlider.moved()
                onPressedChanged:
                {
                    if(pressed)
                        mySlider.pressed(value)
                    else
                        mySlider.released(value)
                }
            }
        }
    }
}
