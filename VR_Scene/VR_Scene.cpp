#include "VR_Scene.h"

VR_Scene::VR_Scene(QWidget *parent)
	: QMainWindow(parent),
	btnColorCalib{new QPushButton("Color Calibration",this)},
	btnSpaceCalib{ new QPushButton("Space Calibration",this) },
	btnStartScene{ new QPushButton("Start Interactive Scene",this) },
	mainLayout{new QVBoxLayout},
	mainWidget{new QWidget},
	camSelection{new QComboBox}
{
	ui.setupUi(this);
	setFixedSize(QSize(250, 300));

	mainLayout->addWidget(camSelection);
	mainLayout->addWidget(btnColorCalib);
	mainLayout->addWidget(btnSpaceCalib);
	mainLayout->addWidget(btnStartScene);

	mainWidget->setLayout(mainLayout);
	setCentralWidget(mainWidget);

	connect(btnColorCalib, &QPushButton::pressed, this, &VR_Scene::startColorCalibrator);

	// POUR LE DEVELOPPEMENT,
	startColorCalibrator();
}

void VR_Scene::startColorCalibrator()
{
	colorCalibrator = new VR_ColorCalibrator(this);
	colorCalibrator->exec();
}
