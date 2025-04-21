#include "log.h"

//日志链表指针
List* g_logs = NULL;

List* getLogs()
{
	return g_logs;
}

void initLogs()
{
	g_logs = list_init(10000,5000,sizeof(Log), LOG_FILE, sizeof(LOG_FILE)+1);
}

long long getAllLogsTotalNumber(long long allLogsTotalNumber)
{
	return g_logs->elementCount;
}

bool isLogExpired(const void*data)
{
	time_t currentTime = getStationTime();
	time_t twoWeekAgoTime = currentTime - 14 * 24 * 60 * 60;
	const Log* log = (const Log*)data;
	return log->createdTime < twoWeekAgoTime;
}

void deleteExpiredLogs() 
{
	list_delete_ex(getLogs(), isLogExpired);
}


// 功能：显示日志信息
void showAllLogsWindow(int currentpage, long long allLogsTotalNumber,char* searchNum)
{
	cleardevice();//清屏
	buildWindow();
	long long start = (currentpage - 1) * 9 + 1;
	long long end = start + 8;
	if (end > allLogsTotalNumber) {
		end = allLogsTotalNumber;  // 最后一页的结束位置
	}
	time_t currentTime = getStationTime();
	time_t weekAgoTime = currentTime-7*24*60*60;
	text(100, 50, "日志描述"); text(600, 50, "创建时间");
	long long flag = 0;
	for (ListNode* node = g_logs->head->next; node != NULL; node = node->next)
	{
		Log* log = (Log*)node->data;
		if (log->createdTime >= weekAgoTime) 
		{
			flag++;
			if (flag >= start && flag <= end) 
			{
				text(100, 50 + (flag - start + 1) * 50, log->description);
				text(600, 50 + (flag - start + 1) * 50, formatTime(log->createdTime));
			}
		}
		else {
			return;
		}
	}
}