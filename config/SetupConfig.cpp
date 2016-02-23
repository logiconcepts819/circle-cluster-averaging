/*
 * SetupConfig.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: ron
 */

#include "SetupConfig.h"
#include "../3rd-party/INIParser/include/INIParser.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace std;
using namespace cppiniparser;

bool SetupConfig::ParseSetupConfig(const std::string & filename,
		size_t & clusterThreshold, std::vector<Circle> & circleSwarm)
{
	try
	{
		INIConfig config = INIParser::Read(filename);

		string thresholdStr = config.GetOption("setup", "ClusterThreshold");
		if (!(istringstream(thresholdStr) >> clusterThreshold))
		{
			cerr << "Invalid value for option 'ClusterThreshold': '"
			     << thresholdStr << '\'' << endl;
			return false;
		}

		size_t counter = 0;
		string circleOption = "Circle0";
		while (config.HasOption("setup", circleOption))
		{
			double centerX, centerY, radius;
			char c1, c2;

			string circleStr = config.GetOption("setup", circleOption);
			istringstream iss(circleStr);
			if ((iss >> centerX >> c1 >> centerY >> c2 >> radius) &&
					c1 == ',' && c2 == ',')
			{
				circleSwarm.push_back(Circle(centerX, centerY, radius));
			}
			else
			{
				cerr << "Invalid value for option '" << circleOption
				     << "': '" << circleStr << '\'' << endl;
			}

			ostringstream oss;
			oss << "Circle" << ++counter;
			circleOption = oss.str();
		}
	}
	catch (exception & e)
	{
		cerr << "INI parse failure: " << e.what() << endl;
		return false;
	}
	return true;
}
