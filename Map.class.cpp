#include <iostream>

#include "Map.class.hpp"


/* STATIC VARIABLES ==========================================================*/


/* CONSTRUCTORS ==============================================================*/
Map::Map( size_t const size, std::string const input ) : size(size) {
	this->array = new Point*[size];
	for (size_t i = 0; i < size; i++) {
		this->array[i] = new Point[size];
	}
	/* PUT INPUT IN ARRAY */
	// std::stringstream newConfig;
	// // double root = sqrt(newSize);
	// size_t i = 1;
	// int direction = 0; // 0 = right, 1 = down, 2 = left, 3 = up
	// size_t offset = 0;
	// size_t steps = newSize - offset;
	// int changeOffsetCount = 1; // usually change offset after 2 direction change, but at the beginning is after the first direction change
	// size_t max = (newSize * newSize) - 1;
	// size_t map[newSize][newSize];
	// size_t x = 0;
	// size_t y = 0;
	//
	// // set to zero
	// y = 0;
	// while (y < newSize) {
	// 	x = 0;
	// 	while (x < newSize) {
	// 		map[y][x] = 0;
	// 		x++;
	// 	}
	// 	std::cout << '\n';
	// 	y++;
	// }
	//
	// y = 0;
	// x = 0;
	// while (i <= max) {
	// 	map[y][x] = i;
	// 	steps--;
	// 	if (steps == 0) {
	// 		direction = (direction + 1) % 4;
	//
	// 		changeOffsetCount--;
	// 		if (changeOffsetCount == 0) {
	// 			changeOffsetCount = 2;
	// 			offset++;
	// 		}
	// 		steps = newSize - offset;
	// 	}
	//
	// 	if (direction == 0)
	// 		x++;
	// 	else if (direction == 1)
	// 		y++;
	// 	else if (direction == 2)
	// 		x--;
	// 	else if (direction == 3)
	// 		y--;
	//
	// 	i++;
	// }
	//
	// // print
	// y = 0;
	// while (y < newSize) {
	// 	x = 0;
	// 	while (x < newSize) {
	// 		std::cout << map[y][x] << " ";
	// 		x++;
	// 	}
	// 	std::cout << '\n';
	// 	y++;
	// }
	std::cout << "input:" << std::endl << input << std::endl;
}
Map::Map( Map const & src ) {
	*this = src;
}

/* MEMBER OPERATORS OVERLOAD =================================================*/
Map		&Map::operator=( Map const & rhs ) {
	// this->size = rhs->size;
	this->array = new Point*[size];
	for (size_t i = 0; i < size; i++) {
		this->array[i] = new Point[size];
		for (size_t j = 0; j < size; j++) {
			this->array[i][j] = rhs.array[i][j];
		}
	}
	return ( *this );
}


/* DESTRUCTOR ================================================================*/
Map::~Map( void ) {
	for (size_t i = 0; i < this->size; i++) {
		delete [] this->array[i];
	}
	delete [] this->array;
}

/* MEMBER FUNCTIONS ==========================================================*/


/* NON MEMBER FUNCTIONS ======================================================*/


/* OPERATOR ==================================================================*/
