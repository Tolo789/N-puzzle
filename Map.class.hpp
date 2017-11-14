#ifndef MAP_CLASS_HPP
# define MAP_CLASS_HPP

# include <string>

# include "Point.class.hpp"

class Map {

private:
	Map( void );

protected:

public:
	unsigned int		size;
	Point				**array;

	Map( unsigned int const size, std::string const input );
	Map( Map const & src );
	~Map( void );

	Map &	operator=( Map const & rhs );

};

#endif
