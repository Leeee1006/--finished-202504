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

// ���ܣ���ȡ��������
// ���أ���������ָ��
List* getTickets();

void initTickets();

// ���ܣ���ȡ����
// ����������
long long getTotalNumber(long long TicketsTotalNumber);

bool cmpTicket(const void* d1, const void* d2, int mode);

bool compareTicketByType(const void* d1, const void* d2);

bool compareTicketByTime(const void* d1, const void* d2);

void sortTicket(int flag);

// ���ܣ���ʾ����
// ��������������
void showTicketsWindow(int currentpage, long long TicketsTotalNumber, char* searchNum);
// ���ܣ����ɹ������ (���ڴ���ʱ��)
long long generateTicketId();