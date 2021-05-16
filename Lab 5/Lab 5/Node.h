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

	Location upleft;
	Location downleft;
	Location upright;
	Location downright;
	vector<Location> locations;
	vector<Node> kid;
};