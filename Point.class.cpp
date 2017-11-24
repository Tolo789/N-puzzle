#include <sstream>

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

std::string		Point::toString(void) const {
	std::stringstream		s;

	s << "{ ";
	s << "value:" << this->value;
	s << ", x_current:" << this->x_current;
	s << ", y_current:" << this->y_current;
	s << ", x_final:" << this->x_final;
	s << ", y_final:" << this->y_final;
	s << " }" << std::endl;
	return (s.str());
}

void			Point::swapPoint( Point & p1, Point & p2 ) {
	size_t	tmp;

	tmp = p1.x_current;
	p1.x_current = p2.x_current;
	p2.x_current = tmp;
	tmp = p1.y_current;
	p1.y_current = p2.y_current;
	p2.y_current = tmp;
}

/* NON MEMBER FUNCTIONS ======================================================*/


/* OPERATOR ==================================================================*/
