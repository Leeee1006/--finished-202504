#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "common.h"
#include "login.h"
#include "op.h"
#include "manager.h"
#include "user.h"
#include "log.h"
#include "tendencypredict.h"

#define FONT "consolas"

extern List* packageList; // 全局包裹链表指针
extern List* userList; // 全局用户链表指针
extern List* g_tickets; // 全局工单链表指针
extern List* g_logs; // 全局日志链表指针
extern User* g_currentUser; // 当前用户指针
struct button {
	int x;
	int y;
	COLORREF curcolor;
	COLORREF incolor = RGB(90, 209, 196);
	COLORREF outcolor = RGB(87, 62, 148);
	char* text;
};
struct choice {
	int x;
	int y;
	COLORREF fillcolor;
	COLORREF clickcolor = RGB(90, 209, 196);
	COLORREF noclickcolor = WHITE;
	char* text;
};
void buildWindow();

void messbox(const char* arr);

void isinputbox(int x, int y, int flag, ExMessage m, char* s);

void isinputboxAdress(int x, int y, ExMessage m, char* s);

void inputbox(int x, int y);

void inputboxAdress(int x, int y);

void drawButton(struct button* pb);

void drawChioce(struct choice* ch);

void label(int x, int y, const char* arr);

void label(int x, int y, double number);

void text(int x, int y, const char* arr);

void text(int x, int y, float number);

void text(int x, int y, int number);

void textRed(int x, int y, const char* arr);

void textRed(int x, int y, float number);

void textRed(int x, int y, int number);

bool isInButton(struct button* pb, ExMessage m);

bool isInChoice(struct choice* ch, ExMessage m);

bool isClickButton(struct button* pb, ExMessage m);

bool isClickChoice(struct choice* ch, ExMessage m);

struct button* button(int x, int y, const char* arr);

struct choice* choice(int x, int y, const char* arr);

int pagingWindow(void (*currentPage)(int, long long, char*), int currentpage, long long totalNumber, char* searchNum);

bool searchWindow(const char* arr, char* search, int flag);

void nextwindow(int year, int month, int day);

void futureData(int year, int month, int day);

void settimeMenu();

void alterinformation(int year, int month, int day);

void timeOperation(int year, int month, int day);


//************************************运营员界面**************************************************

void operaterWindow();

void putInMessage();

void deliverToHomeComeTure();

void deliverToHomeMessage();

void deliverToHomeWindow();

void pickUpFromHomeWindow();

void pickUpFromHomeMessage();

void pickUpFromHomeComeTure();

void sendNotificationWindow();

void sendNotificationInfo(double customHoursDiff);

void sendPackageMakeMenu();

void sendPackageMakeSure();

void  sendPackageMakeInfo();

//*****************************************************管理员界面*********************************************
//工单处理界面
void AddressTicketMenu();

void addressDamageLossWindow();

void addressMisdeliveryWindow();

//数据分析界面
void StasticsAnlysisMenu();

void WeeklyBrieflyMenu();

void MainpartMenu();

void MainpartInfo( int year, int month, int day);

//用户管理界面
void userManagementMenu();

void managerFindUserWindow();

void managerFindUserForName();

void managerFindUserForNumber();

void managerFindUserInfo(int flag, char* search);

void managerDeleteUserWindow();

void showTickets();

void showTicketsInfo();

void showAllLogs();
//智能库存界面
void warehouseMenu();

void showWarehouseWindow();

void trackPackageWindow();

void trackPackageFoTrackingNum();

void trackPackageFoSenderPhone();

void trackPackageFoReceiverPhone();

void showTrackPackageInfo(int flag, char* search);
//时间校准界面
void settimeMenu();
void alterinformation(int year, int month, int day);
void timeOperation(int year, int month, int day);
//首界面
void managerMenu();


//**************************用户界面***********************************************


void personalCenter();

void showIdentityCode();

void userUpgrade();

void exchangeCoupons();

void sendTicket();

void miscollection();

void damageLoss();

void pickupPackageMenu();

void sendPackage();

void showSendPackageInfo(char* packageName, char* receiverAddress, char* receiverPhone, char* dormAddress, float weight, float volume, int shippingMethodOption,
	int packageTypeOption, int homeSentOption, int couponOption);

void packageInfoMenu();

void packageShippedMenu();

void packageOrderedMenu();

void packageCanceledMenu();

void packageDeliveredMenu();

void packagePendingMenu();

void packagePendingInfo();

void packagePendWindow();

void packageRefusedMenu();

void packageRefusedWindow();

void packageRefusedInfo();

void packageOrderedInfo();

void cancelPackageWindow();

void userMenu();


//********************************登录注册界面***********************************************

void login();

void Register();

void registerAndLogin();
