//The header file associated with creature.cpp that locates
//and moves the creature recursively to find the path
//to exit.
#pragma once
#ifndef ASS3_CREATURE_H
#define ASS3_CREATURE_H

#include "maze.h"
#include <ostream>

class Creature {
public:
	//output to print out creatures location
	friend ostream& operator<<(ostream& Out, const Creature& Creature);

private:
	int Row; //variable for the Row used when finding paths
	int Col; //variable for column used when finding paths

public:
	Creature(int Row, int Col); //constructor
	string solve(Maze& Maze); //solve function
	bool atExit(const Maze& Maze) const; //determines if at exit
	string goNorth(Maze& Maze); //goNorth function
	string goSouth(Maze& Maze); //goSouth function
	string goEast(Maze& Maze); //goEast function
	string goWest(Maze& Maze); //goWest function
	
};

#endif //ASS3_CREATURE_H