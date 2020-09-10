import QtQuick 2.12
import QtQuick.Controls 2.12
import KLib 1.0

Item {
    width: 500
    height: 300
    Column {
        anchors.fill: parent

        KGraphics_Test {
            id: test
        }

        KAudio_Test {
            id: audio_test
        }

        Row {
            Slider {
                from: 0
                to: 100
                onValueChanged: {
                    audio_test.phase = value;
                }
                width: 100
            }

            Slider {
                from: 0
                to: 1
                onValueChanged: {
                    audio_test.amplitude = value;
                }
            }
            Slider {
                from: 0
                to: 20
                onValueChanged: {
                    audio_test.frequency = Math.pow(2, value);
                }
            }

            Timer {
                interval: 1000
                running: true
                repeat: true
                onTriggered: {
                    lamp.state = !lamp.state;
                }
            }

            KLamp {
                id: lamp
                text: "GG"
            }
        }

        Row {
            Button {
                text: "cuttent: " + test.boolValue
                onClicked: {
                    test.boolValue = !test.boolValue;
                }
            }
            Slider {
                from: 0
                to: 1
                onValueChanged: {
                    test.amplitude = value;
                }
            }
            Slider {
                from: 0
                to: 100
                onValueChanged: {
                    test.freq = Math.pow(2, value);
                }
            }
        }

        Component.onCompleted: {
            test.installMonitor(mon);
        }

        Rectangle {
            width: 500
            height: 180
            color: "#444444"

            KAfterShiningMonitor {
                anchors.fill: parent
                interval: 20
                contentPaintedItem: KHistoryMonitor {
                    max: 1.5
                    min: -1.5
                    id: mon
                }
            }
        }

        KFlexibleModel_Test{
            id: kFlexibleModel_Test

            //Component.onCompleted: cppTest()
        }
    }
}
