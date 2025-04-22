#include "user.h"

// 用户链表指针
extern List* userList;
// 当前用户指针
User* g_currentUser = NULL;

/**
 * @brief 遍历包裹，传出昵称查找用户个数
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
 * @brief 昵称查找单个界面
 */
void trackPackageFoNameWindow(int page, long long TotalNumber, char* name) {//一次显示九个
	cleardevice();//清屏
	buildWindow();
	long long start = (page - 1) * 9 + 1;
	long long end = start + 8;
	if (end > TotalNumber) {
		end = TotalNumber;  // 最后一页的结束位置
	}
	ListNode* current = userList->head->next;
	text(50, 50, "昵称"); text(200, 50, "手机号"); text(400, 50, "经验值"); text(600, 50, "优惠券数"); text(800, 50, "等级");
	long long flag = 0;
	while (current) {
		User* use = (User*)current->data;
		if (strncmp(use->userName, name, 12)==0) {
			flag++;
			if (flag >= start && flag <= end) {
				text(50, 50 + (flag - start + 1) * 50, use->userName);//昵称
				text(200, 50 + (flag - start + 1) * 50, use->phoneNumber);//手机号
				text(400, 50 + (flag - start + 1) * 50, (int)use->experience);//经验值
				text(600, 50 + (flag - start + 1) * 50, use->couponCount);//优惠券数
				if (use->userType == 0)
				{
					text(800, 50 + (flag - start + 1) * 50, "普通");//等级
				}
				else {
					text(800, 50 + (flag - start + 1) * 50,"VIP");//等级
				}
			}
		}
		current = current->next;
	}
	return;
}
/**
 * @brief 账号查找单个界面
 */
void trackPackageFoPhoneNumberWindow(int page, long long TotalNumber, char* phoneNumber) {//一次显示九个
	cleardevice();//清屏
	buildWindow();
	long long start = (page - 1) * 9 + 1;
	long long end = start + 8;
	if (end > TotalNumber) {
		end = TotalNumber;  // 最后一页的结束位置
	}
	ListNode* current = userList->head->next;
	text(50, 50, "昵称"); text(200, 50, "手机号"); text(400, 50, "经验值"); text(600, 50, "优惠券数"); text(800, 50, "等级");
	long long flag = 0;
	while (current) {
		User* use = (User*)current->data;
		if (strncmp(use->phoneNumber, phoneNumber, PHONE)==0) {
			flag++;
			if (flag >= start && flag <= end) {
				text(50, 50 + (flag - start + 1) * 50, use->userName);//昵称
				text(200, 50 + (flag - start + 1) * 50, use->phoneNumber);//手机号
				text(400, 50 + (flag - start + 1) * 50, (int)use->experience);//经验值
				text(600, 50 + (flag - start + 1) * 50, use->couponCount);//优惠券数
				if (use->userType == 0)
				{
					text(800, 50 + (flag - start + 1) * 50, "普通");//等级
				}
				else {
					text(800, 50 + (flag - start + 1) * 50, "VIP");//等级
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
	//查找包裹
	Package refPackage{};
	strncpy(refPackage.trackingNum, trackingNum, TRACKING_NUM);
	Package* foundPackage = (Package*)list_find(packageList, &refPackage, TRACKINGNUM_MODE, cmpPackage);
	//包裹未找到
	if (foundPackage == NULL)
	{
		messbox("包裹不存在，请重新输入！");
		return;
	}
	foundPackage->packageState = Refused;
	//记录拒收时间
	foundPackage->time.refused = getStationTime();
	//保存包裹
	list_save(getPackages());
	//添加日志
	Log tempLog = {};
	sprintf_s(tempLog.description, DESCR, "用户%s拒收包裹%s", g_currentUser->phoneNumber, foundPackage->trackingNum);
	tempLog.createdTime = getStationTime();
	list_add(getLogs(), &tempLog);
	//保存日志
	list_save(getLogs());
	messbox("拒收成功！");
	// 返回
}

void deliverToHomePackage(char* trackingNum,char* receiverAddress) {
	Package package = {};
	strncpy(package.trackingNum, trackingNum, TRACKING_NUM);
	// 查找待取件包裹
	Package refPackage{};
	strncpy(refPackage.trackingNum, trackingNum, TRACKING_NUM);
	strncpy(refPackage.receiverPhone, g_currentUser->phoneNumber, PHONE);
	refPackage.packageState = Pending;
	Package* foundPackage = (Package*)list_find(packageList, &refPackage, TRACKINGNUM_MODE| RECEIVER_PHONE_MODE| PACKAGESTATE_MODE, cmpPackage);
	if (foundPackage == NULL)
	{
		messbox("包裹不存在，请重新输入！");
		return;
	}
	if (foundPackage->packageState != Pending) {//不是待取
		messbox("包裹状态存在问题");
		return;
	}
	// 更改状态
	foundPackage->isHomeDelivered = true;
	strncpy(foundPackage->receiverAddress, receiverAddress, ADDRESS);
	//保存包裹
	list_save(getPackages());
	// 添加日志
	Log tempLog = {};
	sprintf_s(tempLog.description, DESCR, "用户%s选择送件到楼包裹%s", g_currentUser->phoneNumber, foundPackage->trackingNum);
	tempLog.createdTime = getStationTime();
	list_add(getLogs(), &tempLog);
	// 保存日志
	list_save(getLogs());
	messbox("申请送件到楼成功！");
}

void cancelPackage(char* trackingNum)
{
	Package package = {};
	strncpy(package.trackingNum, trackingNum, TRACKING_NUM);
	// 查找已下单包裹
	Package refPackage{};
	strncpy(refPackage.trackingNum, trackingNum, TRACKING_NUM);
	Package* foundPackage = (Package*)list_find(packageList, &refPackage, TRACKINGNUM_MODE, cmpPackage);
	// 包裹未找到
	if (foundPackage == NULL)
	{
		messbox("包裹不存在，请重新输入！");
		return;
	}
	// 确认取消
	foundPackage->packageState = Canceled;
	// 记录取消时间
	foundPackage->time.canceled = getStationTime();
	//保存包裹
	list_save(getPackages());
	// 添加日志
	Log tempLog = {};
	sprintf_s(tempLog.description, DESCR, "用户%s取消包裹%s", g_currentUser->phoneNumber, foundPackage->trackingNum);
	tempLog.createdTime = getStationTime();
	list_add(getLogs(), &tempLog);
	// 保存日志
	list_save(getLogs());
	messbox("取消成功！");
}

void pickupPackage(char* trackingNum)
{
	Package package = {};
	strncpy(package.trackingNum, trackingNum, TRACKING_NUM);
	//查找待取件包裹
	Package refPackage{};
	strncpy(refPackage.trackingNum, trackingNum, TRACKING_NUM);
	strncpy(refPackage.receiverPhone, g_currentUser->phoneNumber, PHONE);
	Package* foundPackage = (Package*)list_find(packageList, &refPackage, TRACKINGNUM_MODE | RECEIVER_PHONE_MODE, cmpPackage);
	//包裹未找到
	if (foundPackage == NULL)
	{
		messbox("包裹不存在，请重新输入！");
		return;
	}
	//更改包裹状态为已签收
	foundPackage->packageState = Delivered;
	//记录签收时间
	foundPackage->time.delivered = getStationTime();
	//更新货架状态
	updateShelfAfterPickup(foundPackage);
	//保存包裹
	list_save(getPackages());
	//添加日志
	Log tempLog = {};
	sprintf_s(tempLog.description, DESCR, "用户%s签收包裹%s", g_currentUser->phoneNumber, foundPackage->trackingNum);
	tempLog.createdTime = getStationTime();
	list_add(getLogs(), &tempLog);
	//保存日志
	list_save(getLogs());
	messbox("取件成功！");
}

void sendPackageInfo(char* packageName, char* receiverAddress, char* receiverPhone, char* dormAddress, float weight, float volume, int shippingMethodOption,
	int packageTypeOption, int homeSentOption, int couponOption)
{
	Package package = {};
	//填写包裹名称
	strncpy(package.packageName, packageName, NAME);
	//自动填充寄件地址
	strcpy_s(package.senderAddress, ADDRESS, "吉林大学大学城");
	//填写取件地址
	strncpy(package.receiverAddress, receiverAddress, ADDRESS);
	// 自动填充寄件人手机号
	strcpy_s(package.senderPhone, PHONE, g_currentUser->phoneNumber);
	// 填写取件人手机号
	strncpy(package.receiverPhone, receiverPhone, PHONE);
	//填写重量
	package.weight = weight;
	//填写体积
	package.volume = volume;
	//选择寄件方式
	switch (shippingMethodOption)
	{
		//普通
	case 0:
		package.shippingMethod = ShippingStandard;
		break;
		//快递
	case 1:
		package.shippingMethod = Express;
		break;
		//经济
	case 2:
		package.shippingMethod = Economic;
		break;
		//输入错误
	default:
		break;
	}
	//选择包裹类型
	switch (packageTypeOption)
	{
		//普通
	case 0:
		package.packageType = PackageStandard;
		break;
		//易碎
	case 1:
		package.packageType = Fragile;
		break;
		//贵重
	case 2:
		package.packageType = Parcel;
		break;
		//输入错误
	default:
		break;
	}
	//是否上门取件
	switch (homeSentOption)
	{
		//快递点自寄
	case 1:
		package.isHomeSent = false;
		break;
		//上门取件
	case 2:
		package.isHomeSent = true;
		strncpy(package.dormAddress, dormAddress, ADDRESS);
		break;
		//输入错误
	default:
		break;
	}
	if (couponOption == 1) //使用优惠券
	{
		g_currentUser->couponCount--;//自动减一
	}
	// 结算运费
	package.shippingFee = calculateShippingFee(&package, g_currentUser);
	
	wchar_t wtext[256];
	char arr[20] = { '\0' };
	sprintf(arr, "%.2f", package.shippingFee);
	int len = MultiByteToWideChar(CP_ACP, 0, arr, -1, wtext, 256);  // GBK 编码
	if (len > 0)
	{
		HWND hnd = GetHWnd();
		MessageBoxW(hnd, wtext, L"寄件金额: ", MB_OK);
		int result = MessageBox(hnd, "确定下单?", "提示", MB_OKCANCEL);
		if (result == 1)
		{
			messbox("下单成功! ");
			//用户经验值增加
			g_currentUser->experience += ((int)log(package.shippingFee) + 1) * EXP_COEF;
			//生成快递单号
			strcpy_s(package.trackingNum, TRACKING_NUM, generateTrackingNumber());
			//添加待寄出包裹
			package.packageState = Ordered;
			package.time.ordered = getStationTime();
			list_add(getPackages(), &package);
			//保存包裹
			list_save(getPackages());
			//添加日志
			Log tempLog = {};
			sprintf_s(tempLog.description, DESCR, "用户%s下单包裹%s", g_currentUser->phoneNumber, package.trackingNum);
			tempLog.createdTime = getStationTime();
			list_add(getLogs(), &tempLog);
			// 保存日志
			list_save(getLogs());
			// 保存用户
			list_save(userList);
		}
		else if (result == 2)
		{
			return;
		}
		else
		{
			;
		}
	}
}
void userupgrade()
{
	if (g_currentUser->userType == Regular)
	{
		g_currentUser->userType = VIP;
		g_currentUser->discount = 80;
		list_save(userList);
		messbox("充值成功！");
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
	strncpy(refPackage.receiverPhone, g_currentUser->phoneNumber, PHONE);
	Package* foundPackage = (Package*)list_find(packageList, &refPackage, TRACKINGNUM_MODE | RECEIVER_PHONE_MODE, cmpPackage);
	if (foundPackage == NULL)
	{//找不到
		messbox("该快递单号的\"已签收\"包裹不存在！");
		return;
	}
	// 发送
	tempTicket.ticketId = generateTicketId();
	// 添加工单
	tempTicket.createdTime = getStationTime();
	strncpy(tempTicket.phoneNumber, g_currentUser->phoneNumber, PHONE);
	list_add(getTickets(), &tempTicket);
	// 保存工单
	list_save(getTickets());
	// 添加日志
	messbox("工单发送成功！");
}
void exchangecoupons(int number)
{
	//优惠券开始时间是3.1日0：00，三个月后就是6.1日0：00
	double threeMonthsInSeconds = (31 + 30 + 31) * 24 * 3600; // 三个月的秒数差
	struct tm activitystarttime = {};
	activitystarttime.tm_year = 125;
	activitystarttime.tm_mon = 2;//2代表3月
	activitystarttime.tm_mday = 1;
	activitystarttime.tm_hour = 0;
	activitystarttime.tm_min = 0;
	activitystarttime.tm_sec = 0;
	mktime(&activitystarttime);
	time_t 	activitystarttime_s = mktime(&activitystarttime);//开始日期秒数
	if (difftime(getStationTime(), activitystarttime_s) >= threeMonthsInSeconds)// 超过活动有效期
	{
		messbox("优惠活动已结束! ");
		return;
	}
	//兑换优惠券
	if (g_currentUser->experience < EXP_OF_PER_COUPON * number)
	{
		messbox("经验值不足！");
		return;
	}
	g_currentUser->couponCount += number;
	g_currentUser->experience -= EXP_OF_PER_COUPON * number;
	messbox("兑换成功！");
	// 保存用户
	list_save(userList);
}