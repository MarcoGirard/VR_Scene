#include "VR_Scene.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VR_Scene w;

	w.show();
	return a.exec();
}
