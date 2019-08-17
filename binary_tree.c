#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct node {
	int value;
	struct node *left;
	struct node *right;
};

/* iterativno pronalazi poziciju novog cvora i dodaje ga u BST */
/* vraca pokazivac na dodani cvor ili postojeci sa istom vrijednoscu */
/* pretpostavlja se da je stablo vec BST */
struct node *bst_add_iterative(struct node **root, int value) {

	while (*root != NULL) {
		if ((*root)->value > value)
			root = &(*root)->left;
		else if ((*root)->value < value)
			root = &(*root)->right;
		else
			/* duplikat: (*root)->value == value */
			return *root;
	}
	*root = malloc(sizeof(struct node));
	(*root)->value = value;
	(*root)->left = NULL;
	(*root)->right = NULL;

	return *root;

}

/* rekurzivno pronalazi poziciju novog cvora i dodaje ga u BST */
/* vraca pokazivac na dodani cvor ili postojeci sa istom vrijednoscu */
/* pretpostavlja se da je stablo vec BST */
struct node *bst_add_recursive(struct node **root, int value) {

	if (*root == NULL) {
		*root = malloc(sizeof(struct node));
		(*root)->value = value;
		(*root)->left = NULL;
		(*root)->right = NULL;
		return *root;
	} else if ((*root)->value > value)
		return bst_add_recursive(&(*root)->left, value);
	else if ((*root)->value < value)
		return bst_add_recursive(&(*root)->right, value);
	else
		/* duplikat: (*root)->value == value */
		return *root;

}

/* iterativno pronalazi poziciju cvora sa vrijednoscu value */
/* vraca pokazivac na pronadjeni cvor ili NULL ukoliko niti jedan cvor nema vrijednost value */
/* pretpostavlja se da je stablo vec BST */
struct node *bst_find_iterative(struct node *root, int value) {

	while (root != NULL) {
		if (root->value > value)
			root = root->left;
		else if (root->value < value)
			root = root->right;
		else
			/* pronasli: root->value == value */
			return root;
	}
	return NULL;

}

/* rekurzivno pronalazi poziciju cvora sa vrijednoscu value */
/* vraca pokazivac na pronadjeni cvor ili NULL ukoliko niti jedan cvor nema vrijednost value */
/* pretpostavlja se da je stablo BST */
struct node *bst_find_recursive(struct node *root, int value) {

	if (root == NULL)
		return NULL;
	else if (root->value > value)
		return bst_find_recursive(root->left, value);
	else if (root->value < value)
		return bst_find_recursive(root->right, value);
	else
		/* pronasli: root->value == value */
		return root;

}

/* racuna visinu stabla */
int tree_height(struct node *root) {

	int height_l, height_r;

	if (root == NULL)
		return 0;

	height_l = tree_height(root->left);		/* racunaj visinu lijevog podstabla */
	height_r = tree_height(root->right);	/* racunaj visinu desnog podstabla */

	/* visina trenutnog (pod)stabla je veca od visine lijevog odnosno desnog podstabla
	 * uvecano za 1 tj. visinu trenutnog cvora */
	return 1 + (height_l > height_r ? height_l : height_r);

}

/* ispisuje sve cvorove stabla u preorder poretku */
void tree_print_preorder(struct node *root) {

	if (root == NULL)
		return;

	printf("%d ", root->value);			/* ispisi trenutni cvor */
	tree_print_preorder(root->left);	/* preorder poretkom ispisi lijevo podstablo */
	tree_print_preorder(root->right);	/* preorder poretkom ispisi desno podstablo */

}

/* ispisuje sve cvorove stabla u postorder poretku */
void tree_print_postorder(struct node *root) {

	if (root == NULL)
		return;

	tree_print_postorder(root->left);	/* postorder poretkom ispisi lijevo podstablo */
	tree_print_postorder(root->right);	/* postorder poretkom ispisi desno podstablo */
	printf("%d ", root->value);			/* ispisi trenutni cvor */

}

/* ispisuje sve cvorove stabla u inorder poretku */
void tree_print_inorder(struct node *root) {

	if (root == NULL)
		return;

	tree_print_inorder(root->left);		/* inorder poretkom ispisi lijevo podstablo */
	printf("%d ", root->value);			/* ispisi trenutni cvor */
	tree_print_inorder(root->right);	/* inorder poretkom ispisi desno podstablo */

}

/* ispisuje sve cvorove stabla u levelorder poretku */
/* typedef void * queue_element_t; */
void tree_print_levelorder(struct node *root) {

	/* iz reda cemo povlaciti trenutni cvor za ispis,
	 * te istovremeno u njega dodavati djecu tog cvora */
	/* typedef void * queue_element_t */
	queue_t queue = queue_new();

	/* ispis pocinje sa korijenom stabla */
	if (root != NULL)
		queue_enqueue(queue, root);

	while (!queue_is_empty(queue)) {
		struct node *current = (struct node *) queue_dequeue(queue);
		printf("%d ", current->value);				/* ispisi trenutni cvor */
		if (current->left != NULL)
			queue_enqueue(queue, current->left);	/* dodaj u red lijevo podstablo */
		if (current->right != NULL)
			queue_enqueue(queue, current->right);	/* dodaj u red desno podstablo */
	}

	queue_delete(queue);

}

/* oslobadja svu dinamicki alociranu memoriju za stablo */
void tree_free(struct node *root) {

	if (root == NULL)
		return;

	tree_free(root->left);	/* oslobodi memoriju za sve cvorove iz lijevog podstabla */
	tree_free(root->right);	/* oslobodi memoriju za sve cvorove iz desnog podstabla */
	free(root);				/* oslobodi memoriju za trenutni cvor */

}

void tree_print_leaves(struct node *root) {
	if (root == NULL)
		return;

	if (root->left == NULL && root->right == NULL)
		printf("%d ", root->value);

	tree_print_leaves(root->left);
	tree_print_leaves(root->right);
}

int tree_equal(struct node *root1, struct node *root2) {
	
	if (root1 == NULL && root2 == NULL)
		return 1;

	if (root1 == NULL && root2 != NULL)
		return 0;

	if (root1 != NULL && root2 == NULL)
		return 0;

	if (root1->value != root2->value)
		return 0;

	if (!tree_equal(root1->left, root2->left))
		return 0;

	if (!tree_equal(root1->right, root2->right))
		return 0;
	
	return 1;
}
