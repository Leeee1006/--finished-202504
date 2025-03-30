#include "common.h"
#include "op.h"
#include "login.h"
extern Package* packageHead;
extern User* userHead;
void testInputPackageInfo() 
{
    Package* pkg = (Package*)malloc(sizeof(Package));
    if (!pkg) {
        fprintf(stderr, "内存分配失败\n");
        return;
    }
    memset(pkg, 0, sizeof(Package));

    printf("请输入包裹信息:\n");

    printf("包裹快递单号：");
    scanf_s("%14s", pkg->trackingNum, (unsigned)_countof(pkg->trackingNum));
    if (isTrackingNumExist(pkg->trackingNum, packageHead))
    {
        fprintf(stderr, "快递单号已存在，请重新输入。\n");
        free(pkg);
        return;
    }

    // 清空输入缓冲区
    while (getchar() != '\n');

    pkg->packageState = Pending;
    pkg->isHomeDelivered = false;
    pkg->isHomeSent = false;
    strncpy(pkg->receiverAddress, "吉林大学本驿站", sizeof(pkg->receiverAddress) - 1);
    pkg->receiverAddress[sizeof(pkg->receiverAddress) - 1] = '\0';

    pkg->time.pending = time(NULL);
    pkg->time.delivered = 0;
    pkg->time.ordered = 0;
    pkg->time.shipped = 0;
    pkg->time.canceled = 0;
    pkg->time.refused = 0;

    printf("包裹名称: ");
    scanf_s("%19s", pkg->packageName, (unsigned)_countof(pkg->packageName));

    // 清空输入缓冲区
    while (getchar() != '\n');

    printf("包裹类型 (0: 普通, 1: 贵重, 2: 大件): ");
    scanf_s("%d", &(pkg->packageType));

    // 清空输入缓冲区
    while (getchar() != '\n');

    printf("包裹体积: ");
    scanf_s("%lf", &(pkg->volume));

    // 清空输入缓冲区
    while (getchar() != '\n');

    printf("包裹重量: ");
    scanf_s("%lf", &(pkg->weight));

    // 清空输入缓冲区
    while (getchar() != '\n');

    printf("寄件地址: ");
    scanf_s("%199s", pkg->senderAddress, (unsigned)_countof(pkg->senderAddress));

    // 清空输入缓冲区
    while (getchar() != '\n');

    printf("收件人手机号: ");
    scanf_s("%11s", pkg->receiverPhone, (unsigned)_countof(pkg->receiverPhone));

    // 校验输入的包裹信息
    if (!validateWeight(pkg->weight) || !validateVolume(pkg->volume) || !validatePackageType(pkg->packageType))
    {
        fprintf(stderr, "包裹信息无效，请重新输入。\n");
        free(pkg);
        return;
    }

    // 放置包裹并生成取件码
    if (placePackageOnShelf(pkg))
    {
        printf("包裹已成功放置，取件码: %s\n", pkg->pickupCode);

        pkg->nextPackage = packageHead;
        packageHead = pkg;

        // 保存包裹信息
        savePackages();
    }
    else
    {
        fprintf(stderr, "包裹放置失败。\n");
        free(pkg);
    }
}

void testLoadPackages()
{
    Package* packages = packageHead;
    if (packages)
    {
        printf("包裹信息加载成功。\n");
        Package* current = packages;
        while (current)
        {
            char timeBuffer[64];
            struct tm timeInfo;
            localtime_s(&timeInfo, &current->time.pending);
            strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", &timeInfo);

            printf("快递单号: %s, 名称: %s, 类型: %d, 体积: %.2f, 重量: %.2f, 取件码: %s, 寄件人手机号: %s, 寄件地址: %s, 收件人手机号: %s, 收件地址: %s, 运费: %.2f, 寄件方式: %d, 使用优惠券数量: %d, 包裹状态: %d, 取件地址: %s, 是否送件到楼: %d, 是否取件到楼: %d 入库时间：%s\r\n",
                current->trackingNum, current->packageName, current->packageType,
                current->volume, current->weight, current->pickupCode,
                current->senderPhone, current->senderAddress, current->receiverPhone,
                current->receiverAddress, current->shippingFee, current->shippingMethod,
                current->usedCouponNum, current->packageState, current->pickupAddress,
                current->isHomeDelivered, current->isHomeSent, timeBuffer);
            current = current->nextPackage;
        }
    }
    else
    {
        fprintf(stderr, "包裹信息加载失败。\n");
    }
}

// 测试用户注册功能
void testUserRegistration()
{
    char userName[NAME], phoneNumber[PHONE], password[PASSWORD];

    printf("请输入用户信息:\n");

    printf("用户名: ");
    scanf("%19s", userName);

    printf("手机号: ");
    scanf("%11s", phoneNumber);

    printf("密码: ");
    scanf("%10s", password);

    // 注册用户
    if (userRegister(userName, phoneNumber, password))
    {
        printf("用户注册成功。\n");
    }
    else
    {
        fprintf(stderr, "用户注册失败。\n");
    }
}
// 测试用户登录功能
void testUserLogin()
{
    char phoneNumber[PHONE];
    char password[PASSWORD];

    printf("请输入登录信息:\n");

    printf("手机号: ");
    scanf("%11s", phoneNumber);

    printf("密码: ");
    scanf("%10s", password);

    // 用户登录
    User* loggedInUser = userLogin(phoneNumber, password);
    if (loggedInUser) {
        printf("用户登录成功。\n");
        printf("你是：%s 级别： %d", loggedInUser->userName, loggedInUser->userType);
        free(loggedInUser);
    }
    else {
        fprintf(stderr, "用户登录失败。\n");
    }
}
void generateRandomPackage(Package* pkg, int index) {
    snprintf(pkg->trackingNum, sizeof(pkg->trackingNum), "TN%05d", index);
    snprintf(pkg->packageName, sizeof(pkg->packageName), "Package%05d", index);
    pkg->packageType = static_cast<PackageType>(rand() % 3);
    pkg->volume = (rand() % 1000) / 10.0;
    pkg->weight = (rand() % 1000) / 10.0;
    snprintf(pkg->senderPhone, sizeof(pkg->senderPhone), "138%08d", rand() % 100000000);
    snprintf(pkg->senderAddress, sizeof(pkg->senderAddress), "Sender Address %05d", index);
    snprintf(pkg->receiverPhone, sizeof(pkg->receiverPhone), "139%08d", rand() % 100000000);
    snprintf(pkg->receiverAddress, sizeof(pkg->receiverAddress), "Receiver Address %05d", index);
    pkg->shippingFee = (rand() % 1000) / 10.0;
    pkg->shippingMethod = static_cast<ShippingMethod>(rand() % 3);
    pkg->usedCouponNum = rand() % 10;
    snprintf(pkg->pickupCode, sizeof(pkg->pickupCode), "PC%05d", index);
    pkg->packageState = static_cast<PackageState>(rand() % 5);
    snprintf(pkg->pickupAddress, sizeof(pkg->pickupAddress), "Pickup Address %05d", index);
    pkg->isHomeDelivered = rand() % 2;
    pkg->isHomeSent = rand() % 2;
    pkg->time.pending = time(NULL) - (rand() % 100000);
    pkg->time.delivered = time(NULL) - (rand() % 100000);
    pkg->time.ordered = time(NULL) - (rand() % 100000);
    pkg->time.shipped = time(NULL) - (rand() % 100000);
    pkg->time.canceled = time(NULL) - (rand() % 100000);
    pkg->time.refused = time(NULL) - (rand() % 100000);
}

void measurePerformance()
{
    const int numPackages = 1000000;
    Package* head = NULL;
    Package* tail = NULL;
    const char* tempFileName = "temp_packages.dat";

    // 生成十万个包裹并写入临时文件
    clock_t start = clock();
    FILE* fp = fopen(tempFileName, "wb");
    if (!fp) {
        fprintf(stderr, "无法打开文件进行写入\n");
        return;
    }
    for (int i = 0; i < numPackages; i++)
    {
        Package pkg;
        memset(&pkg, 0, sizeof(Package));
        generateRandomPackage(&pkg, i);
        fwrite(&pkg, sizeof(Package), 1, fp);
    }
    fclose(fp);
    clock_t end = clock();
    printf("生成并写入十万个包裹所需时间: %.2f 秒\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 从文件读取十万个包裹形成链表
    start = clock();
    fp = fopen(tempFileName, "rb");
    if (!fp) {
        fprintf(stderr, "无法打开文件进行读取\n");
        return;
    }
    for (int i = 0; i < numPackages; i++)
    {
        Package* pkg = (Package*)malloc(sizeof(Package));
        if (!pkg) {
            fprintf(stderr, "内存分配失败\n");
            fclose(fp);
            return;
        }
        fread(pkg, sizeof(Package), 1, fp);
        pkg->nextPackage = NULL;

        if (!head)
            head = tail = pkg;
        else
        {
            tail->nextPackage = pkg;
            tail = pkg;
        }
    }
    fclose(fp);
    end = clock();
    printf("从文件读取并形成链表所需时间: %.2f 秒\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 遍历链表
    start = clock();
    Package* current = head;
    while (current)
    {
        current = current->nextPackage;
    }
    end = clock();
    printf("遍历十万个包裹所需时间: %.2f 秒\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 插入包裹
    start = clock();
    for (int i = 0; i < 1000; i++)
    {
        Package* pkg = (Package*)malloc(sizeof(Package));
        if (!pkg) {
            fprintf(stderr, "内存分配失败\n");
            return;
        }
        memset(pkg, 0, sizeof(Package));
        generateRandomPackage(pkg, numPackages + i);
        pkg->nextPackage = head;
        head = pkg;
    }
    end = clock();
    printf("插入一千个包裹所需时间: %.2f 秒\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 删除包裹
    start = clock();
    for (int i = 0; i < 1000; i++)
    {
        if (head)
        {
            Package* temp = head;
            head = head->nextPackage;
            free(temp);
        }
    }
    end = clock();
    printf("删除一千个包裹所需时间: %.2f 秒\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 释放链表
    start = clock();
    while (head)
    {
        Package* temp = head;
        head = head->nextPackage;
        free(temp);
    }
    end = clock();
    printf("释放链表所需时间: %.2f 秒\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 删除临时文件
    remove(tempFileName);
}

// 测试主函数
int main()
{
    initializeShelves();
    loadPackages();
    int choice = 0;
    while (1)
    {
        printf("请选择测试功能:\n");
        printf("1. 用户注册\n");
        printf("2. 用户登录\n");
        printf("3. 输入包裹信息\n");
        printf("4. 读取包裹信息\n");
        printf("5. 寄取件通知提醒\n");
        printf("6. 性能评估\n");
		printf("7. 释放包裹\n");
		printf("8. 释放用户\n");
		printf("9. 退出\n");
        scanf_s("%d", &choice);
        switch (choice)
        {
        case 1:
            testUserRegistration();
            break;
        case 2:
            testUserLogin();
            break;
        case 3:
            testInputPackageInfo();
            break;
        case 4:
            testLoadPackages();
            break;
        case 5:
            sendNotification(1); // 传递自定义的小时数阈值
            break;
        case 6:
            measurePerformance();
            break;
        case 7:
            freePackages();
        case 8:
            freeUsers();
        case 9:
			return 0;
        default:
            break;
        }
    }

    return 0;
}
