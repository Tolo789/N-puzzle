#include <iostream>
#include <list>
#include "Node.class.hpp"

std::list<Node *>::iterator GetBestNode(std::list<Node *> &openList) {
	return openList.begin();
}



int main(void) {
	std::cout << "Size: " << Node::puzzleSize << std::endl;
	Node::SetPuzzleSize(2);
	std::cout << "Size: " << Node::puzzleSize << std::endl;

	std::list<Node *> openList;
	std::list<Node *> closedList;

	Node *tmp = new Node("1234567890", 0, NULL);
	openList.insert(openList.begin(), tmp);

	tmp = new Node("tmp", 0, NULL);
	openList.insert(openList.begin(), tmp);

	openList.insert(openList.begin(), new Node("toto", 0, NULL));


	openList.insert(openList.begin(), tmp);

	// Pseudo A*
	std::cout << "\nOpen List" << std::endl;
	while (openList.size() > 0) {
		std::list<Node *>::iterator it = GetBestNode(openList);
		// std::list<Node *>::iterator it = openList.begin();


		// Check if is end + add new nodes
		std::cout << **it << std::endl;


		closedList.push_front(*it);
		openList.remove(*it);

	}


	std::cout << std::endl << "Closed List" << std::endl;
	while (closedList.size() > 0) {
		std::list<Node *>::iterator it = closedList.begin();

		std::cout << **it << std::endl;
		closedList.remove(*it);
		delete(*it);
	}


	// delete(tmp);
	return 0;
}