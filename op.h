#pragma once

#include "common.h"
#include "list.h"

#define PACKAGE_FILE "packages.dat"
#define SHELF_STATUS_FILE "shelfstatus.dat"
#define MAX_SHELVES 10  
#define INIT_LEVELS 5   

#define VIP_SHELF_ID 10   // 贵重品专用货架编号
#define LEVEL_CAPACITY 4.0  // 层级容积
#define BULKY_VOLUME 0.5  // 大件体积阈值
#define HEAVY_WEIGHT 1.0  // 重包裹阈值

extern List* packageList;

/**************************** 工具函数 *******************************/
int validateWeight(double weight);
int validateVolume(double volume);
int validatePackageType(int packageType);
int isTrackingNumExist(const char* trackingNum);

/**************************** 货架管理函数 *******************************/
void initializeShelves();
void saveShelves();
void loadPackages();
void savePackages();
void freePackages();

/**************************** 包裹处理函数 *******************************/
void findOptimalLayer(Package* pkg, int* bestShelf, int* bestLevel);
void generatePickupCode(int shelfId, int levelNum, Package* pkg);
int placePackageOnShelf(Package* pkg);

/**************************** 送件和取件功能 *******************************/
void deliverToHome();
void pickUpFromHome();
void sendNotification(int hoursThreshold);