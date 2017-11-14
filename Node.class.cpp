#include <iostream>
#include <sstream>
#include <math.h>
#include "Node.class.hpp"

// === CONSTRUCTOR =============================================================

Node::Node(void) {
	// std::cout << "Node default constructor called" << std::endl;

	return ;
}

Node::Node(std::string configuration, unsigned int depth, Node *prevNode) : configuration(configuration), depth(depth), prevNode(prevNode) {
	// TODO
	// std::cout << "Node standard constructor called" << std::endl;
	this->score = 0;

	return ;
}

Node::Node(Node const & src) {
	// std::cout << "Node copy constructor called" << std::endl;
	*this = src;

	return ;
}

Node::~Node(void) {
	// std::cout << "Node destructor called" << std::endl;

	return ;
}

// === ENDCONSTRUCTOR ==========================================================

// === OPERATORS ===============================================================

Node& Node::operator=(Node const & rhs) {
	std::cout << "Node assignation operator called" << rhs << std::endl;
	// TODO


	return *this;
}

std::ostream & operator<<(std::ostream & o, Node const & rhs) {
	// TODO
	o << rhs.serialize();

	return o;
}

// === ENDOPERATORS ============================================================

// === GET / SET ===============================================================
// === END GET / SET ===========================================================

// === OTHERS ==================================================================
/*
void Node::SetPuzzleSize(unsigned int newSize) {
	Node::puzzleSize = newSize;

	std::stringstream newConfig;
	// double root = sqrt(newSize);
	unsigned int i = 1;
	int direction = 0; // 0 = right, 1 = down, 2 = left, 3 = up
	unsigned int offset = 0;
	unsigned int steps = newSize - offset;
	int times = 1; // first time
	unsigned int max = (newSize * newSize) - 1;
	unsigned int map[newSize][newSize];
	unsigned int x = 0;
	unsigned int y = 0;

	// set to zero
	y = 0;
	while (y < newSize) {
		x = 0;
		while (x < newSize) {
			map[y][x] = 0;
			x++;
		}
		std::cout << '\n';
		y++;
	}

	y = 0;
	x = 0;
	while (i <= max) {
		map[y][x] = i;
		steps--;
		if (steps == 0) {
			direction = (direction + 1) % 4;
		}

		if (direction == 0)
			x++;
		else if (direction == 1)
			y++;
		else if (direction == 2)
			x--;
		else if (direction == 4)
			y--;
		i++;
	}

	y = 0;
	while (y < newSize) {
		x = 0;
		while (x < newSize) {
			std::cout << map[y][x] << " ";
			x++;
		}
		std::cout << '\n';
		y++;
	}
}
*/
void Node::SetPuzzleSize(unsigned int size) {
	Node::puzzleSize = size;

	unsigned int	map[size * size];
	int		v[2] = {1, 0};
	unsigned int	index = 0;
	unsigned int	i = 0;
	unsigned int	offset = 0;
	unsigned int	x = 0;
	unsigned int	y = 0;

	while (i < (size * size) - 1) {
		index = x + y * size;
		std::cout << index << std::endl;
		// map[index] = i;
		i += 1;
		x += v[0];
		y += v[1];
		if (y == x && x == size - offset && v[0] == 1) {
			v[0] = 0, v[1] = 1;
		} else if (x == size - offset && v[1] == 1) {
			v[0] = -1, v[1] = 0;
		} else if (x == offset && y == size - offset && v[0] == -1) {
			v[0] = 0, v[1] = -1;
		} else if (y == x && x == offset && v[1] == -1) {
			v[0] = 1, v[1] = 0;
			offset += 1;
			x = offset;
		}
	}
	// for (unsigned int i = 0; i < size; i++) {
	// 	std::cout << " " << map[i];
	// 	if (!(i % size)) {
	// 		std::cout << std::endl;
	// 	}
	// }
}

// void Node::SetFinalConfig(unsigned int size) {
// 	int		offset_x = 0;
// 	int		offset_y = 0;
// 	int		x = 1;
// 	int		y = 1;
// 	int		i = 0;
//
// 	while (i < (size * size) - 1) {
//
// 		i++;
// 	}
// }

std::string const Node::serialize(void) const {
	// TODO
	std::stringstream debug_str;
	debug_str << "Node{";

	debug_str << "config: " << this->configuration;
	debug_str << ", depth: " << this->depth;
	if (this->prevNode)
		debug_str << ", prev: " << this->prevNode;
	else
		debug_str << ", prev: NULL";


	debug_str << "}";

	return debug_str.str();
}

// === ENDOTHERS ===============================================================

// === STATICVARS ==============================================================

unsigned int Node::puzzleSize = 0;
unsigned int Node::heurChoice = 0;
std::string Node::finalConfig = "";

// === END STATICVARS ==========================================================

// === EXCEPTIONS ==============================================================
// === END EXCEPTIONS ==========================================================
