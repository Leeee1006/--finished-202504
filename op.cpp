#include "op.h"
#include "list.h"

// 定义货架层信息
static ShelfLevel wareHouse[MAX_SHELVES][INIT_LEVELS];
List* packageList = NULL; // 全局包裹链表指针

/**************************** 工具函数 *******************************/
int validateWeight(double weight)
{
    if (weight <= 0)
    {
        fprintf(stderr, "[错误] 无效的重量: %.2f\n", weight);
        return 0;
    }
    return 1;
}

int validateVolume(double volume)
{
    if (volume <= 0)
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
    if (!trackingNum || !packageList || !packageList->head)
    {
        return 0; // 快递单号或包裹列表未初始化或为空
    }

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
                    fprintf(stderr, "[错误] 读取货架层 %d-%d 状态失败\n", i, j);
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
                    i, j, wareHouse[i][j].volumeCapacity, wareHouse[i][j].occupiedVolume, wareHouse[i][j].packageNum);
            }
        }

        // 将初始化的货架状态写入文件
        saveShelves();
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
static void handleValuable(Package* pkg, int* bestShelf, int* bestLevel)
{
    if (!pkg || !bestShelf || !bestLevel) return;

    const short vipShelf = VIP_SHELF_ID - 1;

    for (int j = 0; j < 5; j++)
    {
        if (j >= INIT_LEVELS) break;
        ShelfLevel* sl = &wareHouse[vipShelf][j];
        if (checkCapacity(sl, pkg->volume))
        {
            *bestShelf = vipShelf;
            *bestLevel = j;
            return;
        }
    }
}

/**
 * @brief 处理大件包裹（空间优先策略）
 */
static void handleBulky(Package* pkg, int* bestShelf, int* bestLevel)
{
    if (!pkg || !bestShelf || !bestLevel) return;

    double maxSpace = -1;
    for (int i = 0; i < MAX_SHELVES; i++)
    {
        for (int j = 0; j < INIT_LEVELS; j++)
        {
            ShelfLevel* sl = &wareHouse[i][j];
            if (!checkCapacity(sl, pkg->volume)) continue;

            double available = sl->volumeCapacity - sl->occupiedVolume;
            if (available > maxSpace)
            {
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
static void handleNormal(Package* pkg, int* bestShelf, int* bestLevel)
{
    if (!pkg || !bestShelf || !bestLevel) return;

    double maxSpace = -1;
    for (int i = 0; i < MAX_SHELVES; i++)
    {
        for (int j = 0; j < INIT_LEVELS; j++)
        {
            ShelfLevel* sl = &wareHouse[i][j];
            if (!checkCapacity(sl, pkg->volume)) continue;

            double available = sl->volumeCapacity - sl->occupiedVolume;
            if (available > maxSpace)
            {
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
void findOptimalLayer(Package* pkg, int* bestShelf, int* bestLevel)
{
    if (!pkg || !bestShelf || !bestLevel) return;

    *bestShelf = -1;
    *bestLevel = -1;

    int isValuable = (pkg->packageType == 1);
    int isBulky = (pkg->volume > BULKY_VOLUME || pkg->weight > HEAVY_WEIGHT);

    if (isValuable)
    {
        handleValuable(pkg, bestShelf, bestLevel);
    }
    else if (isBulky)
    {
        handleBulky(pkg, bestShelf, bestLevel);
    }
    else
    {
        handleNormal(pkg, bestShelf, bestLevel);
    }
}

/**
 * @brief 生成包裹取件码
 */
void generatePickupCode(int shelfId, int levelNum, Package* pkg)
{
    if (!pkg || shelfId < 0 || levelNum < 0 || shelfId >= MAX_SHELVES || levelNum >= INIT_LEVELS) return;

    ShelfLevel* sl = &wareHouse[shelfId][levelNum];
    snprintf(pkg->pickupCode, sizeof(pkg->pickupCode), "%d-%d-%d", shelfId + 1, levelNum + 1, sl->packageNum);
}

/**
 * @brief 放置包裹并生成取件码
 */
int placePackageOnShelf(Package* pkg)
{
    if (!pkg) {
        fprintf(stderr, "[错误] 包裹指针为空\n");
        return 0;
    }

    int bestShelf = -1, bestLevel = -1;
    findOptimalLayer(pkg, &bestShelf, &bestLevel);

    if (bestShelf == -1 || bestLevel == -1) {
        fprintf(stderr, "[错误] 找不到合适的货架层\n");
        return 0;
    }

    ShelfLevel* sl = &wareHouse[bestShelf][bestLevel];
    if (!checkCapacity(sl, pkg->volume)) {
        fprintf(stderr, "[错误] 货架层容量不足\n");
        return 0;
    }

    sl->occupiedVolume += pkg->volume;
    sl->packageNum += 1;
    generatePickupCode(bestShelf, bestLevel, pkg);

    return 1;
}


/**************************** 送件和取件功能 *******************************/

/**
 * @brief 送件上门功能
 */
void deliverToHome()
{
    ListNode* current = packageList->head->next;
    while (current)
    {
        Package* pkg = (Package*)current->data;
        if (pkg->isHomeDelivered && pkg->packageState == Pending)
        {
            fprintf(stderr, "快递单号 %s 已送件到楼。\n", pkg->trackingNum);
            pkg->packageState = Delivered;
        }
        current = current->next;
    }
}

/**
 * @brief 快递员上门取件功能
 */
void pickUpFromHome()
{
    ListNode* current = packageList->head->next;
    while (current)
    {
        Package* pkg = (Package*)current->data;
        if (pkg->isHomeSent && pkg->packageState == Pending)
        {
            fprintf(stderr, "快递单号 %s 已到楼取件。\n", pkg->trackingNum);
            pkg->packageState = Shipped;
        }
        current = current->next;
    }
}

/**
 * @brief 寄取件通知提醒功能
 */
void sendNotification(int hoursThreshold)
{
    if (hoursThreshold <= 0) return;
    time_t currentTime = time(NULL);
    ListNode* current = packageList->head->next;
    int hasOverdue = 0;

    while (current)
    {
        Package* pkg = (Package*)current->data;
        double hoursDiff = difftime(currentTime, pkg->time.pending) / 3600;
        if (hoursDiff > hoursThreshold && pkg->packageState == Pending)
        {
            printf("快递单号: %s, 取件码: %s, 取件人电话: %s\n", pkg->trackingNum, pkg->pickupCode, pkg->receiverPhone);
            hasOverdue = 1;
        }
        current = current->next;
    }

    if (!hasOverdue)
    {
        printf("无超过 %d 小时仍未取包裹。\n", hoursThreshold);
    }
}
