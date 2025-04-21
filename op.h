#pragma once

#include "common.h"
#include "list.h"
#include "fore.h"
#include <unordered_set>
#include <string>

// 全局哈希表，用于存储所有已生成的取件码
extern std::unordered_set<std::string> pickupCodeSet;

// 文件路径定义
#define PACKAGE_FILE "packages.dat"
#define SHELF_STATUS_FILE "shelfstatus.dat"

// 货架相关常量
#define MAX_SHELVES 10          // 最大货架数
#define INIT_LEVELS 5           // 每个货架的初始层数
#define VIP_SHELF_ID 10         // 贵重品专用货架编号
#define LEVEL_CAPACITY 4.0      // 每层的体积容量
#define BULKY_VOLUME 0.5        // 大件包裹体积阈值
#define HEAVY_WEIGHT 1.0        // 重包裹重量阈值

// 全局变量
static ShelfLevel wareHouse[MAX_SHELVES][INIT_LEVELS]; // 仓库货架
extern List* packageList;                              // 包裹链表


// 工具函数
int validateWeight(double weight);                     // 校验重量
int validateVolume(double volume);                     // 校验体积
int validatePackageType(int packageType);              // 校验包裹类型
int isTrackingNumExist(const char* trackingNum);       // 检查快递单号是否存在

// 货架管理函数
void initializeShelves();                              // 初始化货架
void saveShelves();                                    // 保存货架状态
void loadPackages();                                   // 加载包裹数据
void savePackages();                                   // 保存包裹数据
void freePackages();                                   // 释放包裹数据
void showWarehouse(int currentshelf);                 // 显示仓库状态
void updateShelfAfterPickup(Package* pkg);            // 更新货架状态（取件后）

// 包裹处理函数
int placePackageOnShelf(Package* pkg);                // 放置包裹到货架
char* InputPackageInfo(char* trackingNum, char* packageName, PackageType m, double volume, double weight, char* senderAddress, char* receiverPhone);

// 送货上门功能
long long deliverToHomeNumber(long long deliverToHomeTotalNumber); // 获取送货上门包裹数量
void deliverToHomeWindow(int page, long long deliverToHomeTotalNumber, char* search); // 显示送货上门界面
void deliverToHomeMakeTrue(char* trackingNum);       // 确认送货上门完成

// 上门取件功能
long long pickUpFromHomeNumber(long long pickUpFromHomeTotalNumber); // 获取上门取件包裹数量
void pickUpFromHomeWindow(int page, long long pickUpFromHomeTotalNumber, char* search); // 显示上门取件界面
void pickUpFromHomeMakeTrue(char* trackingNum);     // 确认上门取件完成

// 通知提醒功能
long long sendNotificationNumber(long long sendNotificationTotalNumber, double customHoursDiff); // 获取需要提醒的包裹数量
void sendNotificationWindow(int page, long long sendNotificationTotalNumber, char* search, double customHoursDiff); // 显示通知提醒界面

// 快递点寄件功能
long long countPackagesForPointDelivery(long long totalPackages); // 获取快递点寄件包裹数量
void displayPointDeliveryPackages(int page, long long totalPackages, char* search); // 显示快递点寄件界面
void confirmPointDelivery(char* trackingNum); // 确认快递点寄件完成
