#include <stdio.h>
#include "avl-tree.h"

int main(){

	AvlNode *node = NULL;
	short int height=0;
	insert(&node, 8);
	insert(&node, 4);
	insert(&node, 9);
	insert(&node, 10);
	insert(&node, 2);
	insert(&node, 6);
	insert(&node, 1);
	insert(&node, 3);
	insert(&node, 5);
	insert(&node, 7);
	printInOrder(&node, 0);
	printf("\n");
	return 0;
}
