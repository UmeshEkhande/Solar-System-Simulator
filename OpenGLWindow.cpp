#include "stdafx.h"
#include "OpenGLWindow.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <iostream>

OpenGLWindow::OpenGLWindow(const QColor& background, QWidget* parent) : mBackground(background)
{
	setParent(parent);
	setMinimumSize(500, 250);
	mPlanetColors =
	{
	QVector3D(1.0f, 0.0f, 0.0f),  // Red
	QVector3D(0.0f, 1.0f, 0.0f),  // Green
	QVector3D(0.0f, 0.0f, 1.0f),  // Blue
	QVector3D(1.0f, 1.0f, 0.0f),  // Yellow
	QVector3D(1.0f, 0.0f, 1.0f),  // Magenta
	QVector3D(0.0f, 1.0f, 1.0f),  // Cyan
	QVector3D(0.5f, 0.5f, 0.5f),  // Gray
	QVector3D(0.8f, 0.8f, 0.0f)   // Olive
	};

	mSpeedMultiplier = 1.0;
	planetOrbitPeriod = {
		87.97f,
		224.7f,
		365.0f,
		687.0f,
		4332.0f,
		10759.0f,
		30685.0f,
		60189.0f

	};
}


OpenGLWindow::~OpenGLWindow()
{
	reset();
}

void OpenGLWindow::reset()
{
	makeCurrent();
	delete mProgram;
	mProgram = nullptr;
	doneCurrent();
	QObject::disconnect(mContextWatchConnection);
}



void OpenGLWindow::paintGL()
{

	glClear(GL_COLOR_BUFFER_BIT);
	mProgram->bind();

	QMatrix4x4 matrix;
	matrix.ortho(-6.0f * mZoomFactor, 6.0f * mZoomFactor, -6.0f * mZoomFactor, 6.0f * mZoomFactor, 0.1f, 100.0f);  // orthographic projection
	matrix.translate(0, 0, -2);

	mProgram->setUniformValue(m_matrixUniform, matrix);
	QVector<GLfloat> mColors;
	QVector<GLfloat> mVertices;

	drawCircle(mVertices, mColors, 0.0f, 0.0f, 0.5f, 600, QVector3D(1.0f, 1.0f, 0.0f));
	drawOrbitingPlanets(mVertices, mColors);

	mVerticesData = mVertices.data();
	mColorsData = mColors.data();

	glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, mVerticesData);
	glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, mColorsData);

	glEnableVertexAttribArray(m_posAttr);
	glEnableVertexAttribArray(m_colAttr);

	glDrawArrays(GL_LINES, 0, mVertices.size() / 2);

	glDisableVertexAttribArray(m_colAttr);
	glDisableVertexAttribArray(m_posAttr);

	mProgram->release();
	update();

}


//Function to draw the circle
void OpenGLWindow::drawCircle(QVector<GLfloat>& mVertices, QVector<GLfloat>& mColors, float cx, float cy, float radius, int segments, const QVector3D& planetColor)
{


	for (int i = 0; i < segments; ++i)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(segments);
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);

		mVertices << cx + x << cy + y;
		mColors << planetColor.x() << planetColor.y() << planetColor.z();

		mVertices << cx << cy;
		mColors << planetColor.x() << planetColor.y() << planetColor.z();

	}
}




void OpenGLWindow::drawOrbitingPlanets(QVector<GLfloat>& mVertices, QVector<GLfloat>& mColors)
{


	for (int i = 0; i < numPlanets; ++i) {
		// Below for loop draws the orbit of planet
		for (int j = 0; j < 360; ++j) {
			float theta = qDegreesToRadians(float(j));
			float x = planetDistance[i] * cosf(theta);
			float y = planetDistance[i] * sinf(theta);
			mVertices << x << y;
			mColors << 1.0f << 1.0f << 1.0f;  // White color for the orbit
		}

		float theta = qDegreesToRadians(planetAngles[i]);
		float x = planetDistance[i] * cosf(theta);
		float y = planetDistance[i] * sinf(theta);

		int planetColorIndex = i % numPlanets;
		QVector3D planetColor = mPlanetColors[planetColorIndex];

		drawCircle(mVertices, mColors, x, y, planetRadius[i], 600, planetColor);
		planetAngles[i] += mSpeedMultiplier * planetSpeed[i];

		// Angle Should be 360 degrees
		if (planetAngles[i] >= 360.0f) {
			planetAngles[i] -= 360.0f;
		}
	}
}


void OpenGLWindow::setZoomFactor(double zoomFactor)
{
	mZoomFactor = zoomFactor;
}

void OpenGLWindow::setSpeedMultiplier(double speedMultiplier)
{
	mSpeedMultiplier = speedMultiplier;
}

void OpenGLWindow::startRevolving()
{
	mIsRevolving = true;
}

void OpenGLWindow::stopRevolving()
{
	mIsRevolving = false;
}

void OpenGLWindow::resetPositions()
{
	for (int i = 0; i < numPlanets; ++i)
	{
		planetAngles[i] = 0.0f;
	}
}

// Function to update the position of the planet
void OpenGLWindow::updatePositions(int numberOfDays)
{
	for (int i = 0; i < numPlanets; ++i)
	{

		float rotationAngle = 360.0f * (static_cast<float>(numberOfDays) / planetOrbitPeriod[i]);
		planetAngles[i] += rotationAngle;
	}
}


void OpenGLWindow::initializeGL()
{
	static const char* vertexShaderSource =
		"attribute highp vec4 posAttr;\n"
		"attribute lowp vec4 colAttr;\n"
		"varying lowp vec4 col;\n"
		"uniform highp mat4 matrix;\n"
		"void main() {\n"
		"   col = colAttr;\n"
		"   gl_Position = matrix * posAttr;\n"
		"}\n";

	static const char* fragmentShaderSource =
		"varying lowp vec4 col;\n"
		"void main() {\n"
		"   gl_FragColor = col;\n"
		"}\n";


	initializeOpenGLFunctions();

	mProgram = new QOpenGLShaderProgram(this);
	mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
	mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);

	if (!mProgram->link())
	{
		qDebug() << "Shader program link error:" << mProgram->log();

	}

	m_posAttr = mProgram->attributeLocation("posAttr");
	m_colAttr = mProgram->attributeLocation("colAttr");
	m_matrixUniform = mProgram->uniformLocation("matrix");

	if (m_posAttr == -1 || m_colAttr == -1 || m_matrixUniform == -1)
	{
		qDebug() << "Shader attribute or uniform location error.";

	}

	glClearColor(mBackground.redF(), mBackground.greenF(), mBackground.blueF(), 1.0f);

}

