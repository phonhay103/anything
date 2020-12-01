#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* createArray(long n)
{
    int *A = (int*)malloc(sizeof(int)*n);
    for (long i = 0; i < n; ++i)
    {
        A[i] = rand()%100;
    }
    return A;
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// 3-way partition based quick sort 
void quicksort3p(int* A, int left, int right)
{
    if (right <= left)
        return;
    
    int i = left-1, j = right;
    int p = left-1, q = right;
    int pivot = A[right];
    while (1)
    {
        // From left, find the first element greater than
        // or equal to pivot. This loop will definitely terminate
        // as pivot is last element
        while (A[++i] < pivot);

        // From right, find the first element smaller than or 
        // equal to pivot
        while (A[--j] > pivot)
            if (j == left)
                break;

        // If i and j cross, then we are done
        if (i >= j)
            break;

        // Swap, so that smaller goes on left greater goes on right
        swap(&A[i], &A[j]);

        // Move all same left occurrence of pivot to beginning of
        // array and keep count using p
        if (A[i] == pivot)
        {
            p++;
            swap(&A[p], &A[i]);
        }
        
        // Move all same right occurrence of pivot to end of array
        // and keep count using q
        if (A[j] == pivot)
        {
            q--;
            swap(&A[j], &A[q]);
        }
    }

    // Move pivot element to its correct index
    swap(&A[i], &A[right]);

    // Move all left same occurrences from beginning
    // to adjacent to A[i]
    j = i-1;
    for (int k = left; k <= p; k++, j--) 
        swap(&A[k], &A[j]);

    // Move all right same occurrences from end
    // to adjacent to A[i]
    i = i+1;
    for (int k = right-1; k >= q; k--, i++)
        swap(&A[i], &A[k]);


    quicksort3p(A, left, j); 
    quicksort3p(A, i, right); 
}

void printArray(int *A, int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d ", A[i]);
    printf("\n");
}

void quicksort(int A[], int low, int high) 
{ 
    if (low >= high) return;

    int pivot = A[high];
    int i = (low - 1);
  
    for (int j = low; j <= high- 1; j++) 
    {
        if (A[j] < pivot)
        {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[high]);

    quicksort(A, low, i);
    quicksort(A, i+2, high);
}
/*
int* copy(int *arr, int n)
{
    int *T = (int*)malloc(sizeof(int)*n);
    for (int i = 0; i < n; ++i)
        T[i] = arr[i];
    return T;
}
*/

int main()
{
    //srand(time(0));
    clock_t start, end;
    long n = 2000000;

    start = clock();
    quicksort(createArray(n), 0, n-1);
    end = clock();
    printf("Thoi gian chay: %lfs\n", (double)(end-start)/CLOCKS_PER_SEC);

    start = clock();
    quicksort3p(createArray(n), 0, n-1);
    end = clock();
    printf("Thoi gian chay: %lfs\n", (double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}