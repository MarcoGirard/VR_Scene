#include "VR_BlobProcess.h"
#include <QTextStream>


VR_BlobProcess::VR_BlobProcess(QObject * parent) :
	VR_ImageProcess(parent)
{
}


VR_BlobProcess::~VR_BlobProcess()
{
}

void VR_BlobProcess::process(const cv::Mat & imgIn, cv::Mat & imgOut)
{

	// Setup SimpleBlobDetector parameters.
	cv::SimpleBlobDetector::Params params;

	params.filterByArea = true;
	params.minArea = 1000;
	params.maxArea = 40000;
	params.filterByColor = true;
	params.blobColor = 255;


#if CV_MAJOR_VERSION < 3   // If you are using OpenCV 2

	// Set up detector with params
	SimpleBlobDetector detector(params);

	// You can use the detector this way
	// detector.detect( im, keypoints);

#else

	// Set up detector with params
	cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);

	// SimpleBlobDetector::create creates a smart pointer. 
	// So you need to use arrow ( ->) instead of dot ( . )
	// detector->detect( im, keypoints);

#endif
	

	detector->detect(imgIn, keypoints);
	if (keypoints.size() > 1) {
		int x1, y1, x2, y2;
		x1 = keypoints.at(0).pt.x;
		x2 = keypoints.at(1).pt.x;
		y1 = keypoints.at(0).pt.y;
		y2 = keypoints.at(1).pt.y;
		mX = (x1 + x2) / 2;
		mY = (y1 + y2) / 2;
		mZ = pow((x2 - x1), 2) + pow((y2 - y1), 2);
	}
	
	cv::Mat imgInDummy;
	imgIn.copyTo(imgInDummy);
	cvtColor(imgInDummy, imgInDummy, CV_RGB2GRAY);
	
	drawKeypoints(imgInDummy, keypoints, imgOut, cv::Scalar(255,128,128), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
}

bool VR_BlobProcess::isTracked()
{
	if (keypoints.size() == 2) {
		tracked = true;
	} else {
		tracked = false;
	}
	return tracked;
}
