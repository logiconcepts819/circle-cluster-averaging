/*
 * ClusterAverage.h
 *
 *  Created on: Feb 18, 2016
 *      Author: ron
 */

#ifndef CLUSTERAVERAGE_H_
#define CLUSTERAVERAGE_H_

#include "shapes/Circle.h"
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <string.h>

class ClusterAverage {
	size_t m_ClusterThreshold;
	std::vector<Circle> m_Swarm;
public:
	ClusterAverage(size_t clusterThreshold = 4)
		: m_ClusterThreshold(clusterThreshold) {}
	virtual ~ClusterAverage() {}

	void AddToSwarm(const Circle & circle) {
		m_Swarm.push_back(circle);
	}

	void AddToSwarm(double x, double y, double r) {
		m_Swarm.push_back(Circle(x, y, r));
	}

	void SetSwarm(const std::vector<Circle> & swarm) {
		m_Swarm = swarm;
	}

	bool ComputeAverage(double & avgX, double & avgY,
			std::vector<std::pair<std::set<Circle>, bool> > * foundClusters = NULL);
};

#endif /* CLUSTERAVERAGE_H_ */
