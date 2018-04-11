#include "VR_BlobProcess.h"



VR_BlobProcess::VR_BlobProcess(QObject * parent) :
	VR_ImageProcess(parent)
{
}


VR_BlobProcess::~VR_BlobProcess()
{
}

void VR_BlobProcess::process(const Mat & imgIn, Mat & imgOut)
{
	// Setup SimpleBlobDetector parameters.
	SimpleBlobDetector::Params params;

	params.filterByArea = true;
	params.minArea = 100;
	params.maxArea = 1000;
	params.filterByColor = true;
	params.blobColor = 255;

#if CV_MAJOR_VERSION < 3   // If you are using OpenCV 2

	// Set up detector with params
	SimpleBlobDetector detector(params);

	// You can use the detector this way
	// detector.detect( im, keypoints);

#else

	// Set up detector with params
	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

	// SimpleBlobDetector::create creates a smart pointer. 
	// So you need to use arrow ( ->) instead of dot ( . )
	// detector->detect( im, keypoints);

#endif
	

	// Read image
	Mat im = imgIn;

	std::vector<cv::KeyPoint> keypoints;

	detector->detect(im, keypoints);

	// Draw detected blobs as red circles.
	// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
	Mat im_with_keypoints;
	drawKeypoints(im, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imgOut = im_with_keypoints;

	
}
