typedef int keyType;

typedef struct avlNode{
    keyType balance, key;
    struct avlNode *left, *right;
} avlNode;

void rotateLeft(avlNode **node);

void rotateRight(avlNode **node);

int insert(avlNode **node, keyType key);

void prkeyTypePreOrder(avlNode **node, keyType height);

void prkeyTypeInOrder(avlNode **node, keyType height);

void prkeyTypePosOrder(avlNode **node, keyType height);

void freeTree(avlNode **node);
