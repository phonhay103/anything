#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    int (*compareKey)(void*, void*);
    int (*compareValue)(void*, void*);
} SymbolTable;

SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*), int (*compareKey)(void*, void*), int (*compareValue)(void*, void*));
void dropSymbolTable(SymbolTable *Table);
void addEntry(void *key, void *value, SymbolTable *Table);
Entry* getByKey(void *key, SymbolTable Table);
void getByValue(void *value, SymbolTable Table);
void addToTable(int n, SymbolTable *Table);
void sortByValue(SymbolTable Table);

int compareName(void *a, void *b)
{
    return strcmp((char*)a, (char*)b);
}

int compareScore(void *a, void *b)
{
    double x = *((double*)a);
    double y = *((double*)b);
    if (x == y)
        return 0;
    else if (x < y)
        return -1;
    else return 1;
}

Entry makeStudent(void *name, void *score)
{
    Entry res;
    res.key = strdup((char*)name);
    res.value = malloc(sizeof(double));
    memcpy(res.value, score, sizeof(double));
    return res;
}

void showSymbolTable(SymbolTable Table)
{
    for (int i = 0; i < Table.total; ++i)
        printf("%s - %.1lf\n", (char*)Table.entries[i].key, *((double*)Table.entries[i].value));
}

int main()
{
    SymbolTable Student = createSymbolTable(makeStudent, compareName, compareScore);
    // addToTable(5, &Student);
    double score;
    score = 3.9; addEntry("B", &score, &Student);
    score = 2; addEntry("D", &score, &Student);
    score = 3; addEntry("A", &score, &Student);
    score = 4; addEntry("C", &score, &Student);
    score = 5; addEntry("F", &score, &Student);
    score = 7.5; addEntry("A", &score, &Student);
    score = 5; addEntry("X", &score, &Student);
    score = 2; addEntry("Z", &score, &Student);

    showSymbolTable(Student);
    
    // Entry *entry = getByKey("C", Student);
    // if(!entry)
    //     printf("Khong tim thay\n");
    // else
    //     printf("%.1lf\n", *((double*)entry->value));

    // score = 5.0;
    // getByValue(&score, Student);
    sortByValue(Student);
    dropSymbolTable(&Student);
    return 0;
}

SymbolTable createSymbolTable(Entry (*makeEntry)(void*, void*), int (*compareKey)(void*, void*), int (*compareValue)(void*, void*))
{
    SymbolTable Table;
    Table.entries = (Entry*)malloc(sizeof(Entry)*INITIAL_SIZE);
    Table.size = INITIAL_SIZE;
    Table.total = 0;
    Table.makeNode = makeEntry;
    Table.compareKey = compareKey;
    Table.compareValue = compareValue;
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

int BS(Entry* entries, int l, int r, void *key, int* found, int (*compare)(void*, void*))
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
        return BS(entries, mid+1, r, key, found, compare);
    else return BS(entries, l, mid-1, key, found, compare);
}

void addEntry(void *key, void *value, SymbolTable *Table)
{
    int found, pos;
    if (Table->total > 0)
        pos = BS(Table->entries, 0, Table->total-1, key, &found, Table->compareKey);
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

Entry* getByKey(void *key, SymbolTable Table)
{
    int found, pos;
    pos = BS(Table.entries, 0, Table.total-1, key, &found, Table.compareKey);
    if (found)
        return &Table.entries[pos];
    return NULL;
}

void addToTable(int n, SymbolTable *Table)
{
    char st[100];
    double score;
    for (int i = 0; i < n; ++i)
    {
        printf("Name: "); fflush(stdin); gets(st);
        printf("Score: "); scanf("%lf", &score);
        addEntry(st, &score, Table);
    }
}

void getByValue(void *value, SymbolTable Table)
{
    int found = 0;
    for (int i = 0; i < Table.total; ++i)
        if (Table.compareValue(value, Table.entries[i].value) == 0)
        {
            printf("Index: %d - Name: %s\n", i, (char*)Table.entries[i].key);
            found = 1;
        }
    if (!found)
        printf("Khong tim thay\n");
}

void sortByValue(SymbolTable Table)
{
    if (Table.total == 0)
    {
        printf("Emtpy!\n");
        return;
    }
    
    Entry *A = (Entry*)malloc(sizeof(Entry)*Table.total);
    for (int i = 0; i < Table.total; ++i) //Entries
        for (int j = 0; j <= i; ++j)
        {
            if (j == i)
                A[i] = Table.makeNode(Table.entries[i].key, Table.entries[i].value);
            int res = Table.compareValue(Table.entries[i].value, A[j].value);
            if (res < 0)
            {
                memcpy(&A[j+1], &A[j], (i-j)*sizeof(Entry));
                A[j] = Table.makeNode(Table.entries[i].key, Table.entries[i].value);
                break;
            }
        }

    for (int i = 0; i < Table.total; ++i)
        printf("%s-%.2lf ", (char*)A[i].key, *((double*)A[i].value));
    puts("");

    for (int i = 0; i < Table.total; ++i)
    {
        free(A[i].key);
        free(A[i].value);
    }
    free(A);
}