/*
 * BentleyOttmanEvent.h
 *
 *  Created on: Feb 22, 2016
 *      Author: ron
 */

#ifndef ALGORITHMS_BENTLEYOTTMANNEVENT_H_
#define ALGORITHMS_BENTLEYOTTMANNEVENT_H_

#include "../shapes/ComparablePoint.h"
#include "BentleyOttmannEventData.h"

class BentleyOttmannEvent {
	ComparablePoint m_point;
	BentleyOttmannEventData m_data;
public:
	BentleyOttmannEvent() {}
	BentleyOttmannEvent(const BentleyOttmannEvent & e)
		: m_point(e.m_point), m_data(e.m_data) {}
	BentleyOttmannEvent(const ComparablePoint & point,
			const BentleyOttmannEventData & data)
		: m_point(point), m_data(data) {}
	virtual ~BentleyOttmannEvent() {}

	BentleyOttmannEvent & operator=(const BentleyOttmannEvent & e) {
		if (this != &e) { m_point = e.m_point; m_data = e.m_data; }
		return *this;
	}

	const ComparablePoint & GetPoint() const { return m_point; }
	void SetPoint(const ComparablePoint & point) { m_point = point; }

	const BentleyOttmannEventData & GetData() const { return m_data; }
	void SetData(const BentleyOttmannEventData & data) { m_data = data; }

	bool operator<(const BentleyOttmannEvent & e) const {
		return m_point < e.m_point;
	}
	bool operator>(const BentleyOttmannEvent & e) const {
		return m_point > e.m_point;
	}
	bool operator!=(const BentleyOttmannEvent & e) const {
		return m_point != e.m_point;
	}
	bool operator>=(const BentleyOttmannEvent & e) const {
		return m_point >= e.m_point;
	}
	bool operator<=(const BentleyOttmannEvent & e) const {
		return m_point <= e.m_point;
	}
	bool operator==(const BentleyOttmannEvent & e) const {
		return m_point == e.m_point;
	}
};

#endif /* ALGORITHMS_BENTLEYOTTMANNEVENT_H_ */
