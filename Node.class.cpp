#include <iostream>
#include <sstream>
#include <string>

#include <iomanip>
#include <math.h>

#include "Node.class.hpp"
#include "Env.class.hpp"
#include "error.hpp"

/* STATIC VARIABLES ==========================================================*/
size_t		Node::size = 3;
std::string	Node::finalHash;

/* CONSTRUCTORS ==============================================================*/

Node::Node( void ) : depth(0), prev(NULL) {
	std::srand(std::time(0));
	this->array = new size_t*[Node::size];
	for (size_t i = 0; i < Node::size; i++) {
		this->array[i] = new size_t[Node::size];
	}

	/* GENERATE FINAL MAP */
	size_t **map = getFinalMap();
	Node::finalHash = getHash(map);

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
	Node::finalHash = getHash(map);

	size_t	value;
	size_t	*finalCoords = new size_t [2];
	for (size_t y = 0; y < Node::size; y++) {
		for (size_t x = 0; x < Node::size; x++) {
			size_t pos = 0;
			value = static_cast<size_t>(std::stoi(input[y][x], &pos , 10));
			if (Node::getFinalPosition( value, map, finalCoords ) < 0) {
				/* ERROR HANDLING */
				throw Node::MissingMemberException();
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
	for (size_t check = 0; check < Node::size * Node::size; check++) {
		if (this->points.find(check) == this->points.end()) {
			throw Node::MissingMemberException();
			// std::cout << "no" << '\n';
		}
	}
}

Node::MissingMemberException::MissingMemberException( void ) throw() {
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

Node::MissingMemberException::~MissingMemberException( void ) throw() {
}

/* MEMBER FUNCTIONS ==========================================================*/

size_t **Node::getFinalMap() {
	int direction = 0; // 0 = right, 1 = down, 2 = left, 3 = up
	size_t offset = 0;
	size_t steps = Node::size - offset;
	size_t x = 0;
	size_t y = 0;
	size_t i = 1;
	int changeOffsetCount = 1; // usually change offset after 2 direction change, but at the beginning is after the first direction change
	size_t max = (Node::size * Node::size) - 1;
	size_t	**map = new size_t* [Node::size];

	for (size_t i = 0; i < Node::size; i++) {
		map[i] = new size_t [Node::size];
	}
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
	std::map<size_t, Point>::iterator it;

	this->score = 0;
	if (Env::options & UNIFORM) {
		return ;
	}
	for (it = this->points.begin(); it != this->points.end(); it++) {
		if ((Env::options & HEUR_MASK) == HEUR_MAN) {
			this->score += this->manhattan(it->second);
		}
		else if ((Env::options & HEUR_MASK) == HEUR_2) {
			this->score += this->manhattanWithLinearConflict(it->second);
		}
		else if ((Env::options & HEUR_MASK) == HEUR_3) {
			this->score += this->tilesMisplaced(it->second);
		}
		else if ((Env::options & HEUR_MASK) == HEUR_4) {
			this->score += this->manhattanLinearMisplaced(it->second);
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
			ret += this->linearVertConflict(p);
		}

		if (p.y_current > p.y_final)
			ret += p.y_current - p.y_final;
		else if (p.y_current < p.y_final)
			ret += p.y_final - p.y_current;
		else {
			ret += this->linearHorConflict(p);
		}
	}
	return (ret);
}

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
	return (2 * conflicts); // every conflict increases h() by at least 2, but actually is even more
}

size_t		Node::linearVertConflict(Point const &p) {
	size_t conflicts = 0;
	size_t x = p.x_current;
	size_t y = p.y_current;
	while (++y < Node::size) {
		Point &tmpPoint = this->points[this->array[y][x]];
		if (tmpPoint.value != 0) {
			if (tmpPoint.x_current == tmpPoint.x_final) {
				if (tmpPoint.y_final > p.y_final && tmpPoint.y_current < p.y_current)
					conflicts++;
				else if (tmpPoint.y_final < p.y_final && tmpPoint.y_current > p.y_current)
					conflicts++;
			}
		}
	}
	return (2 * conflicts); // every conflict increases h() by at least 2, but actually is even more
}

size_t			Node::tilesMisplaced(Point const &p) {
	// Evolved manhattanLinear where we add number of tiles out of place
	size_t	ret = 0;

	if (p.value > 0) {
		if (p.x_current != p.x_final || p.y_current != p.y_final)
			ret += 1;
	}
	return (ret);
}

size_t			Node::manhattanLinearMisplaced(Point const &p) {
	// Evolved manhattanLinear where we add number of tiles out of place
	size_t	ret = 0;

	if (p.value > 0) {
		if (p.x_current > p.x_final)
			ret += p.x_current - p.x_final;
		else if (p.x_current < p.x_final)
			ret += p.x_final - p.x_current;
		else {
			ret += this->linearVertConflict(p);
		}
		if (p.y_current > p.y_final)
			ret += p.y_current - p.y_final;
		else if (p.y_current < p.y_final)
			ret += p.y_final - p.y_current;
		else {
			ret += this->linearHorConflict(p);
		}
		if (p.x_current != p.x_final || p.y_current != p.y_final)
			ret += 1;
	}
	return (ret);
}

std::string		Node::toString(void) {
	std::stringstream		s;
	size_t i = 0;
	size_t j;
	size_t padding = log10(Node::size * Node::size - 1) + 2;
	std::stringstream zeroPad;

	s << "Score: " << this->score << ", Depth: " << this->depth << std::endl;
	for (size_t k = 0; k < padding - 1; k++ ) {
		zeroPad << " ";
	}
	zeroPad << "\033[91m" << "0" << "\033[39m";
	while (i < Node::size) {
		j = 0;
		s << "\t";
		while (j < Node::size) {
			s << std::setw(padding);
			if (this->array[i][j] == 0) {
				s << zeroPad.str();
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

size_t			Node::getInversion( Node &node ) {
	Node	tmpNode = node;
	size_t	array[Node::size * Node::size];
	size_t	n = 0;
	for (size_t y = 0; y < Node::size; y++) {
		for (size_t x = 0; x < Node::size; x++) {
			array[y * Node::size + x] = node.array[y][x];
		}
	}
	for (size_t i = 0; i < Node::size * Node::size; i++) {
		for (size_t j = i + 1; j < Node::size * Node::size; j++) {
			if (array[i] && array[j] && array[i] > array[j]) {
				n++;
			}
		}
	}
	return (n);
}

size_t			Node::getZero( Node &node ) {
	for (size_t y = 0; y < Node::size; y++) {
		for (size_t x = 0; x < Node::size; x++) {
			if (node.array[y][x] == 0) {
				return ((Node::size * Node::size) - (y * Node::size + x));
			}
		}
	}
	return (0);
}

bool			Node::isSolvable( Node &node ) {
	size_t const	n = Node::getInversion(node);
	size_t			ncpy = 0;
	Node			nodecpy = node;

	for (size_t i = 0; i < Node::size; i++) {
		delete [] nodecpy.array[i];
	}
	delete [] nodecpy.array;
	nodecpy.array = nodecpy.getFinalMap();
	ncpy = Node::getInversion(nodecpy);
	if (Node::size & 1)
		return ((n & 1) == (ncpy & 1));
	else {
		return (((n + Node::getZero(node)) & 1) == ((ncpy + Node::getZero(nodecpy)) & 1));
	}
}

std::string		Node::getHash( size_t **array ) {
	std::stringstream	s;

	for (size_t y = 0; y < Node::size; y++) {
		for (size_t x = 0; x < Node::size; x++) {
			s << array[y][x] << ",";
		}
	}
	return (s.str());
}

const char	*Node::MissingMemberException::what( void ) const throw() {
	return (BAD_MEMBER);
}

/* NON MEMBER FUNCTIONS ======================================================*/


/* OPERATOR ==================================================================*/
