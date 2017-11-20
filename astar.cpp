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


static std::vector<Node *>::iterator getBestNode(std::vector<Node *> &myVector) {
	std::vector<Node *>::iterator best = myVector.begin();
	std::vector<Node *>::iterator it = myVector.begin();

	while (it != myVector.end()) {
		if (**it < **best)
			best = it;
		it++;
	}

	return best;
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
	std::vector<Node *> closedList;
	std::vector<Node *>::iterator it;
	it = openList.begin();
	openList.insert(it, startNode);

	// A* main loop
	Node *tmpNode;
	int i; // counter for swaps in 4 directions
	Node *newNode;
	do {
		it = getBestNode(openList);
		tmpNode = *it;

		// Remove node from openList and put in closedList
		closedList.insert(closedList.begin(), tmpNode);
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
				it = getNodeInVector(closedList, newNode);
				if (it == closedList.end()) {
					it = getNodeInVector(openList, newNode);
					if (it == openList.end()) {
						openList.insert(openList.begin(), newNode);
						Env::totalNumberOfStates++;
						size_t const s = openList.size();
						if (s > Env::maxNumberOfState) {
							Env::maxNumberOfState = s;
						}
					}
					else {
						// If already in openList then check if depth is less, if so update prev node
						// This is only useful with greedy searches, classic A* already choose based on shortest path
						if (newNode->depth < (*it)->depth) {
							(*it)->depth = newNode->depth;
							(*it)->prev = newNode->prev;
						}

						delete newNode;
					}
				} else {
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
		std::cout << "Solution found!" << std::endl;
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
			std::cout << (*i)->toString() << std::endl;
			if (Env::options & SLOW_PRINT) {
				std::this_thread::sleep_for(std::chrono::milliseconds(Env::printSpeed));
			}
		}
	}

	// Clear vectors
	clearNodeVector(openList);
	clearNodeVector(closedList);
	return ;
}
