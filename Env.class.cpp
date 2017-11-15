#include "Env.class.hpp"
#include <stdio.h> //

/* STATIC VARIABLES ==========================================================*/
t_puzzle	Env::puzzle = {3, 10000};

/* CONSTRUCTORS ==============================================================*/
Env::Env( void ) :
options(0),
totalNumberOfStates(0),
maxNumberOfState(0),
numberOfMove(0) {
}

Env::Env( Env const & src ) {
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
