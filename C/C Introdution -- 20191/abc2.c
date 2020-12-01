#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node
{
    struct _data
    {
        char word[20];
        char mean[100];
    } data;
    struct _node *left, *right;
} node;

void insertNode(node** root, char word[], char mean[])
{
    if (*root == NULL)
    {
        *root = (node*)malloc(sizeof(node));
        strcpy((*root)->data.word, word);
        strcpy((*root)->data.mean, mean);
        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else if (strcmp((*root)->data.word, word) < 0)
        insertNode(&(*root)->right, word, mean);
    else if (strcmp((*root)->data.word, word) > 0)
        insertNode(&(*root)->left, word, mean);
}

void readFile(node** root)
{
    FILE *f = fopen("in.txt", "r");
    if(f == NULL)
    {
        printf("Can't open file\n");
        return;
    }

    char c;
    int kt = 0;
    char word[20]= "";
    char mean[100]= "";
    while (1)
    {
        c = fgetc(f);
        if(c == EOF)
        {
            if(word != "")
                insertNode(root, word, mean);
            break;
        }
        else if(c == '\n')
        {
            insertNode(root, word, mean);
            strcpy(word, "");
            strcpy(mean, "");
            kt = 0;
        }
        else if (c == ':')
            kt = 1;
        else
        {
            if(kt == 0)
                strncat(word, &c, 1);
            else
                strncat(mean, &c, 1);
        }
    }
    fclose(f);
}


void PreOrder(node* root){
    if(root != NULL)
    {
        printf("%s:%s\n", root->data.word, root->data.mean);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

void InOrder(node* root){
    if(root != NULL)
    {
        InOrder(root->left);
        printf("%s:%s\n", root->data.word, root->data.mean);
        InOrder(root->right);
    }
}

void PostOrder(node* root){
    if(root != NULL)
    {
        PostOrder(root->left);
        PostOrder(root->right);
        printf("%s:%s\n", root->data.word, root->data.mean);
    }
}

int main()
{
    node* root = NULL;
    readFile(&root);
    //PreOrder(root);
    InOrder(root);
    //PostOrder(root);
    return 0;
}