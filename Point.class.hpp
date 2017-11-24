#ifndef POINT_CLASS_HPP
# define POINT_CLASS_HPP

# include <iostream>

class Point {

private:

protected:

public:
	size_t	value;
	size_t	x_current;
	size_t	y_current;
	size_t	x_final;
	size_t	y_final;

	Point( void );
	Point( size_t const value,
		size_t const x_current,
		size_t const y_current,
		size_t const x_final,
		size_t const y_final );
	Point( Point const & src );
	~Point( void );

	std::string		toString(void) const;

	Point &	operator=( Point const & rhs );

	static void		swapPoint( Point & p1, Point & p2 );

};

#endif
