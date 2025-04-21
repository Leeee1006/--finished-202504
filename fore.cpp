#include "fore.h"
void buildWindow()
{//��������
	IMAGE img;
	loadimage(&img, "cai.jpg");
	putimage(0, 0, &img);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	outtextxy(0, 0, "��վʱ��:");
	char buf[50] = "";
	strcpy_s(buf, 50, formatTime(getStationTime()));
	buf[10] = '\0';
	outtextxy(90, 0, buf);
}
void messbox(const char* arr)
{//����char*����,���ڽ����ֽ��ַ���ת��Ϊ���ַ��ַ�����wchar_t ���͵��ַ�����
	wchar_t wtext[256];
	int len = MultiByteToWideChar(CP_ACP, 0, arr, -1, wtext, 256);  // GBK ����
	if (len > 0)
	{
		HWND hnd = GetHWnd();
		MessageBoxW(hnd, wtext, L"��ʾ", MB_OK | MB_ICONINFORMATION);
	}
}
void isinputbox(int x, int y, int flag, ExMessage m, char* s)
{//��ͨ�Ի���
	if (m.message == WM_LBUTTONDOWN && m.x >= x && m.x <= x + 200 && m.y >= y && m.y <= y + 30)
	{
		setfillcolor(WHITE);
		fillrectangle(x, y, x + 200, y + 30);//����
		InputBox(s, ADDRESS, "������");
		settextcolor(BLACK);
		settextstyle(20, 0, FONT);
		setbkmode(TRANSPARENT);
		int width = 200 / 2 - textwidth(s) / 2;
		int height = 30 / 2 - textheight(s) / 2;
		if (flag > 0)
		{//����
			if (validatePassword(s, flag) == 0)
			{
				messbox("��ʽ����");
				s[0] = '\0';
			}
			else
			{
				outtextxy(x + width, y + height, s);
				return;
			}
		}
		else if (flag == 0)
		{//6������
			if (isChineseString(s, 12) == 0)
			{
				messbox("��ʽ����");
				s[0] = '\0';
				return;
			}
			else
			{
				outtextxy(x + width, y + height, s);
				return;
			}
		}
		else if (flag == -1)
		{//�ַ���ת����,�������
			double num = (double)atof(s);
			if (num <= 0 || validateVolume(num) == 0)
			{
				messbox("�����ʽ����");
			}
			else
			{
				s[9] = '\0';
				outtextxy(x + width, y + height, s);
			}
		}
		else if (flag == -2)
		{//�ַ���ת����,��������
			double num = (double)atof(s);
			if (num <= 0 || validateWeight(num) == 0)
			{
				messbox("������ʽ����");
			}
			else
			{
				s[9] = '\0';
				outtextxy(x + width, y + height, s);
			}
		}
	}
}
void isinputboxAdress(int x, int y, ExMessage m, char* s)
{//���Ի���    ��ַ�Ի���
	if (m.message == WM_LBUTTONDOWN && m.x >= x && m.x <= x + 500 && m.y >= y && m.y <= y + 30)
	{
		setfillcolor(WHITE);
		fillrectangle(x, y, x + 500, y + 30);//����
		InputBox(s, ADDRESS, "������");
		settextcolor(BLACK);
		settextstyle(20, 0, FONT);
		setbkmode(TRANSPARENT);
		int width = 500 / 2 - textwidth(s) / 2;
		int height = 30 / 2 - textheight(s) / 2;
		if (isChineseString(s, ADDRESS - 1) == 0)
		{
			messbox("��ʽ����");
			s[0] = '\0';
			return;
		}
		else
		{
			outtextxy(x + width, y + height, s);
			return;

		}
	}
}
void inputbox(int x, int y)
{
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	fillrectangle(x, y, x + 200, y + 30);
}
void inputboxAdress(int x, int y)
{
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	fillrectangle(x, y, x + 500, y + 30);
}
void drawButton(struct button* pb)
{//����ť
	setlinecolor(BLACK);
	setfillcolor(pb->curcolor);
	fillrectangle(pb->x, pb->y, pb->x + 150, pb->y + 50);
	settextcolor(WHITE);
	settextstyle(30, 0, FONT);
	setbkmode(TRANSPARENT);
	int width = 150 / 2 - textwidth(pb->text) / 2;
	int height = 50 / 2 - textheight(pb->text) / 2;
	outtextxy(pb->x + width, pb->y + height, pb->text);
}
void drawChioce(struct choice* ch)
{
	setlinecolor(BLACK);
	setfillcolor(ch->fillcolor);
	fillcircle(ch->x, ch->y + 15, 10);
	settextcolor(BLACK);
	settextstyle(30, 0, FONT);
	setbkmode(TRANSPARENT);
	outtextxy(ch->x + 15, ch->y, ch->text);
}
void label(int x, int y, const char* arr)
{//��������ֱ�ǩ
	settextcolor(BLACK);
	settextstyle(30, 0, FONT);
	setbkmode(TRANSPARENT);
	outtextxy(x, y, arr);
}
void label(int x, int y, double number)
{//���غ�������д���֣���ɫΪ��ɫ
	char arr[50] = { '\0' };
	sprintf(arr, "%.2f", number);
	label(x, y, arr);
}
void text(int x, int y, const char* arr)
{//��д���֣�������ɫΪ��ɫ
	settextcolor(BLACK);
	settextstyle(18, 0, FONT);
	setbkmode(TRANSPARENT);
	outtextxy(x, y, arr);
}
void textRed(int x, int y, const char* arr)
{//��д����,������ɫΪ��ɫ
	settextcolor(RED);
	settextstyle(18, 0, FONT);
	setbkmode(TRANSPARENT);
	outtextxy(x, y, arr);
}
void text(int x, int y, int number)
{//���غ�������д���֣���ɫΪ��ɫ
	char arr[50] = { '\0' };
	sprintf(arr, "%d", number);
	text(x, y, arr);
}
void text(int x, int y, float number)
{//���غ�������д���֣���ɫΪ��ɫ
	char arr[50] = { '\0' };
	sprintf(arr, "%.2f", number);
	text(x, y, arr);
}
void textRed(int x, int y, int number)
{//���غ�������д���֣���ɫΪ��ɫ
	char arr[50] = { '\0' };
	sprintf(arr, "%d", number);
	textRed(x, y, arr);
}
void textRed(int x, int y, float number)
{//���غ�������д���֣���ɫΪ��ɫ
	char arr[50] = { '\0' };
	sprintf(arr, "%.2f", number);
	textRed(x, y, arr);
}
bool isInButton(struct button* pb, ExMessage m)
{
	if (m.x >= pb->x && m.x <= pb->x + 150 && m.y >= pb->y && m.y <= pb->y + 50)
	{
		pb->curcolor = pb->incolor;
		return true;
	}
	pb->curcolor = pb->outcolor;
	return false;
}
bool isInChoice(struct choice* ch, ExMessage m)
{
	if (m.x >= ch->x - 10 && m.x <= ch->x + 10 && m.y >= ch->y + 5 && m.y <= ch->y + 25)
	{
		return true;
	}
	return false;
}
bool isClickButton(struct button* pb, ExMessage m)
{
	if (isInButton(pb, m) && m.message == WM_LBUTTONDOWN)
	{
		return true;
	}
	return false;
}
bool isClickChoice(struct choice* ch, ExMessage m)
{
	if (isInChoice(ch, m) && m.message == WM_LBUTTONDOWN)
	{
		ch->fillcolor = ch->clickcolor;
		return true;
	}
	return false;
}
struct button* button(int x, int y, const char* arr)
{
	struct button* pb = (struct button*)malloc(sizeof(struct button));
	pb->x = x;
	pb->y = y;
	pb->incolor = RGB(90, 209, 196);
	pb->outcolor = RGB(87, 62, 148);
	pb->curcolor = RGB(87, 62, 148);
	size_t length = strlen(arr) + 1;
	pb->text = (char*)malloc(sizeof(char) * length);
	strcpy_s(pb->text, length, arr);
	return pb;
}
struct choice* choice(int x, int y, const char* arr)
{
	struct choice* ch = (struct choice*)malloc(sizeof(struct choice));
	ch->x = x;
	ch->y = y;
	ch->fillcolor = WHITE;
	ch->clickcolor = RGB(90, 209, 196);
	ch->noclickcolor = WHITE;
	size_t length = strlen(arr) + 1;
	ch->text = (char*)malloc(sizeof(char) * length);
	strcpy_s(ch->text, length, arr);
	return ch;
}
int pagingWindow(void (*currentPage)(int, long long, char*), int currentpage, long long totalNumber, char* searchNum)
{//��װ��ҳҳ�溯��
	buildWindow();
	int startpage = 1;//��ȡ��һҳ
	currentpage = startpage;//��ǰҳ��Ϊ��һҳ
	long long lastpage;
	if (totalNumber % 9 != 0)
	{
		lastpage = totalNumber / 9 + 1;
	}
	else
	{
		lastpage = totalNumber / 9;
	}//��ȡ���һҳ
	currentPage(startpage, totalNumber, searchNum);// ��ʾ��һҳ������
	struct button* p1 = button(850, 600, "����");
	struct button* p2 = button(200, 550, "��ҳ");
	struct button* p3 = button(350, 550, "��һҳ");
	struct button* p4 = button(500, 550, "��һҳ");
	struct button* p5 = button(650, 550, "ĩҳ");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		drawButton(p4);
		drawButton(p5);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				cleardevice();
				flag = 1;
				free(p1);
				free(p2);
				free(p3);
				free(p4);
				free(p5);
				return flag;
			}
			if (isClickButton(p2, m))
			{//��ҳ
				if (currentpage == startpage)
				{//������ҳ
					;
				}
				else
				{
					currentpage = 1;
					currentPage(currentpage, totalNumber, searchNum);
				}
			}
			if (isClickButton(p3, m))
			{//��һҳ
				if (currentpage == startpage)
				{//������ҳ
					;
				}
				else
				{
					currentpage--;
					currentPage(currentpage, totalNumber, searchNum);
				}
			}
			if (isClickButton(p4, m))
			{//��һҳ
				if (currentpage != lastpage)
				{//��ǰ�������һҳ
					currentpage++;
					currentPage(currentpage, totalNumber, searchNum);
				}
				else
				{
					;
				}
			}
			if (isClickButton(p5, m))
			{//ĩҳ
				if (currentpage != lastpage)
				{//��ǰ�������һҳ
					currentpage = lastpage;
					currentPage(currentpage, totalNumber, searchNum);
				}
				else
				{
					;
				}
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
}
bool searchWindow(const char* arr, char* search, int flag)
{
	buildWindow();
	label(300, 150, arr);
	struct button* p1 = button(650, 450, "ȷ��");
	struct button* p2 = button(350, 450, "����");
	inputbox(450, 300);
	ExMessage m;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		if (peekmessage(&m, EX_MOUSE))
		{
			isinputbox(450, 300, flag, m, search);
			if (isClickButton(p1, m))
			{
				if (strlen(search) == 0)
				{
					messbox("�����ʽ��������������");
				}
				else
				{
					cleardevice();
					free(p1);
					return true;
				}
			}
			if (isClickButton(p2, m))
			{
				cleardevice();
				free(p2);
				return false;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
}
//              *******************************************************************************************��¼����**********************************************************
//��¼+ע��
void registerAndLogin()
{//��¼+ע��
	buildWindow();
	struct button* p1 = button(450, 200, "ע��");
	struct button* p2 = button(450, 400, "��¼");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	if (flag == 1)
	{
		free(p1);
		cleardevice();
		Register();
	}
	if (flag == 2)
	{
		free(p2);
		cleardevice();
		login();
	}
}
//��¼����
void login()
{//��¼����	
	buildWindow();
	label(300, 200, "�ֻ��ţ�");
	label(300, 300, "���룺");
	inputbox(480, 300);
	inputbox(480, 200);
	struct button* p1 = button(350, 400, "����");
	struct button* p2 = button(550, 400, "��¼");
	BeginBatchDraw();
	ExMessage m;
	int flag = 0;
	char password[PASSWORD] = { 0 };
	char phoneNumber[PHONE] = { 0 };
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		if (peekmessage(&m, EX_MOUSE))
		{
			isinputbox(480, 200, 11, m, phoneNumber);
			isinputbox(480, 300, 6, m, password);
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	if (flag == 1)
	{
		free(p1);
		cleardevice();
		registerAndLogin();
	}
	if (flag == 2)
	{
		free(p2);
		if (strncmp(phoneNumber, "18336109923", PHONE) == 0 && strncmp(password, "666888", PASSWORD) == 0)//����Ա
		{
			cleardevice();
			managerMenu();
			operaterWindow();
		}
		if (strncmp(phoneNumber, "16668219582", PHONE) == 0 && strncmp(password, "000111", PASSWORD) == 0)//��ӪԱ
		{
			cleardevice();
			operaterWindow();
		}
		else
		{
			g_currentUser = userLogin(phoneNumber, password);
			if (g_currentUser == NULL)
			{
				messbox("�ֻ��Ż��������");
				cleardevice();
				login();
			}
			cleardevice();
			userMenu();
		}
	}
}
//ע�����
void Register()
{ //ע�����
	buildWindow();
	label(300, 100, "�ǳ�:");
	label(300, 200, "�ֻ���:");
	label(300, 300, "����:");

	inputbox(480, 100);
	label(850, 100, "����(6������)");
	inputbox(480, 200);
	label(850, 200, "11λ����");
	inputbox(480, 300);
	label(850, 300, "6λ����");
	struct button* p1 = button(350, 400, "����");
	struct button* p2 = button(550, 400, "ע��");
	BeginBatchDraw();
	ExMessage m;
	int flag = 0;
	char userName[NAME] = { 0 };
	char password[PASSWORD] = { 0 };
	char phoneNumber[PHONE] = { 0 };
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		if (peekmessage(&m, EX_MOUSE))
		{
			isinputbox(480, 100, 0, m, userName);
			isinputbox(480, 200, 11, m, phoneNumber);
			isinputbox(480, 300, 6, m, password);
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	if (flag == 1)
	{
		free(p1);
		cleardevice();
		registerAndLogin();
	}
	if (flag == 2)
	{
		free(p2);
		if (strlen(userName) > 0 && strlen(phoneNumber) > 0 && strlen(password) > 0)
		{
			if (userRegister(userName, phoneNumber, password) == 0)
			{
				messbox("�ֻ����Ѵ���");
				cleardevice();
				Register();
			}
			else
			{
				cleardevice();
				login();
			}
		}
		else
		{
			messbox("������Ч������������");
			cleardevice();
			Register();
		}
	}
}
//******************************************************************************************�û�����********************************************************************************
//�û��׽��棨�˵����棩
void userMenu()
{//�û��׽���
	buildWindow();
	struct button* p1 = button(450, 120, "������Ϣ");
	struct button* p2 = button(450, 230, "��Ҫ�ļ�");
	struct button* p3 = button(450, 340, "��Ҫȡ��");
	struct button* p4 = button(450, 450, "��������");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		drawButton(p4);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;
			}
			if (isClickButton(p4, m))
			{
				flag = 4;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag) {
	case 1:
		free(p1);
		packageInfoMenu();
		break;
	case 2:
		free(p2);
		sendPackage();
		break;
	case 3:
		free(p3);
		pickupPackageMenu();
		break;
	case 4:
		free(p4);
		personalCenter();
		break;
	default:
		break;
	}
}
//*****������Ϣ
//������Ϣ�˵�
void packageInfoMenu()
{//������Ϣ
	buildWindow();
	label(50, 50, "�ļ���Ϣ");
	struct button* p1 = button(100, 180, "�Ѽĳ�");
	struct button* p2 = button(400, 180, "���ĳ�");
	struct button* p3 = button(700, 180, "��ȡ��");
	label(50, 300, "ȡ����Ϣ");
	struct button* p4 = button(100, 430, "��ǩ��");
	struct button* p5 = button(400, 430, "��ȡ");
	struct button* p6 = button(700, 430, "����");
	struct button* p7 = button(850, 550, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		drawButton(p4);
		drawButton(p5);
		drawButton(p6);
		drawButton(p7);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;
			}
			if (isClickButton(p4, m))
			{
				flag = 4;
				break;
			}
			if (isClickButton(p5, m))
			{
				flag = 5;
				break;
			}
			if (isClickButton(p6, m))
			{
				flag = 6;
				break;
			}
			if (isClickButton(p7, m))
			{
				flag = 7;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		sortPackagesByTime(2);
		packageShippedMenu();
		break;
	case 2:
		free(p2);
		sortPackagesByTime(0);
		packageOrderedMenu();
		break;
	case 3:
		free(p3);
		sortPackagesByTime(5);
		packageCanceledMenu();
		break;
	case 4:
		free(p4);
		sortPackagesByTime(3);
		packageDeliveredMenu();
		break;
	case 5:
		free(p5);
		sortPackagesByTime(1);
		packagePendingMenu();
		break;
	case 6:
		free(p6);
		sortPackagesByTime(4);
		packageRefusedMenu();
		break;
	case 7:
		free(p7);
		userMenu();
		break;
	default:
		break;
	}
}
//�Ѽĳ���Ϣ
void packageShippedMenu()
{//�Ѽĳ�
	buildWindow();
	int currentpage = 0;
	long long packageShippedTotalNumber = 0;
	if (pagingWindow(showPackageShippedWindow, currentpage, getPackageShippedNum(g_currentUser->phoneNumber, packageShippedTotalNumber), g_currentUser->phoneNumber) == 1)
	{
		packageInfoMenu();
	}
}//�Ѽĳ�
//���ĳ���Ϣ
void packageOrderedMenu()
{//���ĳ�
	buildWindow();
	struct button* p1 = button(450, 150, "��ѯ��Ϣ");
	struct button* p2 = button(450, 350, "ȡ���ļ�");
	struct button* p3 = button(850, 550, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		packageOrderedInfo();
		break;
	case 2:
		free(p2);
		cancelPackageWindow();
		break;
	case 3:
		free(p3);
		packageInfoMenu();
		break;
	default:
		break;
	}
}
void packageOrderedInfo()
{//��ѯ��Ϣ
	buildWindow();
	int currentpage = 0;
	long long packageOrderedTotalNumber = 0;
	if (pagingWindow(showPackageOrderedWindow, currentpage, getPackageOrderedNum(g_currentUser->phoneNumber, packageOrderedTotalNumber), g_currentUser->phoneNumber) == 1)
	{
		packageOrderedMenu();
	}
}
void cancelPackageWindow()
{//ȡ���ļ�
	char trackingNum[TRACKING_NUM] = { '\0' };
	if (searchWindow("������Ҫȡ���ļ������Ŀ�ݵ���", trackingNum, 10))
	{
		cancelPackage(trackingNum);
		cancelPackageWindow();
	}
	else
	{
		packageOrderedMenu();
	}
}
//��ȡ����Ϣ
void packageCanceledMenu()
{//��ȡ��
	buildWindow();
	int currentpage = 0;
	long long packageCanceledTotalNumber = 0;
	if (pagingWindow(showPackageCanceledWindow, currentpage, getPackageCanceledNum(g_currentUser->phoneNumber, packageCanceledTotalNumber), g_currentUser->phoneNumber) == 1)
	{
		packageInfoMenu();
	}
}
//��ǩ����Ϣ
void packageDeliveredMenu()
{//��ǩ��
	buildWindow();
	int currentpage = 0;
	long long packageDeliveredTotalNumber = 0;
	if (pagingWindow(showPackageDeliveredWindow, currentpage, getPackageDeliveredNum(g_currentUser->phoneNumber, packageDeliveredTotalNumber), g_currentUser->phoneNumber) == 1)
	{
		packageInfoMenu();
	}
}
//��ȡ��Ϣ
void packagePendingMenu()
{//��ȡ�˵�
	buildWindow();
	struct button* p1 = button(450, 150, "��ѯ��Ϣ");
	struct button* p2 = button(450, 350, "�ͻ���¥");
	struct button* p3 = button(850, 550, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		packagePendingInfo();
		break;
	case 2:
		free(p2);
		packagePendWindow();
		break;
	case 3:
		free(p3);
		packageInfoMenu();
		break;
	default:
		break;
	}
}
void packagePendingInfo()
{//��ȡ��Ϣ
	buildWindow();
	int currentpage = 0;
	long long packagePendingTotalNumber = 0;
	if (pagingWindow(showPackagePendingWindow, currentpage, getPackagePendingNum(g_currentUser->phoneNumber, packagePendingTotalNumber), g_currentUser->phoneNumber) == 1)
	{
		packagePendingMenu();
	}
}
void packagePendWindow()
{//�ͻ���¥����
	buildWindow();
	label(200, 150, "��ݵ��ţ�");
	inputbox(450, 150);
	char trackingNum[TRACKING_NUM] = { '\0' };

	label(200, 350, "�����ַ��");
	inputbox(450, 350);
	char receiverAddress[ADDRESS] = { '\0' };
	label(700, 350, "������������");
	struct button* p1 = button(650, 450, "�µ�");
	struct button* p2 = button(350, 450, "����");
	ExMessage m;
	BeginBatchDraw();
	int flag = 0;
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		if (peekmessage(&m, EX_MOUSE))
		{
			isinputbox(450, 150, 10, m, trackingNum);
			isinputbox(450, 350, 0, m, receiverAddress);
			if (isClickButton(p1, m))
			{
				if (strlen(receiverAddress) == 0 || strlen(trackingNum) == 0)
				{
					messbox("�����ʽ��������������");
				}
				else
				{
					flag = 1;
					break;
				}
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	if (flag == 1)
	{
		deliverToHomePackage(trackingNum, receiverAddress);
		free(p1);
		cleardevice();
		packagePendWindow();
	}
	if (flag == 2)
	{
		free(p2);
		cleardevice();
		packagePendingMenu();
	}
}
//������Ϣ
void packageRefusedMenu()
{//����
	buildWindow();
	struct button* p1 = button(450, 150, "��ѯ��Ϣ");
	struct button* p2 = button(450, 350, "��Ҫ����");
	struct button* p3 = button(850, 550, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		packageRefusedInfo();
		break;
	case 2:
		free(p2);
		packageRefusedWindow();
		break;
	case 3:
		free(p3);
		packageInfoMenu();
		break;
	default:
		break;
	}
}
void packageRefusedInfo()
{//������Ϣ
	buildWindow();
	int currentpage = 0;
	long long packageRefusedTotalNumber = 0;
	if (pagingWindow(showPackageRefusedWindow, currentpage, getPackageRefusedNum(g_currentUser->phoneNumber, packageRefusedTotalNumber), g_currentUser->phoneNumber) == 1)
	{
		packageRefusedMenu();
	}
}
void packageRefusedWindow()
{
	//��Ҫ����
	char trackingNum[TRACKING_NUM] = { '\0' };
	if (searchWindow("������Ҫ���հ����Ŀ�ݵ���", trackingNum, 10))
	{
		refusePackage(trackingNum);
		packageRefusedWindow();
	}
	else
	{
		packageRefusedMenu();
	}
}
//********��Ҫȡ��
void pickupPackageMenu()
{//��Ҫȡ��
	char trackingNum[TRACKING_NUM] = { '\0' };
	if (searchWindow("������Ҫȡ�������Ŀ�ݵ���", trackingNum, 10))
	{
		pickupPackage(trackingNum);
		pickupPackageMenu();
	}
	else
	{
		userMenu();
	}
}
//*****��Ҫ�ļ�
void sendPackage()
{//��Ҫ�ļ�
	buildWindow();
	struct button* p1 = button(250, 600, "����");
	struct button* p2 = button(550, 600, "��һ��");
	label(50, 50, "��������:");
	char packageName[NAME] = { '\0' };
	inputbox(200, 50);
	text(400, 50, "(����������)");

	label(500, 50, "����:");
	char packageweight[DIGITS] = { '\0' };
	double weight = 0.0;
	inputbox(650, 50);
	text(850, 50, "(ǧ��)");

	label(50, 120, "�������:");
	char packagevolume[DIGITS] = { '\0' };
	inputbox(200, 120);
	double volume = 0.0;
	text(400, 120, "(������)");

	label(500, 120, "�ռ��˵绰");
	char receiverPhone[PHONE] = { '\0' };
	inputbox(650, 120);

	label(50, 190, "�ռ���ַ:");
	char receiverAddress[ADDRESS] = { '\0' };
	inputboxAdress(200, 190);

	label(50, 260, "�����ַ:");
	char dormAddress[ADDRESS] = { '\0' };
	inputboxAdress(200, 260);
	label(800, 260, "(�Ǳ���)");

	label(250, 410, "�������:");
	int shippingMethodOption = -1;
	struct choice* ch1 = choice(400, 410, "���");
	struct choice* ch2 = choice(500, 410, "��ͨ");
	struct choice* ch3 = choice(600, 410, "����");

	label(250, 480, "��Ʒ����:");
	int packageTypeOption = -1;
	struct choice* ch4 = choice(400, 480, "��ͨ");
	struct choice* ch5 = choice(500, 480, "����");
	struct choice* ch6 = choice(600, 480, "����");

	label(250, 550, "�ļ���ʽ:");
	int homeSentOption = -1;
	struct choice* ch7 = choice(400, 550, "�Լ�");
	struct choice* ch8 = choice(500, 550, "����ȡ��");

	label(250, 340, "�Ż�ȯ");
	int couponOption = -1;
	struct choice* ch9 = choice(400, 340, "ʹ��");
	struct choice* ch10 = choice(500, 340, "����");

	BeginBatchDraw();
	ExMessage m;
	int flag = 0;
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawChioce(ch1);
		drawChioce(ch2);
		drawChioce(ch3);
		drawChioce(ch4);
		drawChioce(ch5);
		drawChioce(ch6);
		drawChioce(ch7);
		drawChioce(ch8);
		drawChioce(ch9);
		drawChioce(ch10);
		if (peekmessage(&m, EX_MOUSE))
		{
			isinputboxAdress(200, 260, m, dormAddress);
			isinputboxAdress(200, 190, m, receiverAddress);
			isinputbox(650, 50, -2, m, packageweight);
			weight = (double)atof(packageweight);
			isinputbox(200, 50, 0, m, packageName);
			isinputbox(200, 120, -1, m, packagevolume);
			volume = (double)atof(packagevolume);
			isinputbox(650, 120, 11, m, receiverPhone);
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickChoice(ch1, m))
			{
				shippingMethodOption = 1;
				ch2->fillcolor = ch2->noclickcolor;
				ch3->fillcolor = ch3->noclickcolor;
			}
			if (isClickChoice(ch2, m))
			{
				shippingMethodOption = 0;
				ch1->fillcolor = ch1->noclickcolor;
				ch3->fillcolor = ch3->noclickcolor;
			}
			if (isClickChoice(ch3, m))
			{
				shippingMethodOption = 2;
				ch2->fillcolor = ch2->noclickcolor;
				ch1->fillcolor = ch1->noclickcolor;
			}

			if (isClickChoice(ch4, m))
			{
				packageTypeOption = 0;
				ch5->fillcolor = ch5->noclickcolor;
				ch6->fillcolor = ch6->noclickcolor;
			}
			if (isClickChoice(ch5, m))
			{
				packageTypeOption = 2;
				ch4->fillcolor = ch4->noclickcolor;
				ch6->fillcolor = ch6->noclickcolor;
			}
			if (isClickChoice(ch6, m))
			{
				packageTypeOption = 1;
				ch4->fillcolor = ch4->noclickcolor;
				ch5->fillcolor = ch5->noclickcolor;
			}

			if (isClickChoice(ch7, m))
			{
				homeSentOption = 1;//�Լ�
				ch8->fillcolor = ch8->noclickcolor;
			}
			if (isClickChoice(ch8, m))
			{
				homeSentOption = 2;//����ȡ��
				ch7->fillcolor = ch7->noclickcolor;
			}

			if (isClickChoice(ch9, m))
			{
				couponOption = 1;
				ch10->fillcolor = ch10->noclickcolor;
			}
			if (isClickChoice(ch10, m))
			{
				couponOption = 2;
				ch9->fillcolor = ch9->noclickcolor;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	if (flag == 1)
	{
		free(p1);
		cleardevice();
		userMenu();
	}
	if (flag == 2)
	{
		free(p2);
		if (homeSentOption == -1)//
		{
			messbox("��Ϣδ��д����");
			cleardevice();
			sendPackage();
		}
		if (homeSentOption == 1)//�Լ�
		{
			if (strlen(receiverAddress) == 0 || strlen(packageweight) == 0 || strlen(packageName) == 0 || strlen(packagevolume) == 0 || strlen(receiverPhone) == 0 ||
				(ch1->fillcolor == WHITE && ch2->fillcolor == WHITE && ch3->fillcolor == WHITE) || (ch4->fillcolor == WHITE && ch5->fillcolor == WHITE && ch6->fillcolor == WHITE)
				|| (ch7->fillcolor == WHITE && ch8->fillcolor == WHITE) || (ch9->fillcolor == WHITE && ch10->fillcolor == WHITE))
			{//��Ϣ��д������
				messbox("��Ϣδ��д����");
				cleardevice();
				sendPackage();
			}
		}
		if (homeSentOption == 2)
		{
			if (strlen(dormAddress) == 0 || strlen(receiverAddress) == 0 || strlen(packageweight) == 0 || strlen(packageName) == 0 || strlen(packagevolume) == 0 || strlen(receiverPhone) == 0 ||
				(ch1->fillcolor == WHITE && ch2->fillcolor == WHITE && ch3->fillcolor == WHITE) || (ch4->fillcolor == WHITE && ch5->fillcolor == WHITE && ch6->fillcolor == WHITE)
				|| (ch7->fillcolor == WHITE && ch8->fillcolor == WHITE) || (ch9->fillcolor == WHITE && ch10->fillcolor == WHITE))
			{//��Ϣ��д������
				messbox("��Ϣδ��д����");
				cleardevice();
				sendPackage();
			}
		}
		if (strcmp(receiverPhone, g_currentUser->phoneNumber) == 0)// ȡ�����ֻ�����ļ����ֻ�����ͬ
		{
			messbox("ȡ�����ֻ��Ų�����ļ����ֻ�����ͬ�����������룡");
			cleardevice();
			sendPackage();
		}
		if (couponOption == 1 && g_currentUser->couponCount == 0)
		{
			messbox("�Ż�ȯ��������");
			cleardevice();
			sendPackage();
		}
		if (strcmp(receiverAddress, "�����ѧ��") == 0)	//ȡ����ַ��ļ���ַ��ͬ
		{
			messbox("ȡ����ַ������ļ���ַ��ͬ�����������룡");
			cleardevice();
			sendPackage();
		}
		else
		{
			sendPackageInfo(packageName, receiverAddress, receiverPhone, dormAddress, weight, volume, shippingMethodOption,
				packageTypeOption, homeSentOption, couponOption);
			cleardevice();
			sendPackage();
		}
	}
}
//****��������
void personalCenter()
{//��������
	buildWindow();
	struct button* p1 = button(450, 100, "�����");
	struct button* p2 = button(450, 200, "��Ա����");
	struct button* p3 = button(450, 300, "�Żݸ���");
	struct button* p4 = button(450, 400, "���͹���");
	struct button* p5 = button(450, 500, "�˳���¼");
	struct button* p6 = button(850, 550, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		drawButton(p4);
		drawButton(p5);
		drawButton(p6);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;
			}
			if (isClickButton(p4, m))
			{
				flag = 4;
				break;
			}
			if (isClickButton(p5, m))
			{
				flag = 5;
				break;
			}
			if (isClickButton(p6, m))
			{
				flag = 6;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		showIdentityCode();
		break;
	case 2:
		free(p2);
		userUpgrade();
		break;
	case 3:
		free(p3);
		exchangeCoupons();
		break;
	case 4:
		free(p4);
		sendTicket();
		break;
	case 5:
		free(p5);
		g_currentUser = NULL;
		login();
		break;
	case 6:
		free(p6);
		userMenu();
		break;
	default:
		break;
	}
}
void showIdentityCode()
{//����봰��
	buildWindow();
	label(200, 250, "����룺");
	label(450, 250, g_currentUser->identityCode);
	ExMessage m;
	int flag = 0;
	struct button* p = button(850, 550, "����");
	BeginBatchDraw();
	while (1)
	{
		drawButton(p);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p, m))
			{
				cleardevice();
				flag = 1;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	if (flag == 1)
	{
		free(p);
		personalCenter();
	}

}
void userUpgrade()
{//��Ա����
	buildWindow();
	if (g_currentUser->userType == VIP)
	{
		struct button* p = button(500, 600, "����");
		label(200, 200, "���������Ļ�Ա��");
		ExMessage m;
		int flag = 0;
		BeginBatchDraw();
		while (1)
		{
			drawButton(p);
			if (peekmessage(&m, EX_MOUSE))
			{
				if (isClickButton(p, m))
				{
					cleardevice();
					flag = 1;
					break;
				}
			}
			FlushBatchDraw();
		}
		EndBatchDraw();
		if (flag == 1)
		{
			free(p);
			personalCenter();
		}
	}
	else
	{
		label(200, 200, "���Ƿ�Ը�⻨��300Ԫ��ֵ��Ա��");
		struct button* p1 = button(250, 600, "����");
		struct button* p2 = button(550, 600, "��ֵ");
		ExMessage m;
		int flag = 0;
		BeginBatchDraw();
		while (1)
		{
			drawButton(p1);
			drawButton(p2);
			if (peekmessage(&m, EX_MOUSE))
			{
				if (isClickButton(p1, m))
				{
					flag = 1;
					break;
				}
				if (isClickButton(p2, m))
				{
					flag = 2;
					break;
				}
			}
			FlushBatchDraw();
		}
		EndBatchDraw();
		if (flag == 1)
		{
			free(p1);
			cleardevice();
			personalCenter();
		}
		if (flag == 2)
		{
			free(p2);
			userupgrade();
			cleardevice();
			personalCenter();
		}
	}
}
void exchangeCoupons()
{//�Żݸ���
	buildWindow();
	label(100, 200, "��ǰ����ֵ��");
	label(300, 200, g_currentUser->experience);
	label(100, 300, "�һ��Ż�ȯ��Ҫ����10�㾭��ֵ");
	struct button* p1 = button(250, 600, "����");
	struct button* p2 = button(550, 600, "�һ�");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	if (flag == 1)
	{
		free(p1);
		cleardevice();
		personalCenter();
	}
	if (flag == 2)
	{
		free(p2);
		exchangecoupons();
		cleardevice();
		personalCenter();
	}
}
void sendTicket()
{//���͹���
	buildWindow();
	struct button* p1 = button(450, 180, "��ȡ����");
	struct button* p2 = button(450, 400, "��/��ʧ");
	struct button* p3 = button(850, 550, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		miscollection();
		break;
	case 2:
		free(p2);
		damageLoss();
		break;
	case 3:
		free(p3);
		personalCenter();//@
		break;
	default:
		break;
	}
}
void miscollection()
{//��ȡ����
	char trackingNum[TRACKING_NUM] = { '\0' };
	if (searchWindow("�����뱻��ȡ�����Ŀ�ݵ���", trackingNum, 10))
	{
		sendticket(1, trackingNum);
		sendTicket();
	}
	else
	{
		sendTicket();
	}
}
void damageLoss()
{//��/��ʧ����
	char trackingNum[TRACKING_NUM] = { '\0' };
	if (searchWindow("�����뱻��/��ʧ�����Ŀ�ݵ���", trackingNum, 10))
	{
		sendticket(2, trackingNum);
		sendTicket();
	}
	else
	{
		sendTicket();

	}
}

//***************************************************************************����Ա����*******************************************************************************
//����Ա�׽��棨�˵����棩
void managerMenu()
{//����Ա�׽���
	buildWindow();
	struct button* p1 = button(450, 120, "���ܿ��");
	struct button* p2 = button(450, 230, "�û�����");
	struct button* p3 = button(450, 340, "���ݷ���");
	struct button* p4 = button(450, 450, "��������");
	struct button* p6 = button(850, 50, "�޸�ʱ��");
	struct button* p5 = button(850, 550, "�˳�");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		drawButton(p4);
		drawButton(p5);
		drawButton(p6);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;

			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;

			}
			if (isClickButton(p4, m))
			{
				flag = 4;
				break;

			}
			if (isClickButton(p5, m))
			{
				flag = 5;
				break;

			}
			if (isClickButton(p6, m))
			{
				flag = 6;
				break;

			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		warehouseMenu();
		break;
	case 2:
		free(p2);
		userManagementMenu();
		break;
	case 3:
		free(p3);
		StasticsAnlysisMenu();
		break;
	case 4:
		free(p4);
		AddressTicketMenu();
		break;
	case 5:
		free(p5);
		login();
		break;
	case 6:
		free(p6);
		settimeMenu();
		break;
	default:
		break;
	}
}
//�޸�ʱ��
void settimeMenu()
{
	buildWindow();
	label(300, 100, "������������վ��ɵ�ʱ��");
	struct button* p1 = button(650, 550, "ȷ��");
	struct button* p2 = button(350, 550, "����");
	label(100, 200, "��ݣ�");
	inputbox(450, 200);
	int year = 0;
	char Year[5] = { '\0' };

	label(100, 300, "�·ݣ�");
	inputbox(450, 300);
	int month = 0;
	char Month[3] = { '\0' };

	label(100, 400, "���ڣ�");
	inputbox(450, 400);
	int day = 0;
	char Day[3] = { '\0' };
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		if (peekmessage(&m, EX_MOUSE))
		{
			isinputbox(450, 200, 4, m, Year);
			year = (double)atof(Year);
			isinputbox(450, 300, 2, m, Month);
			month = (double)atof(Month);
			isinputbox(450, 400, 2, m, Day);
			day = (double)atof(Day);
			if (isClickButton(p1, m))
			{
				if (strlen(Year) == 0 || strlen(Month) == 0 || strlen(Day) == 0)
				{
					messbox("�����ʽ��������������");
				}
				else
				{
					flag = 1;
					break;
				}
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	if (flag == 1)
	{
		free(p1);
		if (!validateDate(year, month, day))
		{
			messbox("���󣺷Ƿ�����ֵ");
			cleardevice();
			settimeMenu();
		}
		else
		{
			cleardevice();
			alterinformation(year, month, day);
		}
	}
	if (flag == 2)
	{
		free(p2);
		cleardevice();
		managerMenu();
	}
}
void alterinformation(int year, int month, int day)
{
	buildWindow();
	struct button* p1 = button(450, 250, "У׼ʱ��");
	struct button* p2 = button(850, 550, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}

		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	switch (flag)
	{
	case 1:
		free(p1);
		timeOperation(year, month, day);
		cleardevice();
		managerMenu();
		break;
	case 2:
		free(p2);
		cleardevice();
		managerMenu();
		break;
	default:
		break;
	}
}
void timeOperation(int year, int month, int day)
{
	time_t startdate;
	if (!inputDateSafe(&startdate, year, month, day))
	{
		fprintf(stderr, "����������Ч\n");
		return;
	}
	struct tm start_tm = {};
	localtime_s(&start_tm, &startdate);
	time_t nowtime = time(NULL);
	struct tm now_tm = {};
	localtime_s(&now_tm, &nowtime);
	start_tm.tm_hour = now_tm.tm_hour;
	start_tm.tm_min = now_tm.tm_min;
	start_tm.tm_sec = now_tm.tm_sec;
	mktime(&start_tm);
	startdate = mktime(&start_tm);
	setStationTime(startdate);//��������ʱ��
	saveTime();//���洴���õ�ʱ��
	nowtime = getStationTime();//���������վʱ��
	//�������������վʱ�����ж��Ż�ȯ�����Ƿ����
	//�Ż�ȯ��ʼʱ����3.1��0��00�������º����6.1��0��00
	double threeMonthsInSeconds = (31 + 30 + 31) * 24 * 3600; // �����µ�������
	struct tm activitystarttime = {};
	activitystarttime.tm_year = 125;
	activitystarttime.tm_mon = 2;//2����3��
	activitystarttime.tm_mday = 1;
	activitystarttime.tm_hour = 0;
	activitystarttime.tm_min = 0;
	activitystarttime.tm_sec = 0;
	mktime(&activitystarttime);
	time_t 	activitystarttime_s = mktime(&activitystarttime);//��ʼ��������
	if (difftime(nowtime, activitystarttime_s) >= threeMonthsInSeconds)//�����Խ�����£���ô��ʼɾ��
	{
		//�����û��������Ұ����ǵ��Ż�ȯ������
		ListNode* head = getUsers()->head->next;
		for (ListNode* node = head; node != NULL; node = node->next)
		{
			User* us = (User*)node->data;
			us->couponCount = 0;
		}
	}
	//�����ǹ���ɾ������
	deleteExpiredLogs();
	messbox("ʱ��У׼�ɹ���");
}
//����Ա���ܿ�����
void warehouseMenu()
{//����Ա���ܿ�����
	buildWindow();
	struct button* p1 = button(450, 200, "ʵʱ����");
	struct button* p2 = button(450, 400, "����׷��");
	struct button* p3 = button(850, 550, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		showWarehouseWindow();
		break;
	case 2:
		free(p2);
		trackPackageWindow();
		break;
	case 3:
		free(p3);
		managerMenu();
		break;
	default:
		break;
	}
}
void showWarehouseWindow()
{//ʵʱ����
	buildWindow();
	int currentshelf = 1;  // ��ǰҳ��
	showWarehouse(currentshelf);// ��ʾ��һҳ������
	struct button* p1 = button(850, 600, "����");
	struct button* p2 = button(200, 550, "��ҳ");
	struct button* p3 = button(350, 550, "��һҳ");
	struct button* p4 = button(500, 550, "��һҳ");
	struct button* p5 = button(650, 550, "ĩҳ");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		drawButton(p4);
		drawButton(p5);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				cleardevice();
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{//��ҳ
				if (currentshelf != 1)
				{//	������ҳ
					currentshelf = 1;
					showWarehouse(currentshelf);
				}
			}
			if (isClickButton(p3, m))
			{//��һҳ
				if (currentshelf != 1)
				{//������ҳ
					currentshelf--;
					showWarehouse(currentshelf);
				}
			}
			if (isClickButton(p4, m))
			{//��һҳ
				if (currentshelf < MAX_SHELVES)
				{//��ǰ�������һҳ
					currentshelf++;
					showWarehouse(currentshelf);
				}
			}
			if (isClickButton(p5, m))
			{//ĩҳ
				if (currentshelf != MAX_SHELVES)
				{//��ǰ�������һҳ
					currentshelf = MAX_SHELVES;
					showWarehouse(currentshelf);
				}
			}
		}

		FlushBatchDraw();
	}
	EndBatchDraw();
	if (flag == 1)
	{
		free(p1);
		warehouseMenu();
	}
}
void trackPackageWindow()
{
	buildWindow();
	label(50, 50, "׷�ٷ�ʽ��");
	struct button* p1 = button(450, 150, "��ݵ���");
	struct button* p2 = button(450, 300, "�ļ��绰");
	struct button* p3 = button(450, 450, "�ռ��绰");
	struct button* p4 = button(850, 550, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		drawButton(p4);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;
			}
			if (isClickButton(p4, m))
			{
				flag = 4;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		trackPackageFoTrackingNum();
		break;
	case 2:
		free(p2);
		trackPackageFoSenderPhone();
		break;
	case 3:
		free(p3);
		trackPackageFoReceiverPhone();
		break;
	case 4:
		free(p4);
		warehouseMenu();
		break;
	default:
		break;
	}
}
void trackPackageFoTrackingNum() {
	char trackingNum[TRACKING_NUM] = { '\0' };
	if (searchWindow("��������Ҫ���Ұ����Ŀ�ݵ���", trackingNum, 10))
	{
		Package refPackage = {};
		strncpy(refPackage.trackingNum, trackingNum, TRACKING_NUM);

		Package* foundPackage = (Package*)list_find(packageList, &refPackage, TRACKINGNUM_MODE, cmpPackage);
		if (foundPackage == NULL)
		{
			messbox("���������ڣ�����������");
			trackPackageFoTrackingNum();
		}
		else
		{
			showTrackPackageInfo(1, trackingNum);
		}
	}
	else
	{
		trackPackageWindow();
	}
}
void trackPackageFoSenderPhone() {
	char senderPhone[PHONE] = { '\0' };
	if (searchWindow("��������Ҫ���Ҽļ��˵绰", senderPhone, 11))
	{
		Package refPackage = {};
		strncpy(refPackage.senderPhone, senderPhone, PHONE);

		Package* foundPackage = (Package*)list_find(packageList, &refPackage, SENDER_PHONE_MODE, cmpPackage);
		if (foundPackage == NULL)
		{
			messbox("���������ڣ�����������");
			trackPackageFoSenderPhone();
		}
		else
		{
			showTrackPackageInfo(2, senderPhone);
		}
	}
	else
	{
		trackPackageWindow();
	}
}
void trackPackageFoReceiverPhone() {
	char receiverPhone[PHONE] = { '\0' };
	if (searchWindow("��������Ҫ�����ռ��˵绰", receiverPhone, 11))
	{
		Package refPackage = {};
		strncpy(refPackage.receiverPhone, receiverPhone, PHONE);
		Package* foundPackage = (Package*)list_find(packageList, &refPackage, RECEIVER_PHONE_MODE, cmpPackage);
		if (foundPackage == NULL)
		{
			messbox("���������ڣ�����������");
			trackPackageFoReceiverPhone();
		}
		else
		{
			showTrackPackageInfo(3, receiverPhone);
		}
	}
	else
	{
		trackPackageWindow();
	}
}
void showTrackPackageInfo(int flag, char* search) {
	if (flag == 1)//����ݵ��Ų���
	{
		buildWindow();
		int currentpage = 0;  // ��ǰҳ��
		if (pagingWindow(trackPackageFoTrackingNumWindow, currentpage, 1, search) == 1)
		{
			trackPackageWindow();
		}
	}
	if (flag == 2)//���ļ��绰����
	{
		buildWindow();
		int currentpage = 0;  // ��ǰҳ��
		long long totalNumber = 0;
		if (pagingWindow(trackPackageFoSenderPhoneWindow, currentpage, trackPackageFoSenderPhoneNumber(totalNumber, search), search) == 1)
		{
			trackPackageWindow();
		}
	}
	if (flag == 3)//���ռ��绰����
	{
		buildWindow();
		int currentpage = 0;  // ��ǰҳ��
		long long totalNumber = 0;
		if (pagingWindow(trackPackageFoReceiverPhoneWindow, currentpage, trackPackageFoReceiverPhoneNumber(totalNumber, search), search) == 1)
		{
			trackPackageWindow();
		}
	}
}
//����Ա�û��������
void userManagementMenu()
{//����Ա�û��������
	buildWindow();
	struct button* p1 = button(450, 120, "�û�����");
	struct button* p2 = button(450, 230, "ɾ���û�");
	struct button* p3 = button(450, 340, "������Ϣ");
	struct button* p4 = button(450, 450, "��־��Ϣ");
	struct button* p5 = button(850, 550, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		drawButton(p4);
		drawButton(p5);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;
			}
			if (isClickButton(p4, m))
			{
				flag = 4;
				break;
			}
			if (isClickButton(p5, m))
			{
				flag = 5;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		managerFindUserWindow();
		break;
	case 2:
		free(p2);
		managerDeleteUserWindow();
		break;
	case 3:
		free(p3);
		showTickets();
		break;
	case 4:
		free(p4);
		showAllLogs();
		break;
	case 5:
		free(p5);
		managerMenu();
		break;
	default:
		break;
	}
}
void managerFindUserWindow()
{//�û�����
	buildWindow();
	label(50, 50, "������ʽ��");
	struct button* p1 = button(450, 200, "�ǳƼ���");
	struct button* p2 = button(450, 400, "�˺ż���");
	struct button* p4 = button(850, 550, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p4);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickButton(p4, m))
			{
				flag = 4;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		managerFindUserForName();
		break;
	case 2:
		free(p2);
		managerFindUserForNumber();
		break;
	case 4:
		free(p4);
		userManagementMenu();
		break;
	default:
		break;
	}
}
void managerFindUserForName() {
	char name[20] = { '\0' };
	if (searchWindow("��������Ҫ�����û����ǳ�", name, 0))
	{
		User refUser = {};
		strncpy(refUser.userName, name, 12);
		User* foundUser = (User*)list_find(userList, &refUser, NAME_MODE, cmpUser);
		//�û�������
		if (foundUser == NULL)
		{
			messbox("�û�������!");
			managerFindUserForName();
		}
		else
		{
			managerFindUserInfo(1, name);
		}
	}
	else
	{
		managerFindUserWindow();
	}
}
void managerFindUserForNumber()
{
	char phoneNumber[PHONE] = { '\0' };
	if (searchWindow("��������Ҫ�����û����ֻ���", phoneNumber, 11))
	{
		User refUser = {};
		strncpy(refUser.phoneNumber, phoneNumber, PHONE);
		User* foundUser = (User*)list_find(userList, &refUser, PHONE_MODE, cmpUser);
		//�û�������
		if (foundUser == NULL)
		{
			messbox("�û�������!");
			managerFindUserForNumber();
		}
		else
		{
			managerFindUserInfo(2, phoneNumber);
		}
	}
	else
	{
		managerFindUserWindow();
	}
}
void managerFindUserInfo(int flag, char* search)
{
	if (flag == 1)//���ǳƲ���
	{
		buildWindow();
		int currentpage = 0;  // ��ǰҳ��
		long long totalNumber = 0;
		if (pagingWindow(trackPackageFoNameWindow, currentpage, trackPackageFoNameNumber(totalNumber, search), search) == 1)
		{
			managerFindUserWindow();
		}
	}
	if (flag == 2)
	{
		buildWindow();
		int currentpage = 0;  // ��ǰҳ��
		if (pagingWindow(trackPackageFoPhoneNumberWindow, currentpage, 1, search) == 1)
		{
			managerFindUserWindow();
		}
	}
}
void managerDeleteUserWindow()
{//ɾ���û�
	char phoneNumber[PHONE] = { '\0' };
	if (searchWindow("��������Ҫɾ���û����ֻ���", phoneNumber, 11))
	{
		cleardevice();
		buildWindow();
		managerDeleteUser(phoneNumber);
		managerDeleteUserWindow();
	}
	else
	{
		userManagementMenu();
	}
}
void showTickets()
{//������Ϣ
	buildWindow();
	label(50, 50, "����ʽ��");
	struct button* p1 = button(450, 200, "��������");
	struct button* p2 = button(450, 400, "ʱ������");
	struct button* p4 = button(850, 550, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p4);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickButton(p4, m))
			{
				flag = 4;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		sortTicket(1);
		showTicketsInfo();
		break;
	case 2:
		free(p2);
		sortTicket(2);
		showTicketsInfo();
		break;
	case 4:
		free(p4);
		userManagementMenu();
		break;
	default:
		break;
	}
}
void showTicketsInfo()
{
	int currentpage = 0;
	long long TicketsTotalNumber = 0;
	if (pagingWindow(showTicketsWindow, currentpage, getTotalNumber(TicketsTotalNumber), NULL) == 1)
	{
		userManagementMenu();
	}
}
void showAllLogs()
{//��־��Ϣ
	buildWindow();
	int currentpage = 0;
	long long allLogsTotalNumber = 0;
	if (pagingWindow(showAllLogsWindow, currentpage, getAllLogsTotalNumber(allLogsTotalNumber), NULL) == 1)
	{
		userManagementMenu();
	}
}
//����Ա���ݷ�������
void StasticsAnlysisMenu()
{//����Ա���ݷ�������
	buildWindow();
	struct button* p1 = button(450, 180, "ÿ�ܼ�");
	struct button* p2 = button(450, 400, "����Ԥ��");
	struct button* p3 = button(850, 550, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		WeeklyBrieflyMenu();
		break;
	case 2:
		free(p2);
		MainpartMenu();
		break;
	case 3:
		free(p3);
		managerMenu();
		break;
	default:
		break;
	}
}
void WeeklyBrieflyMenu()
{//ÿ�ܼ�
	buildWindow();
	WeeklyBriefly();
	struct button* p1 = button(500, 600, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				cleardevice();
				flag = 1;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	if (flag == 1)
	{
		free(p1);
		StasticsAnlysisMenu();
	}
}
void MainpartMenu()
{
	buildWindow();
	label(300, 100, "��������ҪԤ�����ֹʱ��");
	struct button* p1 = button(650, 550, "ȷ��");
	struct button* p2 = button(350, 550, "����");
	label(100, 200, "��ݣ�");
	inputbox(450, 200);
	int year = 0;
	char Year[5] = { '\0' };

	label(100, 300, "�·ݣ�");
	inputbox(450, 300);
	int month = 0;
	char Month[3] = { '\0' };

	label(100, 400, "���ڣ�");
	inputbox(450, 400);
	int day = 0;
	char Day[3] = { '\0' };
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		if (peekmessage(&m, EX_MOUSE))
		{
			isinputbox(450, 200, 4, m, Year);
			year = (double)atof(Year);
			isinputbox(450, 300, 2, m, Month);
			month = (double)atof(Month);
			isinputbox(450, 400, 2, m, Day);
			day = (double)atof(Day);
			if (isClickButton(p1, m))
			{
				if (strlen(Year) == 0 || strlen(Month) == 0 || strlen(Day) == 0)
				{
					messbox("�����ʽ��������������");
				}
				else
				{
					flag = 1;
					break;
				}
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	if (flag == 1)
	{
		free(p1);
		if (!validateDate(year, month, day))
		{
			messbox("���󣺷Ƿ�����ֵ");
			cleardevice();
			MainpartMenu();
		}
		else
		{
			cleardevice();
			nextwindow(year, month, day);
		}
	}
	if (flag == 2)
	{
		free(p2);
		cleardevice();
		StasticsAnlysisMenu();
	}
}
void nextwindow(int year, int month, int day)
{
	buildWindow();
	struct button* p1 = button(450, 180, "���ͼ��");
	struct button* p2 = button(450, 400, "Ԥ��δ��");
	struct button* p3 = button(850, 550, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);//���ͼ�񲿷�
		MainpartInfo(year, month, day);
		break;
	case 2:
		free(p2);//Ԥ��δ������
		futureData(year, month, day);
		break;
	case 3:
		free(p3);
		StasticsAnlysisMenu();
		break;
	default:
		break;
	}

}
void MainpartInfo(int year, int month, int day)
{//���ͼ�񲿷�
	buildWindow();
	Mainpart(year, month, day);

}
void futureData(int year, int month, int day)
{
	futuredata(year, month, day);
}
//����Ա   ��������   ����
void AddressTicketMenu()
{//����Ա�����������
	buildWindow();
	struct button* p1 = button(450, 200, "��ȡ����");
	struct button* p2 = button(450, 400, "�𻵶�ʧ");
	struct button* p3 = button(850, 550, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;

			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		addressMisdeliveryWindow();
		break;
	case 2:
		free(p2);
		addressDamageLossWindow();
		break;
	case 3:
		free(p3);
		managerMenu();
		break;
	default:
		break;
	}
}
void addressMisdeliveryWindow()
{//��ȡ�������
	char ticketid[50] = { '\0' };
	if (searchWindow("��������Ҫ������ȡ�����Ĺ������", ticketid, 10))
	{
		long long  ticketId = (long long)atof(ticketid);
		AddressMisdelivery(ticketId);
		AddressTicketMenu();
	}
	else
	{
		AddressTicketMenu();
	}
}
void addressDamageLossWindow()
{//�𻵶�ʧ�������
	char ticketid[50] = { '\0' };
	if (searchWindow("��������Ҫ�����𻵶�ʧ�����Ĺ������", ticketid, 10))
	{
		long long  ticketId = (long long)atof(ticketid);
		AddressDamageLoss(ticketId);
		AddressTicketMenu();
	}
	else
	{
		AddressTicketMenu();
	}
}
//******************************************************************��ӪԱ����************************************************************************************
//��ӪԱ�׽���
void operaterWindow()
{
	buildWindow();
	struct button* p1 = button(450, 100, "�������");
	struct button* p2 = button(450, 200, "�ͼ���¥");
	struct button* p3 = button(450, 300, "����ȡ��");
	struct button* p6 = button(450, 400, "�����ļ�");
	struct button* p4 = button(450, 500, "֪ͨ����");
	struct button* p5 = button(850, 550, "�˳�");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		drawButton(p4);
		drawButton(p5);
		drawButton(p6);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;

			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;

			}
			if (isClickButton(p4, m))
			{
				flag = 4;
				break;
			}

			if (isClickButton(p5, m))
			{
				flag = 5;
				break;
			}

			if (isClickButton(p6, m))
			{
				flag = 6;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		putInMessage();
		break;
	case 2:
		free(p2);
		deliverToHomeWindow();
		break;
	case 3:
		free(p3);
		pickUpFromHomeWindow();
		break;
	case 4:
		free(p4);
		sendNotificationWindow();
		break;
	case 5:
		free(p5);
		login();
		break;
	case 6:
		free(p6);
		sendPackageMakeMenu();
		break;
	default:
		break;
	}
}
//¼����Ϣ
void putInMessage()
{
	buildWindow();
	label(50, 100, "��ݵ���:");
	inputbox(200, 100);
	char  trackingNum[TRACKING_NUM] = { '\0' };

	label(500, 100, "��������:");
	inputbox(650, 100);
	char packageName[NAME] = { '\0' };
	text(850, 100, "����������");

	label(50, 200, "��������:");
	PackageType packagetype{};
	struct choice* ch1 = choice(200, 200, "��ͨ");
	struct choice* ch2 = choice(300, 200, "����");
	struct choice* ch3 = choice(400, 200, "����");

	label(500, 200, "��������:");
	inputbox(650, 200);
	char weight[50] = { '\0' };
	double w = 0.0;
	text(850, 200, "(ǧ��)");

	label(50, 300, "�������:");
	inputbox(200, 300);
	char volume[50] = { '\0' };
	double v = 0.0;
	text(400, 300, "(������)");

	label(500, 300, "�ռ��˵绰");
	inputbox(650, 300);
	char  receiverPhone[PHONE] = { '\0' };


	label(50, 400, "�ļ���ַ:");
	inputboxAdress(200, 400);
	char senderAddress[ADDRESS] = { '\0' };
	struct button* p1 = button(250, 600, "����");
	struct button* p2 = button(550, 600, "ȷ��");
	BeginBatchDraw();
	ExMessage m;
	int flag = 0;
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawChioce(ch1);
		drawChioce(ch2);
		drawChioce(ch3);
		if (peekmessage(&m, EX_MOUSE))
		{
			isinputbox(200, 100, 10, m, trackingNum);
			isinputbox(650, 100, 0, m, packageName);
			isinputbox(200, 300, -1, m, volume);
			v = (double)atof(volume);
			isinputboxAdress(200, 400, m, senderAddress);
			isinputbox(650, 200, -2, m, weight);
			w = (double)atof(weight);
			isinputbox(650, 300, 11, m, receiverPhone);
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				if (strlen(trackingNum) == 0 || strlen(packageName) == 0 || (ch1->fillcolor == WHITE && ch2->fillcolor == WHITE && ch3->fillcolor == WHITE)
					|| strlen(weight) == 0 || strlen(volume) == 0 || strlen(receiverPhone) == 0 || strlen(senderAddress) == 0)
				{
					messbox("��Ϣδ��д����");
				}
				else
				{
					flag = 2;
					break;
				}
			}
			if (isClickChoice(ch1, m))
			{
				packagetype = PackageStandard;
				ch2->fillcolor = ch2->noclickcolor;
				ch3->fillcolor = ch3->noclickcolor;
			}
			if (isClickChoice(ch2, m))
			{
				packagetype = Parcel;
				ch1->fillcolor = ch1->noclickcolor;
				ch3->fillcolor = ch3->noclickcolor;
			}
			if (isClickChoice(ch3, m))
			{
				packagetype = Fragile;
				ch1->fillcolor = ch1->noclickcolor;
				ch2->fillcolor = ch2->noclickcolor;
			}
		}

		FlushBatchDraw();
	}
	EndBatchDraw();
	if (flag == 1)
	{
		free(p1);
		operaterWindow();
	}
	if (flag == 2)
	{
		char pickupCode[50] = { '\0' };
		strncpy(pickupCode, InputPackageInfo(trackingNum, packageName, packagetype, v, w, senderAddress, receiverPhone), sizeof(pickupCode) - 1);
		pickupCode[sizeof(pickupCode) - 1] = '\0';
		messbox(pickupCode);
		free(p2);
		cleardevice();
		putInMessage();
	}
}
//�ͼ���¥
void deliverToHomeWindow()
{
	buildWindow();
	struct button* p1 = button(450, 200, "��ʾ��Ϣ");
	struct button* p2 = button(450, 400, "ȷ���ʹ�");
	struct button* p3 = button(850, 600, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		deliverToHomeMessage();
		break;
	case 2:
		free(p2);
		deliverToHomeComeTure();
		break;
	case 3:
		free(p3);
		operaterWindow();
		break;
	default:
		break;
	}
}
void deliverToHomeMessage()
{//��ʾ��Ϣ
	buildWindow();
	int currentpage = 0;  // ��ǰҳ��
	long long deliverToHomeTotalNumber = 0;
	if (pagingWindow(deliverToHomeWindow, currentpage, deliverToHomeNumber(deliverToHomeTotalNumber), NULL) == 1)
	{
		deliverToHomeWindow();
	}
}
void deliverToHomeComeTure()
{//ȷ���ʹ�
	char trackingNum[TRACKING_NUM] = { '\0' };
	if (searchWindow("������ȷ���Ѿ��ʹﵽ¥�����Ŀ�ݵ���", trackingNum, 10))
	{
		deliverToHomeMakeTrue(trackingNum);
		deliverToHomeComeTure();
	}
	else
	{
		deliverToHomeWindow();

	}
}
//����ȡ��
void pickUpFromHomeWindow()
{
	buildWindow();
	struct button* p1 = button(450, 200, "��ʾ��Ϣ");
	struct button* p2 = button(450, 400, "ȷ��ȡ��");
	struct button* p3 = button(850, 600, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		pickUpFromHomeMessage();
		break;
	case 2:
		free(p2);
		pickUpFromHomeComeTure();
		break;
	case 3:
		free(p3);
		operaterWindow();
		break;
	default:
		break;
	}
}
void pickUpFromHomeMessage()
{//��ʾ��Ϣ
	buildWindow();
	int currentpage = 0;  // ��ǰҳ��
	long long pickUpFromHomeTotalNumber = 0;
	if (pagingWindow(pickUpFromHomeWindow, currentpage, pickUpFromHomeNumber(pickUpFromHomeTotalNumber), NULL) == 1)
	{
		pickUpFromHomeWindow();
	}
}
void pickUpFromHomeComeTure()
{//ȷ��ȡ��
	char trackingNum[TRACKING_NUM] = { '\0' };
	buildWindow();
	label(300, 150, "������ȷ���Ѿ�ȡ�������Ŀ�ݵ���");
	if (searchWindow("������ȷ���Ѿ�ȡ�������Ŀ�ݵ���", trackingNum, 10))
	{
		pickUpFromHomeMakeTrue(trackingNum);
		pickUpFromHomeComeTure();
	}
	else
	{
		pickUpFromHomeWindow();
	}
}
//�����ļ�
void sendPackageMakeMenu() {
	buildWindow();
	struct button* p1 = button(450, 200, "��ʾ��Ϣ");
	struct button* p2 = button(450, 400, "ȷ�ϼļ�");
	struct button* p3 = button(850, 600, "����");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				flag = 1;
				break;
			}
			if (isClickButton(p2, m))
			{
				flag = 2;
				break;
			}
			if (isClickButton(p3, m))
			{
				flag = 3;
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	switch (flag)
	{
	case 1:
		free(p1);
		sortPackagesByTime(0);
		sendPackageMakeInfo();
		break;
	case 2:
		free(p2);
		sendPackageMakeSure();
		break;
	case 3:
		free(p3);
		operaterWindow();
		break;
	default:
		break;
	}
}
void  sendPackageMakeInfo() {
	buildWindow();
	int currentpage = 0;  // ��ǰҳ��
	long long deliverToHomeTotalNumber = 0;
	if (pagingWindow(displayPointDeliveryPackages, currentpage, countPackagesForPointDelivery(deliverToHomeTotalNumber), NULL) == 1)
	{
		sendPackageMakeMenu();
	}
}
void sendPackageMakeSure() {
	char trackingNum[TRACKING_NUM] = { '\0' };
	buildWindow();
	label(300, 150, "������ȷ���ĳ������Ŀ�ݵ���");
	if (searchWindow("������ȷ���ĳ������Ŀ�ݵ���", trackingNum, 10))
	{
		confirmPointDelivery(trackingNum);
		sendPackageMakeSure();
	}
	else
	{
		sendPackageMakeMenu();
	}
}
//֪ͨ����
void sendNotificationWindow()
{
	char hour[10] = { '\0' };
	buildWindow();
	label(300, 150, "��������Ҫ�趨��ʱ����ֵ");
	if (searchWindow("��������Ҫ�趨��ʱ����ֵ", hour, 2))
	{
		double customHoursDiff = atof(hour);
		sendNotificationInfo(customHoursDiff);
	}
	else
	{
		operaterWindow();
	}
}
void sendNotificationInfo(double customHoursDiff)
{
	buildWindow();
	long long totalNumber = sendNotificationNumber(0, customHoursDiff);
	int startpage = 1;//��ȡ��һҳ
	int currentpage = startpage;//��ǰҳ��Ϊ��һҳ
	long long lastpage;
	if (totalNumber % 9 != 0)
	{
		lastpage = totalNumber / 9 + 1;
	}
	else
	{
		lastpage = totalNumber / 9;
	}//��ȡ���һҳ
	sendNotificationWindow(startpage, totalNumber, NULL, customHoursDiff);// ��ʾ��һҳ������
	struct button* p1 = button(850, 600, "����");
	struct button* p2 = button(200, 550, "��ҳ");
	struct button* p3 = button(350, 550, "��һҳ");
	struct button* p4 = button(500, 550, "��һҳ");
	struct button* p5 = button(650, 550, "ĩҳ");
	ExMessage m;
	int flag = 0;
	BeginBatchDraw();
	while (1)
	{
		drawButton(p1);
		drawButton(p2);
		drawButton(p3);
		drawButton(p4);
		drawButton(p5);
		if (peekmessage(&m, EX_MOUSE))
		{
			if (isClickButton(p1, m))
			{
				cleardevice();
				flag = 1;
				free(p1);
				free(p2);
				free(p3);
				free(p4);
				free(p5);
				break;
			}
			if (isClickButton(p2, m))
			{//��ҳ
				if (currentpage == startpage)
				{//������ҳ
					;
				}
				else
				{
					currentpage = 1;
					sendNotificationWindow(currentpage, totalNumber, NULL, customHoursDiff);
				}
			}
			if (isClickButton(p3, m))
			{//��һҳ
				if (currentpage == startpage)
				{//������ҳ
					;
				}
				else
				{
					currentpage--;
					sendNotificationWindow(currentpage, totalNumber, NULL, customHoursDiff);
				}
			}
			if (isClickButton(p4, m))
			{//��һҳ
				if (currentpage != lastpage)
				{//��ǰ�������һҳ
					currentpage++;
					sendNotificationWindow(currentpage, totalNumber, NULL, customHoursDiff);
				}
				else
				{
					;
				}
			}
			if (isClickButton(p5, m))
			{//ĩҳ
				if (currentpage != lastpage)
				{//��ǰ�������һҳ
					currentpage = lastpage;
					sendNotificationWindow(currentpage, totalNumber, NULL, customHoursDiff);
				}
				else
				{
					;
				}
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	operaterWindow();
}

