#ifndef VR_IMAGE_H
#define VR_IMAGE_H



class VR_Image
{
public:
	VR_Image();
	VR_Image(QImage image);
	~VR_Image();

	void fromQImage(QImage image);


private:

};

#endif //VR_IMAGE
