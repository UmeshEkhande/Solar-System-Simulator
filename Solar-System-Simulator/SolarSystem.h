#pragma once
#include "OpenGLWindow.h"
#include "Point3D.h"
#include "Circle.h"
#include<vector>

class SolarSystem
{
public:
	SolarSystem();
	~SolarSystem();

public: 	
	void drawSolarSystem(std::vector<float>& mVertices, std::vector<float>& mColors);
	void resetPositions();
	void updatePositions(int numberOfDays);
	void setSpeedMultiplier(double speedMultiplier);
	const std::vector<float>& getCurrentVertices() const { return mCurrentVertices; }
	const std::vector<float>& getCurrentColors() const { return mCurrentColors; }

private:
	void drawOrbitingPlanets(std::vector<float>& vertices, std::vector<float>& colors);

private:
	QVector<float> planetOrbitPeriod;
	double* mSpeedMultiplier;
	enum { numPlanets = 8 };
	const float planetRadius[numPlanets] = { 0.2f, 0.3f, 0.4f, 0.25f, 0.35f, 0.3f, 0.25f, 0.1f };
	const float planetDistance[8] = { 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	const float planetSpeed[numPlanets] = { 0.25f, 0.2f, 0.15f, 0.12f, 0.1f, 0.08f, 0.06f, 0.04f };
	float planetAngles[numPlanets] = { 0.0f };

	std::vector<Point3D> mPlanetColors;

	std::vector<float> mCurrentVertices;
	std::vector<float> mCurrentColors;


	SolarSystem* solar;
	Circle* circle;
};

