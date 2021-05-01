#include<iostream>
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
class Rectangle {
	Location up_left;
	Location up_right;
	Location down_left;
	Location down_right;
public:
	Rectangle(Location up_left, Location up_right, Location down_left, Location down_right) :up_left(up_left), up_right(up_right),
		down_left(down_left), down_right(down_right) {
	}

};
int main() {

}