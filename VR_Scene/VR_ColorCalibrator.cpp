#include "VR_ColorCalibrator.h"


VR_ColorCalibrator::VR_ColorCalibrator(QWidget *parent)
	: QDialog(parent),
	mainWidget{new QWidget(parent)},
	mainLayout{new QHBoxLayout(parent)},
	videoTabs{new QTabWidget(parent)},
	blurWidget{ new QWidget(parent)},
	thresholdWidget{ new QWidget(parent)},
	rawVideoLabel{ new QLabel(parent) },
	blurVideoLabel{ new QLabel(parent) },
	threshVideoLabel{ new QLabel(parent) },
	erodedVideoLabel{ new QLabel(parent) },
	trackingStatusLight{ new QLabel(parent) },
	blobInfo{ new QLabel(parent)},
	activeVideoLabel{ nullptr },
	blobVideoLabel{new QLabel(parent)},
	hueScrollBar{ new QLowHighScrollBar("Hue",parent) },
	saturationScrollBar{ new QLowHighScrollBar("Saturation",parent) },
	valueScrollBar{ new QLowHighScrollBar("Value",parent)},
	thresholdWidgetLayout{ new QVBoxLayout() },
	blurWidgetLayout{ new QVBoxLayout()},
	addWidgetLayout{ new QVBoxLayout()},
	currentFrameType{VR_ImageProcessor::ProcessedImageType::RAW},
	blurWidgdetLabel{new QLabel("Blur", parent)},
	blurSpinbox{new QSpinBox(parent)},
	saveBtn{new QPushButton("Enregistrer l'image", parent)},
	chkBoxProcess{ new QCheckBox(parent) },
	chkBoxDetect{new QCheckBox(parent)}
{

	chkBoxProcess->setCheckState(Qt::Checked);
	/* Video tabs setup */
	videoTabs->addTab(rawVideoLabel, "raw");
	videoTabs->addTab(blurVideoLabel, "blur");
	videoTabs->addTab(threshVideoLabel, "threshold");
	videoTabs->addTab(erodedVideoLabel, "eroded");
	videoTabs->addTab(blobVideoLabel, "blobs");
	activeVideoLabel = rawVideoLabel; // start with raw cam input as first display

	/* Blur widget setup*/
	blurSpinbox->setRange(3, 13);
	blurSpinbox->setSingleStep(2);
	blurSpinbox->setValue(3);
	blurSpinbox->setToolTip(QString("min: 1 (pas de blur)\nmax: 13\nAttention, ne pas changer\nla valeur trop rapidement!"));
	blurWidget->setLayout(blurWidgetLayout);
	blurWidgetLayout->addWidget(blurWidgdetLabel);
	blurWidgetLayout->addWidget(blurSpinbox);
	blurWidgetLayout->addStretch();
	blurWidget->hide();

	/* Threshold widget setup*/
	hueScrollBar->setRange(0, 255);
	hueScrollBar->set(89, 128);
	saturationScrollBar->setRange(0, 255);
	saturationScrollBar->set(46, 205);
	valueScrollBar->setRange(0, 255);
	valueScrollBar->set(46, 188);
	thresholdWidget->setLayout(thresholdWidgetLayout);
	thresholdWidgetLayout->addWidget(hueScrollBar);
	thresholdWidgetLayout->addWidget(saturationScrollBar);
	thresholdWidgetLayout->addWidget(valueScrollBar);
	thresholdWidgetLayout->addStretch();
	thresholdWidget->hide();

	/* trackingStatusLight setup*/
	trackingStatusLight->setFixedSize(QSize(12, 12));
	
	trackingStatusLight->setAutoFillBackground(true);
	setIndicatorLightColor(trackingStatusLight);
	
	
	mainLayout->addWidget(videoTabs);
	mainLayout->addWidget(blurWidget);
	mainLayout->addWidget(thresholdWidget);
	mainLayout->addLayout(addWidgetLayout);
	addWidgetLayout->addWidget(saveBtn);
	addWidgetLayout->addWidget(chkBoxProcess);
	addWidgetLayout->addWidget(chkBoxDetect);
	addWidgetLayout->addWidget(blobInfo);
	addWidgetLayout->addWidget(trackingStatusLight);
	setLayout(mainLayout);

	connect(saveBtn, &QPushButton::clicked, this, &VR_ColorCalibrator::saveImage);
	connect(&imageProcessor, &VR_ImageProcessor::processDone, this, &VR_ColorCalibrator::receiveFrame);
	connect(videoTabs, &QTabWidget::currentChanged, this, &VR_ColorCalibrator::tabChanged);

	connect(hueScrollBar, &QLowHighScrollBar::valueUpdated, this, &VR_ColorCalibrator::thresholdValueChanged);
	connect(saturationScrollBar, &QLowHighScrollBar::valueUpdated, this, &VR_ColorCalibrator::thresholdValueChanged);
	connect(valueScrollBar, &QLowHighScrollBar::valueUpdated, this, &VR_ColorCalibrator::thresholdValueChanged);

	connect(this, &VR_ColorCalibrator::newThresholdValues, &imageProcessor, &VR_ImageProcessor::updateThresholdValues);
	connect(blurSpinbox, QOverload<int>::of(&QSpinBox::valueChanged), &imageProcessor, &VR_ImageProcessor::kernelSizeUpdated);
	
	connect(chkBoxProcess, &QCheckBox::toggled, this, &VR_ColorCalibrator::processStateChanged);
	connect(chkBoxDetect, &QCheckBox::toggled, &imageProcessor, &VR_ImageProcessor::toggleBlobDetection);

	connect(&imageProcessor, &VR_ImageProcessor::sendViewerCoordinates, this, &VR_ColorCalibrator::receiveViewerCoordinates);

	thresholdValueChanged();

}

VR_ThresholdValues VR_ColorCalibrator::thresholdValues()
{
	return currentThresholdValues;
}

void VR_ColorCalibrator::tabChanged()
{

	switch (videoTabs->currentIndex()) {
	case 0: currentFrameType = VR_ImageProcessor::ProcessedImageType::RAW;
		thresholdWidget->hide();
		blurWidget->hide();
		activeVideoLabel = rawVideoLabel;
		break;
	case 1: currentFrameType = VR_ImageProcessor::ProcessedImageType::BLURRED;
		thresholdWidget->hide();
		blurWidget->show();
		activeVideoLabel = blurVideoLabel;
		break;
	case 2: currentFrameType = VR_ImageProcessor::ProcessedImageType::THRESHOLDED;
		thresholdWidget->show();
		blurWidget->hide();
		activeVideoLabel = threshVideoLabel;
		break;
	case 3: currentFrameType = VR_ImageProcessor::ProcessedImageType::ERODED;
		thresholdWidget->hide();
		blurWidget->hide();
		activeVideoLabel = erodedVideoLabel;
		break; 
	case 4: currentFrameType = VR_ImageProcessor::ProcessedImageType::BLOB;
		thresholdWidget->hide();
		blurWidget->hide();
		activeVideoLabel = blobVideoLabel;
		break;
	}
}

void VR_ColorCalibrator::thresholdValueChanged()
{
	currentThresholdValues.minHue = hueScrollBar->lowValue();
	currentThresholdValues.maxHue = hueScrollBar->highValue();
	currentThresholdValues.minSaturation = saturationScrollBar->lowValue();
	currentThresholdValues.maxSaturation = saturationScrollBar->highValue();
	currentThresholdValues.minValue = valueScrollBar->lowValue();
	currentThresholdValues.maxValue = valueScrollBar->highValue();
	emit newThresholdValues(currentThresholdValues);
}

void VR_ColorCalibrator::saveImage()
{
	++savedImgCount;
	
	string frameName = "frame_" + std::to_string(savedImgCount) + ".jpg";
	activeVideoLabel->pixmap()->save(QString::fromStdString(frameName));
}

void VR_ColorCalibrator::processStateChanged()
{
	if (chkBoxProcess->isChecked()) {
		imageProcessor.setProcess(true);
	} else {
		imageProcessor.setProcess(false);
	}
}

void VR_ColorCalibrator::receiveViewerCoordinates(int x, int y, int z)
{
	string text = "[X:" + std::to_string(x) + ",Y:" + std::to_string(y) + ",Z:" + std::to_string(z) + "]";
	blobInfo->setText(QString::fromStdString(text));
	emit sendViewerCoordinates(x, y, z);
}

QString VR_ColorCalibrator::getImagePath()
{
	return QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
}

void VR_ColorCalibrator::process()
{
	imageProcessor.process();
}

void VR_ColorCalibrator::setIndicatorLightColor(QLabel * label)
{
	QPalette palette;
	if (imageProcessor.isTracked()) {
		palette.setColor(QPalette::Window, Qt::green);
	}
	else {
		palette.setColor(QPalette::Window, Qt::red);
	}
	label->setPalette(palette);

}

void VR_ColorCalibrator::receiveFrame()
{
	setIndicatorLightColor(trackingStatusLight);
	activeVideoLabel->setPixmap(imageProcessor.getPixmap(currentFrameType));
}
