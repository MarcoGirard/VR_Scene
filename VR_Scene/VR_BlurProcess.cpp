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

	int const * row{ nullptr };
	int const *currentinpixel{ nullptr };
	int pixelout;
	double totalr{ 0.0 }, totalg{ 0.0 }, totalb{ 0.0 };
	int imgwidth{ imgIn.cols }, imgheight{ imgIn.rows };
	uchar r, g, b;
	int currentKernelSize = kernelSize;

	const int horizontaloffset{ static_cast<int>((currentKernelSize - 1) / 2) };
	const int verticaloffset{ static_cast<int>(imgwidth * horizontaloffset) };
	
	int * curout{ reinterpret_cast<int*>(imgOut.ptr()) };
	curout += verticaloffset + horizontaloffset; // placer le pointeur du pixel de sortie 

	/* loop through imgs */
	for (int i{ horizontaloffset }; i < (imgheight - horizontaloffset); ++i) {
		row = reinterpret_cast<int const *>(imgIn.ptr(i));
		curout += 2 * horizontaloffset; // on ignore les x premières et dernières colonnes au changement de ligne
		for (int j{ horizontaloffset }; j < (imgwidth - horizontaloffset); ++j) {
			currentinpixel = &row[j];
			*curout = 0;
			totalr = totalg = totalb = 0;
			
			/* loop around pixel */
			for (int l{ -verticaloffset }; l <= verticaloffset; l += verticaloffset){
				currentinpixel += l;
				for (int k{ -horizontaloffset }; k <= horizontaloffset; ++k) {
					currentinpixel += k;

					totalr += (*currentinpixel & 0x00ff0000) >> 16;
					totalg += (*currentinpixel & 0x0000ff00) >> 8;
					totalb += (*currentinpixel & 0x000000ff);
				}
			}
			totalr /= (currentKernelSize * currentKernelSize);
			totalg /= (currentKernelSize * currentKernelSize);
			totalb /= (currentKernelSize * currentKernelSize);

			*curout = 0xFF000000;
			*curout |= (static_cast<unsigned int>(std::floor(totalr)) << 16);
			*curout |= (static_cast<unsigned int>(std::floor(totalg)) << 8);
			*curout |= (static_cast<unsigned int>(std::floor(totalb)));

			/* pendant l'itération sur une ligne, on tasse de "un pixel" (32bits) */
			++curout;
		}
	}

}

void VR_BlurProcess::updateKernelSize(int newKernelSize)
{
	kernelSize = newKernelSize;
}
