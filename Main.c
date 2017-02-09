#include <stdio.h>
#include <stdlib.h>

#include "Dictionary.h"


static int randInt() { return (rand() * rand()); }
static unsigned randUnsigned() { return (unsigned)(rand() * rand()); }

int main() {
    enum { DataSize = 8 };
    typedef int DataType;

    int i;
    int iteration = 10000;
    int insertPos = randUnsigned() % iteration;
    int size;
    DataType data0[] = { randInt(), randInt(), randInt(), randInt() };
    DataType data[DataSize] = { randInt(), randInt(), randInt(), randInt(), randInt(), randInt(), randInt(), randInt() };
    String str0 = { (Bytes)data0, sizeof(data0) };
    String str;
    Dictionary *dict = Dictionary_new();

    for (i = 0; i < iteration; ++i) {
        if (i == insertPos) { Dictionary_insert(dict, &str0); }
        size = (randUnsigned() % (DataSize - 1)) + 1;
        data[randUnsigned() % size] = randInt();
        data[randUnsigned() % size] = randInt();
        Dictionary_insert(dict, String_initi(&str, data, size, sizeof(DataType)));
    }

    printf("%d\n", Dictionary_find(dict, &str0));
    data[randUnsigned() % DataSize] = randInt();
    data[randUnsigned() % DataSize] = randInt();
    printf("%d\n", Dictionary_find(dict, String_init(&str0, data, sizeof(data))));

    Dictionary_delete(dict);

    return 0;
}
