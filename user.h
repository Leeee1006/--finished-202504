#pragma once
#include "common.h"
#include "list.h"
#include "package.h"
#include "log.h"
#include "ticket.h"
#include "timeFormat.h"
#include "manager.h"
#include"fore.h"

#define UPGRADE_FEE 300.0       // 会员升级花费
#define COUPON_VALUE 5.0        // 优惠券面额
#define EXP_COEF 100				// 经验值系数
#define EXP_OF_PER_COUPON 10	// 兑换每张优惠券消耗的经验值

enum UserModes
{
	PHONE_MODE = 1 << 0,
	NAME_MODE = 1 << 1,
};

List* getUsers();

bool cmpUser(const void* d1, const void* d2, int mode);

char* generateIdentityCode(const char* phone);


// ************************************

// 功能：拒收包裹
void refusePackage(char* trackingNum);

// ************************************

// 功能：取消包裹
void cancelPackage(char* trackingNum);


// ************************************

// 功能：取件
void pickupPackage(char* trackingNum);

// 功能：寄件
//参数：包裹名称，收件人地址，宿舍地址，收件人手机号，包裹重量，包裹体积，寄件方式选项，包裹类型选项，是否上门取件选项
void sendPackageInfo(char* packageName, char* receiverAddress, char* receiverPhone, char* dormAddress, float weight, float volume, int shippingMethodOption,
	int packageTypeOption, int homeSentOption, int couponOption);

// ************************************
//功能：申请送货上门
//参数：快递单号，收件地址
void deliverToHomePackage(char* trackingNum, char* receiverAddress);


long long  trackPackageFoNameNumber(long long TotalNumber, char* name);

void trackPackageFoNameWindow(int page, long long TotalNumber, char* name);

void trackPackageFoPhoneNumberWindow(int page, long long TotalNumber, char* phoneNumber);
// 功能：会员升级
void userupgrade();

// 功能：发送工单
void sendticket(int ticketTypeOption, char* pkgTrackingNum);

// 功能：兑换优惠券
void exchangecoupons(int number);