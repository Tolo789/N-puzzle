#ifndef NODE_HPP
# define NODE_HPP
# include <iostream>

class Node {

public:
	public static heurChoice;

	Node(void);
	Node(Node const & src);
	Node(std::string configuration, size_t size, Node *prevNode);
	~Node(void);

	Node& operator=(Node const & rhs);

	std::string const  serialize(void) const;

private:
	std::string configuration;
	size_t size;
	size_t score;
	Node *prevNode;

};

std::ostream & operator<<(std::ostream & o, Node const & rhs);

#endif
