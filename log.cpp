#include "log.h"

//��־����ָ��
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


// ���ܣ���ʾ��־��Ϣ
void showAllLogsWindow(int currentpage, long long allLogsTotalNumber,char* searchNum)
{
	cleardevice();//����
	buildWindow();
	long long start = (currentpage - 1) * 9 + 1;
	long long end = start + 8;
	if (end > allLogsTotalNumber) {
		end = allLogsTotalNumber;  // ���һҳ�Ľ���λ��
	}
	time_t currentTime = getStationTime();
	time_t weekAgoTime = currentTime-7*24*60*60;
	text(100, 50, "��־����"); text(600, 50, "����ʱ��");
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