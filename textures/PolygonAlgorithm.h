#pragma once
// static class is different from singleton that singleton can be passed as parameter. 
#include <algorithm>
#include "Shape.h"

using namespace std;

struct Point
{
    int x;
    int y;
};

static class PolygonAlgorithm
{
public:
    bool onSegment(Point p, Point q, Point r);
    int orientation(Point p, Point q, Point r);
    bool isIntersect(Point p1, Point q1, Point p2, Point q2);
    bool isInside(Point polygon[], int number, Point p);
};

