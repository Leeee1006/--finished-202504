#include "fore.h"
void buildWindow()
{//创建窗口
	IMAGE img;
	loadimage(&img, "cai.jpg");
	putimage(0, 0, &img);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	outtextxy(0, 0, "驿站时间:");
	char buf[50] = "";
	strcpy_s(buf, 50, formatTime(getStationTime()));
	buf[10] = '\0';
	outtextxy(90, 0, buf);
}
void messbox(const char* arr)
{//处理char*类型,用于将多字节字符串转换为宽字符字符串（wchar_t 类型的字符串）
	wchar_t wtext[256];
	int len = MultiByteToWideChar(CP_ACP, 0, arr, -1, wtext, 256);  // GBK 编码
	if (len > 0)
	{
		HWND hnd = GetHWnd();
		MessageBoxW(hnd, wtext, L"提示", MB_OK | MB_ICONINFORMATION);
	}
}
void isinputbox(int x, int y, int flag, ExMessage m, char* s)
{//普通对话框
	if (m.message == WM_LBUTTONDOWN && m.x >= x && m.x <= x + 200 && m.y >= y && m.y <= y + 30)
	{
		setfillcolor(WHITE);
		fillrectangle(x, y, x + 200, y + 30);//矩形
		InputBox(s, ADDRESS, "请输入");
		settextcolor(BLACK);
		settextstyle(20, 0, FONT);
		setbkmode(TRANSPARENT);
		int width = 200 / 2 - textwidth(s) / 2;
		int height = 30 / 2 - textheight(s) / 2;
		if (flag > 0)
		{//数字
			if (validatePassword(s, flag) == 0)
			{
				messbox("格式错误");
				s[0] = '\0';
			}
			else
			{
				outtextxy(x + width, y + height, s);
				return;
			}
		}
		else if (flag == 0)
		{//6个汉字
			if (isChineseString(s, 12) == 0)
			{
				messbox("格式错误");
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
		{//字符串转数字,体积限制
			double num = (double)atof(s);
			if (num <= 0 || validateVolume(num) == 0)
			{
				messbox("体积格式错误");
			}
			else
			{
				s[9] = '\0';
				outtextxy(x + width, y + height, s);
			}
		}
		else if (flag == -2)
		{//字符串转数字,重量限制
			double num = (double)atof(s);
			if (num <= 0 || validateWeight(num) == 0)
			{
				messbox("重量格式错误");
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
{//长对话框    地址对话框
	if (m.message == WM_LBUTTONDOWN && m.x >= x && m.x <= x + 500 && m.y >= y && m.y <= y + 30)
	{
		setfillcolor(WHITE);
		fillrectangle(x, y, x + 500, y + 30);//矩形
		InputBox(s, ADDRESS, "请输入");
		settextcolor(BLACK);
		settextstyle(20, 0, FONT);
		setbkmode(TRANSPARENT);
		int width = 500 / 2 - textwidth(s) / 2;
		int height = 30 / 2 - textheight(s) / 2;
		if (isChineseString(s, ADDRESS - 1) == 0)
		{
			messbox("格式错误");
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
{//画按钮
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
{//输入框文字标签
	settextcolor(BLACK);
	settextstyle(30, 0, FONT);
	setbkmode(TRANSPARENT);
	outtextxy(x, y, arr);
}
void label(int x, int y, double number)
{//重载函数，编写数字，颜色为黑色
	char arr[50] = { '\0' };
	sprintf(arr, "%.2f", number);
	label(x, y, arr);
}
void text(int x, int y, const char* arr)
{//编写文字，文字颜色为黑色
	settextcolor(BLACK);
	settextstyle(18, 0, FONT);
	setbkmode(TRANSPARENT);
	outtextxy(x, y, arr);
}
void textRed(int x, int y, const char* arr)
{//编写文字,文字颜色为红色
	settextcolor(RED);
	settextstyle(18, 0, FONT);
	setbkmode(TRANSPARENT);
	outtextxy(x, y, arr);
}
void text(int x, int y, int number)
{//重载函数，编写数字，颜色为黑色
	char arr[50] = { '\0' };
	sprintf(arr, "%d", number);
	text(x, y, arr);
}
void text(int x, int y, float number)
{//重载函数，编写数字，颜色为黑色
	char arr[50] = { '\0' };
	sprintf(arr, "%.2f", number);
	text(x, y, arr);
}
void textRed(int x, int y, int number)
{//重载函数，编写数字，颜色为红色
	char arr[50] = { '\0' };
	sprintf(arr, "%d", number);
	textRed(x, y, arr);
}
void textRed(int x, int y, float number)
{//重载函数，编写数字，颜色为红色
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
{//封装分页页面函数
	buildWindow();
	int startpage = 1;//获取第一页
	currentpage = startpage;//当前页面为第一页
	long long lastpage;
	if (totalNumber % 9 != 0)
	{
		lastpage = totalNumber / 9 + 1;
	}
	else
	{
		lastpage = totalNumber / 9;
	}//获取最后一页
	currentPage(startpage, totalNumber, searchNum);// 显示第一页的数据
	struct button* p1 = button(850, 600, "返回");
	struct button* p2 = button(200, 550, "首页");
	struct button* p3 = button(350, 550, "上一页");
	struct button* p4 = button(500, 550, "下一页");
	struct button* p5 = button(650, 550, "末页");
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
			{//首页
				if (currentpage == startpage)
				{//已是首页
					;
				}
				else
				{
					currentpage = 1;
					currentPage(currentpage, totalNumber, searchNum);
				}
			}
			if (isClickButton(p3, m))
			{//上一页
				if (currentpage == startpage)
				{//已是首页
					;
				}
				else
				{
					currentpage--;
					currentPage(currentpage, totalNumber, searchNum);
				}
			}
			if (isClickButton(p4, m))
			{//下一页
				if (currentpage != lastpage)
				{//当前不是最后一页
					currentpage++;
					currentPage(currentpage, totalNumber, searchNum);
				}
				else
				{
					;
				}
			}
			if (isClickButton(p5, m))
			{//末页
				if (currentpage != lastpage)
				{//当前不是最后一页
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
	struct button* p1 = button(650, 450, "确定");
	struct button* p2 = button(350, 450, "返回");
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
					messbox("输入格式错误，请重新输入");
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
//              *******************************************************************************************登录界面**********************************************************
//登录+注册
void registerAndLogin()
{//登录+注册
	buildWindow();
	struct button* p1 = button(450, 200, "注册");
	struct button* p2 = button(450, 400, "登录");
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
//登录界面
void login()
{//登录界面	
	buildWindow();
	label(300, 200, "手机号：");
	label(300, 300, "密码：");
	inputbox(480, 300);
	inputbox(480, 200);
	struct button* p1 = button(350, 400, "返回");
	struct button* p2 = button(550, 400, "登录");
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
		if (strncmp(phoneNumber, "18336109923", PHONE) == 0 && strncmp(password, "666888", PASSWORD) == 0)//管理员
		{
			cleardevice();
			managerMenu();
			operaterWindow();
		}
		if (strncmp(phoneNumber, "16668219582", PHONE) == 0 && strncmp(password, "000111", PASSWORD) == 0)//运营员
		{
			cleardevice();
			operaterWindow();
		}
		else
		{
			g_currentUser = userLogin(phoneNumber, password);
			if (g_currentUser == NULL)
			{
				messbox("手机号或密码错误");
				cleardevice();
				login();
			}
			cleardevice();
			userMenu();
		}
	}
}
//注册界面
void Register()
{ //注册界面
	buildWindow();
	label(300, 100, "昵称:");
	label(300, 200, "手机号:");
	label(300, 300, "密码:");

	inputbox(480, 100);
	label(850, 100, "汉字(6个以内)");
	inputbox(480, 200);
	label(850, 200, "11位数字");
	inputbox(480, 300);
	label(850, 300, "6位数字");
	struct button* p1 = button(350, 400, "返回");
	struct button* p2 = button(550, 400, "注册");
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
				messbox("手机号已存在");
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
			messbox("输入无效，请重新输入");
			cleardevice();
			Register();
		}
	}
}
//******************************************************************************************用户界面********************************************************************************
//用户首界面（菜单界面）
void userMenu()
{//用户首界面
	buildWindow();
	struct button* p1 = button(450, 120, "包裹信息");
	struct button* p2 = button(450, 230, "我要寄件");
	struct button* p3 = button(450, 340, "我要取件");
	struct button* p4 = button(450, 450, "个人中心");
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
//*****包裹信息
//包裹信息菜单
void packageInfoMenu()
{//包裹信息
	buildWindow();
	label(50, 50, "寄件信息");
	struct button* p1 = button(100, 180, "已寄出");
	struct button* p2 = button(400, 180, "待寄出");
	struct button* p3 = button(700, 180, "已取消");
	label(50, 300, "取件信息");
	struct button* p4 = button(100, 430, "已签收");
	struct button* p5 = button(400, 430, "待取");
	struct button* p6 = button(700, 430, "拒收");
	struct button* p7 = button(850, 550, "返回");
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
//已寄出信息
void packageShippedMenu()
{//已寄出
	buildWindow();
	int currentpage = 0;
	long long packageShippedTotalNumber = 0;
	if (pagingWindow(showPackageShippedWindow, currentpage, getPackageShippedNum(g_currentUser->phoneNumber, packageShippedTotalNumber), g_currentUser->phoneNumber) == 1)
	{
		packageInfoMenu();
	}
}//已寄出
//待寄出信息
void packageOrderedMenu()
{//待寄出
	buildWindow();
	struct button* p1 = button(450, 150, "查询信息");
	struct button* p2 = button(450, 350, "取消寄件");
	struct button* p3 = button(850, 550, "返回");
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
{//查询信息
	buildWindow();
	int currentpage = 0;
	long long packageOrderedTotalNumber = 0;
	if (pagingWindow(showPackageOrderedWindow, currentpage, getPackageOrderedNum(g_currentUser->phoneNumber, packageOrderedTotalNumber), g_currentUser->phoneNumber) == 1)
	{
		packageOrderedMenu();
	}
}
void cancelPackageWindow()
{//取消寄件
	char trackingNum[TRACKING_NUM] = { '\0' };
	if (searchWindow("请输入要取消寄件包裹的快递单号", trackingNum, 10))
	{
		cancelPackage(trackingNum);
		cancelPackageWindow();
	}
	else
	{
		packageOrderedMenu();
	}
}
//已取消信息
void packageCanceledMenu()
{//已取消
	buildWindow();
	int currentpage = 0;
	long long packageCanceledTotalNumber = 0;
	if (pagingWindow(showPackageCanceledWindow, currentpage, getPackageCanceledNum(g_currentUser->phoneNumber, packageCanceledTotalNumber), g_currentUser->phoneNumber) == 1)
	{
		packageInfoMenu();
	}
}
//已签收信息
void packageDeliveredMenu()
{//已签收
	buildWindow();
	int currentpage = 0;
	long long packageDeliveredTotalNumber = 0;
	if (pagingWindow(showPackageDeliveredWindow, currentpage, getPackageDeliveredNum(g_currentUser->phoneNumber, packageDeliveredTotalNumber), g_currentUser->phoneNumber) == 1)
	{
		packageInfoMenu();
	}
}
//待取信息
void packagePendingMenu()
{//待取菜单
	buildWindow();
	struct button* p1 = button(450, 150, "查询信息");
	struct button* p2 = button(450, 350, "送货到楼");
	struct button* p3 = button(850, 550, "返回");
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
{//待取信息
	buildWindow();
	int currentpage = 0;
	long long packagePendingTotalNumber = 0;
	if (pagingWindow(showPackagePendingWindow, currentpage, getPackagePendingNum(g_currentUser->phoneNumber, packagePendingTotalNumber), g_currentUser->phoneNumber) == 1)
	{
		packagePendingMenu();
	}
}
void packagePendWindow()
{//送货到楼申请
	buildWindow();
	label(200, 150, "快递单号：");
	inputbox(450, 150);
	char trackingNum[TRACKING_NUM] = { '\0' };

	label(200, 350, "宿舍地址：");
	inputbox(450, 350);
	char receiverAddress[ADDRESS] = { '\0' };
	label(700, 350, "六个汉字以内");
	struct button* p1 = button(650, 450, "下单");
	struct button* p2 = button(350, 450, "返回");
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
					messbox("输入格式错误，请重新输入");
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
//拒收信息
void packageRefusedMenu()
{//拒收
	buildWindow();
	struct button* p1 = button(450, 150, "查询信息");
	struct button* p2 = button(450, 350, "我要拒收");
	struct button* p3 = button(850, 550, "返回");
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
{//拒收信息
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
	//我要拒收
	char trackingNum[TRACKING_NUM] = { '\0' };
	if (searchWindow("请输入要拒收包裹的快递单号", trackingNum, 10))
	{
		refusePackage(trackingNum);
		packageRefusedWindow();
	}
	else
	{
		packageRefusedMenu();
	}
}
//********我要取件
void pickupPackageMenu()
{//我要取件
	char trackingNum[TRACKING_NUM] = { '\0' };
	if (searchWindow("请输入要取件包裹的快递单号", trackingNum, 10))
	{
		pickupPackage(trackingNum);
		pickupPackageMenu();
	}
	else
	{
		userMenu();
	}
}
//*****我要寄件
void sendPackage()
{//我要寄件
	buildWindow();
	struct button* p1 = button(250, 600, "返回");
	struct button* p2 = button(550, 600, "下一步");
	label(50, 50, "包裹名称:");
	char packageName[NAME] = { '\0' };
	inputbox(200, 50);
	text(400, 50, "(六个字以内)");

	label(500, 50, "重量:");
	char packageweight[DIGITS] = { '\0' };
	double weight = 0.0;
	inputbox(650, 50);
	text(850, 50, "(千克)");

	label(50, 120, "包裹体积:");
	char packagevolume[DIGITS] = { '\0' };
	inputbox(200, 120);
	double volume = 0.0;
	text(400, 120, "(立方米)");

	label(500, 120, "收件人电话");
	char receiverPhone[PHONE] = { '\0' };
	inputbox(650, 120);

	label(50, 190, "收件地址:");
	char receiverAddress[ADDRESS] = { '\0' };
	inputboxAdress(200, 190);

	label(50, 260, "宿舍地址:");
	char dormAddress[ADDRESS] = { '\0' };
	inputboxAdress(200, 260);
	label(800, 260, "(非必填)");

	label(250, 410, "快递类型:");
	int shippingMethodOption = -1;
	struct choice* ch1 = choice(400, 410, "快递");
	struct choice* ch2 = choice(500, 410, "普通");
	struct choice* ch3 = choice(600, 410, "经济");

	label(250, 480, "物品类型:");
	int packageTypeOption = -1;
	struct choice* ch4 = choice(400, 480, "普通");
	struct choice* ch5 = choice(500, 480, "贵重");
	struct choice* ch6 = choice(600, 480, "易碎");

	label(250, 550, "寄件方式:");
	int homeSentOption = -1;
	struct choice* ch7 = choice(400, 550, "自寄");
	struct choice* ch8 = choice(500, 550, "上门取件");

	label(250, 340, "优惠券");
	int couponOption = -1;
	struct choice* ch9 = choice(400, 340, "使用");
	struct choice* ch10 = choice(500, 340, "不用");

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
				homeSentOption = 1;//自寄
				ch8->fillcolor = ch8->noclickcolor;
			}
			if (isClickChoice(ch8, m))
			{
				homeSentOption = 2;//上门取件
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
			messbox("信息未填写完整");
			cleardevice();
			sendPackage();
		}
		if (homeSentOption == 1)//自寄
		{
			if (strlen(receiverAddress) == 0 || strlen(packageweight) == 0 || strlen(packageName) == 0 || strlen(packagevolume) == 0 || strlen(receiverPhone) == 0 ||
				(ch1->fillcolor == WHITE && ch2->fillcolor == WHITE && ch3->fillcolor == WHITE) || (ch4->fillcolor == WHITE && ch5->fillcolor == WHITE && ch6->fillcolor == WHITE)
				|| (ch7->fillcolor == WHITE && ch8->fillcolor == WHITE) || (ch9->fillcolor == WHITE && ch10->fillcolor == WHITE))
			{//信息填写不完整
				messbox("信息未填写完整");
				cleardevice();
				sendPackage();
			}
		}
		if (homeSentOption == 2)
		{
			if (strlen(dormAddress) == 0 || strlen(receiverAddress) == 0 || strlen(packageweight) == 0 || strlen(packageName) == 0 || strlen(packagevolume) == 0 || strlen(receiverPhone) == 0 ||
				(ch1->fillcolor == WHITE && ch2->fillcolor == WHITE && ch3->fillcolor == WHITE) || (ch4->fillcolor == WHITE && ch5->fillcolor == WHITE && ch6->fillcolor == WHITE)
				|| (ch7->fillcolor == WHITE && ch8->fillcolor == WHITE) || (ch9->fillcolor == WHITE && ch10->fillcolor == WHITE))
			{//信息填写不完整
				messbox("信息未填写完整");
				cleardevice();
				sendPackage();
			}
		}
		if (strcmp(receiverPhone, g_currentUser->phoneNumber) == 0)// 取件人手机号与寄件人手机号相同
		{
			messbox("取件人手机号不能与寄件人手机号相同，请重新输入！");
			cleardevice();
			sendPackage();
		}
		if (couponOption == 1 && g_currentUser->couponCount == 0)
		{
			messbox("优惠券数量不足");
			cleardevice();
			sendPackage();
		}
		if (strcmp(receiverAddress, "吉大大学城") == 0)	//取件地址与寄件地址相同
		{
			messbox("取件地址不能与寄件地址相同，请重新输入！");
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
//****个人中心
void personalCenter()
{//个人中心
	buildWindow();
	struct button* p1 = button(450, 100, "身份码");
	struct button* p2 = button(450, 200, "会员升级");
	struct button* p3 = button(450, 300, "优惠福利");
	struct button* p4 = button(450, 400, "发送工单");
	struct button* p5 = button(450, 500, "退出登录");
	struct button* p6 = button(850, 550, "返回");
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
{//身份码窗口
	buildWindow();
	label(200, 250, "身份码：");
	label(450, 250, g_currentUser->identityCode);
	ExMessage m;
	int flag = 0;
	struct button* p = button(850, 550, "返回");
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
{//会员升级
	buildWindow();
	if (g_currentUser->userType == VIP)
	{
		struct button* p = button(500, 600, "返回");
		label(200, 200, "您已是尊贵的会员！");
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
		label(200, 200, "您是否愿意花费300元充值会员？");
		struct button* p1 = button(250, 600, "返回");
		struct button* p2 = button(550, 600, "充值");
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
{//优惠福利
	buildWindow();
	label(100, 200, "当前经验值：");
	label(300, 200, g_currentUser->experience);
	label(100, 300, "兑换优惠券需要消耗10点经验值");
	struct button* p1 = button(250, 600, "返回");
	struct button* p2 = button(550, 600, "兑换");
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
{//发送工单
	buildWindow();
	struct button* p1 = button(450, 180, "误取申请");
	struct button* p2 = button(450, 400, "损坏/丢失");
	struct button* p3 = button(850, 550, "返回");
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
{//误取申请
	char trackingNum[TRACKING_NUM] = { '\0' };
	if (searchWindow("请输入被误取包裹的快递单号", trackingNum, 10))
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
{//损坏/丢失申请
	char trackingNum[TRACKING_NUM] = { '\0' };
	if (searchWindow("请输入被损坏/丢失包裹的快递单号", trackingNum, 10))
	{
		sendticket(2, trackingNum);
		sendTicket();
	}
	else
	{
		sendTicket();

	}
}

//***************************************************************************管理员界面*******************************************************************************
//管理员首界面（菜单界面）
void managerMenu()
{//管理员首界面
	buildWindow();
	struct button* p1 = button(450, 120, "智能库存");
	struct button* p2 = button(450, 230, "用户管理");
	struct button* p3 = button(450, 340, "数据分析");
	struct button* p4 = button(450, 450, "工单处理");
	struct button* p6 = button(850, 50, "修改时间");
	struct button* p5 = button(850, 550, "退出");
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
//修改时间
void settimeMenu()
{
	buildWindow();
	label(300, 100, "请输入想让驿站变成的时间");
	struct button* p1 = button(650, 550, "确定");
	struct button* p2 = button(350, 550, "返回");
	label(100, 200, "年份：");
	inputbox(450, 200);
	int year = 0;
	char Year[5] = { '\0' };

	label(100, 300, "月份：");
	inputbox(450, 300);
	int month = 0;
	char Month[3] = { '\0' };

	label(100, 400, "日期：");
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
					messbox("输入格式错误，请重新输入");
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
			messbox("错误：非法日期值");
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
	struct button* p1 = button(450, 250, "校准时差");
	struct button* p2 = button(850, 550, "返回");
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
		fprintf(stderr, "日期输入无效\n");
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
	setStationTime(startdate);//创建好了时差
	saveTime();//保存创建好的时差
	nowtime = getStationTime();//获得现在驿站时间
	//下面根据现在驿站时间来判断优惠券功能是否过期
	//优惠券开始时间是3.1日0：00，三个月后就是6.1日0：00
	double threeMonthsInSeconds = (31 + 30 + 31) * 24 * 3600; // 三个月的秒数差
	struct tm activitystarttime = {};
	activitystarttime.tm_year = 125;
	activitystarttime.tm_mon = 2;//2代表3月
	activitystarttime.tm_mday = 1;
	activitystarttime.tm_hour = 0;
	activitystarttime.tm_min = 0;
	activitystarttime.tm_sec = 0;
	mktime(&activitystarttime);
	time_t 	activitystarttime_s = mktime(&activitystarttime);//开始日期秒数
	if (difftime(nowtime, activitystarttime_s) >= threeMonthsInSeconds)//如果超越三个月，那么开始删除
	{
		//遍历用户链表，并且把他们的优惠券都清零
		ListNode* head = getUsers()->head->next;
		for (ListNode* node = head; node != NULL; node = node->next)
		{
			User* us = (User*)node->data;
			us->couponCount = 0;
		}
	}
	//下面是工单删除部分
	deleteExpiredLogs();
	messbox("时间校准成功！");
}
//管理员智能库存界面
void warehouseMenu()
{//管理员智能库存界面
	buildWindow();
	struct button* p1 = button(450, 200, "实时看板");
	struct button* p2 = button(450, 400, "包裹追踪");
	struct button* p3 = button(850, 550, "返回");
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
{//实时看板
	buildWindow();
	int currentshelf = 1;  // 当前页面
	showWarehouse(currentshelf);// 显示第一页的数据
	struct button* p1 = button(850, 600, "返回");
	struct button* p2 = button(200, 550, "首页");
	struct button* p3 = button(350, 550, "上一页");
	struct button* p4 = button(500, 550, "下一页");
	struct button* p5 = button(650, 550, "末页");
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
			{//首页
				if (currentshelf != 1)
				{//	不是首页
					currentshelf = 1;
					showWarehouse(currentshelf);
				}
			}
			if (isClickButton(p3, m))
			{//上一页
				if (currentshelf != 1)
				{//不是首页
					currentshelf--;
					showWarehouse(currentshelf);
				}
			}
			if (isClickButton(p4, m))
			{//下一页
				if (currentshelf < MAX_SHELVES)
				{//当前不是最后一页
					currentshelf++;
					showWarehouse(currentshelf);
				}
			}
			if (isClickButton(p5, m))
			{//末页
				if (currentshelf != MAX_SHELVES)
				{//当前不是最后一页
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
	label(50, 50, "追踪方式：");
	struct button* p1 = button(450, 150, "快递单号");
	struct button* p2 = button(450, 300, "寄件电话");
	struct button* p3 = button(450, 450, "收件电话");
	struct button* p4 = button(850, 550, "返回");
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
	if (searchWindow("请输入需要查找包裹的快递单号", trackingNum, 10))
	{
		Package refPackage = {};
		strncpy(refPackage.trackingNum, trackingNum, TRACKING_NUM);

		Package* foundPackage = (Package*)list_find(packageList, &refPackage, TRACKINGNUM_MODE, cmpPackage);
		if (foundPackage == NULL)
		{
			messbox("包裹不存在，请重新输入");
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
	if (searchWindow("请输入需要查找寄件人电话", senderPhone, 11))
	{
		Package refPackage = {};
		strncpy(refPackage.senderPhone, senderPhone, PHONE);

		Package* foundPackage = (Package*)list_find(packageList, &refPackage, SENDER_PHONE_MODE, cmpPackage);
		if (foundPackage == NULL)
		{
			messbox("包裹不存在，请重新输入");
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
	if (searchWindow("请输入需要查找收件人电话", receiverPhone, 11))
	{
		Package refPackage = {};
		strncpy(refPackage.receiverPhone, receiverPhone, PHONE);
		Package* foundPackage = (Package*)list_find(packageList, &refPackage, RECEIVER_PHONE_MODE, cmpPackage);
		if (foundPackage == NULL)
		{
			messbox("包裹不存在，请重新输入");
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
	if (flag == 1)//按快递单号查找
	{
		buildWindow();
		int currentpage = 0;  // 当前页面
		if (pagingWindow(trackPackageFoTrackingNumWindow, currentpage, 1, search) == 1)
		{
			trackPackageWindow();
		}
	}
	if (flag == 2)//按寄件电话查找
	{
		buildWindow();
		int currentpage = 0;  // 当前页面
		long long totalNumber = 0;
		if (pagingWindow(trackPackageFoSenderPhoneWindow, currentpage, trackPackageFoSenderPhoneNumber(totalNumber, search), search) == 1)
		{
			trackPackageWindow();
		}
	}
	if (flag == 3)//按收件电话查找
	{
		buildWindow();
		int currentpage = 0;  // 当前页面
		long long totalNumber = 0;
		if (pagingWindow(trackPackageFoReceiverPhoneWindow, currentpage, trackPackageFoReceiverPhoneNumber(totalNumber, search), search) == 1)
		{
			trackPackageWindow();
		}
	}
}
//管理员用户管理界面
void userManagementMenu()
{//管理员用户管理界面
	buildWindow();
	struct button* p1 = button(450, 120, "用户检索");
	struct button* p2 = button(450, 230, "删除用户");
	struct button* p3 = button(450, 340, "工单信息");
	struct button* p4 = button(450, 450, "日志信息");
	struct button* p5 = button(850, 550, "返回");
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
{//用户检索
	buildWindow();
	label(50, 50, "检索方式：");
	struct button* p1 = button(450, 200, "昵称检索");
	struct button* p2 = button(450, 400, "账号检索");
	struct button* p4 = button(850, 550, "返回");
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
	if (searchWindow("请输入需要查找用户的昵称", name, 0))
	{
		User refUser = {};
		strncpy(refUser.userName, name, 12);
		User* foundUser = (User*)list_find(userList, &refUser, NAME_MODE, cmpUser);
		//用户不存在
		if (foundUser == NULL)
		{
			messbox("用户不存在!");
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
	if (searchWindow("请输入需要查找用户的手机号", phoneNumber, 11))
	{
		User refUser = {};
		strncpy(refUser.phoneNumber, phoneNumber, PHONE);
		User* foundUser = (User*)list_find(userList, &refUser, PHONE_MODE, cmpUser);
		//用户不存在
		if (foundUser == NULL)
		{
			messbox("用户不存在!");
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
	if (flag == 1)//按昵称查找
	{
		buildWindow();
		int currentpage = 0;  // 当前页面
		long long totalNumber = 0;
		if (pagingWindow(trackPackageFoNameWindow, currentpage, trackPackageFoNameNumber(totalNumber, search), search) == 1)
		{
			managerFindUserWindow();
		}
	}
	if (flag == 2)
	{
		buildWindow();
		int currentpage = 0;  // 当前页面
		if (pagingWindow(trackPackageFoPhoneNumberWindow, currentpage, 1, search) == 1)
		{
			managerFindUserWindow();
		}
	}
}
void managerDeleteUserWindow()
{//删除用户
	char phoneNumber[PHONE] = { '\0' };
	if (searchWindow("请输入需要删除用户的手机号", phoneNumber, 11))
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
{//工单信息
	buildWindow();
	label(50, 50, "排序方式：");
	struct button* p1 = button(450, 200, "种类排序");
	struct button* p2 = button(450, 400, "时间排序");
	struct button* p4 = button(850, 550, "返回");
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
{//日志信息
	buildWindow();
	int currentpage = 0;
	long long allLogsTotalNumber = 0;
	if (pagingWindow(showAllLogsWindow, currentpage, getAllLogsTotalNumber(allLogsTotalNumber), NULL) == 1)
	{
		userManagementMenu();
	}
}
//管理员数据分析界面
void StasticsAnlysisMenu()
{//管理员数据分析界面
	buildWindow();
	struct button* p1 = button(450, 180, "每周简报");
	struct button* p2 = button(450, 400, "周期预测");
	struct button* p3 = button(850, 550, "返回");
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
{//每周简报
	buildWindow();
	WeeklyBriefly();
	struct button* p1 = button(500, 600, "返回");
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
	label(300, 100, "请输入需要预测的起止时间");
	struct button* p1 = button(650, 550, "确定");
	struct button* p2 = button(350, 550, "返回");
	label(100, 200, "年份：");
	inputbox(450, 200);
	int year = 0;
	char Year[5] = { '\0' };

	label(100, 300, "月份：");
	inputbox(450, 300);
	int month = 0;
	char Month[3] = { '\0' };

	label(100, 400, "日期：");
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
					messbox("输入格式错误，请重新输入");
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
			messbox("错误：非法日期值");
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
	struct button* p1 = button(450, 180, "拟合图像");
	struct button* p2 = button(450, 400, "预测未来");
	struct button* p3 = button(850, 550, "返回");
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
		free(p1);//拟合图像部分
		MainpartInfo(year, month, day);
		break;
	case 2:
		free(p2);//预测未来部分
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
{//拟合图像部分
	buildWindow();
	Mainpart(year, month, day);

}
void futureData(int year, int month, int day)
{
	futuredata(year, month, day);
}
//管理员   工单处理   界面
void AddressTicketMenu()
{//管理员工单处理界面
	buildWindow();
	struct button* p1 = button(450, 200, "误取处理");
	struct button* p2 = button(450, 400, "损坏丢失");
	struct button* p3 = button(850, 550, "返回");
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
{//误取处理界面
	char ticketid[50] = { '\0' };
	if (searchWindow("请输入需要处理误取工单的工单编号", ticketid, 10))
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
{//损坏丢失处理界面
	char ticketid[50] = { '\0' };
	if (searchWindow("请输入需要处理损坏丢失工单的工单编号", ticketid, 10))
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
//******************************************************************运营员界面************************************************************************************
//运营员首界面
void operaterWindow()
{
	buildWindow();
	struct button* p1 = button(450, 100, "包裹入库");
	struct button* p2 = button(450, 200, "送件到楼");
	struct button* p3 = button(450, 300, "上门取件");
	struct button* p6 = button(450, 400, "包裹寄件");
	struct button* p4 = button(450, 500, "通知提醒");
	struct button* p5 = button(850, 550, "退出");
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
//录入信息
void putInMessage()
{
	buildWindow();
	label(50, 100, "快递单号:");
	inputbox(200, 100);
	char  trackingNum[TRACKING_NUM] = { '\0' };

	label(500, 100, "包裹名称:");
	inputbox(650, 100);
	char packageName[NAME] = { '\0' };
	text(850, 100, "六个字以内");

	label(50, 200, "包裹类型:");
	PackageType packagetype{};
	struct choice* ch1 = choice(200, 200, "普通");
	struct choice* ch2 = choice(300, 200, "贵重");
	struct choice* ch3 = choice(400, 200, "易碎");

	label(500, 200, "包裹重量:");
	inputbox(650, 200);
	char weight[50] = { '\0' };
	double w = 0.0;
	text(850, 200, "(千克)");

	label(50, 300, "包裹体积:");
	inputbox(200, 300);
	char volume[50] = { '\0' };
	double v = 0.0;
	text(400, 300, "(立方米)");

	label(500, 300, "收件人电话");
	inputbox(650, 300);
	char  receiverPhone[PHONE] = { '\0' };


	label(50, 400, "寄件地址:");
	inputboxAdress(200, 400);
	char senderAddress[ADDRESS] = { '\0' };
	struct button* p1 = button(250, 600, "返回");
	struct button* p2 = button(550, 600, "确定");
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
					messbox("信息未填写完整");
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
//送件到楼
void deliverToHomeWindow()
{
	buildWindow();
	struct button* p1 = button(450, 200, "显示信息");
	struct button* p2 = button(450, 400, "确认送达");
	struct button* p3 = button(850, 600, "返回");
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
{//显示信息
	buildWindow();
	int currentpage = 0;  // 当前页面
	long long deliverToHomeTotalNumber = 0;
	if (pagingWindow(deliverToHomeWindow, currentpage, deliverToHomeNumber(deliverToHomeTotalNumber), NULL) == 1)
	{
		deliverToHomeWindow();
	}
}
void deliverToHomeComeTure()
{//确认送达
	char trackingNum[TRACKING_NUM] = { '\0' };
	if (searchWindow("请输入确定已经送达到楼包裹的快递单号", trackingNum, 10))
	{
		deliverToHomeMakeTrue(trackingNum);
		deliverToHomeComeTure();
	}
	else
	{
		deliverToHomeWindow();

	}
}
//上门取件
void pickUpFromHomeWindow()
{
	buildWindow();
	struct button* p1 = button(450, 200, "显示信息");
	struct button* p2 = button(450, 400, "确认取件");
	struct button* p3 = button(850, 600, "返回");
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
{//显示信息
	buildWindow();
	int currentpage = 0;  // 当前页面
	long long pickUpFromHomeTotalNumber = 0;
	if (pagingWindow(pickUpFromHomeWindow, currentpage, pickUpFromHomeNumber(pickUpFromHomeTotalNumber), NULL) == 1)
	{
		pickUpFromHomeWindow();
	}
}
void pickUpFromHomeComeTure()
{//确认取件
	char trackingNum[TRACKING_NUM] = { '\0' };
	buildWindow();
	label(300, 150, "请输入确定已经取件包裹的快递单号");
	if (searchWindow("请输入确定已经取件包裹的快递单号", trackingNum, 10))
	{
		pickUpFromHomeMakeTrue(trackingNum);
		pickUpFromHomeComeTure();
	}
	else
	{
		pickUpFromHomeWindow();
	}
}
//包裹寄件
void sendPackageMakeMenu() {
	buildWindow();
	struct button* p1 = button(450, 200, "显示信息");
	struct button* p2 = button(450, 400, "确认寄件");
	struct button* p3 = button(850, 600, "返回");
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
	int currentpage = 0;  // 当前页面
	long long deliverToHomeTotalNumber = 0;
	if (pagingWindow(displayPointDeliveryPackages, currentpage, countPackagesForPointDelivery(deliverToHomeTotalNumber), NULL) == 1)
	{
		sendPackageMakeMenu();
	}
}
void sendPackageMakeSure() {
	char trackingNum[TRACKING_NUM] = { '\0' };
	buildWindow();
	label(300, 150, "请输入确定寄出包裹的快递单号");
	if (searchWindow("请输入确定寄出包裹的快递单号", trackingNum, 10))
	{
		confirmPointDelivery(trackingNum);
		sendPackageMakeSure();
	}
	else
	{
		sendPackageMakeMenu();
	}
}
//通知提醒
void sendNotificationWindow()
{
	char hour[10] = { '\0' };
	buildWindow();
	label(300, 150, "请输入需要设定的时间阈值");
	if (searchWindow("请输入需要设定的时间阈值", hour, 2))
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
	int startpage = 1;//获取第一页
	int currentpage = startpage;//当前页面为第一页
	long long lastpage;
	if (totalNumber % 9 != 0)
	{
		lastpage = totalNumber / 9 + 1;
	}
	else
	{
		lastpage = totalNumber / 9;
	}//获取最后一页
	sendNotificationWindow(startpage, totalNumber, NULL, customHoursDiff);// 显示第一页的数据
	struct button* p1 = button(850, 600, "返回");
	struct button* p2 = button(200, 550, "首页");
	struct button* p3 = button(350, 550, "上一页");
	struct button* p4 = button(500, 550, "下一页");
	struct button* p5 = button(650, 550, "末页");
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
			{//首页
				if (currentpage == startpage)
				{//已是首页
					;
				}
				else
				{
					currentpage = 1;
					sendNotificationWindow(currentpage, totalNumber, NULL, customHoursDiff);
				}
			}
			if (isClickButton(p3, m))
			{//上一页
				if (currentpage == startpage)
				{//已是首页
					;
				}
				else
				{
					currentpage--;
					sendNotificationWindow(currentpage, totalNumber, NULL, customHoursDiff);
				}
			}
			if (isClickButton(p4, m))
			{//下一页
				if (currentpage != lastpage)
				{//当前不是最后一页
					currentpage++;
					sendNotificationWindow(currentpage, totalNumber, NULL, customHoursDiff);
				}
				else
				{
					;
				}
			}
			if (isClickButton(p5, m))
			{//末页
				if (currentpage != lastpage)
				{//当前不是最后一页
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

