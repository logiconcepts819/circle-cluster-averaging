/*
 * ClusterReporter.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: ron
 */

#include "ClusterReporter.h"
#include <iostream>

using namespace std;

void ClusterReporter::OutputReport(size_t clusterThreshold,
		const std::vector<std::pair<std::set<Circle>, bool> > & foundClusters)
{
	cout << "Minimum number of circles in each cluster to count towards "
			"average: " << clusterThreshold << endl << endl;
	if (foundClusters.empty())
	{
		cout << "No clusters were found" << endl << endl;
	}
	else
	{
		cout << "Here are the clusters that were found:" << endl;

		size_t counter1 = 0;
		for (vector<pair<set<Circle>, bool> >::const_iterator
				it = foundClusters.begin(); it != foundClusters.end(); ++it)
		{
			cout << "\tCluster " << (++counter1) << " ("
			     << (it->second ? "": "not ") << "considered in the averaging "
				 "operation):" << endl;

			size_t counter2 = 0;
			for (set<Circle>::const_iterator it2 = it->first.begin();
					it2 != it->first.end(); ++it2)
			{
				cout << "\t\tCircle " << (++counter2) << ": center=("
				     << it2->GetCenterX() << ',' << it2->GetCenterY()
					 << "), radius=" << it2->GetRadius() << endl;
			}
		}
		cout << endl;
	}
}
