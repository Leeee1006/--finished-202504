#include "common.h"
#include "op.h"
#include "list.h"
#include "login.h"

extern List* packageList; // 全局包裹链表指针
extern List* userList; // 全局用户链表指针

void testInputPackageInfo()
{
    Package* pkg = (Package*)safeMalloc(sizeof(Package),"input_temppkg");
    if (!pkg)
    {
        fprintf(stderr, "内存分配失败\n");
        return;
    }
    memset(pkg, 0, sizeof(Package));

    printf("请输入包裹信息:\n");

    printf("包裹快递单号：");
    scanf("%7s", pkg->trackingNum);
    if (isTrackingNumExist(pkg->trackingNum))
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
    pkg->time.delivered = time(NULL);
    pkg->time.ordered = time(NULL);
    pkg->time.shipped = time(NULL);
    pkg->time.canceled = time(NULL);
    pkg->time.refused = time(NULL);

    printf("包裹名称: ");
    scanf("%19s", pkg->packageName);

    // 清空输入缓冲区
    while (getchar() != '\n');

    printf("包裹类型 (0: 普通, 1: 贵重, 2: 大件): ");
    scanf("%d", (int*)&(pkg->packageType));

    // 清空输入缓冲区
    while (getchar() != '\n');

    printf("包裹体积: ");
    scanf("%f", &(pkg->volume));

    // 清空输入缓冲区
    while (getchar() != '\n');

    printf("包裹重量: ");
    scanf("%f", &(pkg->weight));

    // 清空输入缓冲区
    while (getchar() != '\n');

    printf("寄件地址: ");
    scanf("%50s", pkg->senderAddress);

    // 清空输入缓冲区
    while (getchar() != '\n');

    printf("收件人手机号: ");
    scanf("%11s", pkg->receiverPhone);

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

        list_add(packageList, pkg);

        // 保存包裹信息
        savePackages();
        saveShelves();
    }
    else
    {
        fprintf(stderr, "包裹放置失败。\n");
        free(pkg);
    }
}

void testLoadPackages()
{

    ListNode* current = packageList->head->next; // 跳过头节点
    printf("包裹信息加载成功。\n");

    while (current)
    {
        if (current->data == NULL) {
            fprintf(stderr, "发现空数据节点，跳过。\n");
            current = current->next;
            continue;
        }

        Package* pkg = (Package*)current->data;

        // 避免访问空指针
        const char* trackingNum = pkg->trackingNum ? pkg->trackingNum : "(空)";
        const char* packageName = pkg->packageName ? pkg->packageName : "(空)";
        const char* senderPhone = pkg->senderPhone ? pkg->senderPhone : "(空)";
        const char* senderAddress = pkg->senderAddress ? pkg->senderAddress : "(空)";
        const char* receiverPhone = pkg->receiverPhone ? pkg->receiverPhone : "(空)";
        const char* receiverAddress = pkg->receiverAddress ? pkg->receiverAddress : "(空)";
        const char* pickupAddress = pkg->pickupAddress ? pkg->pickupAddress : "(空)";

        // 修正时间转换
        char timeBuffer[64] = "(无时间)";
        if (pkg->time.pending != 0) {
            struct tm timeInfo;
            time_t pendingTime = pkg->time.pending; // 确保是 time_t
            if (localtime_s(&timeInfo, &pendingTime) == 0) {
                strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", &timeInfo);
            }
        }

        printf("快递单号: %s, 名称: %s, 类型: %d, 体积: %.2f, 重量: %.2f, 取件码: %s, "
            "寄件人手机号: %s, 寄件地址: %s, 收件人手机号: %s, 收件地址: %s, 运费: %.2f, "
            "寄件方式: %d, 使用优惠券数量: %d, 包裹状态: %d, 取件地址: %s, "
            "是否送件到楼: %d, 是否取件到楼: %d, 入库时间：%s\n",
            trackingNum, packageName, pkg->packageType,
            pkg->volume, pkg->weight, pkg->pickupCode,
            senderPhone, senderAddress, receiverPhone,
            receiverAddress, pkg->shippingFee, pkg->shippingMethod,
            pkg->usedCouponNum, pkg->packageState, pickupAddress,
            pkg->isHomeDelivered, pkg->isHomeSent, timeBuffer);

        current = current->next;
    }
}


// 测试用户注册功能
void testUserRegistration()
{
    char userName[NAME], phoneNumber[PHONE], password[PASSWORD];

    printf("请输入用户信息:\n");

    printf("用户名: ");
    scanf("%12s", userName);

    printf("手机号: ");
    scanf("%11s", phoneNumber);

    printf("密码: ");
    scanf("%6s", password);

    // 注册用户
    if (userRegister(userName, phoneNumber, password,Regular))
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
    scanf("%6s", password);

    // 用户登录
    User* loggedInUser = userLogin(phoneNumber, password);
    if (loggedInUser)
    {
        printf("用户登录成功。\n");
        printf("你是：%s 级别： %d\n", loggedInUser->userName, loggedInUser->userType);
    }
    else
    {
        fprintf(stderr, "用户登录失败。\n");
    }
}

// 测试主函数
int main()
{
    loadPackages();
    initializeShelves();
    loadUsers();
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
        printf("9. 退出\n");
        scanf("%d", &choice);
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
            // 性能评估功能可以在这里实现
            break;
        case 9:
            freePackages();
            freeUsers();
            return 0;
        default:
            break;
        }
    }

    return 0;
}
