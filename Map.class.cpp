#include <iostream>
#include <string>
#include <stdlib.h>

#include "Map.class.hpp"


/* STATIC VARIABLES ==========================================================*/


/* CONSTRUCTORS ==============================================================*/
Map::Map( size_t const size, std::string **input ) : size(size) {
	this->array = (size_t**)malloc(sizeof(size_t) * size);
	for (size_t i = 0; i < size; i++) {
		this->array[i] = (size_t*)malloc(sizeof(size_t) * size);
	}

	/* GENERATE FINAL MAP */
	size_t i = 1;
	int direction = 0; // 0 = right, 1 = down, 2 = left, 3 = up
	size_t offset = 0;
	size_t steps = size - offset;
	int changeOffsetCount = 1; // usually change offset after 2 direction change, but at the beginning is after the first direction change
	size_t max = (size * size) - 1;
	// size_t map[size][size];
	size_t	**map = new size_t* [size];
	for (size_t i = 0; i < size; i++) {
		map[i] = new size_t [size];
	}
	size_t x = 0;
	size_t y = 0;

	// set to zero
	y = 0;
	while (y < size) {
		x = 0;
		while (x < size) {
			map[y][x] = 0;
			x++;
		}
		// std::cout << '\n';
		y++;
	}

	y = 0;
	x = 0;
	while (i <= max) {
		map[y][x] = i;
		steps--;
		if (steps == 0) {
			direction = (direction + 1) % 4;

			changeOffsetCount--;
			if (changeOffsetCount == 0) {
				changeOffsetCount = 2;
				offset++;
			}
			steps = size - offset;
		}

		switch (direction) {
			case 0:
				x++;
				break;
			case 1:
				y++;
				break;
			case 2:
				x--;
				break;
			case 3:
				y--;
				break;
			default:
				break;
		}
		// if (direction == 0)
		// else if (direction == 1)
		// else if (direction == 2)
		// else if (direction == 3)

		i++;
	}
	size_t	index;
	size_t	value;
	size_t	*finalCoords = new size_t [2];
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			// index = x + y * size;
			size_t pos = 0;
			value = static_cast<size_t>(std::stoi(input[y][x], &pos , 10));
			if (Map::getFinalPosition( value, map, size, finalCoords ) < 0) {
				/* ERROR HANDLING */
				std::cout << "ERROR" << std::endl;
			} else {
				Point newPoint = Point(value, x, y, finalCoords[0], finalCoords[1]);
				this->array[y][x] = value;
				this->points.insert(std::pair<size_t, Point>(value, newPoint));
			}
		}
	}
	delete [] finalCoords;
	for (size_t i = 0; i < size; i++) {
		delete [] map[i];
	}
	delete [] map;
}
Map::Map( Map const & src ) {
	*this = src;
}

/* MEMBER OPERATORS OVERLOAD =================================================*/
Map		&Map::operator=( Map const & rhs ) {
	// this->size = rhs->size;
	this->array = (size_t**)malloc(sizeof(size_t) * size);
	for (size_t i = 0; i < size; i++) {
		this->array[i] = (size_t*)malloc(sizeof(size_t) * size);
		for (size_t j = 0; j < size; j++) {
			this->array[i][j] = rhs.array[i][j];
		}
	}
	return ( *this );
}


/* DESTRUCTOR ================================================================*/
Map::~Map( void ) {
	for (size_t i = 0; i < this->size; i++) {
		free(this->array[i]);
	}
	free(this->array);
}

/* MEMBER FUNCTIONS ==========================================================*/

int		Map::getFinalPosition(
	size_t const value,
	size_t **map,
	size_t const size,
	size_t *finalCoords ) {
		for (size_t i = 0; i < size; i++) {
			for (size_t j = 0; j < size; j++) {
				if (value == map[i][j]) {
					finalCoords[0] = j;
					finalCoords[1] = i;
					return (0);
				}
			}
		}
		return (-1);
	}

	/* NON MEMBER FUNCTIONS ======================================================*/


	/* OPERATOR ==================================================================*/
