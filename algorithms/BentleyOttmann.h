/*
 * BentleyOttmann.h
 *
 *  Created on: Feb 22, 2016
 *      Author: ron
 */

#ifndef ALGORITHMS_BENTLEYOTTMANN_H_
#define ALGORITHMS_BENTLEYOTTMANN_H_

#include "../shapes/ComparableHorizontalSegment.h"
#include "BentleyOttmannEvent.h"
#include <cstddef>
#include <map>
#include <queue>
#include <vector>

class BentleyOttmann {
	// We want smaller values to take priority over larger values in the
	// priority queue (instead of the other way around as per default), so we
	// must have priority queue use the greater-than operator for comparisons
	std::priority_queue<BentleyOttmannEvent,
		std::vector<BentleyOttmannEvent>,
		std::greater<BentleyOttmannEvent> > m_eventQ;

	std::map<ComparableHorizontalSegment, Circle> m_segmentDict;

	void AddToDictionary(const BentleyOttmannEvent & event);
	void RemoveFromDictionary(const BentleyOttmannEvent & event);
	bool PopNextEvent(BentleyOttmannEvent & event);
	void GetAdjacentCircles(const BentleyOttmannEvent & event,
			std::vector<Circle> & circles) const;
public:
	typedef void (*ExplorationCB)(const Circle & targetCircle,
			const std::vector<Circle> & adjacentCircles, void * extraParams);
private:
	ExplorationCB m_Callback;
	void * m_CallbackParams;

public:
	BentleyOttmann() : m_Callback(NULL), m_CallbackParams(NULL) {}
	virtual ~BentleyOttmann() {}

	void SetCallback(ExplorationCB callback, void * extraParams = NULL) {
		m_Callback = callback; m_CallbackParams = extraParams;
	}

	void AddCircle(double x, double y, double r);
	void Explore();
};

#endif /* ALGORITHMS_BENTLEYOTTMANN_H_ */
