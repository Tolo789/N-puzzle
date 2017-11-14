#include <iostream>
#include <sstream>
#include <math.h>
#include "Node.class.hpp"

// === CONSTRUCTOR =============================================================

Node::Node(void) {
	// std::cout << "Node default constructor called" << std::endl;

	return ;
}

Node::Node(std::string configuration, size_t depth, Node *prevNode) : configuration(configuration), depth(depth), prevNode(prevNode) {
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

void Node::SetPuzzleSize(size_t newSize) {
	Node::puzzleSize = newSize;

	std::stringstream newConfig;
	// double root = sqrt(newSize);
	size_t i = 1;
	int direction = 0; // 0 = right, 1 = down, 2 = left, 3 = up
	size_t offset = 0;
	size_t steps = newSize - offset;
	int changeOffsetCount = 1; // usually change offset after 2 direction change, but at the beginning is after the first direction change
	size_t max = (newSize * newSize) - 1;
	size_t map[newSize][newSize];
	size_t x = 0;
	size_t y = 0;

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

			changeOffsetCount--;
			if (changeOffsetCount == 0) {
				changeOffsetCount = 2;
				offset++;
			}
			steps = newSize - offset;
		}

		if (direction == 0)
			x++;
		else if (direction == 1)
			y++;
		else if (direction == 2)
			x--;
		else if (direction == 3)
			y--;

		i++;
	}

	// print
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

	// save coords to find references faster
	// std::map<size_t, size_t[2]> newCoordMap;
	std::array<size_t, 2> tmp;
	y = 0;
	while (y < newSize) {
		x = 0;
		while (x < newSize) {
			tmp[0] = x;
			tmp[1] = y;
			// Node::coordMap.insert(std::pair<size_t, std::array<size_t, 2>(map[y][x], tmp));
			x++;
		}
		std::cout << '\n';
		y++;
	}
	// Node::coordMap = newCoordMap;
}

std::array<size_t, 2> Node::GetNumberFinalPos(size_t number) {
	std::map<size_t, std::array<size_t, 2> >::iterator it = Node::coordMap.find(number);

	// if (it != Node::coordMap.end())
		return it->second;
	// return NULL;
}

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

size_t Node::puzzleSize = 0;
size_t Node::heurChoice = 0;

std::map<size_t, std::array<size_t, 2> > Node::coordMap;
std::string Node::finalConfig = "";

// === END STATICVARS ==========================================================

// === EXCEPTIONS ==============================================================
// === END EXCEPTIONS ==========================================================
