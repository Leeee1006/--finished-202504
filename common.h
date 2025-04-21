#pragma once
#pragma warning(disable:4200)
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <easyx.h>
#include <math.h>
#include <time.h>
#include <stdbool.h> 

#define DIGITS          21 // ���ִ�����
#define PHONE           12  // �ֻ��ų���
#define NAME            13  // ���Ƴ���
#define PASSWORD        7  // ���볤��
#define ID_CODE         31  // ����볤��
#define TRACKING_NUM    11  // ��ݵ��ų���
#define ADDRESS         51 // ��ַ������
#define DESCR           101 // ��������

#define LOG_FILE        "logs.dat"
#define PACKAGE_FILE    "packages.dat"
#define SHELF_FILE      "shelfstatus.dat"
#define TICKET_FILE     "tickets.dat"
#define TIME_FILE       "time.dat"
#define USER_FILE       "users.dat"

/* �û����� */
typedef enum {
    Regular,
    VIP,
    Operator,
    Admin
} UserType;

/* �������� */
typedef enum {
    PackageStandard,
    Parcel,
    Fragile
} PackageType;

/* �ļ���ʽ */
typedef enum {
    ShippingStandard,
    Express,
    Economic
} ShippingMethod;

/* ����״̬ */
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

/* �������� */
typedef enum {
    Miscollection,
    DamageLoss,
} TicketType;

/* ���ܲ���Ϣ */
typedef struct {
    float volumeCapacity;
    float occupiedVolume;
    int packageNum;
} ShelfLevel;

/* ʱ����Ϣ */
typedef struct {
    time_t ordered;
    time_t shipped;
    time_t canceled;
    time_t pending;
    time_t delivered;
    time_t refused;
} PackageTime;

/* �û���Ϣ */
typedef struct User {
    unsigned int experience;
    unsigned short couponCount;
    unsigned short discount;
    UserType userType;
    char userName[NAME];
    char phoneNumber[PHONE];
    char identityCode[ID_CODE];
    char password[PASSWORD];
} User;

/* ������Ϣ */
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
    PackageTime time;
    char trackingNum[TRACKING_NUM];
    char packageName[NAME];
    char senderPhone[PHONE];
    char senderAddress[ADDRESS];
    char receiverPhone[PHONE];
    char receiverAddress[ADDRESS];
    char pickupCode[ID_CODE];
    char dormAddress[ADDRESS]; //�������λ��
} Package;

/* ������Ϣ */
typedef struct Ticket {
    time_t createdTime;
    int ticketId;
    TicketType ticketType;
    char description[DESCR];
	char phoneNumber[PHONE];
	char pkgTrackingNum[TRACKING_NUM];
	bool isHandled;
} Ticket;

/* ��־��Ϣ */
typedef struct Log {
    time_t createdTime;
    struct Log* nextLog;
    char description[DESCR];
} Log;

/* ͳ������ */
typedef struct {
    double weeklyRevenue;
    int sendCount;
    int pickupCount;
    int remainPackages;
} Statistics;
