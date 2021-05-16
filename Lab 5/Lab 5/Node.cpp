#include "Node.h"

//Earth radius
double radius = 6367444.65;

Node::Node(Location downleft, Location upleft, Location downright, Location upright) : upleft(upleft),
downright(downright),
upright(upright),
downleft(downleft) {

}

//length between two locations (info about theory in README)

double Node::lenghth(double& longitude1, double& latitude1, double& longitude2, double& latitude2) {
    double x1 = (longitude1 * 2 * acos(0.0)) / 180;
    double y1 = (latitude1 * 2 * acos(0.0)) / 180;
    double x2 = (longitude2 * 2 * acos(0.0)) / 180;
    double y2 = (latitude2 * 2 * acos(0.0)) / 180;
    double result = 2 * asin(sqrt(pow(sin((x2 - x1) / 2), 2) + cos(x2) * cos(x1) * pow(sin((y2 - y1) / 2), 2))) * radius;
    return result;
}


//spliting nodes from the biggest root to leaves in order - actually forming of a R-tree

void Node::formTree() {

    //max quantity of leaves per node
    int maxLeaves = 5;
    if (this->locations.size() > maxLeaves) 
    {
        //parameters of node - rectangle actually

        double width = lenghth(this->upleft.latitude, this->upleft.longitude, this->upright.latitude, this->upright.longitude);
        double height = lenghth(this->upleft.latitude, this->upleft.longitude, this->downleft.latitude, this->downleft.longitude);

        // ===
        // = =
        // = =
        // === - form

        if (width > height) 
        {

            double halfWidth = this->upleft.latitude + abs(this->upleft.latitude - this->upright.latitude) / 2;
            Location  up(halfWidth, this->upleft.longitude, this->upleft.type, this->upleft.subType, this->upleft.name, this->upleft.address);
            Location down(halfWidth, this->downleft.longitude, this->upleft.type, this->upleft.subType, this->upleft.name, this->upleft.address);
            Node Left(this->downleft, this->upleft, down, up);
            Node Right(down, up, this->downright, this->upright);
            while (this->locations.size() > 0)
            {
                //chosing in which subNode locations should be contained

                if (Left.isinside(this->locations[this->locations.size() - 1]))
                    Left.insert(this->locations[this->locations.size() - 1]);
                else
                    Right.insert(this->locations[this->locations.size() - 1]);
                this->locations.pop_back();
            }

            this->kid.push_back(Left);
            this->kid.push_back(Right);
            Left.formTree();
            Right.formTree();
        }

        // ======
        // =    =
        // ====== - form

        else 
        {

            double halfHight = this->upleft.longitude + abs(this->upleft.longitude - this->downleft.longitude) / 2;
            Location  left(this->upleft.latitude, halfHight, this->upleft.type, this->upleft.subType, this->upleft.name, this->upleft.address);
            Location right(this->upright.latitude, halfHight, this->upleft.type, this->upleft.subType, this->upleft.name, this->upleft.address);
            Node node1(left, this->upleft, right, this->upright);
            Node node2(this->downleft, left, this->downright, right);
            while (this->locations.size() > 0) 
            {
                //chosing in which subNode locations should be contained

                if (node1.isinside(this->locations[this->locations.size() - 1]))
                    node1.insert(this->locations[this->locations.size() - 1]);
                else
                    node2.insert(this->locations[this->locations.size() - 1]);
                this->locations.pop_back();
            }
            this->kid.push_back(node1);

            this->kid.push_back(node2);

            this->kid[0].formTree();
            this->kid[1].formTree();
        }
    }
}

//checking if location is inside of current node function

bool Node::isinside(Location loc)
{
    bool check = loc.longitude >= this->upleft.longitude && 
        loc.longitude <= this->downleft.longitude && 
        loc.latitude >= this->upleft.latitude && 
        loc.latitude <= this->upright.latitude;
    return check;
}

//just insertion func

void Node::insert(Location loc) 
{
    //checking if loction is inside of the current node
    if (!this->isinside(loc)) 
    {
        //changing a size, increase, of current node if location is not inside of this node
        double up = min(this->upleft.longitude, loc.longitude);
        double down = max(this->downleft.longitude, loc.longitude);
        double left = min(this->downleft.latitude, loc.latitude);
        double right = max(this->downright.latitude, loc.latitude);
        this->upleft.longitude = up;
        this->upright.longitude = up;
        this->downleft.longitude = down;
        this->downright.longitude = down;
        this->downleft.latitude = left;
        this->upleft.latitude = left;
        this->downright.latitude = right;
        this->upright.latitude = right;
    }

    //pushing a location to a current node vector

    locations.push_back(loc);
}