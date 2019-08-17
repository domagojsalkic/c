#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int najbolji(int *brojNagrada, int size) {
	int* memo = malloc(size * sizeof(int));

	for (int i = 0; i < 5; i++) {
		if (i == 0)
			memo[i] = brojNagrada[i];
		else
			memo[i] = max(memo[i - 1], brojNagrada[i]);
	}
	for (int i = 4; i < size; i++) {
		if (memo[i-1] < (brojNagrada[i] + memo[i - 5])) {
			memo[i] = brojNagrada[i] + memo[i - 5];
		}
		else {
			memo[i] = memo[i - 1];
		}
	}
	for (int i = 0; i < size; i++) {
		printf("%d ",memo[i]);
	}
	return memo[size-1];
}

int main() {
	int *brojNagrada, size = 0;
	scanf("%d", &size);
	srand(time(NULL));
	brojNagrada = (int)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		brojNagrada[i] = (rand() % 40);
	}
	for (int i = 0; i < size; i++) {
		printf("%d ", brojNagrada[i]);
	}
	printf("\n");
	printf("\n%d ",najbolji(brojNagrada, size));
}
