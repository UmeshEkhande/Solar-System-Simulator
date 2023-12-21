#include "pch.h"
#include "Circle.h"
#include<vector>

Circle::Circle()
{

}

Circle::Circle(Point3D gCenter, float gRadius):center(gCenter),radius(gRadius)
{

}

Circle::~Circle()
{

}




void Circle::drawCircle(std::vector<float>& mVertices, std::vector<float>& mColors, float cx, float cy, float radius, int segments, Point3D circleColor)
{
	for (int j = 0; j < 360; ++j) {
		float theta = float(j) * 3.1415926f / 180.0f;
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);
		mVertices.push_back(x);
		mVertices.push_back(y);

		mColors.push_back(circleColor.x());
		mColors.push_back(circleColor.y());
		mColors.push_back(circleColor.z());

	}
}

void Circle::drawColoredCircle(std::vector<float>& mVertices, std::vector<float>& mColors, float cx, float cy, float radius, int segments, Point3D circleColor)
{
	for (int i = 0; i < segments; ++i)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(segments);
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);

		mVertices.push_back(cx);
		mVertices.push_back(cy);

		mColors.push_back(circleColor.x());
		mColors.push_back(circleColor.y());
		mColors.push_back(circleColor.z());

		mVertices.push_back(cx + x);
		mVertices.push_back(cy + y);
		mColors.push_back(circleColor.x());
		mColors.push_back(circleColor.y());
		mColors.push_back(circleColor.z());
	}
}