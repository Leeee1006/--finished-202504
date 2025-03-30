#include "common.h"
#include "op.h"
#include "login.h"
extern Package* packageHead;
extern User* userHead;
void testInputPackageInfo() 
{
    Package* pkg = (Package*)malloc(sizeof(Package));
    if (!pkg) {
        fprintf(stderr, "�ڴ����ʧ��\n");
        return;
    }
    memset(pkg, 0, sizeof(Package));

    printf("�����������Ϣ:\n");

    printf("������ݵ��ţ�");
    scanf_s("%14s", pkg->trackingNum, (unsigned)_countof(pkg->trackingNum));
    if (isTrackingNumExist(pkg->trackingNum, packageHead))
    {
        fprintf(stderr, "��ݵ����Ѵ��ڣ����������롣\n");
        free(pkg);
        return;
    }

    // ������뻺����
    while (getchar() != '\n');

    pkg->packageState = Pending;
    pkg->isHomeDelivered = false;
    pkg->isHomeSent = false;
    strncpy(pkg->receiverAddress, "���ִ�ѧ����վ", sizeof(pkg->receiverAddress) - 1);
    pkg->receiverAddress[sizeof(pkg->receiverAddress) - 1] = '\0';

    pkg->time.pending = time(NULL);
    pkg->time.delivered = 0;
    pkg->time.ordered = 0;
    pkg->time.shipped = 0;
    pkg->time.canceled = 0;
    pkg->time.refused = 0;

    printf("��������: ");
    scanf_s("%19s", pkg->packageName, (unsigned)_countof(pkg->packageName));

    // ������뻺����
    while (getchar() != '\n');

    printf("�������� (0: ��ͨ, 1: ����, 2: ���): ");
    scanf_s("%d", &(pkg->packageType));

    // ������뻺����
    while (getchar() != '\n');

    printf("�������: ");
    scanf_s("%lf", &(pkg->volume));

    // ������뻺����
    while (getchar() != '\n');

    printf("��������: ");
    scanf_s("%lf", &(pkg->weight));

    // ������뻺����
    while (getchar() != '\n');

    printf("�ļ���ַ: ");
    scanf_s("%199s", pkg->senderAddress, (unsigned)_countof(pkg->senderAddress));

    // ������뻺����
    while (getchar() != '\n');

    printf("�ռ����ֻ���: ");
    scanf_s("%11s", pkg->receiverPhone, (unsigned)_countof(pkg->receiverPhone));

    // У������İ�����Ϣ
    if (!validateWeight(pkg->weight) || !validateVolume(pkg->volume) || !validatePackageType(pkg->packageType))
    {
        fprintf(stderr, "������Ϣ��Ч�����������롣\n");
        free(pkg);
        return;
    }

    // ���ð���������ȡ����
    if (placePackageOnShelf(pkg))
    {
        printf("�����ѳɹ����ã�ȡ����: %s\n", pkg->pickupCode);

        pkg->nextPackage = packageHead;
        packageHead = pkg;

        // ���������Ϣ
        savePackages();
    }
    else
    {
        fprintf(stderr, "��������ʧ�ܡ�\n");
        free(pkg);
    }
}

void testLoadPackages()
{
    Package* packages = packageHead;
    if (packages)
    {
        printf("������Ϣ���سɹ���\n");
        Package* current = packages;
        while (current)
        {
            char timeBuffer[64];
            struct tm timeInfo;
            localtime_s(&timeInfo, &current->time.pending);
            strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", &timeInfo);

            printf("��ݵ���: %s, ����: %s, ����: %d, ���: %.2f, ����: %.2f, ȡ����: %s, �ļ����ֻ���: %s, �ļ���ַ: %s, �ռ����ֻ���: %s, �ռ���ַ: %s, �˷�: %.2f, �ļ���ʽ: %d, ʹ���Ż�ȯ����: %d, ����״̬: %d, ȡ����ַ: %s, �Ƿ��ͼ���¥: %d, �Ƿ�ȡ����¥: %d ���ʱ�䣺%s\r\n",
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
        fprintf(stderr, "������Ϣ����ʧ�ܡ�\n");
    }
}

// �����û�ע�Ṧ��
void testUserRegistration()
{
    char userName[NAME], phoneNumber[PHONE], password[PASSWORD];

    printf("�������û���Ϣ:\n");

    printf("�û���: ");
    scanf("%19s", userName);

    printf("�ֻ���: ");
    scanf("%11s", phoneNumber);

    printf("����: ");
    scanf("%10s", password);

    // ע���û�
    if (userRegister(userName, phoneNumber, password))
    {
        printf("�û�ע��ɹ���\n");
    }
    else
    {
        fprintf(stderr, "�û�ע��ʧ�ܡ�\n");
    }
}
// �����û���¼����
void testUserLogin()
{
    char phoneNumber[PHONE];
    char password[PASSWORD];

    printf("�������¼��Ϣ:\n");

    printf("�ֻ���: ");
    scanf("%11s", phoneNumber);

    printf("����: ");
    scanf("%10s", password);

    // �û���¼
    User* loggedInUser = userLogin(phoneNumber, password);
    if (loggedInUser) {
        printf("�û���¼�ɹ���\n");
        printf("���ǣ�%s ���� %d", loggedInUser->userName, loggedInUser->userType);
        free(loggedInUser);
    }
    else {
        fprintf(stderr, "�û���¼ʧ�ܡ�\n");
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

    // ����ʮ���������д����ʱ�ļ�
    clock_t start = clock();
    FILE* fp = fopen(tempFileName, "wb");
    if (!fp) {
        fprintf(stderr, "�޷����ļ�����д��\n");
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
    printf("���ɲ�д��ʮ�����������ʱ��: %.2f ��\n", (double)(end - start) / CLOCKS_PER_SEC);

    // ���ļ���ȡʮ��������γ�����
    start = clock();
    fp = fopen(tempFileName, "rb");
    if (!fp) {
        fprintf(stderr, "�޷����ļ����ж�ȡ\n");
        return;
    }
    for (int i = 0; i < numPackages; i++)
    {
        Package* pkg = (Package*)malloc(sizeof(Package));
        if (!pkg) {
            fprintf(stderr, "�ڴ����ʧ��\n");
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
    printf("���ļ���ȡ���γ���������ʱ��: %.2f ��\n", (double)(end - start) / CLOCKS_PER_SEC);

    // ��������
    start = clock();
    Package* current = head;
    while (current)
    {
        current = current->nextPackage;
    }
    end = clock();
    printf("����ʮ�����������ʱ��: %.2f ��\n", (double)(end - start) / CLOCKS_PER_SEC);

    // �������
    start = clock();
    for (int i = 0; i < 1000; i++)
    {
        Package* pkg = (Package*)malloc(sizeof(Package));
        if (!pkg) {
            fprintf(stderr, "�ڴ����ʧ��\n");
            return;
        }
        memset(pkg, 0, sizeof(Package));
        generateRandomPackage(pkg, numPackages + i);
        pkg->nextPackage = head;
        head = pkg;
    }
    end = clock();
    printf("����һǧ����������ʱ��: %.2f ��\n", (double)(end - start) / CLOCKS_PER_SEC);

    // ɾ������
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
    printf("ɾ��һǧ����������ʱ��: %.2f ��\n", (double)(end - start) / CLOCKS_PER_SEC);

    // �ͷ�����
    start = clock();
    while (head)
    {
        Package* temp = head;
        head = head->nextPackage;
        free(temp);
    }
    end = clock();
    printf("�ͷ���������ʱ��: %.2f ��\n", (double)(end - start) / CLOCKS_PER_SEC);

    // ɾ����ʱ�ļ�
    remove(tempFileName);
}

// ����������
int main()
{
    initializeShelves();
    loadPackages();
    int choice = 0;
    while (1)
    {
        printf("��ѡ����Թ���:\n");
        printf("1. �û�ע��\n");
        printf("2. �û���¼\n");
        printf("3. ���������Ϣ\n");
        printf("4. ��ȡ������Ϣ\n");
        printf("5. ��ȡ��֪ͨ����\n");
        printf("6. ��������\n");
		printf("7. �ͷŰ���\n");
		printf("8. �ͷ��û�\n");
		printf("9. �˳�\n");
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
            sendNotification(1); // �����Զ����Сʱ����ֵ
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
