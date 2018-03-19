#include "VR_ColorCalibrator.h"

VR_ColorCalibrator::VR_ColorCalibrator(QWidget *parent)
	: QDialog(parent),
	mainWidget{new QWidget()},
	mainLayout{new QHBoxLayout()},
	videoTabs{new QTabWidget()},
	videoLabel{new QLabel()},
	getFrameProcess{new VR_FrameGrabberProcess(this)}
{
	videoTabs->addTab(videoLabel, "raw");
	videoTabs->addTab(new QLabel("lolololo"), "blur");
	videoTabs->addTab(new QLabel("lol"), "treshold");
	mainLayout->addWidget(videoTabs);
	setLayout(mainLayout);

	connect(getFrameProcess, &VR_FrameGrabberProcess::frameAvailable, this, &VR_ColorCalibrator::receiveFrame);
}

VR_ColorCalibrator::~VR_ColorCalibrator()
{
}

void VR_ColorCalibrator::receiveFrame(QImage frame)
{
	videoLabel->setPixmap(getFrameProcess->getPixmap());
}
