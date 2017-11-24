#include <string>

#include <stdio.h>

bool		ft_isdigit(int c) {
	return (c >= '0' && c <= '9');
}

int			all_digit(std::string const s) {
	size_t const	len = s.length();

	for (size_t i = 0; i < len; i++) {
		if (i > 0 && s[i] == '#') {
			break ;
		}
		if (!ft_isdigit(s[i])) {
			return (1);
		}
	}
	return (0);
}
