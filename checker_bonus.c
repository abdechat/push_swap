/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      :::::::    */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achancha <achancha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 21:28:34 by achancha          #+#    #+#             */
/*   Updated: 2026/11/23 21:28:34 by achancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "checker_bonus.h"

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

static enum e_read	read_line(char *line)
{
	ssize_t	bytes_read;
	int		len;

	len = 0;
	while (len < 4)
	{
		bytes_read = read(0, &line[len], 1);
		if (bytes_read == 0 && len == 0)
			return (READ_EOF);
		if (bytes_read <= 0)
			return (READ_FAILURE);
		if (line[len] == '\n')
		{
			line[len] = '\0';
			return (READ_LINE);
		}
		++len;
	}
	return (READ_FAILURE);
}

static enum e_bool	read_ops(struct s_state *state)
{
	char		line[4];
	enum e_read	status;

	while (TRUE)
	{
		status = read_line(line);
		if (status == READ_EOF)
			return (TRUE);
		if (status == READ_FAILURE || !run_line(state, line))
			return (FALSE);
	}
}

int	main(int argc, char **argv)
{
	struct s_state	state;
	int				count;

	count = argc - 1;
	if (count == 0)
		return (0);
	state = (struct s_state){0};
	state.stacks[STK_A].size = count;
	if (!parse_args(count, argv + 1, state.stacks[STK_A].items)
		|| !read_ops(&state))
	{
		write(2, "Error\n", 6);
		return (255);
	}
	if (is_solved(&state))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	return (0);
}
