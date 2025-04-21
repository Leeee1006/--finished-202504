#pragma once
#include "common.h"
#include "list.h"
#include "user.h"
#include "log.h"
#include "timeFormat.h"

enum PackageModes
{
	TRACKINGNUM_MODE = 1 << 0,
	SENDER_PHONE_MODE = 1 << 1,
	RECEIVER_PHONE_MODE = 1 << 2,
	PACKAGESTATE_MODE = 1 << 3,
};

List* getPackages();

bool comparePackageByTime(const void* d1, const void* d2);

bool cmpPackage(const void* d1, const void* d2, int mode);

void sortPackagesByTime(int curchoice);

// 功能：计算运费
// 参数：包裹指针
// 返回：运费
double calculateShippingFee(Package* package, User* user);

// 功能：生成快递单号
// 返回：快递单号字符串
char* generateTrackingNumber();

// 功能：获取已下单包裹总量
// 参数：包裹链表指针，寄件人手机号，总数
// 返回：已下单包裹总量
long long getPackageOrderedNum(char* senderPhone, long long totalNum);

// 功能：显示已下单包裹总量
// 参数：包裹链表指针，寄件人手机号,当前界面，包裹总数
void showPackageOrderedWindow(int currentpage, long long totalNum, char* senderPhone);

// 功能：获取已取消包裹总量
// 参数：包裹链表指针，寄件人手机号，总数
// 返回：已取消包裹总量
long long getPackageCanceledNum(char* senderPhone, long long totalNum);

// 功能：显示已取消包裹
// 参数：包裹链表指针，寄件人手机号,当前界面，包裹总数
void showPackageCanceledWindow(int currentpage, long long totalNum, char* senderPhone);

// 功能：获取已寄出包裹总量
// 参数：包裹链表指针，寄件人手机号，总数
// 返回：已寄出包裹总量
long long getPackageShippedNum(char* senderPhone, long long totalNum);
// 功能：显示已寄出包裹
// 参数：包裹链表指针，寄件人手机号,当前界面，包裹总数
void showPackageShippedWindow(int currentpage, long long totalNum, char* senderPhone);

// 功能：获取待取件包裹总量
// 参数：包裹链表指针，收件人手机号，总数
long long getPackagePendingNum(char* receiverPhone, long long totalNum);

// 功能：显示待取件包裹
// 参数：包裹链表指针，收件人手机号,当前界面，包裹总数
void showPackagePendingWindow(int currentpage, long long totalNum, char* receiverPhone);

// 功能：获取已拒收包裹总量
// 参数：包裹链表指针，收件人手机号，总数
long long getPackageRefusedNum(char* receiverPhone, long long totalNum);
// 功能：显示已拒收包裹
// 参数：包裹链表指针，收件人手机号,当前界面，包裹总数
void showPackageRefusedWindow(int currentpage, long long totalNum, char* receiverPhone);

// 功能：获取已签收包裹总量
// 参数：包裹链表指针，取件人手机号，总数
long long getPackageDeliveredNum(char* receiverPhone, long long totalNum);
// 功能：显示已签收包裹
// 参数：包裹链表指针，取件人手机号,当前界面，包裹总数
void showPackageDeliveredWindow(int currentpage, long long totalNum, char* receiverPhone);

