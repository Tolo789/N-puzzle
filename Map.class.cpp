#include <iostream>

#include "Map.class.hpp"


/* STATIC VARIABLES ==========================================================*/


/* CONSTRUCTORS ==============================================================*/
Map::Map( unsigned int const size, std::string const input ) : size(size) {
	this->array = new Point*[size];
	for (unsigned int i = 0; i < size; i++) {
		this->array[i] = new Point[size];
	}
	/* PUT INPUT IN ARRAY */
	std::cout << "input:" << std::endl << input << std::endl;
}
Map::Map( Map const & src ) {
	*this = src;
}

/* MEMBER OPERATORS OVERLOAD =================================================*/
Map		&Map::operator=( Map const & rhs ) {
	// this->size = rhs->size;
	this->array = new Point*[size];
	for (unsigned int i = 0; i < size; i++) {
		this->array[i] = new Point[size];
		for (unsigned int j = 0; j < size; j++) {
			this->array[i][j] = rhs.array[i][j];
		}
	}
	return ( *this );
}


/* DESTRUCTOR ================================================================*/
Map::~Map( void ) {
	for (unsigned int i = 0; i < this->size; i++) {
		delete [] this->array[i];
	}
	delete [] this->array;
}

/* MEMBER FUNCTIONS ==========================================================*/


/* NON MEMBER FUNCTIONS ======================================================*/


/* OPERATOR ==================================================================*/
