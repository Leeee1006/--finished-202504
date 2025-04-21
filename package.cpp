#include "package.h"

// ��������ָ��
extern List* packageList;

List* getPackages()
{
	return packageList;
}

static int timechoice = 0; // ȫ�ֱ��������ڴ洢ѡ�������ʽ
bool comparePackageByTime(const void* d1, const void* d2) {
	const Package* pkg1 = (const Package*)d1;
	const Package* pkg2 = (const Package*)d2;
	switch (timechoice) {
	case 0:
		return pkg1->time.ordered > pkg2->time.ordered; // ���µ�ʱ�併������
	case 1:
		return pkg1->time.pending > pkg2->time.pending; // �����ĳ�ʱ�併������
	case 2:
		return pkg1->time.shipped > pkg2->time.shipped; // ������ʱ�併������
	case 3:
		return pkg1->time.delivered > pkg2->time.delivered; // ��ǩ��ʱ�併������
	case 4:
		return pkg1->time.refused > pkg2->time.refused; // ������ʱ�併������
	case 5:
		return pkg1->time.canceled > pkg2->time.canceled; // ��ȡ��ʱ�併������	
	}
	return false;
}

void sortPackagesByTime(int curchoice) {
	if (packageList == NULL || packageList->elementCount <= 1) {
		return; // ����Ϊ�ջ�ֻ��һ��Ԫ�أ���������
	}
	timechoice = curchoice; // ����ȫ�ֱ���Ϊ��ǰѡ�������ʽ
	list_sort(packageList, comparePackageByTime);
}
bool cmpPackage(const void* d1, const void* d2, int mode)
{
	const Package* pkg1 = (const Package*)d1;
	const Package* pkg2 = (const Package*)d2;
	if (mode & TRACKINGNUM_MODE)//�ȽϿ�ݵ���
	{
		if (strncmp(pkg1->trackingNum, pkg2->trackingNum, TRACKING_NUM - 1) != 0)
		{
			return false;
		}
	}
	if (mode & SENDER_PHONE_MODE)//�Ƚϼļ����ֻ���
	{
		if (strncmp(pkg1->senderPhone, pkg2->senderPhone, PHONE - 1) != 0)
		{
			return false;
		}
	}
	if (mode & RECEIVER_PHONE_MODE)//�Ƚ��ռ����ֻ���
	{
		if (strncmp(pkg1->receiverPhone, pkg2->receiverPhone, PHONE - 1) != 0)
		{
			return false;
		}
	}
	if (mode & PACKAGESTATE_MODE)//�Ƚϰ���״̬
	{
		if (pkg1->packageState != pkg2->packageState)
		{
			return false;
		}
	}
	return true;
}

double calculateShippingFee(Package* package, User* user)
{
	//�ױ�ϵ��
	const double VOLUMETRIC_WEIGHT_RATIO = 6000.0;
	//����/(Ԫ/ǧ��)
	const double FIRST_WEIGHT = 12.0;
	//����/(Ԫ/ǧ��)
	const double SUBSEQUENT_WEIGHT = 3.0;
	//�������/ǧ��
	double volumetricWeight = package->volume / VOLUMETRIC_WEIGHT_RATIO;
	//ʵ������/ǧ��
	double actualWeight = fmax(package->weight, volumetricWeight);
	//�����˷�
	double baseShippingFee = FIRST_WEIGHT + SUBSEQUENT_WEIGHT * (fmax(actualWeight - 1.0, 0.0));
	//�ļ���ʽ�ӷ�
	double shippingMethodFee = 0.0;
	switch (package->shippingMethod)
	{
		//��ͨ
	case ShippingStandard:
		shippingMethodFee = 0.0;
		break;
		//����
	case Express:
		shippingMethodFee = 10.0;
		break;
		//�Ỻ
	case Economic:
		shippingMethodFee = -10.0;
		break;
	}
	//�������ͼӷ�
	double packageTypeFee = 0.0;
	switch (package->packageType)
	{
		//��ͨ
	case PackageStandard:
		shippingMethodFee = 0.0;
		break;
		//����
	case Fragile:
		shippingMethodFee = 10.0;
		break;
		//����
	case Parcel:
		shippingMethodFee = 30.0;
		break;
	}
	//���żļ��ӷ�
	double HomeSentFee = 0.0;
	if (package->isHomeSent)
	{
		switch (user->userType)
		{
		case Regular:
			HomeSentFee = 3.0;
			break;
		case VIP:
			HomeSentFee = 1.0;
			break;
		}
	}
	//ʵ���˷�
	double actualShippingFee = fmax(baseShippingFee + shippingMethodFee + packageTypeFee + HomeSentFee, 0.0) * user->discount / 100.0;
	return actualShippingFee;
}

char* generateTrackingNumber()
{
	time_t temp = getStationTime();
	return digitalTime(temp) + 4;
}
long long getPackageOrderedNum(char* senderPhone, long long totalNum)
{
	totalNum = 0;
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->senderPhone, senderPhone) == 0 && pkg->packageState == Ordered)
		{
			totalNum++;
		}
	}
	return totalNum;
}
void showPackageOrderedWindow(int currentpage, long long totalNum, char* senderPhone)//���ĳ�
{
	cleardevice();//����
	buildWindow();
	long long start = (currentpage - 1) * 9 + 1;
	long long end = start + 8;
	if (end > totalNum) {
		end = totalNum;  // ���һҳ�Ľ���λ��
	}
	long long flag = 0;
	text(50, 50, "��ݵ���"), text(200, 50, "ȡ���˵绰"); text(400, 50, "�ռ���ַ"); text(800, 50, "�µ�ʱ��"); text(970, 50, "�ļ����");
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->senderPhone, senderPhone) == 0 && pkg->packageState == Ordered)
		{
			flag++;
			if (flag >= start && flag <= end) {
				text(50, 50 + (flag - start + 1) * 50, pkg->trackingNum);//��ݵ���
				text(200, 50 + (flag - start + 1) * 50, pkg->receiverPhone);//ȡ���˵绰
				text(400, 50 + (flag - start + 1) * 50, pkg->receiverAddress);//�ռ���ַ
				text(800, 50 + (flag - start + 1) * 50, formatTime(pkg->time.ordered));//�µ�ʱ��
				text(970, 50 + (flag - start + 1) * 50, pkg->shippingFee);//�ļ����
			}
		}
	}
}
long long getPackageCanceledNum(char* senderPhone, long long totalNum)
{
	totalNum = 0;
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->senderPhone, senderPhone) == 0 && pkg->packageState == Canceled)
		{
			totalNum++;
		}
	}
	return totalNum;
}
void showPackageCanceledWindow(int currentpage, long long totalNum, char* senderPhone)//��ȡ��
{
	cleardevice();//����
	buildWindow();
	long long start = (currentpage - 1) * 9 + 1;
	long long end = start + 8;
	if (end > totalNum) {
		end = totalNum;  // ���һҳ�Ľ���λ��
	}
	long long flag = 0;
	text(50, 50, "��ݵ���"), text(200, 50, "ȡ���˵绰"); text(400, 50, "�ռ���ַ"); text(800, 50, "ȡ��ʱ��"); text(970, 50, "�ļ����");
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->senderPhone, senderPhone) == 0 && pkg->packageState == Canceled)
		{
			flag++;
			if (flag >= start && flag <= end) {
				text(50, 50 + (flag - start + 1) * 50, pkg->trackingNum);//��ݵ���
				text(200, 50 + (flag - start + 1) * 50, pkg->receiverPhone);//ȡ���˵绰
				text(400, 50 + (flag - start + 1) * 50, pkg->receiverAddress);//�ռ���ַ
				text(800, 50 + (flag - start + 1) * 50, formatTime(pkg->time.canceled));//ȡ��ʱ��
				text(970, 50 + (flag - start + 1) * 50, pkg->shippingFee);//�ļ����
			}
		}
	}
}

long long getPackageShippedNum(char* senderPhone, long long totalNum)
{
	totalNum = 0;
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->senderPhone, senderPhone) == 0 && pkg->packageState == Shipped)
		{
			totalNum++;
		}
	}
	return totalNum;
}

void showPackageShippedWindow(int currentpage, long long totalNum, char* senderPhone)//�Ѽĳ�
{
	cleardevice();//����
	buildWindow();
	long long start = (currentpage - 1) * 9 + 1;
	long long end = start + 8;
	if (end > totalNum) {
		end = totalNum;  // ���һҳ�Ľ���λ��
	}
	long long flag = 0;
	text(50, 50, "��ݵ���"), text(200, 50, "�ռ��˵绰"); text(400, 50, "�ռ���ַ"); text(800, 50, "ǩ��ʱ��"); text(970, 50, "�ļ����");
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->senderPhone, senderPhone) == 0 && pkg->packageState == Shipped)
		{
			flag++;
			if (flag >= start && flag <= end)
			{
				text(50, 50 + (flag - start + 1) * 50, pkg->trackingNum);//��ݵ���
				text(200, 50 + (flag - start + 1) * 50, pkg->receiverPhone);//�ռ��˵绰
				text(400, 50 + (flag - start + 1) * 50, pkg->receiverAddress);//�ռ���ַ
				text(800, 50 + (flag - start + 1) * 50, formatTime(pkg->time.shipped));//ǩ��ʱ��
				text(970, 50 + (flag - start + 1) * 50, pkg->shippingFee);//�ļ����
			}
		}
	}
}

long long getPackagePendingNum(char* receiverPhone, long long totalNum)
{
	totalNum = 0;
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->receiverPhone, receiverPhone) == 0 && pkg->packageState == Pending)
		{
			totalNum++;
		}
	}
	return totalNum;
}

void showPackagePendingWindow(int currentpage, long long totalNum, char* receiverPhone)//��ȡ
{
	cleardevice();//����
	buildWindow();
	long long start = (currentpage - 1) * 9 + 1;
	long long end = start + 8;
	if (end > totalNum) {
		end = totalNum;  // ���һҳ�Ľ���λ��
	}
	long long flag = 0;
	text(200, 50, "��ݵ���"), text(450, 50, "ȡ����"); text(700, 50, "���ʱ��");
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->receiverPhone, receiverPhone) == 0 && pkg->packageState == Pending)
		{
			flag++;
			if (flag >= start && flag <= end) {
				text(200, 50 + (flag - start + 1) * 50, pkg->trackingNum);//��ݵ���
				text(450, 50 + (flag - start + 1) * 50, pkg->pickupCode);//ȡ����
				text(700, 50 + (flag - start + 1) * 50, formatTime(pkg->time.pending));//���ʱ��
			}
		}
	}
}

long long getPackageRefusedNum(char* receiverPhone, long long totalNum)
{
	totalNum = 0;
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->receiverPhone, receiverPhone) == 0 && pkg->packageState == Refused)
		{
			totalNum++;
		}
	}
	return totalNum;
}

void showPackageRefusedWindow(int currentpage, long long totalNum, char* receiverPhone)//����
{
	cleardevice();//����
	buildWindow();
	long long start = (currentpage - 1) * 9 + 1;
	long long end = start + 8;
	if (end > totalNum) {
		end = totalNum;  // ���һҳ�Ľ���λ��
	}
	long long flag = 0;
	text(200, 50, "��ݵ���"), text(450, 50, "ȡ����"); text(700, 50, "����ʱ��");
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->receiverPhone, receiverPhone) == 0 && pkg->packageState == Refused)
		{
			flag++;
			if (flag >= start && flag <= end) {
				text(200, 50 + (flag - start + 1) * 50, pkg->trackingNum);//��ݵ���
				text(450, 50 + (flag - start + 1) * 50, pkg->pickupCode);//ȡ����
				text(700, 50 + (flag - start + 1) * 50, formatTime(pkg->time.refused));//����ʱ��
			}
		}
	}
}

long long getPackageDeliveredNum(char* receiverPhone, long long totalNum)
{
	totalNum = 0;
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->receiverPhone, receiverPhone) == 0 && pkg->packageState == Delivered)
		{
			totalNum++;
		}
	}
	return totalNum;
}

void showPackageDeliveredWindow(int currentpage, long long totalNum, char* receiverPhone)//��ǩ��
{
	cleardevice();//����
	buildWindow();
	long long start = (currentpage - 1) * 9 + 1;
	long long end = start + 8;
	if (end > totalNum) {
		end = totalNum;  // ���һҳ�Ľ���λ��
	}
	long long flag = 0;
	text(200, 50, "��ݵ���"), text(450, 50, "ȡ����"); text(700, 50, "ǩ��ʱ��");
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->receiverPhone, receiverPhone) == 0 && pkg->packageState == Delivered)
		{
			flag++;
			if (flag >= start && flag <= end) {
				text(200, 50 + (flag - start + 1) * 50, pkg->trackingNum);//��ݵ���
				text(450, 50 + (flag - start + 1) * 50, pkg->pickupCode);//ȡ����
				text(700, 50 + (flag - start + 1) * 50, formatTime(pkg->time.delivered));//ǩ��ʱ��
			}
		}
	}
}

