import QtQuick 2.11
import qmlplugins 1.0

BasicGridCell {
    id: cell
    property color selectColor
    property color oddColor
    property color evenColor
    property color underFireColor
    property color hoveredColor

    background: Rectangle {
        color: {
            if(underFire)
                return underFireColor
            else if(selected)
                return selectColor
            else if((rowIndex + columnIndex) % 2)
                return evenColor
            else
                return oddColor
        }
        border.width: hovered ? 3 : 1
        border.color: hovered ? hoveredColor : "black"
    }
}
