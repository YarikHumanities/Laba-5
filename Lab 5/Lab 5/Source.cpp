#include<iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#define rad 6367444.65;
using namespace std;
const int maxleaf = 5;
double maxFrom(double, double);
double minFrom(double, double);
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
	vector<Node> kid;

	Node(Location up_left, Location up_right, Location down_left, Location down_right) :up_left(up_left), up_right(up_right),
		down_left(down_left), down_right(down_right) {
	}

	 //theory in ReadMe

	double lenght(double& longitude1, double& latitude1, double& longitude2, double& latitude2) {
		double x1 = (longitude1 * 2 * acos(0.0)) / 180;
		double y1 = (latitude1 * 2 * acos(0.0)) / 180;
		double x2 = (longitude2 * 2 * acos(0.0)) / 180;
		double y2 = (latitude2 * 2 * acos(0.0)) / 180;

		double result = 2 * asin(sqrt(pow(sin((x2 - x1) / 2), 2) + cos(x2) * cos(x1) * pow(sin((y2 - y1) / 2), 2)))*rad;
		return result;
	}

	void form_tree()
	{
		if (this->locations_v.size() > maxleaf)
		{
			double width = lenght(this->up_left.latitude, this->up_left.longitude, this->up_right.latitude, this->up_right.longitude);
			double height = lenght(this->up_left.latitude, this->up_left.longitude, this->down_right.latitude, this->down_right.longitude);
			if (height > width)
			{
				//double halfHight = this->up_left.longitude + abs(this->up_left.longitude - this->down_left.longitude) / 2;
				Location  left(this->up_left.latitude, this->up_left.longitude + abs(this->up_left.longitude - this->down_left.longitude) / 2, this->up_left.type, this->up_left.subType, this->up_left.name, this->up_left.address);
				Location right(this->up_right.latitude, this->up_left.longitude + abs(this->up_left.longitude - this->down_left.longitude) / 2, this->up_left.type, this->up_left.subType, this->up_left.name, this->up_left.address);
				Node rectUp(left, this->up_left, right, this->up_right);
				Node rectD(this->down_left, left, this->down_right, right);
				while (this->locations_v.size() > 0)
				{
					if (rectUp.isinside(this->locations_v[this->locations_v.size() - 1]))
						rectUp.insert(this->locations_v[this->locations_v.size() - 1]);
					else
						rectD.insert(this->locations_v[this->locations_v.size() - 1]);
					this->locations_v.pop_back();
				}
				
			}
			else
			{
				Location  up(this->up_left.latitude + abs(this->up_left.latitude - this->up_right.latitude) / 2, this->up_left.longitude, this->up_left.type, this->up_left.subType, this->up_left.name, this->up_left.address);
				Location down(this->up_left.latitude + abs(this->up_left.latitude - this->up_right.latitude) / 2, this->down_left.longitude, this->up_left.type, this->up_left.subType, this->up_left.name, this->up_left.address);
				Node childL(this->down_left, this->up_left, down, up);
				Node childR(down, up, this->down_right, this->up_right);
				while (this->locations_v.size() > 0)
				{
					if (childL.isinside(this->locations_v[this->locations_v.size() - 1]))
						childL.insert(this->locations_v[this->locations_v.size() - 1]);
					else
						childR.insert(this->locations_v[this->locations_v.size() - 1]);
					this->locations_v.pop_back();
				}
				this->kid.push_back(childL);
				this->kid.push_back(childR);
				childL.form_tree();
				childR.form_tree();
			}
		}
	}
	bool isinside(Location loc)
	{
		return loc.longitude >= this->up_left.longitude && loc.longitude <= this->down_left.longitude
			&& loc.latitude >= this->up_left.latitude && loc.latitude <= this->up_right.latitude;
	}
	void insert(Location loc) {
		if (!(loc.longitude >= this->up_left.longitude && loc.longitude <= this->down_left.longitude
			&& loc.latitude >= this->up_left.latitude && loc.latitude <= this->up_right.latitude)) 
		{
			//finish up
			//changing size of current node if locations does not fits
			this->up_left.longitude = min(this->up_left.longitude, loc.longitude);
			this->down_left.longitude = max(this->down_left.longitude, loc.longitude);
			this->up_right.longitude = min(this->up_left.longitude, loc.longitude);
			this->down_right.longitude = max(this->down_left.longitude, loc.longitude);

			this->down_left.latitude = min(this->down_left.latitude, loc.latitude);
			this->up_left.latitude = min(this->down_left.latitude, loc.latitude);
			this->down_right.latitude = max(this->down_right.latitude, loc.latitude);
			this->up_right.latitude = max(this->down_right.latitude, loc.latitude);
		}
		//adding locs to current node
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

			//changing comas to dots in coordinates

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

	void search(double latitude, double longitude, double radius, Node node)
	{

	}
};





int main() {
	R_tree Tree;
	Tree.reading_from_file("C:/Users/User/coding/Labs 1.2/Laba-5/Lab 5/Lab 5/file.csv");
}

double maxFrom(double a, double b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}
double minFrom(double a, double b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}