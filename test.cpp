#include "fore.h"

int main()
{
	initLogs();
	initTickets();
	initializeShelves();
	loadUsers();
	loadPackages();
	loadTime();
	deleteExpiredLogs();
	initgraph(1080, 665);
	setbkcolor(WHITE);
	setlinestyle(PS_SOLID, 2);
	cleardevice();
	registerAndLogin();
}