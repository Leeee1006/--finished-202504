#pragma once
#include "common.h"

#define PACKAGE_FILE "packages.dat"

#define MAX_SHELVES 10  
#define INIT_LEVELS 5   

#define VIP_SHELF_ID 10   // ����Ʒר�û��ܱ��
#define LEVEL_CAPACITY 4.0  // �㼶�ݻ�
#define BULKY_VOLUME 0.5  // ��������ֵ
#define HEAVY_WEIGHT 1.0  // �ذ�����ֵ

// У�������Ƿ�Ϸ�
int validateWeight(double weight);

// У������Ƿ�Ϸ�
int validateVolume(double volume);

// У����������Ƿ�Ϸ�
int validatePackageType(int packageType);

// ��ȫ�ڴ����
void* safeMalloc(size_t size, const char* context);

// ��ȫ�ļ�����
FILE* safeFopen(const char* path, const char* mode);

// ��ʼ�����ܽṹ
void initializeShelves();

// �������а������ݲ����»���״̬
void loadPackages();

// ������ID�Ƿ��Ѵ���
int isTrackingNumExist(const char* trackingNum, Package* head);

// �ͷŰ�������
void freePackages();

// ���ð���
int placePackageOnShelf(Package* pkg);

// ��¼������Ϣ
void savePackages();

void sendNotification(int hoursThreshold);

void pickUpFromHome();

void deliverToHome();

