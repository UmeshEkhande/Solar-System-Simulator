#include "stdafx.h"
#include "SolarSystem.h"


SolarSystem::SolarSystem()
{
	mPlanetColors =
	{
	Point3D(1.0, 0.0, 0.0),  // Red
	Point3D(0.0, 1.0, 0.0),  // Green
	Point3D(0.0, 0.0, 1.0),  // Blue
	Point3D(1.0, 1.0, 0.0),  // Yellow
	Point3D(1.0, 0.0, 1.0),  // Magenta
	Point3D(0.0, 1.0, 1.0),  // Cyan
	Point3D(0.5, 0.5f, 0.5f),  // Gray
	Point3D(0.8, 0.8, 0.0)   // Olive
	};

	mSpeedMultiplier = new double; 
	circle = new Circle();
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

void SolarSystem::drawSolarSystem(std::vector<float>& mVertices, std::vector<float>& mColors)
{
	circle->drawColoredCircle(mVertices, mColors, 0.0f, 0.0f, 0.5f, 600, Point3D(1.0, 1.0, 0.0));
	drawOrbitingPlanets(mVertices, mColors);
}


void SolarSystem::drawOrbitingPlanets(std::vector<GLfloat>& mVertices, std::vector<GLfloat>& mColors)
{


	for (int i = 0; i < numPlanets; ++i) {
		
		circle->drawCircle(mVertices, mColors, 0, 0, planetDistance[i], 100, Point3D(1.0, 1.0, 1.0));

		float theta = float(planetAngles[i]) * 3.1415926f / 180.0f;
		float x = planetDistance[i] * cosf(theta);
		float y = planetDistance[i] * sinf(theta);

		Point3D planetColor = mPlanetColors[i];

		circle->drawColoredCircle(mVertices, mColors, x, y, planetRadius[i], 600, planetColor);
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


