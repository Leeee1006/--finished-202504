#include "common.h"
#include "op.h"
#include "list.h"
#include "login.h"

extern List* packageList; // ȫ�ְ�������ָ��
extern List* userList; // ȫ���û�����ָ��

void testInputPackageInfo()
{
    Package* pkg = (Package*)safeMalloc(sizeof(Package),"input_temppkg");
    if (!pkg)
    {
        fprintf(stderr, "�ڴ����ʧ��\n");
        return;
    }
    memset(pkg, 0, sizeof(Package));

    printf("�����������Ϣ:\n");

    printf("������ݵ��ţ�");
    scanf("%7s", pkg->trackingNum);
    if (isTrackingNumExist(pkg->trackingNum))
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
    pkg->time.delivered = time(NULL);
    pkg->time.ordered = time(NULL);
    pkg->time.shipped = time(NULL);
    pkg->time.canceled = time(NULL);
    pkg->time.refused = time(NULL);

    printf("��������: ");
    scanf("%19s", pkg->packageName);

    // ������뻺����
    while (getchar() != '\n');

    printf("�������� (0: ��ͨ, 1: ����, 2: ���): ");
    scanf("%d", (int*)&(pkg->packageType));

    // ������뻺����
    while (getchar() != '\n');

    printf("�������: ");
    scanf("%f", &(pkg->volume));

    // ������뻺����
    while (getchar() != '\n');

    printf("��������: ");
    scanf("%f", &(pkg->weight));

    // ������뻺����
    while (getchar() != '\n');

    printf("�ļ���ַ: ");
    scanf("%50s", pkg->senderAddress);

    // ������뻺����
    while (getchar() != '\n');

    printf("�ռ����ֻ���: ");
    scanf("%11s", pkg->receiverPhone);

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

        list_add(packageList, pkg);

        // ���������Ϣ
        savePackages();
        saveShelves();
    }
    else
    {
        fprintf(stderr, "��������ʧ�ܡ�\n");
        free(pkg);
    }
}

void testLoadPackages()
{

    ListNode* current = packageList->head->next; // ����ͷ�ڵ�
    printf("������Ϣ���سɹ���\n");

    while (current)
    {
        if (current->data == NULL) {
            fprintf(stderr, "���ֿ����ݽڵ㣬������\n");
            current = current->next;
            continue;
        }

        Package* pkg = (Package*)current->data;

        // ������ʿ�ָ��
        const char* trackingNum = pkg->trackingNum ? pkg->trackingNum : "(��)";
        const char* packageName = pkg->packageName ? pkg->packageName : "(��)";
        const char* senderPhone = pkg->senderPhone ? pkg->senderPhone : "(��)";
        const char* senderAddress = pkg->senderAddress ? pkg->senderAddress : "(��)";
        const char* receiverPhone = pkg->receiverPhone ? pkg->receiverPhone : "(��)";
        const char* receiverAddress = pkg->receiverAddress ? pkg->receiverAddress : "(��)";
        const char* pickupAddress = pkg->pickupAddress ? pkg->pickupAddress : "(��)";

        // ����ʱ��ת��
        char timeBuffer[64] = "(��ʱ��)";
        if (pkg->time.pending != 0) {
            struct tm timeInfo;
            time_t pendingTime = pkg->time.pending; // ȷ���� time_t
            if (localtime_s(&timeInfo, &pendingTime) == 0) {
                strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", &timeInfo);
            }
        }

        printf("��ݵ���: %s, ����: %s, ����: %d, ���: %.2f, ����: %.2f, ȡ����: %s, "
            "�ļ����ֻ���: %s, �ļ���ַ: %s, �ռ����ֻ���: %s, �ռ���ַ: %s, �˷�: %.2f, "
            "�ļ���ʽ: %d, ʹ���Ż�ȯ����: %d, ����״̬: %d, ȡ����ַ: %s, "
            "�Ƿ��ͼ���¥: %d, �Ƿ�ȡ����¥: %d, ���ʱ�䣺%s\n",
            trackingNum, packageName, pkg->packageType,
            pkg->volume, pkg->weight, pkg->pickupCode,
            senderPhone, senderAddress, receiverPhone,
            receiverAddress, pkg->shippingFee, pkg->shippingMethod,
            pkg->usedCouponNum, pkg->packageState, pickupAddress,
            pkg->isHomeDelivered, pkg->isHomeSent, timeBuffer);

        current = current->next;
    }
}


// �����û�ע�Ṧ��
void testUserRegistration()
{
    char userName[NAME], phoneNumber[PHONE], password[PASSWORD];

    printf("�������û���Ϣ:\n");

    printf("�û���: ");
    scanf("%12s", userName);

    printf("�ֻ���: ");
    scanf("%11s", phoneNumber);

    printf("����: ");
    scanf("%6s", password);

    // ע���û�
    if (userRegister(userName, phoneNumber, password,Regular))
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
    scanf("%6s", password);

    // �û���¼
    User* loggedInUser = userLogin(phoneNumber, password);
    if (loggedInUser)
    {
        printf("�û���¼�ɹ���\n");
        printf("���ǣ�%s ���� %d\n", loggedInUser->userName, loggedInUser->userType);
    }
    else
    {
        fprintf(stderr, "�û���¼ʧ�ܡ�\n");
    }
}

// ����������
int main()
{
    loadPackages();
    initializeShelves();
    loadUsers();
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
        printf("9. �˳�\n");
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
            sendNotification(1); // �����Զ����Сʱ����ֵ
            break;
        case 6:
            // �����������ܿ���������ʵ��
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
