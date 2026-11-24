/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      :::::::    */
/*   checker_state_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achancha <achancha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 21:28:34 by achancha          #+#    #+#             */
/*   Updated: 2026/11/23 21:28:34 by achancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "checker_bonus.h"

static int	ft_strcmp(const char *a, const char *b)
{
	while (*a != '\0' && *a == *b)
	{
		++a;
		++b;
	}
	return ((unsigned char)*a - (unsigned char)*b);
}

static void	reorder_stack(struct s_stack *stack, enum e_move move)
{
	int	top_item;
	int	second_idx;

	if (stack->size <= 1)
		return ;
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

static void	apply(struct s_state *state, const struct s_op *op)
{
	struct s_stack *const	src = &state->stacks[op->src];
	struct s_stack *const	dst = &state->stacks[op->dst];

	if (op->move != MOVE_PUSH)
	{
		reorder_stack(src, op->move);
		if (dst != src)
			reorder_stack(dst, op->move);
		return ;
	}
	if (src->size == 0)
		return ;
	dst->top_idx = (dst->top_idx + STACK_CAP - 1) % STACK_CAP;
	dst->items[dst->top_idx] = src->items[src->top_idx];
	src->top_idx = (src->top_idx + 1) % STACK_CAP;
	++dst->size;
	--src->size;
}

enum e_bool	run_line(struct s_state *state, const char *line)
{
	const struct s_op	ops[] = {
	{"sa", MOVE_SWAP, STK_A, STK_A},
	{"sb", MOVE_SWAP, STK_B, STK_B},
	{"ss", MOVE_SWAP, STK_A, STK_B},
	{"pa", MOVE_PUSH, STK_B, STK_A},
	{"pb", MOVE_PUSH, STK_A, STK_B},
	{"ra", MOVE_ROTATE, STK_A, STK_A},
	{"rb", MOVE_ROTATE, STK_B, STK_B},
	{"rr", MOVE_ROTATE, STK_A, STK_B},
	{"rra", MOVE_REVERSE, STK_A, STK_A},
	{"rrb", MOVE_REVERSE, STK_B, STK_B},
	{"rrr", MOVE_REVERSE, STK_A, STK_B}};
	int					i;

	i = 0;
	while (i < 11)
	{
		if (!ft_strcmp(line, ops[i].name))
		{
			apply(state, &ops[i]);
			return (TRUE);
		}
		++i;
	}
	return (FALSE);
}

enum e_bool	is_solved(const struct s_state *state)
{
	const struct s_stack *const	stack_a = &state->stacks[STK_A];
	int							i;

	if (state->stacks[STK_B].size > 0)
		return (FALSE);
	i = 0;
	while (i + 1 < stack_a->size)
	{
		if (stack_a->items[(stack_a->top_idx + i) % STACK_CAP]
			> stack_a->items[(stack_a->top_idx + i + 1) % STACK_CAP])
			return (FALSE);
		++i;
	}
	return (TRUE);
}
