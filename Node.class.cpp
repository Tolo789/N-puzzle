#include <iostream>
#include <sstream>
#include <string>

#include "Node.class.hpp"


/* STATIC VARIABLES ==========================================================*/


/* CONSTRUCTORS ==============================================================*/
Node::Node( size_t const size, std::string **input ) : size(size), depth(0), prev(NULL) {
	this->array = new size_t*[size];
	for (size_t i = 0; i < size; i++) {
		this->array[i] = new size_t[size];
	}

	/* GENERATE FINAL MAP */
	size_t i = 1;
	int direction = 0; // 0 = right, 1 = down, 2 = left, 3 = up
	size_t offset = 0;
	size_t steps = size - offset;
	int changeOffsetCount = 1; // usually change offset after 2 direction change, but at the beginning is after the first direction change
	size_t max = (size * size) - 1;
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
			size_t pos = 0;
			value = static_cast<size_t>(std::stoi(input[y][x], &pos , 10));
			if (Node::getFinalPosition( value, map, size, finalCoords ) < 0) {
				/* ERROR HANDLING */
				std::cout << "ERROR" << std::endl;
			} else {
				Point newPoint = Point(value, x, y, finalCoords[0], finalCoords[1]);
				this->array[y][x] = value;
				this->points.insert(std::pair<size_t, Point>(value, newPoint));
			}
		}
	}
	this->updateScore();
	delete [] finalCoords;
	for (size_t i = 0; i < size; i++) {
		delete [] map[i];
	}
	delete [] map;
}

Node::Node( Node const & src ) {
	*this = src;
}

/* MEMBER OPERATORS OVERLOAD =================================================*/
Node		&Node::operator=( Node const & rhs ) {
	this->size = rhs.size;
	// std::cout << size << '\n';
	this->points = rhs.points;
	this->depth = rhs.depth;
	this->prev = rhs.prev;

	this->array = new size_t*[this->size];
	for (size_t i = 0; i < this->size; i++) {
		this->array[i] = new size_t[this->size];
		for (size_t j = 0; j < size; j++) {
			this->array[i][j] = rhs.array[i][j];
		}
	}
	return ( *this );
}

bool		Node::operator<( const Node& rhs ) {
	size_t lTotScore = this->depth + this->score;
	size_t rTotScore = rhs.depth + rhs.score;
	if (lTotScore < rTotScore)
		return true;
	else if (lTotScore > rTotScore)
		return false;
	else if (this->depth < rhs.depth)  // if same score, then compare depth
		return true;
	return false;
}

bool		Node::operator==( const Node& rhs ) {
	// consider equal with comparison of points, not of depth
	if (this->score != rhs.score)
		return false;

	size_t lSize = this->points.size();
	if (lSize != rhs.points.size())
		return false;

	std::map<size_t, Point>::iterator lIt = this->points.begin();
	std::map<size_t, Point>::const_iterator rIt = rhs.points.begin();
	while (lSize > 0) {
		if (lIt->second.x_current != rIt->second.x_current)
			return false;
		if (lIt->second.y_current != rIt->second.y_current)
			return false;
		lIt++;
		rIt++;
		lSize--;
	}
	return true;
}

// bool		Node::operator!=( const Node& rhs ) {
// 	return !(this == rhs);
// }


/* DESTRUCTOR ================================================================*/
Node::~Node( void ) {
	for (size_t i = 0; i < this->size; i++) {
		delete this->array[i];
	}
	delete this->array;
	this->points.clear();
}

/* MEMBER FUNCTIONS ==========================================================*/

int	Node::getFinalPosition(
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

void			Node::updateScore(void) {
	// TODO: score should depend on heuristic choice
	std::map<size_t, Point>::iterator it;
	this->score = 0;
	for (it = this->points.begin(); it != this->points.end(); it++) {
		if (it->second.value > 0) {
			if (it->second.x_current >= it->second.x_final)
				this->score += it->second.x_current - it->second.x_final;
			else
				this->score += it->second.x_final - it->second.x_current;

			if (it->second.y_current >= it->second.y_final)
				this->score += it->second.y_current - it->second.y_final;
			else
				this->score += it->second.y_final - it->second.y_current;
		}
	}

	return ;
}

std::string		Node::toString(void) {
	std::stringstream		s;

	s << "Score: " << this->score << ", Depth: " << this->depth << std::endl;
	// s << "Points:\n";
	// std::map<size_t, Point>::iterator it;
	// for (it = this->points.begin(); it != this->points.end(); it++) {
	// 	s << "\t" << (it->second).toString();
	// }
	// s << "Graphical:" << std::endl;
	size_t i = 0;
	size_t j;
	while (i < this->size) {
		j = 0;
		s << "\t";
		while (j < this->size) {
			if (j > 0)
				s << " ";
			s << this->array[i][j];
			j++;
		}
		s << std::endl;
		i++;
	}


	return (s.str());
}

/* NON MEMBER FUNCTIONS ======================================================*/


/* OPERATOR ==================================================================*/
