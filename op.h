#pragma once

#include "common.h"
#include "list.h"

#define PACKAGE_FILE "packages.dat"
#define SHELF_STATUS_FILE "shelfstatus.dat"
#define MAX_SHELVES 10  
#define INIT_LEVELS 5   

#define VIP_SHELF_ID 10   // ����Ʒר�û��ܱ��
#define LEVEL_CAPACITY 4.0  // �㼶�ݻ�
#define BULKY_VOLUME 0.5  // ��������ֵ
#define HEAVY_WEIGHT 1.0  // �ذ�����ֵ

extern List* packageList;

/**************************** ���ߺ��� *******************************/
int validateWeight(double weight);
int validateVolume(double volume);
int validatePackageType(int packageType);
int isTrackingNumExist(const char* trackingNum);

/**************************** ���ܹ����� *******************************/
void initializeShelves();
void saveShelves();
void loadPackages();
void savePackages();
void freePackages();

/**************************** ���������� *******************************/
void findOptimalLayer(Package* pkg, int* bestShelf, int* bestLevel);
void generatePickupCode(int shelfId, int levelNum, Package* pkg);
int placePackageOnShelf(Package* pkg);

/**************************** �ͼ���ȡ������ *******************************/
void deliverToHome();
void pickUpFromHome();
void sendNotification(int hoursThreshold);