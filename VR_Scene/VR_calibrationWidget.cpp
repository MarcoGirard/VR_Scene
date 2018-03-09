#include "VR_calibrationWidget.h"
#include <qlabel.h>

VR_calibrationWidget::VR_calibrationWidget()
	: videoTabs{new QTabWidget()},
	mainLayout{new QHBoxLayout()}
{
	videoTabs->addTab(new QLabel("lol"), "raw");
	videoTabs->addTab(new QLabel("lolololo"), "blur");
	videoTabs->addTab(new QLabel("lol"), "treshold");
	mainLayout->addWidget(videoTabs);
	setLayout(mainLayout);


}

VR_calibrationWidget::~VR_calibrationWidget()
{
}
