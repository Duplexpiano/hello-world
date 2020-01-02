#include <stdlib.h> 
#include <stdio.h>
#include <string.h> 
#include <windows.h> 
#include <time.h> 
# define LEN sizeof(struct Student) 
struct Student {
	char num[10];     //ѧ�� 
	char name[20];    //���� 
	char sex[10];    //�Ա� 
	char birthday[20];  //����
	char stu_gra[16]; //�༶
	char address[20];  //��Դ��
	char dor_num[5];  //����� 
	char stu_col[20]; //ѧԺ
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
	char user_id[11]; //�˺�
	char pwd[20]; //����
	char user_name[15]; //����
	long phone; //�绰
}USERS;
void menu();
void start();
void welcome();
char filename[30];//ȫ�ֱ�������������Ҫ�򿪵��ļ����� 
struct Student* Creat(int n);
//��������
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
	if ((fp = fopen("users.txt", "rb")) == NULL)                 /*������ļ�������*/
	{
		if ((fp = fopen("users.txt", "wb+")) == NULL)
		{
			printf("\n\t\t�޷������ļ���\n");
			exit(0);
		}
	}
}
/*ע���˺�*/
void registers()  //���ṹ��Ĵ�С��һ��д����߶���1���ṹ���С
{
	USERS a, b;
	FILE* fp;
	char temp[20];
	int count = 0;
	system("CLS");
	system("color 2E");
	printf("\t\t\t��ӭ����ע����棡\n");
	printf("\t\t\t-----------------------\n");
	Sleep(40);
	fp = fopen("users.txt", "r+");
	fread(&b, sizeof(USERS), 1, fp);
	printf("\n\n\t\t\t�������˺ţ�");
	scanf("%s", a.user_id);
	while (1) {
		if (strcmp(a.user_id, b.user_id)) { /*������������*/
			if (!feof(fp))    /*���δ���ļ�β*/
				fread(&b, sizeof(USERS), 1, fp);
			else
				break;
		}
		else {
			printf("\n\t\t\t���˺��Ѵ��ڣ�������ע�ᣡ\n");
			Sleep(1000);
			fclose(fp);
			return;
		}
	}
	printf("\n\t\t\t������������");
	scanf("%s", a.user_name);
	getchar();
	printf("\n\t\t\t������绰���룺");
	scanf("%ld", &a.phone);
	printf("\n\t\t\t���������룺");
	scanf(" %s", a.pwd);
	printf("\n\t\t\t��ȷ�����룺");
	scanf(" %s", temp);
	do {
		if (!strcmp(a.pwd, temp)) {
			fp = fopen("users.txt", "a");
			fwrite(&a, sizeof(USERS), 1, fp);
			printf("\n\n\t\t\t�˺�ע��ɹ������¼��\n");
			Sleep(500);
			fclose(fp);
			return;
		}
		else {
			printf("\n\t\t\t�������벻ƥ�䣡���������룡\n");
			putchar('\a');
			scanf("%s", a.pwd);
			printf("\t\t\t��ȷ�����룺");
			scanf("%s", temp);
		}
	} while (1);
	system("CLS");
}
/*��¼ϵͳ*/
void  Input_login() {
	USERS a, b;
	FILE* fp;
	system("cls");
	int i;
	system("color 2E");
	printf("\t\t\t��ӭ������¼���棡\n");
	printf("===============================================================================\r");
	for (i = 1; i < 80; i++) {
		Sleep(40);
		printf(">");
	}
	printf("\n");
	fp = fopen("users.txt", "r");
	fread(&b, sizeof(USERS), 1, fp);
	printf("\n\n\t\t\t�������˺�:");
	scanf("%s", a.user_id);
	while (1) {
		if (strcmp(a.user_id, b.user_id) == 0)
			break;
		else {
			if (!feof(fp))
				fread(&b, sizeof(USERS), 1, fp);
			else {
				printf("\n\n\t\t\t���˺Ų����ڣ����������룡\n");
				Sleep(500);
				fclose(fp);
				return;
			}
		}
	}
	printf("\n\t\t\t���������룺");
	scanf("%s", a.pwd);
	do {
		if (strcmp(a.pwd, b.pwd) == 0) {
			fclose(fp);
			printf("\n\n\t\t\t**  ��¼�ɹ�  **");
			Sleep(500);
			return;
		}
		else {
			printf("\n\t\t\t���벻��ȷ!�������������룺");
			scanf("%s", a.pwd);
		}
	} while (strcmp(a.pwd, b.pwd) == 0);
}
//���ݴ���(wbֻд)
void WriteData_wb(struct Student* head) {
	FILE* fp;
	struct Student* p;
	if ((fp = fopen(filename, "wb")) == NULL)
		printf("\a \t\t�ļ��򿪴���");
	p = head;
	while (p != NULL) {
		if (fwrite(p, LEN, 1, fp) != 1) {
			printf("\n\t\tд�����ݳ���\n");
			fclose(fp);
			return;
		}
		p = p->next;
	}
	fclose(fp);
}

//���ݴ���(ab׷��) 
void WriteData_ab(struct Student* head) {
	FILE* fp;
	struct Student* p;
	if ((fp = fopen(filename, "ab")) == NULL)
		printf("\a \t\t�ļ��򿪴���!");
	p = head;
	while (p != NULL) {
		if (fwrite(p, LEN, 1, fp) != 1) {
			printf("\\n\t\tд�����ݳ���\n");
			fclose(fp);
			return;
		}
		p = p->next;
	}
	fclose(fp);
}


//��ȡ�����ļ����浽������ ������ָ�������ͷָ�� 
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
			printf("\n\t\t�ڴ��������\n");
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

//ȫ����ѯ 
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

//ѧ�Ų�ѯ 
int query_num() {
	system("cls");
	void menu_print_out();
	struct Student* p;
	char str_num[10];
	printf("\n\t\t��������Ҫ��ѯ��ѧ��:");
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
	printf("\n\t\t���ݿ���û�д洢��Ҫ��ѯ�����ݣ�\n");
	printf("\n\n");
	return 0;
}

//������ѯ 
int query_name() {
	system("cls");
	void menu_print_out(void);
	struct Student* p;
	char str_name[20];
	printf("\n\t\t��������Ҫ��ѯ������:");
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
	printf("\n\t\t���ݿ���û�д洢��Ҫ��ѯ�����ݣ�\n");
	printf("\n\n");
	return 0;
}
int query_col() {
	system("cls");
	void menu_print_out(void);
	struct Student* p;
	char str_col[20];
	printf("\n\t\t��������Ҫ��ѯ��ѧԺ:");
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
	printf("\n\t\t���ݿ���û�д洢��Ҫ��ѯ�����ݣ�\n");
	printf("\n\n");
	return 0;
}

//��1���޸�����֮ɾ����¼ 
int delStudent() {
	struct Student* p1, * p2, * head;
	char str_num[20];
	printf("\n\t\t��������Ҫɾ����ѧ����Ϣ:");
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
		printf("\n\t\t���ݿ���û�д洢��Ҫɾ�������ݣ�\n");
	printf("\n\n");
	return 0;
}

//��2���޸�����֮�޸ļ�¼
int change1() {
	void menu_print_in(void);
	struct Student* p1, * p2, * head;
	char str_num[20];
	printf("\n\t\t��������Ҫ�޸ĵ�ѧ����Ϣ:");
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
		printf("\n\t\t���ݿ���û�д洢��Ҫɾ�������ݣ�\n");
	return 0;
}
void start() {//��ӭ���� 
	int i;
	system("color 3E");
	printf("\n\n\n\n\n\n\n\n\n\t\t\t�ѡѡѡѡѡѡѡѡѡѡѡѡѡѡѡѡѡ�\n");
	printf("\t\t\t��                                ��\n");
	printf("\t\t\t��    ��ӭʹ��ѧ��ѧ������ϵͳ    ��\n");
	printf("\t\t\t��                                ��\n");
	printf("\t\t\t�ѡѡѡѡѡѡѡѡѡѡѡѡѡѡѡѡѡ�\n");
	printf("\n\t\t\t\tϵͳ��ʼ����.........\n");
	printf("===============================================================================\r");
	for (i = 1; i < 80; i++) {
		Sleep(40);
		printf(">");
	}
	system("CLS");
	welcome();
}
//��¼����
void welcome() {
	Create_Users_File();
	system("CLS");
	system("color 2F");
	printf("\n\n\n\n\n\n\t\t\t�����������������\n");
	printf("\t\t\t��  ��ӭʹ��ѧ��ѧ������ϵͳ  ��\n");
	printf("\t\t\t�����������������\n");
	printf("\t\t\t-------------------------\n");
	printf("\t\t\t1����¼/Login\n");
	printf("\t\t\t-------------------------\n");
	printf("\t\t\t2��ע��/Register\n");
	printf("\t\t\t-------------------------\n");
	printf("\t\t\t�����빦��ǰ�����ѡ�������Ŀ:");
	int a;
	scanf("%d", &a);
	while (a != 1 && a != 2) {
		printf("\n\t\t������������ȷ�ĺ���!\n");
		putchar('\a');
		printf("\n\t\t�����빦��ǰ�����ѡ�������Ŀ:");
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
	printf("\n\t\t\t�����������...");
	getchar();
	system("CLS");
	menu();
}
//���˵�
void menu() {
	void addStudent();
	void query();
	int File_name();
	void change();
	system("CLS");
	system("color 2E");
	printf("\n\n");
	printf("\t\t\t	  ���˵�/Menu\n");
	printf("\t\t\t*****************************\n");
	printf("\t\t\t  1.����/Input Information\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t  2.��ѯ/Look For Information\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t  3.�޸�/Modify Information\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t  4.�˳�ϵͳ/Exit\n");
	printf("\t\t\t-----------------------------\n");
	printf("\n\t\t�����빦��ǰ�����ѡ�������Ŀ:");
	int a;
	scanf("%d", &a);
	while (a != 1 && a != 2 && a != 3 && a != 4) {
		printf("\n\t\t������������ȷ�ĺ���!\n");
		putchar('\a');
		printf("\n\t\t�����빦��ǰ�����ѡ�������Ŀ:");
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
	printf("\n\t\t��������Ҫ�򿪵��ļ�:");
	if (scanf("%s", filename) != 1)
		printf("\a error!");
	return 0;
}
//�����˵�֮������� 
void addStudent() {
	int Creat_num();
	system("cls");
	getchar();
	system("CLS");
	system("color 3E");
	printf("\n\n\n");
	printf("\t\t\t*          �������/Add        *\n");
	printf("\t\t\t��-------------------------------��\n");
	printf("\t\t\t    1. �½��ļ�/Newly-built File\n");
	printf("\t\t\t��-------------------------------��\n");
	printf("\t\t\t    2. ��������/Add Data\n");
	printf("\t\t\t��-------------------------------��\n");
	printf("\t\t\t    3. ����/Return\n");
	printf("\t\t\t��-------------------------------��\n");
	printf("\n\t\t�����빦��ǰ�����ѡ�������Ŀ:");
	int a;
	scanf("%d", &a);
	while (a != 1 && a != 2 && a != 3) {
		printf("\n\t\t������������ȷ�ĺ���!\n");
		putchar('\a');
		printf("\n\t\t�����빦��ǰ�����ѡ�������Ŀ:");
		scanf("%d", &a);
	}
	switch (a) {
	case 1:
		WriteData_wb(Creat(Creat_num()));
		printf("\n\t\t�½��ļ��ɹ��������ѳɹ�����\n");
		system("pause");
		system("cls");
		addStudent();
		break;
	case 2:
		WriteData_ab(Creat(Creat_num()));
		printf("\n\t\t�����ѳɹ����\n");
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

//�����˵�-��ѯ���� 
void query() {
	system("cls");
	system("color 3E");
	getchar();
	while (1) {
		system("CLS");
		system("color A");
		printf("\n\n\n");
		printf("\t\t\t---------��ѯ����/Index--------\n\n");
		printf("\t\t\t-------------------------------\n");
		printf("\t\t\t       1.������������/Find All\n");
		printf("\t\t\t-------------------------------\n");
		printf("\t\t\t       2.ѧ������/ID Index\n");
		printf("\t\t\t-------------------------------\n");
		printf("\t\t\t       3.��������/Name Index\n");
		printf("\t\t\t-------------------------------\n");
		printf("\t\t\t       4.ѧԺ����/College Index\n");
		printf("\t\t\t-------------------------------\n");
		printf("\t\t\t       5.����/Return\n");
		printf("\t\t\t-------------------------------\n");
		printf("\n\t\t�����빦��ǰ�����ѡ�������Ŀ:");
		int a = 0;
		scanf("%d", &a);
		while (a != 1 && a != 2 && a != 3 && a != 4 && a != 5) {
			printf("\n\t\t����������������룡\n");
			putchar('\a');
			//getchar();
			printf("\n\t\t�����빦��ǰ�����ѡ�������Ŀ:");
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
	printf("\n\t\t��������Ҫ��ӵ����ݸ���:");
	int n;
	if (scanf("%d", &n) != 1) {
		printf("\a error!");
	}
	return n;
}
//�����˵�֮�޸�����/ 
void change() {
	system("cls");
	system("color 3E");
	getchar();
	while (1) {
		system("CLS");
		system("color B");
		printf("\n\n\n");
		printf("\t\t\t-------�޸�����/Modify-------\n\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t       1.ɾ��/Delete\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t       2.�޸�/Modify\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t       3.����/Return\n");
		printf("\t\t\t-----------------------------\n");
		printf("\n\t\t�����빦��ǰ�����ѡ�������Ŀ:");
		int a = 0;
		scanf("%d", &a);
		while (a != 1 && a != 2 && a != 3) {
			printf("\n\t\t������������ȷ�ĺ���!\n");
			putchar('\a');
			getchar();
			printf("\n\t\t�����빦��ǰ�����ѡ�������Ŀ:");
			scanf("%d", &a);
		}
		switch (a) {
		case 1:
			delStudent();
			printf("\n\n\t\t�ѳɹ�ɾ��ָ������\n");
			system("pause");
			getchar();
			break;
		case 2:
			change1();
			printf("\n\n\t\t�ѳɹ��޸�ָ������\n");
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

//���������ʾ�� 
void menu_print_in() {
	printf("----------------------------------------------------------------------------------\n");
	printf("ѧ��    ����   �Ա�  ����        �༶     ��Դ��        �����   ѧԺ\n");
	printf("----------------------------------------------------------------------------------\n");
}
void menu_print_out(void) {
	printf("----------------------------------------------------------------------------------\n");
	printf("ѧ��    ����   �Ա�  ����        �༶     ��Դ��        �����   ѧԺ\n");
	printf("----------------------------------------------------------------------------------\n");
}
