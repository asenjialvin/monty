#include "monty.h"

/**
 * f_pop - pop top element off of `stack'
 * @stack: double pointer to head of stack
 * @line_number: line number of current operation
 *
 * Return: void
 */
void f_pop(stack_t **stack, unsigned int line_number)
{
	stack_t *pop = *stack;

	if (var.stack_len == 0)
	{
		fprintf(stderr,
			"L%u: can't pop an empty stack\n",
			line_number);
		exit(EXIT_FAILURE);
	}
	(*stack)->next->prev = (*stack)->prev;
	(*stack)->prev->next = (*stack)->next;
	if (var.stack_len != 1)
		*stack = (*stack)->next;
	else
		*stack = NULL;
	free(pop);
	var.stack_len--;
}
