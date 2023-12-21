#include "stdafx.h"
#include "OpenGLWindow.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <iostream>
#include "SolarSystem.h"
#include <QTimer>

OpenGLWindow::OpenGLWindow(const QColor& background, QWidget* parent) : mBackground(background)
{
	setParent(parent);
	setMinimumSize(500, 250);
	mZoomFactor = 1.25;
    solar = new SolarSystem();
	timer = new QTimer(this);
}

void OpenGLWindow::updateData(std::vector<float>& vertices, std::vector<float>& colors)
{
	mVertices.clear();
	mColors.clear();
	mVertices = vertices;
	mColors = colors;
	update();
}

void OpenGLWindow::startRendering()
{
	connect(timer, &QTimer::timeout, this, &OpenGLWindow::updateSolarSystemData);
	timer->start(16); 
}

void OpenGLWindow::stopRendering()
{

	timer->stop();
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

void OpenGLWindow::updateSolarSystemData()
{
	mVertices.clear();
	mColors.clear();
	solar->drawSolarSystem(mVertices, mColors);
	update();
}

void OpenGLWindow::setZoomFactor(double &zoomFactor)
{
	mZoomFactor = zoomFactor;
	update();
}

void OpenGLWindow::setSpeedMultiplier(double speedMultiplier)
{
	solar->setSpeedMultiplier(speedMultiplier);
}

void OpenGLWindow::startRevolving()
{	
	timer->start(16);
}

void OpenGLWindow::stopRevolving()
{
	timer->stop();
}

void OpenGLWindow::resetPositions()
{
	
	solar->resetPositions();
	updateSolarSystemData();
}

void OpenGLWindow::updatePositions(int numberOfDays)
{
	solar->updatePositions(numberOfDays);
	updateSolarSystemData();
}

void OpenGLWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	mProgram->bind();

	QMatrix4x4 matrix;
	matrix.ortho(-6.0f * mZoomFactor, 6.0f * mZoomFactor, -6.0f * mZoomFactor, 6.0f * mZoomFactor, 0.1f, 100.0f);  // orthographic projection
	matrix.translate(0, 0, -2);

	mProgram->setUniformValue(m_matrixUniform, matrix);

	mVerticesData = mVertices.data();
	mColorsData = mColors.data();

	int size = mVertices.size();

	glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, mVerticesData);
	glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, mColorsData);

	glEnableVertexAttribArray(m_posAttr);
	glEnableVertexAttribArray(m_colAttr);

	glDrawArrays(GL_LINES, 0, size / 2);

	glDisableVertexAttribArray(m_colAttr);
	glDisableVertexAttribArray(m_posAttr);

	//mProgram->release();


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

