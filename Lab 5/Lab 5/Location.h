#pragma once
#include<iostream>
#include <string>
using namespace std;
class Location
{
public:
	Location(double latitude, double longitude, std::string type, std::string subtype, std::string name, std::string street);
	void print_loc();
	double latitude;
	double longitude;
	std::string type;
	std::string subType;
	std::string name;
	std::string  address;
};