#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

int main()
{
    // Init
    JRB PhoneBook = make_jrb();
    JRB iter; // iterator for RB Tree

    // Add
    // jrb_insert_str(PhoneBook, "A", new_jval_l(1000));
    // jrb_insert_str(PhoneBook, "B", new_jval_l(1001));
    // jrb_insert_str(PhoneBook, "C", new_jval_l(1002));
    // jrb_insert_str(PhoneBook, "D", new_jval_l(1003));
    // jrb_insert_str(PhoneBook, "E", new_jval_l(1004));
    // jrb_insert_str(PhoneBook, "ABC", new_jval_l(1005));
    for (int i = 0; i < 5; ++i)
    {
        char st[100];
        long number;
        printf("Name: "); fflush(stdin); gets(st);
        printf("Number: "); scanf("%ld", &number);
        jrb_insert_str(PhoneBook, strdup(st), new_jval_l(number)); // how free st ???
    }

    // Show
    jrb_traverse(iter, PhoneBook) {
        printf("%s: %ld\n", jval_s(iter->key), jval_l(iter->val));
    }

    // Delete node
    iter = jrb_find_str(PhoneBook, "ABC");
    if (iter)
    {
        // free(jval_s(iter->key));
        jrb_delete_node(iter);
    }

    // Change node
    iter = jrb_find_str(PhoneBook, "A");
    if (iter == NULL)
        printf("Not found\n");
    else
    {
        long num;
        printf("Change number: "); scanf("%ld", &num);
        iter->val = new_jval_l(num);
    }

    // Show again
    jrb_traverse(iter, PhoneBook) {
        printf("%s: %ld\n", jval_s(iter->key), jval_l(iter->val));
    }

    // Delete tree
    jrb_free_tree(PhoneBook);

    return 0;
}