#include <stdio.h>
#include <stdlib.h>
#include "MyAlgo.h"

void initMyAlgo() {
    root = NULL;
}

void insertMyAlgo(unsigned int addr, unsigned int netmask, unsigned int gw) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->prefix = addr;
    newNode->netmask = netmask;
    newNode->gateway = gw;
    newNode->left = NULL;
    newNode->right = NULL;

    if (root == NULL) {
        root = newNode;
    } else {
        struct Node* current = root;
        while (1) {
            if ((addr & netmask) == (current->prefix & current->netmask)) {
                if (current->netmask <= netmask) {
                    if (current->right == NULL) {
                        current->right = newNode;
                        break;
                    } else {
                        current = current->right;
                    }
                } else {
                    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
                    temp->prefix = current->prefix;
                    temp->netmask = current->netmask;
                    temp->gateway = current->gateway;
                    temp->left = current->left;
                    temp->right = current->right;

                    current->prefix = addr;
                    current->netmask = netmask;
                    current->gateway = gw;
                    current->left = newNode;
                    current->right = temp;
                    break;
                }
            } else {
                if (current->netmask <= netmask) {
                    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
                    temp->prefix = addr;
                    temp->netmask = netmask;
                    temp->gateway = gw;
                    temp->left = newNode;
                    temp->right = NULL;

                    current->right = temp;
                    break;
                } else {
                    if (current->left == NULL) {
                        current->left = newNode;
                        break;
                    } else {
                        current = current->left;
                    }
                }
            }
        }
    }
}

// Function to perform a lookup and return the longest prefix matching gateway
unsigned int lookupMyAlgo(unsigned int addr) {
    unsigned int longestMatch = 0;
    struct Node* current = root;

    while (current != NULL) {
        if ((addr & current->netmask) == (current->prefix & current->netmask)) {
            longestMatch = current->gateway;
            current = current->right;
        } else {
            current = current->left;
        }
    }

    return longestMatch;
}

// Function to print the tree (for debugging purposes)
void printTree(struct Node* node) {
    if (node == NULL) {
        return;
    }

    printf("Prefix: %u, Netmask: %u, Gateway: %u\n", node->prefix, node->netmask, node->gateway);
    printTree(node->left);
    printTree(node->right);
}