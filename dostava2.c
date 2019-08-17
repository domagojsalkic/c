#include <stdio.h>
#include <time.h>
#include "queue/queue.h"

struct point {
	int x, y;
	int dist;
};

int in_array(queue_element_t p, queue_element_t point, int size) {
	for (int i = 0; i < size; ++i) {
		if (point[i].x == p->x && point[i].y == p->y)
			return 0;
	}
	return 1;
}

int shortest_path(int **matrix, int n, int m) {
	if (matrix[1][0] && matrix[0][1])
		return -1;
	queue_element_t point = malloc(sizeof(struct point) * (m * n));
	queue_t que = queue_new();
	queue_element_t elem;
	int i = 0, j = 0, size = 0;
	point->x = 0;
	point->y = 0;
	point->dist = 0;
	queue_enqueue(que, &point[0]);
	while (!queue_is_empty(que)) {
		elem = queue_dequeue(que);
		i = elem->x;
		j = elem->y;	
		if (i == n - 1 && j == m - 1) {
			return elem->dist;
		}
		if (i + 1 < n && matrix[i + 1][j] == 0){// && !in_array(elem,point,m*n)) {
			++size;
			point[size].x = elem->x + 1;
			point[size].y = elem->y;
			point[size].dist = elem->dist + 1;
			queue_enqueue(que, &point[size]);
		}
		if (j + 1 < m && matrix[i][j+1]==0) {// && !in_array(elem, point, m*n)) {
			++size;
			point[size].x = elem->x;
			point[size].y = elem->y + 1;
			point[size].dist = elem->dist + 1;
			queue_enqueue(que, &point[size]);
		}		
		if (i - 1 >= 0 && matrix[i - 1][j] == 0 && in_array(elem, point, size+1)) {
			++size;
			point[size].x = elem->x - 1;
			point[size].y = elem->y;
			point[size].dist = elem->dist + 1;
			queue_enqueue(que, &point[size]);
		}
		if (j - 1 >= 0 && matrix[i][j - 1] == 0 && in_array(elem,point, size+1)) {
			++size;
			point[size].x = elem->x;
			point[size].y = elem->y - 1;
			point[size].dist = elem->dist + 1;
			queue_enqueue(que, &point[size]);
		}
	}
	return -1;
}

int main() {

	int n = 0, m = 0;
	srand(time(NULL));
	while (1) {
		scanf("%d %d", &n, &m);
		if (n >= 2 && m < 1000)
			break;
	}
	int **matrix = malloc(sizeof(*matrix) * n);
	if (matrix)
	{
		for (int i = 0; i < n; i++) {
			matrix[i] = malloc(sizeof(*matrix[i]) * m);
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			matrix[i][j] = rand() % 2;
		}
	}
	matrix[0][0] = 0;
	matrix[n - 1][m - 1] = 0;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			printf("%d ", matrix[i][j]);
		}
		putchar('\n');
	}

	printf("%d ",shortest_path(matrix,n,m));


	return 0;
}