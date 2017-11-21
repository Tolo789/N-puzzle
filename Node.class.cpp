#include <iostream>
#include <sstream>
#include <string>

#include "Node.class.hpp"
#include "Env.class.hpp"


/* STATIC VARIABLES ==========================================================*/
size_t Node::size = 0;

/* CONSTRUCTORS ==============================================================*/

Node::Node( void ) : depth(0), prev(NULL) {
	std::srand(std::time(0));
	this->array = new size_t*[Node::size];
	for (size_t i = 0; i < Node::size; i++) {
		this->array[i] = new size_t[Node::size];
	}

	/* GENERATE FINAL MAP */
	size_t **map = getFinalMap();

	// Copy final map on Node and create related Points
	size_t	value;
	for (size_t y = 0; y < Node::size; y++) {
		for (size_t x = 0; x < Node::size; x++) {
			value = map[y][x];
			Point newPoint = Point(value, x, y, x, y);
			this->array[y][x] = value;
			this->points.insert(std::pair<size_t, Point>(value, newPoint));
		}
	}

	// Delete final map
	for (size_t i = 0; i < Node::size; i++) {
		delete [] map[i];
	}
	delete [] map;

	// Shuffle the puzzle
	size_t	lastMove = 0;
	Point	zero = this->points[0];
	int		neighbours;
	size_t	rand;
	size_t	tmpValue;

	Point	top;
	Point	left;
	Point	bottom;
	Point	right;
	for (size_t n = 0; n < Env::puzzle.iterations; n++) {
		neighbours = 0;
		if (zero.x_current > 0) {
			left = this->points[this->array[zero.y_current][zero.x_current - 1]];
			if (left.value != lastMove) {
				neighbours++;
			} else {
				left = zero;
			}
		} else {
			left = zero;
		}
		if (zero.y_current > 0) {
			top = this->points[this->array[zero.y_current - 1][zero.x_current]];
			if (top.value != lastMove) {
				neighbours++;
			} else {
				top = zero;
			}
		} else {
			top = zero;
		}
		if (zero.x_current < Node::size - 1) {
			right = this->points[this->array[zero.y_current][zero.x_current + 1]];
			if (right.value != lastMove) {
				neighbours++;
			} else {
				right = zero;
			}
		} else {
			right = zero;
		}
		if (zero.y_current < Node::size - 1) {
			bottom = this->points[this->array[zero.y_current + 1][zero.x_current]];
			if (bottom.value != lastMove) {
				neighbours++;
			} else {
				bottom = zero;
			}
		} else {
			bottom = zero;
		}

		rand = std::rand() % neighbours;
		if (rand == 0 && zero.value != left.value) {
			Point::swapPoint( this->points[0], this->points[left.value] );
			rand--;
			tmpValue = this->array[zero.y_current][zero.x_current];
			this->array[zero.y_current][zero.x_current] = this->array[left.y_current][left.x_current];
			this->array[left.y_current][left.x_current] = tmpValue;
		}
		else if (zero.value != left.value) {
			rand--;
		}
		if (rand == 0 && zero.value != bottom.value) {
			Point::swapPoint( this->points[0], this->points[bottom.value] );
			rand--;
			tmpValue = this->array[zero.y_current][zero.x_current];
			this->array[zero.y_current][zero.x_current] = this->array[bottom.y_current][bottom.x_current];
			this->array[bottom.y_current][bottom.x_current] = tmpValue;
		}
		else if (zero.value != bottom.value) {
			rand--;
		}
		if (rand == 0 && zero.value != top.value) {
			Point::swapPoint( this->points[0], this->points[top.value] );
			rand--;
			tmpValue = this->array[zero.y_current][zero.x_current];
			this->array[zero.y_current][zero.x_current] = this->array[top.y_current][top.x_current];
			this->array[top.y_current][top.x_current] = tmpValue;
		}
		else if (zero.value != top.value) {
			rand--;
		}
		if (rand == 0 && zero.value != right.value) {
			Point::swapPoint( this->points[0], this->points[right.value] );
			rand--;
			tmpValue = this->array[zero.y_current][zero.x_current];
			this->array[zero.y_current][zero.x_current] = this->array[right.y_current][right.x_current];
			this->array[right.y_current][right.x_current] = tmpValue;
		}
		else if (zero.value != right.value) {
			rand--;
		}
		zero = this->points[0];
	}
	Node::updateScore();
}

Node::Node( std::string **input ) : depth(0), prev(NULL) {
	this->array = new size_t*[Node::size];
	for (size_t i = 0; i < Node::size; i++) {
		this->array[i] = new size_t[Node::size];
	}

	/* GENERATE FINAL MAP */
	size_t **map = getFinalMap();

	size_t	value;
	size_t	*finalCoords = new size_t [2];
	for (size_t y = 0; y < Node::size; y++) {
		for (size_t x = 0; x < Node::size; x++) {
			size_t pos = 0;
			value = static_cast<size_t>(std::stoi(input[y][x], &pos , 10));
			if (Node::getFinalPosition( value, map, finalCoords ) < 0) {
				/* ERROR HANDLING */
				std::cout << "ERROR" << std::endl;
			} else {
				Point newPoint = Point(value, x, y, finalCoords[0], finalCoords[1]);
				this->array[y][x] = value;
				this->points.insert(std::pair<size_t, Point>(value, newPoint));
			}
		}
	}
	this->updateScore();

	// Delete everything
	delete [] finalCoords;
	for (size_t i = 0; i < Node::size; i++) {
		delete [] map[i];
	}
	delete [] map;
}

Node::Node( Node const & src ) {
	*this = src;
}

/* MEMBER OPERATORS OVERLOAD =================================================*/
Node		&Node::operator=( Node const & rhs ) {
	this->points = rhs.points;
	this->depth = rhs.depth;
	this->prev = rhs.prev;

	this->array = new size_t*[Node::size];
	for (size_t i = 0; i < Node::size; i++) {
		this->array[i] = new size_t[Node::size];
		for (size_t j = 0; j < Node::size; j++) {
			this->array[i][j] = rhs.array[i][j];
		}
	}
	return ( *this );
}

bool		Node::operator<( const Node& rhs ) {
	size_t lTotScore = this->depth + this->score;
	size_t rTotScore = rhs.depth + rhs.score;

	if (lTotScore < rTotScore)
		return true;
	else if (lTotScore > rTotScore)
		return false;
	else
		return (this->depth < rhs.depth); // if same total score, then compare depth
}

bool		Node::operator==( const Node& rhs ) {
	// consider equal with comparison of points, not of depth
	if (this->score != rhs.score)
		return false;

	size_t lSize = this->points.size();
	if (lSize != rhs.points.size())
		return false;

	std::map<size_t, Point>::iterator lIt = this->points.begin();
	std::map<size_t, Point>::const_iterator rIt = rhs.points.begin();
	while (lSize > 0) {
		if (lIt->second.x_current != rIt->second.x_current)
			return false;
		if (lIt->second.y_current != rIt->second.y_current)
			return false;
		lIt++;
		rIt++;
		lSize--;
	}
	return true;
}

// bool		Node::operator!=( const Node& rhs ) {
// 	return !(this == rhs);
// }


/* DESTRUCTOR ================================================================*/
Node::~Node( void ) {
	for (size_t i = 0; i < Node::size; i++) {
		delete this->array[i];
	}
	delete this->array;
	this->points.clear();
}

/* MEMBER FUNCTIONS ==========================================================*/

size_t **Node::getFinalMap() {
	int direction = 0; // 0 = right, 1 = down, 2 = left, 3 = up
	size_t offset = 0;
	size_t steps = Node::size - offset;
	int changeOffsetCount = 1; // usually change offset after 2 direction change, but at the beginning is after the first direction change
	size_t max = (Node::size * Node::size) - 1;
	size_t	**map = new size_t* [Node::size];
	for (size_t i = 0; i < Node::size; i++) {
		map[i] = new size_t [Node::size];
	}
	size_t x = 0;
	size_t y = 0;

	// set to zero
	y = 0;
	while (y < Node::size) {
		x = 0;
		while (x < Node::size) {
			map[y][x] = 0;
			x++;
		}
		y++;
	}

	// Fill numbers with snake form
	y = 0;
	x = 0;
	size_t i = 1;
	while (i <= max) {
		map[y][x] = i;
		steps--;
		if (steps == 0) {
			direction = (direction + 1) % 4;

			changeOffsetCount--;
			if (changeOffsetCount == 0) {
				changeOffsetCount = 2;
				offset++;
			}
			steps = Node::size - offset;
		}

		switch (direction) {
			case 0:
				x++;
				break;
			case 1:
				y++;
				break;
			case 2:
				x--;
				break;
			case 3:
				y--;
				break;
			default:
				break;
		}

		i++;
	}

	return map;
}

int	Node::getFinalPosition(
size_t const value,
size_t **map,
size_t *finalCoords ) {
	for (size_t i = 0; i < Node::size; i++) {
		for (size_t j = 0; j < Node::size; j++) {
			if (value == map[i][j]) {
				finalCoords[0] = j;
				finalCoords[1] = i;
				return (0);
			}
		}
	}
	return (-1);
}

void			Node::updateScore(void) {
	// TODO: score should depend on heuristic choice
	std::map<size_t, Point>::iterator it;
	this->score = 0;
	for (it = this->points.begin(); it != this->points.end(); it++) {
		if ((Env::options & HEUR_MASK) == HEUR_MAN) {
			this->score += this->manhattan(it->second);
		}
		else if ((Env::options & HEUR_MASK) == HEUR_2) {
			this->score += this->manhattanWithLinearConflict(it->second);
		}
	}

	return ;
}

size_t			Node::manhattan(Point const &p) {
	size_t	ret = 0;

	if (p.value > 0) {
		if (p.x_current >= p.x_final)
			ret += p.x_current - p.x_final;
		else
			ret += p.x_final - p.x_current;

		if (p.y_current >= p.y_final)
			ret += p.y_current - p.y_final;
		else
			ret += p.y_final - p.y_current;
	}
	return (ret);
}

size_t			Node::manhattanWithLinearConflict(Point const &p) {
	// Evolved manhattan that searches for conflicts when Point is in final colum/row
	size_t	ret = 0;

	if (p.value > 0) {
		if (p.x_current > p.x_final)
			ret += p.x_current - p.x_final;
		else if (p.x_current < p.x_final)
			ret += p.x_final - p.x_current;
		else {
			ret += this->linearHorConflict(p);
		}

		if (p.y_current > p.y_final)
			ret += p.y_current - p.y_final;
		else if (p.y_current < p.y_final)
			ret += p.y_final - p.y_current;
		else {
			ret += this->linearVertConflict(p);
		}
	}
	return (ret);
}

// size_t		Node::linearConflict(Point const &p, bool horizontalSearch) {
// 	size_t conflicts = 0;
// 	size_t x = (horizontalSearch) ? 0 : p.x_current;
// 	size_t y = (horizontalSearch) ? p.y_current : 0;
// 	while (x < Node::size && y < Node::size) {
// 		Point &tmpPoint = this->points[this->array[y][x]];
// 		if (tmpPoint.value != 0 && tmpPoint.value != p.value) {
// 			if (horizontalSearch && tmpPoint.y_current == tmpPoint.y_final) {
// 				if (tmpPoint.x_final > p.x_final && tmpPoint.x_current < p.x_current)
// 					conflicts++;
// 				else if (tmpPoint.x_final < p.x_final && tmpPoint.x_current > p.x_current)
// 					conflicts++;
// 			}
// 			else if (!horizontalSearch && tmpPoint.x_final == tmpPoint.x_final) {
// 				if (tmpPoint.y_final > p.y_final && tmpPoint.y_current < p.y_current)
// 					conflicts++;
// 				else if (tmpPoint.y_final < p.y_final && tmpPoint.y_current > p.y_current)
// 					conflicts++;
// 			}
// 		}
//
// 		(horizontalSearch) ? x++ : y++;
// 	}
//
// 	return 2 * conflicts; // every conflict increases h() by 2
// }

size_t		Node::linearHorConflict(Point const &p) {
	size_t conflicts = 0;
	size_t x = p.x_current;
	size_t y = p.y_current;
	while (++x < Node::size) {
		Point &tmpPoint = this->points[this->array[y][x]];
		if (tmpPoint.value != 0) {
			if (tmpPoint.y_current == tmpPoint.y_final) {
				if (tmpPoint.x_final > p.x_final && tmpPoint.x_current < p.x_current)
					conflicts++;
				else if (tmpPoint.x_final < p.x_final && tmpPoint.x_current > p.x_current)
					conflicts++;
			}
		}
	}

	return 2 * conflicts; // every conflict increases h() by 2
}

size_t		Node::linearVertConflict(Point const &p) {
	size_t conflicts = 0;
	size_t x = p.x_current;
	size_t y = p.y_current;
	while (++y < Node::size) {
		Point &tmpPoint = this->points[this->array[y][x]];
		if (tmpPoint.value != 0) {
			if (tmpPoint.y_final > p.y_final && tmpPoint.y_current < p.y_current)
				conflicts++;
			else if (tmpPoint.y_final < p.y_final && tmpPoint.y_current > p.y_current)
				conflicts++;
		}
	}

	return 2 * conflicts; // every conflict increases h() by 2
}

std::string		Node::toString(void) {
	std::stringstream		s;

	s << "Score: " << this->score << ", Depth: " << this->depth << std::endl;
	// s << "Points:\n";
	// std::map<size_t, Point>::iterator it;
	// for (it = this->points.begin(); it != this->points.end(); it++) {
	// 	s << "\t" << (it->second).toString();
	// }
	// s << "Graphical:" << std::endl;
	size_t i = 0;
	size_t j;
	while (i < Node::size) {
		j = 0;
		s << "\t";
		while (j < Node::size) {
			if (j > 0)
				s << " ";
			if (this->array[i][j] == 0) {
				s << "\033[91m" << this->array[i][j] << "\033[39m";
			} else {
				s << this->array[i][j];
			}
			j++;
		}
		s << std::endl;
		i++;
	}


	return (s.str());
}

/* NON MEMBER FUNCTIONS ======================================================*/


/* OPERATOR ==================================================================*/
