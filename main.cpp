#include <iostream>
#include <list>
#include "Node.class.hpp"

std::list<Node *>::iterator GetBestNode(std::list<Node *> &openList) {
	return openList.begin();
}



int main(void) {
	size_t newSize = 3;
	Node::SetPuzzleSize(newSize);

	// Check that final pos is correct
	size_t i = 0;
	std::array<size_t, 2> pos;
	while (i < newSize * newSize) {
		pos = Node::GetNumberFinalPos(i);
		std::cout << "Coord for " << i << ":" << "\tx = " << pos[0] << "\ty = " << pos[1] << std::endl;
		i++;
	}
	std::cout << std::endl;

	std::list<Node *> openList;
	std::list<Node *> closedList;

	size_t elems[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
	Node *tmp = new Node(elems, 0, NULL);
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
