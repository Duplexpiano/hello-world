#include <stdlib.h> 
#include <stdio.h>
#include <string.h> 
#include <windows.h> 
#include <time.h> 
# define LEN sizeof(struct Student) 
struct Student {
	char num[10];     //学号 
	char name[20];    //姓名 
	char sex[10];    //性别 
	char birthday[20];  //生日
	char stu_gra[16]; //班级
	char address[20];  //生源地
	char dor_num[5];  //宿舍号 
	char stu_col[20]; //学院
	struct Student* next;
};
typedef struct COL {
	char col_num[8];
	char col_name[16];
	char lean_name[8];
	char col_phone;
	struct COL* next_col;
	struct COL* next_gra;
}COL;
typedef struct GRA {
	char gra_num[8];
	char gra_pro[20];
	char gra_col[16];
	struct GRA* next_class;
	struct GRA* next_stu;
}GRA;
typedef struct The_users {
	char user_id[11]; //账号
	char pwd[20]; //密码
	char user_name[15]; //姓名
	long phone; //电话
}USERS;
void menu();
void start();
void welcome();
char filename[30];//全局变量，用来保存要打开的文件名字 
struct Student* Creat(int n);
//生成链表
struct Student* Creat(int n) {
	void menu_print_in(void);
	struct Student* head;
	struct Student* p1, * p2;
	int i;
	system("cls");
	for (i = 1; i < n + 1; i++) {
		p1 = (struct Student*)malloc(LEN);
		menu_print_in();
		scanf("%s%s%s%s%s%s%s%s", p1->num, p1->name, p1->sex, p1->birthday,
			p1->stu_gra, p1->address, p1->dor_num, p1->stu_col);
		p1->next = NULL;
		if (i == 1)
			head = p2 = p1;
		else {
			p2->next = p1;
			p2 = p1;
		}
	}
	return(head);
}

void Create_Users_File()
{
	FILE* fp;
	if ((fp = fopen("users.txt", "rb")) == NULL)                 /*如果此文件不存在*/
	{
		if ((fp = fopen("users.txt", "wb+")) == NULL)
		{
			printf("\n\t\t无法建立文件！\n");
			exit(0);
		}
	}
}
/*注册账号*/
void registers()  //按结构体的大小，一次写入或者读入1个结构体大小
{
	USERS a, b;
	FILE* fp;
	char temp[20];
	int count = 0;
	system("CLS");
	system("color 2E");
	printf("\t\t\t欢迎来到注册界面！\n");
	printf("\t\t\t-----------------------\n");
	Sleep(40);
	fp = fopen("users.txt", "r+");
	fread(&b, sizeof(USERS), 1, fp);
	printf("\n\n\t\t\t请输入账号：");
	scanf("%s", a.user_id);
	while (1) {
		if (strcmp(a.user_id, b.user_id)) { /*如果两串不相等*/
			if (!feof(fp))    /*如果未到文件尾*/
				fread(&b, sizeof(USERS), 1, fp);
			else
				break;
		}
		else {
			printf("\n\t\t\t此账号已存在！请重新注册！\n");
			Sleep(1000);
			fclose(fp);
			return;
		}
	}
	printf("\n\t\t\t请输入姓名：");
	scanf("%s", a.user_name);
	getchar();
	printf("\n\t\t\t请输入电话号码：");
	scanf("%ld", &a.phone);
	printf("\n\t\t\t请输入密码：");
	scanf(" %s", a.pwd);
	printf("\n\t\t\t请确认密码：");
	scanf(" %s", temp);
	do {
		if (!strcmp(a.pwd, temp)) {
			fp = fopen("users.txt", "a");
			fwrite(&a, sizeof(USERS), 1, fp);
			printf("\n\n\t\t\t账号注册成功，请登录！\n");
			Sleep(500);
			fclose(fp);
			return;
		}
		else {
			printf("\n\t\t\t两次密码不匹配！请重新输入！\n");
			putchar('\a');
			scanf("%s", a.pwd);
			printf("\t\t\t请确认密码：");
			scanf("%s", temp);
		}
	} while (1);
	system("CLS");
}
/*登录系统*/
void  Input_login() {
	USERS a, b;
	FILE* fp;
	system("cls");
	int i;
	system("color 2E");
	printf("\t\t\t欢迎来到登录界面！\n");
	printf("===============================================================================\r");
	for (i = 1; i < 80; i++) {
		Sleep(40);
		printf(">");
	}
	printf("\n");
	fp = fopen("users.txt", "r");
	fread(&b, sizeof(USERS), 1, fp);
	printf("\n\n\t\t\t请输入账号:");
	scanf("%s", a.user_id);
	while (1) {
		if (strcmp(a.user_id, b.user_id) == 0)
			break;
		else {
			if (!feof(fp))
				fread(&b, sizeof(USERS), 1, fp);
			else {
				printf("\n\n\t\t\t此账号不存在，请重新输入！\n");
				Sleep(500);
				fclose(fp);
				return;
			}
		}
	}
	printf("\n\t\t\t请输入密码：");
	scanf("%s", a.pwd);
	do {
		if (strcmp(a.pwd, b.pwd) == 0) {
			fclose(fp);
			printf("\n\n\t\t\t**  登录成功  **");
			Sleep(500);
			return;
		}
		else {
			printf("\n\t\t\t密码不正确!请重新输入密码：");
			scanf("%s", a.pwd);
		}
	} while (strcmp(a.pwd, b.pwd) == 0);
}
//数据存盘(wb只写)
void WriteData_wb(struct Student* head) {
	FILE* fp;
	struct Student* p;
	if ((fp = fopen(filename, "wb")) == NULL)
		printf("\a \t\t文件打开错误");
	p = head;
	while (p != NULL) {
		if (fwrite(p, LEN, 1, fp) != 1) {
			printf("\n\t\t写入数据出错\n");
			fclose(fp);
			return;
		}
		p = p->next;
	}
	fclose(fp);
}

//数据存盘(ab追加) 
void WriteData_ab(struct Student* head) {
	FILE* fp;
	struct Student* p;
	if ((fp = fopen(filename, "ab")) == NULL)
		printf("\a \t\t文件打开错误!");
	p = head;
	while (p != NULL) {
		if (fwrite(p, LEN, 1, fp) != 1) {
			printf("\\n\t\t写入数据出错\n");
			fclose(fp);
			return;
		}
		p = p->next;
	}
	fclose(fp);
}


//读取数据文件保存到链表中 ，返回指向此链表头指针 
struct Student* ReadData(void) {
	struct Student* head = NULL;
	struct Student* p1, * p2;//s = p1;p = p2; 

	FILE* fp;
	if ((fp = fopen(filename, "rb+")) == NULL) {
		printf("\n\t\tFile can not open!\n");
		exit(0);
	}
	while (!feof(fp)) {
		if ((p1 = (struct Student*)malloc(LEN)) == NULL) {
			printf("\n\t\t内存申请出错\n");
			fclose(fp);
			exit(0);
		}
		if (fread(p1, LEN, 1, fp) != 1) {
			free(p1);
			break;
		}
		if (head == NULL)
			head = p2 = p1;
		else {
			p2->next = p1;
			p2 = p1;
		}
	}
	fclose(fp);
	return (head);
}

//全部查询 
void display()
{
	system("cls");
	void menu_print_out(void);
	struct Student* p;
	p = ReadData();
	menu_print_out();
	do {
		printf("%-8s%-8s%-4s%-12s%-10s%-15s%-6s%-30s", p->num, p->name, p->sex, p->birthday, p->stu_gra, p->address, p->dor_num, p->stu_col);
		p = p->next;
		printf("\n\n");
	} while (p != NULL);
	printf("\n\n");
}

//学号查询 
int query_num() {
	system("cls");
	void menu_print_out();
	struct Student* p;
	char str_num[10];
	printf("\n\t\t请输入您要查询的学号:");
	scanf("%s", str_num);
	p = ReadData();
	menu_print_out();
	do {
		if (strcmp(p->num, str_num) == 0) {
			printf("%-8s%-8s%-4s%-12s%-10s%-15s%-6s%-30s", p->num, p->name, p->sex, p->birthday, p->stu_gra, p->address, p->dor_num, p->stu_col);
			printf("\n\n");
			return 0;
		}
		p = p->next;
	} while (p != NULL);
	printf("\n\t\t数据库中没有存储您要查询的数据！\n");
	printf("\n\n");
	return 0;
}

//姓名查询 
int query_name() {
	system("cls");
	void menu_print_out(void);
	struct Student* p;
	char str_name[20];
	printf("\n\t\t请输入您要查询的姓名:");
	scanf("%s", str_name);
	p = ReadData();
	menu_print_out();
	do {
		if (strcmp(p->name, str_name) == 0) {
			printf("%-8s%-8s%-4s%-12s%-10s%-15s%-6s%-30s", p->num, p->name, p->sex, p->birthday, p->stu_gra, p->address, p->dor_num, p->stu_col);
			printf("\n\n");
			return 0;
		}
		p = p->next;
	} while (p != NULL);
	printf("\n\t\t数据库中没有存储您要查询的数据！\n");
	printf("\n\n");
	return 0;
}
int query_col() {
	system("cls");
	void menu_print_out(void);
	struct Student* p;
	char str_col[20];
	printf("\n\t\t请输入您要查询的学院:");
	scanf("%s", str_col);
	p = ReadData();
	menu_print_out();
	do {
		if (strcmp(p->stu_col, str_col) == 0) {
			printf("%-8s%-8s%-4s%-12s%-10s%-15s%-6s%-30s", p->num, p->name, p->sex, p->birthday, p->stu_gra, p->address, p->dor_num, p->stu_col);
			printf("\n\n");
			return 0;
		}
		p = p->next;
	} while (p != NULL);
	printf("\n\t\t数据库中没有存储您要查询的数据！\n");
	printf("\n\n");
	return 0;
}

//【1】修改数据之删除记录 
int delStudent() {
	struct Student* p1, * p2, * head;
	char str_num[20];
	printf("\n\t\t请输入您要删除的学号信息:");
	scanf("%s", str_num);
	p1 = ReadData();
	p2 = p1->next;
	head = p1;
	while (p2 != NULL) {
		if (strcmp(p1->num, str_num) == 0)
			WriteData_wb(p2);
		else if (strcmp(p2->num, str_num) == 0) {
			p1->next = p2->next;
			WriteData_wb(head);
		}
		p2 = p2->next;
		p1 = p1->next;
	}
	if (p2 != NULL)
		printf("\n\t\t数据库中没有存储您要删除的数据！\n");
	printf("\n\n");
	return 0;
}

//【2】修改数据之修改记录
int change1() {
	void menu_print_in(void);
	struct Student* p1, * p2, * head;
	char str_num[20];
	printf("\n\t\t请输入您要修改的学号信息:");
	scanf("%s", str_num);
	p1 = ReadData();
	p2 = p1->next;
	head = p1;
	while (p2 != NULL) {
		if (strcmp(p1->num, str_num) == 0) {
			menu_print_in();
			scanf("%s%s%s%s%s%s%s%s", p1->num, p1->name, p1->sex, p1->birthday,
				p1->stu_gra, p1->address, p1->dor_num, p1->stu_col);
			WriteData_wb(head);
		}
		else if (strcmp(p2->num, str_num) == 0) {
			menu_print_in();
			scanf("%s%s%s%s%s%s%s", p1->num, p1->name, p1->sex, p1->birthday,
				p1->stu_gra, p1->address, p1->dor_num, p1->stu_col);
			WriteData_wb(head);
		}
		p2 = p2->next;
		p1 = p1->next;
	}
	if (p2 != NULL)
		printf("\n\t\t数据库中没有存储您要删除的数据！\n");
	return 0;
}
void start() {//欢迎界面 
	int i;
	system("color 3E");
	printf("\n\n\n\n\n\n\n\n\n\t\t\t⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙\n");
	printf("\t\t\t⊙                                ⊙\n");
	printf("\t\t\t⊙    欢迎使用学生学籍管理系统    ⊙\n");
	printf("\t\t\t⊙                                ⊙\n");
	printf("\t\t\t⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙⊙\n");
	printf("\n\t\t\t\t系统开始启动.........\n");
	printf("===============================================================================\r");
	for (i = 1; i < 80; i++) {
		Sleep(40);
		printf(">");
	}
	system("CLS");
	welcome();
}
//登录界面
void welcome() {
	Create_Users_File();
	system("CLS");
	system("color 2F");
	printf("\n\n\n\n\n\n\t\t\t★★★★★★★★★★★★★★★★\n");
	printf("\t\t\t★  欢迎使用学生学籍管理系统  ★\n");
	printf("\t\t\t★★★★★★★★★★★★★★★★\n");
	printf("\t\t\t-------------------------\n");
	printf("\t\t\t1、登录/Login\n");
	printf("\t\t\t-------------------------\n");
	printf("\t\t\t2、注册/Register\n");
	printf("\t\t\t-------------------------\n");
	printf("\t\t\t请输入功能前的序号选择服务项目:");
	int a;
	scanf("%d", &a);
	while (a != 1 && a != 2) {
		printf("\n\t\t错误，请输入正确的号码!\n");
		putchar('\a');
		printf("\n\t\t请输入功能前的序号选择服务项目:");
		scanf("%d", &a);
	}
	switch (a) {
	case 1: Input_login();
		break;
	case 2: registers();
		system("CLS");
		getchar();
		Input_login();
		break;
	}
	printf("\n\t\t\t按任意键继续...");
	getchar();
	system("CLS");
	menu();
}
//主菜单
void menu() {
	void addStudent();
	void query();
	int File_name();
	void change();
	system("CLS");
	system("color 2E");
	printf("\n\n");
	printf("\t\t\t	  主菜单/Menu\n");
	printf("\t\t\t*****************************\n");
	printf("\t\t\t  1.输入/Input Information\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t  2.查询/Look For Information\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t  3.修改/Modify Information\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t  4.退出系统/Exit\n");
	printf("\t\t\t-----------------------------\n");
	printf("\n\t\t请输入功能前的序号选择服务项目:");
	int a;
	scanf("%d", &a);
	while (a != 1 && a != 2 && a != 3 && a != 4) {
		printf("\n\t\t错误，请输入正确的号码!\n");
		putchar('\a');
		printf("\n\t\t请输入功能前的序号选择服务项目:");
		scanf("%d", &a);
	}
	switch (a) {
	case 1:
		File_name();
		addStudent();
		break;
	case 2:
		File_name();
		query();
		break;
	case 3:
		File_name();
		change();
		break;
	case 4:
		exit(0);
		break;
	}
}

int File_name() {
	printf("\n\t\t请输入您要打开的文件:");
	if (scanf("%s", filename) != 1)
		printf("\a error!");
	return 0;
}
//二级菜单之添加数据 
void addStudent() {
	int Creat_num();
	system("cls");
	getchar();
	system("CLS");
	system("color 3E");
	printf("\n\n\n");
	printf("\t\t\t*          添加数据/Add        *\n");
	printf("\t\t\t※-------------------------------※\n");
	printf("\t\t\t    1. 新建文件/Newly-built File\n");
	printf("\t\t\t※-------------------------------※\n");
	printf("\t\t\t    2. 增添数据/Add Data\n");
	printf("\t\t\t※-------------------------------※\n");
	printf("\t\t\t    3. 返回/Return\n");
	printf("\t\t\t※-------------------------------※\n");
	printf("\n\t\t请输入功能前的序号选择服务项目:");
	int a;
	scanf("%d", &a);
	while (a != 1 && a != 2 && a != 3) {
		printf("\n\t\t错误，请输入正确的号码!\n");
		putchar('\a');
		printf("\n\t\t请输入功能前的序号选择服务项目:");
		scanf("%d", &a);
	}
	switch (a) {
	case 1:
		WriteData_wb(Creat(Creat_num()));
		printf("\n\t\t新建文件成功且数据已成功保存\n");
		system("pause");
		system("cls");
		addStudent();
		break;
	case 2:
		WriteData_ab(Creat(Creat_num()));
		printf("\n\t\t数据已成功添加\n");
		system("pause");
		system("cls");
		addStudent();
		break;
	case 3:
		system("cls");
		getchar();
		menu();
		break;
	}
}

//二级菜单-查询数据 
void query() {
	system("cls");
	system("color 3E");
	getchar();
	while (1) {
		system("CLS");
		system("color A");
		printf("\n\n\n");
		printf("\t\t\t---------查询数据/Index--------\n\n");
		printf("\t\t\t-------------------------------\n");
		printf("\t\t\t       1.索引所有数据/Find All\n");
		printf("\t\t\t-------------------------------\n");
		printf("\t\t\t       2.学号索引/ID Index\n");
		printf("\t\t\t-------------------------------\n");
		printf("\t\t\t       3.姓名索引/Name Index\n");
		printf("\t\t\t-------------------------------\n");
		printf("\t\t\t       4.学院索引/College Index\n");
		printf("\t\t\t-------------------------------\n");
		printf("\t\t\t       5.返回/Return\n");
		printf("\t\t\t-------------------------------\n");
		printf("\n\t\t请输入功能前的序号选择服务项目:");
		int a = 0;
		scanf("%d", &a);
		while (a != 1 && a != 2 && a != 3 && a != 4 && a != 5) {
			printf("\n\t\t输入错误，请重新输入！\n");
			putchar('\a');
			//getchar();
			printf("\n\t\t请输入功能前的序号选择服务项目:");
			scanf("%d", &a);
		}
		switch (a) {
		case 1: display();
			system("pause");
			getchar();
			break;
		case 2: query_num();
			system("pause");
			getchar();
			break;
		case 3: query_name();
			system("pause");
			getchar();
			break;
		case 4: query_col();
			system("pause");
			getchar();
			break;
		case 5: system("cls");
			getchar();
			menu();
			break;
		}
	}
}
int Creat_num() {
	printf("\n\t\t请输入您要添加的数据个数:");
	int n;
	if (scanf("%d", &n) != 1) {
		printf("\a error!");
	}
	return n;
}
//二级菜单之修改数据/ 
void change() {
	system("cls");
	system("color 3E");
	getchar();
	while (1) {
		system("CLS");
		system("color B");
		printf("\n\n\n");
		printf("\t\t\t-------修改数据/Modify-------\n\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t       1.删除/Delete\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t       2.修改/Modify\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t       3.返回/Return\n");
		printf("\t\t\t-----------------------------\n");
		printf("\n\t\t请输入功能前的序号选择服务项目:");
		int a = 0;
		scanf("%d", &a);
		while (a != 1 && a != 2 && a != 3) {
			printf("\n\t\t错误，请输入正确的号码!\n");
			putchar('\a');
			getchar();
			printf("\n\t\t请输入功能前的序号选择服务项目:");
			scanf("%d", &a);
		}
		switch (a) {
		case 1:
			delStudent();
			printf("\n\n\t\t已成功删除指定数据\n");
			system("pause");
			getchar();
			break;
		case 2:
			change1();
			printf("\n\n\t\t已成功修改指定数据\n");
			system("pause");
			getchar();
			break;
		case 3:
			system("cls");
			getchar();
			menu();
			break;
		}
	}
}

//输入输出提示栏 
void menu_print_in() {
	printf("----------------------------------------------------------------------------------\n");
	printf("学号    姓名   性别  生日        班级     生源地        宿舍号   学院\n");
	printf("----------------------------------------------------------------------------------\n");
}
void menu_print_out(void) {
	printf("----------------------------------------------------------------------------------\n");
	printf("学号    姓名   性别  生日        班级     生源地        宿舍号   学院\n");
	printf("----------------------------------------------------------------------------------\n");
}
