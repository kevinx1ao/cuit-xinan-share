 
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
 
# include <math.h>
# include <conio.h>
 
# define eps 1;
 
typedef struct
{
    char name[50];
    int num;
    int Chinese;
    int Math;
    int English;
    int sum;
}Node;
 
Node student[1000];
 
int n;
 
char text[50];
 
int cmp(const void *a, const void *b)
{
    return (*(Node *)b).sum > (*(Node *)a).sum?1:-1;
}
 
int cmpnum(const void *a, const void *b)
{
    return (*(Node *)a).num > (*(Node *)b).num?1:-1;
}
 
void showstudent()
{
	void menu();
    int i;
	printf(" \t姓名\t学号\t语文\t数学\t英语\t总分\n");
	for(i=0;i<n;i++)
	{
		printf("\t%s\t%d\t%d\t%d\t%d\t%d\n",student[i].name,student[i].num,student[i].Chinese,student[i].Math,student[i].English,student[i].sum);
	}
    getch();
    menu();
}
 
void sortnum()
{
	void menu();
    int i,j,k;
	char a[55];
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(student[j].num>student[j+1].num)
			{
				k=student[j].num;
				student[j].num=student[j+1].num;
				student[j+1].num=k;
				k=student[j].Chinese;
				student[j].Chinese=student[j+1].Chinese;
				student[j+1].Chinese=k;
				k=student[j].Math;
				student[j].Math=student[j+1].Math;
				student[j+1].Math=k;
				k=student[j].English;
				student[j].English=student[j+1].English;
				student[j+1].English=k;
				k=student[j].sum;
				student[j].sum=student[j+1].sum;
				student[j+1].sum=k;
				strcpy(a,student[j].name);
				strcpy(student[j].name,student[j+1].name);
				strcpy(student[j+1].name,a);
			}
		}
	}
	showstudent();
    getch();
    menu();
}
 
void sortsum()
{
	void menu();
    qsort(student, n, sizeof(Node), cmp);
    showstudent();
    getch();
    menu();
}
 
void searchnum(int number)
{
	void menu();
    int min = 0, max = n-1, mid;
    bool escape = false;
    qsort(student, n, sizeof(Node), cmpnum);
    while(min <= max)
    {
        mid = (min + max) / 2;
        if(student[mid].num > number)
        {
            max = mid - eps;
        }
        else if(student[mid].num < number)
        {
            min = mid + eps;
        }
        else
        {
            escape = true;
            printf("\t姓名\t学号\t语文\t数学\t英语\t总分\n");
            printf("\t%s\t%d\t%d\t%d\t%d\t%d\n", student[mid].name, student[mid].num, student[mid].Chinese, student[mid].Math, student[mid].English, student[mid].sum);
            break;
        }
    }
    if(!escape)
    {
        printf("\t查无此人");
    }
    getch();
    menu();
}
 
void searchname()
{ 
	void menu();
	int i;
	for(i=0;i<n;i++)
	{
		if(strcmp(text,student[i].name)==0)
		{
			printf("\t姓名\t学号\t语文\t数学\t英语\t总分\n");
            printf("\t%s\t%d\t%d\t%d\t%d\t%d\n", student[i].name, student[i].num, student[i].Chinese, student[i].Math, student[i].English, student[i].sum);
			break;
		}
	}
	if(i>=n)
	{
		printf("\t查无此人\n");
	}
    getch();
    menu();
}
 
void save()
{
	void menu();
    FILE *fp;
	fp=fopen("4.txt","w");
	int i;
	fprintf(fp, "\t姓名\t学号\t语文\t数学\t英语\t总分\n");
	for(i=0;i<n;i++)
	{
		if(student[i].Chinese<60||student[i].Math<60||student[i].English<60)
		{
		    printf("\t%s\t%d\t%d\t%d\t%d\n",student[i].name,student[i].num,student[i].Chinese,student[i].Math,student[i].English);
			fprintf(fp,"\t%s\t%d\t%d\t%d\t%d\n",student[i].name,student[i].num,student[i].Chinese,student[i].Math,student[i].English);
		}
	}
	printf("\n");
	printf("┏━━━━┓\n");
    printf("┃保存成功┃\n");
    printf("┗━━━━┛\n");
    getch();
    menu();
}
 
void menu()
{
    int choice;
    system("cls");
    printf("                    菜单\n");
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃                 0.退出                                     ┃\n");
    printf("┃                 1.显示学生信息                             ┃\n");
    printf("┃                 2.显示按学号排序后的学生信息               ┃\n");
    printf("┃                 3.显示按总分排序后的学生信息               ┃\n");
    printf("┃                 4.按学号查学生各科分数和总分               ┃\n");
    printf("┃                 5.按姓名查学生各科分数和总分               ┃\n");
    printf("┃                 6.抽取出三科成绩中有补考的学生并保存       ┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("                    选择代码（0，1，2，3，4，5，6）： ");
    scanf("%d", &choice);
    switch(choice)
    {
        case 0:
        {
            system("cls");
            printf("谢谢使用!\n");
            exit(0);
        }
        case 1:
        {
            system("cls");
            showstudent();
 
        }
        case 2:
        {
            system("cls");
            sortnum();
        }
        case 3:
        {
            system("cls");
            sortsum();
        }
        case 4:
        {
            system("cls");
            int num;
            printf("\t请输入要查找学生的学号：");
            scanf("%d", &num);
            searchnum(num);
        }
        case 5:
        {
            system("cls");
            printf("\t请输入要查找学生的姓名：");
            scanf("%s", text);
            searchname();
        }
        case 6:
        {
            system("cls");
            save();
        }
    }
}
 
int main()
{
	void menu();
    n = 0;
    FILE * fp;
   fp=fopen("1.txt","r+");
   {
        while(fscanf(fp, "%s %d %d %d %d", student[n].name, &student[n].num, &student[n].Chinese, &student[n].Math, &student[n].English)!=EOF)
        {
            student[n].sum = 0;
            student[n].sum +=  student[n].Chinese;
            student[n].sum +=  student[n].Math;
            student[n].sum +=  student[n].English;
            n++;
        }
        fclose(fp);
   }
   fp=fopen("2.txt","r+");
   {
        while(fscanf(fp, "%s %d %d %d %d", student[n].name, &student[n].num, &student[n].Chinese, &student[n].Math, &student[n].English)!=EOF)
        {
            student[n].sum = 0;
            student[n].sum +=  student[n].Chinese;
            student[n].sum +=  student[n].Math;
            student[n].sum +=  student[n].English;
            n++;
        }
        fclose(fp);
   }
    menu();
    return 0;
}
