#ifndef MY_ALGO
#define MY_ALGO

typedef struct Node {
    unsigned int prefix;
    unsigned int netmask;
    unsigned int gateway;
    struct Node* left;
    struct Node* right;
} Node;

extern Node *root;

void initMyAlgo();

void insertPrefix(Node *, unsigned int, unsigned int, unsigned int, int);

void insertMyAlgo(unsigned int, unsigned int, unsigned int);

unsigned int lookupPrefix(Node *, unsigned int, int);

unsigned int lookupMyAlgo(unsigned int);

void printNode(Node* node, int depth);

void printTree();

#endif