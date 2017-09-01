#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool error = false;
char error_msg[10];

void push(int *stack, int *size, int value) {
	if (*size >= 10) {
		error = true;
		error_msg[0] = value;
		error_msg[1] = '\0';
		printf("set error to %d\n", value);
		//printf("error: pushing when there's no space left\n");
	} else {
		//printf("pushing at %d\n", *size);
		stack[*size] = value;
		++*size;
		//++*pos;
		//return *(stack + *pos);
	}
}

int pop(int *stack, int *size) {
	if (*size <= 0) {
		error = true;
		error_msg[0] = (char)0;
		error_msg[1] = '\0';
		//printf("error: popping when there's nothing on the stack\n");
	} else {
		--*size;
		//printf("popping at %d\n", *size);
		
		int value = stack[*size];
		
		return value;
		//return stack[*pos--];
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
		//printf("input was: %d\n", input);
		
		if (input == EOF) {
			break;
		}
		
		if (error && input != '\n') {
			continue;
		}
		
		if (isdigit(input) > 0) {
			if(last_was_digit) {
				//printf("doing pop\n");
				int num = pop(stack, &stack_size);
				//printf("done with pop\n");
				
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
					int num1 = pop(stack, &stack_size);
					int num2 = pop(stack, &stack_size);
					push(stack, &stack_size, num2 + num1);
					//printf("calculated + with %d %d and result %d at %d\n", num1, num2, num1 + num2, stack_size - 1);
					break;
				}
				
				case '-':
				{
					int num1 = pop(stack, &stack_size);
					int num2 = pop(stack, &stack_size);

					push(stack, &stack_size, num2 - num1);
					//printf("calculated - with %d %d and result %d at %d\n", num1, num2, num2 - num1, stack_size - 1);
					break;
				}
				
				case '*':
				{
					int num1 = pop(stack, &stack_size);
					int num2 = pop(stack, &stack_size);
					push(stack, &stack_size, num2 * num1);
					//printf("calculated * with %d %d and result %d at %d\n", num1, num2, num2 * num1, stack_size - 1);
					break;

				}
				
				case '/':
				{
					int num1 = pop(stack, &stack_size);
					int num2 = pop(stack, &stack_size);
					
					if(num1 == 0) {
						//printf("error: division by zero\n");
						error = true;
						error_msg[0] = '/';
						error_msg[1] = '\0';
						
						continue;
					}
					
					
					push(stack, &stack_size, (int)(num2 / num1));
					//printf("calculated / with %d %d and result %d at %d\n", num1, num2, num2 / num1, stack_size - 1);
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
