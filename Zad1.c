#include <stdio.h>
#include <time.h>
#include<stdlib.h>

#define koraka 3

int svaki_dan(int *niz, int size);
int najbolji(int* niz, int size);
int niz_najboljih_dana(int*niz, int size,int n,int poc);

int main(){
	int niz[8] = {-2,-3,4,-1,-2,1,5,-3}, size = 8;
	//scanf("%d", &size);	
	//srand(time(NULL));
	//niz = malloc (size*sizeof(int));
	/*for (int i = 0; i < size; i++) {
		niz[i] = (rand() % 20) - 10;
	}*/
	for (int i = 0; i < size; i++) {
		printf("%d ",niz[i]);
	}

	//printf("%d \n", svaki_dan(niz, sizeof(niz) / sizeof(*niz)));
	//printf("%d \n",niz_najboljih_dana(niz, size, koraka, 0));
	printf("\n%d ", najbolji(niz, size));  


	free(niz);

	return 0;
}

int svaki_dan(int *niz, int size) {
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += niz[i];
	}
	return sum;
}

int niz_najboljih_dana(int*niz, int size,int n,int poc) {
	int maxNagrada = 0;
	if ((poc + n) <= size) {
		for (int i = poc + n; i >= poc; i--)
			maxNagrada += niz[i];
		return max(maxNagrada, niz_najboljih_dana(niz, size, n , poc+1));
	}
	return maxNagrada;
}
int najbolji(int* niz, int size) {
	int najveciUkupno=niz[0], najveciDo=niz[0];
	for (int i = 0; i < size; i++) {
		najveciDo = max(niz[i],(niz[i]+najveciDo));
		najveciUkupno = max(najveciUkupno,najveciDo);
	}
	return najveciUkupno;
}