#pragma once
#include "Point3D.h"
#include "pch.h"

class GEOMETRY_API Line
{
public:
	Line(Point3D inStart, Point3D inEnd);
	~Line();

public:
	Point3D& start();
	Point3D& end();

private:
	Point3D mStart;
	Point3D mEnd;
};
