import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

Button {
    id: control
    Layout.fillHeight: true
    Layout.fillWidth: true
    contentItem: Text {
      renderType: Text.NativeRendering
      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter
      font.family: "Helvetica"
      font.pointSize: 16
      color: "black"
      text: control.text
    }
}
