Circle Cluster Averaging Test Tool
==================================

Introduction
------------

This test tool reads a set of circles in 2D space; breaks it up into clusters,
which are sets of circles that overlap one another; and averages all the
clusters that contain some minimum number of circles.

Build/cleanup instructions
--------------------------

To build the test tool, type the following command:

```
make
```

The output binary will have filename 'test'.

To clean everything up, type the following command:

```
make clean
```

Running the test tool
---------------------

You can run the test tool on one of the example config files in the example
directory, or you can make your own config file and pass its filename as an
argument to the test tool. The examples directory contains circle swarm
examples, each of which contain the cluster threshold and the swarm of circles
to be formed into clusters and then averaged. For example, when you run

```
/path/to/test /path/to/examples/swarm1.ini
```

you will see the following output:

```
Minimum number of circles in each cluster to count towards average: 4

Here are the clusters that were found:
	Cluster 1 (considered in the averaging operation):
		Circle 1: center=(1.9,1.9), radius=0.2
		Circle 2: center=(2,2), radius=0.25
		Circle 3: center=(2.1,2.1), radius=0.5
		Circle 4: center=(2.3,2.4), radius=0.3
	Cluster 2 (not considered in the averaging operation):
		Circle 1: center=(5,5), radius=1

Average center: (2.075, 2.1)
```
