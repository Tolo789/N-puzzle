#ifndef NODE_HPP
# define NODE_HPP
# include <iostream>

class Node {

public:
	static size_t puzzleSize;
	static size_t heurChoice;

	static void SetPuzzleSize(size_t newSize);

	Node(void);
	Node(Node const & src);
	Node(std::string configuration, size_t depth, Node *prevNode);
	~Node(void);

	Node& operator=(Node const & rhs);

	std::string const  serialize(void) const;

private:
	static std::string finalConfig;

	size_t GetScore(void);

	std::string configuration;
	size_t depth;
	size_t score;
	Node *prevNode;

};

std::ostream & operator<<(std::ostream & o, Node const & rhs);

#endif
