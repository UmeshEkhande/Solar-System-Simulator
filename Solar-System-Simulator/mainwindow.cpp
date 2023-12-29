#include "stdafx.h"
#include "mainwindow.h"
#include "OpenGLWindow.h"
#include "SolarSystem.h"
#include <QPushButton>
#include <QGridLayout>
#include <QInputDialog>
#include <iostream>
#include <vector>

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent)
{
	setupUi();
	connect(mStartButton, &QPushButton::clicked, this, &MainWindow::startBtn);
	connect(mStopButton, &QPushButton::clicked, this, &MainWindow::stopBtn);
	connect(mResetButton, &QPushButton::clicked, this, &MainWindow::resetBtn);
	connect(mUpdateButton, &QPushButton::clicked, this, &MainWindow::updateBtn);
	connect(mSpeedComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onSpeedComboBoxIndexChanged);
	connect(mZoomSlider, &QSlider::valueChanged, this, &MainWindow::zoomSliderChanged);
	connect(mTabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
	connect(mDrawBezierBtn, &QPushButton::clicked, this, &MainWindow::drawCurveUsingBezier);
	connect(mHermiteBtn, &QPushButton::clicked, this, &MainWindow::drawCurveUsingHermite);
	connect(mBSplineBtn, &QPushButton::clicked, this, &MainWindow::drawCurveUsingBSpline);
	connect(mClearBtn, &QPushButton::clicked, this, &MainWindow::clearWindow);

}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{

	resize(900, 720);
	mWidget = new QWidget(this);
	mBaseLayout = new QGridLayout(mWidget);
	mVbuttonsLayout = new QVBoxLayout();
	mButtonsLayout = new QHBoxLayout();
	mSpeedComboBox = new QComboBox(this);

	mTabWidget = new QTabWidget(this);

	mInputButtonsLayout = new QHBoxLayout();
	mVTab2ButtonsLayout = new QVBoxLayout();

	mVPoint1Layout = new QVBoxLayout();
	mVPoint2Layout = new QVBoxLayout();
	mVPoint3Layout = new QVBoxLayout();
	mVPoint4Layout = new QVBoxLayout();

	mPoint1 = new QLabel(this);
	mPoint2 = new QLabel(this);
	mPoint3 = new QLabel(this);
	mPoint4 = new QLabel(this);

	mX1Input = new QLineEdit(mWidget);
	mY1Input = new QLineEdit(mWidget);
	mZ1Input = new QLineEdit(mWidget);

	mX2Input = new QLineEdit(mWidget);
	mY2Input = new QLineEdit(mWidget);
	mZ2Input = new QLineEdit(mWidget);

	mX3Input = new QLineEdit(mWidget);
	mY3Input = new QLineEdit(mWidget);
	mZ3Input = new QLineEdit(mWidget);

	mX4Input = new QLineEdit(mWidget);
	mY4Input = new QLineEdit(mWidget);
	mZ4Input = new QLineEdit(mWidget);

	mDrawBezierBtn = new QPushButton("Draw Bezier", mWidget);
	mHermiteBtn = new QPushButton("Draw Hermite", mWidget);
	mBSplineBtn = new QPushButton("Draw BSpline", mWidget);
	mClearBtn = new QPushButton("Clear", mWidget);

	QWidget* solarSystemTab = new QWidget(mTabWidget);
	QWidget* curveTab = new QWidget(mTabWidget);

	mStartButton = new QPushButton("Start", mWidget);
	mStopButton = new QPushButton("Stop", mWidget);
	mResetButton = new QPushButton("Reset", mWidget);
	mUpdateButton = new QPushButton("Update", mWidget);

	mZoomSlider = new QSlider(Qt::Horizontal, mWidget);
	mRenderer = new OpenGLWindow(QColor(0, 0, 0), mWidget);
	mBezierRenderer = new OpenGLWindow(QColor(0, 0, 0), mWidget);

	mTabWidget->setFixedSize(900, 720);

	mVTab2ButtonsLayout->addWidget(mDrawBezierBtn);
	mVTab2ButtonsLayout->addWidget(mHermiteBtn);
	mVTab2ButtonsLayout->addWidget(mBSplineBtn);
	mVTab2ButtonsLayout->addWidget(mClearBtn);

	mPoint1->setText("Point1");
	mVPoint1Layout->addWidget(mPoint1, 0, Qt::AlignHCenter);
	mX1Input->setPlaceholderText("Enter X Coordinate");
	mVPoint1Layout->addWidget(mX1Input);
	mY1Input->setPlaceholderText("Enter Y Coordinate");
	mVPoint1Layout->addWidget(mY1Input);
	mZ1Input->setPlaceholderText("Enter Z Coordinate");
	mVPoint1Layout->addWidget(mZ1Input);


	mPoint2->setText("Point2");
	mVPoint2Layout->addWidget(mPoint2, 0, Qt::AlignHCenter);
	mX2Input->setPlaceholderText("Enter X Coordinate");
	mVPoint2Layout->addWidget(mX2Input);
	mY2Input->setPlaceholderText("Enter Y Coordinate");
	mVPoint2Layout->addWidget(mY2Input);
	mZ2Input->setPlaceholderText("Enter Z Coordinate");
	mVPoint2Layout->addWidget(mZ2Input);

	mPoint3->setText("Point3");
	mVPoint3Layout->addWidget(mPoint3, 0, Qt::AlignHCenter);
	mX3Input->setPlaceholderText("Enter X Coordinate");
	mVPoint3Layout->addWidget(mX3Input);
	mY3Input->setPlaceholderText("Enter Y Coordinate");
	mVPoint3Layout->addWidget(mY3Input);
	mZ3Input->setPlaceholderText("Enter Z Coordinate");
	mVPoint3Layout->addWidget(mZ3Input);

	mPoint4->setText("Point4");
	mVPoint4Layout->addWidget(mPoint4, 0, Qt::AlignHCenter);
	mX4Input->setPlaceholderText("Enter X Coordinate");
	mVPoint4Layout->addWidget(mX4Input);
	mY4Input->setPlaceholderText("Enter Y Coordinate");
	mVPoint4Layout->addWidget(mY4Input);
	mZ4Input->setPlaceholderText("Enter Z Coordinate");
	mVPoint4Layout->addWidget(mZ4Input);

	mInputButtonsLayout->addLayout(mVTab2ButtonsLayout);
	mInputButtonsLayout->addLayout(mVPoint1Layout);
	mInputButtonsLayout->addLayout(mVPoint2Layout);
	mInputButtonsLayout->addLayout(mVPoint3Layout);
	mInputButtonsLayout->addLayout(mVPoint4Layout);
	mInputButtonsLayout->setAlignment(Qt::AlignTop);

	QVBoxLayout* solarSystemLayout = new QVBoxLayout();
	solarSystemLayout->addLayout(mButtonsLayout);
	solarSystemLayout->addWidget(mRenderer, 1);
	solarSystemLayout->addWidget(mZoomSlider);
	solarSystemTab->setLayout(solarSystemLayout);

	QVBoxLayout* curveLayout = new QVBoxLayout();
	curveLayout->addLayout(mInputButtonsLayout);
	curveLayout->addWidget(mBezierRenderer,1);
	curveTab->setLayout(curveLayout);
;

	mTabWidget->addTab(solarSystemTab, "Solar System Simulator");
	mTabWidget->addTab(curveTab, "Curve");


	setCentralWidget(mWidget);
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

	mZoomSlider->setRange(0, 100);
	mZoomSlider->setValue(50);

	mVbuttonsLayout->addWidget(mTabWidget);
	mBaseLayout->addLayout(mVbuttonsLayout, 0, 0);

	onTabChanged(mTabWidget->currentIndex());  
	setWindowTitle(QCoreApplication::translate("Solar System Simulator", "Solar System Simulator", nullptr));

}

void MainWindow::drawCurveUsingBezier()
{
	mVertices.clear();
	mVerticess.clear();
	mColors.clear();
	mColorss.clear();

	xCoordinate = mX1Input->text().toFloat();
	yCoordinate = mY1Input->text().toFloat();
	zCoordinate = mZ1Input->text().toFloat();

	x1Coordinate = mX2Input->text().toFloat();
	y1Coordinate = mY2Input->text().toFloat();
	z1Coordinate = mZ2Input->text().toFloat();

	x2Coordinate = mX3Input->text().toFloat();
	y2Coordinate = mY3Input->text().toFloat();
	z2Coordinate = mZ3Input->text().toFloat();

	x3Coordinate = mX4Input->text().toFloat();
	y3Coordinate = mY4Input->text().toFloat();
	z3Coordinate = mZ4Input->text().toFloat();

	Point3D p0 = Point3D(xCoordinate, yCoordinate, zCoordinate);
	Point3D p1 = Point3D(x1Coordinate, y1Coordinate, z1Coordinate);
	Point3D p2 = Point3D(x2Coordinate, y2Coordinate, z2Coordinate);
	Point3D p3 = Point3D(x3Coordinate, y3Coordinate, z3Coordinate);

	ver << xCoordinate << yCoordinate << zCoordinate;
	col << 0.0f << 1.0f << 0.0f;

	Bezier bezier(p0, p1, p2, p3);
	bezier.drawCurve(p0, p1, p2, p3, mVerticess, mColorss);

	for (int i = 0; i < mVerticess.size(); i += 3)
	{
		ver << mVerticess[i] << mVerticess[i + 1] << mVerticess[i + 2];
	}
	for (int i = 0; i < mColorss.size(); i += 3)
	{
		col << mColorss[i] << mColorss[i + 1] << mColorss[i + 2];
	}

	ver << x3Coordinate << y3Coordinate << z3Coordinate;
	col << 0.0f << 1.0f << 0.0f;

	mBezierRenderer->updateData(ver, col,1);

	ver.clear();
	col.clear();
	mVertices.clear();
	mColors.clear();
}

void MainWindow::drawCurveUsingHermite()
{
	mVertices.clear();
	mColors.clear();

	xCoordinate = mX1Input->text().toFloat();
	yCoordinate = mY1Input->text().toFloat();
	zCoordinate = mZ1Input->text().toFloat();

	x1Coordinate = mX2Input->text().toFloat();
	y1Coordinate = mY2Input->text().toFloat();
	z1Coordinate = mZ2Input->text().toFloat();

	x2Coordinate = mX3Input->text().toFloat();
	y2Coordinate = mY3Input->text().toFloat();
	z2Coordinate = mZ3Input->text().toFloat();

	x3Coordinate = mX4Input->text().toFloat();
	y3Coordinate = mY4Input->text().toFloat();
	z3Coordinate = mZ4Input->text().toFloat();

	Point3D p0 = Point3D(xCoordinate, yCoordinate, zCoordinate);
	Point3D p1 = Point3D(x1Coordinate, y1Coordinate, z1Coordinate);
	Point3D p2 = Point3D(x2Coordinate, y2Coordinate, z2Coordinate);
	Point3D p3 = Point3D(x3Coordinate, y3Coordinate, z3Coordinate);

	mVertices.push_back(xCoordinate);
	mVertices.push_back(yCoordinate);
	mVertices.push_back(zCoordinate);

	mColors.push_back(0.0f);
	mColors.push_back(1.0f);
	mColors.push_back(0.0f);

	 Hermite hermite(p0,p1,p2,p3);
	 hermite.drawCurve(p0, p1, p2, p3, mVertices, mColors);

	mVertices.push_back(x3Coordinate);
	mVertices.push_back(y3Coordinate);
	mVertices.push_back(z3Coordinate);

	mColors.push_back(0.0f);
	mColors.push_back(1.0f);
	mColors.push_back(0.0f);

	mBezierRenderer->updateData(mVertices, mColors);
	mVertices.clear();
	mColors.clear();

}

void MainWindow::drawCurveUsingBSpline()
{
	mVertices.clear();
	mColors.clear();

	xCoordinate = mX1Input->text().toFloat();
	yCoordinate = mY1Input->text().toFloat();
	zCoordinate = mZ1Input->text().toFloat();

	x1Coordinate = mX2Input->text().toFloat();
	y1Coordinate = mY2Input->text().toFloat();
	z1Coordinate = mZ2Input->text().toFloat();

	x2Coordinate = mX3Input->text().toFloat();
	y2Coordinate = mY3Input->text().toFloat();
	z2Coordinate = mZ3Input->text().toFloat();

	x3Coordinate = mX4Input->text().toFloat();
	y3Coordinate = mY4Input->text().toFloat();
	z3Coordinate = mZ4Input->text().toFloat();

	Point3D p0 = Point3D(xCoordinate, yCoordinate, zCoordinate);
	Point3D p1 = Point3D(x1Coordinate, y1Coordinate, z1Coordinate);
	Point3D p2 = Point3D(x2Coordinate, y2Coordinate, z2Coordinate);
	Point3D p3 = Point3D(x3Coordinate, y3Coordinate, z3Coordinate);

	mVertices.push_back(xCoordinate);
	mVertices.push_back(yCoordinate);
	mVertices.push_back(zCoordinate);

	mColors.push_back(0.0f);
	mColors.push_back(1.0f);
	mColors.push_back(0.0f);

	BSpline3D BSpline3D(p0, p1, p2, p3);
	BSpline3D.drawCurveBspline(mVertices, mColors);

	mVertices.push_back(x3Coordinate);
	mVertices.push_back(y3Coordinate);
	mVertices.push_back(z3Coordinate);

	mColors.push_back(0.0f);
	mColors.push_back(1.0f);
	mColors.push_back(0.0f);

	mBezierRenderer->updateData(mVertices, mColors);
	mVertices.clear();
	mColors.clear();
}

void MainWindow::clearWindow()
{
	mVertices.clear();
	mColors.clear();
	mBezierRenderer->updateData(mVertices, mColors);
}

void MainWindow::onTabChanged(int tabIndex)
{
	if (tabIndex == 0)  
	{
		mRenderer->startRendering();
		mZoomSlider->show();
	}
	else
	{
		mRenderer->stopRendering();
		mRenderer->resetPositions();
	}

}


void MainWindow::zoomSliderChanged(int value)
{
	GLfloat zoomFactor = 0.5 + (value / 100.0) * 1.0;
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
	double speedMultiplier{1.0}; 

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
  