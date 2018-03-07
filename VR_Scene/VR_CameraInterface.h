#ifndef VR_CAMERAINTERFACE_H
#define VR_CAMERAINTERFACE_H


class VR_CameraInterface
{
public:
	VR_CameraInterface();
	~VR_CameraInterface();


	virtual void connect() = 0;
	virtual void disconnect() = 0;
	virtual bool present(QVideoFrame const & frame) = 0;

signals:
	//va être remplacé par VR_Image!?
	void frameAvailable(VR_Image frame);
};


#endif // !VR_CAMERAINTERFACE

