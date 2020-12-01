#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5

typedef struct
{
    char name[80];
    long number;
} PhoneEntry;

typedef struct
{
    PhoneEntry *entries;
    int total;
    int size; // Max
} PhoneBook;

PhoneBook createPhoneBook();
void dropPhoneBook(PhoneBook* book);
void addPhoneNumber(char * name, long number, PhoneBook* book);
PhoneEntry* getPhoneNumber(char * name, PhoneBook book);

int main()
{
    PhoneBook book = createPhoneBook();
    
    addPhoneNumber("Do Lam", 909090, &book);
    addPhoneNumber("Tuan Dung", 929292, &book);
    addPhoneNumber("Anh Thang", 919191, &book);
    addPhoneNumber("Ngo Phong", 949494, &book);
    addPhoneNumber("C", 333333, &book);
    addPhoneNumber("B", 222222, &book);
    addPhoneNumber("A", 111111, &book);
    addPhoneNumber("D", 444444, &book);

    for (int i = 0; i < book.total; ++i)
        printf("%s - %ld\n", book.entries[i].name, book.entries[i].number);
    
    PhoneEntry *entry = getPhoneNumber("Do Lam", book);
    if(!entry)
        printf("Khong tim thay\n");
    else
        printf("%ld\n", entry->number);
    return 0;
}

PhoneBook createPhoneBook()
{
    PhoneBook P;
    P.entries = (PhoneEntry*)malloc(sizeof(PhoneEntry)*INITIAL_SIZE);
    P.size = INITIAL_SIZE;
    P.total = 0;
    return P;
}

void dropPhoneBook(PhoneBook* book)
{
    free(book->entries);
    book->total = 0;
    book->size = 0;
}

int binarySearch(PhoneEntry* entries, int l, int r, char *name, int* found)
{
    if (r < l)
    {
        *found = 0;
        return l; //r+1
    }
    int mid = (l+r)/2;
    int res = strcmp(name, entries[mid].name);
    if (res == 0)
    {
        *found = 1;
        return mid;
    }
    else if (res > 0)
        return binarySearch(entries, mid+1, r, name, found);
    else return binarySearch(entries, l, mid-1, name, found);
}

void addPhoneNumber(char * name, long number, PhoneBook* book)
{
    int found, pos;
    if (book->total > 0)
        pos = binarySearch(book->entries, 0, book->total-1, name, &found);
    else // Phonebook emtpy
    {
        found = 0;
        pos = 0;
    }

    if (found)
        book->entries[pos].number = number;
    else // New entry
    {
        if (book->total >= book->size)
        {
            book->size += INCREMENTAL_SIZE;
            book->entries = (PhoneEntry*)realloc(book->entries, sizeof(PhoneEntry)*(book->size));
        }
        if (pos < book->total) // move entries after pos
        {
            memcpy(&(book->entries[pos+1]), &(book->entries[pos]), (book->total-pos)*sizeof(PhoneEntry));
        }
        // Insert entry at pos
        strcpy(book->entries[pos].name, name);
        book->entries[pos].number = number;
        book->total++;
    }
}

PhoneEntry* getPhoneNumber(char * name, PhoneBook book)
{
    int found, pos;
    pos = binarySearch(book.entries, 0, book.total-1, name, &found);
    if (found)
        return &book.entries[pos];
    return NULL;
}