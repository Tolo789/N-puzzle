#ifndef NODE_HPP
# define NODE_HPP

# include <iostream>
# include <map>
# include <array>

class Node {

public:
	static size_t puzzleSize;
	static size_t heurChoice;

	static void SetPuzzleSize(size_t newSize);
	static std::array<size_t, 2> GetNumberFinalPos(size_t number);

	Node(void);
	Node(Node const & src);
	Node(size_t configuration[], size_t depth, Node *prevNode);
	~Node(void);

	Node& operator=(Node const & rhs);

	std::string const  serialize(void) const;

private:
	static std::string finalConfig;
	static std::map<size_t, std::array<size_t, 2> > coordMap;

	size_t GetScore(void);

	size_t *configuration;
	size_t depth;
	size_t score;
	Node *prevNode;

};

std::ostream & operator<<(std::ostream & o, Node const & rhs);

#endif
