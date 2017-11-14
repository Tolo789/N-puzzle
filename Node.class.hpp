#ifndef NODE_HPP
# define NODE_HPP
# include <iostream>

class Node {

public:
	static unsigned int puzzleSize;
	static unsigned int heurChoice;

	static void SetPuzzleSize(unsigned int newSize);

	Node(void);
	Node(Node const & src);
	Node(std::string configuration, unsigned int depth, Node *prevNode);
	~Node(void);

	Node& operator=(Node const & rhs);

	std::string const  serialize(void) const;

private:
	static std::string finalConfig;

	unsigned int GetScore(void);

	std::string configuration;
	unsigned int depth;
	unsigned int score;
	Node *prevNode;

};

std::ostream & operator<<(std::ostream & o, Node const & rhs);

#endif
