#include <vector>
#include <string>
#include <sstream>

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

int		main(int ac, char **av) {
	std::string **ret = treatInput("1 2 3\n4 5 6\n7 8 0");
	Map *map = new Map(3, ret);
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
