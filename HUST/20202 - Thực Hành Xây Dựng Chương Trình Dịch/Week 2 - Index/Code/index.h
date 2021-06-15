#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "lib/jrb.h"

#define MAX_NUM_STOPWORDS 50
#define MAX_LENGTH_STOPWORD 50
#define MAX_LIST_INDEX_LENGTH 1000
#define MAX_LINE_LENGTH 200

const char *stopw_filepath = "data/stopw.txt";
const char *text_filepath = "data/vanban.txt";

JRB create_dict();
void delete_dict(JRB dict);
void show_dict(JRB dict);
void insert_word_to_dict(JRB dict, char *key, int line, int column);
char *to_lowercase(char *word);
char *trim(char *s);
char* remove_dot_after(char* word);
void remove_stopw_from_dict(JRB dict, char stopw[MAX_NUM_STOPWORDS][MAX_LENGTH_STOPWORD], int num_of_stopw);

JRB create_dict()
{
    return make_jrb();
}

void delete_dict(JRB dict)
{
    jrb_free_tree(dict);
}

void show_dict(JRB dict)
{
    char *st;
    char list_index[MAX_LIST_INDEX_LENGTH];
    JRB node;

    jrb_traverse(node, dict)
    {
        st = strdup(jval_s(node->val));
        for (int i = 0; i < strlen(st); ++i)
            if (st[i] == '.')
                st[i] = ',';
        printf("%s %s\n", jval_s(node->key), st);
        free(st);
    }
}

void insert_word_to_dict(JRB dict, char *key, int line, int column)
{
    char new_list_index[MAX_LIST_INDEX_LENGTH];
    char st[200];
    JRB node = jrb_find_str(dict, key);
    if (!node) /* Word does not exist */
    {
        // Create new word in dict: default num = 1
        sprintf(new_list_index, "1,(%d.%d)", line, column);
        jrb_insert_str(dict, key, new_jval_s(strdup(new_list_index)));
    }
    else /* Word exists */
    {
        // Get number of rows at the first of list_index
        char *num = strtok(jval_s(node->val), ",");

        // Inscrease 1 & add to new_list_index at first
        itoa(atoi(num) + 1, new_list_index, 100);

        // Get row indexs & add to new_list_index
        num = strtok(NULL, ",");
        while (num != NULL)
        {
            strcat(new_list_index, ",");
            strcat(new_list_index, num);
            num = strtok(NULL, ",");
        }
        // Add new index to new_list_index
        sprintf(new_list_index, "%s,(%d.%d)", new_list_index, line, column);

        // Update new list_index
        node->val = new_jval_s(strdup(new_list_index));
    }
}

char *to_lowercase(char *word)
{
    for (int i = 0; i < strlen(word); ++i)
        word[i] = tolower(word[i]);
    return word;
}

char *ltrim(char *s)
{
    while (isspace(*s))
        s++;
    return s;
}

char *rtrim(char *s)
{
    char *back = s + strlen(s);
    while (isspace(*--back))
        ;
    *(back + 1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s));
}

char* remove_dot_after(char* word)
{
    if (word[strlen(word)-1] == '.')
        word[strlen(word)-1] = '\0';
    return word;
}

void remove_stopw_from_dict(JRB dict, char stopw[MAX_NUM_STOPWORDS][MAX_LENGTH_STOPWORD], int num_of_stopw)
{
    JRB node;
    for (int i = 0; i < num_of_stopw; ++i)
    {
        node = jrb_find_str(dict, stopw[i]);
        if (node)
            jrb_delete_node(node);
    }
}