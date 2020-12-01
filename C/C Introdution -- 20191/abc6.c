#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct _sinhvien
{
    char username[50];
    char password[50];
    double diem;
} SV;

typedef struct _node
{
    SV data;
    struct _node *left, *right;
} node;

void insertNode(node** root, SV sv)
{
    if (*root == NULL)
    {
        *root = (node*)malloc(sizeof(node));
        (*root)->data = sv;
        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else if (strcmp(sv.username, (*root)->data.username) < 0)
        insertNode (&(*root)->left, sv);
    else if (strcmp(sv.username, (*root)->data.username) > 0)
        insertNode (&(*root)->right, sv);
}

//fscanf fgetc fscanf fgetc fscanf
node* Create_BST(char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
    {
        printf("Can't open file %s\n", file_name);
        exit(-1);
    }

    node* root = NULL;
    char st[100], *s;
    SV sv;
    while (fgets(st, 100, f) != NULL)
    {
        strcpy(sv.username, strtok(st, "\n\t"));
        strcpy(sv.password, strtok(NULL, "\n\t"));
        sv.diem = strtod(strtok(NULL, "\n\t"), &s);
        insertNode(&root, sv);
    }

    fclose(f);
    return root;
}

void update(FILE *f, node* root)
{
    if (root != NULL)
    {
        update(f, root->left);
        fprintf(f, "%s\t%s\t%.1lf\n", root->data.username, root->data.password, root->data.diem);
        update(f, root->right);
    }
}

void update_file(char *file_name, node* root)
{
    FILE *f = fopen(file_name, "w");
    update(f, root);
    fclose(f);
}

node* search(node* root, char* username)
{
    if (root == NULL || strcmp(username, root->data.username) == 0)
       return root;
    if (strcmp(username, root->data.username) < 0)
       return search(root->left, username);
    else
        return search(root->right, username);
}

void user1(node* result)
{
    system("cls");
    printf("User: %s\n", result->data.username);
    puts("1. Xem diem");
    puts("2. Thay doi mat khau");
    puts("3. Luu va dang xuat");

    printf("Diem cua ban: %.1lf\n", result->data.diem);
}

void user2(node* result)
{
    char new_password[50];
    char r_new_password[50];
    int space;
    while (1)
    {
        space = 0;
        printf("New password: "); fflush(stdin); gets(new_password);
        printf("Confirm new password: "); fflush(stdin); gets(r_new_password);
        for (int i = 0; i < strlen(new_password); ++i)
            if (new_password[i] == ' ')
            {
                puts("Mat khau khong chua dau cach\n");
                space = 1;
                break;
            }

        if(strcmp(new_password, r_new_password) == 0 && space == 0)
        {
            strcpy(result->data.password, new_password);
            break;
        }
    }

    system("cls");
    printf("User: %s\n", result->data.username);
    puts("1. Xem diem");
    puts("2. Thay doi mat khau");
    puts("3. Luu va dang xuat");
}

void admin1(node** root)
{
    SV sv;
    puts("Sinh vien moi:");
    while (1)
    {
        printf("Username: "); fflush(stdin); gets(sv.username);
        printf("Password: "); fflush(stdin); gets(sv.password);
        printf("Diem: "); scanf("%lf", &sv.diem);
        for (int i = 0; i < strlen(sv.username); ++i)
            if (sv.username[i] == ' ')
            {
                puts("Ten tai khoan khong chua dau cach\n");
                continue;
            }
        if (search(*root, sv.username) != NULL)
        {
            puts("Tai khoan da ton tai\n");
            continue;
        }
        for (int i = 0; i < strlen(sv.password); ++i)
            if (sv.password[i] == ' ')
            {
                puts("Mat khau khong chua dau cach\n");
                continue;
            }
        break;
    }
    insertNode(root, sv);

    system("cls");
    puts("Admin:");
    puts("1. Them sinh vien");
    puts("2. Hien danh sach sinh vien");
    puts("3. Xoa sinh vien");
    puts("4. Luu va dang xuat");
}

void admin2(node* root)
{
    if (root != NULL)
    {
        admin2(root->left);
        if (strcmp(root->data.username, "Admin") != 0)
            printf("%s\t%s\t%.1lf\n", root->data.username, root->data.password, root->data.diem);
        admin2(root->right);
    }
}

node* minValueNode(node* root)
{
    while (root != NULL && root->left != NULL)
        root = root->left;
    return root;
}

void deleteNode(node** root, char *username)
{
    if (root == NULL) return;

    if (strcmp(username, (*root)->data.username) < 0)
        deleteNode(&(*root)->left, username);

    else if (strcmp(username, (*root)->data.username) > 0)
        deleteNode(&(*root)->right, username);

    else
    {
        // node with only one child or no child
        if ((*root)->left == NULL && (*root)->right == NULL)
            free(*root);
        
        // node with only right
        else if ((*root)->left == NULL)
        {
            node* temp = *root;
            *root = (*root)->right;
            free(temp);
        }

        // node with only left
        else if ((*root)->right == NULL)
        {
            node* temp = *root;
            *root = (*root)->left;
            free(temp);
        }

        // node with two children
        else
        {
            // Get the inorder successor (smallest in the right subtree)
            node* temp = minValueNode((*root)->right);

            // Copy the inorder successor's content to this node
            (*root)->data = temp->data;

            // Delete the inorder successor
            deleteNode(&(*root)->right, temp->data.username);
        }
    }
}

void dangNhap(char *file_name, node** root)
{
    int count = 0;
    char username[50], password[50];
    node *result;

    while (1)
    {
        printf("Username: "); fflush(stdin); gets(username);
        printf("Password: "); fflush(stdin); gets(password);
        result = search(*root, username);

        if (result != NULL && strcmp(password, result->data.password) == 0)
            break;

        if (count < 3)
        {
            count++;
            puts("Sai mat khau hoac tai khoan\n");
        }
        else
            exit(0);
    }

    if (strcmp("Admin", username) != 0)
    {
        int select;
        system("cls");
        printf("User: %s\n", username);
        puts("1. Xem diem");
        puts("2. Thay doi mat khau");
        puts("3. Luu va dang xuat");
        while (1)
        {
            printf(">>> "); scanf("%d", &select);
            switch (select)
            {
            case 1:
                user1(result);
                break;
            case 2:
                user2(result);
                break;
            case 3:
                update_file(file_name, *root);
                return;
            default:
                break;
            }
        }
        
    }
    else
    {
        int select;
        system("cls");
        puts("Admin:");
        puts("1. Them sinh vien");
        puts("2. Hien danh sach sinh vien");
        puts("3. Xoa sinh vien");
        puts("4. Luu va dang xuat");
        while (1)
        {
            printf(">>> "); scanf("%d", &select);
            switch (select)
            {
            case 1:
                admin1(root);
                break;
            case 2:
                admin2(*root);
                break;
            case 3:
                printf("Username can xoa: "); fflush(stdin); gets(username);
                result = search(*root, username);
                if (result == NULL)
                    puts("Ten tai khoan khong ton tai\n");
                else
                {
                    system("cls");
                    puts("Admin:");
                    puts("1. Them sinh vien");
                    puts("2. Hien danh sach sinh vien");
                    puts("3. Xoa sinh vien");
                    puts("4. Luu va dang xuat");
                    printf("%s\t%s\t%.2lf\n", result->data.username, result->data.password, result->data.diem);
                    deleteNode(root, username);
                    puts("Deleted!");
                }
                break;
            case 4:
                update_file(file_name, *root);
                return;
            default:
                break;
            }
        }
    }
}

int main()
{
    char file_name[] = "sinhvien.txt";
    node* root = Create_BST(file_name);
    int select;
    // MENU
    while (1)
    {
        system("cls");
        puts("1. Dang nhap");
        puts("2. Thoat");
        printf(">>> "); scanf("%d", &select);
        if (select == 1)
            dangNhap(file_name, &root);
        else if (select == 2)
            break;
    }puts("END");
    return 0;
}