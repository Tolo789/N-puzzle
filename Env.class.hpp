#ifndef ENV_HPP
# define ENV_HPP

# include <iostream>

/* OPTIONS VALUE */
# define	HEUR_MAN		0x01
# define	HEUR_2			0x02
# define	HEUR_3			0x04
# define	SIZE			0x08
# define	ITERATIONS		0xa0

# define	HEUR_CHAR		'h'
# define	SIZE_CHAR		's'
# define	ITERATIONS_CHAR	'i'

# define	HEUR_MAN_STR	"man"
# define	HEUR_2_STR		"2"
# define	HEUR_3_STR		"3"

# define	PARAMS_STR		"hsi"

/* MASKS */
# define	HEUR_MASK		0x07

typedef struct	s_puzzle {
	size_t	size;
	size_t	iterations;
}				t_puzzle;

class Env {

private:
	Env( Env const & src );
	~Env( void );
	Env &	operator=( Env const & rhs );

protected:

public:
	unsigned char	options;
	size_t			totalNumberOfStates;
	size_t			maxNumberOfState;
	size_t			numberOfMove;

	static t_puzzle	puzzle;

	Env( void );

};

#endif
