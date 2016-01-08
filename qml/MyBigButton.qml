import QtQuick 2.2


import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.1
import QtQuick.Window 2.1
import QtQuick.Controls.Styles 1.4
import org.qtproject.example 1.0
Button {
    Layout.fillHeight: true
    Layout.fillWidth: true
    style: ButtonStyle {
          label: Text {
            renderType: Text.NativeRendering
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.family: "Helvetica"
            font.pointSize: 16
            color: "black"
            text: control.text
          }
        }
}

