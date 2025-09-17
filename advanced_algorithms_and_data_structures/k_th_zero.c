#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "k_th_zero.h"

#define MAX_NUM_LEN 6 + 2 // +2 for \0 and \n
#define MAX_ELEMENTS_COUNT 200000
#define MAX_ELEMENT_STR_LEN 6
#define MAX_ELEMENTS_STR_LEN (6 * MAX_ELEMENTS_COUNT) + (MAX_ELEMENTS_COUNT - 1) + 2 // + whitespace, \0 and \n
#define MAX_QUERY_STR_LEN 6 * 3 + 2 + 2
#define S_ARGS_COUNT 3
#define U_ARGS_COUNT 2


static int32_t read_int32_from_line(FILE* opened_file) {
	int32_t elements_count;
	char num_buf[MAX_NUM_LEN];
	fgets(num_buf, sizeof(num_buf), opened_file);
	sscanf_s(num_buf, "%" PRId32, &elements_count);
	return elements_count;
}

static void read_int32_array_from_line(int32_t** elements, const size_t elements_count, FILE* opened_file) {
	size_t max_elements_str_len = (MAX_ELEMENT_STR_LEN * elements_count) + (elements_count - 1) + 2;
	char* elements_buf = (char*)malloc(max_elements_str_len * sizeof(char));
	assert(elements_buf != NULL);
	char* elements_buf_pos = elements_buf;
	fgets(elements_buf_pos, max_elements_str_len * sizeof(char), opened_file);
	int32_t element;
	int bytes_read;
	for (int32_t i = 0; i < elements_count; i++) {
		sscanf_s(elements_buf_pos, "%" PRId32 "%n", &element, &bytes_read);
		elements_buf_pos += bytes_read;
		(*elements)[i] = element;
	}
	free(elements_buf);
	return;
}

struct query {
	char type;
	int32_t left;
	int32_t right;
	int32_t param;
	int32_t idx;
	int16_t block_idx;
};

static void read_queries(struct query** queries, const size_t queries_count, FILE* opened_file) {
	for (size_t i = 0; i < queries_count; i++) {
		char* query_buf = (char*)malloc(MAX_QUERY_STR_LEN * sizeof(char));
		assert(query_buf != NULL);
		char* query_buf_pos = query_buf;
		fgets(query_buf_pos, MAX_QUERY_STR_LEN * sizeof(char), opened_file);
		char type;
		int32_t left;
		int32_t right;
		int32_t param;
		int32_t idx;
		int16_t block_idx;
		int bytes_read;
		sscanf_s(query_buf_pos, "%c%n", &type, (unsigned)sizeof(char), &bytes_read);
		query_buf_pos += bytes_read;
		sscanf_s(query_buf_pos, "%" PRId32 "%n", &left, &bytes_read);
		query_buf_pos += bytes_read;
		if (type == 's') {
			sscanf_s(query_buf_pos, "%" PRId32 "%n", &right, &bytes_read);
			query_buf_pos += bytes_read;
		}
		if (type == 'u') {
			right = left;
		}
		sscanf_s(query_buf_pos, "%" PRId32 "%n", &param, &bytes_read);
		free(query_buf);
		(*queries)[i] = (struct query){ type, left - 1, right - 1, param, (int32_t)i, -1 };
	}
	return;
}

static int cmpQuery(const void* pa, const void* pb) {
	const struct query* a = pa;
	const struct query* b = pb;
	if (a->block_idx != b->block_idx) {
		return (a->block_idx < b->block_idx) ? -1 : 1;
	}
	if (a->right < b->right) return -1;
	if (a->right > b->right) return 1;
	return 0;
}

static void mo_sort(struct query** queries, const size_t queries_count, const int16_t block_size) {
	for (size_t i = 0; i < queries_count; i++) {
		(*queries)[i].block_idx = (int16_t)((*queries)[i].left / block_size);
	}
	qsort(*queries, queries_count, sizeof(struct query), cmpQuery);
}

static void answer(struct query** queries) {

}

static int16_t init_blocks_array(struct query*** blocks, const int16_t block_size, const int32_t elements_count) {
	int16_t blocks_count = block_size;
	int16_t additional_block_size = elements_count - (block_size * block_size);
	if (additional_block_size > 0) {
		blocks_count++;
	}
	*blocks = (struct query**)malloc(blocks_count * sizeof(struct query*));
	for (int i = 0; i < block_size; i++) {
		(*blocks)[i] = (struct query*)malloc(block_size * sizeof(struct query));
	}
	if (additional_block_size > 0) {
		(*blocks)[block_size] = (struct query*)malloc(additional_block_size * sizeof(struct query));
	}
	return blocks_count;
}

//static void group

void k_th_zero() {

	FILE *input = fopen("k_th_zero_input.txt", "r");

	size_t elements_count = read_int32_from_line(input);
	int32_t* elements = (int32_t*)malloc(elements_count * sizeof(int32_t));
	read_int32_array_from_line(&elements, elements_count, input);

	int16_t block_size = max(1, (int16_t)sqrt(elements_count));
	size_t queries_count = read_int32_from_line(input);
	struct query* queries = (struct query*)malloc(queries_count * sizeof(struct query));
	read_queries(&queries, queries_count, input);

	for (int i = 0; i < queries_count; i++) {
		printf("%c %" PRId32 " %" PRId32 " %" PRId32 " b=%" PRId32 "\n", queries[i].type, queries[i].left, queries[i].right, queries[i].param, queries[i].block_idx);
	}
	printf("\n");


	mo_sort(&queries, queries_count, block_size);



	for (int i = 0; i < queries_count; i++) {
		printf("%c %" PRId32 " %" PRId32 " %" PRId32 " b=%" PRId32 "\n", queries[i].type, queries[i].left, queries[i].right, queries[i].param, queries[i].block_idx);
	}
	printf("\n");


	for (int i = 0; i < elements_count; i++) {
		printf("%d ", elements[i]);
	}
	printf("\n");
	printf("%d\n", block_size);

	

	free(elements);
	fclose(input);
	//int elements[]

}
