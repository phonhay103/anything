#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _data
{
    char word[20];
    char mean[100];
} _data;

typedef struct _node
{
    _data data;
    struct _node *left, *right;
} node;

void insertNode(node** root, _data data)
{
    if (*root == NULL)
    {
        *root = (node*)malloc(sizeof(node));
        (*root)->data = data;
        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else if (strcmp((*root)->data.word, data.word) < 0)
        insertNode(&(*root)->right, data);
    else if (strcmp((*root)->data.word, data.word) > 0)
        insertNode(&(*root)->left, data);
}

node* Create_BST(char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
    {
        printf("Khong tim thay file %s\n", file_name);
        exit(-1);
    }

    node* root = NULL;
    _data data;
    while(fscanf(f, "%s", data.word) == 1)
    {
        fgetc(f);
        fscanf(f, "%s\n", data.mean);
        printf("- %s %s\n", data.word, data.mean);
        insertNode(&root, data);
    }

    fclose(f);
    return root;
}

void preorder(node* root)
{
    if (root != NULL)
    {
        printf("- %s %s\n", root->data.word, root->data.mean);
        preorder(root->left);
        preorder(root->right);
    }
}

void add_word(node** root)
{
    _data data;
    printf("Nhap tu: "); fflush(stdin); gets(data.word);
    printf("Nhap nghia: "); fflush(stdin); gets(data.mean);
    for (int i = 0; i < strlen(data.word); ++i)
        if (data.word[i] == ' ') data.word[i] = '_';
    for (int i = 0; i < strlen(data.mean); ++i)
        if (data.mean[i] == ' ') data.mean[i] = '_';
    insertNode(root, data);
}

node* search(node* root, char* word)
{
    if (root == NULL)
        return NULL;
    
    printf ("- %s %s\n", root->data.word, root->data.mean);
    if (strcmp(word, root->data.word) == 0)
        return root;
    else if (strcmp(word, root->data.word) < 0)
        return search(root->left, word);
    else
        return search(root->right, word);
}

void translate(node* root)
{
    char word[50];
    //printf("Nhap tu can tra: "); fflush(stdin); scanf("%s", word);
    ///*
    printf("Nhap tu can tra: "); fflush(stdin); gets(word);
    for (int i = 0; i < strlen(word); ++i)
        if (word[i] == ' ') word[i] = '_';
    //*/
    if (search(root, word) == NULL)
        printf("Khong tim thay tu can tra\n"); 
}

void update(FILE *f, node* root)
{
    if (root != NULL)
    {
        fprintf(f, "%s %s\n", root->data.word, root->data.mean);
        update(f, root->left);
        update(f, root->right);
    }
}

void update_file(char *file_name, node* root)
{
    FILE *f = fopen(file_name, "w");
    update(f, root);
    fclose(f);
}

void delete_tree(node** root)
{
    while (*root != NULL)
    {
        node* temp = *root;
        if ((*root)->left != NULL)
        {
            *root = (*root)->left;
            free(temp);
        }
        else if ((*root)->right != NULL)
        {
            *root = (*root)->right;
            free(temp);
        }
        else
        {
            *root = NULL;
            free(temp);
        }
        
    }
}

int main(int argc, char *argv[])
{
    char *file_name = argv[1];
    node* root = Create_BST(file_name);
    
    puts("1. Hien thi tu dien");
    puts("2. Them 1 tu vao tu dien");
    puts("3. Tra tu dien");
    puts("4. Luu va thoat");
    while (1)
    {
        int select;
        printf(">>> "); fflush(stdin); scanf("%d", &select);
        switch (select)
        {
        case 1:
            preorder(root);
            break;
        case 2:
            add_word(&root);
            break;
        case 3:
            translate(root);
            break;
        case 4:
            update_file(file_name, root);
            delete_tree(&root);
            return 0;
        default:
            break;
        }
    }
    return 0;
}
