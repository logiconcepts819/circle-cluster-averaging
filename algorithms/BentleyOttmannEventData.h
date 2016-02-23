/*
 * BentleyOttmannEventData.h
 *
 *  Created on: Feb 22, 2016
 *      Author: ron
 */

#ifndef ALGORITHMS_BENTLEYOTTMANNEVENTDATA_H_
#define ALGORITHMS_BENTLEYOTTMANNEVENTDATA_H_

#include "../shapes/Circle.h"
#include "../shapes/ComparableHorizontalSegment.h"

class BentleyOttmannEventData {
public:
	enum EventType {
		LEFT_ENDPOINT,
		RIGHT_ENDPOINT
	};
private:
	EventType m_evtType;
	ComparableHorizontalSegment m_segment;
	Circle m_circle;
public:
	BentleyOttmannEventData() : m_evtType(LEFT_ENDPOINT) {}
	BentleyOttmannEventData(const BentleyOttmannEventData & d)
		: m_evtType(d.m_evtType), m_segment(d.m_segment),
		  m_circle(d.m_circle) {}
	BentleyOttmannEventData(EventType evtType,
		const ComparableHorizontalSegment & segment, const Circle & circle)
		: m_evtType(evtType), m_segment(segment), m_circle(circle) {}
	virtual ~BentleyOttmannEventData() {}

	BentleyOttmannEventData & operator=(const BentleyOttmannEventData & d) {
		if (this != &d) {
			m_evtType = d.m_evtType; m_segment = d.m_segment;
			m_circle = d.m_circle;
		}
		return *this;
	}

	EventType GetEventType() const { return m_evtType; }
	void SetEventType(EventType evtType) { m_evtType = evtType; }

	const ComparableHorizontalSegment & GetSegment() const {
		return m_segment;
	}
	void SetSegment(const ComparableHorizontalSegment & segment) {
		m_segment = segment;
	}

	const Circle & GetCircle() const { return m_circle; }
	void SetCircle(const Circle & circle) { m_circle = circle; }
};

#endif /* ALGORITHMS_BENTLEYOTTMANNEVENTDATA_H_ */
