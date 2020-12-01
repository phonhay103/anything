#include <stdio.h>
#include <string.h>
#include <windows.h>

int main()
{
    int i = 333;
    char st[100];
    sprintf(st, "%d", &i);
    FILE *f = fopen("aa.txt", "w");
    fputs(st, f);
    fclose(f);

    printf("%d - %x\n", i, &i);
    printf("Press any key");
    getchar();
    return 0;
}