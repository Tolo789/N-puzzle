#include <string.h>
#include <string>
#include <iostream>

#include "Env.class.hpp"
#include "error.hpp"
#include "tools.hpp"

// #include <stdio.h>

static void	del_null_params(int *ac, char **av, int offset) {
	int		i;
	int		n;
	char	*tmp;

	n = 1;
	while (n < *ac)
	{
		i = 1;
		while (i < *ac - 1)
		{
			if (av[i] == NULL)
			{
				tmp = av[i];
				av[i] = av[i + 1];
				av[i + 1] = tmp;
			}
			i++;
		}
		n++;
	}
	*ac -= offset;
}

static int	setHeuristic(char const *param) {
	if (!param) {
		return (ft_error(UNKNOWN_OPTION, 1));
	} else if (Env::options & HEUR_MASK) {
		return (ft_error(ONLY_ONE_HEUR, 1));
	} else if (!strcmp(param, HEUR_MAN_STR)) {
		Env::options |= HEUR_MAN;
	} else if (!strcmp(param, HEUR_2_STR)) {
		Env::options |= HEUR_2;
	} else if (!strcmp(param, HEUR_3_STR)) {
		Env::options |= HEUR_3;
	} else {
		return (ft_error(INVALID_HEUR, 1));
	}
	return (0);
}

static int	setSize(char const *param) {
	if (!param) {
		return (ft_error(INVALID_OPTION_VALUE, 1));
	} else {
		if (all_digit(std::string(param))) {
			return (ft_error(INVALID_OPTION_VALUE, 1));
		}
		try {
			Env::puzzle.size = std::stoi(param);
			if (Env::puzzle.size > 1) {
				Env::options |= SIZE;
				return (0);
			} else {
				return (ft_error(INVALID_OPTION_VALUE, 1));
			}
		} catch (...) {
			return (ft_error(INVALID_OPTION_VALUE, 1));
		}
	}
}

static int	setIterations(char const *param) {
	if (!param) {
		return (ft_error(INVALID_OPTION_VALUE, 1));
	} else {
		if (all_digit(std::string(param))) {
			return (ft_error(INVALID_OPTION_VALUE, 1));
		}
		try {
			Env::puzzle.iterations = std::stoi(param);
			if (Env::puzzle.iterations) {
				Env::options |= ITERATIONS;
				return (0);
			} else {
				return (ft_error(INVALID_OPTION_VALUE, 1));
			}
		} catch (...) {
			return (ft_error(INVALID_OPTION_VALUE, 1));
		}
		return (0);
	}
}

static int	switch_set_options(char const *arg, char const *param) {
	if (!arg)
		return (0);
	else
		arg++;
	while (arg && *arg)
	{
		if (*arg && strchr(PARAMS_STR, static_cast<int>(*arg)))
		{
			if (*arg == HEUR_CHAR  && !*(arg + 1)) {
				return (setHeuristic(param));
			} else if (*arg == SIZE_CHAR  && !*(arg + 1)) {
				return (setSize(param));
			} else if (*arg == ITERATIONS_CHAR  && !*(arg + 1)) {
				return (setIterations(param));
			} else if (*arg == HELP_CHAR  && !*(arg + 1)) {
				Env::options |= HELP;
				return (0);
			} else {
				return (ft_error(UNKNOWN_OPTION, 1));
			}
		}
		else
			return (ft_error(UNKNOWN_OPTION, 1));
		arg++;
	}
	return (0);
}

int			get_options(int *ac, char **av) {
	int		i;
	int		n;

	i = 1;
	n = 0;
	while (i < *ac)
	{
		if (av[i][0] == '-')
		{
			if (switch_set_options(av[i], av[i + 1]) > 0)
				return (1);
			av[i] = NULL;
			av[i + 1] = NULL;
			n += 2;
			i += 2;
		}
		else
			i++;
	}
	Env::options |= !(Env::options & HEUR_MASK) ? HEUR_MAN : Env::options;
	del_null_params(ac, av, n);
	return (0);
}
