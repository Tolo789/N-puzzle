#ifndef POINT_CLASS_HPP
# define POINT_CLASS_HPP

class Point {

private:

protected:

public:
	unsigned int	value;
	unsigned int	x_current;
	unsigned int	y_current;
	unsigned int	x_final;
	unsigned int	y_final;

	Point( void );
	Point( unsigned int const value,
		unsigned int const x_current,
		unsigned int const y_current,
		unsigned int const x_final,
		unsigned int const y_final );
	Point( Point const & src );
	~Point( void );

	Point &	operator=( Point const & rhs );

};

#endif
