#include <stdio.h>
#include <stdlib.h>

#include "Dictionary.h"

static int randInt() { return (rand() * rand()); }

int main() {
    enum { DataSize = 8 };
    typedef int DataType;

    int i;
    int iteration = 10000;
    int insertPos = randInt() % iteration;
    int size;
    DataType data0[] = { randInt(), randInt(), randInt(), randInt() };
    DataType data[DataSize] = { randInt(), randInt(), randInt(), randInt(), randInt(), randInt(), randInt(), randInt() };
    String str0 = { (Bytes)data0, sizeof(data0) };
    String str;
    Dictionary *dict = Dictionary_new();

    for (i = 0; i < iteration; ++i) {
        if (i == insertPos) { Dictionary_insert(dict, &str0); }
        size = (randInt() % (DataSize - 1)) + 1;
        data[randInt() % size] = randInt();
        data[randInt() % size] = randInt();
        Dictionary_insert(dict, String_initi(&str, data, size, sizeof(DataType)));
    }

    printf("%d\n", Dictionary_find(dict, &str0));
    data[randInt() % DataSize] = randInt();
    data[randInt() % DataSize] = randInt();
    printf("%d\n", Dictionary_find(dict, String_init(&str0, data, sizeof(data))));

    Dictionary_delete(dict);

    return 0;
}
