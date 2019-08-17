#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define min(a,b) a<b ? a:b

int minimalno_koraka_rekurzija(int n, int *memo)
{
	if (n == 1)
		return 0;
	if (memo[n] != -1)
		return memo[n];

	int rez = minimalno_koraka_rekurzija(n - 1, memo);

	if (n % 2 == 0)
		rez = min(rez, minimalno_koraka_rekurzija(n / 2, memo));
	if (n % 3 == 0)
		rez = min(rez, minimalno_koraka_rekurzija(n / 3, memo));

	memo[n] = 1 + rez;
	return memo[n];
}

int koraci(int n)
{
	int *memo = malloc(sizeof(int)*n+1);

	for (int i = 0; i <= n; i++)
		memo[i] = -1;

	return  minimalno_koraka_rekurzija(n, memo);
}

int minimalno_koraka(int n) { // O(n)
	int min = 0;
	if (n < 2)
		return 0;
	while (n != 1) {
		if ((n - 1) % 3 == 0 && (n / 2) % 2 != 0) {
			n--; n /= 3; min += 2;
		}
		else if (n % 3 == 0) {
			n /= 3; min++;
		}
		else if ((n - 1) % 2 == 0 && (n / 3) % 3 != 0) {
			n--; n /= 2; min += 2;
		}
		else if (n % 2 == 0) {
			n /= 2; min++;
		}
		else {
			n--; min++;
		}
	}
		
	return min;
}

int main() {
	int n = 0;
	scanf("%d", &n);
	putchar('\n');
	printf("%d", minimalno_koraka(n)); //O(n)

	printf("\n%d", koraci(n));


	return 0;
}

