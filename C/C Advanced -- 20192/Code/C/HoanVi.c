#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n; // Số phần tử của mảng sử dụng
int bool[50]; // Đánh dấu đã sử dụng
int A[50]; // Mảng lưu hoán vị

void show()
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    puts("");
}

void backtrack(int k)
{
    for (int i = 0; i < n; i++)
        //Kiểm tra nếu phần tử chưa được chọn thì sẽ đánh dấu
        if (!bool[i])
        {
            A[k] = i; // Lưu phần tử vào hoán vị
            bool[i] = 1; // Đánh dấu đã dùng
            if (k == n-1) // Kiểm tra nếu đã chứa một hoán vị thì xuất
                show();
            else
                backtrack(k + 1);
            bool[i] = 0;
        }
}
 
int main() {
    memset(bool, 0, sizeof(bool));
    printf("n = "); scanf("%d", &n);
    backtrack(0);
}