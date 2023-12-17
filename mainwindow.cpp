#include "stdafx.h"
#include "mainwindow.h"
#include "OpenGLWindow.h"
#include "SolarSystem.h"
#include <QPushButton>
#include <QGridLayout>
#include <QInputDialog>
#include <iostream>   

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	setupUi();
	connect(mStartButton, &QPushButton::clicked, this, &MainWindow::startBtn);
	connect(mStopButton, &QPushButton::clicked, this, &MainWindow::stopBtn);
	connect(mResetButton, &QPushButton::clicked, this, &MainWindow::resetBtn);
	connect(mUpdateButton, &QPushButton::clicked, this, &MainWindow::updateBtn);
	connect(mSpeedComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onSpeedComboBoxIndexChanged);
	connect(mZoomSlider, &QSlider::valueChanged, this, &MainWindow::zoomSliderChanged);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
	resize(720, 700);
	mWidget = new QWidget(this);
	mBaseLayout = new QGridLayout(mWidget);
	mVbuttonsLayout = new QVBoxLayout();
	mButtonsLayout = new QHBoxLayout();
	mSpeedComboBox = new QComboBox(this);
	mZoomSlider = new QSlider(Qt::Horizontal, mWidget);
	mRenderer = new OpenGLWindow(QColor(0, 0, 0), mWidget);

	QVector<GLfloat> mVertices;
	QVector<GLfloat> mColors;
	//solar = new SolarSystem();
	//QVector<QVector<GLfloat>> solarData = solar.getData();
	//solar.drawSolarSystem(mVertices, mColors);
	//const QVector<GLfloat>& vertices = solarData.at(0);
	//const QVector<GLfloat>& colors = solarData.at(1);
	//mRenderer->setData(mVertices, mColors);

	setCentralWidget(mWidget);
	mStartButton = new QPushButton("Start", mWidget);
	mStopButton = new QPushButton("Stop", mWidget);
	mResetButton = new QPushButton("Reset", mWidget);
	mUpdateButton = new QPushButton("Update", mWidget);
	mTimeInput = new QLineEdit(mWidget);
	mTimeInput->setPlaceholderText("Enter days");

	mStartButton->setFixedWidth(130);
	mButtonsLayout->addWidget(mStartButton);
	mStopButton->setFixedWidth(130);
	mButtonsLayout->addWidget(mStopButton);
	mResetButton->setFixedWidth(130);
	mButtonsLayout->addWidget(mResetButton);
	mUpdateButton->setFixedWidth(130);
	mButtonsLayout->addWidget(mUpdateButton);
	mTimeInput->setFixedWidth(130);
	mButtonsLayout->addWidget(mTimeInput);

	mSpeedComboBox->addItem("0.5x");
	mSpeedComboBox->addItem("1x");
	mSpeedComboBox->addItem("1.5x");
	mSpeedComboBox->addItem("2x");
	mSpeedComboBox->addItem("3x");
	mSpeedComboBox->setFixedWidth(130);
	mSpeedComboBox->setCurrentIndex(1);
	mButtonsLayout->addWidget(mSpeedComboBox);
	mVbuttonsLayout->addLayout(mButtonsLayout);

	mZoomSlider->setRange(0, 100);
	mZoomSlider->setValue(50);


	mVbuttonsLayout->addWidget(mRenderer, 1);
	mVbuttonsLayout->addWidget(mZoomSlider);
	mBaseLayout->addLayout(mVbuttonsLayout, 0, 0);
	setWindowTitle(QCoreApplication::translate("Solar System Simulator", "Solar System Simulator", nullptr));
}


void MainWindow::zoomSliderChanged(int value)
{
	double zoomFactor = 0.5 + (value / 100.0) * 1.5;
	mRenderer->setZoomFactor(zoomFactor);
}


void MainWindow::startBtn()
{
	mRenderer->startRevolving();
}

void MainWindow::stopBtn()
{
	mRenderer->stopRevolving();
}

void MainWindow::resetBtn()
{
	mRenderer->resetPositions();
}

void MainWindow::updateBtn()
{
	bool ok;
	int numberOfDays = mTimeInput->text().toInt(&ok);

	if (ok)
	{
		mRenderer->updatePositions(numberOfDays);
	}
	else
	{
	}
}

void MainWindow::onSpeedComboBoxIndexChanged(int index)
{
	double speedMultiplier{1.0}; // Default speed

	switch (index)
	{
	case 0:
	{
		speedMultiplier = 0.5;
		break;
	}
	case 1:
	{
		speedMultiplier = 1.0;
		break;
	}
	case 2:
	{
		speedMultiplier = 1.5;
		break;
	}
	case 3:
	{
		speedMultiplier = 2.0;
		break;
	}
	case 4:
	{
		speedMultiplier = 3.0;
		break;
	}
	default:
	{
		break;
	}
	}
	mRenderer->setSpeedMultiplier(speedMultiplier);
}
  