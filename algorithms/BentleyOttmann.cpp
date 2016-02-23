/*
 * BentleyOttmann.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: ron
 */

#include "BentleyOttmann.h"

// Solution based on answers to question regarding linear sweep of circles at
// http://stackoverflow.com/questions/20265527

void BentleyOttmann::AddToDictionary(const BentleyOttmannEvent & event)
{
	m_segmentDict.insert(std::make_pair(event.GetData().GetSegment(),
			event.GetData().GetCircle()));
}

void BentleyOttmann::RemoveFromDictionary(const BentleyOttmannEvent & event)
{
	m_segmentDict.erase(event.GetData().GetSegment());
}

bool BentleyOttmann::PopNextEvent(BentleyOttmannEvent & event)
{
	bool nonEmpty = !m_eventQ.empty();
	if (nonEmpty)
	{
		event = m_eventQ.top();
		m_eventQ.pop();
	}
	return nonEmpty;
}

void BentleyOttmann::GetAdjacentCircles(const BentleyOttmannEvent & event,
		std::vector<Circle> & circles) const
{
	std::map<ComparableHorizontalSegment, Circle>::const_iterator it =
			m_segmentDict.find(event.GetData().GetSegment());

	circles.clear();
	if (it != m_segmentDict.end())
	{
		std::map<ComparableHorizontalSegment, Circle>::const_iterator it2 = it;
		if (it2 != m_segmentDict.begin()
				&& event.GetData().GetCircle() != (--it2)->second)
		{
			circles.push_back(it2->second);
		}

		if (++it != m_segmentDict.end()
				&& event.GetData().GetCircle() != it->second
				&& (circles.empty() || circles.back() != it->second))
		{
			circles.push_back(it->second);
		}
	}
}

void BentleyOttmann::AddCircle(double x, double y, double r)
{
	ComparablePoint p1(x - r, y - r);
	ComparablePoint p2(x + r, y - r);
	ComparablePoint p3(x - r, y + r);
	ComparablePoint p4(x + r, y + r);

	ComparableHorizontalSegment s1(x - r, x + r, y - r);
	ComparableHorizontalSegment s2(x - r, x + r, y + r);

	BentleyOttmannEventData d1(
			BentleyOttmannEventData::LEFT_ENDPOINT, s1, Circle(x, y, r));
	BentleyOttmannEventData d2(
			BentleyOttmannEventData::RIGHT_ENDPOINT, s2, Circle(x, y, r));

	m_eventQ.push(BentleyOttmannEvent(p1, d1));
	m_eventQ.push(BentleyOttmannEvent(p2, d2));
	m_eventQ.push(BentleyOttmannEvent(p3, d1));
	m_eventQ.push(BentleyOttmannEvent(p4, d2));
}

void BentleyOttmann::Explore()
{
	BentleyOttmannEvent event;
	while (PopNextEvent(event))
	{
		switch (event.GetData().GetEventType())
		{
		case BentleyOttmannEventData::LEFT_ENDPOINT:
		{
			std::vector<Circle> adjCircles;
			AddToDictionary(event);
			GetAdjacentCircles(event, adjCircles);
			m_Callback(event.GetData().GetCircle(), adjCircles,
					m_CallbackParams);
			break;
		}
		case BentleyOttmannEventData::RIGHT_ENDPOINT:
			RemoveFromDictionary(event);
			break;
		default:
			break;
		}
	}
}
