#ifndef MY_ALGO
#define MY_ALGO

typedef struct Node {
    unsigned int prefix;
    unsigned int netmask;
    unsigned int gateway;
    unsigned int prefixeLength;
    struct Node* child;
    struct Node* right;
} Node;

extern Node *root;

void initMyAlgo();

void insertMyAlgo(unsigned int, unsigned int, unsigned int);

unsigned int lookupMyAlgo(unsigned int);

#endif