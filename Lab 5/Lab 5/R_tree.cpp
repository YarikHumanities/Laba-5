#include "R_tree.h"

R_tree::R_tree() {
    this->root = nullptr;
}

void R_tree::reading_from_file(std::string fileName) {
    ifstream inFile(fileName);
    cout << "File is open\n";
    if (inFile.is_open()) {
        string latitude, lontitude, type, subType, name, address;
        while (!inFile.eof()) {
            getline(inFile, latitude, ';');
            if (latitude == "\n") {
                break;
            }
            getline(inFile, lontitude, ';');
            for (int i = 0; i < latitude.size(); i++) {
                if (latitude[i] == ',') {
                    latitude[i] = '.';
                }
            }
            for (int i = 0; i < lontitude.size(); i++) {
                if (lontitude[i] == ',') {
                    lontitude[i] = '.';
                }
            }
            getline(inFile, type, ';');
            getline(inFile, subType, ';');
            getline(inFile, name, ';');
            getline(inFile, address, ';');
            Location location(stod(latitude), stod(lontitude), type, subType, name, address);
            if (this->root == nullptr)
            {
                this->root = new Node(location, location, location, location);
                this->root->insert(location);
            }
            this->root->insert(location);
        }
        this->root->formTree();
        inFile.close();
    }
    else {
        cout << "File wasn't opened" << endl;
    }
}
void R_tree::search(double latitude, double longitude, double radius, Node node)
{
    if (node.isinside(Location(latitude, longitude, "", "", "", "")) ||
        node.lenghth(latitude, longitude, node.upleft.latitude, longitude) < radius ||
        node.lenghth(latitude, longitude, node.upright.latitude, longitude) < radius ||
        node.lenghth(latitude, longitude, latitude, node.upleft.longitude) < radius ||
        node.lenghth(latitude, longitude, latitude, node.downleft.longitude) < radius)
    {
        for (int i = 0; i < node.locations.size(); i++)
        {
            if (node.lenghth(latitude, longitude, node.locations[i].latitude, node.locations[i].longitude) < radius)
            {
                cout << " Latitude:" << node.locations[i].latitude 
                    << " Longitude: " << node.locations[i].longitude 
                    <<"Name: "<<node.locations[i].name 
                    << " Type: " << node.locations[i].type 
                    << " Subtype: " <<node.locations[i].subType 
                    << " Adress: " << node.locations[i].address<<endl;
            }
        }
        if (!node.kid.empty())
        {
            search(latitude, longitude, radius, node.kid[0]);
            search(latitude, longitude, radius, node.kid[1]);
        }
    }
}