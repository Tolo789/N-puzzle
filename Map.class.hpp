#ifndef MAP_CLASS_HPP
# define MAP_CLASS_HPP

# include <string>

# include "Point.class.hpp"

class Map {

private:
	Map( void );

protected:

public:
	size_t		size;
	Point				**array;

	Map( size_t const size, std::string **input );
	Map( Map const & src );
	~Map( void );

	Map &	operator=( Map const & rhs );

	static int	getFinalPosition( size_t const value, size_t **map, size_t const size, size_t *finalCoords );
};

#endif
