#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "square_string.h"

#define MAX_STRING_LENGTH 100 + 1 + 1 // +1 for null terminator && +1 for possible newline character
#define MAX_NUMBER_OF_STRINGS_LENGTH 3 + 1 + 1 // +1 for null terminator && +1 for possible newline character

void square_string() {

	int8_t strings_count = 0;
	FILE* input = fopen("square_string_input.txt", "r");
	char num_buf[MAX_NUMBER_OF_STRINGS_LENGTH];
	fgets(num_buf, sizeof(num_buf), input);
	strings_count = (int8_t)strtol(num_buf, NULL, 10);
	for (int8_t i = 0; i < strings_count; i++) {

		char buf[MAX_STRING_LENGTH];
		fgets(buf, sizeof(buf), input);
		size_t len = strlen(buf);
		if (len % 2 == 0) {
			printf("No\n");
		} else {
			size_t half_len = len / 2;
			char* first_half = (char*)malloc(half_len);
			char* second_half = (char*)malloc(half_len);
			assert(first_half != NULL && second_half != NULL);
			memcpy(first_half, buf, half_len * sizeof(char));
			memcpy(second_half, buf + half_len, half_len * sizeof(char));
			int cmp = memcmp(first_half, second_half, half_len * sizeof(char));
			if (cmp == 0) {
				printf("Yes\n");
			}
			else {
				printf("No\n");
			}
			free(first_half);
			free(second_half);
		}
	}
	fclose(input);

}
