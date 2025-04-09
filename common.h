#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <graphics.h>
#include <math.h>
#include <time.h>
#include <stdbool.h> 

#define PHONE           12  // 手机号长度
#define NAME            13  // 名称长度
#define PASSWORD        7  // 密码长度
#define ID_CODE         23  // 身份码长度
#define TRACKING_NUM    8  // 快递单号长度
#define ADDRESS         51 // 地址名长度
#define DESCR           101 // 描述长度

/* 用户类型 */
typedef enum {
    Regular,
    VIP,
    Operator,
    Admin
} UserType;

/* 包裹类型 */
typedef enum {
    PackageStandard,
    Parcel,
    Fragile
} PackageType;

/* 寄件方式 */
typedef enum {
    ShippingStandard,
    Express,
    Economic
} ShippingMethod;

/* 包裹状态 */
typedef enum {
    Ordered,
    Shipped,
    Pending,
    Delivered,
    Refused,
    Canceled,
    Misdelivered,
    DamagedLost
} PackageState;

/* 工单类型 */
typedef enum {
    Miscollection,
    DamageLoss,
    ComplaintSuggestion,
    ComplaintSuggestionAddressed
} TicketType;

/* 货架层信息 */
typedef struct {
    float volumeCapacity;
    float occupiedVolume;
    int packageNum;
} ShelfLevel;

/* 时间信息 */
typedef struct {
    time_t ordered;
    time_t shipped;
    time_t canceled;
    time_t pending;
    time_t delivered;
    time_t refused;
} PackageTime;

/* 用户信息 */
typedef struct User {
    unsigned int experience;
    unsigned short couponCount;
    unsigned short discount;
    UserType userType;
    struct User* nextUser;
    char userName[NAME];
    char phoneNumber[PHONE];
    char identityCode[ID_CODE];
    char password[PASSWORD];
} User;

/* 包裹信息 */
typedef struct Package {
    float volume;
    float weight;
    float shippingFee;
    PackageType packageType;
    ShippingMethod shippingMethod;
    PackageState packageState;
    unsigned short usedCouponNum;
    bool isHomeDelivered;
    bool isHomeSent;
    struct Package* nextPackage;
    PackageTime time;
    char trackingNum[TRACKING_NUM];
    char packageName[NAME];
    char senderPhone[PHONE];
    char senderAddress[ADDRESS];
    char receiverPhone[PHONE];
    char receiverAddress[ADDRESS];
    char pickupCode[ID_CODE];
    char pickupAddress[ADDRESS];
} Package;

/* 工单信息 */
typedef struct Ticket {
    time_t createdTime;
    unsigned short ticketId;
    TicketType ticketType;
    struct Ticket* nextTicket;
    char description[DESCR];
    char phoneNumber[PHONE];
    char trackingNum[TRACKING_NUM];
    bool isHandled;
} Ticket;

/* 日志信息 */
typedef struct Log {
    time_t createdTime;
    struct Log* nextLog;
    char description[DESCR];
} Log;

/* 统计数据 */
typedef struct {
    double weeklyRevenue;
    int sendCount;
    int pickupCount;
    int remainPackages;
} Statistics;
