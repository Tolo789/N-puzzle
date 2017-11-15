#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "Map.class.hpp"

std::string		**treatInput(std::string input) {
	std::vector<std::string>	splitLine;
	std::string		**ret;
	std::string					line;
	std::istringstream			f(input);

	while (getline(f, line, '\n')) {
		splitLine.push_back(line);
	}
	std::cout << splitLine.size() << std::endl;
	size_t	splitLineSize = splitLine.size();
	ret = new std::string* [splitLineSize];
	for (size_t i = 0; i < splitLineSize; i++) {
		std::istringstream	p(splitLine[i]);
		std::vector<std::string>	subSplitLine;
		while (getline(p, line, ' ')) {
			subSplitLine.push_back(line);
		}
		ret[i] = new std::string [subSplitLine.size()];
		for (size_t j = 0; j < subSplitLine.size(); j++) {
			ret[i][j] = std::string(subSplitLine[j]);
		}
	}
	return (ret);
}

// void	ft_e(Map mapOne) {
// 	std::map<size_t, Point>::iterator it;
// 	for (it = mapOne.points.begin(); it != mapOne.points.end(); it++) {
// 		std::cout << (it->second).toString() << std::endl;
// 	}
// 	return;
// }

int		main(int ac, char **av) {
	std::string **ret = treatInput("1 2 3\n4 0 6\n7 8 5");
	Map *mapOne = new Map(3, ret);

	// find specific point in map
	Point tmp = mapOne->points.find(4)->second;
	std::cout << std::endl << "Test for find in map:" << std::endl;
	std::cout << tmp.toString();
	// test if map is well linked with array
	std::cout << mapOne->array[tmp.y_current][tmp.x_current] << std::endl;

	// iter over all points
	std::cout << std::endl << "Printing all points" << std::endl;
	std::map<size_t, Point>::iterator it;
	ft_e(*mapOne);
	for (it = mapOne->points.begin(); it != mapOne->points.end(); it++) {
		std::cout << (it->second).toString() << std::endl;
	}

	/*
		do things
		.....
	*/
	delete [] ret[0];
	delete [] ret[1];
	delete [] ret[2];
	delete [] ret;
	return 0;
}
