#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort/common.h"
#include "sort/bubble.h"
#include "sort/selection.h"
#include "sort/insertion.h"
#include "sort/shell.h"
#include "sort/quick.h"

/* ispisuje sve clanove niza u jednom retku */
void print(element_t *numbers, size_t len) {
	element_t *p;
	for (p = numbers; p < numbers + len; ++p) {
		if (p != numbers)
			printf(", ");
		printf("%d", *p);
	}
	putchar('\n');
}

/* funkcija za usporedbu dva člana tipa element_t (sinonim definiran u sort/types.h)  */
int element_t_compare(const void *e1, const void *e2) {
	return *((element_t *) e1) - *((element_t *) e2);
}

int main() {

	element_t numbers[10000];	/* mijenjanjem veličine ovog niza mijenjamo ukupan broj brojeva koje je potrebno sortirati */
	size_t i;
	clock_t start;
	clock_t end;

	/* napunimo niz slucajnim brojevima */
	for (i = 0; i < COUNTOF(numbers); ++i)
		numbers[i] = (rand() % 2 ? 1 : -1) * (rand() % COUNTOF(numbers));

	printf("Prije: ");
	print(numbers, COUNTOF(numbers));

	start = clock();
	/* otkomentirati (samo jedan) algoritam */
	//bubble_sort_simple(numbers, COUNTOF(numbers));
	//bubble_sort(numbers, COUNTOF(numbers), sizeof(element_t), element_t_compare);
	//selection_sort_simple(numbers, COUNTOF(numbers));
	//selection_sort(numbers, COUNTOF(numbers), sizeof(element_t), element_t_compare);
	//insertion_sort_simple(numbers, COUNTOF(numbers));
	//insertion_sort(numbers, COUNTOF(numbers), sizeof(element_t), element_t_compare);
	//shell_sort_simple(numbers, COUNTOF(numbers));
	//shell_sort(numbers, COUNTOF(numbers), sizeof(element_t), element_t_compare);
	//quick_sort_simple(numbers, COUNTOF(numbers));
	//quick_sort(numbers, COUNTOF(numbers), sizeof(element_t), element_t_compare);
	end = clock();

	printf("Poslije: ");
	print(numbers, COUNTOF(numbers));

	printf("Trajanje: %.03lf ms\n", (end - start) * 1000.0 / CLOCKS_PER_SEC);

	/* provjerimo jesu li brojevi u uzlaznom poretku */
	for (i = 1; i < COUNTOF(numbers); ++i)
		if (numbers[i] < numbers[i - 1]) {
			printf("Greska na indeksu %lu!\n", i);
			break;
		}
	if (i == COUNTOF(numbers))
		puts("Ok");

	return 0;

}
