#include "monty.h"
#include <stdio.h>
#define _POSIX_C_SOURCE 200809L


int main(int argc, char *argv[])
{
	instruction_t instructions[] = {
		{"push", f_push},
		{"pall", f_pall},
		{"pint", f_pint},
		{"swap", f_swap},
		{"add", f_add},
		{"pop", f_pop},
		{"nop", f_nop},
		{NULL, NULL}
	};
	char line[1024];
	size_t len = 0;
	FILE *file;
	stack_t *stack = NULL;
	unsigned int line_number = 0;

	if (argc != 2)
	{
		fprintf(stderr, "L<line_number>: usage: push integer\n");
		exit (EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}


	while (fgets(line, sizeof(line), file) != NULL)
	{
		line_number++;
		len = strlen(line);
		if (len > 0 && line[len - 1] == '\n')
		{
			line[len - 1] = '\0';
		}
		f_process_line(&stack, line, instructions);
	}
	fclose(file);

	free_stack(&stack);

	return (EXIT_SUCCESS);
}
void f_process_line(stack_t **stack, const char *line, instruction_t instructions[])
{
	int i;
	char *opcode = strtok((char *)line, " ");
	if (opcode != NULL)
	{
		int found = 0;

		for (i = 0; instructions[i].opcode != NULL; i++)
		{
			if (strcmp(opcode, instructions[i].opcode) == 0)
			{
				instructions[i].f(stack, 0);
				found = 1;
				break;
			}
		}
		if (!found)
		{
			fprintf(stderr, "Unknown opcode: %s\n", opcode);
		}
	}
}

void free_stack(stack_t **stack)
{
	if (*stack != NULL)
	{
		stack_t *temp = *stack;
		*stack = (*stack)->next;
		free(temp);
	}
}
