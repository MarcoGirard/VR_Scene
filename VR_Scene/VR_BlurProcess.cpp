#include "VR_BlurProcess.h"



VR_BlurProcess::VR_BlurProcess(QObject * parent) :
	VR_ImageProcess(parent)
{
}


VR_BlurProcess::~VR_BlurProcess()
{
}

void VR_BlurProcess::process(const Mat &imgIn, Mat &imgOut)
{
	imgOut = imgIn; // QUESTION POUR JC : est-ce que cette opération est couteuse?


	int * row, * currentinpixel, pixelout;
	double totalr{ 0 }, totalg{ 0 }, totalb{ 0 };
	int imgwidth{ imgIn.cols }, imgheight{ imgIn.rows };
	uchar r, g, b;

	const int horizontaloffset{ static_cast<int>(std::floor(kernelSize / 2)) };
	const int verticaloffset{ static_cast<int>(imgwidth * horizontaloffset) };
	
	int * curout = reinterpret_cast<int*>(imgOut.ptr());
	curout += imgwidth + horizontaloffset; // placer le pointeur du pixel de sortie 
	
	/* loop through imgs */
	for (int i{ horizontaloffset }; i < (imgheight - horizontaloffset); ++i) {
		row = reinterpret_cast<int*>(imgOut.ptr(i));
		curout += 2 * horizontaloffset; // on ignore les x premières et dernières colonnes au changement de ligne
		for (int j{ horizontaloffset }; j < (imgwidth - horizontaloffset); ++j) {
			currentinpixel = &row[j];
			pixelout = 0;
			totalr = totalg = totalb = 0;
			
			/* loop around pixel */
			for (int l{ -verticaloffset }; l <= verticaloffset; l += verticaloffset){
				currentinpixel += l;
				for (int k{ -horizontaloffset }; k <= horizontaloffset; k+=horizontaloffset) {
					currentinpixel += k;

					totalr += (*currentinpixel & 0x00ff0000) >> 16;
					totalg += (*currentinpixel & 0x0000ff00) >> 8;
					totalb += (*currentinpixel & 0x000000ff);
				}
			}
			/* on recompose le pixel avec nos valeurs rgb */
			pixelout += (totalr / 9);
			pixelout <<= 8;
			pixelout += (totalg / 9);
			pixelout <<= 8;
			pixelout += (totalb/ 9);
			pixelout += 0xff000000;
			*curout = pixelout;
			
			/* pendant l'itération sur une ligne, on tasse de "un pixel" (32bits) */
			++curout;
		}
	}

}

void VR_BlurProcess::updateKernelSize(int newKernelSize)
{
	kernelSize = newKernelSize;
}
