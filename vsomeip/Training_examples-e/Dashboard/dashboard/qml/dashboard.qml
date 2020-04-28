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

import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

Window {
    id: root
    visible: true
    width: 1024
    height: 600


    color: "#181818"
    //title: "Qt Quick Extras Demo"

    ValueSource {
        id: valueSource
    }


    // Dashboards are typically in a landscape orientation, so we need to ensure
    // our height is never greater than our width.
    Item {
        id: container
        width: root.width
        height: Math.min(root.width, root.height)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: 0

        Row {
            id: gaugeRow
            anchors.verticalCenterOffset: -7
            anchors.horizontalCenterOffset: -5
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: container.width * 0.02

        }

        Text {
            id: text1
            x: 417
            y: 103
            width: 151
            height: 34
            color: "#f90f0f"

            text:"ECLABS "
            font.bold: true
            styleColor: "#f33939"
            textFormat: Text.RichText
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 18
        }

        CircularGauge {
            id: circularGauge2
            x: 56
            y: 247
            width: 240
            height: 152
        }

        CircularGauge {
            id: circularGauge1
            x: 136
            y: 373
            width: 272
            height: 253
            anchors.horizontalCenterOffset: 340
            anchors.horizontalCenter: parent.horizontalCenter
            scale: 0.6
            value: Cluster.temp/10

            maximumValue: 1
            z: -1
            Behavior on value {
                NumberAnimation{
                    duration: 2000;
                }

            }
            style: IconGaugeStyle {
                id: tempGaugeStyle

                icon: "qrc:/images/temperature-icon.png"
                maxWarningColor: Qt.rgba(0.5, 0, 0, 1)

                tickmarkLabel: Text {
                    color: "white"
                    visible: styleData.value === 0 || styleData.value === 1
                    font.pixelSize: tempGaugeStyle.toPixels(0.225)
                    text: styleData.value === 0 ? "C" : (styleData.value === 1 ? "H" : "")
                }
            }
        }

        CircularGauge {
            id: fuelGauge
            x: 250
            y: 143
            width: 272
            height: 149
            value: Cluster.fuel/10
            maximumValue: 1
            anchors.rightMargin: 707
            anchors.right: circularGauge1.right
            anchors.topMargin: 432
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 54
            Behavior on value {
                NumberAnimation{
                    duration: 2000;
                }

            }
            style: IconGaugeStyle {
                id: fuelGaugeStyle

                icon: "qrc:/images/fuel-icon.png"
                minWarningColor: Qt.rgba(0.5, 0, 0, 1)

                tickmarkLabel: Text {
                    color: "white"
                    visible: styleData.value === 0 || styleData.value === 1
                    font.pixelSize: fuelGaugeStyle.toPixels(0.225)
                    text: styleData.value === 0 ? "E" : (styleData.value === 1 ? "F" : "")
                }
            }
        }

        TurnIndicator {
            id: rightIndicator
            x: 965
            y: 273
            anchors.verticalCenter: parent.verticalCenter
            width: height
            height: container.height * 0.1 - gaugeRow.spacing
            anchors.verticalCenterOffset: 1

            direction: Qt.RightArrow

            on: Cluster.r_value>0 ? true:false;
                //valueSource.turnSignal == Qt.RightArrow

        } TurnIndicator {
            id: leftIndicator
            x: 14
            y: 273
            anchors.verticalCenter: parent.verticalCenter
            width: height
            height: container.height * 0.1 - gaugeRow.spacing
            anchors.verticalCenterOffset: 3

            direction: Qt.LeftArrow
            on: Cluster.l_value>0 ? true:false;
        }


        CircularGauge {
            id: speedometer
            x: 292
            y: 143
            width: 400
            height: 400
            //value: valueSource.kph
            value: Cluster.speed
            anchors.verticalCenter: parent.verticalCenter
            maximumValue: 240
            // We set the width to the height, because the height will always be
            // the more limited factor. Also, all circular controls letterbox
            // their contents to ensure that they remain circular. However, we
            // don't want to extra space on the left and right of our gauges,
            // because they're laid out horizontally, and that would create
            // large horizontal gaps between gauges on wide screens.
            anchors.verticalCenterOffset: 23
            scale: 0.9
            Behavior on value {
                NumberAnimation{
                    duration: 500;
                }

            }

            style: DashboardGaugeStyle {}
        }


        CircularGauge {
            id: tachometer
            x: 732
            y: 470
            width: 240
            height: 152
            anchors.verticalCenterOffset: 23
            value: Cluster.rpm
            maximumValue: 8
            anchors.verticalCenter: parent.verticalCenter
            Behavior on value {
                NumberAnimation{
                    duration: 1000;
                }

            }
            style: TachometerStyle {}
        }
    }
}
