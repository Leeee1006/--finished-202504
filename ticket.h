#pragma once
#include "common.h"
#include "user.h"
#include "manager.h"
#include "timeFormat.h"

enum TicketModes
{
	TICKETID_MODE = 1 << 0,
	TICKET_TYPE_MODE = 1 << 1,
};

// 功能：获取工单链表
// 返回：工单链表指针
List* getTickets();

void initTickets();

// 功能：获取总数
// 参数：数量
long long getTotalNumber(long long TicketsTotalNumber);

bool cmpTicket(const void* d1, const void* d2, int mode);

bool compareTicketByType(const void* d1, const void* d2);

bool compareTicketByTime(const void* d1, const void* d2);

void sortTicket(int flag);

// 功能：显示工单
// 参数：工单类型
void showTicketsWindow(int currentpage, long long TicketsTotalNumber, char* searchNum);
// 功能：生成工单编号 (等于创建时间)
long long generateTicketId();