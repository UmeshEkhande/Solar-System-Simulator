#include "pch.h"
#include "BSpline3D.h"

#include <vector>

using namespace std;

BSpline3D::BSpline3D(Point3D inP0, Point3D inP1, Point3D inP2, Point3D inP3) :
    degree(3),
    mP0(inP0),
    mP1(inP1),
    mP2(inP2),
    mP3(inP3)
{
    // Generate a simple knot vector for an open B-spline
    int n = 4;
    int m = n + degree + 1;

    for (int i = 0; i <= m; ++i) {
        if (i < degree + 1) {
            knots.push_back(0.0);
        }
        else if (i <= n) {
            knots.push_back(static_cast<double>(i - degree));
        }
        else {
            knots.push_back(static_cast<double>(n - degree + 1));
        }
    }
}
BSpline3D::~BSpline3D()
{

}

// B-spline basis function
double BSpline3D::basisFunction(int i, int k, double t) {
    if (k == 0) {
        return (t >= knots[i] && t < knots[i + 1]) ? 1.0 : 0.0;
    }

    double denom1 = knots[i + k] - knots[i];
    double term1 = (denom1 != 0.0) ? ((t - knots[i]) / denom1) * basisFunction(i, k - 1, t) : 0.0;

    double denom2 = knots[i + k + 1] - knots[i + 1];
    double term2 = (denom2 != 0.0) ? ((knots[i + k + 1] - t) / denom2) * basisFunction(i + 1, k - 1, t) : 0.0;

    return term1 + term2;
}

// Evaluate 3D B-spline curve at parameter t
void  BSpline3D::evaluate(double t, vector<float>& mVertices, vector<float>& mColors)
{
    int n = 4;
    double x = 0.0, y = 0.0, z = 0.0;

    double basis = basisFunction(0, degree, t);
    x += basis * mP0.x();
    y += basis * mP0.y();
    z += basis * mP0.z();

    mVertices.push_back(x);
    mVertices.push_back(y);
    mVertices.push_back(z);

    mColors.push_back(0.0f);
    mColors.push_back(1.0f);
    mColors.push_back(0.0f);

    basis = basisFunction(1, degree, t);
    x += basis * mP1.x();
    y += basis * mP1.y();
    z += basis * mP1.z();

    mVertices.push_back(x);
    mVertices.push_back(y);
    mVertices.push_back(z);

    mColors.push_back(0.0f);
    mColors.push_back(1.0f);
    mColors.push_back(0.0f);

    basis = basisFunction(2, degree, t);
    x += basis * mP2.x();
    y += basis * mP2.y();
    z += basis * mP2.z();

    mVertices.push_back(x);
    mVertices.push_back(y);
    mVertices.push_back(z);

    mColors.push_back(0.0f);
    mColors.push_back(1.0f);
    mColors.push_back(0.0f);

    basis = basisFunction(3, degree, t);
    x += basis * mP3.x();
    y += basis * mP3.y();
    z += basis * mP3.z();

    mVertices.push_back(x);
    mVertices.push_back(y);
    mVertices.push_back(z);

    mColors.push_back(0.0f);
    mColors.push_back(1.0f);
    mColors.push_back(0.0f);

}

void BSpline3D::drawCurveBspline(vector<float>& mVertices, vector<float>& mColors)
{
    for (double t = 0.0; t <= 4.0; t += 0.01)
    {
        evaluate(t, mVertices, mColors);
    }
}