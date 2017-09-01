#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool error = false;
char error_msg[10];

void push(int *stack, int *size, int value) {
	if (error) {
		return;
	}
	if (*size >= 10) {
		error = true;
		error_msg[0] = value + '0';
		error_msg[1] = '\0';
	} else {
		stack[*size] = value;
		++*size;
	}
}

int pop(int *stack, int *size) {
	if (error) {
		return -1;
	}
	if (*size <= 0) {
		error = true;
		error_msg[0] = (char)0;
		error_msg[1] = '\0';
	} else {
		--*size;
		return stack[*size];
	}
	return -1;
}

int main(void)
{
	int stack[10];
	int stack_size = 0;
	int input;
	int line = 1;
	bool last_was_digit = false;
	while (1) {
		input = getchar();
		if (input == EOF) {
			break;
		}
		if (error && input != '\n') {
			continue;
		}
		if (isdigit(input) > 0) {
			if (last_was_digit) {
				int num = pop(stack, &stack_size);
				num *= 10;
				num += input;
				input = num;
			}
			push(stack, &stack_size, input - '0');
			last_was_digit = true;
		} else {
			switch (input) {
				case '\n':
					if (!error) {
						if (stack_size == 0 || stack_size > 1) {
							error = true;
							strcpy(error_msg, "\\n");
						}
					}
					if (error) {
						printf("line %d: error at %s\n", line, error_msg);
					} else {
						printf("line %d: %d\n", line, stack[0]);
					}
					stack_size = 0;
					++line;
					error = false;
				 	break;
				case '+':
				{
					if (stack_size < 2) {
						error = true;
						error_msg[0] = '+';
						error_msg[1] = '\0';
						break;
					}
					int num1 = pop(stack, &stack_size);
					int num2 = pop(stack, &stack_size);
					push(stack, &stack_size, num2 + num1);
					break;
				}
				case '-':
				{
					if (stack_size < 2) {
						error = true;
						error_msg[0] = '-';
						error_msg[1] = '\0';
						break;
					}
					int num1 = pop(stack, &stack_size);
					int num2 = pop(stack, &stack_size);
					push(stack, &stack_size, num2 - num1);
					break;
				}
				case '*':
				{
					if (stack_size < 2) {
						error = true;
						error_msg[0] = '*';
						error_msg[1] = '\0';
						break;
					}
					int num1 = pop(stack, &stack_size);
					int num2 = pop(stack, &stack_size);
					push(stack, &stack_size, num2 * num1);
					break;
				}
				case '/':
				{
					if (stack_size < 2) {
						error = true;
						error_msg[0] = '/';
						error_msg[1] = '\0';
						break;
					}
					int num1 = pop(stack, &stack_size);
					int num2 = pop(stack, &stack_size);
					if (num1 == 0) {
						error = true;
						error_msg[0] = '/';
						error_msg[1] = '\0';
						break;
					}
					push(stack, &stack_size, (int)(num2 / num1));
					break;
				}
				case ' ':
					break;
				default:
					error = true;
					error_msg[0] = (char)input;
					error_msg[1] = '\0';
			}
			last_was_digit = false;
		}
	}
	return 0;
}