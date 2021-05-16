#include "R_tree.h"

R_tree::R_tree() {
    this->root = nullptr;
}

void R_tree::reading_from_file(std::string fileName) {
    ifstream inFile(fileName);

    if (!inFile.is_open()) {
        cout << "File is not opened" << endl;
    }
    else {
        cout << "File opened" << endl;
        string latitude, lontitude, type, subType, name, address;
        while (!inFile.eof()) {
            getline(inFile, latitude, ';');
            if (latitude == "\n") {
                break;
            }

            //change comas to dots in coordinates

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
                //make zero node from location which in future will be expanded to a big root node

                this->root = new Node(location, location, location, location);
                this->root->insert(location);
            }
            this->root->insert(location);
        }
        //function of forming the tree by spliting one big node first to smaller in order

        this->root->formTree();




        inFile.close();
    }
 
}

//search function for r_tree - if lenght between one of any adges 
void R_tree::search(double latitude, double longitude, double radius, Node node)
{
    // - if lenght between one of any adges will be less than radius - our location definitely inside of current node

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

        //if node are not finish and it has kids-node we must to go deeper with recurcion

        if (!node.kid.empty())
        {
            search(latitude, longitude, radius, node.kid[0]);
            search(latitude, longitude, radius, node.kid[1]);
        }
    }
}