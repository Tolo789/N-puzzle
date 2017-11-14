#include "Point.class.hpp"

/* STATIC VARIABLES ==========================================================*/


/* CONSTRUCTORS ==============================================================*/
Point::Point( void ) {

}

Point::Point( size_t const value,
	size_t const x_current,
	size_t const y_current,
	size_t const x_final,
	size_t const y_final ) :
	value(value),
	x_current(x_current),
	y_current(y_current),
	x_final(x_final),
	y_final(y_final) {

}

Point::Point( Point const & src ) {
	*this = src;
}

/* MEMBER OPERATORS OVERLOAD =================================================*/
Point		&Point::operator=( Point const & rhs ) {
	this->value = rhs.value;
	this->x_current = rhs.x_current;
	this->y_current = rhs.y_current;
	this->x_final = rhs.x_final;
	this->y_final = rhs.y_final;
	return ( *this );
}


/* DESTRUCTOR ================================================================*/
Point::~Point( void ) {
}

/* MEMBER FUNCTIONS ==========================================================*/


/* NON MEMBER FUNCTIONS ======================================================*/


/* OPERATOR ==================================================================*/
