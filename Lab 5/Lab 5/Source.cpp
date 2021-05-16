#include<iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
const int maxleaf = 5;
//double maxFrom(double, double);
//double minFrom(double, double);
class Location {

	

public:
	double latitude;
	double longitude;
	string type;
	string subType;
	string name;
	string address;

	Location(double latitude, double longitude, string type, string subType, string name, string address) : latitude(latitude),
		longitude(longitude), type(type), subType(subType), name(name), address(address) {
	}

	void print_loc(/*double latitude, double longitude, string type, string subType, string name, string address*/) {
		cout << "Latitude: " << this->latitude << " Longitude: " << this->longitude << " Type: " << this->type << " SubType: " << 
			this->subType << " Name: " << this->name <<
			"Address: " << this->address << endl;
	}

};
class Node {
	

public:
	Location upleft;
	Location upright;
	Location downleft;
	Location downright;

	vector<Location> locations;
	vector<Node> kid;

	Node(Location upleft, Location upright, Location downleft, Location downright) :upleft(upleft), upright(upright),
		downleft(downleft), downright(downright) {}

	 //theory in ReadMe

	double lenght(double& longitude1, double& latitude1, double& longitude2, double& latitude2) {
		double radius = 6367444.65;
		double x1 = (longitude1 * 2 * acos(0.0)) / 180;
		double y1 = (latitude1 * 2 * acos(0.0)) / 180;
		double x2 = (longitude2 * 2 * acos(0.0)) / 180;
		double y2 = (latitude2 * 2 * acos(0.0)) / 180;

		double result = 2 * asin(sqrt(pow(sin((x2 - x1) / 2), 2) + cos(x2) * cos(x1) * pow(sin((y2 - y1) / 2), 2)))*radius;
		return result;
	}
	void form_tree() {
		if (this->locations.size() > 5) {
			double width = lenght(this->upleft.latitude, this->upleft.longitude, this->upright.latitude, this->upright.longitude);
			double height = lenght(this->upleft.latitude, this->upleft.longitude, this->downleft.latitude, this->downleft.longitude);
			if (width > height) {
				double halfWidth = this->upleft.latitude + abs(this->upleft.latitude - this->upright.latitude) / 2;
				Location  up(halfWidth, this->upleft.longitude, this->upleft.type, this->upleft.subType, this->upleft.name, this->upleft.address);
				Location down(halfWidth, this->downleft.longitude, this->upleft.type, this->upleft.subType, this->upleft.name, this->upleft.address);
				Node rectLeft(this->downleft, this->upleft, down, up);
				Node rectRight(down, up, this->downright, this->upright);
				while (this->locations.size() > 0) {

					if (rectLeft.isinside(this->locations[this->locations.size() - 1]))
						rectLeft.insert(this->locations[this->locations.size() - 1]);
					else
						rectRight.insert(this->locations[this->locations.size() - 1]);
					this->locations.pop_back();
				}
				this->kid.push_back(rectLeft);
				this->kid.push_back(rectRight);
				rectLeft.form_tree();
				rectRight.form_tree();
			}
			else {
				double halfHight = this->upleft.longitude + abs(this->upleft.longitude - this->downleft.longitude) / 2;
				Location  left(this->upleft.latitude, halfHight, this->upleft.type, this->upleft.subType, this->upleft.name, this->upleft.address);
				Location right(this->upright.latitude, halfHight, this->upleft.type, this->upleft.subType, this->upleft.name, this->upleft.address);
				Node rectUp(left, this->upleft, right, this->upright);
				Node rectDown(this->downleft, left, this->downright, right);
				while (this->locations.size() > 0) {
					if (rectUp.isinside(this->locations[this->locations.size() - 1]))
						rectUp.insert(this->locations[this->locations.size() - 1]);
					else
						rectDown.insert(this->locations[this->locations.size() - 1]);
					this->locations.pop_back();
				}
				this->kid.push_back(rectUp);
				this->kid.push_back(rectDown);
				this->kid[0].form_tree();
				this->kid[1].form_tree();
			}
		}
	}
	/*void form_tree()
	{
		if (this->locations.size() > 5)
		{
			double width = lenght(this->upleft.latitude, this->upleft.longitude, this->upright.latitude, this->upright.longitude);
			double height = lenght(this->upleft.latitude, this->upleft.longitude, this->downleft.latitude, this->downleft.longitude);
			if (width > height)
			{
				Location  up(this->upleft.latitude + abs(this->upleft.latitude - this->upright.latitude) / 2, this->upleft.longitude, this->upleft.type, this->upleft.subType, this->upleft.name, this->upleft.address);
				Location down(this->upleft.latitude + abs(this->upleft.latitude - this->upright.latitude) / 2, this->downleft.longitude, this->upleft.type, this->upleft.subType, this->upleft.name, this->upleft.address);
				Node childL(this->downleft, this->upleft, down, up);
				Node childR(down, up, this->downright, this->upright);
				while (this->locations.size() > 0)
				{
					if (childL.isinside(this->locations[this->locations.size() - 1]))
						childL.insert(this->locations[this->locations.size() - 1]);
					else
						childR.insert(this->locations[this->locations.size() - 1]);
					this->locations.pop_back();
				}
				this->kid.push_back(childL);
				this->kid.push_back(childR);
				childL.form_tree();
				childR.form_tree();
				
				
			}
			else
			{
				Location  left(this->upleft.latitude, this->upleft.longitude + abs(this->upleft.longitude - this->downleft.longitude) / 2,
					this->upleft.type, this->upleft.subType, this->upleft.name, this->upleft.address);
				Location right(this->upright.latitude, this->upleft.longitude + abs(this->upleft.longitude - this->downleft.longitude) / 2,
					this->upleft.type, this->upleft.subType, this->upleft.name, this->upleft.address);
				Node rectUp(left, this->upleft, right, this->upright);
				Node rectD(this->downleft, left, this->downright, right);
				while (this->locations.size() > 0)
				{
					if (rectUp.isinside(this->locations[this->locations.size() - 1]))
						rectUp.insert(this->locations[this->locations.size() - 1]);
					else
						rectD.insert(this->locations[this->locations.size() - 1]);
					this->locations.pop_back();
				}
				this->kid.push_back(rectUp);
				this->kid.push_back(rectD);
				this->kid[0].form_tree();
				this->kid[1].form_tree();
				
			}
		}
	}*/
	bool isinside(Location loc)
	{
		return loc.longitude >= this->upleft.longitude && loc.longitude <= this->downleft.longitude
			&& loc.latitude >= this->upleft.latitude && loc.latitude <= this->upright.latitude;
	}
	void change(Location location) {
		double up = min(this->upleft.longitude, location.longitude);
		double down = max(this->downleft.longitude, location.longitude);
		double left = min(this->downleft.latitude, location.latitude);
		double right = max(this->downright.latitude, location.latitude);
		this->upleft.longitude = up;
		this->upright.longitude = up;
		this->downleft.longitude = down;
		this->downright.longitude = down;
		this->downleft.latitude = left;
		this->upleft.latitude = left;
		this->downright.latitude = right;
		this->upright.latitude = right;
	}
	void insert(Location loc) {
		if (!this->isinside(loc)) 
		{
			//finish up
			//changing size of current node if locations does not fits
			/*this->upleft.longitude = min(this->upleft.longitude, loc.longitude);
			this->downleft.longitude = max(this->downleft.longitude, loc.longitude);
			this->upright.longitude = min(this->upleft.longitude, loc.longitude);
			this->downright.longitude = max(this->downleft.longitude, loc.longitude);

			this->downleft.latitude = min(this->downleft.latitude, loc.latitude);
			this->upleft.latitude = min(this->downleft.latitude, loc.latitude);
			this->downright.latitude = max(this->downright.latitude, loc.latitude);
			this->upright.latitude = max(this->downright.latitude, loc.latitude);*/
			this->change(loc);
		}
		//adding locs to current node
		locations.push_back(loc);
	}
};





class R_tree {
public:

	Node* root;

	R_tree() {
		this->root = nullptr;

	}
	void reading_from_file(string naming) {
		ifstream inFile("C:/Users/User/coding/Labs 1.2/Laba-5/Lab 5/Lab 5/mainFile.csv");
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
				//loc.print_loc();
				if (this->root == nullptr) {
					this->root = new Node(loc, loc, loc, loc);
					this->root->insert(loc);
				}
				this->root->insert(loc);
			}

			this->root->form_tree();
			inFile.close();
		}

	}

	void search(double latitude, double longitude, double radius, Node node)
	{
		if (node.isinside(Location(latitude, longitude, "", "", "", "")) ||
			node.lenght(latitude, longitude, node.upleft.latitude, longitude) < radius ||
			node.lenght(latitude, longitude, node.upright.latitude, longitude) < radius || 
			node.lenght(latitude, longitude, latitude, node.upleft.longitude) < radius || 
			node.lenght(latitude, longitude, latitude, node.downleft.longitude) < radius)
		{
			for (int i = 0; i < node.locations.size(); i++)
			{
				if (node.lenght(latitude, longitude, node.locations[i].latitude, node.locations[i].longitude) < radius)
				{
					cout << node.locations[i].name << " " << node.locations[i].type << " " <<
						node.locations[i].subType << " " << node.locations[i].address << " " <<
						node.locations[i].latitude << " " << node.locations[i].longitude << endl;
				}
			}
			if (!node.kid.empty())
			{
				search(latitude, longitude, radius, node.kid[0]);
				search(latitude, longitude, radius, node.kid[1]);
			}
		}
	}
};





int main() {
	setlocale(LC_ALL, "rus");
	R_tree Tree;
	Tree.reading_from_file("C:/Users/User/coding/Labs 1.2/Laba-5/Lab 5/Lab 5/mainFile.csv");
	/*Tree.search(50.44353, 30.48964, 400, Tree.root->kid[0]);
	Tree.search(50.44353, 30.48964, 400, Tree.root->kid[1]);*/
	Tree.search(50.39195, 30.45944, 500, Tree.root->kid[0]);
	Tree.search(50.39195, 30.45944, 500, Tree.root->kid[1]);
	cout << "===============================" << endl;
	Tree.search(48.50099, 35.95139, 500, Tree.root->kid[0]);
	Tree.search(48.50099, 35.95139, 500, Tree.root->kid[1]);

}

//double maxFrom(double a, double b) {
//	if (a > b) {
//		return a;
//	}
//	else {
//		return b;
//	}
//}
//double minFrom(double a, double b) {
//	if (a < b) {
//		return a;
//	}
//	else {
//		return b;
//	}
//}