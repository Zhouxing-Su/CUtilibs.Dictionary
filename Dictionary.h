////////////////////////////////
/// usage : 1.	a dictionary implemented by trie (prefix tree).
///         2.  it is very convenient to collaborate with an array and use the id as index.
/// 
/// note  : 1.	it requires that each string to be inserted is unique, 
///             so that it is a bijection between str and id.
///
/// example:
///         #include <stdio.h>
///         #include <stdlib.h>
///
///         #include "Dictionary.h"
///
///         static int randInt() { return (rand() * rand()); }
///
///         int main() {
///             enum { DataSize = 8 };
///             typedef int DataType;
///         
///             int i;
///             int iteration = 10000;
///             int insertPos = randInt() % iteration;
///             int size;
///             DataType data0[] = { randInt(), randInt(), randInt(), randInt() };
///             DataType data[DataSize] = { randInt(), randInt(), randInt(), randInt(), randInt(), randInt(), randInt(), randInt() };
///             String str0 = { (Bytes)data0, sizeof(data0) };
///             String str;
///             Dictionary *dict = Dictionary_new();
///         
///             for (i = 0; i < iteration; ++i) {
///                 if (i == insertPos) { Dictionary_insert(dict, &str0); }
///                 size = (randInt() % (DataSize - 1)) + 1;
///                 data[randInt() % size] = randInt();
///                 data[randInt() % size] = randInt();
///                 Dictionary_insert(dict, String_initi(&str, data, size, sizeof(DataType)));
///             }
///         
///             printf("%d\n", Dictionary_find(dict, &str0));
///             data[randInt() % DataSize] = randInt();
///             data[randInt() % DataSize] = randInt();
///             printf("%d\n", Dictionary_find(dict, String_init(&str0, data, sizeof(data))));
///
///             Dictionary_delete(dict);
///         
///             return 0;
///         }
///
////////////////////////////////

#ifndef SZX_CUTILIBS_DICTIONARY_H
#define SZX_CUTILIBS_DICTIONARY_H



enum {
    Dictionary_BitsInByte = 8,
    Dictionary_AlphabetSize = (1 << Dictionary_BitsInByte) // number of characters that could be in the string.
};

enum {
    Dictionary_InvalidId = 0 // stand for no child.
};

typedef int String_SizeType;
typedef unsigned char *Bytes;
typedef struct String {
    Bytes bytes;
    String_SizeType size;
} String;

typedef struct Dictionary Dictionary;
typedef int Dictionary_SizeType;
typedef Dictionary_SizeType Dictionary_Id;

struct Dictionary {
    // in the root node: the number of child (so empty string is not supported).
    // in other nodes: the unique id of the leaf in this dictionary.
    Dictionary_Id id; // consecutive integers start from 1 in this dictionary.
    // OPTIMIZE[szx][2]: make it Dictionary** and use lazy allocation pattern to reduce wasted memory in leaves.
    // pointer of children indexed by character in certain depth.
    Dictionary *child[Dictionary_AlphabetSize];
};


/// methods for Dictionary.
Dictionary* Dictionary_new();
void Dictionary_delete(Dictionary *dict);

// it assumes that the str is not empty and does not exist in this dictionary yet.
void Dictionary_insert(Dictionary *dict, String *str);
// return Dictionary_InvalidId if not found.
Dictionary_Id Dictionary_find(Dictionary *dict, String *str);


/// methods for String.
static String* String_init(String *str, void *bytes, String_SizeType size) {
    str->bytes = (Bytes)bytes;
    str->size = size;
    return str;
}
static String* String_initi(String *str, void *bytes, String_SizeType itemCount, String_SizeType itemSize) {
    String_init(str, bytes, itemCount * itemSize);
    return str;
}


#endif // SZX_CUTILIBS_DICTIONARY_H
