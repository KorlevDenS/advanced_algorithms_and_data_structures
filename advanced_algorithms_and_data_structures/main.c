#include <stdio.h>
#include <time.h>

#include "main.h"
#include "test.h"
#include "square_string.h"
#include "k_th_zero.h"

typedef struct {
	const char* name;
	void (*alg_task)();
} AlgTask;

int main() {

	printf("Advanced Algorithms and Data Structures\n");
	printf("-------------------------\n");
	
	AlgTask alg_tasks[] = {
		//{ "Test", test},
		//{"Square string?", square_string},
		{"K-th zero", k_th_zero}
	};

	int tasks_count = sizeof(alg_tasks) / sizeof(alg_tasks[0]);

	for (int i = 0; i < tasks_count; i++) {
		printf("Task: \"%s\":\n\n", alg_tasks[i].name);
		clock_t start = clock();
		alg_tasks[i].alg_task();
		clock_t end = clock();
		double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
		printf("\nElapsed time: %.6f s | %.3f ms\n", elapsed, elapsed * 1000);
		printf("-------------------------\n");
	}
	
	return 0;
}