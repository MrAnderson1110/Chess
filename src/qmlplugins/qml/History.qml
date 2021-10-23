import QtQuick 2.11
import QtQml 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import qmlplugins 1.0

ListView {
    id: history
    model: AppHistory

    boundsBehavior: Flickable.StopAtBounds
    onCountChanged: { history.currentIndex = count - 1 }

    clip: true
    delegate: RowLayout {
        spacing: 10
        Rectangle {
            color: "transparent"
            Layout.preferredWidth: tm_num.width
            Layout.preferredHeight: tm_num.height
            Text {
                id: num
                text: (index % 2 === 0) ? (index / 2) + 1 + "." : ""
            }
            TextMetrics {
                id: tm_num
                text: "999."
            }
        }
//        Rectangle {
//            color: "transparent"
//            Layout.preferredWidth: tm_command.width
//            Layout.preferredHeight: tm_command.height
//            Text {
//                id: command
//                text: snap.command
//            }
//            TextMetrics {
//                id: tm_command
//                text: "W:"
//            }
//        }
        Rectangle {
            color: "transparent"
            Layout.preferredWidth: tm_move.width
            Layout.preferredHeight: tm_move.height
            Text {
                id: move
                text: snap.move
            }
            TextMetrics {
                id: tm_move
                text: "W99-99#"
            }
        }
//        Rectangle {
//            color: "transparent"
//            Layout.preferredWidth: tm_defeated.width
//            Layout.preferredHeight: tm_defeated.height
//            Text {
//                id: defeated
//                text: snap.defeated
//            }
//            TextMetrics {
//                id: tm_defeated
//                text: "KgKg"
//            }
//        }
    }
}
