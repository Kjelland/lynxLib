import QtQuick 2.6

Item {
    id: crossSquare
    property string color: "red"
    property string backgroundColor: "black"

    onColorChanged:
    {
        canvas.requestPaint()
    }

    Canvas
    {
        id: canvas
        width: parent.parent.width
        height: parent.parent.height
        property int thickness: (width + height)/20

        onPaint:
        {
            var ctx = getContext("2d")
            ctx.fillStyle = color
            ctx.fillRect(0, 0, width, height)
            ctx.fillRect(thickness, thickness, width - 2*thickness, height - 2*thickness)
            ctx.lineWidth = thickness
            ctx.strokeStyle = backgroundColor
            ctx.moveTo(thickness,thickness)
            ctx.lineTo(width - thickness, height - thickness)
            ctx.moveTo(thickness, height - thickness)
            ctx.lineTo(width - thickness, thickness)
            ctx.stroke()
        }
    }
}
