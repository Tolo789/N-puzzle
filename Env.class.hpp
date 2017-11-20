#ifndef ENV_HPP
# define ENV_HPP

# include <iostream>

/* OPTIONS VALUE */
# define	HEUR_MAN		0x01
# define	HEUR_2			0x02
# define	HEUR_3			0x04
# define	SIZE			0x08
# define	ITERATIONS		0x10
# define	HELP			0x20
# define	SLOW_PRINT		0x40

# define	HEUR_CHAR		'e'
# define	SIZE_CHAR		's'
# define	ITERATIONS_CHAR	'i'
# define	HELP_CHAR		'h'
# define	SLOW_PRINT_CHAR	'p'

# define	HEUR_MAN_STR	"man"
# define	HEUR_2_STR		"2"
# define	HEUR_3_STR		"3"

# define	PARAMS_STR		"hesip"

/* MASKS */
# define	HEUR_MASK		0x07

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
	static unsigned char	options;
	static size_t			printSpeed;
	static size_t			totalNumberOfStates;
	static size_t			maxNumberOfState;
	static size_t			numberOfMove;

	static t_puzzle	puzzle;


};

#endif
