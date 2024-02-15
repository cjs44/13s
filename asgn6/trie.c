// trie.c

#include <stdlib.h>
#include <stdint.h>
#include "trie.h"
#include "code.h"

// constructor for a TrieNode
TrieNode *trie_node_create(uint16_t code) {
    // allocate memory and set to parameters
    TrieNode *n = (TrieNode *) calloc(1, sizeof(TrieNode));
    if (n) {
        n->code = code;
        // null children
        for (int i = 0; i < ALPHABET; i++) {
            n->children[i] = NULL;
        }
    }
    return n;
}

// destructor for a Trie Node
void trie_node_delete(TrieNode *n) {
    if (n) {
        free(n);
        n = NULL;
    }
}

// initialize a trie
TrieNode *trie_create(void) {
    TrieNode *n = trie_node_create(EMPTY_CODE);
    if (n) {
        return n;
    } else {
        return NULL;
    }
}

// delete trie not including root
void trie_reset(TrieNode *root) {
    if (root) {
        // delete children
        for (int i = 0; i < ALPHABET; i++) {
            if (root->children[i]) {
                trie_delete(root->children[i]);
                root->children[i] = NULL;
            }
        }
    }
}

// delete the whole trie from passed node down
void trie_delete(TrieNode *n) {
    if (n) {
        // delete all of the children recursively
        for (int i = 0; i < ALPHABET; i++) {
            if (n->children[i]) {
                trie_delete(n->children[i]);
                n->children[i] = NULL;
            }
        }
        // delete that root node
        trie_node_delete(n);
    }
}

// return the child node with the sym
TrieNode *trie_step(TrieNode *n, uint8_t sym) {
    return n->children[sym];
}
