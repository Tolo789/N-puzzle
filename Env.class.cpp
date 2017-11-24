#include "Env.class.hpp"

/* STATIC VARIABLES ==========================================================*/
unsigned short	Env::options = 0;
size_t			Env::printSpeed = 500;
size_t			Env::totalNumberOfStates = 0;
size_t			Env::maxNumberOfState = 0;
size_t			Env::numberOfMove = 0;
t_puzzle		Env::puzzle = {3, 10000};


/* CONSTRUCTORS ==============================================================*/
Env::Env( void ) {
}

/* MEMBER OPERATORS OVERLOAD =================================================*/
// Env		&Env::operator=( Env const & rhs ) {
// 	return (rhs);
// }


/* DESTRUCTOR ================================================================*/
Env::~Env( void ) {
}

/* MEMBER FUNCTIONS ==========================================================*/


/* NON MEMBER FUNCTIONS ======================================================*/


/* OPERATOR ==================================================================*/
