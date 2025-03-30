#pragma once
#include "common.h"

#define PACKAGE_FILE "packages.dat"

#define MAX_SHELVES 10  
#define INIT_LEVELS 5   

#define VIP_SHELF_ID 10   // 贵重品专用货架编号
#define LEVEL_CAPACITY 4.0  // 层级容积
#define BULKY_VOLUME 0.5  // 大件体积阈值
#define HEAVY_WEIGHT 1.0  // 重包裹阈值

// 校验重量是否合法
int validateWeight(double weight);

// 校验体积是否合法
int validateVolume(double volume);

// 校验包裹类型是否合法
int validatePackageType(int packageType);

// 安全内存分配
void* safeMalloc(size_t size, const char* context);

// 安全文件操作
FILE* safeFopen(const char* path, const char* mode);

// 初始化货架结构
void initializeShelves();

// 加载现有包裹数据并更新货架状态
void loadPackages();

// 检查包裹ID是否已存在
int isTrackingNumExist(const char* trackingNum, Package* head);

// 释放包裹链表
void freePackages();

// 放置包裹
int placePackageOnShelf(Package* pkg);

// 记录包裹信息
void savePackages();

void sendNotification(int hoursThreshold);

void pickUpFromHome();

void deliverToHome();

