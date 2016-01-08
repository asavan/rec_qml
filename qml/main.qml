/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.1
import QtQuick.Controls.Styles 1.4
import org.qtproject.example 1.0

ApplicationWindow {
    flags: Qt.Window |
           Qt.WindowTitleHint | Qt.WindowSystemMenuHint | Qt.WindowMinMaxButtonsHint
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

        onAccepted: {console.log(login.text)
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
            console.log("exit")
            Qt.quit()
        }
        onDiscard: Qt.quit()
        onHelp: {
            console.log("help")
            aboutBox.open()
        }
       TextField {

           style: TextFieldStyle {
                  textColor: "black"
                  // @disable-check M17
                  font.pixelSize: 20
                  background: Rectangle {
                      radius: 2
                      implicitHeight: 50
                      implicitWidth: 400
                  }
              }
           // inputMask: "X"
           id: login
           focus: true
       }
    }


    Action {
           id: rightAction
           text: "Следующий вопрос"
           shortcut: "ctrl+r"
           iconSource: "images/editredo.png"
           iconName: "format-justify-right"
           onTriggered: {
               document.go = true
               textArea.forceActiveFocus()
           }
       }

    Action {
           id: exitAction
           text: "Выход и сохранение"
           shortcut: "ctrl+q"
           iconSource: "images/filesave.png"
           onTriggered: {
               document.exit()
               Qt.quit()
           }
       }

    Action {
           id: leftAction
           text: "Предыдущий вопрос"
           shortcut: "ctrl+l"
           iconSource: "images/editundo.png"
           onTriggered: document.go = false
       }

    menuBar: MenuBar {
        Menu {
            title: "&File"
            MenuItem { action: exitAction }
            MenuItem { action: rightAction }
            MenuItem { action: leftAction }
        }

        Menu {
            title: "&Help"
            MenuItem { text: "About..." ; onTriggered: aboutBox.open() }
        }
    }

    RowLayout {
        id: examInfo
        spacing: 0
        anchors.top: parent.top
         height: 40
          width: parent.width
    TextArea{
         font.pixelSize: 20
         id: examInfoNumber
         readOnly: true
         text:"Вопрос номер " + document.questionNumber + " из " + document.size
         Layout.fillHeight: true
         Layout.fillWidth: true
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
         style: TextFieldStyle {
                 textColor: "black"
                 background: Rectangle {
                     radius: 2
                     implicitWidth: 100
                     implicitHeight: 24
                     color: "white"
                     border.color: "#333"
                     border.width: 1
                 }
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
            // height: parent.height*2/3
            // frameVisible: false
            font.pixelSize: 20
            height: 320
           // width: parent.width
           // anchors.top: parent.top
           // anchors.bottom: textArea.top
            readOnly: true
            text: document.question
            // textFormat: Qt.RichText
        }


        TextArea {
            Accessible.name: "document"
            id: textArea
            font.pixelSize: 20
            baseUrl: "qrc:/"
            text: document.text
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
