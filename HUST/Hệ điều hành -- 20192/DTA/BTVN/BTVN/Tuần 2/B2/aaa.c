#include <stdio.h>
#include <string.h>

int main()
{
    char st[100];
    FILE *f = fopen("aa.txt", "r");
    fgets(st, 10, f);
    fclose(f);

    int d;
    sscanf(st, "%d", &d);

    //int *p = (int*)d;
    //printf("%d - %x\n", *p, p);
    char *p = (char*) 0x61fffe;
    printf("%c - %x\n", *p, p);

    printf("Press any key");
    getchar();
    return 0;
}