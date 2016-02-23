/*
 * ClusterReporter.h
 *
 *  Created on: Feb 23, 2016
 *      Author: ron
 */

#ifndef REPORTER_CLUSTERREPORTER_H_
#define REPORTER_CLUSTERREPORTER_H_

#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include "../shapes/Circle.h"

namespace ClusterReporter
{

void OutputReport(size_t clusterThreshold,
		const std::vector<std::pair<std::set<Circle>, bool> > & foundClusters);

}

#endif /* REPORTER_CLUSTERREPORTER_H_ */
