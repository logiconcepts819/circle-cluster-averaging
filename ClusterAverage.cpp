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

	for (std::vector<Circle>::const_iterator it = adjCircles.begin();
			it != adjCircles.end(); ++it)
	{
		if (it->OverlapExists(targetCircle))
		{
			// The circles overlap in some way

			std::map<Circle, size_t>::const_iterator it2 =
					circleClusterMap.find(*it);

			// Find a cluster containing the adjacent circle.  Otherwise,
			// create a new cluster with that adjacent circle.
			size_t clusterIdx1;
			if (it2 != circleClusterMap.end())
			{
				clusterIdx1 = it2->second;
			}
			else
			{
				std::set<Circle> clusterSet;
				clusterSet.insert(*it);

				clusterIdx1 = circleClusters.size();
				circleClusters.push_back(clusterSet);
				circleClusterMap.insert(std::make_pair(*it, clusterIdx1));
			}

			// Add the target circle to a cluster in some fashion, or if it
			// exists in a different cluster, merge the two clusters together.
			// Here, the objective is to ensure that no circle appears in more
			// than one cluster.
			std::set<Circle> & refClusterSet1 = circleClusters.at(clusterIdx1);
			it2 = circleClusterMap.find(targetCircle);
			if (it2 != circleClusterMap.end())
			{
				// Check whether a merge is necessary
				size_t clusterIdx2 = it2->second;
				if (clusterIdx2 != clusterIdx1)
				{
					// Merge the two clusters together
					std::set<Circle> & refClusterSet2 = circleClusters.at(
							clusterIdx2);
					while (!refClusterSet1.empty())
					{
						std::set<Circle>::iterator it3 = refClusterSet1.begin();
						refClusterSet2.insert(*it3);
						refClusterSet1.erase(it3);
						circleClusterMap.at(*it3) = clusterIdx2;
					}
				}
			}
			else
			{
				// Add the target circle to the cluster containing the adjacent
				// circle
				refClusterSet1.insert(targetCircle);
				circleClusterMap.insert(std::make_pair(targetCircle,
						clusterIdx1));
			}
		}
		else
		{
			// The circles don't overlap in any way
			size_t vecSize = circleClusters.size();

			// Make a new cluster containing adjacent circle if necessary
			if (circleClusterMap.find(*it) == circleClusterMap.end())
			{
				std::set<Circle> clusterSet;
				clusterSet.insert(*it);
				circleClusters.push_back(clusterSet);
				circleClusterMap.insert(std::make_pair(*it, vecSize++));
			}

			// Make a new cluster containing target circle if necessary
			if (circleClusterMap.find(targetCircle) == circleClusterMap.end())
			{
				std::set<Circle> clusterSet;
				clusterSet.insert(targetCircle);
				circleClusters.push_back(clusterSet);
				circleClusterMap.insert(std::make_pair(targetCircle, vecSize));
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
