#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../SPA labos 6/list/list.h"
#include "book.h"
#include "../SPA labos 6/map/map.h"
#include "../SPA labos 6/set/djb2.h"
#include "../SPA labos 6/set/set.h"

void ukupan_broj_autora_set(struct book *knjige, unsigned broj) {
	set_t autori;
	autori = set_new_advanced(strcmp, djb2);

	while (*knjige->author) {
		if (!set_is_member(autori, knjige->author))
			set_add(autori, knjige->author);
		++knjige;
	}
	printf("U datoteci se nalazi: %d knjiga, a ukupan broj autora je: %d \n", broj, set_size(autori));
	set_delete(autori);
}

void ukupan_broj_autora_map(struct book *knjige, unsigned broj) {
	map_t autori = map_new_advanced(strcmp, djb2);
	int broj_autora = 0;

	while (*knjige->author) {
		if (map_has_key(autori, knjige->author)) {
			map_put(autori, _strdup(knjige->author), map_get(autori, knjige->author) + 1);
		}
		else {
			map_put(autori, _strdup(knjige->author), 1);
			++broj_autora;
		}
		++knjige;
	}
	printf("U datoteci se nalazi: %d knjiga, a ukupan broj autora je: %d \n",broj, broj_autora);
	map_delete(autori);
}


void autori_i_knjige(struct book *knjige, unsigned broj) {
	map_t autori = map_new_advanced(strcmp, djb2);
	map_element_t elem;
	while (*knjige->author) {
		if (map_has_key(autori, knjige->author)) {
			map_put(autori, _strdup(knjige->author), (map_get(autori, knjige->author) + 1));
		}
		else {
			map_put(autori, _strdup(knjige->author), 1);
		}
		++knjige;
	}

	map_iterator_t iter = map_iterator(autori);

	for (iter; map_iterator_is_valid(iter); map_iterator_next(iter)) {
		elem = map_iget(iter);
		printf("%s - %d\n", elem.key, elem.value);
	}
	map_iterator_delete(iter);
	map_delete(autori);
}

/*
void autori_i_knjige_popis(struct book *knjige, unsigned broj) {
	
}
*/

int main() {

	struct book *knjige_niz = NULL;
	unsigned broj_knjiga = 0;

	if (load_books("knjige.csv", &knjige_niz, &broj_knjiga))
		return -1;

	ukupan_broj_autora_set(knjige_niz, broj_knjiga);

	autori_i_knjige(knjige_niz, broj_knjiga);

	//autori_i_knjige_popis (knjige_niz, broj_knjiga);

	free(knjige_niz);

	return 0;

}



