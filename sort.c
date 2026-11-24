/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      :::::::    */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achancha <achancha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 21:28:34 by achancha          #+#    #+#             */
/*   Updated: 2026/11/23 21:28:34 by achancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int	stack_get(const struct s_stack *stack, int depth)
{
	return (stack->items[(stack->top_idx + depth) % STACK_CAP]);
}

static void	bring_to_top(struct s_state *state, enum e_stack side, int rank)
{
	const struct s_stack *const	stack = &state->stacks[side];
	const enum e_op				rotate[] = {RA, RB};
	const enum e_op				reverse[] = {RRA, RRB};
	int							depth;

	depth = 0;
	while (stack_get(stack, depth) != rank)
		++depth;
	if (depth <= stack->size / 2)
	{
		while (depth > 0)
		{
			apply(state, rotate[side]);
			--depth;
		}
		return ;
	}
	while (depth < stack->size)
	{
		apply(state, reverse[side]);
		++depth;
	}
}

static void	selection_sort(struct s_state *state)
{
	const struct s_stack *const	stack_a = &state->stacks[STK_A];
	const struct s_stack *const	stack_b = &state->stacks[STK_B];

	while (stack_a->size > 1)
	{
		bring_to_top(state, STK_A, stack_b->size);
		apply(state, PB);
	}
	while (stack_b->size > 0)
		apply(state, PA);
}

static void	chunk_sort(struct s_state *state)
{
	const struct s_stack *const	stack_a = &state->stacks[STK_A];
	const struct s_stack *const	stack_b = &state->stacks[STK_B];
	int							chunk_size;

	chunk_size = 1;
	while (chunk_size * chunk_size < stack_a->size * 2)
		++chunk_size;
	while (stack_a->size > 0)
	{
		if (stack_get(stack_a, 0) < stack_b->size)
		{
			apply(state, PB);
			apply(state, RB);
		}
		else if (stack_get(stack_a, 0) < stack_b->size + chunk_size)
			apply(state, PB);
		else
			apply(state, RA);
	}
	while (stack_b->size > 0)
	{
		bring_to_top(state, STK_B, stack_b->size - 1);
		apply(state, PA);
	}
}

void	sort(struct s_state *state)
{
	if (state->requested != ADAPTIVE)
		state->resolved = state->requested;
	else if (state->disorder < 0.2)
		state->resolved = SIMPLE;
	else if (state->disorder < 0.5)
		state->resolved = MEDIUM;
	else
		state->resolved = COMPLEX;
	if (state->inversions == 0)
		return ;
	if (state->resolved == SIMPLE)
		selection_sort(state);
	else if (state->resolved == MEDIUM)
		chunk_sort(state);
	else
		quick_sort(state);
}
