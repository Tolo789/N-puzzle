#ifndef NODE_CLASS_HPP
# define NODE_CLASS_HPP

# include <string>
# include <map>

# include "Point.class.hpp"

class Node {

private:
	Node( void );

	size_t **getFinalMap(size_t size);
	static int	getFinalPosition( size_t const value, size_t **map, size_t const size, size_t *finalCoords );

protected:

public:
	size_t					size; // TODO: make it static
	size_t					depth;
	size_t					score;
	std::map<size_t, Point>	points;
	size_t					**array;
	Node					*prev;

	Node( size_t const size );
	Node( size_t const size, std::string **input );
	Node( Node const & src );
	~Node( void );

	Node &	operator=( Node const & rhs );
	bool	operator<( const Node& rhs );
	bool	operator==( const Node& rhs );

	void			updateScore(void);
	std::string		toString(void);
};

#endif
