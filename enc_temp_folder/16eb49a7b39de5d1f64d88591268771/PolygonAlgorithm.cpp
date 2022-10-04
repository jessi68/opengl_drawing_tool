#include "PolygonAlgorithm.h"
#include <iostream>
#include <cstdlib>

using namespace std;
// Define Infinite (Using INT_MAX caused overflow problems)
#define INF 10000

// Given three collinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool PolygonAlgorithm::onSegment(Point p, Point q, Point r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;
	return false;
}

int PolygonAlgorithm::orientation(Point p, Point q, Point r)
{
	float externalProductValue = 	(p.x - q.x) * (r.y - q.y) - (p.y - q.y) * (r.x - q.x) ;

	if (abs(externalProductValue) < 0.0001 ) return 0; // collinear
	return (externalProductValue > 0) ? 1 : 2; // 1: counterclockwise, 2: clockwise
}

bool PolygonAlgorithm::isIntersect(Point p1, Point q1, Point p2, Point q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and p2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
}

bool PolygonAlgorithm::isInside(vector<Point> polygon, int vertexNumber, Point p)
{
    // There must be at least 3 vertices in polygon[]
    if (vertexNumber < 3) return false;

    // Create a point for line segment from p to infinite
    Point extreme = { INF, p.y };

    // To count number of points in polygon
    // whose y-coordinate is equal to
    // y-coordinate of the point
    int decrease = 0;

    // Count intersections of the above line with sides of polygon
    int count = 0, i = 0;
    int next;
    do
    {
        next = i + 1;
        if (next >= vertexNumber) {
            next = 0;
        }
        
        if (polygon[i].y == p.y) decrease++;

        // Check if the line segment from 'p' to 'extreme' intersects
        // with the line segment from 'polygon[i]' to 'polygon[next]'

        if (isIntersect(polygon[i], polygon[next], p, extreme))
        {
            // If the point 'p' is collinear with line segment 'i-next',
            // then check if it lies on segment. If it lies, return true,
            // otherwise false
            if (orientation(polygon[i], p, polygon[next]) == 0) {
                cout << i << " x " << p.x << " yyyy " << p.y << next << endl;
                return onSegment(polygon[i], p, polygon[next]);
            } 
            count++;
        }
        i = next;
    } while (i != 0);

    // Reduce the count by decrease amount
    // as these points would have been added twice
    count -= decrease;
    
    cout << count << " count" << endl;
    // Return true if count is odd, false otherwise
    return count & 1; // Same as (count%2 == 1)
}
