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

// ���ܣ������˷�
// ����������ָ��
// ���أ��˷�
double calculateShippingFee(Package* package, User* user);

// ���ܣ����ɿ�ݵ���
// ���أ���ݵ����ַ���
char* generateTrackingNumber();

// ���ܣ���ȡ���µ���������
// ��������������ָ�룬�ļ����ֻ��ţ�����
// ���أ����µ���������
long long getPackageOrderedNum(char* senderPhone, long long totalNum);

// ���ܣ���ʾ���µ���������
// ��������������ָ�룬�ļ����ֻ���,��ǰ���棬��������
void showPackageOrderedWindow(int currentpage, long long totalNum, char* senderPhone);

// ���ܣ���ȡ��ȡ����������
// ��������������ָ�룬�ļ����ֻ��ţ�����
// ���أ���ȡ����������
long long getPackageCanceledNum(char* senderPhone, long long totalNum);

// ���ܣ���ʾ��ȡ������
// ��������������ָ�룬�ļ����ֻ���,��ǰ���棬��������
void showPackageCanceledWindow(int currentpage, long long totalNum, char* senderPhone);

// ���ܣ���ȡ�Ѽĳ���������
// ��������������ָ�룬�ļ����ֻ��ţ�����
// ���أ��Ѽĳ���������
long long getPackageShippedNum(char* senderPhone, long long totalNum);
// ���ܣ���ʾ�Ѽĳ�����
// ��������������ָ�룬�ļ����ֻ���,��ǰ���棬��������
void showPackageShippedWindow(int currentpage, long long totalNum, char* senderPhone);

// ���ܣ���ȡ��ȡ����������
// ��������������ָ�룬�ռ����ֻ��ţ�����
long long getPackagePendingNum(char* receiverPhone, long long totalNum);

// ���ܣ���ʾ��ȡ������
// ��������������ָ�룬�ռ����ֻ���,��ǰ���棬��������
void showPackagePendingWindow(int currentpage, long long totalNum, char* receiverPhone);

// ���ܣ���ȡ�Ѿ��հ�������
// ��������������ָ�룬�ռ����ֻ��ţ�����
long long getPackageRefusedNum(char* receiverPhone, long long totalNum);
// ���ܣ���ʾ�Ѿ��հ���
// ��������������ָ�룬�ռ����ֻ���,��ǰ���棬��������
void showPackageRefusedWindow(int currentpage, long long totalNum, char* receiverPhone);

// ���ܣ���ȡ��ǩ�հ�������
// ��������������ָ�룬ȡ�����ֻ��ţ�����
long long getPackageDeliveredNum(char* receiverPhone, long long totalNum);
// ���ܣ���ʾ��ǩ�հ���
// ��������������ָ�룬ȡ�����ֻ���,��ǰ���棬��������
void showPackageDeliveredWindow(int currentpage, long long totalNum, char* receiverPhone);

