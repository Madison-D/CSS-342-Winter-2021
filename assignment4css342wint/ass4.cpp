// This is the main or driver file for ass4 
// a Skip List data structure to store integers 
#include <cassert>
#include <iostream>
#include <cstdlib>
#include "skiplist.h"

using namespace std;

//this function is the test1 function, provided in the starter file
//tests several functions including: add, remove, add(vector)
void test1() {
// setting seed for easy testing
  srand(10000);
  //srand(static_cast<unsigned int>(time(0)));
  SkipList skp(5, 80);
  cout << boolalpha;
  skp.add(3);
  skp.add(5);
  skp.add(vector<int>{1, 7, 9});
  // cannot add existing
  assert(!skp.add(vector<int>{1, 7}));
  cout << skp << endl;
  cout << "7 ? " << skp.contains(7) << endl;
  cout << "3 ? " << skp.contains(3) << endl;
  cout << "-100 ? " << skp.contains(-100) << endl;
  cout << "100 ? " << skp.contains(100) << endl;
  bool result = skp.remove(5);
  assert(result);
  result = skp.remove(5);
  assert(!result);
  cout << skp << endl;
}

//this function is my test2 function where I tested
//different/changed values 
/*
void test2(){
  // setting seed for easy testing
  srand(10000);
  //srand(static_cast<unsigned int>(time(0)));
  SkipList skp(5, 50);
  cout << boolalpha;
  skp.add(3);
  skp.add(5);
  skp.add(vector<int>{1, 2, 3, 4, 11, 7, 9});
  // cannot add existing
  assert(!skp.add(vector<int>{1, 7}));
  cout << skp << endl;
  cout << "7 ? " << skp.contains(7) << endl;
  cout << "3 ? " << skp.contains(3) << endl;
  cout << "-100 ? " << skp.contains(-100) << endl;
  cout << "100 ? " << skp.contains(100) << endl;
  bool result = skp.remove(5);
  assert(result);
  result = skp.remove(5);
  assert(!result);
  cout << skp << endl;
}
*/

//main function that calls the test functions
int main() {

  test1();
  //test2();

  cout << "Done." << endl;
  return 0;
}