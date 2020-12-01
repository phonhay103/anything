#include <stdio.h>
#include <string.h>
#include "jrb.h"

void addStudent(JRB SV, char *name, double score);
void show(JRB SV);
JRB searchByName(JRB SV, char *name);
void changeScore(JRB SV, char *name, double score);
void searchByScore(JRB SV, double score);
void sortByScore(JRB SV);
void deleteStudent(JRB SV, char *name);
void deleteAll(JRB SV);

int main()
{
    JRB SV = make_jrb();
    addStudent(SV, "A", 5.5);
    addStudent(SV, "B", 6.5);
    addStudent(SV, "G", 6.5);
    addStudent(SV, "U", 7.5);
    addStudent(SV, "X", 9.5);
    addStudent(SV, "H", 3.5);
    addStudent(SV, "A", 2.5);
    addStudent(SV, "Z", 6.5);
    show(SV);

    // JRB rs = searchByName(SV, "A");
    // if (rs)
    //     printf("\n%s - %.2lf\n", jval_s(rs->key), jval_d(rs->val));
    // else
    //     printf("\nNot found\n");

    // changeScore(SV, "H", 4.0);
    // show(SV);

    // printf("\nScore = 6.5: \n");
    // searchByScore(SV, 6.5);

    // printf("\nSort by score: \n");
    // sortByScore(SV);

    // deleteStudent(SV, "A");
    // show(SV);

    deleteAll(SV);
    return 0;
}

void addStudent(JRB SV, char *name, double score)
{
    jrb_insert_str(SV, name, new_jval_d(score));
}

void show(JRB SV)
{
    JRB iter;
    jrb_traverse(iter, SV)
    {
        printf("%s - %.2lf\n", jval_s(iter->key), jval_d(iter->val));
    }
}

JRB searchByName(JRB SV, char *name)
{
    return jrb_find_str(SV, name);
}

void changeScore(JRB SV, char *name, double score)
{
    JRB rs = jrb_find_str(SV, name);
    if (rs)
        rs->val = new_jval_d(score);
}

void searchByScore(JRB SV, double score)
{
    JRB iter;
    jrb_traverse(iter, SV)
    {
        if (jval_d(iter->val) == score)
            printf("%s - %.2lf\n", jval_s(iter->key), jval_d(iter->val));
    }
}

void sortByScore(JRB SV)
{
    JRB iter;
    JRB A = make_jrb();
    jrb_traverse(iter, SV)
    {
        jrb_insert_dbl(A, jval_d(iter->val), new_jval_s(jval_s(iter->key)));
    }
    jrb_traverse(iter, A)
    {
        printf("%s - %.2lf\n", jval_s(iter->val), jval_d(iter->key));
    }
    jrb_free_tree(A);
}

void deleteStudent(JRB SV, char *name)
{
    JRB rs = jrb_find_str(SV, name);
    if (rs)
        jrb_delete_node(rs);
}

void deleteAll(JRB SV)
{
    jrb_free_tree(SV);
}