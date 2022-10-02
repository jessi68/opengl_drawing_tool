#pragma once
// static class is different from singleton that singleton can be passed as parameter. 
#include <algorithm>
#include "Polygon.h"
#include "Point.h"

using namespace std;

class PolygonAlgorithm
{
public:
    static bool isInside(vector<Point> polygon, int vertexNumber, Point p);
private:
    static bool onSegment(Point p, Point q, Point r);
    static int orientation(Point p, Point q, Point r);
    static bool isIntersect(Point p1, Point q1, Point p2, Point q2);
};

