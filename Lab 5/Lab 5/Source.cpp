#include<iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#define rad 6367444.65;
using namespace std;


class Location {

	

public:
	double latitude;
	double longitude;
	string type;
	string subType;
	string name;
	string address;

	Location(double latitude_, double longitude_, string type_, string subType_, string name_, string address_) : latitude(latitude_),
		longitude(longitude_), type(type_), subType(subType_), name(name_), address(address_) {
	}

	void print_loc(/*double latitude, double longitude, string type, string subType, string name, string address*/) {
		cout << "Latitude: " << this->latitude << " Longitude: " << this->longitude << " Type: " << this->type << " SubType: " << 
			this->subType << " Name: " << this->name <<
			"Address: " << this->address << endl;
	}

};
class Node {
	

public:
	Location up_left;
	Location up_right;
	Location down_left;
	Location down_right;

	vector<Location> locations_v;

	Node(Location up_left, Location up_right, Location down_left, Location down_right) :up_left(up_left), up_right(up_right),
		down_left(down_left), down_right(down_right) {
	}
	double lenght(double& longitude1, double& latitude1, double& longitude2, double& latitude2) {
		double x1 = (longitude1 * 2 * acos(0.0)) / 180;
		double y1 = (latitude1 * 2 * acos(0.0)) / 180;
		double x2 = (longitude2 * 2 * acos(0.0)) / 180;
		double y2 = (latitude2 * 2 * acos(0.0)) / 180;

		double result = 2 * asin(sqrt(pow(sin((x2 - x1) / 2), 2) + cos(x2) * cos(x1) * pow(sin((y2 - y1) / 2), 2)))*rad;
		return result;
	}

	void insert(Location loc) {
		if (!(loc.longitude >= this->up_left.longitude && loc.longitude <= this->down_left.longitude
			&& loc.latitude >= this->up_left.latitude && loc.latitude <= this->up_right.latitude)) 
		{
			//finish up
		}
		locations_v.push_back(loc);

	}
};





class R_tree {
public:

	Node* root;

	R_tree() {
		this->root = nullptr;

	}
	void reading_from_file(string naming) {
		ifstream inFile("C:/Users/User/coding/Labs 1.2/Laba-5/Lab 5/Lab 5/file.csv");
		if (!inFile.is_open()) {
			cout << "Cannot open the file" << endl;
		}
		else {
			cout << "File opened" << endl;
			string latitude;
			string longitude;
			string type;
			string subType;
			string name;
			string address;
			while (!inFile.eof()) {
				getline(inFile, latitude, ';');
				if (latitude == "\n") {
					break;
				}
				for (int i = 0; i < latitude.size(); i++) {
					if (latitude[i] == ',') {
						latitude[i] = '.';
					}
				}
				getline(inFile, longitude, ';');
				for (int i = 0; i < longitude.size(); i++) {
					if (longitude[i] == ',') {
						longitude[i] = '.';
					}
				}
				getline(inFile, type, ';');
				getline(inFile, subType, ';');
				getline(inFile, name, ';');
				getline(inFile, address, ';');
			
				//stod() - string to double

				Location loc(stod(latitude), stod(longitude), type, subType, name, address);
				loc.print_loc();
			}
		}

	}

	void insert_loc(Location loc) {

	}
};





int main() {
	R_tree Tree;
	Tree.reading_from_file("C:/Users/User/coding/Labs 1.2/Laba-5/Lab 5/Lab 5/file.csv");
}