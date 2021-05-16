#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Location.h"

class Node
{
public:
	Node(Location leftDown, Location leftUp, Location rightDown, Location rightUp);

	void insert(Location location);
	bool isinside(Location location);
	//void changel(Location location);
	double lenghth(double& longitude1, double& latitude1, double& longitude2, double& latitude2);
	void formTree();

	//four corners of the node

	Location upleft;
	Location downleft;
	Location upright;
	Location downright;

	//all of the locations that is contained in node - LEAVES
	vector<Location> locations;

	//all of the kids that is contained in node - ONLY OTHER NODES
	vector<Node> kid;
};