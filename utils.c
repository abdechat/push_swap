#include <sdlib.h>

t_list	*new_node(int value)
{
	t_list *new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	return new;
}

void push_top(t_stack *stack, t_list *new)
{
	if (!stack || !new)
		return ;
	new->prev = NULL;
	new->next = stack->top;
	if (!stack->bottom)
		stack->bottom = new;
	else
		stack->top->prev = new;
	stack->top = new;
	stack->size++;
}


void push_bottom(t_stack *stack, t_list *new)
{
	if (!stack || !new)
		return ;
	new->next = NULL;
	if (stack->bottom)
	{
		new->prev = stack->bottom;
		stack->bottom->next = new;
	}
	else
	{
		new->prev = NULL;
		stack->top = new;
	}
	stack->bottom = new;
	stack->size++;
}

void sa(t_stack *stack)
{
	int x;

	if (!stack || !stack->top || !stack->top->next)
		return ;
	x = stack->top->value;
	stack->top->value = stack->top->next->value; 
	stack->top->next->value = x;
}

void sb(t_stack *stack)
{
	int x;

	if (!stack || !stack->top || !stack->top->next)
		return ;
	x = stack->top->value;
	stack->top->value = stack->top->next->value; 
	stack->top->next->value = x;
}

void ss(t_stack *stack_a, t_stack *stack_b)
{
	sa(stack_a);
	sb(stack_b);
}

void pa(t_stack *stack_a, t_stack *stack_b)
{
	t_list	*node;

	if (!stack_b || !stack_b->top || !stack_a)
		return ;
	node = stack_b->top;
	stack_b->top = node->next;
	if (stack_b->size > 1)
		stack_b->top->prev = NULL;
	else
	{
		stack_b->top = NULL;
		stack_b->bottom = NULL;
	}
	stack_b->size--;
	push_top(stack_a,node);
}

void pb(t_stack *stack_a, t_stack *stack_b)
{
	t_list	*node;

	if (!stack_a || !stack_a->top || !stack_b)
		return ;
	node = stack_a->top;
	stack_a->top = node->next;
	if (stack_a->size > 1)
		stack_a->top->prev = NULL;
	else
	{
		stack_a->top = NULL;
		stack_a->bottom = NULL;
	}
	stack_a->size--;
	push_top(stack_b,node);
}

void ra(t_stack *stack)
{
	t_list *node;

	if (!stack || stack->size < 2)
		return ;
	node = stack->top;
	stack->top = node->next;
	stack->top->prev = NULL;
	push_bottom(stack, node);
	stack->size--;
}

void rb(t_stack *stack)
{
	t_list *node;

	if (!stack || stack->size < 2)
		return ;
	node = stack->top;
	stack->top = node->next;
	stack->top->prev = NULL;
	push_bottom(stack, node);
	stack->size--;
}
















