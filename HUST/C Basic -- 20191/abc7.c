#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char ten_mon[50];
    int so_luong;
    double gia_tien;
} Menu;

typedef struct request
{
    int ID;
    int order[50];
    long total;
    struct request *next;
} Request;

void create_menu(char *file_name, Menu menu[], int *n)
{
    FILE *f = fopen(file_name, "r");
    fscanf(f, "%d\n", n);
    int i = 0;
    char st[50];
    while (fgets(st, 50, f) != NULL)
    {
        strtok(st, " \n");
        strcpy(menu[i].ten_mon, strtok(NULL, " \n"));
        menu[i].so_luong = atoi(strtok(NULL, " \n"));
        menu[i].gia_tien = atof(strtok(NULL, " \n"));
        i++;
    }
}

void show_menu(Menu menu[], int n)
{
    system("cls");
    for (int i = 0; i < n; ++i)
        if (menu[i].so_luong > 0)
            printf("%d %s %d %.0lf\n", i+1, menu[i].ten_mon, menu[i].so_luong, menu[i].gia_tien);
}

void order(Menu menu[], int n, Request** List, char *file_name)
{
    int A[50];
    puts("Nhap so luong:");
    for (int i = 0; i < n; ++i)
    {
        if (menu[i].so_luong == 0)
        {
            A[i] = 0;
            continue;
        }
        do
        {
            
            printf("%d %s (%.0lf): ", i+1, menu[i].ten_mon, menu[i].gia_tien); scanf("%d", &A[i]);
        } while (A[i] < 0);
    }

    for (int i = 0; i < n; ++i)
        if (A[i] > menu[i].so_luong)
        {
            printf("Xin loi, nha hang khong con du suat an dap ung yeu cau cua quy khach.");
            return;
        }
    
    Request *temp = (Request*)malloc(sizeof(Request));
    temp->total = 0;
    for (int i = 0; i < n; ++i)
    {
        temp->order[i] = A[i];
        temp->total += A[i]*menu[i].gia_tien;
    }

    printf("=> Tong so tien phai tra la: %ld\n", temp->total);

    if (*List == NULL)
    {
        temp->ID = 1;
        temp->next = NULL;
    }
    else
    {
        temp->ID = (*List)->ID + 1;
        temp->next = *List;
    }
    *List = temp;

    FILE *f = fopen(file_name, "w");
    fprintf(f, "%d\n", n);
    for (int i = 0; i < n; ++i)
        fprintf(f, "%d %s %d %.0lf\n", i+1, menu[i].ten_mon, menu[i].so_luong - A[i], menu[i].gia_tien);
    fclose(f);
}

void show_order(Request *List, Menu menu[], int n)
{
    while (List != NULL)
    {
        printf("Don hang so %d\n", List->ID);
        printf("Mon da chon\tSo Luong\tThanh tien\n");
        for (int i = 0; i < n; ++i)
            if (List->order[i] != 0)
                printf("%s\t%d\t%.0lf\n", menu[i].ten_mon, List->order[i], menu[i].gia_tien * List->order[i]);
        printf("Tong hoa don thanh toan: %ld\n", List->total);
        List = List->next;
    }
}

void favorite(Request *List, Menu menu[], int n)
{
    int A[50];
    while (List != NULL)
    {
        for (int i = 0; i < n; ++i)
            A[i] += List->order[i];
        List = List->next;
    }

    int S_max = A[0], max = 0;
    for (int i = 1; i < n;  ++i)
        if (A[i] > S_max)
        {
            S_max = A[i];
            max = i;
        }
    printf("Mon an ua chuong nhat la: %s - %d\n", menu[max].ten_mon, S_max);
}

int main()
{
    char file_name[] = "thucdontheongay.txt";
    int n;
    Menu menu[50];
    Request *List = NULL;
    int select;

    puts("MENU:");
    puts("1. Danh sach mon an hom nay");
    puts("2. Nhan Order");
    puts("3. Thong tin toan bo order");
    puts("4. Mon an duoc ua chuong nhat");
    puts("5. Thoat");
    while (1)
    {
        create_menu(file_name, menu, &n);
        printf(">>> "); scanf("%d", &select);
        switch (select)
        {
        case 1:
            show_menu(menu, n);
            break;
        case 2:
            order(menu, n, &List, file_name);
            break;
        case 3:
            show_order(List, menu, n);
            break;
        case 4:
            favorite(List, menu, n);
            break;
        case 5:
            return 0;
        default:
            system("cls");
            break;
        }
    }
    return 0;
}