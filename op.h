#pragma once

#include "common.h"
#include "list.h"
#include"fore.h"

#define PACKAGE_FILE "packages.dat"
#define SHELF_STATUS_FILE "shelfstatus.dat"
#define MAX_SHELVES 10  
#define INIT_LEVELS 5   

#define VIP_SHELF_ID 10   // ����Ʒר�û��ܱ��
#define LEVEL_CAPACITY 4.0  // �㼶�ݻ�
#define BULKY_VOLUME 0.5  // ��������ֵ
#define HEAVY_WEIGHT 1.0  // �ذ�����ֵ
static ShelfLevel wareHouse[MAX_SHELVES][INIT_LEVELS];
extern List* packageList;

// ���ߺ���
int validateWeight(double weight);
int validateVolume(double volume);
int validatePackageType(int packageType);
int isTrackingNumExist(const char* trackingNum);

// ���ܹ�����
void initializeShelves();
void saveShelves();
void loadPackages();
void savePackages();
void freePackages();
void showWarehouse(int currentshelf);
void updateShelfAfterPickup(Package* pkg);

// ����������
int placePackageOnShelf(Package* pkg);
char* InputPackageInfo(char* trackingNum, char* packageName, PackageType m, double volume, double weight, char* senderAddress, char* receiverPhone);

// �ͻ����Ź���
long long deliverToHomeNumber(long long deliverToHomeTotalNumber);
void deliverToHomeWindow(int page, long long deliverToHomeTotalNumber, char* search);
void deliverToHomeMakeTrue(char* trackingNum);

// ����ȡ������
long long pickUpFromHomeNumber(long long pickUpFromHomeTotalNumber);
void pickUpFromHomeWindow(int page, long long pickUpFromHomeTotalNumber, char* search);
void pickUpFromHomeMakeTrue(char* trackingNum);

// ֪ͨ���ѹ���
long long sendNotificationNumber(long long sendNotificationTotalNumber, double customHoursDiff);
void sendNotificationWindow(int page, long long sendNotificationTotalNumber, char* search, double customHoursDiff);

//
long long countPackagesForPointDelivery(long long totalPackages);
void displayPointDeliveryPackages(int page, long long totalPackages, char* search);
void confirmPointDelivery(char* trackingNum);