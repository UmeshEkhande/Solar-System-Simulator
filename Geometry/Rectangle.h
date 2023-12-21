#pragma once
#include "Line.h"
#include <vector>
#include "pch.h"


class GEOMETRY_API Rectangle
{
public:
	Rectangle();
	Rectangle(Point3D inMin, Point3D inMax);
	~Rectangle();

public:
	std::vector<Line> lines();

private:
	std::vector<Line> mLines;
};



