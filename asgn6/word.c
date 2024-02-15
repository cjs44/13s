// word.c

#include <stdlib.h>
#include <stdint.h>
#include "word.h"
#include "code.h"

// create a word and allocate
Word *word_create(uint8_t *syms, uint32_t len) {
    // allocate memory and set to parameters
    Word *w = (Word *) calloc(1, sizeof(Word));
    if (w) {
        w->len = len;
        uint8_t *ws = (uint8_t *) calloc(w->len, sizeof(uint8_t));
        if (ws) {
            w->syms = ws;
            // copy over symbols from passed syms
            for (uint32_t i = 0; i < w->len; i++) {
                w->syms[i] = syms[i];
            }
        }
    }
    return w;
}

// create new word and add passed sym
Word *word_append_sym(Word *w, uint8_t sym) {
    // create a new word
    Word *nw = (Word *) calloc(1, sizeof(Word));
    nw->len = w->len + 1;
    // create syms for the new word
    uint8_t *ns = (uint8_t *) calloc(w->len + 1, sizeof(uint8_t));
    nw->syms = ns;
    if (nw) {
        // copy over symbols from passed word
        for (uint32_t i = 0; i < w->len; i++) {
            nw->syms[i] = w->syms[i];
        }
        // append new symbol
        nw->syms[w->len] = sym;
    }
    return nw;
}

// destruct a word
void word_delete(Word *w) {
    if (w) {
        free(w);
        w = NULL;
    }
}

// create a new WordTable
WordTable *wt_create(void) {
    WordTable *wt = (WordTable *) calloc(MAX_CODE, sizeof(Word *));
    if (wt) {
        // initialize single empty word
        wt[EMPTY_CODE] = word_create(NULL, 0);
    }
    return wt;
}

// resset a WordTable to just the first word
void wt_reset(WordTable *wt) {
    if (wt) {
        for (int i = START_CODE; i < MAX_CODE; i++) {
            if (wt[i]) {
                // delete the word
                word_delete(wt[i]);
                wt[i] = NULL;
            }
        }
    }
}

// delete all words and frees
void wt_delete(WordTable *wt) {
    if (wt) {
        wt_reset(wt);
        word_delete(wt[0]);
        free(wt);
        wt = NULL;
    }
}
