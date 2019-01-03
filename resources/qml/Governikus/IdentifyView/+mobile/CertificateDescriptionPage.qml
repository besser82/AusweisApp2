import QtQuick 2.10

import Governikus.Global 1.0
import Governikus.TitleBar 1.0
import Governikus.View 1.0

SectionPage
{
	id: root
	leftTitleBarAction: TitleBarAction { state: "back"; onClicked: firePop() }
	headerTitleBarAction: TitleBarAction { text: name; font.bold: true }

	property string name

	content: Item
	{
		height: pane.height + 2 * Constants.component_spacing
		width: root.width

		Column
		{
			anchors.fill: parent
			anchors.margins: Constants.component_spacing

			Pane {
				id: pane
				title: qsTr("Provider Information") + settingsModel.translationTrigger

				Repeater {
					id: listView
					model: certificateDescriptionModel

					LabeledText {
						id: delegate
						label: model.label
						text: model.text
						textFormat: Text.PlainText
						width: parent.width
					}
				}
			}
		}
	}
}