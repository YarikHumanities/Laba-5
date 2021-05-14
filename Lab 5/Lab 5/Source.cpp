#include<iostream>
#include <string>
#include <cmath>
using namespace std;
class Location {

private:
	double latitude;
	double longitude;
	string type;
	string subType;
	string name;
	string address;

public:
	Location(double latitude_, double longitude_, string type_, string subType_, string name_, string address_) : latitude(latitude_),
		longitude(longitude_), type(type_), subType(subType_), name(name_), address(address_) {
	}


};
class R_tree {

};
class Node {
	Location up_left;
	Location up_right;
	Location down_left;
	Location down_right;
public:
	Node(Location up_left, Location up_right, Location down_left, Location down_right) :up_left(up_left), up_right(up_right),
		down_left(down_left), down_right(down_right) {
	}
	double lenght(double longitude1, double latitude1, double longitude2, double latitude2) {
		double x1 = (longitude1 * 2 * acos(0.0)) / 180;
		double y1 = (latitude1 * 2 * acos(0.0)) / 180;
		double x2 = (longitude2 * 2 * acos(0.0)) / 180;
		double y2 = (latitude2 * 2 * acos(0.0)) / 180;

		double result = 2 * asin(sqrt(pow(sin((x2 - x1) / 2), 2) + cos(x2) * cos(x1) * pow(sin((y2 - y1) / 2), 2)));
	}
};



int main() {

}