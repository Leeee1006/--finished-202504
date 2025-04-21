#include "op.h"
#include "list.h"

// 定义货架层信息
List* packageList = NULL; // 全局包裹链表指针

/**************************** 工具函数 *******************************/
int validateWeight(double weight)
{
    if (weight <= 0||weight>100)
    {
        fprintf(stderr, "[错误] 无效的重量: %.2f\n", weight);
        return 0;
    }
    return 1;
}

int validateVolume(double volume)
{
    if (volume <= 0||volume>4)
    {
        fprintf(stderr, "[错误] 无效的体积: %.2f\n", volume);
        return 0;
    }
    return 1;
}

int validatePackageType(int packageType)
{
    if (packageType < 0 || packageType > 2)
    {
        fprintf(stderr, "[错误] 无效的包裹类型: %d\n", packageType);
        return 0;
    }
    return 1;
}

/**
 * @brief 校验快递单号是否已存在
 *
 * @param trackingNum 快递单号
 * @return int 存在返回1，否则返回0
 */
int isTrackingNumExist(const char* trackingNum)
{
    ListNode* current = packageList->head->next;
    while (current)
    {
        Package* pkg = (Package*)current->data;
        if (pkg && pkg->trackingNum && strcmp(pkg->trackingNum, trackingNum) == 0)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}


/**
 * @brief 检查货架层容量是否足够
 *
 * @param sl 货架层指针
 * @param volume 包裹体积
 * @return int 容量足够返回1，否则返回0
 */
static int checkCapacity(ShelfLevel* sl, double volume)
{
    if (!sl) return 0;
    return (sl->occupiedVolume + volume <= sl->volumeCapacity);
}

/****************************货架管理函数*******************************/
/**
* @brief 初始化货架结构
*/
void initializeShelves()
{
    FILE* shelfFp = fopen(SHELF_STATUS_FILE, "rb");
    if (shelfFp)
    {
        for (int i = 0; i < MAX_SHELVES; i++)
        {
            for (int j = 0; j < INIT_LEVELS; j++)
            {
                size_t read = fread(&wareHouse[i][j], sizeof(ShelfLevel), 1, shelfFp);
                if (read != 1)
                {
                    fprintf(stderr, "[错误] 读取货架层 %d-%d 状态失败\n", i + 1, j + 1);
                }
            }
        }
        fclose(shelfFp);
        printf("[信息] 货架状态已加载\n");
    }
    else
    {
        // 如果文件不存在，初始化货架状态
        for (int i = 0; i < MAX_SHELVES; i++)
        {
            for (int j = 0; j < INIT_LEVELS; j++)
            {
                wareHouse[i][j].volumeCapacity = LEVEL_CAPACITY;
                wareHouse[i][j].occupiedVolume = 0.0;
                wareHouse[i][j].packageNum = 0;
                printf("初始化货架层 %d-%d: 容量 %.2f, 已占用 %.2f, 包裹数 %d\n",
                    i + 1, j + 1, wareHouse[i][j].volumeCapacity, wareHouse[i][j].occupiedVolume, wareHouse[i][j].packageNum);
            }
        }

        // 将初始化的货架状态写入文件
        saveShelves();
    }
}

void showWarehouse(int currentshelf)
{
    cleardevice();//清屏
    buildWindow();
    text(400, 50, "货架编号:"); text(550, 50, currentshelf);
    text(50, 100, "货架层编号"); text(200, 100, "体积容量"); text(350, 100, "占用体积"); text(500, 100, "体积占用率"); text(650, 100, "包裹数量"); text(800, 100, "爆仓预警");
    for (int levelId = 0; levelId < INIT_LEVELS; levelId++)
    {
        float occupancyRate = 100.0 * wareHouse[currentshelf - 1][levelId].occupiedVolume / wareHouse[currentshelf-1][levelId].volumeCapacity;
        if (occupancyRate >= 80) {
            textRed(50, 150 + 50 * levelId, levelId + 1);
            textRed(200, 150 + 50 * levelId, wareHouse[currentshelf - 1][levelId].volumeCapacity);
            textRed(350, 150 + 50 * levelId, wareHouse[currentshelf - 1][levelId].occupiedVolume);
            textRed(500, 150 + 50 * levelId, occupancyRate);
            textRed(650, 150 + 50 * levelId, wareHouse[currentshelf - 1][levelId].packageNum);
            textRed(800, 150 + 50 * levelId, "货架空间不足");
        }
        else
        {
            text(50, 150 + 50 * levelId, levelId + 1);
            text(200, 150 + 50 * levelId, wareHouse[currentshelf - 1][levelId].volumeCapacity);
            text(350, 150 + 50 * levelId, wareHouse[currentshelf - 1][levelId].occupiedVolume);
            text(500, 150 + 50 * levelId, occupancyRate);
            text(650, 150 + 50 * levelId, wareHouse[currentshelf - 1][levelId].packageNum);
            text(800, 150 + 50 * levelId, "货架空间充足");
        }
    }
}

void saveShelves()
{
    FILE* shelfFp = safeFopen(SHELF_STATUS_FILE, "wb");

    for (int i = 0; i < MAX_SHELVES; i++)
    {
        for (int j = 0; j < INIT_LEVELS; j++)
        {
            size_t written = fwrite(&wareHouse[i][j], sizeof(ShelfLevel), 1, shelfFp);
            if (written != 1)
            {
                fprintf(stderr, "[错误] 记录货架状态失败！\n");
                fclose(shelfFp);
                return;
            }
        }
    }
    fclose(shelfFp);
}

/**
 * @brief 加载现有包裹数据
 */

void loadPackages()
{
    packageList = list_init(25000, 47000, sizeof(Package), PACKAGE_FILE, strlen(PACKAGE_FILE) + 1);
    if (!packageList)
    {
        fprintf(stderr, "[错误] 初始化包裹链表失败\n");
        return;
    }
}

/**
 * @brief 保存包裹数据
 */
void savePackages()
{
    list_save(packageList);
    saveShelves();
}

/**
 * @brief 释放包裹数据
 */
void freePackages()
{
    list_free(packageList);
}

/****************************包裹处理函数*******************************/

/**
 * @brief 处理贵重品
 */
static void handleValuable(Package* pkg, int* bestShelf, int* bestLevel) {
    if (!pkg || !bestShelf || !bestLevel) return;
    const int vipShelf = VIP_SHELF_ID - 1;
    for (int level = 0; level < INIT_LEVELS; ++level) {
        ShelfLevel* sl = &wareHouse[vipShelf][level];
        if (sl && checkCapacity(sl, pkg->volume)) {
            *bestShelf = vipShelf;
            *bestLevel = level;
            return;
        }
    }
}


/**
 * @brief 处理普通包裹（小包裹找第一个能放的，大包裹找最大空间，空间相等则底层优先）
 */
static void handlePackage(Package* pkg, int* bestShelf, int* bestLevel, bool prioritizeSpace)
{
    if (!pkg || !bestShelf || !bestLevel) {
        return;
    }

    // 初始化默认值为无效位置
    *bestShelf = *bestLevel = -1;

    // 检查输入有效性
    if (pkg->volume <= 0) {
        return;
    }

    // 模式1: 优先最小层和货架（快速匹配）
    if (!prioritizeSpace) {
        // 预先计算总循环次数，避免每次循环都计算
        const int totalLevels = INIT_LEVELS;
        const int totalShelves = MAX_SHELVES;
        const int vipShelfIndex = VIP_SHELF_ID - 1;

        // 层优先遍历
        for (int level = 0; level < totalLevels; ++level) {
            for (int shelf = 0; shelf < totalShelves; ++shelf) {
                // 跳过VIP货架
                if (shelf == vipShelfIndex) {
                    continue;
                }

                // 直接引用数组元素，减少指针解引用
                if ((wareHouse[shelf][level].occupiedVolume + pkg->volume) <= wareHouse[shelf][level].volumeCapacity) {
                    *bestShelf = shelf;
                    *bestLevel = level;
                    return; // 快速返回第一个匹配位置
                }
            }
        }
        return; // 未找到合适位置
    }

    // 模式2: 优先最大剩余空间（全局最优）
    // 使用临时变量减少对输出参数的反复写入
    int optimalShelf = -1;
    int optimalLevel = -1;
    double maxAvailable = -1.0;

    // 预先计算常量
    const int vipShelfIndex = VIP_SHELF_ID - 1;

    // 两层循环查找最佳位置
    for (int level = 0; level < INIT_LEVELS; ++level) {
        for (int shelf = 0; shelf < MAX_SHELVES; ++shelf) {
            // 跳过VIP货架
            if (shelf == vipShelfIndex) {
                continue;
            }

            // 直接引用数组元素减少指针操作
            ShelfLevel* sl = &wareHouse[shelf][level];

            // 检查是否有足够容量
            const double neededSpace = pkg->volume;
            const double remainingSpace = sl->volumeCapacity - sl->occupiedVolume;

            if (neededSpace > remainingSpace) {
                continue; // 容量不足，直接跳过
            }

            // 评估当前位置是否更优
            const bool hasMoreSpace = remainingSpace > maxAvailable;
            const bool hasSameSpaceButBetterPosition =
                (remainingSpace == maxAvailable) && (
                    (level < optimalLevel) ||
                    (level == optimalLevel && shelf < optimalShelf)
                    );

            if (hasMoreSpace || hasSameSpaceButBetterPosition || maxAvailable < 0) {
                maxAvailable = remainingSpace;
                optimalShelf = shelf;
                optimalLevel = level;
            }
        }
    }

    // 设置最终结果
    *bestShelf = optimalShelf;
    *bestLevel = optimalLevel;
}


/**
 * @brief 主分配函数
 */
static void findOptimalLayer(Package* pkg, int* bestShelf, int* bestLevel) {
    if (!pkg || !bestShelf || !bestLevel) return;

    *bestShelf = -1;
    *bestLevel = -1;

    if (pkg->volume <= 0) {
        fprintf(stderr, "[错误] 包裹体积非法：%.2f\n", pkg->volume);
        return;
    }

    if (pkg->packageType == 1 || pkg->packageType == 2) {
        handleValuable(pkg, bestShelf, bestLevel);
    }
    else {
        bool isBulky = (pkg->volume > BULKY_VOLUME || pkg->weight > HEAVY_WEIGHT);
        handlePackage(pkg, bestShelf, bestLevel, isBulky);
    }
}

/**
 * @brief 生成包裹取件码
 */
static void generatePickupCode(int shelfId, int levelNum, Package* pkg) {
    if (!pkg) return;

    if (shelfId < 0 || shelfId >= MAX_SHELVES || levelNum < 0 || levelNum >= INIT_LEVELS) {
        snprintf(pkg->pickupCode, sizeof(pkg->pickupCode), "ERR");
        fprintf(stderr, "[错误] 请检查generatePickupCode函数传入参数合法性！\n");
        return;
    }

    ShelfLevel* sl = &wareHouse[shelfId][levelNum];
    if (!sl) {
        snprintf(pkg->pickupCode, sizeof(pkg->pickupCode), "ERR");
        fprintf(stderr, "[错误] 货架层指针为空\n");
        return;
    }

    snprintf(pkg->pickupCode, sizeof(pkg->pickupCode), "%d-%d-%03d", shelfId + 1, levelNum + 1, sl->packageNum);
}

/**
 * @brief 放置包裹并生成取件码
 */
int placePackageOnShelf(Package* pkg) {
    if (!pkg) {
        fprintf(stderr, "[错误] 包裹指针为空\n");
        return 0;
    }

    int bestShelf = -1, bestLevel = -1;
    findOptimalLayer(pkg, &bestShelf, &bestLevel);

    if (bestShelf < 0 || bestShelf >= MAX_SHELVES || bestLevel < 0 || bestLevel >= INIT_LEVELS) {
        fprintf(stderr, "[错误] 找不到合适的货架层，或位置非法 (shelf=%d, level=%d)\n", bestShelf, bestLevel);
        return 0;
    }

    ShelfLevel* sl = &wareHouse[bestShelf][bestLevel];
    if (!sl || !checkCapacity(sl, pkg->volume)) {
        fprintf(stderr, "[错误] 货架层容量不足或访问异常\n");
        return 0;
    }

    sl->occupiedVolume += pkg->volume;
    sl->packageNum += 1;
    generatePickupCode(bestShelf, bestLevel, pkg);

    return 1;
}
/**
 * @brief 输入包裹信息
 *
 * @param trackingNum 快递单号
 * @param packageName 包裹名称
 * @param m 包裹类型
 * @param volume 包裹体积
 * @param weight 包裹重量
 * @param senderAddress 发件人地址
 * @param receiverPhone 收件人电话
 * @return char* 取件码
 */
char* InputPackageInfo(char* trackingNum, char* packageName, PackageType m, double volume, double weight, char* senderAddress, char* receiverPhone)
{
    // 参数校验

    Package* pkg = (Package*)safeMalloc(sizeof(Package), "分配失败");
    memset(pkg, 0, sizeof(Package));

    // 设置包裹信息
    strncpy(pkg->trackingNum, trackingNum, sizeof(pkg->trackingNum) - 1);
    pkg->trackingNum[sizeof(pkg->trackingNum) - 1] = '\0';

    if (isTrackingNumExist(pkg->trackingNum)) {
        messbox("快递单号已存在，请重新输入。");
        free(pkg);
        return NULL;
    }

    pkg->packageState = Pending;
    pkg->isHomeDelivered = false;
    pkg->isHomeSent = false;

    strncpy(pkg->receiverAddress, "默认是吉林大学本驿站", sizeof(pkg->receiverAddress) - 1);
    pkg->receiverAddress[sizeof(pkg->receiverAddress) - 1] = '\0';

    // 初始化时间信息
    pkg->time.pending = getStationTime();
    pkg->time.delivered = 0;
    pkg->time.ordered = 0;
    pkg->time.shipped = 0;
    pkg->time.canceled = 0;
    pkg->time.refused = 0;

    strncpy(pkg->packageName, packageName, sizeof(pkg->packageName) - 1);
    pkg->packageName[sizeof(pkg->packageName) - 1] = '\0';

    pkg->packageType = m;
    pkg->volume = volume;
    pkg->weight = weight;

    strncpy(pkg->senderAddress, senderAddress, sizeof(pkg->senderAddress) - 1);
    pkg->senderAddress[sizeof(pkg->senderAddress) - 1] = '\0';

    strncpy(pkg->receiverPhone, receiverPhone, sizeof(pkg->receiverPhone) - 1);
    pkg->receiverPhone[sizeof(pkg->receiverPhone) - 1] = '\0';

    // 放置包裹并生成取件码
    if (placePackageOnShelf(pkg)) {
        list_add(packageList, pkg);
        savePackages(); // 保存包裹信息

        //添加日志
        Log tempLog = {};
        sprintf_s(tempLog.description, DESCR, "运营员入库包裹 单号%s 收件人电话%s", pkg->trackingNum, pkg->receiverPhone);
        tempLog.createdTime = getStationTime();
        list_add(getLogs(), &tempLog);
        //保存日志
        list_save(getLogs());

        return pkg->pickupCode;
    }
    else {
        messbox("包裹放置失败，请重新输入。");
        free(pkg);
        return NULL;
    }
}


//********************************************送货上门功能************************

/**
 * @brief 遍历包裹，传出送检上门包裹个数
 */
long long  deliverToHomeNumber(long long deliverToHomeTotalNumber) {
    ListNode* current = packageList->head->next;
    while (current) {
        Package* pkg = (Package*)current->data;
        if (pkg->isHomeDelivered && pkg->packageState == Pending) {
            deliverToHomeTotalNumber++;
        }
        current = current->next;
    }
    return deliverToHomeTotalNumber;
}
/**
 * @brief 送件上门包裹单个界面
 */
void  deliverToHomeWindow(int page, long long deliverToHomeTotalNumber, char* search) {//一次显示九个
    cleardevice();//清屏
    buildWindow();
    long long start = (page - 1) * 9 + 1;
    long long end = start + 8;
    if (end > deliverToHomeTotalNumber) {
        end = deliverToHomeTotalNumber;  // 最后一页的结束位置
    }
    ListNode* current = packageList->head->next;
    text(150, 50, "快递单号"); text(250, 50, "取件码"); text(400, 50, "收件人电话"); text(650, 50, "送达地址");
    long long flag = 0;
    while (current) {
        Package* pkg = (Package*)current->data;
        if (pkg->isHomeDelivered && pkg->packageState == Pending) {
            flag++;
            if (flag >= start && flag <= end) {
                text(150, 50 + (flag - start + 1) * 50, pkg->trackingNum);//快递单号
                text(250, 50 + (flag - start + 1) * 50, pkg->pickupCode);//取件码
                text(400, 50 + (flag - start + 1) * 50, pkg->receiverPhone);
                text(650, 50 + (flag - start + 1) * 50, pkg->receiverAddress);//送件地址
            }
        }
        current = current->next;
    }
    return;
}
/**
 * @brief 确认已送达到楼功能
 */
void deliverToHomeMakeTrue(char* trackingNum) {
    ListNode* current = packageList->head->next;
    while (current) {
        Package* pkg = (Package*)current->data;
        if (strcmp(pkg->trackingNum, trackingNum) == 0 && pkg->isHomeDelivered && pkg->packageState == Pending) {
            pkg->packageState = Delivered;
            messbox("确认已送达成功");
            //添加日志
            Log tempLog = {};
            sprintf_s(tempLog.description, DESCR, "运营员上门送件 单号%s 收件人电话%s", pkg->trackingNum, pkg->receiverPhone);
            tempLog.createdTime = getStationTime();
            list_add(getLogs(), &tempLog);
            //保存日志
            list_save(getLogs());
            break;
        }
        current = current->next;
    }
    if (current == NULL) {
        messbox("未找到包裹，快递单号输入错误");
    }
    savePackages();
}

//******************************上门取件功能**************************

/**
 * @brief 遍历包裹，传出上门取件包裹个数
 */
long long  pickUpFromHomeNumber(long long pickUpFromHomeTotalNumber) {
    ListNode* current = packageList->head->next;
    while (current) {
        Package* pkg = (Package*)current->data;
        if (pkg->isHomeSent && pkg->packageState == Ordered) {
            pickUpFromHomeTotalNumber++;
        }
        current = current->next;
    }
    return pickUpFromHomeTotalNumber;
}
/**
 * @brief 上门取件包裹单个界面
 */
void  pickUpFromHomeWindow(int page, long long pickUpFromHomeTotalNumber, char* search) {//一次显示九个
    cleardevice();//清屏
    buildWindow();
    long long start = (page - 1) * 9 + 1;
    long long end = start + 8;
    if (end > pickUpFromHomeTotalNumber) {
        end = pickUpFromHomeTotalNumber;  // 最后一页的结束位置
    }
    ListNode* current = packageList->head->next;
    text(150, 50, "快递单号"); text(400, 50, "寄件人电话"); text(650, 50, "取件地址");
    long long flag = 0;
    while (current) {
        Package* pkg = (Package*)current->data;
        if (pkg->isHomeSent && pkg->packageState == Ordered) {
            flag++;
            if (flag >= start && flag <= end) {
                text(150, 50 + (flag - start + 1) * 50, pkg->trackingNum);//快递单号
                text(400, 50 + (flag - start + 1) * 50, pkg->senderPhone);//取件码
                text(650, 50 + (flag - start + 1) * 50, pkg->dormAddress);//取件地址
            }
        }
        current = current->next;
    }
    return;
}
/**
 * @brief 确认已到楼取件功能
 */
void pickUpFromHomeMakeTrue(char* trackingNum) {
    ListNode* current = packageList->head->next;
    while (current) {
        Package* pkg = (Package*)current->data;
        if (strcmp(pkg->trackingNum, trackingNum) == 0 && pkg->isHomeSent && pkg->packageState == Ordered) {
            pkg->isHomeSent = false;
            messbox("确认已成功取件");
            //添加日志
            Log tempLog = {};
            sprintf_s(tempLog.description, DESCR, "运营员到楼取件 单号%s 收件人电话%s", pkg->trackingNum, pkg->receiverPhone);
            tempLog.createdTime = getStationTime();
            list_add(getLogs(), &tempLog);
            //保存日志
            list_save(getLogs());
            break;
        }
        current = current->next;
    }
    if (current == NULL) {
        messbox("未找到包裹，快递单号输入错误");
    }
    savePackages();
}
//*********************************通知提醒功能********************************
/**
 * @brief 遍历包裹，传出需要提醒包裹个数
 * customHoursDiff是设定的时间差 你可以在调用函数时传入
 */
long long sendNotificationNumber(long long sendNotificationTotalNumber, double customHoursDiff) {
    time_t currentTime = getStationTime();
    ListNode* current = packageList->head->next;
    while (current) {
        Package* pkg = (Package*)current->data;
        double hoursDiff = difftime(currentTime, pkg->time.pending) / 3600;
        if (hoursDiff > customHoursDiff && pkg->packageState == Pending) {
            sendNotificationTotalNumber++;
        }
        current = current->next;
    }
    return sendNotificationTotalNumber;
}

/**
 * @brief 通知提醒包裹单个界面
 */
void sendNotificationWindow(int page, long long sendNotificationTotalNumber, char* search, double customHoursDiff) { // 一次显示九个
    cleardevice(); // 清屏
    buildWindow();
    time_t currentTime = getStationTime();
    ListNode* current = packageList->head->next;
    long long start = (page - 1) * 9 + 1;
    long long end = start + 8;
    if (end > sendNotificationTotalNumber) {
        end = sendNotificationTotalNumber; // 最后一页的结束位置
    }
    text(150, 50, "快递单号"); text(250, 50, "取件码"); text(400, 50, "收件人电话"); text(650, 50, "送达地址");
    long long flag = 0;
    while (current) {
        Package* pkg = (Package*)current->data;
        double hoursDiff = difftime(currentTime, pkg->time.pending) / 3600;
        if (hoursDiff > customHoursDiff && pkg->packageState == Pending) {
            flag++;
            if (flag >= start && flag <= end) {
                text(150, 50 + (flag - start + 1) * 50, pkg->trackingNum); // 快递单号
                text(250, 50 + (flag - start + 1) * 50, pkg->pickupCode); // 取件码
                text(400, 50 + (flag - start + 1) * 50, pkg->receiverPhone); // 收件人电话
                text(650, 50 + (flag - start + 1) * 50, pkg->senderAddress); // 送件地址
            }
        }
        current = current->next;
    }
    return;
}
//*********************************快递点寄件功能********************************
/**
 * @brief 遍历包裹，传出快递点寄件包裹个数
 */
long long countPackagesForPointDelivery(long long totalPackages) {
    ListNode* current = packageList->head->next;
    while (current) {
        Package* pkg = (Package*)current->data;
        // 筛选条件：状态为 Ordered
        if (pkg->packageState == Ordered) {
            totalPackages++;
        }
        current = current->next;
    }
    return totalPackages;
}

/**
 * @brief 快递点寄件包裹单个界面
 */
void displayPointDeliveryPackages(int page, long long totalPackages, char* search) { // 一次显示九个
    cleardevice(); // 清屏
    buildWindow();
    long long start = (page - 1) * 9 + 1;
    long long end = start + 8;
    if (end > totalPackages) {
        end = totalPackages; // 最后一页的结束位置
    }
    ListNode* current = packageList->head->next;
    text(150, 50, "快递单号");
    text(400, 50, "寄件人电话");
    text(650, 50, "下单时间");
    long long flag = 0;
    while (current) {
        Package* pkg = (Package*)current->data;
        // 筛选条件：状态为 Ordered
        if ( pkg->packageState == Ordered) {
            flag++;
            if (flag >= start && flag <= end) {
                text(150, 50 + (flag - start + 1) * 50, pkg->trackingNum); // 快递单号
                text(400, 50 + (flag - start + 1) * 50, pkg->senderPhone); // 寄件人电话
                text(650, 50 + (flag - start + 1) * 50, formatTime( pkg->time.ordered)); // 寄件地址
            }
        }
        current = current->next;
    }
    return;
}

/**
 * @brief 确认快递点寄件包裹已寄出功能
 */
void confirmPointDelivery(char* trackingNum) {
    ListNode* current = packageList->head->next;
    while (current) {
        Package* pkg = (Package*)current->data;
        // 筛选条件：状态为 Ordered
        if (strcmp(pkg->trackingNum, trackingNum) == 0 && pkg->packageState == Ordered) {
            pkg->packageState = Shipped; // 更新状态为已寄出
            messbox("确认已寄出成功");
            // 添加日志
            Log tempLog = {};
            sprintf_s(tempLog.description, DESCR, "运营员快递点寄件 单号%s 寄件人电话%s", pkg->trackingNum, pkg->senderPhone);
            tempLog.createdTime = getStationTime();
            list_add(getLogs(), &tempLog);
            // 保存日志
            list_save(getLogs());
            break;
        }
        current = current->next;
    }
    if (current == NULL) {
        messbox("未找到包裹，快递单号输入错误");
    }
    savePackages();
}
