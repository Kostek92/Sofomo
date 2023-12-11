import QtQuick
import app.AppController
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    GeolocationDataBox {
        id: geoDataBox

        anchors {
          top: parent.top
          bottom: parent.bottom
          right: parent.right
          rightMargin: 50
          left: parent.horizontalCenter
        }
    }
    Rectangle
    {
        id: inputFrame
        width: 140
        height: 40
        anchors {
          top: parent.top
          margins: 30
          left: parent.left
          right: parent.horizontalCenter
        }
        radius:5
        border.color: "gray"
        border.width: 1
        TextInput {
            id: input
            text: "Enter IP or URL..."
            font.pixelSize: 15
            anchors
            {
                fill:parent
                margins:3
            }
            enabled: !AppController.processing
            focus: true
            MouseArea{
                id: inputMouseArea
                anchors.fill: parent
                onClicked:
                {
                    input.text = ""
                    inputMouseArea.visible = false
                }
            }
        }

    }
    RowLayout
    {
        id:buttonsRow
        height: 50
        spacing: 5
        anchors {
          top: inputFrame.bottom
          topMargin: 5
          left: inputFrame.left
          right: inputFrame.right
        }
        Button
        {
            Layout.preferredWidth:  parent.width / 2
            Layout.fillWidth: true
            Layout.fillHeight: true
            id: getDataButton
            text: "Get data"
            font.pixelSize: 15
            enabled: !AppController.processing
            onClicked:
            {
                AppController.onGetDataClicked(input.text)
            }
        }
        Button
        {
            Layout.preferredWidth: parent.width / 2
            Layout.fillWidth: true
            Layout.fillHeight: true
            id: deleteButton
            text: "Delete data"
            font.pixelSize: 15
            enabled: !AppController.processing
            onClicked:
            {
                AppController.onDeleteDataClicked(input.text)
            }
        }
    }
    Text {
        id: statusInfo
        text: AppController.statusInfo
        anchors
        {
            top:buttonsRow.bottom
            topMargin:15
            left:buttonsRow.left
        }
        font.pixelSize: 17
        font.italic: true

    }




}
