#include "R_tree.h"
//double maxFrom(double, double); 
//double minFrom(double, double); 
void user_search(double a, double b, int radius, R_tree& Tree) {
    Tree.search(48.50099, 35.95139, radius, Tree.root->kid[0]);
    Tree.search(48.50099, 35.95139, radius, Tree.root->kid[1]);
}
int main()
{
    setlocale(LC_CTYPE, "");
    R_tree Tree;
    Tree.reading_from_file("C:/Users/User/coding/Labs 1.2/Laba-5/Lab 5/Lab 5/ukraine_poi.csv");
    while (true) {
        double a, b;
        int r;
        cout << "Enter lat: ";
        cin >> a;
        cout << "Enter long: ";
        cin >> b;
        cout << "Enter radius: ";
        cin >> r;
        user_search(a, b, r, Tree);
        
   }

   

}

//double maxFrom(double a, double b) { 
// if (a > b) { 
//  return a; 
// } 
// else { 
//  return b; 
// } 
//} 
//double minFrom(double a, double b) { 
// if (a < b) { 
//  return a; 
// } 
// else { 
//  return b; 
// } 