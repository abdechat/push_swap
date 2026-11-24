/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      :::::::    */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabraou <ysabraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 21:28:34 by ysabraou          #+#    #+#             */
/*   Updated: 2026/11/23 21:28:34 by ysabraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include <limits.h>
# include <unistd.h>

# define STACK_CAP 200000

enum e_bool
{
	FALSE,
	TRUE
};

enum e_read
{
	READ_LINE,
	READ_EOF,
	READ_FAILURE
};

enum e_stack
{
	STK_A,
	STK_B
};

enum e_move
{
	MOVE_SWAP,
	MOVE_ROTATE,
	MOVE_REVERSE,
	MOVE_PUSH
};

struct s_stack
{
	int	items[STACK_CAP];
	int	top_idx;
	int	size;
};

struct s_op
{
	const char		*name;
	enum e_move		move;
	enum e_stack	src;
	enum e_stack	dst;
};

struct s_state
{
	struct s_stack	stacks[2];
};

enum e_bool	run_line(struct s_state *state, const char *line);
enum e_bool	is_solved(const struct s_state *state);

#endif
