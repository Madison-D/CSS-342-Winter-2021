//The creature class associated with creatur.h that locates
//and moves the creature recursively to find the path
//to exit.

#include "creature.h"

// Operator overload <<
// pre-condition, takes in Creature 
// post-condistion prints Out creature's location
std::ostream& operator<<(std::ostream& Out, const Creature& Creature) {
	Out << "Creature's location (" << 
		Creature.Col << ", " << Creature.Row << ')';
	return Out;
}

// Constructor for Creature
// pre-condition is the coordinates provided and used for Row and Col
// post-conditioninitializes ints Row and Col
Creature::Creature(int Row, int Col) : Row(Row), Col(Col) {}

// Checks if creature is at exit
// pre-condition, creature is not at exit of Maze
// post-condition, returns successfully when creature is at exit of Maze
bool Creature::atExit(const Maze& Maze) const {
	return (Row == Maze.getExitRow() && Col == Maze.getExitColumn());
}

// Solve function solves and returns Path from Maze
// pre-condition Creature is at starting point
// post-condition Creature is at exit and a path was obtained and returned
string Creature::solve(Maze& Maze) {
	string Path;
	Maze.markAsPath(Row, Col);
	if (atExit(Maze)) {
		return Path;
	}
	Path = goNorth(Maze);
	if (Path == "X") {
		Path = goWest(Maze);
		if (Path == "X") {
			Path = goEast(Maze);
			if (Path == "X") {
				Path = goSouth(Maze);
			}
		}
	}
	return Path;
}

// goNorth function
// pre-condition creature needs to move north
// post-condition moves creature north recursively through the Maze
string Creature::goNorth(Maze& Maze) {
	string newPath; 
	if (Maze.isClear(Row - 1, Col)) {
		Row--;
		Maze.markAsPath(Row, Col);
		if (atExit(Maze)) {
			newPath = "N";
		}
		else {
			newPath = goNorth(Maze);
			if (newPath == "X") {
				newPath = goWest(Maze);
				if (newPath == "X") {
					newPath = goEast(Maze);
					if (newPath == "X") {
						Maze.markAsVisited(Row, Col);
						Row++;
					}
				}
			}
		}
	}
	return "X";
}

// goWest function
// pre-condition creature needs to move west
// post-condition moves creature west recursively through the Maze
string Creature::goWest(Maze& Maze) {
	string newPath;
	if (Maze.isClear(Row, Col - 1)) {
		Col--;
		Maze.markAsPath(Row, Col);
		if (atExit(Maze)) {
			newPath = "W";
		}
		else {
			newPath = goNorth(Maze);
			if (newPath == "X") {
				newPath = goWest(Maze);
				if (newPath == "X") {
					newPath = goSouth(Maze);
					if (newPath == "X") {
						Maze.markAsVisited(Row, Col);
						Col++;
					}
				}
			}
		}
	}
	return "X";
}

// goEast function
// pre-condition creature needs to move east
// post-condition moves creature east recursively through the Maze
string Creature::goEast(Maze& Maze) {
	string newPath;
	if (Maze.isClear(Row, Col + 1)) {
		Col++;
		Maze.markAsPath(Row, Col);
		if (atExit(Maze)) {
			newPath = "E";
		}
		else {
			newPath = goNorth(Maze);
			if (newPath == "X") {
				newPath = goSouth(Maze);
				if (newPath == "X") {
					newPath = goEast(Maze);
					if (newPath == "X") {
						Maze.markAsVisited(Row, Col);
						Col--;
					}
				}
			}
		}
	}
	return "X";
}

// goSouth function
// pre-condition creature needs to move south
// post-condition moves creature south recursively through the Maze
string Creature::goSouth(Maze& Maze) {
	string newPath;
	if (Maze.isClear(Row + 1, Col)) {
		Row++;
		Maze.markAsPath(Row, Col);
		if (atExit(Maze)) {
			newPath = "S";
		}
		else {
			newPath = goWest(Maze);
			if (newPath == "X") {
				newPath = goSouth(Maze);
				if (newPath == "X") {
					newPath = goEast(Maze);
					if (newPath == "X") {
						Maze.markAsVisited(Row, Col);
						Row--;
					}
				}
			}
		}
	}
	return "X";
}