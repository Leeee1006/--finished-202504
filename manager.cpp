#include"manager.h"

/**
 * @brief ��ݵ��Ų��ҵ�������
 */
void  trackPackageFoTrackingNumWindow(int page, long long TotalNumber, char* trackingNum) {//һ����ʾ�Ÿ�
	cleardevice();//����
	buildWindow();
	long long start = (page - 1) * 9 + 1;
	long long end = start + 8;
	if (end > TotalNumber) {
		end = TotalNumber;  // ���һҳ�Ľ���λ��
	}
	ListNode* current = packageList->head->next;
	text(10, 50, "��ݵ���"); text(150, 50, "����״̬"); text(250, 50, "�ռ��˵绰"); text(400, 50, "ȡ����ַ"); text(800, 50, "�ļ���ַ");
	long long flag = 0;
	while (current) {
		Package* pkg = (Package*)current->data;
		if (strncmp(pkg->trackingNum, trackingNum, TRACKING_NUM) == 0) {
			flag++;
			if (flag >= start && flag <= end) {
				text(10, 50 + (flag - start + 1) * 50, pkg->trackingNum);//��ݵ���
				switch (pkg->packageState)
				{
				case Ordered:
					text(150, 50 + (flag - start + 1) * 50, "���ĳ�");
					break;
				case Shipped:
					text(150, 50 + (flag - start + 1) * 50, "�Ѽĳ�");
					break;
				case Pending:
					text(150, 50 + (flag - start + 1) * 50, "��ȡ");
					break;
				case Delivered:
					text(150, 50 + (flag - start + 1) * 50, "��ǩ��");
					break;
				case Refused:
					text(150, 50 + (flag - start + 1) * 50, "�Ѿ���");
					break;
				case Canceled:
					text(150, 50 + (flag - start + 1) * 50, "��ȡ��");
					break;
				case Misdelivered:
					text(150, 50 + (flag - start + 1) * 50, "��ȡ");
					break;
				case DamagedLost:
					text(150, 50 + (flag - start + 1) * 50, "��/��ʧ");
					break;
				}
				text(250, 50 + (flag - start + 1) * 50, pkg->receiverPhone);//�ռ��˵绰
				text(400, 50 + (flag - start + 1) * 50, pkg->receiverAddress);//ȡ����ַ
				text(800, 50 + (flag - start + 1) * 50, pkg->senderAddress);//�ļ���ַ
			}
		}
		current = current->next;
	}
	return;
}
/**
 * @brief ���������������ļ��绰���Ұ�������
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
 * @brief �ļ��绰���ҵ�������
 */
void trackPackageFoSenderPhoneWindow(int page, long long TotalNumber, char* senderPhone) {//һ����ʾ�Ÿ�
	cleardevice();//����
	buildWindow();
	long long start = (page - 1) * 9 + 1;
	long long end = start + 8;
	if (end > TotalNumber) {
		end = TotalNumber;  // ���һҳ�Ľ���λ��
	}
	ListNode* current = packageList->head->next;
	text(10, 50, "��ݵ���"); text(150, 50, "����״̬"); text(250, 50, "�ռ��˵绰"); text(400, 50, "ȡ����ַ"); text(900, 50, "�ļ���ַ");
	long long flag = 0;
	while (current) {
		Package* pkg = (Package*)current->data;
		if (strncmp(pkg->senderPhone, senderPhone, PHONE) == 0) {
			flag++;
			if (flag >= start && flag <= end) {
				text(10, 50 + (flag - start + 1) * 50, pkg->trackingNum);//��ݵ���
				switch (pkg->packageState)
				{
				case Ordered:
					text(150, 50 + (flag - start + 1) * 50, "���ĳ�");
					break;
				case Shipped:
					text(150, 50 + (flag - start + 1) * 50, "�Ѽĳ�");
					break;
				case Pending:
					text(150, 50 + (flag - start + 1) * 50, "��ȡ");
					break;
				case Delivered:
					text(150, 50 + (flag - start + 1) * 50, "��ǩ��");
					break;
				case Refused:
					text(150, 50 + (flag - start + 1) * 50, "�Ѿ���");
					break;
				case Canceled:
					text(150, 50 + (flag - start + 1) * 50, "��ȡ��");
					break;
				case Misdelivered:
					text(150, 50 + (flag - start + 1) * 50, "��ȡ");
					break;
				case DamagedLost:
					text(150, 50 + (flag - start + 1) * 50, "��/��ʧ");
					break;
				}

				text(250, 50 + (flag - start + 1) * 50, pkg->receiverPhone);//�ռ��˵绰
				text(400, 50 + (flag - start + 1) * 50, pkg->receiverAddress);//ȡ����ַ
				text(900, 50 + (flag - start + 1) * 50, pkg->senderAddress);//�ļ���ַ
			}
		}
		current = current->next;
	}
	return;
}
/**
 * @brief ���������������ռ��绰���Ұ�������
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
 * @brief �ռ��绰���ҵ�������
 */
 /**
  * @brief �ռ��绰���ҵ�������
  */
void trackPackageFoReceiverPhoneWindow(int page, long long TotalNumber, char* receiverPhone) {//һ����ʾ�Ÿ�
	cleardevice();//����
	buildWindow();
	long long start = (page - 1) * 9 + 1;
	long long end = start + 8;
	if (end > TotalNumber) {
		end = TotalNumber;  // ���һҳ�Ľ���λ��
	}
	ListNode* current = packageList->head->next;
	text(10, 50, "��ݵ���"); text(150, 50, "����״̬"); text(250, 50, "�ռ��˵绰"); text(400, 50, "ȡ����ַ"); text(650, 50, "�ļ���ַ");
	long long flag = 0;
	while (current) {
		Package* pkg = (Package*)current->data;
		if (strncmp(pkg->receiverPhone, receiverPhone, PHONE) == 0) {
			flag++;
			if (flag >= start && flag <= end) {
				text(10, 50 + (flag - start + 1) * 50, pkg->trackingNum);//��ݵ���
				switch (pkg->packageState)
				{
				case Ordered:
					text(150, 50 + (flag - start + 1) * 50, "���ĳ�");
					break;
				case Shipped:
					text(150, 50 + (flag - start + 1) * 50, "�Ѽĳ�");
					break;
				case Pending:
					text(150, 50 + (flag - start + 1) * 50, "��ȡ");
					break;
				case Delivered:
					text(150, 50 + (flag - start + 1) * 50, "��ǩ��");
					break;
				case Refused:
					text(150, 50 + (flag - start + 1) * 50, "�Ѿ���");
					break;
				case Canceled:
					text(150, 50 + (flag - start + 1) * 50, "��ȡ��");
					break;
				case Misdelivered:
					text(150, 50 + (flag - start + 1) * 50, "��ȡ");
					break;
				case DamagedLost:
					text(150, 50 + (flag - start + 1) * 50, "��/��ʧ");
					break;
				}
				text(250, 50 + (flag - start + 1) * 50, pkg->receiverPhone);//�ռ��˵绰
				text(400, 50 + (flag - start + 1) * 50, pkg->receiverAddress);//ȡ����ַ
				text(650, 50 + (flag - start + 1) * 50, pkg->senderAddress);//�ļ���ַ
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
	//�û�������
	if (foundUser == NULL)
	{
		messbox("�û�������");
		return;
	}
	//�û�����
	else
	{
		Package ref1{};
		strncpy(ref1.senderPhone, phoneNumber, PHONE - 1);
		Package* foundPackage1 = (Package*)list_find(packageList, &ref1, SENDER_PHONE_MODE, cmpPackage);
		if (foundPackage1 != NULL)
		{
			messbox("���û���δ�ĳ��İ���,�޷�ɾ��");
			return;
		}
		Package ref2{};
		strncpy(ref2.receiverPhone, phoneNumber, PHONE - 1);
		Package* foundPackage2 = (Package*)list_find(packageList, &ref2, RECEIVER_PHONE_MODE, cmpPackage);
		if (foundPackage2 != NULL)
		{
			messbox("���û���δ��ȡ�İ������޷�ɾ��");
			return;
		}
		list_delete(userList, &ref, PHONE_MODE, cmpUser);
		messbox("�û�ɾ���ɹ�");
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
		messbox("����������!");
		return;
	}
	foundTicket->isHandled = true;
	list_delete(g_tickets, &refTicket, TICKETID_MODE, cmpTicket);//����ɹ���ɾ���ýڵ�
	list_save(g_tickets);
	// �����־
	Log tmpLog = {};
	sprintf_s(tmpLog.description, DESCR, "����Ա������ ���%d", foundTicket->ticketId);
	tmpLog.createdTime = getStationTime();
	list_add(g_logs, &tmpLog);
	list_save(g_logs);
	messbox("����ɹ�");

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
		messbox("����������!");
		return;
	}
	foundTicket->isHandled = true;
	list_delete(g_tickets, &refTicket, TICKETID_MODE, cmpTicket);//����ɹ���ɾ���ýڵ�
	list_save(g_tickets);
	// �����־
	Log tmpLog = {};
	sprintf_s(tmpLog.description, DESCR, "����Ա������ ���%d", foundTicket->ticketId);
	tmpLog.createdTime = getStationTime();
	list_add(g_logs, &tmpLog);
	list_save(g_logs);
	messbox("����ɹ�");

	Package refPackage{};
	strncpy(refPackage.trackingNum, foundTicket->pkgTrackingNum, TRACKING_NUM);
	Package* foundPackage = (Package*)list_find(packageList, &refPackage, TRACKINGNUM_MODE, cmpPackage);
	if (foundPackage != NULL)
	{
		foundPackage->packageState = DamagedLost;
	}
}