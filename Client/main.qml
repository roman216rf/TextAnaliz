import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.1
import ClientModule 1.0

Window {
    width: 360
    height: 600
    visible: true
    maximumHeight: 600
    maximumWidth: 360
    minimumHeight: 600
    minimumWidth: 360
    title: qsTr("L-Telecom тестовое задание")

    Connections{
        target: client //подключение класса Client к слою GUI
        onMsgViewSignal: {
            msgBox.title = title
            msgBox.text = text
            msgBox.open()
        }
        onPrintResult: {
            result.text = data
        }
    }

    Client{
        id: clientProp
        status: client.status
        color: client.color
    }

    FileDialog{
        id: openFileDialog
        title: "Выберите файл для разбора"
        onAccepted: {
            client.setFilePath(openFileDialog.fileUrl.toString().slice(8))  //Путь до выбранного файла передаётся в метод setFilePath класса Client
            pathFile.text = openFileDialog.fileUrl.toString().slice(8)
        }
    }

    MessageDialog{
        id: msgBox
    }

    Column {
        id: column
        height: 600
        width: 360

        ScrollView {
            id: scrollView
            anchors.top: rectangle.bottom
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            Text {
                id: result
                text: qsTr("Результат")
                anchors.fill: parent
                font.pixelSize: 12
                anchors.bottomMargin: 15
                anchors.leftMargin: 15

            }
        }

        Rectangle {
            id: rectangle
            height: 245
            color: "#ffffff"
            border.width: 0
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top


            TextInput {
                id: ipaddr
                width: 113
                height: 25
                text: "192.168.0.1"
                anchors.left: parent.left
                anchors.top: text1.bottom
                font.pixelSize: 12
                anchors.leftMargin: 15
                anchors.topMargin: 0
            }

            Text {
                id: text1
                width: 113
                height: 22
                text: qsTr("IP адрес сервера")
                anchors.left: parent.left
                anchors.top: parent.top
                font.pixelSize: 12
                anchors.topMargin: 15
                anchors.leftMargin: 16
            }

            TextInput {
                id: port
                width: 30
                height: 25
                text: "2323"
                anchors.left: ipaddr.right
                anchors.top: text2.bottom
                font.pixelSize: 12
                anchors.leftMargin: 15
                anchors.topMargin: 0
            }

            Text {
                id: text2
                width: 35
                height: 22
                text: qsTr("Порт")
                anchors.left: text1.right
                anchors.top: parent.top
                font.pixelSize: 12
                anchors.leftMargin: 15
                anchors.topMargin: 15
            }

            Button {
                id: connecting
                width: 118
                height: 24
                text: qsTr("Подключение")
                anchors.left: parent.left
                anchors.top: ipaddr.bottom
                anchors.topMargin: 18
                anchors.leftMargin: 15
                onClicked: client.clickedConnectingButton(ipaddr.text, port.text)
            }

            Text {
                id: stateLine
                width: 73
                height: 16
                text: clientProp.status
                anchors.left: connecting.right
                anchors.top: port.bottom
                color: clientProp.color
                font.pixelSize: 12
                anchors.leftMargin: 7
                anchors.topMargin: 22
            }

            Text {
                id: text4
                y: 140
                width: 78
                height: 18
                text: qsTr("Путь к файлу")
                anchors.left: parent.left
                anchors.bottom: pathFile.top
                font.pixelSize: 12
                anchors.leftMargin: 16
                anchors.bottomMargin: 11
            }

            TextInput {
                id: pathFile
                y: 169
                width: 250
                height: 23
                text: qsTr("...")
                anchors.left: parent.left
                anchors.bottom: send.top
                font.pixelSize: 12
                anchors.bottomMargin: 25
                anchors.leftMargin: 15
            }

            Button {
                id: openFile
                y: 167
                width: 73
                height: 27
                text: qsTr("Открыть")
                anchors.left: pathFile.right
                anchors.bottom: parent.bottom
                anchors.leftMargin: 15
                anchors.bottomMargin: 51
                onClicked: openFileDialog.open()
            }

            Button {
                id: send
                y: 217
                width: 212
                height: 20
                text: qsTr("Отправить файл на сервер")
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                anchors.leftMargin: 16
                anchors.bottomMargin: 8
                onClicked: client.sendToServer()
            }
        }

    }
}


