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

extern List* packageList; // ȫ�ְ�������ָ��
extern List* userList; // ȫ���û�����ָ��
extern List* g_tickets; // ȫ�ֹ�������ָ��
extern List* g_logs; // ȫ����־����ָ��
extern User* g_currentUser; // ��ǰ�û�ָ��
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


//************************************��ӪԱ����**************************************************

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

//*****************************************************����Ա����*********************************************
//�����������
void AddressTicketMenu();

void addressDamageLossWindow();

void addressMisdeliveryWindow();

//���ݷ�������
void StasticsAnlysisMenu();

void WeeklyBrieflyMenu();

void MainpartMenu();

void MainpartInfo( int year, int month, int day);

//�û��������
void userManagementMenu();

void managerFindUserWindow();

void managerFindUserForName();

void managerFindUserForNumber();

void managerFindUserInfo(int flag, char* search);

void managerDeleteUserWindow();

void showTickets();

void showTicketsInfo();

void showAllLogs();
//���ܿ�����
void warehouseMenu();

void showWarehouseWindow();

void trackPackageWindow();

void trackPackageFoTrackingNum();

void trackPackageFoSenderPhone();

void trackPackageFoReceiverPhone();

void showTrackPackageInfo(int flag, char* search);
//ʱ��У׼����
void settimeMenu();
void alterinformation(int year, int month, int day);
void timeOperation(int year, int month, int day);
//�׽���
void managerMenu();


//**************************�û�����***********************************************


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


//********************************��¼ע�����***********************************************

void login();

void Register();

void registerAndLogin();
