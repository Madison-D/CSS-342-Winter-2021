// ass3.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include "creature.h"
#include "maze.h"
#include <cassert>

//This is the first test function
//it reads the original maze.txt file
//provided and prints it out with results of the
//path that was found.
void test() {
    Maze M("maze.txt");
    // cout << m << endl;
    Creature C(4, 4);
    cout << "Path: " << C.solve(M) << endl;
    cout << M << endl;
}

//This is my added test1 function that reads file maze1.txt
//it then compares the result with the correct answer using 
// assert.
void test1() {
    Maze M1("maze1.txt");
    // cout << m << endl;
    Creature C(6,13);
    cout << "Path: " << C.solve(M1) << endl;
    assert(C.solve(M1) == "NNNWWWWWWN"); //fix
    cout << M1 << endl;
}

//This is my added test2 function that reads file maze2.txt
//it then compares the result with the correct answer using 
//assert.
void test2() {
    Maze M2("maze2.txt");
    // cout << m << endl;
    Creature C(3, 13);
    cout << "Path: " << C.solve(M2) << endl;
    assert(C.solve(M2) == "NNWWWWWN");//fix
    cout << M2 << endl;
}

//This is my added test3 function that reads file maze3.txt
//it then compares the result with the correct answer using 
//assert.
void test3() {
    Maze M3("maze3.txt");
    // cout << m << endl;
    Creature C(6, 2);
    cout << "Path: " << C.solve(M3) << endl;
    assert(C.solve(M3) == "NNNNEEEEEN"); //fix
    cout << M3 << endl;
}

//The main function calls all four functions listed above 
//before printing "done."
int main() {
    test();
    test1();
    test2();
    test3();
    cout << "Done!" << std::endl;
    return 0;
}