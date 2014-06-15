#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

void rotateLeft(AvlNode **node){

	AvlNode *a = *node;
	AvlNode *b = a->right;
	a->right = b->left;
	b->left = a;
	a->balance = b->balance = 0;
	*node = b;
}

void rotateRight(AvlNode **node){

	AvlNode *a = *node;
	AvlNode *b = a->left;
	a->left = b->right;
	b->right = a;
	a->balance = b->balance = 0;
	*node = b;
}

int insert(AvlNode **node, int key){

	if(!*node){
		AvlNode *newNode = (AvlNode*)malloc(sizeof(AvlNode));
		if(!newNode){
			printf("\nMALLOC FAILURE");
			exit(0);
		}
		newNode->right = newNode->left = NULL;
		newNode->key = key;
		newNode->balance = 0;
		*node = newNode;
		return 1;
	}
	else if(key < (*node)->key){
		if(insert(&(*node)->left, key)){
			(*node)->balance--;
			switch((*node)->balance){
				case 0:
					return 0;
				case -1:	
					return 1;
				case -2:	
					if((*node)->left->balance == -1)
						rotateRight(node);
					else{
						switch((*node)->left->right->balance){
							case -1:
								rotateLeft(&(*node)->left);
								rotateRight(node);
								(*node)->right->balance++;
								break;
							case 0:
								rotateLeft(&(*node)->left);
								rotateRight(node);
								break;
							case 1:
								rotateLeft(&(*node)->left);
								rotateRight(node);
								(*node)->left->balance--;
								break;
						}
					}
					return 0;				
			}
		}
		else 								
			return 0;
	}
	else{
		if(insert(&(*node)->right, key)){
			(*node)->balance++;
			switch((*node)->balance){
				case 0:						
					return 0;
				case 1:						
					return 1;
				case 2:						
					if((*node)->right->balance == 1)	
						rotateLeft(node);
					else{
						switch((*node)->right->left->balance){
							case -1:
								rotateRight(&(*node)->right);
								rotateLeft(node);
								(*node)->right->balance++;
								break;
							case 0:
								rotateRight(&(*node)->right);
								rotateLeft(node);
								break;
							case 1:
								rotateRight(&(*node)->right);
								rotateLeft(node);
								(*node)->left->balance--;
								break;
						}
					}
					return 0;
			}
		}
		else 									
			return 0;
	}
}

void printPreOrder(AvlNode **node, int height){

	if(*node){
		printf("key: %d\tbalance: %d\theight: %d\n", (*node)->key, (*node)->balance, height);
		printPreOrder(&(*node)->left, height+1);
		printPreOrder(&(*node)->right, height+1);
	}
}

void printInOrder(AvlNode **node, int height){

	if(*node){
		printInOrder(&(*node)->left, height+1);
		printf("key: %d\tbalance: %d\theight: %d\n", (*node)->key, (*node)->balance, height);
		printInOrder(&(*node)->right, height+1);
	}
}

void printPosOrder(AvlNode **node, int height){

	if(*node){
		printPosOrder(&(*node)->left, height+1);
		printPosOrder(&(*node)->right, height+1);
		printf("key: %d\tbalance: %d\theight: %d\n", (*node)->key, (*node)->balance, height);
	}
}


AvlNode* delete(AvlNode **node, int key, short int *height){

	AvlNode *aux = *node, *aux2, aux3;
	if((*node)->key == key){
		if((*node)->right){
			if((*node)->left){
				if((*node)->right->left){

				}
				else{
					aux2 = (*node)->right;
					aux2->left = (*node)->left;
					aux2->balance = (*node)->balance-1;
					free(*node);
					if(aux2->balance == -2){
						if(aux2->left->balance == -1)	//simple rotate
							rotateRight(&aux2);
						else if(aux2->left->balance == 0){
							rotateRight(&aux2);
							aux2->balance++;
							aux2->right->balance--;
						}
						else{					//double rotate
							switch(aux2->left->right->balance){
								case -1:
									rotateLeft(&aux2->left);
									rotateRight(&aux2);
									aux2->right->balance++;
									break;
								case 0:
									rotateLeft(&aux2->left);
									rotateRight(&aux2);
									break;
								case 1:
									rotateLeft(&aux2->left);
									rotateRight(&aux2);
									aux2->left->balance--;
									break;
							}
						}
					}
					return aux2;
				}
			}
			else{
				aux = (*node)->right;
				free(*node);
				*height = 1;
				return aux;
			}
		}
		else if((*node)->left){
			aux = (*node)->left;
			free(*node);
			*height = 1;
			return aux;
		}
		else{
			free(*node);
			*height = 1;
			return NULL;
		}
	}
	else if(key < (*node)->key){
		(*node)->left = delete(&(*node)->left, key, height);
		if(*height){
            (*node)->balance++;
            switch((*node)->balance){
				case 0:
					return *node;
				case 1:
					*height = 0;
					return *node;
				case 2:
					if((*node)->right->balance != -1){
						rotateLeft(node);
					}
					*height = 0;
					return *node;
			}
		}
		else
			return *node;
	}
	else{
		if(delete(&(*node)->right, key, height));
	}
}

/*
 *	delete all nodes of the tree
 * */

void freeTree(AvlNode **node){
	if(*node){
		freeTree(&(*node)->left);
		freeTree(&(*node)->right);
		free(*node);
	}
}
