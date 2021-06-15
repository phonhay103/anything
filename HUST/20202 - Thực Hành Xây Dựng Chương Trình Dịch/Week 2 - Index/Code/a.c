#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// char stopw_list[30][20]; // Lưu stop words
// int stopw_length = 0; // Số lượng stop words
// void build_stopw_list()
// {
//     FILE *f = fopen("stopw.txt", "r");

//     stopw_length = 0;
//     while (fscanf(f, "%s", stopw_list[stopw_length]) != EOF)
//          stopw_length += 1;
//     fclose(f);
// }

void build_stopw_list()
{
    FILE *f = fopen("vanban.txt", "r");
    char word[20];
    char temp[20];
    int n;

    while (fscanf(f, "%s", word) != EOF) // Duyệt từng từ - từ chỉ chứa: "a-z A-Z . - "
    {
        // Kiểm tra từ hợp lệ: Loại bỏ kí tự dư thừa và lấy phần còn lại (nếu rỗng thì bỏ qua)
        n = 0;
        for (int i = 0; i <= strlen(word); ++i)
            if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z') || word[i] == '.' || word[i] == '-')
                temp[n++] = word[i];
        temp[n] = '\0';
        if (n == 0 || strcmp(temp, ".") == 0 || strcmp(temp, "-") == 0)
            continue;
        puts(temp);

        // Kiểm tra từ stop word

        // Kiểm tra tên riêng

        // Xóa dấu chấm dư thừa ở cuối
    }
    fclose(f);
}

int main()
{
    build_stopw_list();
    return 0;
}