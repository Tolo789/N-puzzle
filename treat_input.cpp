#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "error.hpp"
#include "tools.hpp"
#include "treat_input.hpp"

int		treatInput(t_treatInput *retTreatinput, std::string input) {
	std::vector<std::string>	splitLine;
	std::string					**ret;
	std::string					line;
	std::istringstream			f(input);

	retTreatinput->size = 0;
	retTreatinput->ret = NULL;

	while (getline(f, line, '\n') && line.length() && line[0] == '#');
	if (all_digit(std::string(line))) {
		return (ft_error(INVALID_SIZE, 1));
	}
	try {
		retTreatinput->size = std::stoi(line);
	} catch (...) {
		return (ft_error(INVALID_SIZE, 1));
	}
	while (getline(f, line, '\n')) {
		splitLine.push_back(line);
	}
	size_t	splitLineSize = splitLine.size();
	ret = new std::string* [splitLineSize];
	for (size_t i = 0; i < splitLineSize; i++) {
		std::istringstream	p(splitLine[i]);
		std::vector<std::string>	subSplitLine;
		while (getline(p, line, ' ')) {
			if (line.length()) {
				subSplitLine.push_back(line);
			}
		}
		ret[i] = new std::string [subSplitLine.size()];
		for (size_t j = 0; j < subSplitLine.size(); j++) {
			ret[i][j] = std::string(subSplitLine[j]);
		}
	}
	retTreatinput->ret = ret;
	return (0);
}
