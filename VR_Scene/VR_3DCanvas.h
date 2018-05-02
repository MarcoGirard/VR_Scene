#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class VR_3DCanvas : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit VR_3DCanvas(QWidget * parent = 0);
	~VR_3DCanvas();

protected:
	/*void mousePressEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;
	void timerEvent(QTimerEvent *e) override;*/

	void initializeGL() override;
	//void resizeGL(int w, int h) override;
	//void paintGL() override;

	void initShaders();
	//void initTextures();

private:
	QOpenGLShaderProgram program;
};

