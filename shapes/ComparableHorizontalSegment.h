/*
 * ComparableHorizontalSegment.h
 *
 *  Created on: Feb 22, 2016
 *      Author: ron
 */

#ifndef SHAPES_COMPARABLEHORIZONTALSEGMENT_H_
#define SHAPES_COMPARABLEHORIZONTALSEGMENT_H_

#include "HorizontalSegment.h"

class ComparableHorizontalSegment: public HorizontalSegment {
public:
	ComparableHorizontalSegment() : HorizontalSegment() {}
	ComparableHorizontalSegment(const ComparableHorizontalSegment & s)
		: HorizontalSegment(*((HorizontalSegment *) &s)) {}
	ComparableHorizontalSegment(double x1, double x2, double y)
		: HorizontalSegment(x1, x2, y) {}
	virtual ~ComparableHorizontalSegment() {}

	ComparableHorizontalSegment & operator=(const ComparableHorizontalSegment & s) {
		*((HorizontalSegment *) this) = *((HorizontalSegment *) &s);
		return *this;
	}

	bool operator<(const ComparableHorizontalSegment & s) const {
		if (GetY() < s.GetY()) return true;
		if (GetY() > s.GetY()) return false;
		if (GetX1() < s.GetX1()) return true;
		if (GetX1() > s.GetX1()) return false;
		return GetX2() < s.GetX2();
	}
	bool operator>(const ComparableHorizontalSegment & s) const {
		return s < *this;
	}
	bool operator!=(const ComparableHorizontalSegment & s) const {
		return *this < s || *this > s;
	}

	bool operator>=(const ComparableHorizontalSegment & s) const {
		return !(*this < s);
	}
	bool operator<=(const ComparableHorizontalSegment & s) const {
		return !(*this > s);
	}
	bool operator==(const ComparableHorizontalSegment & s) const {
		return !(*this != s);
	}
};

#endif /* SHAPES_COMPARABLEHORIZONTALSEGMENT_H_ */
