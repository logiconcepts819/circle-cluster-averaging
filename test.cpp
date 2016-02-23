#include "ClusterAverage.h"
#include "config/SetupConfig.h"
#include "reporter/ClusterReporter.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char * argv[])
{
	if (argc <= 1)
	{
		cerr << "Usage: " << argv[0] << " INI-config-filename" << endl;
		return EXIT_FAILURE;
	}

	size_t clusterThreshold = 4;
	vector<Circle> circleSwarm;
	if (!SetupConfig::ParseSetupConfig(argv[1], clusterThreshold, circleSwarm))
	{
		return EXIT_FAILURE;
	}

	ClusterAverage avgClass(clusterThreshold);
	avgClass.SetSwarm(circleSwarm);

	double avgX, avgY;
	vector<pair<set<Circle>, bool> > foundClusters;
	bool avgFound = avgClass.ComputeAverage(avgX, avgY, &foundClusters);
	ClusterReporter::OutputReport(clusterThreshold, foundClusters);
	if (avgFound)
	{
		cout << "Average center: (" << avgX << ", " << avgY << ')' << endl;
	}
	else
	{
		cout << "No average found" << endl;
	}

	return EXIT_SUCCESS;
}
