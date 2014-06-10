typedef struct AvlNode{
	int balance, key;
	struct AvlNode *left, *right;
} AvlNode;

void rotateLeft(AvlNode **node);

void rotateRight(AvlNode **node);

int insert(AvlNode **node, int key);

void printTree(AvlNode **node, int height);

AvlNode* delete(AvlNode **node, int key, short int *height);
