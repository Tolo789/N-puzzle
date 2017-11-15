#include <string.h>
#include <string>
#include <iostream>

#include "Env.class.hpp"
#include "error.hpp"

#include <stdio.h>

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

static int	setHeuristic(Env *env, char const *param) {
	if (!param) {
		return (ft_error(UNKNOWN_OPTION, 1));
	} else if (env->options & HEUR_MASK) {
		return (ft_error(ONLY_ONE_HEUR, 1));
	} else if (!strcmp(param, HEUR_MAN_STR)) {
		env->options |= HEUR_MAN;
	} else if (!strcmp(param, HEUR_2_STR)) {
		env->options |= HEUR_2;
	} else if (!strcmp(param, HEUR_3_STR)) {
		env->options |= HEUR_3;
	} else {
		return (ft_error(INVALID_HEUR, 1));
	}
	return (0);
}

static int	setSize(Env *env, char const *param) {
	if (!param) {
		return (ft_error(INVALID_OPTION_VALUE, 1));
	} else {
		env->options |= SIZE;
		Env::puzzle.size = std::stoi(param);
		return (0);
	}
}

static int	setIterations(Env *env, char const *param) {
	if (!param) {
		return (ft_error(INVALID_OPTION_VALUE, 1));
	} else {
		env->options |= ITERATIONS;
		Env::puzzle.iterations = std::stoi(param);
		return (0);
	}
}

static int	switch_set_options(char const *arg, char const *param, Env *env) {
	if (!arg)
		return (0);
	else
		arg++;
	while (arg && *arg)
	{
		if (*arg && strchr(PARAMS_STR, static_cast<int>(*arg)))
		{
			if (*arg == HEUR_CHAR  && !*(arg + 1)) {
				return (setHeuristic(env, param));
			} else if (*arg == SIZE_CHAR  && !*(arg + 1)) {
				return (setSize(env, param));
			} else if (*arg == ITERATIONS_CHAR  && !*(arg + 1)) {
				return (setIterations(env, param));
			} else if (*arg == HELP_CHAR  && !*(arg + 1)) {
				env->options |= HELP;
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

int			get_options(Env *env, int *ac, char **av) {
	int		i;
	int		n;

	i = 1;
	n = 0;
	while (i < *ac)
	{
		if (av[i][0] == '-')
		{
			if (switch_set_options(av[i], av[i + 1], env) > 0)
				return (1);
			av[i] = NULL;
			av[i + 1] = NULL;
			n += 2;
			i += 2;
		}
		else
			i++;
	}
	env->options |= !(env->options & HEUR_MASK) ? HEUR_MAN : env->options;
	del_null_params(ac, av, n);
	printf("%hhx\n", env->options);
	return (0);
}
