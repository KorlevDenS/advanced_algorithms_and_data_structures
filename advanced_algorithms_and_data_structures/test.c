#include <stdio.h>
#include <string.h>

#include "test.h"

void test() {

	char buf[11];



	FILE* input = fopen("square_string_input.txt", "r");


	fgets(buf, sizeof(buf), input);

	fclose(input);

	printf("Input: %s\n", buf);
	//printf("Output: %zu\n", (size_t)(writwe_ptr - buf));
	printf("Output: %zu\n", strlen(buf));

}