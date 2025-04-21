#include "package.h"

// 包裹链表指针
extern List* packageList;

List* getPackages()
{
	return packageList;
}

static int timechoice = 0; // 全局变量，用于存储选择的排序方式
bool comparePackageByTime(const void* d1, const void* d2) {
	const Package* pkg1 = (const Package*)d1;
	const Package* pkg2 = (const Package*)d2;
	switch (timechoice) {
	case 0:
		return pkg1->time.ordered > pkg2->time.ordered; // 按下单时间降序排序
	case 1:
		return pkg1->time.pending > pkg2->time.pending; // 按待寄出时间降序排序
	case 2:
		return pkg1->time.shipped > pkg2->time.shipped; // 按发货时间降序排序
	case 3:
		return pkg1->time.delivered > pkg2->time.delivered; // 按签收时间降序排序
	case 4:
		return pkg1->time.refused > pkg2->time.refused; // 按拒收时间降序排序
	case 5:
		return pkg1->time.canceled > pkg2->time.canceled; // 按取消时间降序排序	
	}
	return false;
}

void sortPackagesByTime(int curchoice) {
	if (packageList == NULL || packageList->elementCount <= 1) {
		return; // 链表为空或只有一个元素，无需排序
	}
	timechoice = curchoice; // 设置全局变量为当前选择的排序方式
	list_sort(packageList, comparePackageByTime);
}
bool cmpPackage(const void* d1, const void* d2, int mode)
{
	const Package* pkg1 = (const Package*)d1;
	const Package* pkg2 = (const Package*)d2;
	if (mode & TRACKINGNUM_MODE)//比较快递单号
	{
		if (strncmp(pkg1->trackingNum, pkg2->trackingNum, TRACKING_NUM - 1) != 0)
		{
			return false;
		}
	}
	if (mode & SENDER_PHONE_MODE)//比较寄件人手机号
	{
		if (strncmp(pkg1->senderPhone, pkg2->senderPhone, PHONE - 1) != 0)
		{
			return false;
		}
	}
	if (mode & RECEIVER_PHONE_MODE)//比较收件人手机号
	{
		if (strncmp(pkg1->receiverPhone, pkg2->receiverPhone, PHONE - 1) != 0)
		{
			return false;
		}
	}
	if (mode & PACKAGESTATE_MODE)//比较包裹状态
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
	//抛比系数
	const double VOLUMETRIC_WEIGHT_RATIO = 6000.0;
	//首重/(元/千克)
	const double FIRST_WEIGHT = 12.0;
	//续重/(元/千克)
	const double SUBSEQUENT_WEIGHT = 3.0;
	//体积重量/千克
	double volumetricWeight = package->volume / VOLUMETRIC_WEIGHT_RATIO;
	//实际重量/千克
	double actualWeight = fmax(package->weight, volumetricWeight);
	//基础运费
	double baseShippingFee = FIRST_WEIGHT + SUBSEQUENT_WEIGHT * (fmax(actualWeight - 1.0, 0.0));
	//寄件方式加费
	double shippingMethodFee = 0.0;
	switch (package->shippingMethod)
	{
		//普通
	case ShippingStandard:
		shippingMethodFee = 0.0;
		break;
		//紧急
	case Express:
		shippingMethodFee = 10.0;
		break;
		//轻缓
	case Economic:
		shippingMethodFee = -10.0;
		break;
	}
	//包裹类型加费
	double packageTypeFee = 0.0;
	switch (package->packageType)
	{
		//普通
	case PackageStandard:
		shippingMethodFee = 0.0;
		break;
		//易碎
	case Fragile:
		shippingMethodFee = 10.0;
		break;
		//贵重
	case Parcel:
		shippingMethodFee = 30.0;
		break;
	}
	//上门寄件加费
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
	//实际运费
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
void showPackageOrderedWindow(int currentpage, long long totalNum, char* senderPhone)//待寄出
{
	cleardevice();//清屏
	buildWindow();
	long long start = (currentpage - 1) * 9 + 1;
	long long end = start + 8;
	if (end > totalNum) {
		end = totalNum;  // 最后一页的结束位置
	}
	long long flag = 0;
	text(50, 50, "快递单号"), text(200, 50, "取件人电话"); text(400, 50, "收件地址"); text(800, 50, "下单时间"); text(970, 50, "寄件金额");
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->senderPhone, senderPhone) == 0 && pkg->packageState == Ordered)
		{
			flag++;
			if (flag >= start && flag <= end) {
				text(50, 50 + (flag - start + 1) * 50, pkg->trackingNum);//快递单号
				text(200, 50 + (flag - start + 1) * 50, pkg->receiverPhone);//取件人电话
				text(400, 50 + (flag - start + 1) * 50, pkg->receiverAddress);//收件地址
				text(800, 50 + (flag - start + 1) * 50, formatTime(pkg->time.ordered));//下单时间
				text(970, 50 + (flag - start + 1) * 50, pkg->shippingFee);//寄件金额
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
void showPackageCanceledWindow(int currentpage, long long totalNum, char* senderPhone)//已取消
{
	cleardevice();//清屏
	buildWindow();
	long long start = (currentpage - 1) * 9 + 1;
	long long end = start + 8;
	if (end > totalNum) {
		end = totalNum;  // 最后一页的结束位置
	}
	long long flag = 0;
	text(50, 50, "快递单号"), text(200, 50, "取件人电话"); text(400, 50, "收件地址"); text(800, 50, "取消时间"); text(970, 50, "寄件金额");
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->senderPhone, senderPhone) == 0 && pkg->packageState == Canceled)
		{
			flag++;
			if (flag >= start && flag <= end) {
				text(50, 50 + (flag - start + 1) * 50, pkg->trackingNum);//快递单号
				text(200, 50 + (flag - start + 1) * 50, pkg->receiverPhone);//取件人电话
				text(400, 50 + (flag - start + 1) * 50, pkg->receiverAddress);//收件地址
				text(800, 50 + (flag - start + 1) * 50, formatTime(pkg->time.canceled));//取消时间
				text(970, 50 + (flag - start + 1) * 50, pkg->shippingFee);//寄件金额
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

void showPackageShippedWindow(int currentpage, long long totalNum, char* senderPhone)//已寄出
{
	cleardevice();//清屏
	buildWindow();
	long long start = (currentpage - 1) * 9 + 1;
	long long end = start + 8;
	if (end > totalNum) {
		end = totalNum;  // 最后一页的结束位置
	}
	long long flag = 0;
	text(50, 50, "快递单号"), text(200, 50, "收件人电话"); text(400, 50, "收件地址"); text(800, 50, "签收时间"); text(970, 50, "寄件金额");
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->senderPhone, senderPhone) == 0 && pkg->packageState == Shipped)
		{
			flag++;
			if (flag >= start && flag <= end)
			{
				text(50, 50 + (flag - start + 1) * 50, pkg->trackingNum);//快递单号
				text(200, 50 + (flag - start + 1) * 50, pkg->receiverPhone);//收件人电话
				text(400, 50 + (flag - start + 1) * 50, pkg->receiverAddress);//收件地址
				text(800, 50 + (flag - start + 1) * 50, formatTime(pkg->time.shipped));//签收时间
				text(970, 50 + (flag - start + 1) * 50, pkg->shippingFee);//寄件金额
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

void showPackagePendingWindow(int currentpage, long long totalNum, char* receiverPhone)//待取
{
	cleardevice();//清屏
	buildWindow();
	long long start = (currentpage - 1) * 9 + 1;
	long long end = start + 8;
	if (end > totalNum) {
		end = totalNum;  // 最后一页的结束位置
	}
	long long flag = 0;
	text(200, 50, "快递单号"), text(450, 50, "取件码"); text(700, 50, "入库时间");
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->receiverPhone, receiverPhone) == 0 && pkg->packageState == Pending)
		{
			flag++;
			if (flag >= start && flag <= end) {
				text(200, 50 + (flag - start + 1) * 50, pkg->trackingNum);//快递单号
				text(450, 50 + (flag - start + 1) * 50, pkg->pickupCode);//取件码
				text(700, 50 + (flag - start + 1) * 50, formatTime(pkg->time.pending));//入库时间
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

void showPackageRefusedWindow(int currentpage, long long totalNum, char* receiverPhone)//拒收
{
	cleardevice();//清屏
	buildWindow();
	long long start = (currentpage - 1) * 9 + 1;
	long long end = start + 8;
	if (end > totalNum) {
		end = totalNum;  // 最后一页的结束位置
	}
	long long flag = 0;
	text(200, 50, "快递单号"), text(450, 50, "取件码"); text(700, 50, "拒收时间");
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->receiverPhone, receiverPhone) == 0 && pkg->packageState == Refused)
		{
			flag++;
			if (flag >= start && flag <= end) {
				text(200, 50 + (flag - start + 1) * 50, pkg->trackingNum);//快递单号
				text(450, 50 + (flag - start + 1) * 50, pkg->pickupCode);//取件码
				text(700, 50 + (flag - start + 1) * 50, formatTime(pkg->time.refused));//拒收时间
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

void showPackageDeliveredWindow(int currentpage, long long totalNum, char* receiverPhone)//已签收
{
	cleardevice();//清屏
	buildWindow();
	long long start = (currentpage - 1) * 9 + 1;
	long long end = start + 8;
	if (end > totalNum) {
		end = totalNum;  // 最后一页的结束位置
	}
	long long flag = 0;
	text(200, 50, "快递单号"), text(450, 50, "取件码"); text(700, 50, "签收时间");
	for (ListNode* node = packageList->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->receiverPhone, receiverPhone) == 0 && pkg->packageState == Delivered)
		{
			flag++;
			if (flag >= start && flag <= end) {
				text(200, 50 + (flag - start + 1) * 50, pkg->trackingNum);//快递单号
				text(450, 50 + (flag - start + 1) * 50, pkg->pickupCode);//取件码
				text(700, 50 + (flag - start + 1) * 50, formatTime(pkg->time.delivered));//签收时间
			}
		}
	}
}

