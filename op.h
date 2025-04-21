#pragma once

#include "common.h"
#include "list.h"
#include"fore.h"

#define PACKAGE_FILE "packages.dat"
#define SHELF_STATUS_FILE "shelfstatus.dat"
#define MAX_SHELVES 10  
#define INIT_LEVELS 5   

#define VIP_SHELF_ID 10   // 贵重品专用货架编号
#define LEVEL_CAPACITY 4.0  // 层级容积
#define BULKY_VOLUME 0.5  // 大件体积阈值
#define HEAVY_WEIGHT 1.0  // 重包裹阈值
static ShelfLevel wareHouse[MAX_SHELVES][INIT_LEVELS];
extern List* packageList;

// 工具函数
int validateWeight(double weight);
int validateVolume(double volume);
int validatePackageType(int packageType);
int isTrackingNumExist(const char* trackingNum);

// 货架管理函数
void initializeShelves();
void saveShelves();
void loadPackages();
void savePackages();
void freePackages();
void showWarehouse(int currentshelf);
void updateShelfAfterPickup(Package* pkg);

// 包裹处理函数
int placePackageOnShelf(Package* pkg);
char* InputPackageInfo(char* trackingNum, char* packageName, PackageType m, double volume, double weight, char* senderAddress, char* receiverPhone);

// 送货上门功能
long long deliverToHomeNumber(long long deliverToHomeTotalNumber);
void deliverToHomeWindow(int page, long long deliverToHomeTotalNumber, char* search);
void deliverToHomeMakeTrue(char* trackingNum);

// 上门取件功能
long long pickUpFromHomeNumber(long long pickUpFromHomeTotalNumber);
void pickUpFromHomeWindow(int page, long long pickUpFromHomeTotalNumber, char* search);
void pickUpFromHomeMakeTrue(char* trackingNum);

// 通知提醒功能
long long sendNotificationNumber(long long sendNotificationTotalNumber, double customHoursDiff);
void sendNotificationWindow(int page, long long sendNotificationTotalNumber, char* search, double customHoursDiff);

//
long long countPackagesForPointDelivery(long long totalPackages);
void displayPointDeliveryPackages(int page, long long totalPackages, char* search);
void confirmPointDelivery(char* trackingNum);