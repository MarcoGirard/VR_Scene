#include "VR_3DCanvas.h"

/* Pour ce code, et la classe GeometryEngine, je suis parti de l'exemple du Cube OpenGL de Qt Creator */


VR_3DCanvas::VR_3DCanvas(QWidget * parent) :
	QOpenGLWidget(parent),
	geometries(0),
	texture(0),
	angularSpeed(0)
{
}


VR_3DCanvas::~VR_3DCanvas()
{
	makeCurrent();
	delete texture;
	delete geometries;
	doneCurrent();
}


void VR_3DCanvas::mousePressEvent(QMouseEvent * e)
{
	mousePressPosition = QVector2D(e->localPos());
}

void VR_3DCanvas::mouseReleaseEvent(QMouseEvent * e)
{
	// Mouse release position - mouse press position
	QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

	// Rotation axis is perpendicular to the mouse position difference
	// vector
	QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

	// Accelerate angular speed relative to the length of the mouse sweep
	qreal acc = diff.length() / 100.0;

	// Calculate new rotation axis as weighted sum
	rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

	// Increase angular speed
	angularSpeed += acc;
}

void VR_3DCanvas::timerEvent(QTimerEvent * e)
{
	// Decrease angular speed (friction)
	angularSpeed *= 0.99;

	// Stop rotation when speed goes below threshold
	if (angularSpeed < 0.01) {
		angularSpeed = 0.0;
	}
	else {
		// Update rotation
		rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

		// Request an update
		update();
	}
}

void VR_3DCanvas::setViewerPosition(int x, int y, int z)
{
	mX = x;
	mY = y;
	mZ = z;
}

void VR_3DCanvas::initializeGL()
{
	initializeOpenGLFunctions();

	glClearColor(0, 0, 0, 1);

	initShaders();
	initTextures();

	// Enable depth buffer
	glEnable(GL_DEPTH_TEST);

	// Enable back face culling
	glEnable(GL_CULL_FACE);

	geometries = new QGeometryEngine;
	timer.start(12, this);
}

void VR_3DCanvas::resizeGL(int w, int h)
{
	// Calculate aspect ratio
	qreal aspect = qreal(w) / qreal(h ? h : 1);

	// Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
	const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

	// Reset projection
	projection.setToIdentity();

	// Set perspective projection
	projection.perspective(fov, aspect, zNear, zFar);
}

void VR_3DCanvas::paintGL()
{
	// Clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	texture->bind();
	// Calculate model view transformation
	QMatrix4x4 matrix;
	matrix.translate(0.0, 0.0, -5.0);
	matrix.rotate(rotation);

	// Set modelview-projection matrix
	program.setUniformValue("mvp_matrix", projection * matrix);
	// Use texture unit 0 which contains cube.png
	program.setUniformValue("texture", 0);

	// Draw cube geometry
	geometries->drawCubeGeometry(&program);
}

void VR_3DCanvas::initShaders()
{
	// Compile vertex shader
	if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, "vshader.glsl"))
		close();

	// Compile fragment shader
	if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, "fshader.glsl"))
		close();

	// Link shader pipeline
	if (!program.link())
		close();

	// Bind shader pipeline for use
	if (!program.bind())
		close();
}

void VR_3DCanvas::initTextures()
{
	// Load cube.png image
	texture = new QOpenGLTexture(QImage("cube.png").mirrored());

	// Set nearest filtering mode for texture minification
	texture->setMinificationFilter(QOpenGLTexture::Nearest);

	// Set bilinear filtering mode for texture magnification
	texture->setMagnificationFilter(QOpenGLTexture::Linear);

	// Wrap texture coordinates by repeating
	// f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
	texture->setWrapMode(QOpenGLTexture::Repeat);
}
