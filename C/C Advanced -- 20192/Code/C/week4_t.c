#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct
{
    void *key;
    void *value;
} Entry;

typedef struct
{
    Entry *entries;
    int total;
    int size;
    Entry (*makeNode)(void*, void*);
    int (*compare)(void*, void*);
} SymbolTable;

SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*), int (*compare)(void*, void*));
void dropSymbolTable(SymbolTable *Table);
void addEntry(void *key, void *value, SymbolTable *Table);
Entry* getEntry(void *key, SymbolTable Table);

int comparePhone(void* a, void *b)
{
    return strcmp((char*)a, (char*)b);
}

Entry makePhone(void *name, void *number)
{
    Entry res;
    res.key = strdup((char*)name);
    res.value = malloc(sizeof(long));
    memcpy(res.value, number, sizeof(long));
    return res;
}

int main()
{
    SymbolTable book = createSymbolTable(makePhone, comparePhone);

    long num;
    num = 2222; addEntry("B", &num, &book);
    num = 4444; addEntry("D", &num, &book);
    num = 1111; addEntry("A", &num, &book);
    num = 3333; addEntry("C", &num, &book);
    num = 5555; addEntry("F", &num, &book);

    for (int i = 0; i < book.total; ++i)
        printf("%s - %ld\n", (char*)book.entries[i].key, *((long*)book.entries[i].value));
    
    Entry *entry = getEntry("C", book);
    if(!entry)
        printf("Khong tim thay\n");
    else
        printf("%ld\n", *((long*)entry->value));
    return 0;
}

SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*), int (*compare)(void*, void*))
{
    SymbolTable Table;
    Table.entries = (Entry*)malloc(sizeof(Entry)*INITIAL_SIZE);
    Table.size = INITIAL_SIZE;
    Table.total = 0;
    Table.makeNode = makeNode;
    Table.compare = compare;
    return Table;
}

void dropSymbolTable(SymbolTable* Table)
{
    for (int i = 0; i < Table->total; ++i)
    {
        free(Table->entries[i].key);
        free(Table->entries[i].value);
    }
    free(Table->entries);
    Table->total = 0;
    Table->size = 0;
}

int binarySearch(Entry* entries, int l, int r, void *key, int* found, int (*compare)(void*, void*))
{
    if (r < l)
    {
        *found = 0;
        return l; //r+1
    }
    int mid = (l+r)/2;
    int res = compare(key, entries[mid].key);
    if (res == 0)
    {
        *found = 1;
        return mid;
    }
    else if (res > 0)
        return binarySearch(entries, mid+1, r, key, found, compare);
    else return binarySearch(entries, l, mid-1, key, found, compare);
}

void addEntry(void *key, void *value, SymbolTable *Table)
{
    int found, pos;
    if (Table->total > 0)
        pos = binarySearch(Table->entries, 0, Table->total-1, key, &found, Table->compare);
    else // Table emtpy
    {
        found = 0;
        pos = 0;
    }

    if (found) // Renew entry
    {
        free(Table->entries[pos].key);
        free(Table->entries[pos].value);
        Table->entries[pos] = Table->makeNode(key, value);
    }
    else // New entry
    {
        if (Table->total >= Table->size)
        {
            Table->size += INCREMENTAL_SIZE;
            Table->entries = (Entry*)realloc(Table->entries, sizeof(Entry)*(Table->size));
        }
        if (pos < Table->total) // move entries after pos
        {
            memcpy(&(Table->entries[pos+1]), &(Table->entries[pos]), (Table->total-pos)*sizeof(Entry));
        }
        // Insert entry at pos
        Table->entries[pos] = Table->makeNode(key, value);
        Table->total++;
    }
}

Entry* getEntry(void *key, SymbolTable Table)
{
    int found, pos;
    pos = binarySearch(Table.entries, 0, Table.total-1, key, &found, Table.compare);
    if (found)
        return &Table.entries[pos];
    return NULL;
}