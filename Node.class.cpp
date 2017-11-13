#include <iostream>
#include <sstream>
#include "Node.hpp"

// === CONSTRUCTOR =============================================================

Node::Node(void) {
	std::cout << "Node default constructor called" << std::endl;

	return ;
}

Node::Node(std::string configuration, size_t size, Node *prevNode) {
	// TODO
	std::cout << "Node standard constructor called" << std::endl;

	this.score = this.GetScore(size);

	return ;
}

Node::Node(Node const & src) {
	std::cout << "Node copy constructor called" << std::endl;
	*this = src;

	return ;
}

Node::~Node(void) {
	std::cout << "Node destructor called" << std::endl;

	return ;
}

// === ENDCONSTRUCTOR ==========================================================

// === OPERATORS ===============================================================

Node& Node::operator=(Node const & rhs) {
	std::cout << "Node assignation operator called" << std::endl;
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

std::string const Node::serialize(void) const {
	// TODO
	std::stringstream debug_str;
	debug_str << "Node{}";

	return debug_str.str();
}

// === ENDOTHERS ===============================================================

// === STATICVARS ==============================================================
// === END STATICVARS ==========================================================

// === EXCEPTIONS ==============================================================
// === END EXCEPTIONS ==========================================================
