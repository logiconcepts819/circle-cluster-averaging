/*
 * ComparablePoint.h
 *
 *  Created on: Feb 22, 2016
 *      Author: ron
 */

#ifndef SHAPES_COMPARABLEPOINT_H_
#define SHAPES_COMPARABLEPOINT_H_

#include "Point.h"

class ComparablePoint: public Point {
public:
	ComparablePoint() : Point() {}
	ComparablePoint(const ComparablePoint & p) : Point(*((Point *) &p)) {}
	ComparablePoint(double x, double y) : Point(x, y) {}
	virtual ~ComparablePoint() {}

	ComparablePoint & operator=(const ComparablePoint & p) {
		*((Point *) this) = *((Point *) &p);
		return *this;
	}

	bool operator<(const ComparablePoint & p) const {
		if (GetX() < p.GetX()) return true;
		if (GetX() > p.GetX()) return false;
		return GetY() < p.GetY();
	}
	bool operator>(const ComparablePoint & p) const { return p < *this; }
	bool operator!=(const ComparablePoint & p) const {
		return *this < p || *this > p;
	}

	bool operator>=(const ComparablePoint & p) const { return !(*this < p); }
	bool operator<=(const ComparablePoint & p) const { return !(*this > p); }
	bool operator==(const ComparablePoint & p) const { return !(*this != p); }
};

#endif /* SHAPES_COMPARABLEPOINT_H_ */
