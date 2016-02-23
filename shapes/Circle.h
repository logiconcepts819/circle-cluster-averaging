/*
 * Circle.h
 *
 *  Created on: Feb 22, 2016
 *      Author: ron
 */

#ifndef SHAPES_CIRCLE_H_
#define SHAPES_CIRCLE_H_

#include "ComparablePoint.h"

class Circle {
	ComparablePoint m_center;
	double m_radius;
public:
	Circle() : m_radius(0.0) {}
	Circle(const Circle & c) : m_center(c.m_center), m_radius(c.m_radius) {}
	Circle(const ComparablePoint & center, double r)
		: m_center(center), m_radius(r) {}
	Circle(double x, double y, double r) : m_center(x, y), m_radius(r) {}
	virtual ~Circle() {}

	virtual Circle & operator=(const Circle & c) {
		if (this != &c) { m_center = c.m_center; m_radius = c.m_radius; }
		return *this;
	}

	const ComparablePoint & GetCenter() const { return m_center; }
	double GetCenterX() const { return m_center.GetX(); }
	double GetCenterY() const { return m_center.GetY(); }
	virtual void SetCenter(const ComparablePoint & center) { m_center = center; }
	virtual void SetCenterX(double x) { m_center.SetX(x); }
	virtual void SetCenterY(double y) { m_center.SetY(y); }
	virtual void SetCenter(double x, double y) {
		SetCenterX(x); SetCenterY(y);
	}

	double GetRadius() const { return m_radius; }
	void SetRadius(double radius) { m_radius = radius; }

	bool FindIntersections(const Circle & other, bool & inftlyManySolns,
			Point & intersection1, Point & intersection2) const;

	bool OverlapExists(const Circle & other) const;

	bool operator<(const Circle & other) const {
		if (m_center < other.m_center) { return true; }
		if (m_center > other.m_center) { return false; }
		return m_radius < other.m_radius;
	}
	bool operator>(const Circle & c) const { return c < *this; }
	bool operator!=(const Circle & c) const { return *this < c || *this > c; }

	bool operator>=(const Circle & c) const { return !(*this < c); }
	bool operator<=(const Circle & c) const { return !(*this > c); }
	bool operator==(const Circle & c) const { return !(*this != c); }
};

#endif /* SHAPES_CIRCLE_H_ */
