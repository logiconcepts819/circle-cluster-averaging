/*
 * ClusterAverage.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: ron
 */

#include "ClusterAverage.h"
#include "algorithms/BentleyOttmann.h"

using namespace std;

struct ClusterCBParams
{
	std::map<Circle, size_t> circleClusterMap;
	std::vector<std::set<Circle> > circleClusters;
};

static void ClusterCB(const Circle & targetCircle,
		const std::vector<Circle> & adjCircles, void * params)
{
	ClusterCBParams & cbParams = * (ClusterCBParams *) params;

	std::map<Circle, size_t> & circleClusterMap = cbParams.circleClusterMap;
	std::vector<std::set<Circle> > & circleClusters = cbParams.circleClusters;

	// Make a new cluster containing target circle if necessary
	std::map<Circle, size_t>::const_iterator targetIt =
		circleClusterMap.find(targetCircle);
	if (targetIt == circleClusterMap.end())
	{
		targetIt = circleClusterMap.insert(
			std::make_pair(targetCircle, circleClusters.size())).first;

		std::set<Circle> clusterSet;
		clusterSet.insert(targetCircle);
		circleClusters.push_back(clusterSet);
	}

	size_t targetIdx = targetIt->second;
	for (std::vector<Circle>::const_iterator it = adjCircles.begin();
			it != adjCircles.end(); ++it)
	{
		if (it->OverlapExists(targetCircle))
		{
			// The circles overlap in some way

			std::map<Circle, size_t>::const_iterator it2 =
					circleClusterMap.find(*it);

			// Find a cluster containing the adjacent circle. If it exists in
			// a cluster other than the one containing the target circle, merge
			// the two clusters together. If it doesn't exist in any cluster,
			// add the adjacent circle to the cluster containing the target
			// circle.
			if (it2 != circleClusterMap.end())
			{
				// Check whether a merge is necessary
				size_t adjacentIdx = it2->second;
				if (adjacentIdx != targetIdx)
				{
					// Merge the two clusters together so that the adjacent
					// circle and the target circle are in the same cluster
					std::set<Circle> & adjClusterSet = circleClusters.at(
							adjacentIdx);
					std::set<Circle> & tgtClusterSet = circleClusters.at(
							targetIdx);
					while (!adjClusterSet.empty())
					{
						std::set<Circle>::iterator it3 = adjClusterSet.begin();
						tgtClusterSet.insert(*it3);
						adjClusterSet.erase(it3);
						circleClusterMap.at(*it3) = targetIdx;
					}
				}
			}
			else
			{
				// Add the adjacent circle to the cluster containing the target
				// circle
				circleClusters.at(targetIdx).insert(*it);
				circleClusterMap.insert(std::make_pair(*it, targetIdx));
			}
		}
		else
		{
			// The circles don't overlap in any way, so we just make a new
			// cluster containing the adjacent circle if necessary
			if (circleClusterMap.find(*it) == circleClusterMap.end())
			{
				circleClusterMap.insert(std::make_pair(*it, circleClusters.size()));

				std::set<Circle> clusterSet;
				clusterSet.insert(*it);
				circleClusters.push_back(clusterSet);
			}
		}
	}
}

bool ClusterAverage::ComputeAverage(double & avgX, double & avgY,
		std::vector<std::pair<std::set<Circle>, bool> > * foundClusters) {

	BentleyOttmann bentOtt;
	for (std::vector<Circle>::const_iterator it = m_Swarm.begin();
			it != m_Swarm.end(); ++it)
	{
		bentOtt.AddCircle(it->GetCenterX(), it->GetCenterY(), it->GetRadius());
	}

	ClusterCBParams params;
	bentOtt.SetCallback(ClusterCB, &params);
	bentOtt.Explore();

	double sumX = 0.0;
	double sumY = 0.0;
	size_t numTermsInSum = 0;

	if (foundClusters)
	{
		foundClusters->clear();
	}

	for (std::vector<std::set<Circle> >::const_iterator
			it = params.circleClusters.begin();
			it != params.circleClusters.end(); ++it)
	{
		bool thresholdMet = it->size() >= m_ClusterThreshold;
		if (thresholdMet)
		{
			// Only accept a cluster that contains a certain number of circles
			for (std::set<Circle>::const_iterator it2 = it->begin();
					it2 != it->end(); ++it2, ++numTermsInSum)
			{
				sumX += it2->GetCenterX();
				sumY += it2->GetCenterY();
			}
		}

		if (foundClusters && !it->empty())
		{
			foundClusters->push_back(std::make_pair(*it, thresholdMet));
		}
	}

	if (numTermsInSum != 0)
	{
		avgX = sumX / numTermsInSum;
		avgY = sumY / numTermsInSum;
	}

	return numTermsInSum != 0;
}
