import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.5

Item {
    width: 500
    height: 300

//    ListView {
//        anchors { fill: parent; margins: 20 }
//        model: sqlQueryUserConfigModel
//        delegate: Text {
//            text: uk_name + ", " + fk_workgroup_id + ", " + email + ", " + sms + ", " + tag
//        }
//    }

    Component {
        id: editableDelegate
        Item {
            Text {
                width: parent.width
                anchors.margins: 4
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                elide: styleData.elideMode
                text: styleData.value !== undefined ? styleData.value : ""
                color: styleData.textColor
                visible: !styleData.selected
            }
            Loader {
                id: loaderEditor
                anchors.fill: parent
                anchors.margins: 4
                Connections {
                    target: loaderEditor.item
                    onAccepted: {
                        if (typeof styleData.value === 'number')
                            largeModel.setProperty(styleData.row, styleData.role, Number(parseFloat(loaderEditor.item.text).toFixed(0)))
                        else
                            largeModel.setProperty(styleData.row, styleData.role, loaderEditor.item.text)
                    }
                }
                sourceComponent: styleData.selected ? editor : null
                Component {
                    id: editor
                    TextInput {
                        id: textinput
                        color: styleData.textColor
                        text: styleData.value
                        MouseArea {
                            id: mouseArea
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: textinput.forceActiveFocus()
                        }
                    }
                }
            }
        }
    }

    TableView {
        id: userConfigModel

        anchors.fill: parent

//        function showWidth(x) {
//            return x + userConfigModel.width
//        }

        TableViewColumn {
            role: "_id"
            title: "ID"
            width: 50
        }
        TableViewColumn {
            role: "timestamp"
            title: "Timestamp"
            width: 150
        }
        TableViewColumn {
            role: "_data"
            title: "Data"
            width: 100
        }
        TableViewColumn {
            role: "note"
            title: "Note"
            width: 100
        }
        TableViewColumn {
            role: "uk_name"
            title: "Name"
            width: 100
        }
        TableViewColumn {
            role: "fk_workgroup_id"
            title: "Workgroup ID"
            width: 50
        }
        TableViewColumn {
            role: "email"
            title: "Email"
            width: 100
        }
        TableViewColumn {
            role: "sms"
            title: "SMS"
            width: 100
        }
        TableViewColumn {
            role: "tag"
            title: "Tag"
            width: 100
        }

        model: sqlQueryUserConfigModel
        alternatingRowColors: true

        itemDelegate: {
            return editableDelegate;
        }
    }
}
