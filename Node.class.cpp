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
	double root = sqrt(newSize);
	double i = 0;
	while (i < root) {
		i++;
	}
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
std::string Node::finalConfig = "";

// === END STATICVARS ==========================================================

// === EXCEPTIONS ==============================================================
// === END EXCEPTIONS ==========================================================
