/*
 * Circle.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: ron
 */

#include "Circle.h"
#include <math.h>
#include <float.h>

bool Circle::FindIntersections(const Circle & other, bool & inftlyManySolns,
		Point & intersection1, Point & intersection2) const
{
	const double x1 = GetCenterX();
	const double y1 = GetCenterY();
	const double r1 = GetRadius();
	const double x2 = other.GetCenterX();
	const double y2 = other.GetCenterY();
	const double r2 = other.GetRadius();

    bool intersect;
    double x1mx2 = x1 - x2;
    double y1my2 = y1 - y2;
    double r1mr2 = r1 - r2;
    double x1mx22 = x1mx2 * x1mx2;
    double y1my22 = y1my2 * y1my2;
    double r1mr22 = r1mr2 * r1mr2;
    double dist2 = x1mx22 + y1my22;

    if (dist2 <= 4.0 * DBL_EPSILON)
    {
        // The centers of the two circles are the same, so we have either no
        // solution (if the radii are different) or infinitely many solutions
        // (if the radii are the same)
        intersect = r1mr22 <= 4.0 * DBL_EPSILON;
        if (intersect)
        {
            inftlyManySolns = true;
        }
        return intersect;
    }

    double r1pr2 = r1 + r2;
    double r1pr22 = r1pr2 * r1pr2;
    double xdisc = (dist2 - r1mr22) * (r1pr22 - dist2) * y1my22;
    intersect = xdisc >= 0.0;
    if (intersect)
    {
        // The two circles intersect at exactly two places
        double r12 = r1 * r1;
        double r22 = r2 * r2;
        double r22mr12 = r22 - r12;
        double y1my2sgn = y1my2 >= 0.0 ? 1.0 : -1.0;
        double x1px2 = x1 + x2;
        double y1py2 = y1 + y2;
        double r22pdist2 = r22 + dist2;
        double r22mdist2 = r22 - dist2;
        double t1 = r22mr12 * x1mx2 + dist2 * x1px2;
        double t2 = sqrt(xdisc);
        double t3 = r22 * y1my2 + dist2 * y1py2 - r12 * y1my2;
        // t4 should not be negative here
        double t4 = 2.0 * r12 * r22pdist2 - r22mdist2 * r22mdist2 - r12 * r12;
        double t5 = x1mx2 * y1my2sgn * sqrt(t4);
        double t6 = 0.5 / dist2;
        intersection1.SetX(t6 * (t1 - t2));
        intersection2.SetX(t6 * (t1 + t2));
        intersection1.SetY(t6 * (t3 + t5));
        intersection2.SetY(t6 * (t3 - t5));
        inftlyManySolns = false;
        intersect = true;
    }

    return intersect;
}

bool Circle::OverlapExists(const Circle & other) const
{
	double xdiff = GetCenterX() - other.GetCenterX();
	double ydiff = GetCenterY() - other.GetCenterY();
	double rsum = GetRadius() + other.GetRadius();

	// The two circles have some form of overlap if the distance between
	// their centers is at most the sum of their radii
	return xdiff * xdiff + ydiff * ydiff <= rsum * rsum;
}
