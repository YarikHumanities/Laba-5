#include "Location.h"

Location::Location(double latitude, double longitude, std::string type, std::string subType, std::string name, std::string address)
	: latitude(latitude), longitude(longitude), type(type), subType(subType), name(name), address(address)
{}
void Location::print_loc()
{
	cout << "Latitude: " << this->latitude << " Longitude: " << this->longitude << " Type: " << this->type << " SubType: " <<
		this->subType << " Name: " << this->name <<"Address: " << this->address << endl;
}