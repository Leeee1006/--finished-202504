#pragma once

#include "common.h"
#include "list.h"
#include "fore.h"
#include <unordered_set>
#include <string>

// ȫ�ֹ�ϣ�����ڴ洢���������ɵ�ȡ����
extern std::unordered_set<std::string> pickupCodeSet;

// �ļ�·������
#define PACKAGE_FILE "packages.dat"
#define SHELF_STATUS_FILE "shelfstatus.dat"

// ������س���
#define MAX_SHELVES 10          // ��������
#define INIT_LEVELS 5           // ÿ�����ܵĳ�ʼ����
#define VIP_SHELF_ID 10         // ����Ʒר�û��ܱ��
#define LEVEL_CAPACITY 4.0      // ÿ����������
#define BULKY_VOLUME 0.5        // ������������ֵ
#define HEAVY_WEIGHT 1.0        // �ذ���������ֵ

// ȫ�ֱ���
static ShelfLevel wareHouse[MAX_SHELVES][INIT_LEVELS]; // �ֿ����
extern List* packageList;                              // ��������


// ���ߺ���
int validateWeight(double weight);                     // У������
int validateVolume(double volume);                     // У�����
int validatePackageType(int packageType);              // У���������
int isTrackingNumExist(const char* trackingNum);       // ����ݵ����Ƿ����

// ���ܹ�����
void initializeShelves();                              // ��ʼ������
void saveShelves();                                    // �������״̬
void loadPackages();                                   // ���ذ�������
void savePackages();                                   // �����������
void freePackages();                                   // �ͷŰ�������
void showWarehouse(int currentshelf);                 // ��ʾ�ֿ�״̬
void updateShelfAfterPickup(Package* pkg);            // ���»���״̬��ȡ����

// ����������
int placePackageOnShelf(Package* pkg);                // ���ð���������
char* InputPackageInfo(char* trackingNum, char* packageName, PackageType m, double volume, double weight, char* senderAddress, char* receiverPhone);

// �ͻ����Ź���
long long deliverToHomeNumber(long long deliverToHomeTotalNumber); // ��ȡ�ͻ����Ű�������
void deliverToHomeWindow(int page, long long deliverToHomeTotalNumber, char* search); // ��ʾ�ͻ����Ž���
void deliverToHomeMakeTrue(char* trackingNum);       // ȷ���ͻ��������

// ����ȡ������
long long pickUpFromHomeNumber(long long pickUpFromHomeTotalNumber); // ��ȡ����ȡ����������
void pickUpFromHomeWindow(int page, long long pickUpFromHomeTotalNumber, char* search); // ��ʾ����ȡ������
void pickUpFromHomeMakeTrue(char* trackingNum);     // ȷ������ȡ�����

// ֪ͨ���ѹ���
long long sendNotificationNumber(long long sendNotificationTotalNumber, double customHoursDiff); // ��ȡ��Ҫ���ѵİ�������
void sendNotificationWindow(int page, long long sendNotificationTotalNumber, char* search, double customHoursDiff); // ��ʾ֪ͨ���ѽ���

// ��ݵ�ļ�����
long long countPackagesForPointDelivery(long long totalPackages); // ��ȡ��ݵ�ļ���������
void displayPointDeliveryPackages(int page, long long totalPackages, char* search); // ��ʾ��ݵ�ļ�����
void confirmPointDelivery(char* trackingNum); // ȷ�Ͽ�ݵ�ļ����
