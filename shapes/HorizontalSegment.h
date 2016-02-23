/*
 * HorizontalSegment.h
 *
 *  Created on: Feb 22, 2016
 *      Author: ron
 */

#ifndef SHAPES_HORIZONTALSEGMENT_H_
#define SHAPES_HORIZONTALSEGMENT_H_

class HorizontalSegment {
	double m_x1;
	double m_x2;
	double m_y;
public:
	HorizontalSegment() : m_x1(0.0), m_x2(0.0), m_y(0.0) {}
	HorizontalSegment(const HorizontalSegment & s)
		: m_x1(s.m_x1), m_x2(s.m_x2), m_y(s.m_y) {}
	HorizontalSegment(double x1, double x2, double y)
		: m_x1(x1), m_x2(x2), m_y(y) {}
	virtual ~HorizontalSegment() {}

	HorizontalSegment & operator=(const HorizontalSegment & s) {
		if (this != &s) { m_x1 = s.m_x1; m_x2 = s.m_x2; m_y = s.m_y; }
		return *this;
	}

	double GetX1() const { return m_x1; }
	double GetX2() const { return m_x2; }
	double GetY() const { return m_y; }
	void SetX1(double x1) { m_x1 = x1; }
	void SetX2(double x2) { m_x2 = x2; }
	void SetY(double y) { m_y = y; }
};

#endif /* SHAPES_HORIZONTALSEGMENT_H_ */
