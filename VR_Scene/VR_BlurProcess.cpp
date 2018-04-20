#include "VR_BlurProcess.h"



VR_BlurProcess::VR_BlurProcess(QObject * parent) :
	VR_ImageProcess(parent)
{
}


VR_BlurProcess::~VR_BlurProcess()
{
}


//https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_circle/hough_circle.html

void VR_BlurProcess::process(const Mat &imgIn, Mat &imgOut)
{
	imgIn.copyTo(imgOut);
	
	//imgWidth = imgIn.cols;
	//imgHeight = imgIn.rows;
	//
	//currentKernelSize = kernelSize;

	//iterationWidth = imgWidth - (currentKernelSize - 1);
	//iterationHeight = imgHeight - (currentKernelSize - 1);
	//horizontalOffset = currentKernelSize / 2;
	//verticalOffset = imgWidth * horizontalOffset;
	//rowGap = horizontalOffset * 2;
	//
	//currentInPixel = reinterpret_cast<int const*>(imgIn.ptr());
	//curOut = reinterpret_cast<int*>(imgOut.ptr());

	//initialPointerOffset = (currentKernelSize / 2) + ((currentKernelSize / 2)*imgWidth);
	//currentInPixel += initialPointerOffset;
	//curOut += initialPointerOffset;

	///* loop through imgs */
	//for (int i{ 0 }; i < iterationHeight; ++i) {
	//	for (int j{ 0 }; j < iterationWidth; ++j) {
	//		kernelPixel = currentInPixel;
	//		*curOut = 0;
	//		totalR = totalG = totalB = 0.0;
	//		
	//		/* loop around pixel */
	//		for (int l{ -verticalOffset }; l <= verticalOffset; l += verticalOffset){
	//			kernelPixel += l;
	//			for (int k{ -horizontalOffset }; k <= horizontalOffset; ++k) {
	//				kernelPixel += k;

	//				totalR += (*kernelPixel & 0x00ff0000) >> 16;
	//				totalG += (*kernelPixel & 0x0000ff00) >> 8;
	//				totalB += (*kernelPixel & 0x000000ff);
	//			}
	//		}
	//		totalR /= (currentKernelSize * currentKernelSize);
	//		totalG /= (currentKernelSize * currentKernelSize);
	//		totalB /= (currentKernelSize * currentKernelSize);
	//		break;

	//		*curOut = 0xFF000000
	//		 | (static_cast<unsigned int>(std::floor(totalR)) << 16)
	//		 | (static_cast<unsigned int>(std::floor(totalG)) << 8)
	//		 | (static_cast<unsigned int>(std::floor(totalB)));

	//		/* pendant l'itération sur une ligne, on tasse de "un pixel" (32bits) */
	//		++curOut;
	//		++currentInPixel;
	//	}
	//	curOut += rowGap;
	//	currentInPixel += rowGap;
	//}

}

void VR_BlurProcess::updateKernelSize(int newKernelSize)
{
	kernelSize = newKernelSize;
}
