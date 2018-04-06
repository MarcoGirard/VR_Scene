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
	activeVideoLabel{new QLabel(parent)},
	imageProcessor{ new VR_ImageProcessor(parent)},
	hueScrollBar{ new QLowHighScrollBar("Hue",parent) },
	saturationScrollBar{ new QLowHighScrollBar("Saturation",parent) },
	valueScrollBar{ new QLowHighScrollBar("Value",parent)},
	thresholdWidgetLayout{ new QVBoxLayout() },
	blurWidgetLayout{ new QVBoxLayout()},
	currentFrameType{VR_ImageProcessor::ProcessedImageType::RAW},
	blurWidgdetLabel{new QLabel("Blur")},
	blurSpinbox{new QSpinBox(parent)},
	saveBtn{new QPushButton("Enregistrer l'image", this)},
	chkBoxProcess{new QCheckBox(parent)}
{

	chkBoxProcess->setCheckState(Qt::Checked);
	/* Video tabs setup */
	videoTabs->addTab(rawVideoLabel, "raw");
	videoTabs->addTab(blurVideoLabel, "blur");
	videoTabs->addTab(threshVideoLabel, "threshold");
	videoTabs->addTab(erodedVideoLabel, "eroded");
	activeVideoLabel = rawVideoLabel; // start with raw cam input as first display

	/* Blur widget setup*/
	blurSpinbox->setRange(1, 13);
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
	saturationScrollBar->setRange(0, 255);
	valueScrollBar->setRange(0, 255);
	thresholdWidget->setLayout(thresholdWidgetLayout);
	thresholdWidgetLayout->addWidget(hueScrollBar);
	thresholdWidgetLayout->addWidget(saturationScrollBar);
	thresholdWidgetLayout->addWidget(valueScrollBar);
	thresholdWidgetLayout->addStretch();
	thresholdWidget->hide();

	mainLayout->addWidget(videoTabs);
	mainLayout->addWidget(blurWidget);
	mainLayout->addWidget(thresholdWidget);
	mainLayout->addWidget(saveBtn);
	mainLayout->addWidget(chkBoxProcess);
	setLayout(mainLayout);

	connect(saveBtn, &QPushButton::clicked, this, &VR_ColorCalibrator::saveImage);
	connect(imageProcessor, &VR_ImageProcessor::processDone, this, &VR_ColorCalibrator::receiveFrame);
	connect(videoTabs, &QTabWidget::currentChanged, this, &VR_ColorCalibrator::tabChanged);

	connect(hueScrollBar, &QLowHighScrollBar::valueUpdated, this, &VR_ColorCalibrator::thresholdValueChanged);
	connect(saturationScrollBar, &QLowHighScrollBar::valueUpdated, this, &VR_ColorCalibrator::thresholdValueChanged);
	connect(valueScrollBar, &QLowHighScrollBar::valueUpdated, this, &VR_ColorCalibrator::thresholdValueChanged);

	connect(this, &VR_ColorCalibrator::newThresholdValues, imageProcessor, &VR_ImageProcessor::newThresholdValues);
	connect(blurSpinbox, QOverload<int>::of(&QSpinBox::valueChanged), imageProcessor, &VR_ImageProcessor::kernelSizeUpdated);
	
	connect(chkBoxProcess, &QCheckBox::toggled, this, &VR_ColorCalibrator::processStateChanged);
	thresholdValueChanged();

	loadImage();
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
	}
}

// QUESTION POUR JC : Est-ce plus clean de faire tout le temps les 6 appels? 
//					  ou je fais une slot pour chaque?
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

void VR_ColorCalibrator::newKernelSize()
{
	emit kernelSizeUpdated(blurSpinbox->value());
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
		imageProcessor->setProcess(true);
	} else {
		imageProcessor->setProcess(false);
	}
}

void VR_ColorCalibrator::loadImage()
{
	QImage * img = new QImage(getImagePath());
	imageProcessor->setStaticImg(img);
}

QString VR_ColorCalibrator::getImagePath()
{
	return QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
}

void VR_ColorCalibrator::receiveFrame()
{
	activeVideoLabel->setPixmap(imageProcessor->getPixmap(currentFrameType));
}
