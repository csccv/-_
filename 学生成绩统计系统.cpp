/*************************************
*******�������ƣ�ѧ���ɼ�����ϵͳ 
*******��    �ߣ�
*******����������Dev-C++5.11 
*******�������ڣ�2018.06.28
*******������ڣ�2018.07.02 
**************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
 
#define YES 1
#define NO 0
 
typedef struct
{
	int num;
	float prob_score;
	float disc_score;
	float cpp_score;
	double aver_score;
	double sum_score;
	char sex;
}StudentDate;                                            //ѧ��������Ϣ
typedef struct student
{
	char name[20];                                       //ѧ������
	StudentDate one;                                     //ѧ��������Ϣ
	int rank;                                            //�ɼ�����
	struct student *next;
}Student, *List;
 
Student *startCheck();                                   //��¼ϵͳ
Student *createListHead();                               //���������ͷ
void menu();                                             //���˵�
void sortList(Student *pHead);                           //��������
void readListWithFile(Student *pHead, char *file_name);  //���ļ��ж�ȡ���ݣ���������������
int  userChioce(Student *pHead);                         //�û�ѡ��
int  sortMenu();                                         //��ӡѡ��˵�
void passwordCheck();                                    //������
void correctWord();                                      //�޸�����
void addStudentInfo(Student *pHead);                     //�������ĩβ�������
int  scanMenu();                                         //����˵�
void findStudentInfo(Student *pHead);                    //����ѧ����Ϣ
void delStudentInfo(Student *pHead);                     //ɾ��ĳһ��ѧ����Ϣ
void alterStudentInfo(Student *pHead);                   //�޸�ѧ����Ϣ
void saveList(Student *pHead);                           //�����������ļ���
void printList(Student *pHead);                          //��ӡ����
void statisStudentInfo(Student *pHead);                  //�鿴ѧ����Ϣ
int  statisMenu();                                       //�鿴�˵�
void gotoxy(int x, int y);                               //�ı���λ�ú���
void inputData(Student *pHead, Student *node);           //������Ϣ��������Ƿ�Ϸ�
 
int main()
{
	Student *pHead;
 
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//�õ����ھ��
	SMALL_RECT rc = { 0, 0, 94 - 1, 30 - 1 };   //{Yλ��,Xλ��,��,��}
	SetConsoleWindowInfo(hOut, true, &rc);// ���ô���λ�úʹ�С
 
	system("color F1");//���ÿ���̨��ɫ
	pHead = startCheck();//��ȡ��Ϣ
	while (1)
	{
		if (9 == userChioce(pHead)) //��9ʱ�˳�ϵͳ
		{
			break;
		}
	}
 
	return 0;
}
/*================================================
== ��������Student *startCheck()
== ��  �ܣ���½ϵͳ 
== ��  ������ 
== ����ֵ�������ͷָ�� 
=================================================*/
Student *startCheck()
{
	Student *pHead;
	FILE  *fp1;
	char password[20] = "77137714";
	int i;
 
	if ((fp1 = fopen("password.dat", "rb")) == NULL)//�������ļ������ڣ��½������ļ�
	{
		fp1 = fopen("password.dat", "wb");
		fwrite(password, 20, 1, fp1);
		fclose(fp1);
		printf("�����ʼ����ɣ���Ĭ������Ϊ��77137714��");
		passwordCheck();
	}
	else
	{
		passwordCheck();
	}
	//����
	system("CLS");
	system("title ѧ���ɼ�ͳ��ϵͳ-������");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	printf("\n\n\t\t\t��ӭ���뱾ϵͳ����������.....");
	printf("\n\n\n\n\t\t\t��������������������������������������������\n");
	printf("\t\t\t��                    ��\n");
	printf("\t\t\t��������������������������������������������\n");
	gotoxy(26, 7);
	for (i = 0; i < 10; i++)
	{
		printf("��");
		Sleep(100);
	}
 
	pHead = createListHead();
	readListWithFile(pHead, "stud.dat");
 
	return pHead;
}
/*================================================
== ��������Student *createListHead()
== ��  �ܣ�����һ�������� 
== ��  ������ 
== ����ֵ�����������ͷָ�� 
=================================================*/
Student *createListHead()
{
	Student *pHead;
 
	pHead = (List)malloc(sizeof(Student));
	pHead->next = NULL;
 
	return pHead;
}
/*================================================
== ��������void passwordCheck()
== ��  �ܣ��������뼰�ж� 
== ��  ������ 
== ����ֵ���� 
=================================================*/
void passwordCheck()
{
	char password[20], inputword[20];
	int i = 0, j = 0;
	char c = 0;
	FILE *fp = fopen("password.dat", "rb");
 
	system("title ѧ���ɼ�ͳ��ϵͳ-��������");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	fread(password, 20, 1, fp);
	for (i = 0; i < 3; i++)
	{
		j = 0;
		printf("\n\n\n\t\t�㻹��%d�λ���������ȷ����: ", 3 - i);
		printf("\n\n\n\n\t\t\t������������������������������������\n");
		printf("\t\t\t��                ��\n");
		printf("\t\t\t������������������������������������\n");
		gotoxy(26, 8);
		while ((c = getch()) != 13 && j < 20)
		{
			if (c == '\b' && j >0)
			{
				putchar('\b');
				putchar(' ');
				putchar('\b');
				j--;
			}
			else
			{
				if (isprint(c))//isprintΪ���C�Ƿ�Ϊ�ɴ�ӡ�ĺ��� 
				{
					putchar('*');
					inputword[j] = c;
					j++;
				}
			}
		}
		inputword[j] = '\0';
		if (strcmp(inputword, password) == 0)
		{
			return;
		}
		else
		{
			system("CLS");
			printf("\t\t\t�����������");
		}
	}
	if (3 == i)
	{
		system("CLS");
		printf("\n\n\n\t\t�����˷����л��ᣡ���򼴽��˳���");
		Sleep(2000);
		exit(0);
	}
	fclose(fp);
	system("CLS");
 
	return;
}
/*================================================
== ��������void readListWithFile(Student *pHead, char *file_name)
== ��  �ܣ����ļ��ڵ���Ϣ��ȡ�������� 
== ��  ����Student *pHead������ͷָ�� 
           char *file_name���ļ�ָ�� 
== ����ֵ���� 
=================================================*/
void readListWithFile(Student *pHead, char *file_name)
{
	FILE *fp;
	Student *p1, *p2;
	int count, rank = 0;
	StudentDate dat;
	char stu_name[20];
 
	fp = fopen(file_name, "r");
	if (fp == NULL)
	{
		fp = fopen(file_name, "w");
		fclose(fp);
		return;
	}
	fseek(fp, 0L, 2);
	count = ftell(fp);
	p1 = pHead;
	fp = fopen(file_name, "r");
	while (!feof(fp))
	{
		p2 = (List)malloc(sizeof(Student));
		fscanf(fp, "%d %s %c %f %f %f\n", &p2->one.num, p2->name, &p2->one.sex, &p2->one.prob_score,
			&p2->one.disc_score, &p2->one.cpp_score);
		p2->one.sum_score = (double)(p2->one.prob_score + p2->one.disc_score + p2->one.cpp_score);
		p2->one.aver_score = p2->one.sum_score / 3;
		p2->next = NULL;
		p1->next = p2;
		p1 = p2;
		if (ftell(fp) == count)
		{
			break;
		}
	}
	//���������򣬲���ʼ������
	for (p1 = pHead->next; p1 != NULL; p1 = p1->next)
	{
		for (p2 = p1->next; p2 != NULL; p2 = p2->next)
		{
			if (p2->one.aver_score > p1->one.aver_score)
			{
				dat = p2->one;
				strcpy(stu_name, p2->name);
				p2->one = p1->one;
				strcpy(p2->name, p1->name);
				p1->one = dat;
				strcpy(p1->name, stu_name);
			}
		}
		p1->rank = ++rank;
	}
	fclose(fp);
}
/*================================================
== ��������int userChioce(Student *pHead)
== ��  �ܣ��û�����ѡ�� 
== ��  ��������ͷָ�� 
== ����ֵ�����ܶ�Ӧ������ 
=================================================*/
int userChioce(Student *pHead)
{
	int bum;
 
	system("title ѧ���ɼ�ͳ��ϵͳ-���˵�");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	menu();
	printf("�밴��ѡ��: ");
	bum = (int)(getch() - '0');
	switch (bum)
	{
	case 1:
		addStudentInfo(pHead);
		break;
	case 2:
		delStudentInfo(pHead);
		break;
	case 3:
		alterStudentInfo(pHead);
		break;
	case 4:
		findStudentInfo(pHead);
		break;
	case 5:
		statisStudentInfo(pHead);
		break;
	case 9:
		break;
	case 6:
		sortList(pHead);
		break;
	case 7:
		correctWord();
		break;
	case 8:
		MessageBox(NULL, TEXT("���ƣ�ѧ���ɼ�����ϵͳ\nѧУ�������ʵ��ѧ\n���ߣ��ƿ�1705 ������"), TEXT("����"), MB_OK);
		break;
	default:
		break;
	}
 
	return bum;
}
/*================================================
== ��������void addStudentInfo(Student *pHead)
== ��  �ܣ�������ĩβ������� 
== ��  ��������ͷָ�� 
== ����ֵ���� 
=================================================*/
void addStudentInfo(Student *pHead)
{
	FILE *fp;
	Student *p1, *p2, *p3 = pHead;
	StudentDate dat;
	int judge = YES, rank = 0;
	char bum, stu_name[20];
 
	system("title ѧ���ɼ�ͳ��ϵͳ-���");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	fp = fopen("stud.dat", "a");
	while (pHead->next)
	{
		pHead = pHead->next;
	}
	while (judge)
	{
		p1 = (List)malloc(sizeof(Student));
		inputData(p3, p1);
		p1->next = NULL;
		pHead->next = p1;
		pHead = p1;
		fprintf(fp, "%d %s %c %.1f %.1f %.1f\n", p1->one.num, p1->name, p1->one.sex, p1->one.prob_score,
			p1->one.disc_score, p1->one.cpp_score);
		printf("�Ƿ������ӣ�(Y/N)");
		bum = getch();
		if (bum == 'n' || bum == 'N')
		{
			break;
		}
 
	}
	//����������
	for (p1 = p3->next; p1 != NULL; p1 = p1->next)
	{
		for (p2 = p1->next; p2 != NULL; p2 = p2->next)
		{
			if (p2->one.aver_score > p1->one.aver_score)
			{
				dat = p2->one;
				strcpy(stu_name, p2->name);
				p2->one = p1->one;
				strcpy(p2->name, p1->name);
				p1->one = dat;
				strcpy(p1->name, stu_name);
			}
		}
		p1->rank = ++rank;
	}
	fclose(fp);
}
/*================================================
== ��������void inputData(Student *pHead, Student *node)
== ��  �ܣ�������Ϣ������Ƿ�Ϸ� 
== ��  ����Student *pHead������ͷָ�� 
           Student *node��������ָ�� 
== ����ֵ���� 
=================================================*/
void inputData(Student *pHead, Student *node)
{
	Student *p1 = node, *p2, *p3 = pHead;
 
	system("CLS");
	printf("\n\n\t����������ѧ����ѧ�š��������Ա𡢸��ʡ���ɢ��c++�ɼ�\n");
	printf("\tע��:���������пո��Ա�����M��ʾ��Ů��W��ʾ��\n\t���Ƴɼ�Ӧ�ô���0С��100����������ʱ���ÿո����\n");
	scanf("%d %s %c %f %f %f", &p1->one.num, p1->name, &p1->one.sex, &p1->one.prob_score, &p1->one.disc_score, &p1->one.cpp_score);
	// �ж������ѧ���Ƿ��Ѿ�����
	p2 = p3->next;
	while (1)
	{
		if (p2 == NULL)
		{
			break;
		}
		if (p2->one.num == p1->one.num && p2 != node)
		{
			printf("��ѧ���Ѵ��ڣ�����������ѧ��:");
			scanf("%d", &p1->one.num);
			p2 = p3->next;
		}
		else
		{
			p2 = p2->next;
		}
	}
	//�Ա��Ƿ�Ϸ�
	while (1)
	{
		if (p1->one.sex != 'W'&& p1->one.sex != 'M')
		{
			p1->one.sex = getchar();
			printf("�Ա����벻�Ϸ�������������: ");
			p1->one.sex = getchar();
 
		}
		else
		{
			break;
		}
	}
	//�ɼ��Ƿ�Ϸ�
	while (1)
	{
		if (p1->one.prob_score < 0 || p1->one.prob_score > 100)
		{
			printf("���ʳɼ����벻�Ϸ�������������:");
			scanf("%f", &p1->one.prob_score);
		}
		if (p1->one.disc_score < 0 || p1->one.disc_score > 100)
		{
			printf("��ɢ�ɼ����벻�Ϸ�������������:");
			scanf("%f", &p1->one.disc_score);
		}
		if (p1->one.cpp_score < 0 || p1->one.cpp_score > 100)
		{
			printf("c++�ɼ����벻�Ϸ�������������:");
			scanf("%f", &p1->one.cpp_score);
		}
		if (p1->one.prob_score >= 0 && p1->one.prob_score <= 100 && p1->one.disc_score >= 0
			&& p1->one.disc_score <= 100 && p1->one.cpp_score >= 0 && p1->one.cpp_score <= 100)
		{
			break;
		} 
	}
	p1->one.sum_score = (double)(p1->one.prob_score + p1->one.disc_score + p1->one.cpp_score);
	p1->one.aver_score = p1->one.sum_score / 3;
}
/*================================================
== ��������void alterStudentInfo(Student *pHead)
== ��  �ܣ��޸�ѧ����Ϣ 
== ��  ��������ͷָ�� 
== ����ֵ���� 
=================================================*/
void alterStudentInfo(Student *pHead)
{
	int bum, count = 0, j = 0;
	int num;
	char student_name[20];
	Student *p1 = pHead->next;
 
	system("title ѧ���ɼ�ͳ��ϵͳ-�޸�");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	bum = scanMenu();
	if (bum == 1)
	{
		printf("\n\t\t\t������Ҫ�޸�ѧ����ѧ�ţ�");
		scanf("%d", &num);
		while (p1)
		{
			j++;
			if (p1->one.num == num)
			{
				inputData(pHead, p1);
				break;
			}
			p1 = p1->next;
		}
		if (p1 == NULL)
		{
			getch();
			printf("û�и�ѧ����Ϣ��");
		}
	}
	else
	{
		if (bum == 2)
		{
			printf("\n\t\t\t������Ҫ�޸�ѧ����������");
			scanf("%s", student_name);
			while (p1)
			{
				j++;
				if (strcmp(p1->name, student_name) == 0)
				{
					inputData(pHead, p1);
					count = 1;
				}
				p1 = p1->next;
			}
			if (count == 0)
			{
				printf("\n\t\t\tû�и�ѧ����Ϣ��");
				getch();
			}
		}
		else
		{
			if (3 == bum)
			{
				return;
			}
			else
			{
				alterStudentInfo(pHead);
			}
		}
	}
	saveList(pHead);
}
/*================================================
== ��������int scanMenu()
== ��  �ܣ���ѯ�˵���ʾ��ѡ�� 
== ��  ������ 
== ����ֵ�����ܶ�Ӧ������ 
=================================================*/
int scanMenu()
{
	int bum;
 
	system("CLS");
	printf("\n\n\n");
	printf("\t\t������������������������������������������������������������������������������������������������������������������������\n");
	printf("\t\t��                       ��ʲô��ʽ��ѯ ��                  ��\n");
	printf("\t\t�ǩ���������������������������������������������������������������������������������������������������������������������\n");
	printf("\t\t��                    1   ��ѧ����ѧ��                      ��\n");
	printf("\t\t�ǩ���������������������������������������������������������������������������������������������������������������������\n");
	printf("\t\t��                    2   ��ѧ��������                      ��\n");
	printf("\t\t�ǩ���������������������������������������������������������������������������������������������������������������������\n");
	printf("\t\t��                    3   �������˵�                        ��\n");
	printf("\t\t������������������������������������������������������������������������������������������������������������������������\n");
	printf("�밴��ѡ��");
	bum = (int)(getch() - '0');
	system("CLS");
 
	return bum;
}
/*================================================
== ��������void saveList(Student *pHead)
== ��  �ܣ������������ļ� 
== ��  ��������ͷָ�� 
== ����ֵ���� 
=================================================*/
void saveList(Student *pHead)
{
	FILE *fp;
 
	fp = fopen("stud.dat", "w+");
	pHead = pHead->next;
	while (pHead)
	{
		fprintf(fp, "%d %s %c %.1f %.1f %.1f\n", pHead->one.num, pHead->name, pHead->one.sex, pHead->one.prob_score,
			pHead->one.disc_score, pHead->one.cpp_score);
		pHead = pHead->next;
	}
	fclose(fp);
}
/*================================================
== ��������void correctWord()
== ��  �ܣ��޸����� 
== ��  ������ 
== ����ֵ���� 
=================================================*/
void correctWord()
{
	char password[20];
	FILE *fp;
	int i = 0;
	char c;
 
	system("title ѧ���ɼ�ͳ��ϵͳ-�޸�����");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	system("CLS");
	printf("\n\n\n\n\t\t\t�������µ����룺");
 
	while ((c = getch()) != 13 && i < 20)
	{
		if (c == '\b'&&i > 0)
		{
			putchar('\b');
			putchar(' ');
			putchar('\b');
			i--;
		}
		else
		{
			if (isprint(c))//isprintΪ���C�Ƿ�Ϊ�ɴ�ӡ�ĺ��� 
			{
				putchar('*');
				password[i] = c;
				i++;
			}
		}
	}
	password[i] = '\0';
	printf("\n\t\t\t�Ƿ������޸�Ϊ<%s>? Y or N:", password);
	c = getch();
	if (c == 'Y' || c == 'y')
	{
		fp = fopen("password.dat", "wb");
		fwrite(password, 20, 1, fp);
		fclose(fp);
		printf("\n\t\t\t�޸ĳɹ���\n");
	}
	else
	{
		return;
	}
	getch();
}
/*================================================
== ��������void delStudentInfo(Student *pHead)
== ��  �ܣ�ɾ������ 
== ��  ��������ͷָ�� 
== ����ֵ���� 
=================================================*/
void delStudentInfo(Student *pHead)
{
	Student *p1, *p2 = pHead;
	int bum;
	int num, count = 0;
	char student_name[20], c;
 
	system("title ѧ���ɼ�ͳ��ϵͳ-ɾ��");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	bum = scanMenu();
	if (bum == 1)
	{
		p1 = pHead->next;
		printf("\n\t\t\t������Ҫɾ��ѧ����ѧ�ţ�");
		scanf("%d", &num);
		while (p1)
		{
			if (p1->one.num == num)
			{
				count = 1;
				printf("\n\t\t\tɾ���ɹ���ɾ����ѧ��ѧ��Ϊ��%d", num);
				if (p1->next == NULL)
				{
					pHead->next = NULL;
					break;
				}
				else
				{
					pHead->next = p1->next;
					free(p1);
					p1 = pHead->next;
				}
			}
			else
			{
				pHead = pHead->next;
				p1 = pHead->next;
			}
		}
	}
	else
	{
		if (bum == 2)
		{
			p1 = pHead->next;
			printf("\n\t\t\t������Ҫɾ����ѧ��������");
			scanf("%s", student_name);
			//ͳ��һ���ж��ٸ�ѧ��
			while (p1)
			{
				if (strcmp(p1->name, student_name) == 0)
				{
					count++;
				}
				p1 = p1->next;
			}
			if (count > 0)
			{
				printf("'\n\n\n\t\t\tһ����%d���˵���Ϣ ȫ��ɾ��(Y) or ��һɾ��(N)?", count);//ѡ��ȫ��ɾ����������һɾ��
				c = getch();
				//ȫ��ɾ��
				if (c == 'y' || c == 'Y')
				{
					p1 = pHead->next;
					while (p1)
					{
						if (strcmp(p1->name, student_name) == 0)
						{
							printf("\n\t\t\tɾ���ɹ�������Ϊ: %s", student_name);
							if (p1->next == NULL)
							{
								pHead->next = NULL;
								break;
							}
							else
							{
								pHead->next = p1->next;
								free(p1);
								p1 = pHead->next;
							}
						}
						else
						{
							pHead = pHead->next;
							p1 = pHead->next;
						}
					}
 
				}
				else
				{
					//��һɾ��
					p1 = pHead->next;
					while (p1)
					{
						if (strcmp(p1->name, student_name) == 0)
						{
							printf("\n����:%s,ѧ��:%d,�Ա�:%c  �Ƿ�ɾ��(y or n)?", p1->name, p1->one.num, p1->one.sex);
							c = getch();
							if (c == 'y' || c == 'Y')
							{
								if (p1->next == NULL)
								{
									pHead->next = NULL;
									break;
								}
								else
								{
									pHead->next = p1->next;
									free(p1);
									p1 = pHead->next;
								}
								printf("�ɹ���");
							}
							else
							{
								pHead = pHead->next;
								p1 = pHead->next;
							}
						}
						else
						{
							pHead = pHead->next;
							p1 = pHead->next;
						}
					}
				}
 
			}
		}
		else
		{
			if (bum == 3)
			{
				return;
			}
			else
			{
				delStudentInfo(pHead);
			}
		}
	}
	if (count == 0)
	{
		printf("\n\t\t\tû�и�ѧ����Ϣ��");
	}
	else
	{
		saveList(p2);
	}
	getch();
}
/*================================================
== ��������void findStudentInfo(Student *pHead)
== ��  �ܣ����ݲ��� 
== ��  ��������ͷָ�� 
== ����ֵ���� 
=================================================*/
void findStudentInfo(Student *pHead)
{
	int bum, count = 0;
	int num;
	char student_name[20];
 
	pHead = pHead->next;
	system("title ѧ���ɼ�ͳ��ϵͳ-����");//4-������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	bum = scanMenu();
	if (bum == 1)
	{
		printf("������ѧ����ѧ�ţ�");
		scanf("%d", &num);
		while (pHead)
		{
			if (pHead->one.num == num)
			{
				if (count == 0)
				{
					printf("\n\t\t\t�Ѿ��鵽��\n");
					printf("\n\  ���������������ש����������������ש��������ש������������ש������������ש������������ש������������ש������������ש���������");
					printf("\n  �� ѧ�� �� �� ��  ���Ա𩧸�  �ʩ���  ɢ��c  ++ ��ƽ���֩���  �֩����Ω�\n");
					count = 1;
				}
				printf("  �ǩ������������贈���������������贈�������贈�����������贈�����������贈�����������贈�����������贈�����������贈��������\n");
				printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", pHead->one.num,
					pHead->name, pHead->one.sex, pHead->one.prob_score, pHead->one.disc_score,
					pHead->one.cpp_score, pHead->one.aver_score, pHead->one.sum_score, pHead->rank);
				break;
			}
			pHead = pHead->next;
		}
		if (pHead == NULL)
		{
			printf("\n\t\t\tû�и�ѧ����¼��\n");
		}
		else
		{
			printf("  ���������������ߩ����������������ߩ��������ߩ������������ߩ������������ߩ������������ߩ������������ߩ������������ߩ���������\n");
		}
	}
	else
	{
		if (bum == 2)
		{
			printf("������ѧ��������");
			scanf("%s", student_name);
			while (pHead)
			{
				if (strcmp(student_name, pHead->name) == 0)
				{
					if (count == 0)
					{
						printf("\n\t\t\t�Ѿ��鵽��\n");
						printf("\n\  ���������������ש����������������ש��������ש������������ש������������ש������������ש������������ש������������ש���������");
						printf("\n  �� ѧ�� �� �� ��  ���Ա𩧸�  �ʩ���  ɢ��c  ++ ��ƽ���֩���  �֩����Ω�\n");
						count = 1;
					}
					printf("  �ǩ������������贈���������������贈�������贈�����������贈�����������贈�����������贈�����������贈�����������贈��������\n");
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", pHead->one.num,
						pHead->name, pHead->one.sex, pHead->one.prob_score, pHead->one.disc_score,
						pHead->one.cpp_score, pHead->one.aver_score, pHead->one.sum_score, pHead->rank);
				}
				pHead = pHead->next;
			}
			if (count == 0)
			{
				printf("\n\t\t\tû�и�ѧ����¼��");
			}
			else
			{
				printf("  ���������������ߩ����������������ߩ��������ߩ������������ߩ������������ߩ������������ߩ������������ߩ������������ߩ���������\n");
			}
		}
		else
		{
			if (bum == 3)
			{
				return;
			}
			else
			{
				findStudentInfo(pHead);
			}
		}
 
	}
	getch();
}
/*================================================
== ��������void menu()
== ��  �ܣ��˵���ʾ 
== ��  ������ 
== ����ֵ���� 
=================================================*/
void menu()
{
	system("CLS");//����
	printf("\n\n\n\t\t\t\t������������������������������������������������������������������������\n");
	printf("\t\t\t\t��         ѧ���ɼ�ͳ��ϵͳ         ��\n");
	printf("\t\t\t\t������������������������������������������������������������������������\n");
	printf("\t\t\t\t��         1   ����ѧ����¼         ��\n");
	printf("\t\t\t\t������������������������������������������������������������������������\n");
	printf("\t\t\t\t��         2   ɾ��ѧ����¼         ��\n");
	printf("\t\t\t\t������������������������������������������������������������������������\n");
	printf("\t\t\t\t��         3   �޸�ѧ����¼         ��\n");
	printf("\t\t\t\t������������������������������������������������������������������������\n");
	printf("\t\t\t\t��         4   ����ѧ����Ϣ         ��\n");
	printf("\t\t\t\t������������������������������������������������������������������������\n");
	printf("\t\t\t\t��         5   ͳ��ѧ���ɼ�         ��\n");
	printf("\t\t\t\t������������������������������������������������������������������������\n");
	printf("\t\t\t\t��         6   �鿴ѧ���ɼ�         ��\n");
	printf("\t\t\t\t������������������������������������������������������������������������\n");
	printf("\t\t\t\t��         7   �޸ĵ�½����         ��\n");
	printf("\t\t\t\t������������������������������������������������������������������������\n");
	printf("\t\t\t\t��         8      ����              ��\n");
	printf("\t\t\t\t������������������������������������������������������������������������\n");
	printf("\t\t\t\t��         9    �˳�ϵͳ            ��\n");
	printf("\t\t\t\t������������������������������������������������������������������������\n");
}
/*================================================
== ��������void sortList(Student *pHead)
== ��  �ܣ��������� 
== ��  ��������ͷָ�� 
== ����ֵ���� 
=================================================*/
void sortList(Student *pHead)
{
	Student *p1, *p2;
	StudentDate dat;
	char stu_name[20];
	int bum, count = 0, rank;
 
	system("title ѧ���ɼ�ͳ��ϵͳ-�鿴");//6-������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	bum = sortMenu();
	if (bum == 1)//��ƽ���ָߵ�����
	{
		for (p1 = pHead->next; p1 != NULL; p1 = p1->next)
		{
			for (p2 = p1->next; p2 != NULL; p2 = p2->next)
			{
				if (p2->one.aver_score > p1->one.aver_score)
				{
					dat = p2->one;
					rank = p2->rank;
					strcpy(stu_name, p2->name);
					p2->one = p1->one;
					p2->rank = p1->rank;
					strcpy(p2->name, p1->name);
					p1->one = dat;
					p1->rank = rank;
					strcpy(p1->name, stu_name);
				}
			}
		}
	}
	else
	{
		if (bum == 2)//��ѧ�Ÿߵ�����
		{
			for (p1 = pHead->next; p1 != NULL; p1 = p1->next)
			{
				for (p2 = p1->next; p2 != NULL; p2 = p2->next)
				{
					if (p2->one.num < p1->one.num)
					{
						dat = p2->one;
						rank = p2->rank;
						strcpy(stu_name, p2->name);
						p2->one = p1->one;
						p2->rank = p1->rank;
						strcpy(p2->name, p1->name);
						p1->one = dat;
						p1->rank = rank;
						strcpy(p1->name, stu_name);
					}
				}
			}
		}
		else
		{
			if (bum == 3)
			{
				return;
			}
			else
			{
				sortList(pHead);
			}
		}
	}
	printList(pHead);
}
/*================================================
== ��������int sortMenu()
== ��  �ܣ�����ʽ�˵���ʾ��ѡ�� 
== ��  ������ 
== ����ֵ������ʽ��Ӧ������ 
=================================================*/
int sortMenu()
{
	int bum;
 
	system("CLS");
	printf("\n\n\n");
	printf("\t\t������������������������������������������������������������������������������������������������������������������������\n");
	printf("\t\t��                       ��ʲô��ʽ��ѯ ��                  ��\n");
	printf("\t\t�ǩ���������������������������������������������������������������������������������������������������������������������\n");
	printf("\t\t��                    1   ���ɼ��ĸߵ�                      ��\n");
	printf("\t\t�ǩ���������������������������������������������������������������������������������������������������������������������\n");
	printf("\t\t��                    2   ��ѧ�ŵ�����                      ��\n");
	printf("\t\t�ǩ���������������������������������������������������������������������������������������������������������������������\n");
	printf("\t\t��                    3   �������˵�                        ��\n");
	printf("\t\t������������������������������������������������������������������������������������������������������������������������\n");
	printf("�밴��ѡ��");
	bum = (int)(getch() - '0');
	system("CLS");
 
	return bum;
}
/*================================================
== ��������void printList(Student *pHead)
== ��  �ܣ��������ݴ�ӡ 
== ��  ��������ͷָ�� 
== ����ֵ���� 
=================================================*/
void printList(Student *pHead)
{
	int count = 0;
	pHead = pHead->next;
	system("CLS");
	printf("\n\  ���������������ש����������������ש��������ש������������ש������������ש������������ש������������ש������������ש���������");
	printf("\n  �� ѧ�� �� �� ��  ���Ա𩧸�  �ʩ���  ɢ��c  ++ ��ƽ���֩���  �֩����Ω�\n");
	while (pHead)
	{
		printf("  �ǩ������������贈���������������贈�������贈�����������贈�����������贈�����������贈�����������贈�����������贈��������\n");
		printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", pHead->one.num,
			pHead->name, pHead->one.sex, pHead->one.prob_score, pHead->one.disc_score,
			pHead->one.cpp_score, pHead->one.aver_score, pHead->one.sum_score, pHead->rank);
		pHead = pHead->next;
		count++;
	}
	printf("  ���������������ߩ����������������ߩ��������ߩ������������ߩ������������ߩ������������ߩ������������ߩ������������ߩ���������\n");
	printf("\t\t\t�ð�һ��%d����!", count);
	getch();
}
/*================================================
== ��������void statisStudentInfo(Student *pHead)
== ��  �ܣ��鿴ѧ����Ϣ 
== ��  ��������ͷָ�� 
== ����ֵ���� 
=================================================*/
void statisStudentInfo(Student *pHead)
{
	double aver_score[5] = { 0,0,0,0,0 };
	Student *p1 = pHead->next;
	int count = 0;
	int bad = 0, bum;
 
	system("title ѧ���ɼ�ͳ��ϵͳ-ͳ��");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	bum = statisMenu();
	if (bum == 1)
	{
		while (p1)
		{
			aver_score[0] = aver_score[0] + p1->one.prob_score;
			aver_score[1] = aver_score[1] + p1->one.disc_score;
			aver_score[4] = aver_score[4] + p1->one.cpp_score;
			p1 = p1->next;
			count++;
		}
		aver_score[0] = aver_score[0] / count;
		aver_score[1] = aver_score[1] / count;
		aver_score[4] = aver_score[4] / count;
		p1 = pHead->next;
		printf("\n\n  ����������������������������������������������������������������������������������������������������������������������������\n");
		printf("  ��\t���ʵ�ƽ����Ϊ:%.1f��û�дﵽ�ﵽƽ���ֵ�ѧ����        ��\n", aver_score[0]);
		printf("  �ǩ������������ש����������������ש��������ש������������ש������������ש������������ש������������ש������������ש���������\n");
		printf("  �� ѧ�� �� �� ��  ���Ա𩧸�  �ʩ���  ɢ��  c++ ��ƽ���֩���  �֩����Ω�\n");
		printf("  �ǩ������������贈���������������贈�������贈�����������贈�����������贈�����������贈�����������贈�����������贈��������\n");
		while (p1)
		{
			if (p1->one.prob_score < aver_score[0])
			{
				if (bad == 0)
				{
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
						p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				else
				{
					printf("  �ǩ������������贈���������������贈�������贈�����������贈�����������贈�����������贈�����������贈�����������贈��������\n");
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
						p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				bad = 1;
			}
			p1 = p1->next;
		}
		bad = 0;
		p1 = pHead->next;
		printf("  �ǩ������������ߩ����������������ߩ��������ߩ������������ߩ������������ߩ������������ߩ������������ߩ������������ߩ���������\n");
		printf("  ��\t��ɢ��ƽ����Ϊ:%.1f��û�дﵽ�ﵽƽ���ֵ�ѧ����        ��\n", aver_score[1]);
		printf("  �ǩ������������ש����������������ש��������ש������������ש������������ש������������ש������������ש������������ש���������\n");
		printf("  �� ѧ�� �� �� ��  ���Ա𩧸�  �ʩ���  ɢ��  c++ ��ƽ���֩���  �֩����Ω�\n");
		printf("  �ǩ������������贈���������������贈�������贈�����������贈�����������贈�����������贈�����������贈�����������贈��������\n");
		while (p1)
		{
			if (p1->one.disc_score < aver_score[1])
			{
				if (bad == 0)
				{
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
						p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				else
				{
					printf("  �ǩ������������贈���������������贈�������贈�����������贈�����������贈�����������贈�����������贈�����������贈��������\n");
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
						p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				bad = 1;
			}
			p1 = p1->next;
		}
 
		bad = 0;
		p1 = pHead->next;
		printf("  �ǩ������������ߩ����������������ߩ��������ߩ������������ߩ������������ߩ������������ߩ������������ߩ������������ߩ���������\n");
		printf("  ��\tc++��ƽ����Ϊ:%.1f��û�дﵽ�ﵽƽ���ֵ�ѧ����         ��\n", aver_score[4]);
		printf("  �ǩ������������ש����������������ש��������ש������������ש������������ש������������ש������������ש������������ש���������\n");
		printf("  �� ѧ�� �� �� ��  ���Ա𩧸�  �ʩ���  ɢ��  c++ ��ƽ���֩���  �֩����Ω�\n");
		printf("  �ǩ������������贈���������������贈�������贈�����������贈�����������贈�����������贈�����������贈�����������贈��������\n");
		while (p1)
		{
			if (p1->one.cpp_score < aver_score[4])
			{
				if (bad == 0)
				{
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
						p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				else
				{
					printf("  �ǩ������������贈���������������贈�������贈�����������贈�����������贈�����������贈�����������贈�����������贈��������\n");
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
						p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				bad = 1;
			}
			p1 = p1->next;
		}
		printf("  ���������������ߩ����������������ߩ��������ߩ������������ߩ������������ߩ������������ߩ������������ߩ������������ߩ���������\n");
		printf("\t\t\t\t\t\t�ð�һ��%d����!", count);
	}
	else
	{
		if (bum == 2)
		{
			bad = 0;
			printf("\n\n  ����������������������������������������������������������������������������������������������������������������������������\n");
			printf("  ��\t���ʳɼ�����90�ֻ�С��60��ѧ����                       ��\n");
			printf("  �ǩ������������ש����������������ש��������ש������������ש������������ש������������ש������������ש������������ש���������\n");
			printf("  �� ѧ�� �� �� ��  ���Ա𩧸�  �ʩ���  ɢ��  c++ ��ƽ���֩���  �֩����Ω�\n");
			printf("  �ǩ������������贈���������������贈�������贈�����������贈�����������贈�����������贈�����������贈�����������贈��������\n");
			p1 = pHead->next;
			while (p1)
			{
				if (p1->one.prob_score < 60 || p1->one.prob_score >= 90)
				{
					if (bad == 0)
					{
						printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
							p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					else
					{
						printf("  �ǩ������������贈���������������贈�������贈�����������贈�����������贈�����������贈�����������贈�����������贈��������\n");
						printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
							p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					bad = 1;
				}
				p1 = p1->next;
			}
			bad = 0;
			printf("  �ǩ������������ߩ����������������ߩ��������ߩ������������ߩ������������ߩ������������ߩ������������ߩ������������ߩ���������\n");
			printf("  ��\t��ɢ�ɼ�����90�ֻ�С��60��ѧ����                       ��\n");
			printf("  �ǩ������������ש����������������ש��������ש������������ש������������ש������������ש������������ש������������ש���������\n");
			printf("  �� ѧ�� �� �� ��  ���Ա𩧸�  �ʩ���  ɢ��  c++ ��ƽ���֩���  �֩����Ω�\n");
			printf("  �ǩ������������贈���������������贈�������贈�����������贈�����������贈�����������贈�����������贈�����������贈��������\n");
			p1 = pHead->next;
			while (p1)
			{
				if (p1->one.disc_score < 60 || p1->one.disc_score >= 90)
				{
					if (bad == 0)
					{
						printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
							p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					else
					{
						printf("  �ǩ������������贈���������������贈�������贈�����������贈�����������贈�����������贈�����������贈�����������贈��������\n");
						printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
							p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					bad = 1;
				}
				p1 = p1->next;
			}
			bad = 0;
			printf("  �ǩ������������ߩ����������������ߩ��������ߩ������������ߩ������������ߩ������������ߩ������������ߩ������������ߩ���������\n");
			printf("  ��\tc++�ɼ�����90�ֻ�С��60��ѧ����                        ��\n");
			printf("  �ǩ������������ש����������������ש��������ש������������ש������������ש������������ש������������ש������������ש���������\n");
			printf("  �� ѧ�� �� �� ��  ���Ա𩧸�  �ʩ���  ɢ��  c++ ��ƽ���֩���  �֩����Ω�\n");
			printf("  �ǩ������������贈���������������贈�������贈�����������贈�����������贈�����������贈�����������贈�����������贈��������\n");
			p1 = pHead->next;
			while (p1)
			{
				if (p1->one.cpp_score < 60 || p1->one.cpp_score >= 90)
				{
					if (bad == 0)
					{
						printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
							p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					else
					{
						printf("  �ǩ������������贈���������������贈�������贈�����������贈�����������贈�����������贈�����������贈�����������贈��������\n");
						printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
							p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					bad = 1;
				}
				p1 = p1->next;
			}
			printf("  ���������������ߩ����������������ߩ��������ߩ������������ߩ������������ߩ������������ߩ������������ߩ������������ߩ���������\n");
		}
		else
		{
			if (bum == 3)
			{
				return;
			}
			else
			{
				statisStudentInfo(pHead);
			}
		}
	}
	getch();
}
/*================================================
== ��������int statisMenu()
== ��  �ܣ��鿴��ʽ�˵���ѡ�� 
== ��  ������ 
== ����ֵ����ʽ��Ӧ������ 
=================================================*/
int statisMenu()
{
	int bum;
 
	system("CLS");
	printf("\n\n\n");
	printf("\t\t������������������������������������������������������������������������������������������������������������������������\n");
	printf("\t\t��                   ��ʲô��ʽͳ��ѧ����Ϣ��               ��\n");
	printf("\t\t�ǩ���������������������������������������������������������������������������������������������������������������������\n");
	printf("\t\t��                      1   ��ƽ����                        ��\n");
	printf("\t\t�ǩ���������������������������������������������������������������������������������������������������������������������\n");
	printf("\t\t��                      2   ���Ƿ�ϸ�                      ��\n");
	printf("\t\t�ǩ���������������������������������������������������������������������������������������������������������������������\n");
	printf("\t\t��                      3   �������˵�                      ��\n");
	printf("\t\t������������������������������������������������������������������������������������������������������������������������\n");
	printf("�밴��ѡ��");
	bum = (int)(getch() - '0');
	system("CLS");
 
	return bum;
}
/*================================================
== ��������void gotoxy(int x, int y)
== ��  �ܣ�����ƶ���ָ��λ�� 
== ��  ����int x�������� 
           int y�������� 
== ����ֵ���� 
=================================================*/
void gotoxy(int x, int y)//xΪ������,yΪ������
{
	COORD pos = { x, y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}
