//
// Created by Madison Dienhart on 01/10/2021.
//
// Library class demonstrating partially filled arrays
// Can add/remove books from library
// findbooks in library

#include "library.h"
#include <iostream>


// constructor with default name
Library::Library(const string& Name) {
}


// destructor
// nothing on heap
Library::~Library() {
	// destructor
}

// true if book found in library
bool Library::isInLibrary(const string& BookName) const {
	for (int i = 0; i < count; i++) {
		if (Name[i] == BookName) {
			return true;
		}
	}
	return false;
}

// add a new book
// return true if successful, false if
// book already in library
bool Library::addBook(const string& BookName) {
	if (isInLibrary(BookName) == false) {
		Name[count] = BookName;
		count = count + 1;
		return true;
	}
	else {
		return false;
	}
}

// remove a book
// return true if successfully removed
// false if book not in library
bool Library::removeBook(const string& BookName) {
	for (int i = 0; i < count; i++) {
		if (Name[i] == BookName) {
			Name[i] = Name[count - 1];
			count = count - 1;
			return true;
		}
	}
	return false;
}

// list all books
void Library::listAllBooks() const {
	for (int i = 0; i < count; i++) {
		cout << Name[i] << endl;
	}
}

ostream& operator<<(ostream& Out, const Library& Lib) {
	Lib.listAllBooks();
	return Out;
}

Library& Library::operator+=(const Library& RHS)
{
	this->list = (this->list + RHS.list);

	return *this;
}