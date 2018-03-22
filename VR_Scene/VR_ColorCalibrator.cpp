#include "VR_ColorCalibrator.h"

VR_ColorCalibrator::VR_ColorCalibrator(QWidget *parent)
	: QDialog(parent),
	mainWidget{new QWidget()},
	mainLayout{new QHBoxLayout()},
	videoTabs{new QTabWidget()},
	blurWidget{ new QWidget()},
	thresholdWidget{ new QWidget()},
	rawVideoLabel{ new QLabel() },
	blurVideoLabel{ new QLabel() },
	threshVideoLabel{new QLabel()},
	imageProcessor{ new VR_ImageProcessor(parent)},
	hueScrollBar{ new QLowHighScrollBar("Hue",parent) },
	saturationScrollBar{ new QLowHighScrollBar("Saturation",parent) },
	valueScrollBar{ new QLowHighScrollBar("Value",parent)},
	thresholdWidgetLayout{ new QVBoxLayout() },
	blurWidgetLayout{ new QVBoxLayout()},
	currentFrameType{VR_ImageProcessor::ProcessedImageLabel::RAW},
	blurWidgdetLabel{new QLabel("Blur")},
	blurScrollBar{new QScrollBar(Qt::Horizontal,parent)}
{
	videoTabs->addTab(rawVideoLabel, "raw");
	videoTabs->addTab(blurVideoLabel, "blur");
	videoTabs->addTab(threshVideoLabel, "threshold");

	/* Blur widget setup*/
	blurWidget->setLayout(blurWidgetLayout);
	blurWidgetLayout->addWidget(blurWidgdetLabel);
	blurWidgetLayout->addWidget(blurScrollBar);
	blurWidget->hide();


	/* Threshold widget setup*/
	hueScrollBar->setRange(0, 180);
	saturationScrollBar->setRange(0, 255);
	valueScrollBar->setRange(0, 255);
	thresholdWidget->setLayout(thresholdWidgetLayout);
	thresholdWidgetLayout->addWidget(hueScrollBar);
	thresholdWidgetLayout->addWidget(saturationScrollBar);
	thresholdWidgetLayout->addWidget(valueScrollBar);
	thresholdWidget->hide();

	mainLayout->addWidget(videoTabs);
	mainLayout->addWidget(blurWidget);
	mainLayout->addWidget(thresholdWidget);
	setLayout(mainLayout);

	connect(imageProcessor, &VR_ImageProcessor::processDone, this, &VR_ColorCalibrator::receiveFrame);
	connect(videoTabs, &QTabWidget::currentChanged, this, &VR_ColorCalibrator::tabChanged);

	connect(hueScrollBar, &QLowHighScrollBar::actionTriggered, this, &VR_ColorCalibrator::thresholdValueChanged);
	connect(saturationScrollBar, &QLowHighScrollBar::actionTriggered, this, &VR_ColorCalibrator::thresholdValueChanged);
	connect(valueScrollBar, &QLowHighScrollBar::actionTriggered, this, &VR_ColorCalibrator::thresholdValueChanged);

	connect(this, &VR_ColorCalibrator::newThresholdValues, imageProcessor, &VR_ImageProcessor::newThresholdValues);
}

VR_ColorCalibrator::~VR_ColorCalibrator()
{
}

VR_ThresholdValues VR_ColorCalibrator::thresholdValues()
{
	return currentThresholdValues;
}

void VR_ColorCalibrator::tabChanged()
{
	switch (videoTabs->currentIndex()) {
	case 0: currentFrameType = VR_ImageProcessor::ProcessedImageLabel::RAW;
		thresholdWidget->hide();
		blurWidget->hide();
		break;
	case 1: currentFrameType = VR_ImageProcessor::ProcessedImageLabel::BLURRED;
		thresholdWidget->hide();
		blurWidget->show();
		break;
	case 2: currentFrameType = VR_ImageProcessor::ProcessedImageLabel::THRESHOLDED;
		thresholdWidget->show();
		blurWidget->hide();
		break;
	}


}

void VR_ColorCalibrator::thresholdValueChanged(int lowVal, int highVal)
{
	currentThresholdValues.minHue = hueScrollBar->lowValue();
	currentThresholdValues.maxHue = hueScrollBar->highValue();
	currentThresholdValues.minSaturation = saturationScrollBar->lowValue();
	currentThresholdValues.maxSaturation = saturationScrollBar->highValue();
	currentThresholdValues.minValue = valueScrollBar->lowValue();
	currentThresholdValues.maxValue = valueScrollBar->highValue();
	emit newThresholdValues(currentThresholdValues);
}

void VR_ColorCalibrator::receiveFrame()
{
	rawVideoLabel->setPixmap(imageProcessor->getPixmap(currentFrameType));
	blurVideoLabel->setPixmap(imageProcessor->getPixmap(currentFrameType));
	threshVideoLabel->setPixmap(imageProcessor->getPixmap(currentFrameType));

}
