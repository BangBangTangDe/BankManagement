#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

//基本常量
#define user_max 99		//用户最大数
#define take_notes_max 40	//记录数
#define data_file "bankdata.txt"		//数据文件默认地址
#define user_size sizeof(user)
//结构体变量
struct take_notes {
	char handle[10];	//操作
	float money;		//操作的钱数
	struct tm T;		//时间结构体
};

typedef struct {
	char name[25];		//用户名
	unsigned int card;		//银行卡号
	char pass[8];		//密码
	float balance;		//余额
	struct take_notes list[take_notes_max];//处理记录结构体数组
	int flag;//挂失状态 
}user;

/*
**功能函数
*/


/*功能函数*/

//添加新用户
void add_user() {
	int user_num();
	void file_read(user*);
	void file_save(user*, int);
	user p = { NULL };
	char y = NULL;
	printf("\n\n注册用户\n");
	printf("--------------\n你的姓名（20字符内）：");
	rewind(stdin);
	gets(p.name);
	printf("你的密码（6个字符）：");
	rewind(stdin);
	gets(p.pass);

	if (strlen(p.name) == 0 || strlen(p.name) > 20) {
		printf("ERROR224：姓名格式错误！\n");
		y = 'N';
	}
	if (strlen(p.pass) != 6) {
		printf("ERROR224：密码格式错误！\n");
		y = 'N';
	}
	if (y == NULL) {
		user list[user_max] = { NULL };
		file_read(list);
		for (int i = user_num() - 1; i >= 0; i--)
			if (strcmp(list[i].name, p.name) == 0)
			{
				printf("------------------\n");
				printf("提示：系统检测到存在相同的用户名，继续注册将添加新的卡号！\n");
				printf("\tY.继续\t回车键放弃\n");
				printf("键入选择：");
				rewind(stdin);
				y = getchar();
			}
		if (y == 'Y' || y == NULL) {
			(p.card) = ((list + (user_num() - 1))->card + 1);		//新银行卡号
			p.balance = 0;
			list[user_num()] = p;		//加入用户
			file_save(list, user_num() + 1);
			system("cls");
			printf("提示：注册成功！\n\t用户名：%s\t卡号:%d", p.name, p.card);
		}
		else {
			system("cls");
			printf("提示：用户放弃注册！");
		}
	}
	else {
		printf("\n提示：注册失败！回车键返回...\n");
		rewind(stdin);
		getchar();
		system("cls");
	}
}
//用户登录
user* login() {
	static user p = { NULL };
	int user_num();
	void file_read(user*);
	user list[user_max] = { NULL };
	file_read(list);
	if (p.name[0] == NULL) {
		printf("--------------------\n");
		printf("输入卡号：");
		rewind(stdin);
		scanf("%d", &p.card);
		printf("输入密码：");
		rewind(stdin);
		gets(p.pass);
		for (int i = user_num() - 1; i >= 0; i--) {
			if (list[i].card == p.card) {
				if (strcmp(list[i].pass, p.pass) == 0)
					p = list[i];
				else {
					p.name[0] = NULL;
					printf("提示：密码错误！回车键返回.....\n");
					rewind(stdin);
					getchar();
					system("cls");
				}
				break;
			}
			else if (i == 0) {
				p.name[0] = NULL;
				printf("提示：卡号不存在！回车键返回......\n");
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
//余额查询
void balance_num() {
	user* login();
	user *p = login();

	void handle_save(struct tm*, float, char arr[]);
	struct tm* time_now();
	static int num_1 = 1;
	struct tm *t = time_now();
	printf("余额查询-银行系统实例\n\n\n\n");
	printf("\t┌────────────────┬────────────────┬──────────────────┐\n");
	printf("\t│姓名：%-10s│卡号：%-10d│余额：%10.2f元│\n", p->name, p->card, p->balance);
	printf("\t└────────────────┴────────────────┴──────────────────┘\n");
	char p1[10] = "查询余额";
	handle_save(t, 0, p1);		//保存记录
	printf("\n\t$$当前时间：%d-%d-%d %d:%d:%d 已记录", 1900 + t->tm_year, 1 + t->tm_mon, t->tm_mday, 8 + t->tm_hour, t->tm_min, t->tm_sec);
	printf("\n\nY.刷新\t回车键返回.....\n");
	printf("----------------\n键入选择：");
	rewind(stdin);
	if (getchar() == 'Y') {
		system("cls");
		printf("第 %d 次刷新成功！\t", num_1++);
		balance_num();
	}
	else
		system("cls");
}
//取款
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
	printf("\n--------------\n金额：");
	scanf("%f", &money);
	float sum = 0;
	for (int i = 0; p->list[i].handle[0] != NULL; i++)
	{
		if (strcmp(p->list[i].handle, "定期一年") == 0 || strcmp(p->list[i].handle, "定期三年") == 0 || strcmp(p->list[i].handle, "定期五年") == 0)
			sum += p->list[i].money;

	}

	if (money <= 0) {
		system("cls");
		printf("提示：取款失败，原因金额应大于零！\t");
	}
	else if (money > (p->balance - sum)) {
		system("cls");
		printf("提示：取款失败，原因可以取的余额不足或者是定期存款未到期！\t");
	}
	else {
		char p1[5] = "取款";
		handle_save(t, money, p1);
		file_read(list);
		for (num_2; list[num_2].card != p->card; num_2++);
		(p->balance) -= money;
		list[num_2].balance = p->balance;

		file_save(list, user_num());
		system("cls");
		printf("提示：取款成功! 金额：%.2f元\t", money);
	}
}
//存款
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
	printf("\n--------------\n先输入金额->>>>：");
	scanf("%f", &money);
	if (money <= 0) {
		system("cls");
		printf("提示：存款失败，原因金额应大于零！\t");
	}
	else {
		printf("***********理财产品************\n");
		printf("1.定期一年\n2.定期三年\n3.定期五年\n4.普通存款\n请输入:");
		int  ch;
		scanf("%d", &ch);
		while (ch)
		{
			if (ch == 1)
			{
				char p1[10] = "定期一年";
				handle_save(t, money, p1);
				file_read(list);
				for (num_3; list[num_3].card != p->card; num_3++);
				(p->balance) += money;
				list[num_3].balance = p->balance;
				file_save(list, user_num());
				system("cls");
				printf("提示：定期一年存款成功! 金额：%.2f元\t", money);
				break;
			}
			else if (ch == 2)
			{
				char p1[10] = "定期三年";
				handle_save(t, money, p1);
				file_read(list);
				for (num_3; list[num_3].card != p->card; num_3++);
				(p->balance) += money;
				list[num_3].balance = p->balance;
				file_save(list, user_num());
				system("cls");
				printf("提示：定期三年存款成功! 金额：%.2f元\t", money);
				break;
			}
			else if (ch == 3)
			{
				char p1[10] = "定期五年";
				handle_save(t, money, p1);
				file_read(list);
				for (num_3; list[num_3].card != p->card; num_3++);
				(p->balance) += money;
				list[num_3].balance = p->balance;
				file_save(list, user_num());
				system("cls");
				printf("提示：定期五年存款成功! 金额：%.2f元\t", money);
				break;
			}
			else if (ch == 4)
			{
				char p1[10] = "普通存款";
				handle_save(t, money, p1);
				file_read(list);
				for (num_3; list[num_3].card != p->card; num_3++);
				(p->balance) += money;
				list[num_3].balance = p->balance;
				file_save(list, user_num());
				system("cls");
				printf("提示：活期存款成功! 金额：%.2f元\t", money);
				break;
			}
			else {
				system("cls");
				printf("退出\n");
				break;
			}
		}
	}
}
//修改密码
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
	printf("*认证/输入原密码：");
	rewind(stdin);
	gets(pass);
	if (strcmp(p->pass, pass) == 0) {
		printf("输入新密码（6个字符）：");
		rewind(stdin);
		gets(pass);
		if (strlen(pass) == 6) {
			file_read(list);
			for (num_6; list[num_6].card != p->card; num_6++);
			strcpy(list[num_6].pass, pass);
			char ch[10] = "修改密码";
			handle_save(t, 0, ch);
			file_save(list, user_num());
			system("cls");
			printf("提示：新密码设置成功，以后请使用新密码登录！\t");
		}
		else {
			system("cls");
			printf("提示：修改失败，原因新密码不符合规定！\t");
		}
	}
	else {
		system("cls");
		printf("提示：修改失败，原因认证失败！\t");
	}
}
//名下账户
void account() {
	user* login();
	user *p = login();
	void file_read(user*);
	user list[user_max] = { NULL };
	int user_num();
	int num_8 = 0;
	file_read(list);
	system("cls");
	printf("用户：%s 名下账户\n\n\n", p->name);
	printf("\t\t┌─────┬─────────────────┬─────────────┐\n");
	printf("\t\t│序 号│   姓 名         │卡 号        │\n");
	for (int i = user_num() - 1; i >= 0; i--, num_8++)
		if (strcmp(list[i].name, p->name) == 0) {
			printf("\t\t├─────┼─────────────────┼─────────────┤\n");
			printf("\t\t│%5d│%17s│%13d│\n", i, list[i].name, list[i].card);
		}
	printf("\t\t└─────┴─────────────────┴─────────────┘\n");
	printf("\t\t$$共%d条数据\n", num_8);
	printf("\n\n回车键返回......\n");
	rewind(stdin);
	getchar();
	system("cls");
}
//注销
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
		printf("\n\n--------------\n认证/输入密码：");
		rewind(stdin);
		gets(pass);
		if (strcmp(p->pass, pass) == 0) {
			file_read(list);
			for (num_7; list[num_7].card != p->card; num_7++);
			for (num_7; num_7 < user_num() - 1; num_7++)
				list[num_7] = list[num_7 + 1];
			file_save(list, user_num() - 1);
			p->name[0] = NULL;
			printf("\n卡号：%d 注销成功，回车键返回......\n", p->card);
			rewind(stdin);
			getchar();
			return 'Q';
		}
		else {
			system("cls");
			printf("提示：注销失败，原因认证失败！\t");
			return NULL;
		}
	}
	else {
		system("cls");
		printf("提示：默认管理员账户不能注销！\t");
		return NULL;
	}
}
//挂失
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
		printf("**********卡务挂失管理**********\n1.挂失处理 \n2.挂失卡撤销 \n3.其他退出\n-----输入：");
		scanf("%d", &a);
		if (a == 1)
		{
			int cardid = 0;
			printf("--------------\n认证/输入卡号：\n");
			scanf("%d", &cardid);
			user list[user_max] = { NULL };
			char pass[8];
			int num_7 = 0;
			int vis = -1;//判断标志
			file_read(list);
			for (int i = user_num() - 1; i >= 0; i--) {
				if (list[i].card == cardid)
					vis = i;
			}
			if (vis == -1)
			{
				system("cls");
				printf("提示：卡号不存在\n");
				continue;
			}

			if (cardid != 18072801) {
				printf("\n\n--------------\n认证/输入密码：");
				rewind(stdin);
				gets(pass);
				if (strcmp(list[vis].pass, pass) == 0) {
					list[vis].flag = 1;
					file_save(list, user_num());
					printf("\n卡号：%d 挂失成功，回车键返回......\n", list[vis].card);
					rewind(stdin);
					getchar();
					system("cls");
				}
				else {
					system("cls");
					printf("提示：挂失失败，原因认证失败！\t\n");
					continue;

				}
			}
			else {
				system("cls");
				printf("提示：默认管理员账户不能挂失！\t\n");
				continue;
			}
			break;
		}
		else if (a == 2)
		{
			int cardid = 0;
			printf("--------------\n认证/输入卡号：\n");
			scanf("%d", &cardid);
			user list[user_max] = { NULL };
			char pass[8];
			int num_7 = 0;
			int vis = 0;//判断标志
			file_read(list);
			for (int i = user_num() - 1; i >= 0; i--) {
				if (list[i].card == cardid)
					vis = i;
			}
			if (vis == 0)
			{
				system("cls");
				printf("卡号不存在");
				continue;
			}

			if (cardid != 18072801) {
				printf("\n\n--------------\n认证/输入密码：");
				rewind(stdin);
				gets(pass);
				if (strcmp(list[vis].pass, pass) == 0) {
					list[vis].flag = 0;
					file_save(list, user_num());
					printf("\n卡号：%d 恢复正常使用，回车键返回......\n", list[vis].card);
					rewind(stdin);
					getchar();
				}
				else {
					system("cls");
					printf("提示：挂失失败，原因认证失败！\t");

				}
			}
			else {
				system("cls");
				printf("提示：默认管理员账户不能执行此操作！\t");
			}
			break;

		}
		else {
			system("cls");
			break;
		}
	}




}
//登出系统
char out_login() {
	user* login();
	user *p = login();
	printf("\n\n------------------\n");
	printf("\tQ.返回\t回车键登出系统.......\n");
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
//记录查询
void handle_list() {
	user* login();
	user *p = login();
	char h1;
	struct tm t[2];
	printf("\n\n---------------------\n\tA.近%d条记录\tB.按时间段查询\n", take_notes_max);
	printf("键入序号：");
	rewind(stdin);
	h1 = getchar();
	int num_9 = 0;
	if (h1 == 'A') {
		system("cls");
		printf("卡号：%d 最近%d条记录\n\n", p->card, take_notes_max);
		for (int i = 0; (i < take_notes_max) && (p->list[i].handle[0] != NULL); i++)
			printf("##日期：%d年%d月%d日 %d:%d:%d\n\t操作：%s\t金额：%.2f\n", 1900 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, p->list[i].handle, p->list[i].money);
		printf("\n\n\n回车键返回........\n");
		rewind(stdin);
		getchar();
		system("cls");
	}
	else if (h1 == 'B') {
		printf("\n\n------------------------\n输入开始日期（格式：2018-07-29）：");
		scanf("%d-%d-%d", &t[0].tm_year, &t[0].tm_mon, &t[0].tm_mday);
		printf("输入结束日期：");
		scanf("%d-%d-%d", &t[1].tm_year, &t[1].tm_mon, &t[1].tm_mday);
		system("cls");
		printf("日期：%d年%d月%d日-%d年%d月%d日 的记录\n\n", t[0].tm_year, t[0].tm_mon, t[0].tm_mday, t[1].tm_year, t[1].tm_mon, t[1].tm_mday);
		for (int i = 0; (i < take_notes_max) && (p->list[i].handle[0] != NULL); i++)
			if (p->list[i].T.tm_year >= (t[0].tm_year - 1900) && p->list[i].T.tm_mon >= (t[0].tm_mon - 1) && p->list[i].T.tm_mday >= t[0].tm_mday)
				if (p->list[i].T.tm_year <= (t[1].tm_year - 1900) && p->list[i].T.tm_mon <= (t[1].tm_mon - 1) && p->list[i].T.tm_mday <= t[1].tm_mday) {
					printf("##日期：%d年%d月%d日 %d:%d:%d\n\t操作：%s\t金额：%.2f\n", 1900 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, p->list[i].handle, p->list[i].money);
					num_9++;
				}
		printf("\n\n$$共%d条记录\n", num_9);
		printf("\n\n回车键返回.......\n");
		rewind(stdin);
		getchar();
		system("cls");
	}
	else {
		system("cls");
		printf("提示：选择错误，重新选择！\t");
	}
}


//转账
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
	printf("\n\n----------------\n收款人卡号：");
	scanf("%d", &card);
	file_read(list);
	for (int i = user_num() - 1; i >= 0; i--)
		if (list[i].card == card) {
			int ii = strlen(list[i].name);
			printf("##收款人：%s\n", list[i].name);
			printf("$$输入转账金额：");
			scanf("%f", &money);
			float sum = 0;//定期存款 
			struct tm *t=time_now();
			for (int i = 0; p->list[i].handle[0] != NULL; i++)
			{
				if (strcmp(p->list[i].handle, "定期一年") == 0 || strcmp(p->list[i].handle, "定期三年") == 0 || strcmp(p->list[i].handle, "定期五年") == 0)
					sum += p->list[i].money;
		
			}
			if (money >= 0 && money <= p->balance-sum) {
				printf("\tY.确认转账\t回车键取消.........\n");
				printf("键入选择：");
				rewind(stdin);
				if (getchar() == 'Y') {
					for (ii = user_num() - 1; ii >= 0 && (list[ii].card != p->card); ii--);
					list[i].balance += money;
					p->balance -= money;
					list[ii].balance = p->balance;
					file_save(list, user_num());
					char p2[10]="转账->";
					strcat(p2,list[i].name);
					handle_save(t,money,p2);
					system("cls");
					printf("提示：转账成功！ 收款人：%d 金额：%.2f\t", card, money);
				}
				else {
					system("cls");
					printf("提示:取消转账！\t");
				}
			}
			else {
				system("cls");
				printf("提示：余额不足或者还有部分定期存款没到期，转账失败！\t");
			}
			card = 0;
			break;
		}
	if (card != 0) {
		system("cls");
		printf("提示：转账失败，原因不存在的收款人！\t");
	}
}
//利息计算
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
//存款利息查询
void interest_info()
{
	system("cls");
	printf("*********账户存款利息信息*******\n");
	printf("1.定期利率一年1.35%% \n2.定期利率三年1.55%%\n3.定期五年利率3.3%%\n4.活期利率0.55%%\n\n\n");
	user* login();
	user *p = login();
	struct tm* time_now();
	static int num_1 = 1;
	struct tm *t = time_now();
	printf("*************余额查询****************\n");
	printf("\t┌────────────────┬────────────────┬──────────────────┐\n");
	printf("\t│姓名：%-10s│卡号：%-10d│余额：%10.2f元│\n", p->name, p->card, p->balance);
	printf("\t└────────────────┴────────────────┴──────────────────┘\n\n\n");
	float interest = 0;

	for (int i = 0; p->list[i].handle[0] != NULL; i++)
	{
		if (strcmp(p->list[i].handle, "定期一年") == 0)
		{
			printf("定期一年：金额:%f   到期时间:% d年%d月%d日 %d:%d:%d  到期利息：%f\n", p->list[i].money, 1901 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(1, 0.0135, p->list[i].money));
		}
		else if (strcmp(p->list[i].handle, "定期三年") == 0)
		{
			printf("定期三年：金额:%f   到期时间:% d年%d月%d日 %d:%d:%d  到期利息：%f\n", p->list[i].money, 1903 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(3, 0.0155, p->list[i].money));
		}
		else if (strcmp(p->list[i].handle, "定期五年") == 0)
		{
			printf("定期五年：金额:%f   到期时间:% d年%d月%d日 %d:%d:%d  到期利息：%f\n", p->list[i].money, 1905 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(5, 0.033, p->list[i].money));
		}
		else if (strcmp(p->list[i].handle, "活期") == 0) {
			printf("活期：金额:%f   随时存取\n", p->list[i].money);
		}
	}
	printf("\n\n回车键返回.......\n");
	rewind(stdin);
	getchar();
	system("cls");
}
//利息结算
void interest_get()
{
	void file_read(user*);
	void file_save(user*, int);
	void handle_save(struct tm*, float, char arr[]);
	struct tm* time_now();
	int user_num();
	user* login();
	user *p = login();
	struct tm *t = time_now();//当前时间
	printf("**************利息显示************\n");
	for (int i = 0; p->list[i].handle[0] != NULL; i++)
	{
		if (strcmp(p->list[i].handle, "定期一年") == 0)
		{
			printf("定期一年：金额:%f   到期时间:% d年%d月%d日 %d:%d:%d  到期利息：%f\n", p->list[i].money, 1901 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(1, 0.0135, p->list[i].money));
		}
		else if (strcmp(p->list[i].handle, "定期三年") == 0)
		{
			printf("定期三年：金额:%f   到期时间:% d年%d月%d日 %d:%d:%d  到期利息：%f\n", p->list[i].money, 1903 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(3, 0.0155, p->list[i].money));
		}
		else if (strcmp(p->list[i].handle, "定期五年") == 0)
		{
			printf("定期五年：金额:%f   到期时间:% d年%d月%d日 %d:%d:%d  到期利息：%f\n", p->list[i].money, 1905 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(5, 0.033, p->list[i].money));
		}
		else if (strcmp(p->list[i].handle, "普通存款") == 0) {
			printf("活期：金额:%f   随时存取\n", p->list[i].money);
		}
	}
	getchar();
	printf("确认结算：Y/N?\n");
	if (getchar() == 'Y') {
		system("cls");
		for (int i = 0; p->list[i].handle[0] != NULL; i++)
		{
			if (strcmp(p->list[i].handle, "定期一年") == 0)
			{
				if (t->tm_year > p->list[i].T.tm_year + 1 || (t->tm_year == p->list[i].T.tm_year + 1 && t->tm_mon > p->list[i].T.tm_mon) || (t->tm_year == p->list[i].T.tm_year + 1 && t->tm_mon == p->list[i].T.tm_mon &&t->tm_mday >= p->list[i].T.tm_mday))
				{
					printf("正在结算:\n定期一年：金额:%f   到期时间:% d年%d月%d日 %d:%d:%d  到期利息：%f\n", p->list[i].money, 1901 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(1, 0.0135, p->list[i].money));
					int num_3 = 0;
					float money;
					user list[user_max] = { NULL };
					money = interest_money(1, 0.0135, p->list[i].money) + p->list[i].money;


					file_read(list);
					int pos = 0;
					struct tm t;
					for (num_3; list[num_3].card != p->card; num_3++);
					t = list[num_3].list[i].T;
					//找到操作的位置删除
					for (int i = 0; !(t.tm_year == 1901 + p->list[i].T.tm_year &&t.tm_mon == 1 + p->list[i].T.tm_mon && t.tm_mday == p->list[i].T.tm_mday && t.tm_hour == 8 + p->list[i].T.tm_hour && t.tm_min == p->list[i].T.tm_min && t.tm_sec == p->list[i].T.tm_sec); i++);
					for (pos = i; list[num_3].list[pos].handle[0] != NULL; pos++)
					{
						strcpy(list[num_3].list[pos].handle, list[num_3].list[pos + 1].handle);
					}
					(p->balance) += money;
					list[num_3].balance = p->balance;
					file_save(list, user_num());
					system("cls");

					printf("提示：定期结算成功! 金额：%.2f元\t", money);

				}
				else
				{
					printf("定期一年：金额:%f   到期时间:% d年%d月%d日 %d:%d:%d  到期利息：%f <<时间还未到达>>\n", p->list[i].money, 1901 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(1, 0.0135, p->list[i].money));
				}
			}
			else if (strcmp(p->list[i].handle, "定期三年") == 0)
			{
				if (t->tm_year > p->list[i].T.tm_year + 3 || (t->tm_year == p->list[i].T.tm_year + 3 && t->tm_mon > p->list[i].T.tm_mon) || (t->tm_year == p->list[i].T.tm_year + 3 && t->tm_mon == p->list[i].T.tm_mon &&t->tm_mday >= p->list[i].T.tm_mday))
				{
					printf("正在结算:\n定期3年：金额:%f   到期时间:% d年%d月%d日 %d:%d:%d  到期利息：%f\n", p->list[i].money, 1901 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(1, 0.0135, p->list[i].money));
					int num_3 = 0;
					float money;
					user list[user_max] = { NULL };
					money = interest_money(1, 0.0155, p->list[i].money) + p->list[i].money;


					file_read(list);
					int pos = 0;
					struct tm t;
					for (num_3; list[num_3].card != p->card; num_3++);
					t = list[num_3].list[i].T;
					//找到操作的位置删除
					for (int i = 0; !(t.tm_year == 1901 + p->list[i].T.tm_year &&t.tm_mon == 1 + p->list[i].T.tm_mon && t.tm_mday == p->list[i].T.tm_mday && t.tm_hour == 8 + p->list[i].T.tm_hour && t.tm_min == p->list[i].T.tm_min && t.tm_sec == p->list[i].T.tm_sec); i++);
					for (pos = i; list[num_3].list[pos].handle[0] != NULL; pos++)
					{
						strcpy(list[num_3].list[pos].handle, list[num_3].list[pos + 1].handle);
					}
					(p->balance) += money;
					list[num_3].balance = p->balance;
					file_save(list, user_num());
					system("cls");

					printf("提示：定期结算成功! 金额：%.2f元\t", money);

				}
				else
				{
					printf("定期3年：金额:%f   到期时间:% d年%d月%d日 %d:%d:%d  到期利息：%f <<时间还未到达>>\n", p->list[i].money, 1901 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(1, 0.0135, p->list[i].money));
				}
			}
			else if (strcmp(p->list[i].handle, "定期五年") == 0)
			{
				if (t->tm_year > p->list[i].T.tm_year + 5 || (t->tm_year == p->list[i].T.tm_year + 5 && t->tm_mon > p->list[i].T.tm_mon) || (t->tm_year == p->list[i].T.tm_year + 5 && t->tm_mon == p->list[i].T.tm_mon &&t->tm_mday >= p->list[i].T.tm_mday))
				{
					printf("正在结算:\n定期5年：金额:%f   到期时间:% d年%d月%d日 %d:%d:%d  到期利息：%f\n", p->list[i].money, 1901 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(1, 0.0135, p->list[i].money));
					int num_3 = 0;
					float money;
					user list[user_max] = { NULL };
					money = interest_money(1, 0.0155, p->list[i].money) + p->list[i].money;


					file_read(list);
					int pos = 0;
					struct tm t;
					for (num_3; list[num_3].card != p->card; num_3++);
					t = list[num_3].list[i].T;
					//找到操作的位置删除
					for (int i = 0; !(t.tm_year == 1901 + p->list[i].T.tm_year &&t.tm_mon == 1 + p->list[i].T.tm_mon && t.tm_mday == p->list[i].T.tm_mday && t.tm_hour == 8 + p->list[i].T.tm_hour && t.tm_min == p->list[i].T.tm_min && t.tm_sec == p->list[i].T.tm_sec); i++);
					for (pos = i; list[num_3].list[pos].handle[0] != NULL; pos++)
					{
						strcpy(list[num_3].list[pos].handle, list[num_3].list[pos + 1].handle);
					}
					(p->balance) += money;
					list[num_3].balance = p->balance;
					file_save(list, user_num());
					system("cls");

					printf("提示：定期结算成功! 金额：%.2f元\t", money);

				}
				else
				{
					printf("定期5年：金额:%f   到期时间:% d年%d月%d日 %d:%d:%d  到期利息：%f <<时间还未到达>>\n\n", p->list[i].money, 1901 + p->list[i].T.tm_year, 1 + p->list[i].T.tm_mon, p->list[i].T.tm_mday, 8 + p->list[i].T.tm_hour, p->list[i].T.tm_min, p->list[i].T.tm_sec, interest_money(1, 0.0135, p->list[i].money));
				}

			}
			else if (strcmp(p->list[i].handle, "普通存款") == 0) {
				printf("活期：金额:%f   随时存取\n", p->list[i].money);
			}
		}
	}
	else
		system("cls");


}
//用户列表，管理员
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
		printf("欢迎管理员%s\t卡号：%d\n", p->name, p->card);
		file_read(list);
		printf("\n\n");
		printf("\t┌──────┬───────────────┬───────────┬────────────┐\n");
		printf("\t│序号  │姓名           │卡号       │余额        │\n");
		for (int i = user_num() - 1; i >= 0; i--)
			if (list[i].card != 18072801) {
				printf("\t├──────┼───────────────┼───────────┼────────────┤\n");
				printf("\t│%6d│%15s│%11d│%12.2f│\n", i, list[i].name, list[i].card, list[i].balance);
			}
		printf("\t└──────┴───────────────┴───────────┴────────────┘\n");
		printf("\t\t$$共有%d条数据\n", user_num() - 1);
		printf("\n\n--------------------\n对用户操作：\n\tA.修改密码\tB.删除用户\t回车键返回上一级.......\n");
		printf("键入序号：");
		rewind(stdin);
		h1 = getchar();
		if (h1 == 'A' || h1 == 'B') {
			printf("操作用户的序号：");
			scanf("%d", &user_u);
			if (user_u >= 0 && user_u <= (user_num() - 1)) {
				if (h1 == 'A') {
					printf("输入新密码：");
					rewind(stdin);
					gets(list[user_u].pass);
					file_save(list, user_num());
					system("cls");
					printf("卡号：%d 密码修改成功！\t", list[user_u].card);
					user_list();
				}
				else {
					printf("Y.确定删除\t回车键返回.......\n");
					rewind(stdin);
					if (getchar() == 'Y') {
						for (int i = user_num() - 1; i > user_u; user_u++)
							list[user_u] = list[user_u + 1];
						file_save(list, user_num() - 1);
						system("cls");
						printf("提示：删除成功！\t");
						user_list();
					}
					else {
						system("cls");
						printf("提示：放弃删除操作！\t");
						user_list();
					}
				}
			}
			else {
				system("cls");
				printf("提示：操作失败，原因不存在该序号！\t");
				user_list();
			}
		}
		else
			system("cls");
	}
}
//时间函数,获取当前时间
/*tm返回UTC时间，转换北京时间year+1900,mon+1,hour+8*/
struct tm* time_now() {
	struct tm *p;
	time_t *timep = (time_t*)malloc(sizeof(time_t));
	time(timep);
	p = gmtime(timep);
	free(timep);
	return p;
}
//操作记录
void handle_save(struct tm *t, float money, char arr[10]) {
	void file_read(user*);
	void file_save(user*, int);
	int user_num();
	user* login();
	user *p = login();
	user *p1 = (user*)calloc(user_max, user_size);
	int num_4 = 0;
	for (num_4; p->list[num_4].handle[0] != NULL; num_4++);		//取得已存条数
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
//用户数量
int user_num() {
	void file_read(user*);
	int num_5 = 0;
	user list[user_max] = { NULL };
	file_read(list);
	while ((list[num_5].name[0]) != NULL)
		num_5++;
	return num_5;
}
//用户信息加密（凯撒密码）
void data_j(user *p) {
	for (int i = 0; i < strlen(p->name); i++)
		p->name[i] += 2;
	for (int i = 0; i < 6; i++)
		p->pass[i] += 5;
}
//用户信息解密（凯撒密码）
void data_i(user *p) {
	for (int i = 0; i < strlen(p->name); i++)
		p->name[i] -= 2;
	for (int i = 0; i < 6; i++)
		p->pass[i] -= 5;
}

/*文件操作*/
//文件检测
void file_true() {
	void file_save(user *p, int count);
	FILE *data = fopen(data_file, "rb");
	if (data == NULL) {
		user p = { NULL };
		strcpy(p.name, "test");
		p.card = 18072801;
		strcpy(p.pass, "123456");
		p.balance = 100;		//定义一条测试数据
		file_save(&p, 1);		//保存测试的数据
	}
	else
		fclose(data);
}
//写入文件
void file_save(user *p, int count) {
	for (int i = 0; i < count; i++)
		data_j(p + i);
	FILE *data = fopen(data_file, "wb");
	fwrite(p, user_size, count, data);
	fclose(data);
}
//读取文件
void file_read(user *p) {
	void data_i(user*);
	FILE *data = fopen(data_file, "rb");
	fread(p, user_size, user_max, data);
	for (int i = 0; (p + i)->name[0] != NULL; i++)
		data_i(p + i);
	fclose(data);
}

//界面
/*
**显示菜单

*/
//初始化窗口

//初始界面
char face_1() {
	char h1;
	printf("\n\n\n\n\n\t\t\t\t----------------------\n");
	printf("\t\t\t\t *奥力给银行管理系统*\n");
	printf("\t\t\t\t----------------------");
	printf("\n\n\n\n\t\t\t\tA.进入系统\tB.新用户\n\n\t\t\t\tQ.退出系统\n");
	printf("\n\n--------------------------------\n\t\t键入序号：");
	rewind(stdin);		//清除输入缓存
	h1 = getchar();
	if (h1 == 'A' || h1 == 'B' || h1 == 'Q')
		return h1;
	else {
		system("cls");
		printf("提示：选择有误，重新选择！");
	}

}
//登录后界面
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
		printf("欢迎用户：%s\n", p->name);
		printf("\n\n\n\n\t\t\tA.余额查询\tB.取款\n");
		printf("\n\t\t\tC.修改密码\tD.存款\n");
		printf("\n\t\t\tE.名下账户\tF.注销\n");
		printf("\n\t\t\tG.登出系统\tH.记录查询\n");
		printf("\n\t\t\tQ.返回上一级\tI.转账\n");
		printf("\n\t\t\tJ.利息查询\tK.利息结算\n");
		if (p->card == 18072801)
		{
			printf("\n\t\t\tU.用户列表 \t L.挂失处理\n");
		}
		printf("\n----------------\n键入序号：");
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
			printf("提示：选择有误，重新选择！\n");
		}
	}
}


/*主函数*/
/*
**功能实现：银行系统
*/
//主函数
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
				printf("提示：本卡已经挂失，联系管理员！\n");
				p->name[0] = NULL;
			}
		}
		else if (h1 == 'B')
			add_user();
	}
	return 0;
}
