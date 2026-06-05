#include "push_swap.h"
#include <stdio.h>

void	stack_printer(t_node *head)
{
	t_node	*current;

	current = head;
	while (current != NULL)
	{
		printf("[%d], ", current->value);
		if ((current->previous) != NULL)
		{
			printf("previous is: [%d], ", current->previous->value);
		}
		else
		{
			printf("(Previous = NULL), ");
		}
		current = current->next;
	}
	printf("-> NULL\n");
}

int	main(void)
{
	t_node *stack_a;
	t_node *stack_b;

	stack_a = NULL;
	stack_b = NULL;

	stack_a = node_builder(2);
	stack_a->next = node_builder(5);
	stack_a->next->previous = stack_a;
	stack_a->next->next = node_builder(8);
	stack_a->next->next->previous = stack_a->next;

	printf("stack_a's initial state: \n");
	stack_printer(stack_a);
	printf("stack_a after sa: \n");
	sa(&stack_a);
	stack_printer(stack_a);
}