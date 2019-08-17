#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "trie.h"
#include "queue.h"

struct node {
	struct book book;
	struct node *left;
	struct node *right;
};

struct node *bst_add_iterative(struct node **root, struct book book) {

	while (*root != NULL) {
		if ((*root)->book.id > book.id)
			root = &(*root)->left;
		else if ((*root)->book.id < book.id)
			root = &(*root)->right;
		else
			/* duplikat: (*root)->value == value */
			return *root;
	}
	*root = malloc(sizeof(struct node));
	(*root)->book.id = book.id;
	(*root)->left = NULL;
	(*root)->right = NULL;

	return *root;

}

struct node *bst_add_recursive(struct node **root, struct book book) {

	if (*root == NULL) {
		*root = malloc(sizeof(struct node));
		(*root)->book = book;
		(*root)->left = NULL;
		(*root)->right = NULL;
		return *root;
	}
	else if ((*root)->book.id > book.id)
		return bst_add_recursive(&(*root)->left, book);
	else if ((*root)->book.id < book.id)
		return bst_add_recursive(&(*root)->right, book);
	else
		/* duplikat: (*root)->value == value */
		return *root;

}

void tree_print_inorder(struct node *root) {

	if (root == NULL)
		return;

	tree_print_inorder(root->left);		/* inorder poretkom ispisi lijevo podstablo */
	printf("%u %s  -  %u\n", root->book.id, root->book.name, root->book.price);	/* ispisi trenutni cvor */
	tree_print_inorder(root->right);	/* inorder poretkom ispisi desno podstablo */
}

void tree_print_postorder(struct node *root) {

	if (root == NULL)
		return;

	tree_print_postorder(root->left);	/* postorder poretkom ispisi lijevo podstablo */
	tree_print_postorder(root->right);	/* postorder poretkom ispisi desno podstablo */
	printf("%u %s  -  %u \n", root->book.id, root->book.name, root->book.price);	/* ispisi trenutni cvor */

}

void tree_print_preorder(struct node *root) {

	if (root == NULL)
		return;

	printf("%u %s  -  %u \n", root->book.id, root->book.name, root->book.price);	/* ispisi trenutni cvor */
	tree_print_preorder(root->left);	/* preorder poretkom ispisi lijevo podstablo */
	tree_print_preorder(root->right);	/* preorder poretkom ispisi desno podstablo */

}

void tree_free(struct node *root) {

	if (root == NULL)
		return;

	tree_free(root->left);	/* oslobodi memoriju za sve cvorove iz lijevog podstabla */
	tree_free(root->right);	/* oslobodi memoriju za sve cvorove iz desnog podstabla */
	free(root);				/* oslobodi memoriju za trenutni cvor */

}

int main() {

	trie_t root;
	struct book *books;
	struct node *tree = NULL;
	struct node *tree2 = NULL;
	unsigned num_books;
	char book_name[BOOK_NAME_MAX_LEN + 1];
	unsigned i;

	/* ucitavanje knjiga iz datoteke */
	if (load_books("knjige.csv", &books, &num_books))
		return -1;

	/* korijen triea, pocetak svih rijeci, uvijek alociran */
	root = trie_new_node();

	/* ubacivanje knjiga u trie */
	for (i = 0; i < num_books; i++) {
		trie_insert_word(root, books[i].name);
	}

	/* ubacivanje struktura knjiga u binarno stablo */
	for (i = 0; i < num_books; ++i) {
		bst_add_recursive(&tree, books[i]);
	}
	
	/* ISPISIVANJE CLANOVA BINARNOG STABLA */

	//tree_print_postorder(tree);
	//tree_print_inorder(tree);
	//tree_print_preorder(tree);


	/* knjige su u trieu, ne trebaju nam vise kao zaseban niz */
	free(books);
	tree_free(tree);

	/* pretrazivanje knjiga */
	while (1) {
		int search_result = 0;

		printf("\nUpisi ime knjige (prazan string za izlaz iz programa): ");
		gets(book_name);

		if (!strcmp(book_name, ""))
			break;

		search_result = trie_search_word(root, book_name);
		printf("'%s' %s ispravan naziv knjige.\n", book_name, search_result ? "je" : "nije");
		if (!search_result) {
			printf("Moguci kandidati su:\n");
			trie_print_prefixed_word(root, book_name);
		}
	}


	return 0;
}
