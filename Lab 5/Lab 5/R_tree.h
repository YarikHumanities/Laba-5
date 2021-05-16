#pragma once
#include <fstream>
#include <iostream>
#include <cmath>
#include "Location.h"
#include "Node.h"

using namespace std;

class R_tree
{
public:
	Node* root;
	R_tree();
	void reading_from_file(std::string fileName);
	void search(double latitude, double longitude, double radius, Node rect);
};