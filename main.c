/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      :::::::    */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achancha <achancha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 21:28:34 by achancha          #+#    #+#             */
/*   Updated: 2026/11/23 21:28:34 by achancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static int	ft_strcmp(const char *a, const char *b)
{
	while (*a != '\0' && *a == *b)
	{
		++a;
		++b;
	}
	return ((unsigned char)*a - (unsigned char)*b);
}

static int	parse_flags(int argc, char **argv, struct s_state *state)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "--bench"))
			state->is_benchmarking = TRUE;
		else if (!ft_strcmp(argv[i], "--adaptive"))
			state->requested = ADAPTIVE;
		else if (!ft_strcmp(argv[i], "--simple"))
			state->requested = SIMPLE;
		else if (!ft_strcmp(argv[i], "--medium"))
			state->requested = MEDIUM;
		else if (!ft_strcmp(argv[i], "--complex"))
			state->requested = COMPLEX;
		else
			return (i);
		++i;
	}
	return (i);
}

static enum e_bool	parse_int(const char *text, int *out)
{
	long	value;
	long	sign;

	sign = 1;
	if (*text == '-')
	{
		sign = -1;
		++text;
	}
	else if (*text == '+')
		++text;
	if (*text == '\0')
		return (FALSE);
	value = 0;
	while (*text >= '0' && *text <= '9')
	{
		value = value * 10 + sign * (*text - '0');
		if (value > INT_MAX || value < INT_MIN)
			return (FALSE);
		++text;
	}
	if (*text != '\0')
		return (FALSE);
	*out = (int)value;
	return (TRUE);
}

static enum e_bool	parse_args(int count, char **args, int *values)
{
	int	i;
	int	earlier_idx;

	if (count > STACK_CAP)
		return (FALSE);
	i = 0;
	while (i < count)
	{
		if (!parse_int(args[i], &values[i]))
			return (FALSE);
		earlier_idx = 0;
		while (earlier_idx < i)
		{
			if (values[earlier_idx] == values[i])
				return (FALSE);
			++earlier_idx;
		}
		++i;
	}
	return (TRUE);
}

int	main(int argc, char **argv)
{
	struct s_state	state;
	int				values[STACK_CAP];
	int				first_num_idx;
	int				count;

	state = (struct s_state){0};
	first_num_idx = parse_flags(argc, argv, &state);
	count = argc - first_num_idx;
	if (count == 0)
		return (0);
	if (!parse_args(count, argv + first_num_idx, values))
	{
		write(2, "Error\n", 6);
		return (255);
	}
	analyze_input(&state, values, count);
	sort(&state);
	if (state.is_benchmarking)
		print_bench(&state);
	return (0);
}
