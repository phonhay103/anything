#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _student{
	struct _data 
	{
		char mssv[10];
		char name[30];
		float toan;
		float van;
		float anh;
	} data;
	struct _student* next;
} student;

student* createNode()
{
	student* temp = (student*)malloc(sizeof(student));
	printf("MSSV: "); fflush(stdin); gets(temp->data.mssv);
	printf("Name: "); fflush(stdin); gets(temp->data.name);
	printf("Toan: "); scanf("%f", &(temp->data.toan));
	printf("Van: "); scanf("%f", &(temp->data.van));
	printf("Anh: "); scanf("%f", &(temp->data.anh));
	return temp;
}

void addStudent(student** s)
{
	student* iter;
	char ch;

	if(*s == NULL)
	{
		*s = createNode();
		printf("Continue ? (y/n): "); fflush(stdin); ch = getchar();
		if(ch == 'n')
		{
			(*s)->next = NULL;
			return;
		}
		iter = *s;
	}
	else
	{
		iter = *s;
		while(iter->next != NULL)
		iter = iter->next;
	}

	while(1)
	{
		iter->next = createNode();
		iter = iter->next;

		printf("Continue ? (y/n): "); fflush(stdin); ch = getchar();
		if(ch == 'n')
		{
			iter->next = NULL;
			break;
		}
	}
}

void showStudent(student* s)
{
	if(s != NULL)
		printf("MSSV\tName\tToan\tVan\tAnh\n");
	else return;
	while(s != NULL)
	{
		printf("%s\t%s\t%.2lf\t%.2lf\t%.2lf\n", s->data.mssv, s->data.name, s->data.toan, s->data.van, s->data.anh);
		s = s->next;
	}
}

void searchByName(student* s)
{
	char name[30];
	printf("Name: "); fflush(stdin); gets(name);
	while(s != NULL)
	{
		if(strcmp(s->data.name, name) == 0)
		{
			printf("%s\t%s\t%.2lf\t%.2lf\t%.2lf\n", s->data.mssv, s->data.name, s->data.toan, s->data.van, s->data.anh);
			return;
		}
		s = s->next;
	}
	printf("Not Found!\n");
}

void sortByScore(student* s)
{
	
}

void writeFileText(student* s)
{
	FILE *f = fopen("out.txt", "w");
	while(s != NULL)
	{
		fprintf(f, "%s\t%s\t%.2lf\t%.2lf\t%.2lf\n", s->data.mssv, s->data.name, s->data.toan, s->data.van, s->data.anh);
		s = s->next;
	}
	fclose(f);
}

int main()
{
    student* s = NULL;
	int choice;

    while(1)
	{
		puts("_________________Menu_____________________");
		puts("press 1 them sv vao ds");
		puts("press 2 in ra ds sv");
		puts("press 3 tim kiem theo ten");
		puts("press 4 sap xep sv theo diem");
		puts("press 5 ghi vao 1 file");
		printf("Moi chon: "); scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				addStudent(&s);
				break;
			case 2:
				showStudent(s);
				break;
			case 3:
				searchByName(s);
				break;
			case 4:
				sortByScore(s);
				break;
			case 5:
				writeFileText(s);
				break;
			default:
				return 0;
		}
	}
    return 0;
}