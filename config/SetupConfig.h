/*
 * SetupConfig.h
 *
 *  Created on: Feb 23, 2016
 *      Author: ron
 */

#ifndef CONFIG_SETUPCONFIG_H_
#define CONFIG_SETUPCONFIG_H_

#include <vector>
#include <string>
#include "../shapes/Circle.h"

namespace SetupConfig
{

bool ParseSetupConfig(const std::string & filename, size_t & clusterThreshold,
		std::vector<Circle> & circleSwarm);

}

#endif /* CONFIG_SETUPCONFIG_H_ */
