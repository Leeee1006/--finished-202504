#include "ticket.h"
// ��������ָ��
List* g_tickets = NULL;

List* getTickets()
{
	return g_tickets;
}

void initTickets()
{
	g_tickets = list_init(200,100,sizeof(Ticket), TICKET_FILE, sizeof(TICKET_FILE)+1);
}

long long getTotalNumber(long long TicketsTotalNumber) {
	TicketsTotalNumber = g_tickets->elementCount;
	return TicketsTotalNumber;
}

bool cmpTicket(const void* d1, const void* d2, int mode)
{
	const Ticket* tkt1 = (const Ticket*)d1;
	const Ticket* tkt2 = (const Ticket*)d2;
	if (mode & TICKETID_MODE)//�ȽϹ�������
	{
		if (tkt1->ticketId != tkt2->ticketId)
		{
			return false;
		}
	}
	if (mode & TICKET_TYPE_MODE)//�ȽϹ�������
	{
		if (tkt1->ticketType != tkt2->ticketType)
		{
			return false;
		}
	}
	return true;
}

bool compareTicketByType(const void* d1, const void* d2) {
	const Ticket* tkt1 = (const Ticket*)d1;
	const Ticket* tkt2 = (const Ticket*)d2;
	return tkt1->ticketType > tkt2->ticketType;
}
bool compareTicketByTime(const void* d1, const void* d2) {
	const Ticket* tkt1 = (const Ticket*)d1;
	const Ticket* tkt2 = (const Ticket*)d2;
	return tkt1->createdTime > tkt2->createdTime;
}

void sortTicket(int flag) {
	if (g_tickets == NULL || g_tickets->elementCount <= 1) {
		return; // ����Ϊ�ջ�ֻ��һ��Ԫ�أ���������
	}
	if (flag == 1)
	{
		list_sort(g_tickets, compareTicketByType);
	}
	if (flag == 2)
	{
		list_sort(g_tickets, compareTicketByTime);
	}
}

void showTicketsWindow(int currentpage, long long TicketsTotalNumber,char* searchNum)
{
	cleardevice();//����
	buildWindow();
	int start = (currentpage - 1) * 9 + 1;
	int end = start + 8;
	if (end > TicketsTotalNumber) {
		end = TicketsTotalNumber;  // ���һҳ�Ľ���λ��
	}
	int flag = 0;
	text(50, 50, "�������"); text(150, 50, "��������");  text(300, 50, "����ʱ��"); text(500, 50, "�û��绰"); text(750, 50, "��ݵ���"); text(950, 50, "�Ƿ���");
	for (ListNode* node = g_tickets->head->next; node != NULL; node = node->next)
	{
		Ticket* tkt = (Ticket*)node->data;
		flag++;
		if (flag >= start && flag <= end)
		{
			text(50, 50 + (flag - start + 1) * 50, tkt->ticketId);
			switch (tkt->ticketType)
			{
			case Miscollection:
				text(150, 50 + (flag - start + 1) * 50, "��ȡ");
				break;
			case DamageLoss:
				text(150, 50 + (flag - start + 1) * 50, "�𻵶�ʧ");
				break;
			default:
				text(150, 50 + (flag - start + 1) * 50, "��Ϣ����");
				break;
			}
			text(300, 50 + (flag - start + 1) * 50, formatTime(tkt->createdTime));
			text(500, 50 + (flag - start + 1) * 50, tkt->phoneNumber);
			if (tkt->pkgTrackingNum[0] != '\0')
			{
				text(750, 50 + (flag - start + 1) * 50, tkt->pkgTrackingNum);
			}
			if (tkt->isHandled)
			{
				text(950, 50 + (flag - start + 1) * 50, "��");
			}
			else
			{
				text(950, 50 + (flag - start + 1) * 50, "��");
			}
		}
	}
	return;
}

long long generateTicketId()
{
	return getStationTime();
}
