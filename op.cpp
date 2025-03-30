#include "op.h"

// 定义货架层信息
static ShelfLevel wareHouse[MAX_SHELVES][INIT_LEVELS];
Package* packageHead = NULL; // 包裹链表头指针

/**
 * @brief 校验重量是否合法
 */
int validateWeight(double weight) {
    if (weight <= 0) {
        fprintf(stderr, "[错误] 无效的重量: %.2f\n", weight);
        return 0;
    }
    return 1;
}

/**
 * @brief 校验体积是否合法
 */
int validateVolume(double volume) {
    if (volume <= 0) {
        fprintf(stderr, "[错误] 无效的体积: %.2f\n", volume);
        return 0;
    }
    return 1;
}

/**
 * @brief 校验包裹类型是否合法
 */
int validatePackageType(int packageType) 
{
    if (packageType < 0 || packageType > 2) {
        fprintf(stderr, "[错误] 无效的包裹类型: %d\n", packageType);
        return 0;
    }
    return 1;
}

/**
 * @brief 校验快递单号是否已存在
 *
 * @param trackingNum 快递单号
 * @param head 包裹链表头指针
 * @return int 存在返回1，否则返回0
 */
int isTrackingNumExist(const char* trackingNum, Package* head) 
{
    if (!trackingNum || !head) return 0;
    Package* current = head;
    while (current) 
    {
        if (strcmp(current->trackingNum, trackingNum) == 0) {
            return 1;
        }
        current = current->nextPackage;
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
static int checkCapacity(ShelfLevel* sl, double volume) {
    if (!sl) return 0;
    return (sl->occupiedVolume + volume <= sl->volumeCapacity);
}


/**
 * @brief 初始化货架结构
 */
void initializeShelves()
{
    for (int i = 0; i < MAX_SHELVES; i++)
    {
        for (int j = 0; j < INIT_LEVELS; j++)
        {
            wareHouse[i][j].volumeCapacity = LEVEL_CAPACITY;
            wareHouse[i][j].occupiedVolume = 0.0;
            wareHouse[i][j].packageNum = 0;
        }
    }
}

/**
 * @brief 加载现有包裹数据并更新货架状态
 */
void loadPackages()
{
    FILE* fp = safeFopen(PACKAGE_FILE, "rb");
    if (!fp) return;

    // 获取文件大小
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);  // 回到文件开头

    // 计算最大节点数
    size_t nodeSize = sizeof(Package);
    size_t maxNodes = fileSize / nodeSize;
    printf("File size: %ld bytes, Max nodes: %zu\n", fileSize, maxNodes);

    // 分配内存池
    static Package* memoryPool = NULL; // 静态变量保存内存池指针
    memoryPool = (Package*)safeMalloc(maxNodes * nodeSize, "loadPackages");
    // 批量读取数据
    size_t readCount = fread(memoryPool, nodeSize, maxNodes, fp);
    fclose(fp);

    if (readCount != maxNodes) {
        printf("Warning: Expected %zu nodes, but read %zu nodes.\n", maxNodes, readCount);
    }

    // 将读取的数据转换为链表
    Package* tail = NULL;
    for (size_t i = 0; i < readCount; i++) {
        Package* newPackage = &memoryPool[i];
        newPackage->nextPackage = NULL;

        short shelfId, levelNum, count;
        if (sscanf(newPackage->pickupCode, "%hd-%hd-%hd", &shelfId, &levelNum, &count) == 3) {
            if (shelfId >= 1 && shelfId <= MAX_SHELVES &&
                levelNum >= 1 && levelNum <= INIT_LEVELS) {
                ShelfLevel* sl = &wareHouse[shelfId - 1][levelNum - 1];
                sl->occupiedVolume += newPackage->volume;
                if (count > sl->packageNum) {
                    sl->packageNum = count;
                }
            }
        }

        if (!packageHead)
            packageHead = tail = newPackage;
        else {
            if (tail) {
                tail->nextPackage = newPackage;
            }
            tail = newPackage;
        }
    }
}


/**
 * @brief 记录包裹信息
 */
void savePackages()
{
    FILE* fp = safeFopen(PACKAGE_FILE, "wb");
    if (!fp) return;

    Package* current = packageHead;
    while (current)
    {
        size_t written = fwrite(current, sizeof(Package), 1, fp);
        if (written != 1) {
            fprintf(stderr, "[错误] 记录包裹失败！\n");
            fclose(fp);
            return;
        }
        current = current->nextPackage;
    }

    fclose(fp);
}

/**
 * @brief 释放包裹链表
 */
void freePackages()
{
    static Package* memoryPool = NULL; // 静态变量保存内存池指针

    if (memoryPool) {
        free(memoryPool);
        memoryPool = NULL;
    }
    else {
        Package* current = packageHead;
        while (current) {
            Package* next = current->nextPackage;
            free(current);
            current = next;
        }
    }
    packageHead = NULL;
}

/* 贪心算法模块 */

/**
 * @brief 处理贵重品
 */
static void handleValuable(Package* pkg, int* bestShelf, int* bestLevel) {
    if (!pkg || !bestShelf || !bestLevel) return;

    const short vipShelf = VIP_SHELF_ID - 1;

    for (int j = 0; j < 5; j++) {
        if (j >= INIT_LEVELS) break;
        ShelfLevel* sl = &wareHouse[vipShelf][j];
        if (checkCapacity(sl, pkg->volume)) {
            *bestShelf = vipShelf;
            *bestLevel = j;
            return;
        }
    }
}

/**
 * @brief 处理大件包裹（空间优先策略）
 */
static void handleBulky(Package* pkg, int* bestShelf, int* bestLevel) {
    if (!pkg || !bestShelf || !bestLevel) return;

    double maxSpace = -1;
    for (int i = 0; i < MAX_SHELVES; i++) {
        for (int j = 0; j < INIT_LEVELS; j++) {
            ShelfLevel* sl = &wareHouse[i][j];
            if (!checkCapacity(sl, pkg->volume)) continue;

            double available = sl->volumeCapacity - sl->occupiedVolume;
            if (available > maxSpace) {
                maxSpace = available;
                *bestShelf = i;
                *bestLevel = j;
            }
        }
    }
}

/**
 * @brief 处理普通包裹（最大空间策略）
 */
static void handleNormal(Package* pkg, int* bestShelf, int* bestLevel) {
    if (!pkg || !bestShelf || !bestLevel) return;

    double maxSpace = -1;
    for (int i = 0; i < MAX_SHELVES; i++) {
        for (int j = 0; j < INIT_LEVELS; j++) {
            ShelfLevel* sl = &wareHouse[i][j];
            if (!checkCapacity(sl, pkg->volume)) continue;

            double available = sl->volumeCapacity - sl->occupiedVolume;
            if (available > maxSpace) {
                maxSpace = available;
                *bestShelf = i;
                *bestLevel = j;
            }
        }
    }
}

/**
 * @brief 主分配函数
 */
void findOptimalLayer(Package* pkg, int* bestShelf, int* bestLevel) {
    if (!pkg || !bestShelf || !bestLevel) return;

    *bestShelf = -1;
    *bestLevel = -1;

    int isValuable = (pkg->packageType == 1);
    int isBulky = (pkg->volume > BULKY_VOLUME || pkg->weight > HEAVY_WEIGHT);

    if (isValuable) {
        handleValuable(pkg, bestShelf, bestLevel);
    }
    else if (isBulky) {
        handleBulky(pkg, bestShelf, bestLevel);
    }
    else {
        handleNormal(pkg, bestShelf, bestLevel);
    }
}

/**
 * @brief 生成包裹取件码
 */
void generatePickupCode(int shelfId, int levelNum, Package* pkg) {
    if (!pkg || shelfId < 0 || levelNum < 0 || shelfId >= MAX_SHELVES || levelNum >= INIT_LEVELS) return;

    ShelfLevel* sl = &wareHouse[shelfId][levelNum];
    snprintf(pkg->pickupCode, sizeof(pkg->pickupCode), "%d-%d-%d", shelfId + 1, levelNum + 1, sl->packageNum);
}

/**
 * @brief 放置包裹并生成取件码
 */
int placePackageOnShelf(Package* pkg) {
    if (!pkg) 
    {
        printf("包裹未传入\n");
        return 0;
    }

    int bestShelf = -1, bestLevel = -1;
    findOptimalLayer(pkg, &bestShelf, &bestLevel);

    if (bestShelf == -1 || bestLevel == -1) return 0;

    ShelfLevel* sl = &wareHouse[bestShelf][bestLevel];
    if (!checkCapacity(sl, pkg->volume)) return 0;

    sl->occupiedVolume += pkg->volume;
    sl->packageNum += 1;
    generatePickupCode(bestShelf, bestLevel, pkg);

    return 1;
}

/**
 * @brief 送件上门功能
 */
void deliverToHome() {
    Package* current = packageHead;
    while (current) {
        if (current->isHomeDelivered && current->packageState == Pending) {
            fprintf(stderr, "快递单号 %s 已送件到楼。\n", current->trackingNum);
            current->packageState = Delivered;
        }
        current = current->nextPackage;
    }
}

/**
 * @brief 快递员上门取件功能
 */
void pickUpFromHome() {
    Package* current = packageHead;
    while (current) {
        if (current->isHomeSent && current->packageState == Pending) {
            fprintf(stderr, "快递单号 %s 已到楼取件。\n", current->trackingNum);
            current->packageState = Shipped;
        }
        current = current->nextPackage;
    }
}

/**
 * @brief 寄取件通知提醒功能
 */
void sendNotification(int hoursThreshold) 
{
    if (hoursThreshold <= 0) return;
    time_t currentTime = time(NULL);
    Package* current = packageHead;
    int hasOverdue = 0;

    while (current) {
        double hoursDiff = difftime(currentTime, current->time.pending) / 3600;
        if (hoursDiff > hoursThreshold) {
            printf("快递单号: %s, 取件码: %s, 取件人电话: %s\n", current->trackingNum, current->pickupCode, current->receiverPhone);
            hasOverdue = 1;
        }
        current = current->nextPackage;
    }

    if (!hasOverdue) {
        printf("无超过 %d 小时仍未取包裹。\n", hoursThreshold);
    }
}


