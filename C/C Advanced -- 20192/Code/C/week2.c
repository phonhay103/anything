#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int BinarySearch(void *arr, size_t num, size_t size, int l, int r, void *x, int (*compare)(void* a, void* b))
{
    if (r < l)
        return -1;
    int mid = l + (r - l) / 2;
    int result = compare(x, (char*)arr+size*mid);
    if (result == 0)
        return mid;
    else if (result < 0)
        return BinarySearch(arr, num, size, l, mid-1, x, compare);
    else
        return BinarySearch(arr, num, size, mid+1, r, x, compare);
}

int LinearSearch(void *arr, size_t num, size_t size, void *x, int (*compare)(void* a, void* b))
{
    for (int i = 0; i < num; ++i)
    {
        if (compare(x, (char*)arr + i*size) == 0)
            return i;
    }
    return -1;
}

int int_compare(void* a, void* b)
{
    int x = *((int*)a);
    int y = *((int*)b);
    if (x == y)
        return 0;
    else if (x < y)
        return -1;
    else return 1;
}

int float_compare(void* a, void* b)
{
    float x = *((float*)a);
    float y = *((float*)b);
    if (x == y)
        return 0;
    else if (x < y)
        return -1;
    else return 1;
}

void show(void* const arr, size_t num, size_t size, int type)
{
    switch (type)
    {
    case 1:
        for (int i = 0; i < num; ++i)
        printf("%d ", *((int*)arr+i));
        printf("\n");
        break;
    case 2:
        for (int i = 0; i < num; ++i)
        printf("%d ", *((float*)arr+i));
        printf("\n");
        break;
    default:
        break;
    }
}

void _memcpy(void *dest, const void *src, size_t size)
{
    char *cdest = (char*)dest;
    char *csrc = (char*)src;

    for (int i = 0; i < size; ++i)
        cdest[i] = csrc[i];
}

void swap(void *a, void *b, size_t size)
{
    char *temp = (char*)malloc(sizeof(char)*size);
    char *result1 = (char*)a, *result2 = (char*)b;
    //_memcpy(t, r1, size);
    //_memcpy(r1, r2, size);
    //_memcpy(r2, t, size);
    for (int i = 0; i < size; ++i)
    {
        temp[i] = result1[i];
        result1[i] = result2[i];
        result2[i] = temp[i];
    }

    /*
    void *temp = malloc(sizeof(char)*size);
    void *result1 = a, *result2 = b;
    for (int i = 0; i < size; ++i)
    {
        *((char*)temp + i) = *((char*)result1 + i);
        *((char*)result1 + i) = *((char*)result2 + i);
        *((char*)result2 + i) = *((char*)temp + i);
    }
    */
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


int main()
{
    int n = 10;
    int x, y;
    int *A = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; ++i)
        A[i] = rand()%500;
    
    // Search
    // show(A, n, sizeof(A[0]), 1);
    // int index = BinarySearch(A, n, sizeof(A[0]), 0, n, &x, int_compare);
    // int index = LinearSearch(A, n, sizeof(A[0]), &x, int_compare);
    // show(A, n, sizeof(A[0]), 1);
    
    // Qsort 3-way
    show(A, n, sizeof(A[0]), 1);
    _qsort(A, n, sizeof(A[0]), 0, n-1, int_compare);
    show(A, n, sizeof(A[0]), 1);
    
    return 0;
}