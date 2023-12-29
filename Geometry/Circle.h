#pragma once
#include "Point3D.h"
#include <vector>

class GEOMETRY_API Circle : public Point3D
{
public:
	Circle();
	Circle(Point3D gCenter, float gRadius);
	~Circle();

public:
	void drawCircle(std::vector<float>& mVertices, std::vector<float>& mColors, float cx, float cy, float radius, int segments, Point3D circleColor);
	void drawColoredCircle(std::vector<float>& mVertices, std::vector<float>& mColors, float cx, float cy, float radius, int segments, Point3D circleColor);

private:
	std::vector<Point3D> mPoints;
	float radius;
	Point3D center;
	int sSegments = 600;
	Point3D color;
};