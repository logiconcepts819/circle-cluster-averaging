/*
 * Point.h
 *
 *  Created on: Feb 22, 2016
 *      Author: ron
 */

#ifndef SHAPES_POINT_H_
#define SHAPES_POINT_H_

class Point {
	double m_x;
	double m_y;
public:
	Point() : m_x(0.0), m_y(0.0) {}
	Point(const Point & p) : m_x(p.m_x), m_y(p.m_y) {}
	Point(double x, double y) : m_x(x), m_y(y) {}
	virtual ~Point() {}

	Point & operator=(const Point & p) {
		if (this != &p) { m_x = p.m_x; m_y = p.m_y; }
		return *this;
	}

	double GetX() const { return m_x; }
	void SetX(double x) { m_x = x; }

	double GetY() const { return m_y; }
	void SetY(double y) { m_y = y; }

	void SetPoint(double x, double y) { SetX(x); SetY(y); }
};

#endif /* SHAPES_POINT_H_ */
