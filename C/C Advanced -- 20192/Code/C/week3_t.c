#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jval.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
void swap(void *a, void *b, size_t size)
{
    char *temp = (char*)malloc(sizeof(char)*size);
    char *result1 = (char*)a;
    char *result2 = (char*)b;
    for (int i = 0; i < size; ++i)
    {
        temp[i] = result1[i];
        result1[i] = result2[i];
        result2[i] = temp[i];
    }
}

void exch(void *arr, size_t size, int i, int j)
{
    swap((char*)arr+i*size, (char*)arr+j*size, size);
}

void _qsort(void *arr, size_t num, size_t size, int l, int r, int (*compare)(void* a, void* b))
{
    if (r <= l)
        return;

    int i = l-1, j = r;
    int p = l-1, q = r;
    void *pivot = (char*)arr + r*size;

    while (1)
    {
        while ((++i <= r) && (compare((char*)arr+i*size, pivot) < 0));
        while (compare((char*)arr+(--j)*size, pivot) > 0)
            if (j == l) break;
        if (i >= j)
            break;
        exch(arr, size, i, j);
        if (compare((char*)arr + i*size, pivot) == 0)
        {
            p++;
            exch(arr, size, p, i);
        }
        if (compare((char*)arr + j*size, pivot) == 0)
        {
            q--;
            exch(arr, size, j, q);
        }
    }

    exch(arr, size, i, r);
    j = i-1;
    for (int k = l; k <= p; k++, j--)
        exch(arr, size, k, j);
    i = i+1;
    for (int k = r-1; k >= q; k--, i++)
        exch(arr, size, i, k);

    _qsort(arr, num, size, l, j, compare);
    _qsort(arr, num, size, i, r, compare);
}
/////////////////////////////////////////////////////////////////////////////////////////////////

void show_jval(Jval* arr, size_t num, int type)
{
    switch (type)
    {
    case 1:
        for (int i = 0; i < num; ++i)
        printf("%d ", jval_i(arr[i]));
        break;
    default:
        break;
    }
    printf("\n");
}

int compare_jval_i(void* a, void* b)
{
    Jval x = *((Jval*)a);
    Jval y = *((Jval*)b);
    if (jval_i(x) == jval_i(y))
        return 0;
    else if (jval_i(x) < jval_i(y))
        return -1;
    else return 1;
}

Jval* new_jval_array_i(size_t num)
{
    Jval *A = (Jval*)malloc(num*sizeof(Jval));
    for (int i = 0; i < num; ++i)
        A[i] = new_jval_i(rand()%333);
    return A;
}

int main()
{
    int n = 10;
    Jval *A = new_jval_array_i(n);
    show_jval(A, n, 1);
    _qsort(A, n, sizeof(A[0]), 0, n-1, compare_jval_i);
    show_jval(A, n, 1);
    
    return 0;
}