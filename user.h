#pragma once
#include "common.h"
#include "list.h"
#include "package.h"
#include "log.h"
#include "ticket.h"
#include "timeFormat.h"
#include "manager.h"
#include"fore.h"

#define UPGRADE_FEE 300.0       // ��Ա��������
#define COUPON_VALUE 5.0        // �Ż�ȯ���
#define EXP_COEF 100				// ����ֵϵ��
#define EXP_OF_PER_COUPON 10	// �һ�ÿ���Ż�ȯ���ĵľ���ֵ

enum UserModes
{
	PHONE_MODE = 1 << 0,
	NAME_MODE = 1 << 1,
};

List* getUsers();

bool cmpUser(const void* d1, const void* d2, int mode);

char* generateIdentityCode(const char* phone);


// ************************************

// ���ܣ����հ���
void refusePackage(char* trackingNum);

// ************************************

// ���ܣ�ȡ������
void cancelPackage(char* trackingNum);


// ************************************

// ���ܣ�ȡ��
void pickupPackage(char* trackingNum);

// ���ܣ��ļ�
//�������������ƣ��ռ��˵�ַ�������ַ���ռ����ֻ��ţ���������������������ļ���ʽѡ���������ѡ��Ƿ�����ȡ��ѡ��
void sendPackageInfo(char* packageName, char* receiverAddress, char* receiverPhone, char* dormAddress, float weight, float volume, int shippingMethodOption,
	int packageTypeOption, int homeSentOption, int couponOption);

// ************************************
//���ܣ������ͻ�����
//��������ݵ��ţ��ռ���ַ
void deliverToHomePackage(char* trackingNum, char* receiverAddress);


long long  trackPackageFoNameNumber(long long TotalNumber, char* name);

void trackPackageFoNameWindow(int page, long long TotalNumber, char* name);

void trackPackageFoPhoneNumberWindow(int page, long long TotalNumber, char* phoneNumber);
// ���ܣ���Ա����
void userupgrade();

// ���ܣ����͹���
void sendticket(int ticketTypeOption, char* pkgTrackingNum);

// ���ܣ��һ��Ż�ȯ
void exchangecoupons(int number);