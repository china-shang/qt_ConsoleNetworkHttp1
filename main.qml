import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import networkmanger 1.0

ApplicationWindow{

    width: 400
    height: 400
    visible: true
    title: qsTr("title")

    Rectangle{
        anchors.centerIn: parent
        color: "red"
        width: 300
        height: 300
        MouseArea{
            anchors.fill: parent
            onClicked: {
                manger.login()
            }
        }
    }
}
