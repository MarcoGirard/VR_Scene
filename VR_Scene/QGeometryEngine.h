#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class QGeometryEngine : protected QOpenGLFunctions
{
public:
	QGeometryEngine();
	virtual ~QGeometryEngine();

	void drawCubeGeometry(QOpenGLShaderProgram *program);

private:
	void initCubeGeometry();

	QOpenGLBuffer arrayBuf;
	QOpenGLBuffer indexBuf;
};
