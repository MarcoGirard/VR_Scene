#include "VR_ErodeProcess.h"



VR_ErodeProcess::VR_ErodeProcess(QObject * parent) :
	VR_ImageProcess(parent)
{
}


VR_ErodeProcess::~VR_ErodeProcess()
{
}
// https://docs.opencv.org/2.4/doc/tutorials/imgproc/erosion_dilatation/erosion_dilatation.html
void VR_ErodeProcess::process(const cv::Mat & imgIn, cv::Mat & imgOut)
{
	int erosionSize{ 5 };
	/*int erosion_type;
	if (erosion_elem == 0) { erosion_type = MORPH_RECT; }
	else if (erosion_elem == 1) { erosion_type = MORPH_CROSS; }
	else if (erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }*/

	cv::Mat kernel = getStructuringElement(cv::MORPH_RECT,
		cv::Size(2 * erosionSize + 1, 2 * erosionSize + 1),
		cv::Point(erosionSize, erosionSize));

	cv::erode(imgIn, imgOut, kernel);
}
