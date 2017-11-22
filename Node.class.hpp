#ifndef NODE_CLASS_HPP
# define NODE_CLASS_HPP

# include <string>
# include <map>

# include "Point.class.hpp"

class Node {

private:

	size_t		**getFinalMap( void );
	static int	getFinalPosition( size_t const value, size_t **map, size_t *finalCoords );
	size_t		manhattan(Point const &p);
	size_t		manhattanWithLinearConflict(Point const &p);
	size_t		manhattanLinearMisplaced(Point const &p);
	size_t		linearConflict(Point const &p, bool horizontalSearch);
	size_t		linearHorConflict(Point const &p);
	size_t		linearVertConflict(Point const &p);

protected:

public:
	static size_t			size;
	size_t					depth;	// g()
	size_t					score;	// h()
	std::map<size_t, Point>	points;
	size_t					**array;
	Node					*prev;

	Node( void );
	Node( std::string **input );
	Node( Node const & src );
	~Node( void );

	Node &	operator=( Node const & rhs );
	bool	operator<( const Node& rhs );
	bool	operator==( const Node& rhs );

	void			updateScore(void);
	std::string		toString(void);
	static bool		isSolvable( Node &node );

	/* Exception */
	class MissingMemberException : std::exception {

	private:
		MissingMemberException &	operator=( MissingMemberException const & rhs );

	protected:

	public:
		MissingMemberException( void ) throw();
		MissingMemberException( MissingMemberException const & src ) throw();
		virtual const char *what( void ) const throw();
		~MissingMemberException( void ) throw();

	};
};

#endif
