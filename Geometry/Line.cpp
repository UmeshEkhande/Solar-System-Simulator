#include "pch.h"
#include "Line.h"

Line::Line(Point3D inStart, Point3D inEnd) :
	mStart(inStart),
	mEnd(inEnd)
{

}

Line::~Line()
{

}

Point3D& Line::start()
{
	return mStart;
}

Point3D& Line::end()
{
	return mEnd;
}