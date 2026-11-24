/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      :::::::    */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabraou <ysabraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 21:28:34 by ysabraou          #+#    #+#             */
/*   Updated: 2026/11/23 21:28:34 by ysabraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	analyze_input(struct s_state *state, const int *values, int count)
{
	int *const	ranks = state->stacks[STK_A].items;
	const long	pairs = (long)count * (count - 1) / 2;
	int			earlier_idx;
	int			later_idx;

	state->stacks[STK_A].size = count;
	earlier_idx = 0;
	while (earlier_idx < count)
	{
		later_idx = earlier_idx + 1;
		while (later_idx < count)
		{
			if (values[earlier_idx] > values[later_idx])
			{
				++ranks[earlier_idx];
				++state->inversions;
			}
			else
				++ranks[later_idx];
			++later_idx;
		}
		++earlier_idx;
	}
	if (pairs > 0)
		state->disorder = (double)state->inversions / pairs;
}

static void	reorder_stack(struct s_stack *stack, enum e_move move)
{
	int	top_item;
	int	second_idx;

	if (move == MOVE_ROTATE)
	{
		stack->items[(stack->top_idx + stack->size) % STACK_CAP]
			= stack->items[stack->top_idx];
		stack->top_idx = (stack->top_idx + 1) % STACK_CAP;
		return ;
	}
	if (move == MOVE_REVERSE)
	{
		stack->top_idx = (stack->top_idx + STACK_CAP - 1) % STACK_CAP;
		stack->items[stack->top_idx]
			= stack->items[(stack->top_idx + stack->size) % STACK_CAP];
		return ;
	}
	second_idx = (stack->top_idx + 1) % STACK_CAP;
	top_item = stack->items[stack->top_idx];
	stack->items[stack->top_idx] = stack->items[second_idx];
	stack->items[second_idx] = top_item;
}

void	apply(struct s_state *state, enum e_op id)
{
	const struct s_op			ops[N_OPS] = {
	{"sa\n", 3, MOVE_SWAP, STK_A, STK_A},
	{"pa\n", 3, MOVE_PUSH, STK_B, STK_A},
	{"pb\n", 3, MOVE_PUSH, STK_A, STK_B},
	{"ra\n", 3, MOVE_ROTATE, STK_A, STK_A},
	{"rb\n", 3, MOVE_ROTATE, STK_B, STK_B},
	{"rra\n", 4, MOVE_REVERSE, STK_A, STK_A},
	{"rrb\n", 4, MOVE_REVERSE, STK_B, STK_B}};
	const struct s_op *const	op = &ops[id];
	struct s_stack *const		src = &state->stacks[op->src];
	struct s_stack *const		dst = &state->stacks[op->dst];

	++state->total_ops;
	++state->op_counts[id];
	write(1, op->name, op->len);
	if (op->move != MOVE_PUSH)
	{
		reorder_stack(src, op->move);
		return ;
	}
	dst->top_idx = (dst->top_idx + STACK_CAP - 1) % STACK_CAP;
	dst->items[dst->top_idx] = src->items[src->top_idx];
	src->top_idx = (src->top_idx + 1) % STACK_CAP;
	++dst->size;
	--src->size;
}

static void	bench_printf(const char *text, const int *numbers)
{
	int		divisor;
	char	digit;

	while (*text != '\0')
	{
		if (*text != '#')
		{
			write(2, text, 1);
			++text;
			continue ;
		}
		++text;
		divisor = 1;
		while (*numbers / divisor >= 10)
			divisor *= 10;
		while (divisor > 0)
		{
			digit = '0' + (*numbers / divisor) % 10;
			write(2, &digit, 1);
			divisor /= 10;
		}
		++numbers;
	}
}

void	print_bench(const struct s_state *state)
{
	const long			basis_points = (long)(state->disorder * 10000 + 0.5);
	const int			percent_parts[3] = {
		basis_points / 100,
		(basis_points / 10) % 10,
		basis_points % 10};
	const char *const	names[N_ALGOS] = {"Adaptive",
		"Simple", "Medium", "Complex"};
	const char *const	classes[N_ALGOS] = {"",
		" / O(n²)\n", " / O(n√n)\n", " / O(n log n)\n"};

	bench_printf("[bench] disorder: #.##%\n", percent_parts);
	bench_printf("[bench] strategy: ", NULL);
	bench_printf(names[state->requested], NULL);
	bench_printf(classes[state->resolved], NULL);
	bench_printf("[bench] total_ops: #\n", &state->total_ops);
	bench_printf("[bench] sa: # sb: 0 ss: 0 pa: # pb: #\n"
		"[bench] ra: # rb: # rr: 0 rra: # rrb: # rrr: 0\n", state->op_counts);
}
