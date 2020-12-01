/////////////////////////////
// Họ và tên: Lê Ngọc Long //
// MSSV     : 20184137     //
/////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SINHVIEN
{
    char name[50];
    int age;
    double score;
} SV;

typedef struct LIST
{
    SV data;
    struct LIST* next;
} List;
//////////////////////////////////////////////////////////
typedef struct BST_NODE
{
    List* sv;
    struct BST_NODE *left;
    struct BST_NODE *right;
} BNode;

void insertNode(BNode** root, List* sv)
{
    if (*root == NULL)
    {
        *root = (BNode*)malloc(sizeof(BNode));
        (*root)->sv = sv; //
        //X strcpy((*root)->sv->data.name, sv->data.name);
        //? snprintf((*root)->sv->data.name, strlen((*root)->sv->data.name), "%s", sv->data.name);
        //(*root)->sv->data.age = sv->data.age;
        //(*root)->sv->data.score = sv->data.score;
        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else if(sv->data.score <= (*root)->sv->data.score)
        insertNode(&(*root)->left, sv);
    else
        insertNode(&(*root)->right, sv);
}
///////////////////////////////////////////////////////////

List* createList()
{
    List *head = (List*)malloc(sizeof(List));
    printf("Ten: "); fflush(stdin); gets(head->data.name);
    printf("Tuoi: "); scanf("%d", &(head->data.age));
    printf("Thanh tich: "); scanf("%lf", &(head->data.score));
    
    List* Iter = head;
    int s;
    while(1)
    {
        printf("Continue ? (1/0): "); scanf("%d", &s);
        if(s == 0) break;

        List* temp = (List*)malloc(sizeof(List));
        printf("Ten: "); fflush(stdin); gets(temp->data.name);
        printf("Tuoi: "); scanf("%d", &(temp->data.age));
        printf("Thanh tich: "); scanf("%lf", &(temp->data.score));
        Iter->next = temp;
        Iter = Iter->next;
    }
    Iter->next = NULL;
    return head;
}

void add(List **head)
{
    if(*head == NULL)
    {
        *head = createList();
        return;
    }

    List* Iter = *head;
    for(;Iter->next != NULL; Iter = Iter->next);
    int s;
    do
    {
        List* temp = (List*)malloc(sizeof(List));
        printf("Ten: "); fflush(stdin); gets(temp->data.name);
        printf("Tuoi: "); scanf("%d", &(temp->data.age));
        printf("Thanh tich: "); scanf("%lf", &(temp->data.score));
        Iter->next = temp;
        Iter = Iter->next;

        printf("Continue ? (1/0): "); scanf("%d", &s);
    } while(s != 0);

    Iter->next = NULL;
}

void deleteANode(List** head, List* node)
{
    if(node == *head)
    {
        List* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    
    List* Iter = *head;
    while(Iter->next != NULL)
    {
        if(Iter->next == node)
        {
            List* temp = Iter->next;
            Iter->next = Iter->next->next;
            free(temp);
            return;
        }
    }
}

void deleteList(List **head)
{
    while(*head != NULL)
    {
        List* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void show(List* head)
{
    while(head != NULL)
    {
        printf("%s - %d - %.2lf\n", head->data.name, head->data.age, head->data.score);
        head = head->next;
    }
}

int minAge(List* head)
{
    int min = 100;
    while(head != NULL)
    {
        if(head->data.age < min)
            min = head->data.age;
        head = head->next;
    }
    return min;
}

int KT(List* head, List* node)
{
    if(node->data.age == minAge(head))
        return 1;

    int n = 0;
    List* Iter = head;
    while(Iter != NULL)
    {
        if(node->data.age > Iter->data.age)
            n++;
        Iter = Iter->next;
    }

    int count = 0;
    Iter = head;
    while(Iter != NULL)
    {
        if(Iter->data.age < node->data.age && Iter->data.score < node->data.score)
            count++;
        Iter = Iter->next;
    }

    if(count > n/2)
        return 1;
    else return 0;
}

void DSTangQua(List* head)
{
    List* Iter = head;
    while(Iter != NULL)
    {
        if(KT(head, Iter) == 1)
            printf("%s - %.2lf\n", Iter->data.name, Iter->data.score);
        Iter = Iter->next;
    }
}

void TREE(BNode** root, List* head)
{
    List* Iter = head;
    while(Iter != NULL)
    {
        insertNode(root, Iter);
        Iter = Iter->next;
    }
}

void InOrder(BNode* root, double p){
    if(root != NULL)
    {
        InOrder(root->left, p);
        if(root->sv->data.score == p)
            printf("%s - %d - %.2lf\n", root->sv->data.name, root->sv->data.age, root->sv->data.score);
        InOrder(root->right, p);
    }
}

int main()
{
    BNode* root = NULL;
    printf("Nhap danh sach SV:\n");
    List* LList = createList();
    //show(LList);

    TREE(&root, LList);
    //double p;
    //printf("Nhap p: "); scanf("%lf", &p);
    InOrder(root, 10.00);
    deleteList(&LList);
    return 0;
}
