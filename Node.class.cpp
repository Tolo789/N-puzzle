#include <iostream>
#include <sstream>
#include <string>

#include "Node.class.hpp"
#include "Env.class.hpp"


/* STATIC VARIABLES ==========================================================*/


/* CONSTRUCTORS ==============================================================*/
Node::Node( size_t const size ) : size(size) {
	std::srand(std::time(0));
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
		i++;
	}
	size_t	index;
	size_t	value;
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			size_t pos = 0;
			value = map[y][x];
			Point newPoint = Point(value, x, y, x, y);
			this->array[y][x] = value;
			this->points.insert(std::pair<size_t, Point>(value, newPoint));
		}
	}
	for (size_t i = 0; i < size; i++) {
		delete [] map[i];
	}
	delete [] map;
	size_t	lastMove = 0;
	Point	zero = this->points[0];
	int		neighbours;
	size_t	rand;
	size_t	tmpValue;

	Point	top;
	Point	left;
	Point	bottom;
	Point	right;
	for (size_t n = 0; n < Env::puzzle.iterations; n++) {
		neighbours = 0;
		if (zero.x_current > 0) {
			left = this->points[this->array[zero.y_current][zero.x_current - 1]];
			if (left.value != lastMove) {
				neighbours++;
			} else {
				left = zero;
			}
		} else {
			left = zero;
		}
		if (zero.y_current > 0) {
			top = this->points[this->array[zero.y_current - 1][zero.x_current]];
			if (top.value != lastMove) {
				neighbours++;
			} else {
				top = zero;
			}
		} else {
			top = zero;
		}
		if (zero.x_current < this->size - 1) {
			right = this->points[this->array[zero.y_current][zero.x_current + 1]];
			if (right.value != lastMove) {
				neighbours++;
			} else {
				right = zero;
			}
		} else {
			right = zero;
		}
		if (zero.y_current < this->size - 1) {
			bottom = this->points[this->array[zero.y_current + 1][zero.x_current]];
			if (bottom.value != lastMove) {
				neighbours++;
			} else {
				bottom = zero;
			}
		} else {
			bottom = zero;
		}

		// std::cout << "top:" << top.value << '\n';
		// std::cout << "left:" << left.value << '\n';
		// std::cout << "bottom:" << bottom.value << '\n';
		// std::cout << "right:" << right.value << '\n';
		rand = std::rand() % neighbours;
		// std::cout << "neighbours:"<<neighbours << '\n';
		if (rand == 0 && zero.value != left.value) {
			// std::cout << neighbours << " "<< rand << '\n';
			Point::swapPoint( this->points[0], this->points[left.value] );
			rand--;
			tmpValue = this->array[zero.y_current][zero.x_current];
			this->array[zero.y_current][zero.x_current] = this->array[left.y_current][left.x_current];
			this->array[left.y_current][left.x_current] = tmpValue;
		}
		else if (zero.value != left.value) {
			rand--;
		}
		if (rand == 0 && zero.value != bottom.value) {
			// std::cout << neighbours << " "<< rand << '\n';
			Point::swapPoint( this->points[0], this->points[bottom.value] );
			rand--;
			tmpValue = this->array[zero.y_current][zero.x_current];
			this->array[zero.y_current][zero.x_current] = this->array[bottom.y_current][bottom.x_current];
			this->array[bottom.y_current][bottom.x_current] = tmpValue;
		}
		else if (zero.value != bottom.value) {
			rand--;
		}
		if (rand == 0 && zero.value != top.value) {
			// std::cout << neighbours << " "<< rand << '\n';
			Point::swapPoint( this->points[0], this->points[top.value] );
			rand--;
			tmpValue = this->array[zero.y_current][zero.x_current];
			this->array[zero.y_current][zero.x_current] = this->array[top.y_current][top.x_current];
			this->array[top.y_current][top.x_current] = tmpValue;
		}
		else if (zero.value != top.value) {
			rand--;
		}
		if (rand == 0 && zero.value != right.value) {
			Point::swapPoint( this->points[0], this->points[right.value] );
			rand--;
			tmpValue = this->array[zero.y_current][zero.x_current];
			this->array[zero.y_current][zero.x_current] = this->array[right.y_current][right.x_current];
			this->array[right.y_current][right.x_current] = tmpValue;
		}
		else if (zero.value != right.value) {
			rand--;
		}
		zero = this->points[0];
		// std::cout << this->toString() << '\n';
	}
	Node::updateScore();
	// std::cout << top.toString() << '\n';
	// std::cout << left.toString() << '\n';
	// std::cout << bottom.toString() << '\n';
	// std::cout << right.toString() << '\n';
	// }
	// for (size_t y = 0; y < this->size * this->size; y++) {
	// 	std::cout << (this->points[y]).toString() << '\n';
	// }
	// std::cout << "--------------------------" << '\n';
	// Point::swapPoint( this->points[5], this->points[1] );
	// for (size_t y = 0; y < this->size * this->size; y++) {
		// std::cout << (this->points[y]).toString() << '\n';
	// }
	std::cout << this->toString() << '\n';
}

Node::Node( size_t const size, std::string **input ) : size(size) {
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
	this->points = rhs.points;

	this->array = new size_t*[this->size];
	for (size_t i = 0; i < this->size; i++) {
		this->array[i] = new size_t[this->size];
		for (size_t j = 0; j < size; j++) {
			this->array[i][j] = rhs.array[i][j];
		}
	}
	return ( *this );
}


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

	s << "Score: " << this->score << "\nPoints:\n";
	// std::map<size_t, Point>::iterator it;
	// for (it = this->points.begin(); it != this->points.end(); it++) {
	// 	s << "\t" << (it->second).toString();
	// }
	s << "Graphical:" << std::endl;
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
