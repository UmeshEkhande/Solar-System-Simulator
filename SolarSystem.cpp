#include "stdafx.h"
#include "SolarSystem.h"


SolarSystem::SolarSystem()
{
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

	mSpeedMultiplier = new double; 
	*mSpeedMultiplier = 1.0;

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

SolarSystem::~SolarSystem()
{

}

void SolarSystem::drawSolarSystem(QVector<GLfloat>& mVertices, QVector<GLfloat>& mColors)
{
	drawColoredCircle(mVertices, mColors, 0.0f, 0.0f, 0.5f, 600, QVector3D(1.0f, 1.0f, 0.0f));
	drawOrbitingPlanets(mVertices, mColors);
}


void SolarSystem::drawCircle(QVector<GLfloat>& mVertices, QVector<GLfloat>& mColors, float cx, float cy, float radius, int segments, QVector3D circleColor)
{
	for (int j = 0; j < 360; ++j) {
		float theta = float(j) * 3.1415926f / 180.0f;
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);
		mVertices << x << y;
		mColors << circleColor.x() << circleColor.y() << circleColor.z();
	}
}

void SolarSystem::drawColoredCircle(QVector<GLfloat>& mVertices, QVector<GLfloat>& mColors, float cx, float cy, float radius, int segments, QVector3D circleColor)
{
	for (int i = 0; i < segments; ++i)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(segments);
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);

		mVertices << cx << cy;
		mColors << circleColor.x() << circleColor.y() << circleColor.z();

		mVertices << cx + x << cy + y;
		mColors << circleColor.x() << circleColor.y() << circleColor.z();
	}
}

void SolarSystem::drawOrbitingPlanets(QVector<GLfloat>& mVertices, QVector<GLfloat>& mColors)
{
	//mVertices.clear();
	//mColors.clear();

	for (int i = 0; i < numPlanets; ++i) {

		drawCircle(mVertices, mColors, 0, 0, planetDistance[i], 100, QVector3D(1.0f, 1.0f, 1.0f));

		float theta = float(planetAngles[i]) * 3.1415926f / 180.0f;
		float x = planetDistance[i] * cosf(theta);
		float y = planetDistance[i] * sinf(theta);

		QVector3D planetColor = mPlanetColors[i];

		drawColoredCircle(mVertices, mColors, x, y, planetRadius[i], 600, planetColor);
		planetAngles[i] += (*mSpeedMultiplier) * planetSpeed[i];

		// Angle Should be 360 degrees
		if (planetAngles[i] >= 360.0f) {
			planetAngles[i] -= 360.0f;
		}
	}

}

void SolarSystem::setSpeedMultiplier(double speedMultiplier)
{
	*mSpeedMultiplier = speedMultiplier;
}

void SolarSystem::resetPositions()
{
	for (int i = 0; i < numPlanets; ++i)
	{
		planetAngles[i] = 0.0f;
	}
}

void SolarSystem::updatePositions(int numberOfDays)
{
	for (int i = 0; i < numPlanets; ++i)
	{
		float rotationAngle = 360.0f * (static_cast<float>(numberOfDays) / planetOrbitPeriod[i]);
		planetAngles[i] += rotationAngle;
	}

}


