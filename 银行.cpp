#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

//��������
#define user_max 99		//�û������
#define take_notes_max 40	//��¼��
#define data_file "bankdata.txt"		//�����ļ�Ĭ�ϵ�ַ
#define user_size sizeof(user)
//�ṹ�����
struct take_notes {
	char handle[10];	//����
	float money;		//������Ǯ��
	struct tm T;		//ʱ��ṹ��
};

typedef struct {
	char name[25];		//�û���
	unsigned int card;		//���п���
	char pass[8];		//����
	float balance;		//���
	struct take_notes list[take_notes_max];//�����¼�ṹ������
	int flag;//��ʧ״̬ 
}user;

/*
**���ܺ���
*/


/*���ܺ���*/

//������û�
void add_user() {
	int user_num();
	void file_read(user*);
	void file_save(user*, int);
	user p = { NULL };
	char y = NULL;
	printf("\n\nע���û�\n");
	printf("--------------\n���������20�ַ��ڣ���");
	rewind(stdin);
	gets(p.name);
	printf("������루6���ַ�����");
	rewind(stdin);
	gets(p.pass);

	if (strlen(p.name) == 0 || strlen(p.name) > 20) {
		printf("ERROR224��������ʽ����\n");
		y = 'N';
	}
	if (strlen(p.pass) != 6) {
		printf("ERROR224�������ʽ����\n");
		y = 'N';
	}
	if (y == NULL) {
		user list[user_max] = { NULL };
		file_read(list);
		for (int i = user_num() - 1; i >= 0; i--)
			if (strcmp(list[i].name, p.name) == 0)
			{
				printf("------------------\n");
				printf("��ʾ��ϵͳ��⵽������ͬ���û���������ע�Ὣ����µĿ��ţ�\n");
				printf("\tY.����\t�س�������\n");
				printf("����ѡ��");
				rewind(stdin);
				y = getchar();
			}
		if (y == 'Y' || y == NULL) {
			(p.card) = ((list + (user_num() - 1))->card + 1);		//�����п���
			p.balance = 0;
			list[user_num()] = p;		//�����û�
			file_save(list, user_num() + 1);
			system("cls");
			printf("��ʾ��ע��ɹ���\n\t�û�����%s\t����:%d", p.name, p.card);
		}
		else {
			system("cls");
			printf("��ʾ���û�����ע�ᣡ");
		}
	}
	else {
		printf("\n��ʾ��ע��ʧ�ܣ��س�������...\n");
		rewind(stdin);
		getchar();
		system("cls");
	}
}
//�û���¼
user* login() {
	static user p = { NULL };
	int user_num();
	void file_read(user*);
	user list[user_max] = { NULL };
	file_read(list);
	if (p.name[0] == NULL) {
		printf("--------------------\n");
		printf("���뿨�ţ�");
		rewind(stdin);
		scanf("%d", &p.card);
		printf("�������룺");
		rewind(stdin);
		gets(p.pass);
		for (int i = user_num() - 1; i >= 0; i--) {
			if (list[i].card == p.card) {
				if (strcmp(list[i].pass, p.pass) == 0)
					p = list[i];
				else {
					p.name[0] = NULL;
					printf("��ʾ��������󣡻س�������.....\n");
					rewind(stdin);
					getchar();
					system("cls");
				}
				break;
			}
			else if (i == 0) {
				p.name[0] = NULL;
				printf("��ʾ�����Ų����ڣ��س�������......\n");
				rewind(stdin);
				getchar();
				system("cls");
			}
		}
	}
	else {
		for (int i = user_num(); i >= 0; i--)
			if (list[i].card == p.card) {
				p = list[i];
				break;
			}
	}
	return &p;
}
//����ѯ
void balance_num() {
	user* login();
	user *p = login();

	void handle_save(struct tm*, float, char arr[]);
	struct tm* time_now();
	static int num_1 = 1;
	struct tm *t = time_now();
	printf("����ѯ-����ϵͳʵ��\n\n\n\n");
	printf("\t�����������������������������������Щ��������������������������������Щ�������������������������������������\n");
	printf("\t��������%-10s�����ţ�%-10d����%10.2fԪ��\n", p->name, p->card, p->balance);
	printf("\t�����������������������������������ة��������������������������������ة�������������������������������������\n");
	char p1[10] = "��ѯ���";
	handle_save(t, 0, p1);		//�����¼
	printf("\n\t$$��ǰʱ�䣺%d-%d-%d %d:%d:%d �Ѽ�¼", 1900 + t->tm_year, 1 + t->tm_mon, t->tm_mday, 8 + t->tm_hour, t->tm_min, t->tm_sec);
	printf("\n\nY.ˢ��\t�س�������.....\n");
	printf("----------------\n����ѡ��");
	rewind(stdin);
	if (getchar() == 'Y') {
		system("cls");
		printf("�� %d ��ˢ�³ɹ���\t", num_1++);
		balance_num();
	}
	else
		system("cls");
}
//ȡ��
void draw() {
	void file_read(user*);
	void file_save(user*, int);
	void handle_save(struct tm*, float, char arr[]);
	struct tm* time_now();
	struct tm *t = time_now();
	int user_num();
	int num_2 = 0;
	float money;
	user* login();
	user *p = login();
	user list[user_max] = { NULL };
	printf("\n--------------\n��");
	scanf("%f", &money);
	float sum = 0;
	for (int i = 0; p->list[i].handle[0] != NULL; i++)
	{
		if (strcmp(p->list[i].handle, "����һ��") == 0 || strcmp(p->list[i].handle, "��������") == 0 || strcmp(p->list[i].handle, "��������") == 0)
			sum += p->list[i].money;

	}

	if (money <= 0) {
		system("cls");
		printf("��ʾ��ȡ��ʧ�ܣ�ԭ����Ӧ�����㣡\t");
	}
	else if (money > (p->balance - sum)) {
		system("cls");
		printf("��ʾ��ȡ��ʧ�ܣ�ԭ�����ȡ����������Ƕ��ڴ��δ���ڣ�\t");
	}
	else {
		char p1[5] = "ȡ��";
		handle_save(t, money, p1);
		file_read(list);
		for (num_2; list[num_2].card != p->card; num_2++);
		(p->balance) -= money;
		list[num_2].balance = p->balance;

		file_save(list, user_num());
		system("cls");
		printf("��ʾ��ȡ��ɹ�! ��%.2fԪ\t", money);
	}
}
//���
void deposit() {
	void file_read(user*);
	void file_save(user*, int);
	void handle_save(struct tm*, float, char arr[]);
	struct tm* time_now();
	struct tm *t = time_now();
	int user_num();
	int num_3 = 0;
	float money;
	user* login();
	user *p = login();
	user list[user_max] = { NULL };
	printf("\n--------------\n��������->>>>��");
	scanf("%f", &money);
	if (money <= 0) {
		system("cls");
		printf("��ʾ�����ʧ�ܣ�ԭ����Ӧ�����㣡\t");
	}
	else {
		printf("***********��Ʋ�Ʒ************\n");
		printf("1.����һ��\n2.��������\n3.��������\n4.��ͨ���\n������:");
		int  ch;
		scanf("%d", &ch);
		while (ch)
		{
			if (ch == 1)
			{
				char p1[10] = "����һ��";
				handle_save(t, money, p1);
				file_read(list);
				for (num_3; list[num_3].card != p->card; num_3++);
				(p->balance) += money;
				list[num_3].balance = p->balance;
				file_save(list, user_num());
				system("cls");
				printf("��ʾ������һ����ɹ�! ��%.2fԪ\t", money);
				break;
			}
			else if (ch == 2)
			{
				char p1[10] = "��������";
				handle_save(t, money, p1);
				file_read(list);
				for (num_3; list[num_3].card != p->card; num_3++);
				(p->balance) += money;
				list[num_3].balance = p->balance;
				file_save(list, user_num());
				system("cls");
				printf("��ʾ������������ɹ�! ��%.2fԪ\t", money);
				break;
			}
			else if (ch == 3)
			{
				char p1[10] = "��������";
				handle_save(t, money, p1);
				file_read(list);
				for (num_3; list[num_3].card != p->card; num_3++);
				(p->balance) += money;
				list[num_3].balance = p->balance;
				file_save(list, user_num());
				system("cls");
				printf("��ʾ������������ɹ�! ��%.2fԪ\t", money);
				break;
			}
			else if (ch == 4)
			{
				char p1[10] = "��ͨ���";
				handle_save(t, money, p1);
				file_read(list);
				for (num_3; list[num_3].card != p->card; num_3++);
				(p->balance) += money;
				list[num_3].balance = p->balance;
				file_save(list, user_num());
				system("cls");
				printf("��ʾ�����ڴ��ɹ�! ��%.2fԪ\t", money);
				break;
			}
			else {
				system("cls");
				printf("�˳�\n");
				break;
			}
		}
	}
}
//�޸�����
void editpass() {
	void file_read(user*);
	void file_save(user*, int);
	user* login();
	int user_num();
	void handle_save(struct tm*, float, char arr[]);
	struct tm* time_now();
	struct tm *t = time_now();
	user *p = login();
	user list[user_max] = { NULL };
	char pass[8];
	int num_6 = 0;
	printf("\n\n----------------------\n");
	printf("*��֤/����ԭ���룺");
	rewind(stdin);
	gets(pass);
	if (strcmp(p->pass, pass) == 0) {
		printf("���������루6���ַ�����");
		rewind(stdin);
		gets(pass);
		if (strlen(pass) == 6) {
			file_read(list);
			for (num_6; list[num_6].card != p->card; num_6++);
			strcpy(list[num_6].pass, pass);
			char ch[10] = "�޸�����";
			handle_save(t, 0, ch);
			file_save(list, user_num());
			system("cls");
			printf("��ʾ�����������óɹ����Ժ���ʹ���������¼��\t");
		}
		else {
			system("cls");
			printf("��ʾ���޸�ʧ�ܣ�ԭ�������벻���Ϲ涨��\t");
		}
	}
	else {
		system("cls");
		printf("��ʾ���޸�ʧ�ܣ�ԭ����֤ʧ�ܣ�\t");
	}
}
//�����˻�
void account() {
	user* login();
	user *p = login();
	void file_read(user*);
	user list[user_max] = { NULL };
	int user_num();
	int num_8 = 0;
	file_read(list);
	system("cls");
	printf("�û���%s �����˻�\n\n\n", p->name);
	printf("\t\t�������������Щ����������������������������������Щ���������������������������\n");
	printf("\t\t���� �ũ�   �� ��         ���� ��        ��\n");
	for (int i = user_num() - 1; i >= 0; i--, num_8++)
		if (strcmp(list[i].name, p->name) == 0) {
			printf("\t\t�������������੤���������������������������������੤��������������������������\n");
			printf("\t\t��%5d��%17s��%13d��\n", i, list[i].name, list[i].card);
		}
	printf("\t\t�������������ة����������������������������������ة���������������������������\n");
	printf("\t\t$$��%d������\n", num_8);
	printf("\n\n�س�������......\n");
	rewind(stdin);
	getchar();
	system("cls");
}
//ע��
char del_user() {
	user* login();
	user *p = login();
	int user_num();
	void file_read(user*);
	void file_save(user*, int);
	user list[user_max] = { NULL };
	char pass[8];
	int num_7 = 0;
	if (p->card != 18072801) {
		printf("\n\n--------------\n��֤/�������룺");
		rewind(stdin);
		gets(pass);
		if (strcmp(p->pass, pass) == 0) {
			file_read(list);
			for (num_7; list[num_7].card != p->card; num_7++);
			for (num_7; num_7 < user_num() - 1; num_7++)
				list[num_7] = list[num_7 + 1];
			file_save(list, user_num() - 1);
			p->name[0] = NULL;
			printf("\n���ţ�%d ע���ɹ����س�������......\n", p->card);
			rewind(stdin);
			getchar();
			return 'Q';
		}
		else {
			system("cls");
			printf("��ʾ��ע��ʧ�ܣ�ԭ����֤ʧ�ܣ�\t");
			return NULL;
		}
	}
	else {
		system("cls");
		printf("��ʾ��Ĭ�Ϲ���Ա�˻�����ע����\t");
		return NULL;
	}
}
//��ʧ
void report_loss()
{
	system("cls");
	user* login();
	void file_read(user*);
	void file_save(user*, int);
	int user_num();
	int a;
	while (1)
	{
		printf("**********�����ʧ����**********\n1.��ʧ���� \n2.��ʧ������ \n3.�����˳�\n-----���룺");
		scanf("%d", &a);
		if (a == 1)
		{
			int cardid = 0;
			printf("--------------\n��֤/���뿨�ţ�\n");
			scanf("%d", &cardid);
			user list[user_max] = { NULL };
			char pass[8];
			int num_7 = 0;
			int vis = -1;//�жϱ�־
			file_read(list);
			for (int i = user_num() - 1; i >= 0; i--) {
				if (list[i].card == cardid)
					vis = i;
			}
			if (vis == -1)
			{
				system("cls");
				printf("��ʾ�����Ų�����\n");
				continue;
			}

			if (cardid != 18072801) {
				printf("\n\n--------------\n��֤/�������룺");
				rewind(stdin);
				gets(pass);
				if (strcmp(list[vis].pass, pass) == 0) {
					list[vis].flag = 1;
					file_save(list, user_num());
					printf("\n���ţ�%d ��ʧ�ɹ����س�������......\n", list[vis].card);
					rewind(stdin);
					getchar();
					system("cls");
				}
				else {
					system("cls");
					printf("��ʾ����ʧʧ�ܣ�ԭ����֤ʧ�ܣ�\t\n");
					continue;

				}
			}
			else {
				system("cls");
				printf("��ʾ��Ĭ�Ϲ���Ա�˻����ܹ�ʧ��\t\n");
				continue;
			}
			break;
		}
		else if (a == 2)
		{
			int cardid = 0;
			printf("--------------\n��֤/���뿨�ţ�\n");
			scanf("%d", &cardid);
			user list[user_max] = { NULL };
			char pass[8];
			int num_7 = 0;
			int vis = 0;//�жϱ�־
			file_read(list);
			for (int i = user_num() - 1; i >= 0; i--) {
				if (list[i].card == cardid)
					vis = i;
			}
			if (vis == 0)
			{
				system("cls");
				printf("���Ų�����");
				continue;
			}

			if (cardid != 18072801) {
				printf("\n\n--------------\n��֤/�������룺");
				rewind(stdin);
				gets(pass);
				if (strcmp(list[vis].pass, pass) == 0) {
					list[vis].flag = 0;
					file_save(list, user_num());
					printf("\n���ţ�%d �ָ�����ʹ�ã��س�������......\n", list[vis].card);
					rewind(stdin);
					getchar();
				}
				else {
					system("cls");
					printf("��ʾ����ʧʧ�ܣ�ԭ����֤ʧ�ܣ�\t");

				}
			}
			else {
				system("cls");
				printf("��ʾ��Ĭ�Ϲ���Ա�˻�����ִ�д˲�����\t");
			}
			break;

		}
		else {
			system("cls");
			break;
		}
	}




}
//�ǳ�ϵͳ
char out_login() {
	user* login();
	user *p = login();
	printf("\n\n------------------\n");
	printf("\tQ.����\t�س����ǳ�ϵͳ.......\n");
	rewind(stdin);
	if (getchar() == 'Q') {
		system("cls");
		return NULL;
	}
	else {
		p->name[0] = NULL;
		return 'Q';
	}
}
//��¼��ѯ
void handle_list() {
	user* login();
	user *p = login();
	char h1;
	struct tm t[2];
	printf("\n\n---------------------\n\tA.��%d����¼\tB.��ʱ��β�ѯ\n", take_notes_max);
	printf("������ţ�");
	rewind(stdin);
	h1 = getchar();
	int num_9 = 0;
	if (h1 == 'A') {
		system("cls");
		printf("���ţ�%d ���%d����¼\n\n", p->card, take_notes_max);
		for (int i = 0; (i < take_notes_max) && (p->list[i].handle[0] != NULL); i++)
			printf("##���ڣ�%d��%d��%d�� %d:%d:%d\n\t������%s\t��%.2f\n", 1900 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, p->list[i].handle, p->list[i].money);
		printf("\n\n\n�س�������........\n");
		rewind(stdin);
		getchar();
		system("cls");
	}
	else if (h1 == 'B') {
		printf("\n\n------------------------\n���뿪ʼ���ڣ���ʽ��2018-07-29����");
		scanf("%d-%d-%d", &t[0].tm_year, &t[0].tm_mon, &t[0].tm_mday);
		printf("����������ڣ�");
		scanf("%d-%d-%d", &t[1].tm_year, &t[1].tm_mon, &t[1].tm_mday);
		system("cls");
		printf("���ڣ�%d��%d��%d��-%d��%d��%d�� �ļ�¼\n\n", t[0].tm_year, t[0].tm_mon, t[0].tm_mday, t[1].tm_year, t[1].tm_mon, t[1].tm_mday);
		for (int i = 0; (i < take_notes_max) && (p->list[i].handle[0] != NULL); i++)
			if (p->list[i].T.tm_year >= (t[0].tm_year - 1900) && p->list[i].T.tm_mon >= (t[0].tm_mon - 1) && p->list[i].T.tm_mday >= t[0].tm_mday)
				if (p->list[i].T.tm_year <= (t[1].tm_year - 1900) && p->list[i].T.tm_mon <= (t[1].tm_mon - 1) && p->list[i].T.tm_mday <= t[1].tm_mday) {
					printf("##���ڣ�%d��%d��%d�� %d:%d:%d\n\t������%s\t��%.2f\n", 1900 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, p->list[i].handle, p->list[i].money);
					num_9++;
				}
		printf("\n\n$$��%d����¼\n", num_9);
		printf("\n\n�س�������.......\n");
		rewind(stdin);
		getchar();
		system("cls");
	}
	else {
		system("cls");
		printf("��ʾ��ѡ���������ѡ��\t");
	}
}


//ת��
void cover() {
	user* login();
	void file_read(user*);
	void file_save(user*, int);
	struct tm* time_now();
	void handle_save(struct tm *t, float money, char arr[10]);
	int user_num();
	user *p = login();
	user list[user_max] = { NULL };
	int card;
	float money, F;
	printf("\n\n----------------\n�տ��˿��ţ�");
	scanf("%d", &card);
	file_read(list);
	for (int i = user_num() - 1; i >= 0; i--)
		if (list[i].card == card) {
			int ii = strlen(list[i].name);
			printf("##�տ��ˣ�%s\n", list[i].name);
			printf("$$����ת�˽�");
			scanf("%f", &money);
			float sum = 0;//���ڴ�� 
			struct tm *t=time_now();
			for (int i = 0; p->list[i].handle[0] != NULL; i++)
			{
				if (strcmp(p->list[i].handle, "����һ��") == 0 || strcmp(p->list[i].handle, "��������") == 0 || strcmp(p->list[i].handle, "��������") == 0)
					sum += p->list[i].money;
		
			}
			if (money >= 0 && money <= p->balance-sum) {
				printf("\tY.ȷ��ת��\t�س���ȡ��.........\n");
				printf("����ѡ��");
				rewind(stdin);
				if (getchar() == 'Y') {
					for (ii = user_num() - 1; ii >= 0 && (list[ii].card != p->card); ii--);
					list[i].balance += money;
					p->balance -= money;
					list[ii].balance = p->balance;
					file_save(list, user_num());
					char p2[10]="ת��->";
					strcat(p2,list[i].name);
					handle_save(t,money,p2);
					system("cls");
					printf("��ʾ��ת�˳ɹ��� �տ��ˣ�%d ��%.2f\t", card, money);
				}
				else {
					system("cls");
					printf("��ʾ:ȡ��ת�ˣ�\t");
				}
			}
			else {
				system("cls");
				printf("��ʾ��������߻��в��ֶ��ڴ��û���ڣ�ת��ʧ�ܣ�\t");
			}
			card = 0;
			break;
		}
	if (card != 0) {
		system("cls");
		printf("��ʾ��ת��ʧ�ܣ�ԭ�򲻴��ڵ��տ��ˣ�\t");
	}
}
//��Ϣ����
float interest_money(int flag, float percent, float money)
{
	if (flag == 1)
	{
		return  1 * money*percent;
	}
	else if (flag == 3)
	{
		return  3 * money*percent;
	}
	else if (flag == 5)
	{
		return  5 * money*percent;
	}
	else
	{
		printf("error!");
		return 0;
	}
}
//�����Ϣ��ѯ
void interest_info()
{
	system("cls");
	printf("*********�˻������Ϣ��Ϣ*******\n");
	printf("1.��������һ��1.35%% \n2.������������1.55%%\n3.������������3.3%%\n4.��������0.55%%\n\n\n");
	user* login();
	user *p = login();
	struct tm* time_now();
	static int num_1 = 1;
	struct tm *t = time_now();
	printf("*************����ѯ****************\n");
	printf("\t�����������������������������������Щ��������������������������������Щ�������������������������������������\n");
	printf("\t��������%-10s�����ţ�%-10d����%10.2fԪ��\n", p->name, p->card, p->balance);
	printf("\t�����������������������������������ة��������������������������������ة�������������������������������������\n\n\n");
	float interest = 0;

	for (int i = 0; p->list[i].handle[0] != NULL; i++)
	{
		if (strcmp(p->list[i].handle, "����һ��") == 0)
		{
			printf("����һ�꣺���:%f   ����ʱ��:% d��%d��%d�� %d:%d:%d  ������Ϣ��%f\n", p->list[i].money, 1901 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(1, 0.0135, p->list[i].money));
		}
		else if (strcmp(p->list[i].handle, "��������") == 0)
		{
			printf("�������꣺���:%f   ����ʱ��:% d��%d��%d�� %d:%d:%d  ������Ϣ��%f\n", p->list[i].money, 1903 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(3, 0.0155, p->list[i].money));
		}
		else if (strcmp(p->list[i].handle, "��������") == 0)
		{
			printf("�������꣺���:%f   ����ʱ��:% d��%d��%d�� %d:%d:%d  ������Ϣ��%f\n", p->list[i].money, 1905 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(5, 0.033, p->list[i].money));
		}
		else if (strcmp(p->list[i].handle, "����") == 0) {
			printf("���ڣ����:%f   ��ʱ��ȡ\n", p->list[i].money);
		}
	}
	printf("\n\n�س�������.......\n");
	rewind(stdin);
	getchar();
	system("cls");
}
//��Ϣ����
void interest_get()
{
	void file_read(user*);
	void file_save(user*, int);
	void handle_save(struct tm*, float, char arr[]);
	struct tm* time_now();
	int user_num();
	user* login();
	user *p = login();
	struct tm *t = time_now();//��ǰʱ��
	printf("**************��Ϣ��ʾ************\n");
	for (int i = 0; p->list[i].handle[0] != NULL; i++)
	{
		if (strcmp(p->list[i].handle, "����һ��") == 0)
		{
			printf("����һ�꣺���:%f   ����ʱ��:% d��%d��%d�� %d:%d:%d  ������Ϣ��%f\n", p->list[i].money, 1901 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(1, 0.0135, p->list[i].money));
		}
		else if (strcmp(p->list[i].handle, "��������") == 0)
		{
			printf("�������꣺���:%f   ����ʱ��:% d��%d��%d�� %d:%d:%d  ������Ϣ��%f\n", p->list[i].money, 1903 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(3, 0.0155, p->list[i].money));
		}
		else if (strcmp(p->list[i].handle, "��������") == 0)
		{
			printf("�������꣺���:%f   ����ʱ��:% d��%d��%d�� %d:%d:%d  ������Ϣ��%f\n", p->list[i].money, 1905 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(5, 0.033, p->list[i].money));
		}
		else if (strcmp(p->list[i].handle, "��ͨ���") == 0) {
			printf("���ڣ����:%f   ��ʱ��ȡ\n", p->list[i].money);
		}
	}
	getchar();
	printf("ȷ�Ͻ��㣺Y/N?\n");
	if (getchar() == 'Y') {
		system("cls");
		for (int i = 0; p->list[i].handle[0] != NULL; i++)
		{
			if (strcmp(p->list[i].handle, "����һ��") == 0)
			{
				if (t->tm_year > p->list[i].T.tm_year + 1 || (t->tm_year == p->list[i].T.tm_year + 1 && t->tm_mon > p->list[i].T.tm_mon) || (t->tm_year == p->list[i].T.tm_year + 1 && t->tm_mon == p->list[i].T.tm_mon &&t->tm_mday >= p->list[i].T.tm_mday))
				{
					printf("���ڽ���:\n����һ�꣺���:%f   ����ʱ��:% d��%d��%d�� %d:%d:%d  ������Ϣ��%f\n", p->list[i].money, 1901 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(1, 0.0135, p->list[i].money));
					int num_3 = 0;
					float money;
					user list[user_max] = { NULL };
					money = interest_money(1, 0.0135, p->list[i].money) + p->list[i].money;


					file_read(list);
					int pos = 0;
					struct tm t;
					for (num_3; list[num_3].card != p->card; num_3++);
					t = list[num_3].list[i].T;
					//�ҵ�������λ��ɾ��
					for (int i = 0; !(t.tm_year == 1901 + p->list[i].T.tm_year &&t.tm_mon == 1 + p->list[i].T.tm_mon && t.tm_mday == p->list[i].T.tm_mday && t.tm_hour == 8 + p->list[i].T.tm_hour && t.tm_min == p->list[i].T.tm_min && t.tm_sec == p->list[i].T.tm_sec); i++);
					for (pos = i; list[num_3].list[pos].handle[0] != NULL; pos++)
					{
						strcpy(list[num_3].list[pos].handle, list[num_3].list[pos + 1].handle);
					}
					(p->balance) += money;
					list[num_3].balance = p->balance;
					file_save(list, user_num());
					system("cls");

					printf("��ʾ�����ڽ���ɹ�! ��%.2fԪ\t", money);

				}
				else
				{
					printf("����һ�꣺���:%f   ����ʱ��:% d��%d��%d�� %d:%d:%d  ������Ϣ��%f <<ʱ�仹δ����>>\n", p->list[i].money, 1901 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(1, 0.0135, p->list[i].money));
				}
			}
			else if (strcmp(p->list[i].handle, "��������") == 0)
			{
				if (t->tm_year > p->list[i].T.tm_year + 3 || (t->tm_year == p->list[i].T.tm_year + 3 && t->tm_mon > p->list[i].T.tm_mon) || (t->tm_year == p->list[i].T.tm_year + 3 && t->tm_mon == p->list[i].T.tm_mon &&t->tm_mday >= p->list[i].T.tm_mday))
				{
					printf("���ڽ���:\n����3�꣺���:%f   ����ʱ��:% d��%d��%d�� %d:%d:%d  ������Ϣ��%f\n", p->list[i].money, 1901 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(1, 0.0135, p->list[i].money));
					int num_3 = 0;
					float money;
					user list[user_max] = { NULL };
					money = interest_money(1, 0.0155, p->list[i].money) + p->list[i].money;


					file_read(list);
					int pos = 0;
					struct tm t;
					for (num_3; list[num_3].card != p->card; num_3++);
					t = list[num_3].list[i].T;
					//�ҵ�������λ��ɾ��
					for (int i = 0; !(t.tm_year == 1901 + p->list[i].T.tm_year &&t.tm_mon == 1 + p->list[i].T.tm_mon && t.tm_mday == p->list[i].T.tm_mday && t.tm_hour == 8 + p->list[i].T.tm_hour && t.tm_min == p->list[i].T.tm_min && t.tm_sec == p->list[i].T.tm_sec); i++);
					for (pos = i; list[num_3].list[pos].handle[0] != NULL; pos++)
					{
						strcpy(list[num_3].list[pos].handle, list[num_3].list[pos + 1].handle);
					}
					(p->balance) += money;
					list[num_3].balance = p->balance;
					file_save(list, user_num());
					system("cls");

					printf("��ʾ�����ڽ���ɹ�! ��%.2fԪ\t", money);

				}
				else
				{
					printf("����3�꣺���:%f   ����ʱ��:% d��%d��%d�� %d:%d:%d  ������Ϣ��%f <<ʱ�仹δ����>>\n", p->list[i].money, 1901 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(1, 0.0135, p->list[i].money));
				}
			}
			else if (strcmp(p->list[i].handle, "��������") == 0)
			{
				if (t->tm_year > p->list[i].T.tm_year + 5 || (t->tm_year == p->list[i].T.tm_year + 5 && t->tm_mon > p->list[i].T.tm_mon) || (t->tm_year == p->list[i].T.tm_year + 5 && t->tm_mon == p->list[i].T.tm_mon &&t->tm_mday >= p->list[i].T.tm_mday))
				{
					printf("���ڽ���:\n����5�꣺���:%f   ����ʱ��:% d��%d��%d�� %d:%d:%d  ������Ϣ��%f\n", p->list[i].money, 1901 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(1, 0.0135, p->list[i].money));
					int num_3 = 0;
					float money;
					user list[user_max] = { NULL };
					money = interest_money(1, 0.0155, p->list[i].money) + p->list[i].money;


					file_read(list);
					int pos = 0;
					struct tm t;
					for (num_3; list[num_3].card != p->card; num_3++);
					t = list[num_3].list[i].T;
					//�ҵ�������λ��ɾ��
					for (int i = 0; !(t.tm_year == 1901 + p->list[i].T.tm_year &&t.tm_mon == 1 + p->list[i].T.tm_mon && t.tm_mday == p->list[i].T.tm_mday && t.tm_hour == 8 + p->list[i].T.tm_hour && t.tm_min == p->list[i].T.tm_min && t.tm_sec == p->list[i].T.tm_sec); i++);
					for (pos = i; list[num_3].list[pos].handle[0] != NULL; pos++)
					{
						strcpy(list[num_3].list[pos].handle, list[num_3].list[pos + 1].handle);
					}
					(p->balance) += money;
					list[num_3].balance = p->balance;
					file_save(list, user_num());
					system("cls");

					printf("��ʾ�����ڽ���ɹ�! ��%.2fԪ\t", money);

				}
				else
				{
					printf("����5�꣺���:%f   ����ʱ��:% d��%d��%d�� %d:%d:%d  ������Ϣ��%f <<ʱ�仹δ����>>\n\n", p->list[i].money, 1901 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(1, 0.0135, p->list[i].money));
				}

			}
			else if (strcmp(p->list[i].handle, "��ͨ���") == 0) {
				printf("���ڣ����:%f   ��ʱ��ȡ\n", p->list[i].money);
			}
		}
	}
	else
		system("cls");


}
//�û��б�����Ա
void user_list() {
	user* login();
	user *p = login();
	void file_read(user*);
	void file_save(user*, int);
	int user_num();
	int user_u;
	char h1;
	user list[user_max] = { NULL };
	if (p->card == 18072801) {
		printf("��ӭ����Ա%s\t���ţ�%d\n", p->name, p->card);
		file_read(list);
		printf("\n\n");
		printf("\t���������������Щ������������������������������Щ����������������������Щ�������������������������\n");
		printf("\t�����  ������           ������       �����        ��\n");
		for (int i = user_num() - 1; i >= 0; i--)
			if (list[i].card != 18072801) {
				printf("\t���������������੤�����������������������������੤���������������������੤������������������������\n");
				printf("\t��%6d��%15s��%11d��%12.2f��\n", i, list[i].name, list[i].card, list[i].balance);
			}
		printf("\t���������������ة������������������������������ة����������������������ة�������������������������\n");
		printf("\t\t$$����%d������\n", user_num() - 1);
		printf("\n\n--------------------\n���û�������\n\tA.�޸�����\tB.ɾ���û�\t�س���������һ��.......\n");
		printf("������ţ�");
		rewind(stdin);
		h1 = getchar();
		if (h1 == 'A' || h1 == 'B') {
			printf("�����û�����ţ�");
			scanf("%d", &user_u);
			if (user_u >= 0 && user_u <= (user_num() - 1)) {
				if (h1 == 'A') {
					printf("���������룺");
					rewind(stdin);
					gets(list[user_u].pass);
					file_save(list, user_num());
					system("cls");
					printf("���ţ�%d �����޸ĳɹ���\t", list[user_u].card);
					user_list();
				}
				else {
					printf("Y.ȷ��ɾ��\t�س�������.......\n");
					rewind(stdin);
					if (getchar() == 'Y') {
						for (int i = user_num() - 1; i > user_u; user_u++)
							list[user_u] = list[user_u + 1];
						file_save(list, user_num() - 1);
						system("cls");
						printf("��ʾ��ɾ���ɹ���\t");
						user_list();
					}
					else {
						system("cls");
						printf("��ʾ������ɾ��������\t");
						user_list();
					}
				}
			}
			else {
				system("cls");
				printf("��ʾ������ʧ�ܣ�ԭ�򲻴��ڸ���ţ�\t");
				user_list();
			}
		}
		else
			system("cls");
	}
}
//ʱ�亯��,��ȡ��ǰʱ��
/*tm����UTCʱ�䣬ת������ʱ��year+1900,mon+1,hour+8*/
struct tm* time_now() {
	struct tm *p;
	time_t *timep = (time_t*)malloc(sizeof(time_t));
	time(timep);
	p = gmtime(timep);
	free(timep);
	return p;
}
//������¼
void handle_save(struct tm *t, float money, char arr[10]) {
	void file_read(user*);
	void file_save(user*, int);
	int user_num();
	user* login();
	user *p = login();
	user *p1 = (user*)calloc(user_max, user_size);
	int num_4 = 0;
	for (num_4; p->list[num_4].handle[0] != NULL; num_4++);		//ȡ���Ѵ�����
	if (num_4 == take_notes_max) {
		for (int i = 0; i < num_4; i++)
			p->list[i] = p->list[i + 1];
	}
	strcpy(p->list[num_4].handle, arr);
	p->list[num_4].T = *t;
	p->list[num_4].money = money;
	file_read(p1);
	int i = 0;
	for (i = 0; (p1 + i)->card != p->card; i++);

	strcpy((p1 + i)->list[num_4].handle, arr);
	(p1 + i)->list[num_4].T = *t;
	(p1 + i)->list[num_4].money = money;
	file_save(p1, user_num());
	free(p1);
}
//�û�����
int user_num() {
	void file_read(user*);
	int num_5 = 0;
	user list[user_max] = { NULL };
	file_read(list);
	while ((list[num_5].name[0]) != NULL)
		num_5++;
	return num_5;
}
//�û���Ϣ���ܣ��������룩
void data_j(user *p) {
	for (int i = 0; i < strlen(p->name); i++)
		p->name[i] += 2;
	for (int i = 0; i < 6; i++)
		p->pass[i] += 5;
}
//�û���Ϣ���ܣ��������룩
void data_i(user *p) {
	for (int i = 0; i < strlen(p->name); i++)
		p->name[i] -= 2;
	for (int i = 0; i < 6; i++)
		p->pass[i] -= 5;
}

/*�ļ�����*/
//�ļ����
void file_true() {
	void file_save(user *p, int count);
	FILE *data = fopen(data_file, "rb");
	if (data == NULL) {
		user p = { NULL };
		strcpy(p.name, "test");
		p.card = 18072801;
		strcpy(p.pass, "123456");
		p.balance = 100;		//����һ����������
		file_save(&p, 1);		//������Ե�����
	}
	else
		fclose(data);
}
//д���ļ�
void file_save(user *p, int count) {
	for (int i = 0; i < count; i++)
		data_j(p + i);
	FILE *data = fopen(data_file, "wb");
	fwrite(p, user_size, count, data);
	fclose(data);
}
//��ȡ�ļ�
void file_read(user *p) {
	void data_i(user*);
	FILE *data = fopen(data_file, "rb");
	fread(p, user_size, user_max, data);
	for (int i = 0; (p + i)->name[0] != NULL; i++)
		data_i(p + i);
	fclose(data);
}

//����
/*
**��ʾ�˵�

*/
//��ʼ������

//��ʼ����
char face_1() {
	char h1;
	printf("\n\n\n\n\n\t\t\t\t----------------------\n");
	printf("\t\t\t\t *���������й���ϵͳ*\n");
	printf("\t\t\t\t----------------------");
	printf("\n\n\n\n\t\t\t\tA.����ϵͳ\tB.���û�\n\n\t\t\t\tQ.�˳�ϵͳ\n");
	printf("\n\n--------------------------------\n\t\t������ţ�");
	rewind(stdin);		//������뻺��
	h1 = getchar();
	if (h1 == 'A' || h1 == 'B' || h1 == 'Q')
		return h1;
	else {
		system("cls");
		printf("��ʾ��ѡ����������ѡ��");
	}

}
//��¼�����
void face_2() {
	user* login();
	user *p = login();
	void balance_num();
	void draw();
	void deposit();
	void editpass();
	void account();
	char del_user();
	char out_login();
	void handle_list();
	void user_list();
	void cover();
	char h1;
	while (1) {
		printf("��ӭ�û���%s\n", p->name);
		printf("\n\n\n\n\t\t\tA.����ѯ\tB.ȡ��\n");
		printf("\n\t\t\tC.�޸�����\tD.���\n");
		printf("\n\t\t\tE.�����˻�\tF.ע��\n");
		printf("\n\t\t\tG.�ǳ�ϵͳ\tH.��¼��ѯ\n");
		printf("\n\t\t\tQ.������һ��\tI.ת��\n");
		printf("\n\t\t\tJ.��Ϣ��ѯ\tK.��Ϣ����\n");
		if (p->card == 18072801)
		{
			printf("\n\t\t\tU.�û��б� \t L.��ʧ����\n");
		}
		printf("\n----------------\n������ţ�");
		rewind(stdin);
		if ((h1 = getchar()) >= 'A'&&h1 <= 'L') {
			switch (h1) {
			case 'A':
				balance_num(); break;
			case 'B':
				draw(); break;
			case 'C':
				editpass(); break;
			case 'D':
				deposit(); break;
			case 'E':
				account(); break;
			case 'F':
				h1 = del_user(); break;
			case 'G':
				h1 = out_login(); break;
			case 'H':
				handle_list(); break;
			case 'I':
				cover(); break;
			case 'J':
				interest_info();
				break;
			case 'K':
				interest_get();
				break;
			case 'L':
				report_loss();
				break;

			}
			if (h1 == 'Q') {
				system("cls");
				break;
			}
		}
		else if (h1 == 'Q') {
			system("cls");
			break;
		}
		else if (h1 == 'U') {
			system("cls"); user_list();
		}
		else {
			system("cls");
			printf("��ʾ��ѡ����������ѡ��\n");
		}
	}
}


/*������*/
/*
**����ʵ�֣�����ϵͳ
*/
//������
int main() {
	user* login();
	file_true();
	char h1;
	while ((h1 = face_1()) != 'Q') {
		if (h1 == 'A') {
			user *p = login();
			printf("%d",p->flag);
			if (p->name[0] != NULL && p->flag != 1) {
				system("cls");
				face_2();
			}
			else
			{
				system("cls");
				printf("��ʾ�������Ѿ���ʧ����ϵ����Ա��\n");
				p->name[0] = NULL;
			}
		}
		else if (h1 == 'B')
			add_user();
	}
	return 0;
}
