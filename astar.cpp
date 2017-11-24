#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <list>
#include <chrono>
#include <thread>
#include "Env.class.hpp"
#include "astar.hpp"

static void	clearNodeVector(std::vector<Node *> &myVector) {
	// std::cout << "Vector size before clearing: " << myVector.size() << std::endl;

	std::vector<Node *>::iterator it;
	while (myVector.size() > 0) {
		it = myVector.begin();
		delete(*it);
		myVector.erase(it);
	}

	// std::cout << "Vector size after clearing: " << myVector.size() << std::endl << std::endl;
}

static void	clearClosedList(std::map<std::string, Node*> &closedList) {
	std::map<std::string, Node*>::iterator it;
	while (closedList.size() > 0) {
		it = closedList.begin();
		delete it->second;
		closedList.erase(it);
	}

	// std::cout << "Vector size after clearing: " << myVector.size() << std::endl << std::endl;
}

// static void printNodeVector(std::vector<Node *> &myVector) {
// 	std::vector<Node *>::iterator it = myVector.begin();
// 	while (it != myVector.end()) {
// 		std::cout << (*it)->toString() << std::endl;
// 		it++;
// 	}
// }

static std::vector<Node *>::iterator getNodeInVector(std::vector<Node *> &myVector, Node *targetNode) {
	std::vector<Node *>::iterator it = myVector.begin();
	while (it != myVector.end()) {
		if (**it == *targetNode)
			return it;
		it++;
	}

	return it;
}

static std::vector<Node *>::iterator getBestNodePositionDico(std::vector<Node *> &myVector, Node &node) {
	size_t bottom = 0;
	size_t top = myVector.size();
	size_t index = (top + bottom) / 2;

	// Preliminary checks
	if (top > 0) {
		if (node < **(myVector.begin()))
			return myVector.begin();
		if (**(myVector.end() - 1) < node)
			return myVector.end();
	}
	else
		return myVector.begin();

	do {
		if (*myVector[index] < node) { // look on the left side
			bottom = index + 1;
		}
		else if (node < *myVector[index]) { // look on the right side
			top = index - 1;
		}
		else { // good spot found
			break;
		}
		index = (top + bottom) / 2;
	} while (index != bottom);

	return myVector.begin() + index;
}

static Node		*swapNode(Node *original, int const direction) {
	Node *newNode = new Node(*original);
	newNode->depth += 1;
	newNode->prev = original;

	Point &zero = newNode->points[0];
	size_t number = 0;
	switch (direction) {
		case 0: // up
			number = newNode->array[zero.y_current - 1][zero.x_current];
			break;
		case 1: // down
			number = newNode->array[zero.y_current + 1][zero.x_current];
			break;
		case 2: // left
			number = newNode->array[zero.y_current][zero.x_current - 1];
			break;
		case 3: // right
			number = newNode->array[zero.y_current][zero.x_current + 1];
			break;
		default:
			break;
	}
	Point &other = newNode->points[number];
	// Update array
	newNode->array[other.y_current][other.x_current] = 0;
	newNode->array[zero.y_current][zero.x_current] = number;
	// Update points coord
	number = zero.x_current;
	zero.x_current = other.x_current;
	other.x_current = number;
	number = zero.y_current;
	zero.y_current = other.y_current;
	other.y_current = number;
	newNode->updateScore();
	return (newNode);
}

void		runAStar(Node *startNode) {
	// A* begin
	std::vector<Node *> openList;
	// std::vector<Node *> closedList;
	std::map<std::string, Node*> closedList; ///////////////////////
	std::map<std::string, Node*>::iterator	itclosed;
	std::vector<Node *>::iterator it;
	it = openList.begin();
	openList.insert(it, startNode);

	// A* main loop
	Node *tmpNode;
	Node *newNode;
	int i; // counter for swaps in 4 directions
	do {
		it = openList.begin();
		tmpNode = *it;

		// Remove node from openList and put in closedList
		// std::cout << Node::getHash(*tmpNode) << '\n';
		// closedList.insert(closedList.begin(), tmpNode);
		closedList.insert(std::pair<std::string, Node*>(Node::getHash(*tmpNode), tmpNode)); //////////////
		openList.erase(it);

		// check if node is goal, if so exit loop
		if (tmpNode->score == 0) {
			break;
		}

		// foreach neighbour: check if already in one list + check if it's a shortest path
		i = 0;
		while (i < 4) {
			if ((i == 0 && tmpNode->points[0].y_current != 0) ||						// up
				(i == 1 && tmpNode->points[0].y_current != tmpNode->size - 1) ||		// down
				(i == 2 && tmpNode->points[0].x_current != 0) ||						// left
				(i == 3 && tmpNode->points[0].x_current != tmpNode->size - 1)) {		// right

				newNode = swapNode(tmpNode, i);
				// it = getNodeInVector(closedList, newNode);
				itclosed = closedList.find(Node::getHash(*newNode));
				if (itclosed == closedList.end()) {
					it = getNodeInVector(openList, newNode);
					if (it == openList.end()) {
						it = getBestNodePositionDico(openList, *newNode);
						openList.insert(it, newNode);

						Env::totalNumberOfStates++;
						size_t const s = openList.size();
						if (s > Env::maxNumberOfState) {
							Env::maxNumberOfState = s;
						}
					}
					else {
						// If already in openList then check if depth is less, if so update prev node
						// This is only useful with not admissible heuristics, classic A* heur. already choose based on shortest path
						if (newNode->depth < (*it)->depth) {
							// replace old elem with new one
							delete(*it);
							openList.erase(it);
							it = getBestNodePositionDico(openList, *newNode);
							openList.insert(it, newNode);
						}
						else
							delete newNode;
					}
				} else {
					// If already in openList then check if depth is less, if so update prev node
					// This is only useful with not admissible heuristics, classic A* heur. already choose based on shortest path
					if (newNode->depth < itclosed->second->depth) {
						itclosed->second->depth = newNode->depth;
						itclosed->second->prev = newNode->prev;

						openList.insert(openList.begin(), itclosed->second);
						closedList.erase(itclosed);

						// No need to increse totalNumberOfStates because we are putting back an already counted Node
						size_t const s = openList.size();
						if (s > Env::maxNumberOfState) {
							Env::maxNumberOfState = s;
						}
					}

					delete newNode;
				}
			}
			i++;
		}

	} while (openList.size() > 0);
	// Reconstruct path to solution
	if (tmpNode->score != 0) {
		std::cout << "Solution not found" << std::endl;
	}
	else {
		// std::cout << "Solution found!" << std::endl;
		std::list<Node*>	finalList;
		do {
			finalList.push_front(tmpNode);
			tmpNode = tmpNode->prev;
		} while (tmpNode);

		Env::numberOfMove = finalList.size() - 1;
		for (std::list<Node*>::iterator i = finalList.begin(); i != finalList.end(); i++) {
			if (Env::options & SLOW_PRINT) {
				std::system("clear");
			}
			// std::cout << (*i)->toString() << std::endl;
			if (Env::options & SLOW_PRINT) {
				std::this_thread::sleep_for(std::chrono::milliseconds(Env::printSpeed));
			}
		}
	}

	// Clear vectors
	clearNodeVector(openList);
	clearClosedList(closedList);
	return ;
}
