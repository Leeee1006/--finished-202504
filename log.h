#pragma once
#include "common.h"
#include "list.h"
#include "timeFormat.h"
#include"fore.h"

List* getLogs();

void initLogs();

void deleteExpiredLogs();

long long getAllLogsTotalNumber(long long allLogsTotalNumber);

bool isLogExpired(const void* data);

void showAllLogsWindow(int currentpage, long long allLogsTotalNumber, char* searchNum);