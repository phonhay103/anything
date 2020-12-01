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
/////////////////////////////////
typedef struct _QNode
{
    node* BT_node;
    struct _QNode* next;
} QNode;

typedef struct _queue
{
    QNode* front;
    QNode* rear;
} queue;

void initialize(queue *q)
{
    q->front = NULL;
    q->rear = NULL;
}

int isEmtpy(queue *q)
{
    return q->rear == NULL;
}

void enqueue(queue *q, node* BT_node)
{
    QNode* temp = (QNode*)malloc(sizeof(QNode));
    temp->BT_node = BT_node;
    temp->next = NULL;
    if(isEmtpy(q))
        q->front = q->rear = temp;
    else
    {
        q->rear->next = temp;
        q->rear = temp;
    }
}

void dequeue(queue *q)
{
    if (q->front == NULL)
        return;
    QNode *temp = q->front;
    q->front = q->front->next;
    if(q->front == NULL)
        q->rear = NULL;
    free(temp);
}

node* top(queue *q)
{
    return q->front->BT_node;
}
/////////////////////////////////////////////////////
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
    char word[20]="";
    char mean[100]="";
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

void readFile2(node **root)
{
    FILE *f = fopen("in.txt", "r");
    if(f == NULL)
    {
        printf("Can't open file\n");
        return;
    }
    
    char st[100];
    while(fgets(st, 100, f) != NULL)
    {
        char *word = strtok(st, ":");
        char *mean = strtok(NULL, " ");
        insertNode(root, word, mean);
    }
}

void BreadthFirstSearch(node* root)
{
    queue *q = (queue*)malloc(sizeof(queue));
    initialize(q);
    enqueue(q, root);
    while (!isEmtpy(q))
    {
        root = top(q);
        dequeue(q);
        printf("%s:%s\n", root->data.word, root->data.mean);
        if (root->left != NULL) enqueue(q, root->left);
        if (root->right != NULL) enqueue(q, root->right);
    }
    free(q);
}

int main()
{
    node* root = NULL;
    readFile2(&root);
    BreadthFirstSearch(root);
    return 0;
}