#include "VR_BlurProcess.h"



VR_BlurProcess::VR_BlurProcess(QObject * parent) :
	VR_ImageProcess(parent)
{
}


VR_BlurProcess::~VR_BlurProcess()
{
}

void VR_BlurProcess::process(Mat &imgIn, Mat &imgOut)
{
	imgOut = imgIn; // QUESTION POUR JC : est-ce que cette opération est couteuse?


	//int * row, * currentInPixel, pixelOut;
	//double totalR{ 0 }, totalG{ 0 }, totalB{ 0 };
	//int imgWidth{ imgIn.width() }, imgHeight{ imgIn.height() };
	//uchar r, g, b;

	//const int horizontalOffset{ static_cast<int>(std::floor(kernelSize / 2)) };
	//const int verticalOffset{ static_cast<int>(imgWidth * horizontalOffset) };
	//
	//int * curOut = reinterpret_cast<int*>(imgOut.bits());
	//curOut += imgWidth + 1; // Placer le pointeur du pixel de sortie 
	//
	///* LOOP THROUGH IMGS */
	//for (int i{ horizontalOffset }; i < imgHeight - horizontalOffset; ++i) {
	//	row = reinterpret_cast<int*>(imgIn.scanLine(i));
	//	curOut += 2 * horizontalOffset; // on ignore la première et la dernière colonne au changement de ligne
	//	for (int j{ horizontalOffset }; j < imgWidth - horizontalOffset; ++j) {
	//		currentInPixel = &row[j];
	//		pixelOut = 0;
	//		totalR = totalG = totalB = 0;
	//		
	//		/* LOOP AROUND PIXEL */
	//		for (int l{ -verticalOffset }; l <= verticalOffset; l += verticalOffset){
	//			currentInPixel += l;
	//			for (int k{ -horizontalOffset }; k <= horizontalOffset; k+=horizontalOffset) {
	//				currentInPixel += k;

	//				totalR += (*currentInPixel & 0x00FF0000) >> 16;
	//				totalG += (*currentInPixel & 0x0000FF00) >> 8;
	//				totalB += (*currentInPixel & 0x000000FF);
	//			}
	//		}
	//		/* on recompose le pixel avec nos valeurs rgb */
	//		pixelOut += (totalR / 9);
	//		pixelOut <<= 8;
	//		pixelOut += (totalG / 9);
	//		pixelOut <<= 8;
	//		pixelOut += (totalB/ 9);
	//		pixelOut += 0xFF000000;
	//		*curOut = pixelOut;
	//		
	//		/* Pendant l'itération sur une ligne, on tasse de "un pixel" (32bits) */
	//		++curOut;
	//	}
	//}

}

void VR_BlurProcess::updateKernelSize(int newKernelSize)
{
	kernelSize = newKernelSize;
}
