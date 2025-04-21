#include "user.h"

// �û�����ָ��
extern List* userList;
// ��ǰ�û�ָ��
User* g_currentUser = NULL;

/**
 * @brief ���������������ǳƲ����û�����
 */
long long  trackPackageFoNameNumber(long long TotalNumber, char* name) {
	ListNode* current = userList->head->next;
	while (current) {
		User* use = (User*)current->data;
		if (strncmp(use->userName, name, 12)==0) {
			TotalNumber++;
		}
		current = current->next;
	}
	return TotalNumber;
}
/**
 * @brief �ǳƲ��ҵ�������
 */
void trackPackageFoNameWindow(int page, long long TotalNumber, char* name) {//һ����ʾ�Ÿ�
	cleardevice();//����
	buildWindow();
	long long start = (page - 1) * 9 + 1;
	long long end = start + 8;
	if (end > TotalNumber) {
		end = TotalNumber;  // ���һҳ�Ľ���λ��
	}
	ListNode* current = userList->head->next;
	text(50, 50, "�ǳ�"); text(200, 50, "�ֻ���"); text(400, 50, "����ֵ"); text(600, 50, "�Ż�ȯ��"); text(800, 50, "�ȼ�");
	long long flag = 0;
	while (current) {
		User* use = (User*)current->data;
		if (strncmp(use->userName, name, 12)==0) {
			flag++;
			if (flag >= start && flag <= end) {
				text(50, 50 + (flag - start + 1) * 50, use->userName);//�ǳ�
				text(200, 50 + (flag - start + 1) * 50, use->phoneNumber);//�ֻ���
				text(400, 50 + (flag - start + 1) * 50, (int)use->experience);//����ֵ
				text(600, 50 + (flag - start + 1) * 50, use->couponCount);//�Ż�ȯ��
				if (use->userType == 0)
				{
					text(800, 50 + (flag - start + 1) * 50, "��ͨ");//�ȼ�
				}
				else {
					text(800, 50 + (flag - start + 1) * 50,"VIP");//�ȼ�
				}
			}
		}
		current = current->next;
	}
	return;
}
/**
 * @brief �˺Ų��ҵ�������
 */
void trackPackageFoPhoneNumberWindow(int page, long long TotalNumber, char* phoneNumber) {//һ����ʾ�Ÿ�
	cleardevice();//����
	buildWindow();
	long long start = (page - 1) * 9 + 1;
	long long end = start + 8;
	if (end > TotalNumber) {
		end = TotalNumber;  // ���һҳ�Ľ���λ��
	}
	ListNode* current = userList->head->next;
	text(50, 50, "�ǳ�"); text(200, 50, "�ֻ���"); text(400, 50, "����ֵ"); text(600, 50, "�Ż�ȯ��"); text(800, 50, "�ȼ�");
	long long flag = 0;
	while (current) {
		User* use = (User*)current->data;
		if (strncmp(use->phoneNumber, phoneNumber, PHONE)==0) {
			flag++;
			if (flag >= start && flag <= end) {
				text(50, 50 + (flag - start + 1) * 50, use->userName);//�ǳ�
				text(200, 50 + (flag - start + 1) * 50, use->phoneNumber);//�ֻ���
				text(400, 50 + (flag - start + 1) * 50, (int)use->experience);//����ֵ
				text(600, 50 + (flag - start + 1) * 50, use->couponCount);//�Ż�ȯ��
				if (use->userType == 0)
				{
					text(800, 50 + (flag - start + 1) * 50, "��ͨ");//�ȼ�
				}
				else {
					text(800, 50 + (flag - start + 1) * 50, "VIP");//�ȼ�
				}
			}
		}
		current = current->next;
	}
	return;
}
List* getUsers()
{
	return userList;
}
bool cmpUser(const void* d1, const void* d2,int mode)
{
	const User* use1 = (const User*)d1;
	const User* use2 = (const User*)d2;
	if (mode & PHONE_MODE)
	{
		if (strncmp(use1->phoneNumber, use2->phoneNumber, PHONE) != 0)
		{
			return false;
		}
	}
	if (mode & NAME_MODE)
	{
		if (strncmp(use1->userName, use2->userName, 12) != 0)
		{
			return false;
		}
	}
	return true;
}

char* generateIdentityCode(const char* phone)
{
	static char identityCode[ID_CODE] = "";
	identityCode[0] = '0';
	identityCode[1] = 'A';
	identityCode[2] = 'a';
	for (int i = 1; i < 10; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			identityCode[3 * i + j] = (phone[i] + 131 * (identityCode[3 * (i - 1) + j])) % 94 + 33;
		}
	}
	identityCode[30] = '\0';
	return identityCode;
}

void refusePackage(char* trackingNum)
{
	//���Ұ���
	Package refPackage{};
	strncpy(refPackage.trackingNum, trackingNum, TRACKING_NUM);
	Package* foundPackage = (Package*)list_find(packageList, &refPackage, TRACKINGNUM_MODE, cmpPackage);
	//����δ�ҵ�
	if (foundPackage == NULL)
	{
		messbox("���������ڣ����������룡");
		return;
	}
	foundPackage->packageState = Refused;
	//��¼����ʱ��
	foundPackage->time.refused = getStationTime();
	//�������
	list_save(getPackages());
	//�����־
	Log tempLog = {};
	sprintf_s(tempLog.description, DESCR, "�û�%s�����˰���%s", g_currentUser->phoneNumber, foundPackage->trackingNum);
	tempLog.createdTime = getStationTime();
	list_add(getLogs(), &tempLog);
	//������־
	list_save(getLogs());
	messbox("���ճɹ���");
	// ����
}

void deliverToHomePackage(char* trackingNum,char* receiverAddress) {
	Package package = {};
	strncpy(package.trackingNum, trackingNum, TRACKING_NUM);
	// ���Ҵ�ȡ������
	Package refPackage{};
	strncpy(refPackage.trackingNum, trackingNum, TRACKING_NUM);
	strncpy(refPackage.receiverPhone, g_currentUser->phoneNumber, PHONE - 1);
	refPackage.packageState = Pending;
	Package* foundPackage = (Package*)list_find(packageList, &refPackage, TRACKINGNUM_MODE| RECEIVER_PHONE_MODE| PACKAGESTATE_MODE, cmpPackage);
	if (foundPackage == NULL)
	{
		messbox("���������ڣ����������룡");
		return;
	}
	if (foundPackage->packageState != Pending) {//���Ǵ�ȡ
		messbox("����״̬��������");
		return;
	}
	// ����״̬
	foundPackage->isHomeDelivered = true;
	strncpy(foundPackage->receiverAddress, receiverAddress, ADDRESS);
	//�������
	list_save(getPackages());
	// �����־
	Log tempLog = {};
	sprintf_s(tempLog.description, DESCR, "�û�%sѡ���ͼ���¥�˰���%s", g_currentUser->phoneNumber, foundPackage->trackingNum);
	tempLog.createdTime = getStationTime();
	list_add(getLogs(), &tempLog);
	// ������־
	list_save(getLogs());
	messbox("�����ͼ���¥�ɹ���");
}

void cancelPackage(char* trackingNum)
{
	Package package = {};
	strncpy(package.trackingNum, trackingNum, TRACKING_NUM);
	// �������µ�����
	Package refPackage{};
	strncpy(refPackage.trackingNum, trackingNum, TRACKING_NUM);
	Package* foundPackage = (Package*)list_find(packageList, &refPackage, TRACKINGNUM_MODE, cmpPackage);
	// ����δ�ҵ�
	if (foundPackage == NULL)
	{
		messbox("���������ڣ����������룡");
		return;
	}
	// ȷ��ȡ��
	foundPackage->packageState = Canceled;
	// ��¼ȡ��ʱ��
	foundPackage->time.canceled = getStationTime();
	//�������
	list_save(getPackages());
	// �����־
	Log tempLog = {};
	sprintf_s(tempLog.description, DESCR, "�û�%sȡ���˰���%s", g_currentUser->phoneNumber, foundPackage->trackingNum);
	tempLog.createdTime = getStationTime();
	list_add(getLogs(), &tempLog);
	// ������־
	list_save(getLogs());
	messbox("ȡ���ɹ���");
}

void pickupPackage(char* trackingNum)
{
	Package package = {};
	strncpy(package.trackingNum, trackingNum, TRACKING_NUM);
	//���Ҵ�ȡ������
	Package refPackage{};
	strncpy(refPackage.trackingNum, trackingNum, TRACKING_NUM);
	strncpy(refPackage.receiverPhone, g_currentUser->phoneNumber, PHONE - 1);
	Package* foundPackage = (Package*)list_find(packageList, &refPackage, TRACKINGNUM_MODE | RECEIVER_PHONE_MODE, cmpPackage);
	//����δ�ҵ�
	if (foundPackage == NULL)
	{
		messbox("���������ڣ����������룡");
		return;
	}
	//���İ���״̬Ϊ��ǩ��
	foundPackage->packageState = Delivered;
	//��¼ǩ��ʱ��
	foundPackage->time.delivered = getStationTime();
	//���»���״̬
	updateShelfAfterPickup(foundPackage);
	//�������
	list_save(getPackages());
	//�����־
	Log tempLog = {};
	sprintf_s(tempLog.description, DESCR, "�û�%sǩ���˰���%s", g_currentUser->phoneNumber, foundPackage->trackingNum);
	tempLog.createdTime = getStationTime();
	list_add(getLogs(), &tempLog);
	//������־
	list_save(getLogs());
	messbox("ȡ���ɹ���");
}

void sendPackageInfo(char* packageName, char* receiverAddress, char* receiverPhone, char* dormAddress, float weight, float volume, int shippingMethodOption,
	int packageTypeOption, int homeSentOption, int couponOption)
{
	Package package = {};
	//��д��������
	strncpy(package.packageName, packageName, NAME);
	//�Զ����ļ���ַ
	strcpy_s(package.senderAddress, ADDRESS, "�����ѧ��");
	//��дȡ����ַ
	strncpy(package.receiverAddress, receiverAddress, ADDRESS);
	// �Զ����ļ����ֻ���
	strcpy_s(package.senderPhone, PHONE, g_currentUser->phoneNumber);
	// ��дȡ�����ֻ���
	strncpy(package.receiverPhone, receiverPhone, PHONE-1);
	//��д����
	package.weight = weight;
	//��д���
	package.volume = volume;
	//ѡ��ļ���ʽ
	switch (shippingMethodOption)
	{
		//��ͨ
	case 0:
		package.shippingMethod = ShippingStandard;
		break;
		//���
	case 1:
		package.shippingMethod = Express;
		break;
		//����
	case 2:
		package.shippingMethod = Economic;
		break;
		//�������
	default:
		break;
	}
	//ѡ���������
	switch (packageTypeOption)
	{
		//��ͨ
	case 0:
		package.packageType = PackageStandard;
		break;
		//����
	case 1:
		package.packageType = Fragile;
		break;
		//����
	case 2:
		package.packageType = Parcel;
		break;
		//�������
	default:
		break;
	}
	//�Ƿ�����ȡ��
	switch (homeSentOption)
	{
		//��ݵ��Լ�
	case 1:
		package.isHomeSent = false;
		break;
		//����ȡ��
	case 2:
		package.isHomeSent = true;
		strncpy(package.dormAddress, dormAddress, ADDRESS);
		break;
		//�������
	default:
		break;
	}
	if (couponOption == 1) //ʹ���Ż�ȯ
	{
		g_currentUser->couponCount--;//�Զ���һ
	}
	// �����˷�
	package.shippingFee = calculateShippingFee(&package, g_currentUser);
	//�µ�
		//ʹ���Ż�ȯ
	//�û�����ֵ����
	g_currentUser->experience += ((int)log(package.shippingFee) + 1) * EXP_COEF;
	//���ɿ�ݵ���
	strcpy_s(package.trackingNum, TRACKING_NUM, generateTrackingNumber());
	//��Ӵ��ĳ�����
	package.pickupCode[0] = '\0';
	package.packageState = Ordered;
	package.time = { getStationTime(),-1,-1,-1,-1,-1};
	list_add(getPackages(), &package);
	//�������
	list_save(getPackages());
	//�����־
	Log tempLog = {};
	sprintf_s(tempLog.description, DESCR, "�û�%s�µ��˰���%s", g_currentUser->phoneNumber, package.trackingNum);
	tempLog.createdTime = getStationTime();
	list_add(getLogs(), &tempLog);
	// ������־
	list_save(getLogs());
	//��վӯ��10%(δ���)
	wchar_t wtext[256];
	char arr[20] = { '\0' };
	sprintf(arr, "%.2f", package.shippingFee);
	int len = MultiByteToWideChar(CP_ACP, 0, arr, -1, wtext, 256);  // GBK ����
	if (len > 0)
	{
		HWND hnd = GetHWnd();
		MessageBoxW(hnd, wtext, L"�ļ����Ϊ��", MB_OK);
	}
}
void userupgrade()
{
	if (g_currentUser->userType == Regular)
	{
		g_currentUser->userType = VIP;
		g_currentUser->discount = 80;
		list_save(userList);
		messbox("��ֵ�ɹ���");
	}
}

void sendticket(int ticketTypeOption, char* pkgTrackingNum)
{
	Ticket tempTicket = {};
	strncpy(tempTicket.pkgTrackingNum, pkgTrackingNum, TRACKING_NUM);
	switch (ticketTypeOption)
	{
	case 1:
		tempTicket.ticketType = Miscollection;
		break;
	case 2:
		tempTicket.ticketType = DamageLoss;
		break;
	default:
		return;
	}
	Package refPackage{};
	strncpy(refPackage.trackingNum, pkgTrackingNum, TRACKING_NUM);
	strncpy(refPackage.receiverPhone, g_currentUser->phoneNumber, PHONE - 1);
	Package* foundPackage = (Package*)list_find(packageList, &refPackage, TRACKINGNUM_MODE | RECEIVER_PHONE_MODE, cmpPackage);
	if (foundPackage == NULL)
	{//�Ҳ���
		messbox("�ÿ�ݵ��ŵ�\"��ǩ��\"���������ڣ�\n");
		return;
	}
	// ����
	tempTicket.ticketId = generateTicketId();
	// ��ӹ���
	tempTicket.createdTime = getStationTime();
	strncpy(tempTicket.phoneNumber, g_currentUser->phoneNumber, PHONE-1);
	list_add(getTickets(), &tempTicket);
	// ���湤��
	list_save(getTickets());
	// �����־
	Log tempLog = {};
	sprintf_s(tempLog.description, DESCR, "�û�%s�����˹���%.20lld", g_currentUser->phoneNumber, generateTicketId());
	tempLog.createdTime = getStationTime();

	// ������־
	list_add(getLogs(), &tempLog);
	list_save(getLogs());
	messbox("�������ͳɹ���");
}
void exchangecoupons()
{
	//�һ��Ż�ȯ
	if (g_currentUser->experience < EXP_OF_PER_COUPON)
	{
		messbox("����ֵ���㣡");
	}
	else
	{
		g_currentUser->couponCount++;
		g_currentUser->experience -= EXP_OF_PER_COUPON;
		messbox("�һ��ɹ���");
	}
}