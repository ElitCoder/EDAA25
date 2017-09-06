#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
	int c;
	unsigned int len = 0, max_len = 0, word_len = 0;
	char *word = malloc((word_len + 1) * sizeof(char));
	char *max_word = malloc((word_len + 1) * sizeof(char));
	for (;;) {
		c = getchar();
		if (isalpha(c) != 0) {
			++len;
			if (len > word_len) {
				word = realloc(word, (len + 1) * sizeof(char));
				word_len = len;
			}
			word[len - 1] = c;
			word[len] = '\0';
		} else {
			if (c == EOF) {
				break;
			} else {
				if (len > max_len) {
					max_len = len;
					max_word = realloc(max_word, (max_len + 1) * sizeof(char));
					strcpy(max_word, word);
				}
				len = 0;
			}
		}
	}
	printf("%u characters in longest word: %s\n", max_len, max_word);
	free(word);
	free(max_word);
	return 0;
}