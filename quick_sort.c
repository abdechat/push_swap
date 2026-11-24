/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      :::::::    */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabraou <ysabraou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 21:28:34 by ysabraou          #+#    #+#             */
/*   Updated: 2026/11/23 21:28:34 by ysabraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static void	move_one(struct s_state *state, enum e_loc from, enum e_loc to)
{
	if (from == BOT_A)
		apply(state, RRA);
	if (from == BOT_B)
		apply(state, RRB);
	if ((from == TOP_A || from == BOT_A) && (to == TOP_B || to == BOT_B))
		apply(state, PB);
	if ((from == TOP_B || from == BOT_B) && (to == TOP_A || to == BOT_A))
		apply(state, PA);
	if (to == BOT_A)
		apply(state, RA);
	if (to == BOT_B)
		apply(state, RB);
}

static void	order_top(struct s_state *state, int size)
{
	const struct s_stack *const	stack_a = &state->stacks[STK_A];

	if (size < 2)
		return ;
	if (stack_get(stack_a, 0) > stack_get(stack_a, 1))
		apply(state, SA);
	if (size < 3)
		return ;
	if (stack_get(stack_a, 1) > stack_get(stack_a, 2))
	{
		apply(state, PB);
		apply(state, SA);
		apply(state, PA);
	}
	if (stack_get(stack_a, 0) > stack_get(stack_a, 1))
		apply(state, SA);
}

static void	plan_parts(struct s_chunk chunk, struct s_chunk *parts)
{
	const enum e_loc	destinations[N_LOCS][N_PARTS] = {{BOT_A, BOT_B, TOP_B},
	{BOT_B, TOP_B, TOP_A}, {BOT_A, BOT_B, TOP_A}, {TOP_B, BOT_A, TOP_A}};
	const int			low_percents[N_LOCS] = {36, 20, 16, 50};
	const int			high_percents[N_LOCS] = {46, 56, 44, 40};
	int					i;

	parts[PART_LOW].size = chunk.size * low_percents[chunk.loc] / 100;
	parts[PART_HIGH].size = chunk.size * high_percents[chunk.loc] / 100;
	parts[PART_MID].size = chunk.size - parts[PART_LOW].size
		- parts[PART_HIGH].size;
	parts[PART_LOW].min_rank = chunk.min_rank;
	parts[PART_MID].min_rank = chunk.min_rank + parts[PART_LOW].size;
	parts[PART_HIGH].min_rank = parts[PART_MID].min_rank + parts[PART_MID].size;
	i = 0;
	while (i < N_PARTS)
	{
		parts[i].loc = destinations[chunk.loc][i];
		++i;
	}
}

static void	split(struct s_state *state, struct s_chunk chunk,
	struct s_chunk *parts)
{
	const enum e_stack			stack_of[N_LOCS] = {STK_A, STK_A, STK_B, STK_B};
	const struct s_stack *const	stack = &state->stacks[stack_of[chunk.loc]];
	enum e_loc					destination;
	int							rank;
	int							i;

	plan_parts(chunk, parts);
	i = 0;
	while (i < chunk.size)
	{
		if (chunk.loc == BOT_A || chunk.loc == BOT_B)
			rank = stack_get(stack, stack->size - 1);
		else
			rank = stack_get(stack, 0);
		if (rank < parts[PART_MID].min_rank)
			destination = parts[PART_LOW].loc;
		else if (rank < parts[PART_HIGH].min_rank)
			destination = parts[PART_MID].loc;
		else
			destination = parts[PART_HIGH].loc;
		move_one(state, chunk.loc, destination);
		++i;
	}
}

void	quick_sort(struct s_state *state)
{
	struct s_chunk	pending_chunks[64];
	struct s_chunk	chunk;
	int				pending_count;
	int				i;

	*pending_chunks = (struct s_chunk){TOP_A, 0, state->stacks[STK_A].size};
	pending_count = 1;
	while (pending_count > 0)
	{
		--pending_count;
		chunk = pending_chunks[pending_count];
		if (chunk.size > 3)
		{
			split(state, chunk, &pending_chunks[pending_count]);
			pending_count += N_PARTS;
			continue ;
		}
		i = 0;
		while (i < chunk.size)
		{
			move_one(state, chunk.loc, TOP_A);
			++i;
		}
		order_top(state, chunk.size);
	}
}
