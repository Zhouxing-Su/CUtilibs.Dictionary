#include "Dictionary.h"

#include <stdlib.h>


Dictionary* Dictionary_new() {
    Dictionary *dict = (Dictionary*)calloc(1, sizeof(Dictionary));
    return dict;
}

void Dictionary_delete(Dictionary *dict) {
    Dictionary_SizeType i = 0;
    if (dict == NULL) { return; }
    for (; i < Dictionary_AlphabetSize; ++i) { Dictionary_delete(dict->child[i]); }
    free(dict);
}

void Dictionary_insert(Dictionary *dict, String *str) {
    Dictionary_SizeType i;
    Dictionary_Id id = ++(dict->id);
    Dictionary **p;

    for (i = 0; i < str->size; ++i) {
        p = &(dict->child[str->bytes[i]]);
        if (*p == NULL) { *p = Dictionary_new(); }
        dict = *p;
    }

    dict->id = id;
}

Dictionary_Id Dictionary_find(Dictionary *dict, String *str) {
    Dictionary_SizeType i;

    for (i = 0; i < str->size; ++i) {
        dict = dict->child[str->bytes[i]];
        if (dict == NULL) { return Dictionary_InvalidId; }
    }

    return dict->id;
}
