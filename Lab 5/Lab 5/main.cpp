#include "R_tree.h"
////double maxFrom(double, double); 
////double minFrom(double, double); 
int main()
{
    setlocale(LC_CTYPE, "");
    R_tree Tree;
    Tree.reading_from_file("G:/lab_rep/Laba-5/Lab 5/Lab 5/ukraine_poi.csv");
    Tree.search(48.56989, 39.3401, 400, Tree.root->kid[0]);
    Tree.search(48.56989, 39.3401, 400, Tree.root->kid[1]);
    cout << "===============================" << endl;
    Tree.search(48.58669, 23.69158, 500, Tree.root->kid[0]);
    Tree.search(48.58669, 23.69158, 500, Tree.root->kid[1]);
    cout << "===============================" << endl;
    Tree.search(48.50099, 35.95139, 500, Tree.root->kid[0]);
    Tree.search(48.50099, 35.95139, 500, Tree.root->kid[1]);

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