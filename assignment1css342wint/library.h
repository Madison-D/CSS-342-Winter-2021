//
// Created by Yusuf Pisan on 3/26/18.
//
#ifndef ASS1_LIBRARY_H
#define ASS1_LIBRARY_H

#include <string>

// Only for class code, OK to use
using namespace std;

// Library holds books - can add, remove and list books
const int MAX_COUNT = 100;

class Library {
	// display all books in library
	friend ostream& operator<<(ostream& Out, const Library& Lib);
	Library& operator+=(const Library& RHS);
public:
	// constructor with default name
	explicit Library(const string& Name);
	// destructor
	virtual ~Library();

	// add a new book
	// return true if successful, false if
	// book already in library
	bool addBook(const string& BookName);

	// remove a book
	// return true if successfully removed
	// false if book not in library
	bool removeBook(const string& BookName);

	// list all books
	void listAllBooks() const;

	// true if book found in library
	bool isInLibrary(const string& BookName) const;
	string list;
private:
	string Name[MAX_COUNT];
	int count = 0;
	//string list;
};

#endif  // ASS1_LIBRARY_H
