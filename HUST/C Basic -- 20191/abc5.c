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

void Create_BST(FILE *f, node **root)
{
    _data data;
    while(fscanf(f, "%s", data.word) == 1)
    {
        fgetc(f);
        fgets(data.mean, 100, f);
        data.mean[strlen(data.mean)-1] = '\0';
        insertNode(root, data);
    }
}

void inorder(node* root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%s\t%s\n", root->data.word, root->data.mean);
        inorder(root->right);
    }
}

void update(FILE *f, node* root)
{
    if (root != NULL)
    {
        update(f, root->left);
        fprintf(f, "%s\t%s\n", root->data.word, root->data.mean);
        update(f, root->right);
    }
}

node* search(node* root, char* word)
{
    if (root == NULL || strcmp(root->data.word, word) == 0)
       return root;
    if (strcmp(root->data.word, word) > 0)
       return search(root->left, word);
    else
        return search(root->right, word);
}

void translate(node** root)
{
    char st[20], split[20][20], trans[20][20], *word;
    int n = 0;
    printf("Input string: "); gets(st);

    printf("=> Split: \n");
    word = strtok(st, " ");
    while(word != NULL)
    {
        for (int i = 0; i < strlen(word); ++i)
            word[i] = tolower(word[i]);
        puts(word);
        strcpy(split[n], word);
        word = strtok(NULL, " ");
        n -= -1;
    }

    printf("=> Translate: \n");
    for (int i = 0; i < n; ++i)
    {
        node* temp = search(*root, split[i]);
        if (temp == NULL)
        {
            printf("Thieu tu \"%s\": ", split[i]);
            gets(trans[i]);

            for (int j = 0; j < strlen(trans[i]); ++j)
                trans[i][j] = tolower(trans[i][j]);
            _data data;
            strcpy(data.word, split[i]);
            strcpy(data.mean, trans[i]);
            insertNode(root, data);
        }
        else
            strcpy(trans[i], temp->data.mean);
    }

    for (int i = 0; i < n; ++i)
        printf("%s ", trans[i]);
}

int main()
{
    // Init
    node* root = NULL;
    FILE *f;
    
    // Read file
    f = fopen("data.txt", "r");
    if (f == NULL)
    {
        printf("Can't open file data.txt\n");
        return -1;
    }
    Create_BST(f, &root);

    inorder(root);

    translate(&root);

    // Update file
    f = fopen("data.txt", "w");
    update(f, root);
    fclose(f);
    return 0;
}