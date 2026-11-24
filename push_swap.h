/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      :::::::    */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabraou <ysabraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 21:28:34 by ysabraou          #+#    #+#             */
/*   Updated: 2026/11/23 21:28:34 by ysabraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <unistd.h>

# define STACK_CAP 200000

enum e_bool
{
	FALSE,
	TRUE
};

enum e_algo
{
	ADAPTIVE,
	SIMPLE,
	MEDIUM,
	COMPLEX,
	N_ALGOS
};

enum e_stack
{
	STK_A,
	STK_B
};

enum e_op
{
	SA,
	PA,
	PB,
	RA,
	RB,
	RRA,
	RRB,
	N_OPS
};

enum e_move
{
	MOVE_SWAP,
	MOVE_ROTATE,
	MOVE_REVERSE,
	MOVE_PUSH
};

enum e_loc
{
	TOP_A,
	BOT_A,
	TOP_B,
	BOT_B,
	N_LOCS
};

enum e_part
{
	PART_LOW,
	PART_MID,
	PART_HIGH,
	N_PARTS
};

struct s_chunk
{
	enum e_loc	loc;
	int			min_rank;
	int			size;
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
	int				len;
	enum e_move		move;
	enum e_stack	src;
	enum e_stack	dst;
};

struct s_state
{
	struct s_stack	stacks[2];
	enum e_algo		requested;
	enum e_bool		is_benchmarking;
	long			inversions;
	double			disorder;
	enum e_algo		resolved;
	int				total_ops;
	int				op_counts[N_OPS];
};

void		analyze_input(struct s_state *state, const int *values, int count);
int			stack_get(const struct s_stack *stack, int depth);
void		sort(struct s_state *state);
void		quick_sort(struct s_state *state);
void		apply(struct s_state *state, enum e_op id);
void		print_bench(const struct s_state *state);

#endif
