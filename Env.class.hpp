#ifndef ENV_HPP
# define ENV_HPP

# include <iostream>

/* OPTIONS VALUE */
# define	HEUR_MAN		0x0001
# define	HEUR_2			0x0002
# define	HEUR_3			0x0004
# define	HEUR_4			0x0008
# define	SIZE			0x0010
# define	ITERATIONS		0x0020
# define	HELP			0x0040
# define	SLOW_PRINT		0x0080
# define	GREEDY			0x0100
# define	UNIFORM			0x0200

# define	HEUR_CHAR		'e'
# define	SIZE_CHAR		's'
# define	ITERATIONS_CHAR	'i'
# define	HELP_CHAR		'h'
# define	SLOW_PRINT_CHAR	'p'
# define	GREEDY_CHAR		'g'
# define	UNIFORM_CHAR	'u'

# define	HEUR_MAN_STR	"man"
# define	HEUR_2_STR		"linear"
# define	HEUR_3_STR		"misplaced"
# define	HEUR_4_STR		"all"

# define	PARAMS_STR		"hesipgu"

/* MASKS */
# define	HEUR_MASK		0x000f

typedef struct	s_puzzle {
	size_t	size;
	size_t	iterations;
}				t_puzzle;

class Env {

private:
	Env( void );
	Env( Env const & src );
	~Env( void );
	Env &	operator=( Env const & rhs );

protected:

public:
	static unsigned short	options;
	static size_t			printSpeed;
	static size_t			totalNumberOfStates;
	static size_t			maxNumberOfState;
	static size_t			numberOfMove;

	static t_puzzle	puzzle;


};

#endif
