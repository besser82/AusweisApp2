/*
 * \copyright Copyright (c) 2017-2020 Governikus GmbH & Co. KG, Germany
 */

import QtQuick 2.10

import Governikus.Style 1.0

Rectangle {
	id: splashScreen

	visible: true
	anchors.fill: parent

	color: Style.color.background

	signal fireHiding()

	readonly property var startTime: new Date().getTime()

	Image {
		source: "qrc:/images/npa.svg"
		height: Math.min(parent.width, parent.height) * 0.5
		width: height
		fillMode: Image.PreserveAspectFit
		anchors.centerIn: parent
		visible: parent.visible
	}

	Rectangle {
		id: titleBar

		anchors {
			top: parent.top
			left: parent.left
			right: parent.right
		}
		height: plugin.safeAreaMargins.top

		color: Style.color.accent
	}

	function hide() {
		if (!splashScreen.visible) {
			return
		}

		var TIMEOUT = 1000;
		var remaining = startTime + TIMEOUT - new Date().getTime();
		var timer = Qt.createQmlObject("import QtQuick 2.10; Timer {}", splashScreen);
		timer.interval = remaining > 0 ? remaining : 0;
		timer.repeat = false;
		timer.triggered.connect(function(){
			splashScreen.visible = false
			fireHiding()
		})
		timer.start();
	}
}
