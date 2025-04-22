#include"manager.h"

/**
 * @brief 快递单号查找单个界面
 */
void  trackPackageFoTrackingNumWindow(int page, long long TotalNumber, char* trackingNum) {//一次显示九个
	cleardevice();//清屏
	buildWindow();
	long long start = (page - 1) * 9 + 1;
	long long end = start + 8;
	if (end > TotalNumber) {
		end = TotalNumber;  // 最后一页的结束位置
	}
	ListNode* current = packageList->head->next;
	text(10, 50, "快递单号"); text(150, 50, "包裹状态"); text(250, 50, "收件人电话"); text(400, 50, "取件地址"); text(800, 50, "寄件地址");
	long long flag = 0;
	while (current) {
		Package* pkg = (Package*)current->data;
		if (strncmp(pkg->trackingNum, trackingNum, TRACKING_NUM) == 0) {
			flag++;
			if (flag >= start && flag <= end) {
				text(10, 50 + (flag - start + 1) * 50, pkg->trackingNum);//快递单号
				switch (pkg->packageState)
				{
				case Ordered:
					text(150, 50 + (flag - start + 1) * 50, "待寄出");
					break;
				case Shipped:
					text(150, 50 + (flag - start + 1) * 50, "已寄出");
					break;
				case Pending:
					text(150, 50 + (flag - start + 1) * 50, "待取");
					break;
				case Delivered:
					text(150, 50 + (flag - start + 1) * 50, "已签收");
					break;
				case Refused:
					text(150, 50 + (flag - start + 1) * 50, "已拒收");
					break;
				case Canceled:
					text(150, 50 + (flag - start + 1) * 50, "已取消");
					break;
				case Misdelivered:
					text(150, 50 + (flag - start + 1) * 50, "误取");
					break;
				case DamagedLost:
					text(150, 50 + (flag - start + 1) * 50, "损坏/丢失");
					break;
				}
				text(250, 50 + (flag - start + 1) * 50, pkg->receiverPhone);//收件人电话
				text(400, 50 + (flag - start + 1) * 50, pkg->receiverAddress);//取件地址
				text(800, 50 + (flag - start + 1) * 50, pkg->senderAddress);//寄件地址
			}
		}
		current = current->next;
	}
	return;
}
/**
 * @brief 遍历包裹，传出寄件电话查找包裹个数
 */
long long  trackPackageFoSenderPhoneNumber(long long TotalNumber, char* senderPhone) {
	ListNode* current = packageList->head->next;
	while (current) {
		Package* pkg = (Package*)current->data;
		if (strncmp(pkg->senderPhone, senderPhone, PHONE) == 0) {
			TotalNumber++;
		}
		current = current->next;
	}
	return TotalNumber;
}
/**
 * @brief 寄件电话查找单个界面
 */
void trackPackageFoSenderPhoneWindow(int page, long long TotalNumber, char* senderPhone) {//一次显示九个
	cleardevice();//清屏
	buildWindow();
	long long start = (page - 1) * 9 + 1;
	long long end = start + 8;
	if (end > TotalNumber) {
		end = TotalNumber;  // 最后一页的结束位置
	}
	ListNode* current = packageList->head->next;
	text(10, 50, "快递单号"); text(150, 50, "包裹状态"); text(250, 50, "收件人电话"); text(400, 50, "取件地址"); text(900, 50, "寄件地址");
	long long flag = 0;
	while (current) {
		Package* pkg = (Package*)current->data;
		if (strncmp(pkg->senderPhone, senderPhone, PHONE) == 0) {
			flag++;
			if (flag >= start && flag <= end) {
				text(10, 50 + (flag - start + 1) * 50, pkg->trackingNum);//快递单号
				switch (pkg->packageState)
				{
				case Ordered:
					text(150, 50 + (flag - start + 1) * 50, "待寄出");
					break;
				case Shipped:
					text(150, 50 + (flag - start + 1) * 50, "已寄出");
					break;
				case Pending:
					text(150, 50 + (flag - start + 1) * 50, "待取");
					break;
				case Delivered:
					text(150, 50 + (flag - start + 1) * 50, "已签收");
					break;
				case Refused:
					text(150, 50 + (flag - start + 1) * 50, "已拒收");
					break;
				case Canceled:
					text(150, 50 + (flag - start + 1) * 50, "已取消");
					break;
				case Misdelivered:
					text(150, 50 + (flag - start + 1) * 50, "误取");
					break;
				case DamagedLost:
					text(150, 50 + (flag - start + 1) * 50, "损坏/丢失");
					break;
				}

				text(250, 50 + (flag - start + 1) * 50, pkg->receiverPhone);//收件人电话
				text(400, 50 + (flag - start + 1) * 50, pkg->receiverAddress);//取件地址
				text(900, 50 + (flag - start + 1) * 50, pkg->senderAddress);//寄件地址
			}
		}
		current = current->next;
	}
	return;
}
/**
 * @brief 遍历包裹，传出收件电话查找包裹个数
 */
long long trackPackageFoReceiverPhoneNumber(long long TotalNumber, char* receiverPhone) {
	ListNode* current = packageList->head->next;
	while (current) {
		Package* pkg = (Package*)current->data;
		if (strncmp(pkg->receiverPhone, receiverPhone, PHONE) == 0) {
			TotalNumber++;
		}
		current = current->next;
	}
	return TotalNumber;
}
/**
 * @brief 收件电话查找单个界面
 */
 /**
  * @brief 收件电话查找单个界面
  */
void trackPackageFoReceiverPhoneWindow(int page, long long TotalNumber, char* receiverPhone) {//一次显示九个
	cleardevice();//清屏
	buildWindow();
	long long start = (page - 1) * 9 + 1;
	long long end = start + 8;
	if (end > TotalNumber) {
		end = TotalNumber;  // 最后一页的结束位置
	}
	ListNode* current = packageList->head->next;
	text(10, 50, "快递单号"); text(150, 50, "包裹状态"); text(250, 50, "收件人电话"); text(400, 50, "取件地址"); text(650, 50, "寄件地址");
	long long flag = 0;
	while (current) {
		Package* pkg = (Package*)current->data;
		if (strncmp(pkg->receiverPhone, receiverPhone, PHONE) == 0) {
			flag++;
			if (flag >= start && flag <= end) {
				text(10, 50 + (flag - start + 1) * 50, pkg->trackingNum);//快递单号
				switch (pkg->packageState)
				{
				case Ordered:
					text(150, 50 + (flag - start + 1) * 50, "待寄出");
					break;
				case Shipped:
					text(150, 50 + (flag - start + 1) * 50, "已寄出");
					break;
				case Pending:
					text(150, 50 + (flag - start + 1) * 50, "待取");
					break;
				case Delivered:
					text(150, 50 + (flag - start + 1) * 50, "已签收");
					break;
				case Refused:
					text(150, 50 + (flag - start + 1) * 50, "已拒收");
					break;
				case Canceled:
					text(150, 50 + (flag - start + 1) * 50, "已取消");
					break;
				case Misdelivered:
					text(150, 50 + (flag - start + 1) * 50, "误取");
					break;
				case DamagedLost:
					text(150, 50 + (flag - start + 1) * 50, "损坏/丢失");
					break;
				}
				text(250, 50 + (flag - start + 1) * 50, pkg->receiverPhone);//收件人电话
				text(400, 50 + (flag - start + 1) * 50, pkg->receiverAddress);//取件地址
				text(650, 50 + (flag - start + 1) * 50, pkg->senderAddress);//寄件地址
			}
		}
		current = current->next;
	}
	return;
}

void managerDeleteUser(char* phoneNumber)
{
	User ref{};
	strncpy(ref.phoneNumber, phoneNumber, PHONE);
	User* foundUser = (User*)list_find(userList, &ref, PHONE_MODE, cmpUser);
	//用户不存在
	if (foundUser == NULL)
	{
		messbox("用户不存在");
		return;
	}
	//用户存在
	else
	{
		Package ref1{};
		strncpy(ref1.senderPhone, phoneNumber, PHONE - 1);
		Package* foundPackage1 = (Package*)list_find(packageList, &ref1, SENDER_PHONE_MODE, cmpPackage);
		if (foundPackage1 != NULL)
		{
			messbox("该用户有未寄出的包裹,无法删除");
			return;
		}
		Package ref2{};
		strncpy(ref2.receiverPhone, phoneNumber, PHONE - 1);
		Package* foundPackage2 = (Package*)list_find(packageList, &ref2, RECEIVER_PHONE_MODE, cmpPackage);
		if (foundPackage2 != NULL)
		{
			messbox("该用户有未领取的包裹，无法删除");
			return;
		}
		list_delete(userList, &ref, PHONE_MODE, cmpUser);
		messbox("用户删除成功");
	}
}

void AddressMisdelivery(long long ticketId)
{
	Ticket refTicket = {};
	refTicket.ticketId = ticketId;
	refTicket.ticketType = Miscollection;
	Ticket* foundTicket = (Ticket*)list_find(g_tickets, &refTicket, TICKETID_MODE | TICKET_TYPE_MODE, cmpTicket);
	if (foundTicket == NULL)
	{
		messbox("工单不存在!");
		return;
	}
	foundTicket->isHandled = true;
	list_delete(g_tickets, &refTicket, TICKETID_MODE, cmpTicket);//处理成功，删除该节点
	list_save(g_tickets);
	// 添加日志
	Log tmpLog = {};
	sprintf_s(tmpLog.description, DESCR, "管理员处理工单 编号%d", foundTicket->ticketId);
	tmpLog.createdTime = getStationTime();
	list_add(g_logs, &tmpLog);
	list_save(g_logs);
	messbox("处理成功");

	Package refPackage{};
	strncpy(refPackage.trackingNum, foundTicket->pkgTrackingNum, TRACKING_NUM);
	Package* foundPackage = (Package*)list_find(packageList, &refPackage, TRACKINGNUM_MODE, cmpPackage);
	if (foundPackage != NULL)
	{
		foundPackage->packageState = Misdelivered;
	}
}

void AddressDamageLoss(long long ticketId)
{
	Ticket refTicket = {};
	refTicket.ticketId = ticketId;
	refTicket.ticketType = DamageLoss;
	Ticket* foundTicket = (Ticket*)list_find(g_tickets, &refTicket, TICKETID_MODE | TICKET_TYPE_MODE, cmpTicket);
	if (foundTicket == NULL)
	{
		messbox("工单不存在!");
		return;
	}
	foundTicket->isHandled = true;
	list_delete(g_tickets, &refTicket, TICKETID_MODE, cmpTicket);//处理成功，删除该节点
	list_save(g_tickets);
	// 添加日志
	Log tmpLog = {};
	sprintf_s(tmpLog.description, DESCR, "管理员处理工单 编号%d", foundTicket->ticketId);
	tmpLog.createdTime = getStationTime();
	list_add(g_logs, &tmpLog);
	list_save(g_logs);
	messbox("处理成功");

	Package refPackage{};
	strncpy(refPackage.trackingNum, foundTicket->pkgTrackingNum, TRACKING_NUM);
	Package* foundPackage = (Package*)list_find(packageList, &refPackage, TRACKINGNUM_MODE, cmpPackage);
	if (foundPackage != NULL)
	{
		foundPackage->packageState = DamagedLost;
	}
}