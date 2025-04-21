#pragma once
#include"common.h"
#include"user.h"
#include"log.h"
#include"package.h"
#include"fore.h"

void  trackPackageFoTrackingNumWindow(int page, long long TotalNumber, char* trackingNum);

long long  trackPackageFoSenderPhoneNumber(long long TotalNumber, char* receiverPhone);

void trackPackageFoSenderPhoneWindow(int page, long long TotalNumber, char* receiverPhone);

long long trackPackageFoReceiverPhoneNumber(long long TotalNumber, char* receiverPhone);

void trackPackageFoReceiverPhoneWindow(int page, long long TotalNumber, char* receiverPhone);

void managerDeleteUser(char* phoneNumber);

void AddressMisdelivery(long long ticketId);

void AddressDamageLoss(long long ticketId);


