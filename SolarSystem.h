#pragma once
#include "OpenGLWindow.h"
class SolarSystem
{
public:
	SolarSystem();
	~SolarSystem();

public: 	
	void drawSolarSystem(QVector<GLfloat>& mVertices, QVector<GLfloat>& mColors);
	void resetPositions();
	void updatePositions(int numberOfDays);
	void setSpeedMultiplier(double speedMultiplier);

	const QVector<GLfloat>& getCurrentVertices() const { return mCurrentVertices; }
	const QVector<GLfloat>& getCurrentColors() const { return mCurrentColors; }

private:
	void drawColoredCircle(QVector<GLfloat>& mVertices, QVector<GLfloat>& mColors, float cx, float cy, float radius, int segments, QVector3D circleColor);
	void drawOrbitingPlanets(QVector<GLfloat>& vertices, QVector<GLfloat>& colors);
	void drawCircle(QVector<GLfloat>& mVertices, QVector<GLfloat>& mColors, float cx, float cy, float radius, int segments, QVector3D circleColor);

private:
	QVector<float> planetOrbitPeriod;
	double* mSpeedMultiplier;
	enum { numPlanets = 8 };
	int demo = 10;
	const float planetRadius[numPlanets] = { 0.2f, 0.3f, 0.4f, 0.25f, 0.35f, 0.3f, 0.25f, 0.1f };
	const float planetDistance[8] = { 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	const float planetSpeed[numPlanets] = { 0.25f, 0.2f, 0.15f, 0.12f, 0.1f, 0.08f, 0.06f, 0.04f };
	float planetAngles[numPlanets] = { 0.0f };
	QVector<QVector3D> mPlanetColors;
	QVector<QVector<GLfloat>> data;
	SolarSystem* solar;

	QVector<GLfloat> mCurrentVertices;
	QVector<GLfloat> mCurrentColors;
};

