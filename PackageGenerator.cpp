#define _CRT_SECURE_NO_WARNINGS
#include <cassert>
#include "fore.h"
#include "op.h"
#define PHONE 12
#define MAX_MONTH 12
// 月份天数表（2025非闰年）
const int months[MAX_MONTH] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
// 生成指定范围内的随机整数
int rand_range(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

// 生成2025年随机日期
time_t Generate_2025_Date(int choice) {
    struct tm tm = { 0 };
    // Initialize time components
    tm.tm_hour = rand_range(0, 23);  // Random hour 0-23
    tm.tm_min = rand_range(0, 59);    // Random minute 0-59
    tm.tm_sec = 0;

    int s = rand_range(0, 1);
    const int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // Days in each month (2024)

    switch (choice) {
    case 0: // 基础
        tm.tm_year = 124 + s;
        if (s == 1) { // 2025
            tm.tm_mon = rand_range(0, 3); // 0到3个月之间
            if (tm.tm_mon == 0) {
                tm.tm_mday = rand_range(1, 31); // 1月31天
            }
            else if (tm.tm_mon == 1) {
                tm.tm_mday = rand_range(1, 28); // 2月28天（2025年是平年）
            }
            else if (tm.tm_mon == 2) {
                tm.tm_mday = rand_range(1, 31); // 3月31天
            }
            else {
                tm.tm_mday = rand_range(1, 15); // 4月15天
            }
        }
        if (s == 0) { // 2024
            tm.tm_mon = rand_range(0, 11);
            tm.tm_mday = rand_range(1, months[tm.tm_mon]);
        }
        break;

    case 1: // 春节（2025年2月19日）
        tm.tm_year = 125;
        tm.tm_mon = 1; // 2月
        tm.tm_mday = rand_range(15, 31);
        break;

    case 2: // 儿童节（6月1日），修改为最接近的日期
        tm.tm_year = 124;
        tm.tm_mon = 5; // 6月（5表示6月）
        tm.tm_mday = rand_range(1, 3);
        break;

    case 3: // 双11（11月11日），修改为最接近的日期
        tm.tm_year = 124;
        tm.tm_mon = 10; // 11月（10表示11月）
        tm.tm_mday = rand_range(1, 15);
        break;

    case 4: // 中秋节（2024年9月13日），修改为最接近的日期
        tm.tm_year = 124;
        tm.tm_mon = 8; // 9月（8表示9月）
        tm.tm_mday = rand_range(1, 15);
        break;

    case 5: // 双12（12月12日），修改为最接近的日期
        tm.tm_year = 124;
        tm.tm_mon = 11; // 12月（11表示12月）
        tm.tm_mday = rand_range(1, 15);
        break;

    case 6: // 开学季（2024年8月29日）
        tm.tm_year = 124;
        tm.tm_mon = 7; // 8月
        tm.tm_mday = rand_range(25, 31);
        break;

    default: // 默认
        tm.tm_year = 124 + s;
        if (s == 1) { // 2025
            tm.tm_mon = rand_range(0, 3); // 0到3个月之间
            if (tm.tm_mon == 0) {
                tm.tm_mday = rand_range(1, 31); // 1月31天
            }
            else if (tm.tm_mon == 1) {
                tm.tm_mday = rand_range(1, 28); // 2月28天（2025年是平年）
            }
            else if (tm.tm_mon == 2) {
                tm.tm_mday = rand_range(1, 31); // 3月31天
            }
            else {
                tm.tm_mday = rand_range(1, 15); // 4月15天
            }
        }
        if (s == 0) { // 2024
            tm.tm_mon = rand_range(0, 11);
            tm.tm_mday = rand_range(1, months[tm.tm_mon]);
        }
        break;
    }

    // 确保时间不超出最大值2025年4月12日
    if (tm.tm_year == 125 && tm.tm_mon == 3 && tm.tm_mday > 12) { // 如果是2025年4月，并且天数大于12
        tm.tm_mday = 12;
    }

    return mktime(&tm);
}void generate_tracking_number(char* tracking_number)
{
    for (int i = 0; i < 10; i++) {
        // 生成0-9之间的随机数并转为字符 '0' - '9'
        tracking_number[i] = rand_range(0, 9) + '0';
    }
    tracking_number[10] = '\0';  // 添加字符串结束符
   
}
// 生成有效手机号
void Generate_Phone(char* phone)
{
    snprintf(phone, PHONE, "1%03d%03d%03d%d",
        rand_range(300, 999),  // 有效运营商号段
        rand_range(100, 999),
        rand_range(100, 999),
        rand_range(0, 9));
}
User* g_currentUsers;
// 生成包裹名称
void GenerateNames(Package* pkg, int choice)
{
    if (choice == 0)//基础
    {
        const char* names[] = { "电子产品", "服装", "图书", "食品", "家具" };
        strncpy_s(pkg->packageName, names[rand() % 5], NAME);
    }
    if (choice == 1)//春节
    {
        const char* names[] = { "年货", "新衣服", "礼品", "春联", "生鲜" };
        strncpy_s(pkg->packageName, names[rand() % 5], NAME);
    }
    if (choice == 2)//儿童节
    {
        const char* names[] = { "儿童文具", "儿童服装", "儿童图书", "儿童食品", "儿童礼物" };
        strncpy_s(pkg->packageName, names[rand() % 5], NAME);
    }
    if (choice == 3)//双11
    {
        const char* names[] = { "电子产品", "服装", "手机", "日用品", "家具" };
        strncpy_s(pkg->packageName, names[rand() % 5], NAME);
    }
    if (choice == 4)//中秋节
    {
        const char* names[] = { "礼物", "月饼礼盒", "酒类", "中秋食品", "中秋饰品" };
        strncpy_s(pkg->packageName, names[rand() % 5], NAME);
    }
    if (choice == 5)//双12
    {
        const char* names[] = { "清仓处理物品", "冬季服装", "图书", "食品", "家具" };
        strncpy_s(pkg->packageName, names[rand() % 5], NAME);
    }
    if (choice == 6)//开学季
    {
        const char* names[] = { "文具", "书包", "课本", "电子产品", "行李箱" };
        strncpy_s(pkg->packageName, names[rand() % 5], NAME);
    }
    pkg->packageName[NAME - 1] = '\0';  // 强制终止
}
void CreatPackage(Package* pkg, int choice)//利用choice生成包裹的所有内容
{
    //包裹名称
    GenerateNames(pkg, choice);
    //寄件地址/收件地址
    const char* adress1[] = { "北京市","上海市","天津市","重庆市","河北省石家庄市","河北省唐山市","山西省太原市","内蒙古自治区呼和浩特市","辽宁省沈阳市",
        "辽宁省大连市","吉林省长春市","黑龙江省哈尔滨市","江苏省南京市", "江苏省徐州市", "浙江省杭州市", "安徽省合肥市", "福建省福州市", "福建省厦门市", "江西省南昌市",
        "江西省景德镇市", "山东省济南市", "山东省青岛市", "河南省郑州市", "河南省洛阳市", "湖北省武汉市", "湖南省长沙市", "广东省广州市", "广东省深圳市",
        "广东省佛山市", "广西壮族自治区南宁市", "广西壮族自治区桂林市", "海南省海口市", "海南省三亚市", "四川省成都市", "贵州省贵阳市", "贵州省遵义市",
        "云南省昆明市", "西藏自治区拉萨市", "陕西省西安市", "甘肃省兰州市", "青海省西宁市", "宁夏回族自治区银川市", "新疆维吾尔自治区乌鲁木齐市", "广东省珠海市" , "广东省东莞市" ,
        "浙江省温州市" , "江苏省无锡市" , "辽宁省鞍山市" , "黑龙江省大庆市" };
    //收件地址/寄件地址
    const char* adress2[] = { "吉林大学大大学城" };
    int panduan = rand() % 10 + 1;
    //分配权重,少指的是从大学城出发，多指的是从别的地方来的
    if (panduan == 10) 
    {
        strncpy_s(pkg->receiverAddress, adress2[0], ADDRESS);
        pkg->receiverAddress[ADDRESS - 1] = '\0';  // 强制终止
        strncpy_s(pkg->senderAddress, adress1[rand() % 49], ADDRESS);
        pkg->senderAddress[ADDRESS - 1] = '\0';  // 强制终止
        pkg->isHomeDelivered = 0;
        pkg->isHomeSent = rand() % 2;
        if (pkg->isHomeSent == 1)//想要上门寄件
        {
            const char* adress3[] = { "大学城一公寓","大学城二公寓","大学城三公寓"};
            strncpy_s(pkg->dormAddress, adress3[rand() % 3], ADDRESS);
            pkg->dormAddress[ADDRESS - 1] = '\0';  // 强制终止
        }
    }
    else 
    {
        strncpy_s(pkg->receiverAddress, adress2[0], ADDRESS);
        pkg->receiverAddress[ADDRESS - 1] = '\0';  // 强制终止
        strncpy_s(pkg->senderAddress, adress1[rand() % 49], ADDRESS);
        pkg->senderAddress[ADDRESS - 1] = '\0';  // 强制终止
        pkg->isHomeSent = 0;
        pkg->isHomeDelivered = rand() % 2;
        if (pkg->isHomeDelivered == 1)//想要上门取件
        {
            const char* adress4[] = { "大学城一公寓","大学城二公寓","大学城三公寓" };
            strncpy_s(pkg->dormAddress, adress1[rand() % 3], ADDRESS);
            pkg->dormAddress[ADDRESS - 1] = '\0';  // 强制终止

        }
    }
    // 基本属性
    pkg->packageType = (PackageType)(rand() % 3);
    pkg->shippingMethod = (ShippingMethod)(rand() % 3);
    pkg->volume = 0.1 + (rand() % 10000) / 100.0;
    pkg->weight = (rand() % 1001) / 10.0; // 精确到0.1kg的随机重量
    pkg->usedCouponNum = rand() % 5;
    pkg->shippingFee = calculateShippingFee(pkg, g_currentUser);
    // 生成联系方式
 Generate_Phone(pkg->senderPhone);
   strncpy(pkg->receiverPhone, "15139490674", PHONE);
  //  Generate_Phone(pkg->receiverPhone);
        // 生成取件码
    int shelfid = rand() % 10;
    int levelnum = rand() % 5;
    int third = rand() % 100;
    snprintf(pkg->pickupCode, sizeof(pkg->pickupCode), "%d-%d-%03d", shelfid + 1, levelnum + 1, third);
    // 生成基础下单时间
    time_t base = Generate_2025_Date(choice);
    pkg->time.ordered = base;
    // 根据时间线生成唯一快递单号
    generate_tracking_number(pkg->trackingNum);
    //snprintf(pkg->trackingNum, sizeof(pkg->trackingNum), digitalTime(base) + 4);
    int prob = rand_range(0, 100);
    if (prob < 55) {        // 已收件 55%
        pkg->packageState = Delivered;
        pkg->time.shipped = base + rand_range(1, 3) * 86400;  // 1-3天后发货
        pkg->time.delivered = pkg->time.shipped + rand_range(2, 7) * 86400;
    }
    else if (prob < 70) {   // 运输中 15%
        pkg->packageState = Shipped;
        pkg->time.shipped = base + rand_range(1, 3) * 86400;
    }
    else if (prob < 80) {   // 已取消 10%
        pkg->packageState = Canceled;
        pkg->time.canceled = base + rand_range(1, 2) * 86400;
    }
    else if (prob < 85) {   // 已下单 5%
        pkg->packageState = Ordered;
        if (panduan != 10) { pkg->packageState = Shipped; }//确保九里面没有非吉大的用户
        pkg->time.shipped = base + rand_range(1, 3) * 86400;
        pkg->time.pending = pkg->time.shipped + rand_range(1, 5) * 86400;
    }
    else if (prob < 90) {   // 拒收 5%
        pkg->packageState = Refused;
        pkg->time.shipped = base + rand_range(1, 3) * 86400;
        pkg->time.refused = pkg->time.shipped + rand_range(1, 2) * 86400;
    }
    else if (prob < 95) {   // 误取 5%
        pkg->packageState = Misdelivered;
        pkg->time.shipped = base + rand_range(1, 3) * 86400;
        pkg->time.delivered = pkg->time.shipped + rand_range(2, 7) * 86400;
    }
    else {                  // 损坏丢失 5%
        pkg->packageState = DamagedLost;
        pkg->time.shipped = base + rand_range(1, 3) * 86400;
        pkg->time.delivered = pkg->time.shipped + rand_range(2, 7) * 86400;
    }
}
int main() {
    initLogs();
    initTickets();
    loadUsers();
    loadPackages();
    initializeShelves();

    User tmpUser = {};
    tmpUser.discount = 100;
    g_currentUser = &tmpUser;

    srand((unsigned)time(NULL));
    const int count = 100;
    for (int i = 1; i <= count; i++)//基础
    {
        Package pkg;
        CreatPackage(&pkg, 0);
        list_add(getPackages(), &pkg);
    }
    for (int i = 101; i <= 103; i++)//春节
    {
        Package pkg;
        CreatPackage(&pkg, 1);
        list_add(getPackages(), &pkg);
    }
    for (int i = 104; i < 105; i++)//儿童节
    {
        Package pkg;
        CreatPackage(&pkg, 2);
        list_add(getPackages(), &pkg);
    }
    for (int i = 106; i < 110; i++)//双11
    {
        Package pkg;
        CreatPackage(&pkg, 3);
        list_add(getPackages(), &pkg);
    }
    for (int i = 111; i < 112; i++)//中秋节
    {
        Package pkg;
        CreatPackage(&pkg, 4);
        list_add(getPackages(), &pkg);
    }
    for (int i = 113; i < 115; i++)//双12
    {
        Package pkg;
        CreatPackage(&pkg, 5);
        list_add(getPackages(), &pkg);
    }
    for (int i = 116; i < 120; i++)//开学季
    {
        Package pkg;
        CreatPackage(&pkg, 6);
        list_add(getPackages(), &pkg);
    }
    for (int i = 121; i < 200; i++)//为了凑到20000
    {
        Package pkg;
        CreatPackage(&pkg, 0);
        list_add(getPackages(), &pkg);
    }
    //指数函数拟合日期2025.1.1---2025.1.14
    //对数函数拟合日期2025.2.1---2025.2.14

    list_save(getPackages());
    return 0;
}
