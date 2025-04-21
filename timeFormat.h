#pragma once
#include <string.h>
#include <time.h>
#include "common.h"

// ���ܣ���ʽ��ʱ�䣬"yyyy-MM-dd hh:mm:ss"
// ������ʱ��/��
// ���أ���ʽ��ʱ���ַ���
char* formatTime(time_t time);

// ���ܣ����ֻ�ʱ�䣬"yyyyMMddhhmmss"
// ������ʱ��/��
// ���أ����ֻ�ʱ���ַ���
char* digitalTime(time_t time);

// @brief ��ȡ��վʱ��
time_t getStationTime();

// @brief ������վʱ��
void setStationTime(time_t newTime);

void loadTime();

void saveTime();