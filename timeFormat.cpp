#include "timeFormat.h"

// 驿站与现实的时差
time_t g_diffTime = 0;

char* formatTime(time_t time)
{
	static const int FMT_TIME_SIZE = ((int)sizeof("yyyy-MM-dd hh:mm"));
	static char timeString[FMT_TIME_SIZE] = "";
	time_t tempTime = time;
	struct tm timeInfo;
	localtime_s(&timeInfo, &tempTime);
	sprintf_s(timeString, FMT_TIME_SIZE, "%.4d-%.2d-%.2d %.2d:%.2d",
		timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday,
		timeInfo.tm_hour, timeInfo.tm_min);
	return timeString;
}

char* digitalTime(time_t time)
{
	static const int DGT_TIME_SIZE = ((int)sizeof("yyyyMMddhhmmss"));
	static char timeString[DGT_TIME_SIZE] = "";
	time_t tempTime = time;
	struct tm timeInfo;
	localtime_s(&timeInfo, &tempTime);
	sprintf_s(timeString, DGT_TIME_SIZE, "%.4d%.2d%.2d%.2d%.2d%.2d",
		timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday,
		timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
	return timeString;
}


time_t getStationTime()
{
	return time(NULL) + g_diffTime;
}

void setStationTime(time_t newTime)
{
	g_diffTime = newTime - time(NULL);
}

void loadTime()
{
	FILE* fp = NULL;
	fopen_s(&fp, TIME_FILE, "rb");
	if (!fp)
	{
		return;
	}
	fread(&g_diffTime, sizeof(g_diffTime), 1, fp);
	fclose(fp);
}

void saveTime()
{
	FILE* fp = NULL;
	if (fopen_s(&fp, TIME_FILE, "wb") || !fp)
	{
		perror("loadTime");
		exit(EXIT_FAILURE);
	}
	fwrite(&g_diffTime, sizeof(g_diffTime), 1, fp);
	fclose(fp);
}
