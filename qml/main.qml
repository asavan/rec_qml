import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import QtQuick.Dialogs 1.3
import org.qtproject.example 1.0

ApplicationWindow {
    flags: Qt.Window | Qt.WindowTitleHint | Qt.WindowSystemMenuHint | Qt.WindowMinMaxButtonsHint
    visible: false
    id: mainWinwow
    width: 1024
    height: 640
    minimumWidth: 720
    minimumHeight: 300

    title: document.documentTitle
    MessageDialog {
        id: aboutBox
        title: "Комплекс тестирования"
        text: "Комплекс тестирования для школьников 14 школы"
        icon: StandardIcon.Information
    }

    Dialog {
        title: "Введите фамилию и имя"
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        id: welcomeDialog
        width: 420
        Component.onCompleted: {
            login.forceActiveFocus()
        }

        onAccepted: {
            if (login.text != "") {
                document.username = login.text
                mainWinwow.visible = true
                document.startExamen()
                timer.start()
            } else {
                errorDialogName.text = "Введите настоящее имя"
                errorDialogName.visible = true
            }
        }
        onRejected: {
            // console.log("exit")
            Qt.quit()
        }
        onDiscard: Qt.quit()
        onHelp: {
            // console.log("help")
            aboutBox.open()
        }
        TextField {
            font.pixelSize: 20
            anchors.fill: parent
            id: login
            focus: true
        }
    }

    Action {
        id: rightAction
        text: "Следующий вопрос"
        shortcut: "ctrl+r"
        icon.name: "edit-redo"
        onTriggered: {
            document.go = true
            textArea.forceActiveFocus()
        }
    }

    Action {
        id: exitAction
        text: "Выход и сохранение"
        shortcut: "ctrl+q"
        icon.name: "document-save-as"
        onTriggered: {
            document.exit()
            Qt.quit()
        }
    }

    Action {
        id: leftAction
        text: "Предыдущий вопрос"
        shortcut: "ctrl+l"
        icon.name: "edit-undo"
        onTriggered: document.go = false
    }

    menuBar: MenuBar {
        Menu {
            title: "&File"
            MenuItem {
                action: leftAction
                icon.source: "../images/editundo.png"
                icon.color: "transparent"
            }
            MenuItem {
                action: rightAction
                icon.source: "../images/editredo.png"
                icon.color: "transparent"
            }
            MenuItem {
                action: exitAction
                icon.source: "../images/filesave.png"
                icon.color: "transparent"
            }
        }

        Menu {
            title: "&Help"
            MenuItem {
                text: "About..."
                onTriggered: aboutBox.open()
            }
        }
    }

    RowLayout {
        id: examInfo
        spacing: 0
        anchors.top: parent.top
        height: 40
        width: parent.width
        TextArea {
            font.pixelSize: 20
            id: examInfoNumber
            readOnly: true
            text:"Вопрос номер " + document.questionNumber + " из " + document.size
            Layout.fillHeight: true
            Layout.fillWidth: true
            background: Rectangle {
                radius: 2
                color: "transparent"
                border.color: "#333"
                border.width: 1
            }
        }

        Timer {
            id: timer
            interval: 1000; running: false; repeat: true
            onTriggered: {
                time.text = document.timeSpent
            }
        }
        TextField {
            Layout.fillHeight: true
            id: time
            width: 100
            background: Rectangle {
                radius: 2
                implicitWidth: 100
                //                 implicitHeight: 24
                color: "transparent"
                border.color: "#333"
                border.width: 1
            }
            font.pixelSize: 20
            //readOnly: true
        }
    }

    SplitView {
        // anchors.fill: parent
        width: parent.width
        anchors.bottom: buttonlayout.top
        anchors.top: examInfo.bottom
        orientation: Qt.Vertical

        TextArea {
            Accessible.name: "question"
            id: textAreaQ
            SplitView.minimumHeight: 200
            // height: parent.height*2/3
            // frameVisible: false
            font.pixelSize: 20
            readOnly: true
            wrapMode: "Wrap"
            text: document.question
            // textFormat: Qt.RichText
        }


        TextArea {
            Accessible.name: "document"
            id: textArea
            font.pixelSize: 20
            baseUrl: "qrc:/"
            text: document.text
            wrapMode: "Wrap"
            // textFormat: Qt.RichText
            Component.onCompleted: forceActiveFocus()
        }
    }

    RowLayout {
        id: buttonlayout
        width: parent.width
        anchors.bottom: parent.bottom
        height: 70
        spacing: 6
        MyBigButton {
            text: "<- Предыдущий вопрос"
            action: leftAction
        }
        MyBigButton {
            text: "Следующий вопрос ->"
            action: rightAction
        }
        MyBigButton {
            text: "Выход и сохранение"
            action: exitAction
        }
    }


    MessageDialog {
        id: errorDialog
        width: 200
        title: "Комплекс тестирования"
        icon: StandardIcon.Critical
    }

    MessageDialog {
        id: errorDialogName
        width: 200
        title: "Комплекс тестирования"
        icon: StandardIcon.Critical
        onAccepted: welcomeDialog.open()
    }

    DocumentHandler {
        id: document
        target: textArea
        Component.onCompleted: {
            if (document.dbloaded) {
                welcomeDialog.visible = true
            } else {
                onError("Не найдена база с вопросами")
            }

        }
        onError: {
            errorDialog.text = message
            errorDialog.visible = true
        }
    }
}
