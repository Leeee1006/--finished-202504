#define _CRT_SECURE_NO_WARNINGS
#include <cassert>
#include "fore.h"
#include "op.h"
#define PHONE 12
#define MAX_MONTH 12
// �·�������2025�����꣩
const int months[MAX_MONTH] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
// ����ָ����Χ�ڵ��������
int rand_range(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

// ����2025���������
time_t Generate_2025_Date(int choice) {
    struct tm tm = { 0 };
    // Initialize time components
    tm.tm_hour = rand_range(0, 23);  // Random hour 0-23
    tm.tm_min = rand_range(0, 59);    // Random minute 0-59
    tm.tm_sec = 0;

    int s = rand_range(0, 1);
    const int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // Days in each month (2024)

    switch (choice) {
    case 0: // ����
        tm.tm_year = 124 + s;
        if (s == 1) { // 2025
            tm.tm_mon = rand_range(0, 3); // 0��3����֮��
            if (tm.tm_mon == 0) {
                tm.tm_mday = rand_range(1, 31); // 1��31��
            }
            else if (tm.tm_mon == 1) {
                tm.tm_mday = rand_range(1, 28); // 2��28�죨2025����ƽ�꣩
            }
            else if (tm.tm_mon == 2) {
                tm.tm_mday = rand_range(1, 31); // 3��31��
            }
            else {
                tm.tm_mday = rand_range(1, 15); // 4��15��
            }
        }
        if (s == 0) { // 2024
            tm.tm_mon = rand_range(0, 11);
            tm.tm_mday = rand_range(1, months[tm.tm_mon]);
        }
        break;

    case 1: // ���ڣ�2025��2��19�գ�
        tm.tm_year = 125;
        tm.tm_mon = 1; // 2��
        tm.tm_mday = rand_range(15, 31);
        break;

    case 2: // ��ͯ�ڣ�6��1�գ����޸�Ϊ��ӽ�������
        tm.tm_year = 124;
        tm.tm_mon = 5; // 6�£�5��ʾ6�£�
        tm.tm_mday = rand_range(1, 3);
        break;

    case 3: // ˫11��11��11�գ����޸�Ϊ��ӽ�������
        tm.tm_year = 124;
        tm.tm_mon = 10; // 11�£�10��ʾ11�£�
        tm.tm_mday = rand_range(1, 15);
        break;

    case 4: // ����ڣ�2024��9��13�գ����޸�Ϊ��ӽ�������
        tm.tm_year = 124;
        tm.tm_mon = 8; // 9�£�8��ʾ9�£�
        tm.tm_mday = rand_range(1, 15);
        break;

    case 5: // ˫12��12��12�գ����޸�Ϊ��ӽ�������
        tm.tm_year = 124;
        tm.tm_mon = 11; // 12�£�11��ʾ12�£�
        tm.tm_mday = rand_range(1, 15);
        break;

    case 6: // ��ѧ����2024��8��29�գ�
        tm.tm_year = 124;
        tm.tm_mon = 7; // 8��
        tm.tm_mday = rand_range(25, 31);
        break;

    default: // Ĭ��
        tm.tm_year = 124 + s;
        if (s == 1) { // 2025
            tm.tm_mon = rand_range(0, 3); // 0��3����֮��
            if (tm.tm_mon == 0) {
                tm.tm_mday = rand_range(1, 31); // 1��31��
            }
            else if (tm.tm_mon == 1) {
                tm.tm_mday = rand_range(1, 28); // 2��28�죨2025����ƽ�꣩
            }
            else if (tm.tm_mon == 2) {
                tm.tm_mday = rand_range(1, 31); // 3��31��
            }
            else {
                tm.tm_mday = rand_range(1, 15); // 4��15��
            }
        }
        if (s == 0) { // 2024
            tm.tm_mon = rand_range(0, 11);
            tm.tm_mday = rand_range(1, months[tm.tm_mon]);
        }
        break;
    }

    // ȷ��ʱ�䲻�������ֵ2025��4��12��
    if (tm.tm_year == 125 && tm.tm_mon == 3 && tm.tm_mday > 12) { // �����2025��4�£�������������12
        tm.tm_mday = 12;
    }

    return mktime(&tm);
}void generate_tracking_number(char* tracking_number)
{
    for (int i = 0; i < 10; i++) {
        // ����0-9֮����������תΪ�ַ� '0' - '9'
        tracking_number[i] = rand_range(0, 9) + '0';
    }
    tracking_number[10] = '\0';  // ����ַ���������
   
}
// ������Ч�ֻ���
void Generate_Phone(char* phone)
{
    snprintf(phone, PHONE, "1%03d%03d%03d%d",
        rand_range(300, 999),  // ��Ч��Ӫ�̺Ŷ�
        rand_range(100, 999),
        rand_range(100, 999),
        rand_range(0, 9));
}
User* g_currentUsers;
// ���ɰ�������
void GenerateNames(Package* pkg, int choice)
{
    if (choice == 0)//����
    {
        const char* names[] = { "���Ӳ�Ʒ", "��װ", "ͼ��", "ʳƷ", "�Ҿ�" };
        strncpy_s(pkg->packageName, names[rand() % 5], NAME);
    }
    if (choice == 1)//����
    {
        const char* names[] = { "���", "���·�", "��Ʒ", "����", "����" };
        strncpy_s(pkg->packageName, names[rand() % 5], NAME);
    }
    if (choice == 2)//��ͯ��
    {
        const char* names[] = { "��ͯ�ľ�", "��ͯ��װ", "��ͯͼ��", "��ͯʳƷ", "��ͯ����" };
        strncpy_s(pkg->packageName, names[rand() % 5], NAME);
    }
    if (choice == 3)//˫11
    {
        const char* names[] = { "���Ӳ�Ʒ", "��װ", "�ֻ�", "����Ʒ", "�Ҿ�" };
        strncpy_s(pkg->packageName, names[rand() % 5], NAME);
    }
    if (choice == 4)//�����
    {
        const char* names[] = { "����", "�±����", "����", "����ʳƷ", "������Ʒ" };
        strncpy_s(pkg->packageName, names[rand() % 5], NAME);
    }
    if (choice == 5)//˫12
    {
        const char* names[] = { "��ִ�����Ʒ", "������װ", "ͼ��", "ʳƷ", "�Ҿ�" };
        strncpy_s(pkg->packageName, names[rand() % 5], NAME);
    }
    if (choice == 6)//��ѧ��
    {
        const char* names[] = { "�ľ�", "���", "�α�", "���Ӳ�Ʒ", "������" };
        strncpy_s(pkg->packageName, names[rand() % 5], NAME);
    }
    pkg->packageName[NAME - 1] = '\0';  // ǿ����ֹ
}
void CreatPackage(Package* pkg, int choice)//����choice���ɰ�������������
{
    //��������
    GenerateNames(pkg, choice);
    //�ļ���ַ/�ռ���ַ
    const char* adress1[] = { "������","�Ϻ���","�����","������","�ӱ�ʡʯ��ׯ��","�ӱ�ʡ��ɽ��","ɽ��ʡ̫ԭ��","���ɹ����������ͺ�����","����ʡ������",
        "����ʡ������","����ʡ������","������ʡ��������","����ʡ�Ͼ���", "����ʡ������", "�㽭ʡ������", "����ʡ�Ϸ���", "����ʡ������", "����ʡ������", "����ʡ�ϲ���",
        "����ʡ��������", "ɽ��ʡ������", "ɽ��ʡ�ൺ��", "����ʡ֣����", "����ʡ������", "����ʡ�人��", "����ʡ��ɳ��", "�㶫ʡ������", "�㶫ʡ������",
        "�㶫ʡ��ɽ��", "����׳��������������", "����׳��������������", "����ʡ������", "����ʡ������", "�Ĵ�ʡ�ɶ���", "����ʡ������", "����ʡ������",
        "����ʡ������", "����������������", "����ʡ������", "����ʡ������", "�ຣʡ������", "���Ļ���������������", "�½�ά�����������³ľ����", "�㶫ʡ�麣��" , "�㶫ʡ��ݸ��" ,
        "�㽭ʡ������" , "����ʡ������" , "����ʡ��ɽ��" , "������ʡ������" };
    //�ռ���ַ/�ļ���ַ
    const char* adress2[] = { "���ִ�ѧ���ѧ��" };
    int panduan = rand() % 10 + 1;
    //����Ȩ��,��ָ���ǴӴ�ѧ�ǳ�������ָ���Ǵӱ�ĵط�����
    if (panduan == 10) 
    {
        strncpy_s(pkg->receiverAddress, adress2[0], ADDRESS);
        pkg->receiverAddress[ADDRESS - 1] = '\0';  // ǿ����ֹ
        strncpy_s(pkg->senderAddress, adress1[rand() % 49], ADDRESS);
        pkg->senderAddress[ADDRESS - 1] = '\0';  // ǿ����ֹ
        pkg->isHomeDelivered = 0;
        pkg->isHomeSent = rand() % 2;
        if (pkg->isHomeSent == 1)//��Ҫ���żļ�
        {
            const char* adress3[] = { "��ѧ��һ��Ԣ","��ѧ�Ƕ���Ԣ","��ѧ������Ԣ"};
            strncpy_s(pkg->dormAddress, adress3[rand() % 3], ADDRESS);
            pkg->dormAddress[ADDRESS - 1] = '\0';  // ǿ����ֹ
        }
    }
    else 
    {
        strncpy_s(pkg->receiverAddress, adress2[0], ADDRESS);
        pkg->receiverAddress[ADDRESS - 1] = '\0';  // ǿ����ֹ
        strncpy_s(pkg->senderAddress, adress1[rand() % 49], ADDRESS);
        pkg->senderAddress[ADDRESS - 1] = '\0';  // ǿ����ֹ
        pkg->isHomeSent = 0;
        pkg->isHomeDelivered = rand() % 2;
        if (pkg->isHomeDelivered == 1)//��Ҫ����ȡ��
        {
            const char* adress4[] = { "��ѧ��һ��Ԣ","��ѧ�Ƕ���Ԣ","��ѧ������Ԣ" };
            strncpy_s(pkg->dormAddress, adress1[rand() % 3], ADDRESS);
            pkg->dormAddress[ADDRESS - 1] = '\0';  // ǿ����ֹ

        }
    }
    // ��������
    pkg->packageType = (PackageType)(rand() % 3);
    pkg->shippingMethod = (ShippingMethod)(rand() % 3);
    pkg->volume = 0.1 + (rand() % 10000) / 100.0;
    pkg->weight = (rand() % 1001) / 10.0; // ��ȷ��0.1kg���������
    pkg->usedCouponNum = rand() % 5;
    pkg->shippingFee = calculateShippingFee(pkg, g_currentUser);
    // ������ϵ��ʽ
 Generate_Phone(pkg->senderPhone);
   strncpy(pkg->receiverPhone, "15139490674", PHONE);
  //  Generate_Phone(pkg->receiverPhone);
        // ����ȡ����
    int shelfid = rand() % 10;
    int levelnum = rand() % 5;
    int third = rand() % 100;
    snprintf(pkg->pickupCode, sizeof(pkg->pickupCode), "%d-%d-%03d", shelfid + 1, levelnum + 1, third);
    // ���ɻ����µ�ʱ��
    time_t base = Generate_2025_Date(choice);
    pkg->time.ordered = base;
    // ����ʱ��������Ψһ��ݵ���
    generate_tracking_number(pkg->trackingNum);
    //snprintf(pkg->trackingNum, sizeof(pkg->trackingNum), digitalTime(base) + 4);
    int prob = rand_range(0, 100);
    if (prob < 55) {        // ���ռ� 55%
        pkg->packageState = Delivered;
        pkg->time.shipped = base + rand_range(1, 3) * 86400;  // 1-3��󷢻�
        pkg->time.delivered = pkg->time.shipped + rand_range(2, 7) * 86400;
    }
    else if (prob < 70) {   // ������ 15%
        pkg->packageState = Shipped;
        pkg->time.shipped = base + rand_range(1, 3) * 86400;
    }
    else if (prob < 80) {   // ��ȡ�� 10%
        pkg->packageState = Canceled;
        pkg->time.canceled = base + rand_range(1, 2) * 86400;
    }
    else if (prob < 85) {   // ���µ� 5%
        pkg->packageState = Ordered;
        if (panduan != 10) { pkg->packageState = Shipped; }//ȷ��������û�зǼ�����û�
        pkg->time.shipped = base + rand_range(1, 3) * 86400;
        pkg->time.pending = pkg->time.shipped + rand_range(1, 5) * 86400;
    }
    else if (prob < 90) {   // ���� 5%
        pkg->packageState = Refused;
        pkg->time.shipped = base + rand_range(1, 3) * 86400;
        pkg->time.refused = pkg->time.shipped + rand_range(1, 2) * 86400;
    }
    else if (prob < 95) {   // ��ȡ 5%
        pkg->packageState = Misdelivered;
        pkg->time.shipped = base + rand_range(1, 3) * 86400;
        pkg->time.delivered = pkg->time.shipped + rand_range(2, 7) * 86400;
    }
    else {                  // �𻵶�ʧ 5%
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
    for (int i = 1; i <= count; i++)//����
    {
        Package pkg;
        CreatPackage(&pkg, 0);
        list_add(getPackages(), &pkg);
    }
    for (int i = 101; i <= 103; i++)//����
    {
        Package pkg;
        CreatPackage(&pkg, 1);
        list_add(getPackages(), &pkg);
    }
    for (int i = 104; i < 105; i++)//��ͯ��
    {
        Package pkg;
        CreatPackage(&pkg, 2);
        list_add(getPackages(), &pkg);
    }
    for (int i = 106; i < 110; i++)//˫11
    {
        Package pkg;
        CreatPackage(&pkg, 3);
        list_add(getPackages(), &pkg);
    }
    for (int i = 111; i < 112; i++)//�����
    {
        Package pkg;
        CreatPackage(&pkg, 4);
        list_add(getPackages(), &pkg);
    }
    for (int i = 113; i < 115; i++)//˫12
    {
        Package pkg;
        CreatPackage(&pkg, 5);
        list_add(getPackages(), &pkg);
    }
    for (int i = 116; i < 120; i++)//��ѧ��
    {
        Package pkg;
        CreatPackage(&pkg, 6);
        list_add(getPackages(), &pkg);
    }
    for (int i = 121; i < 200; i++)//Ϊ�˴յ�20000
    {
        Package pkg;
        CreatPackage(&pkg, 0);
        list_add(getPackages(), &pkg);
    }
    //ָ�������������2025.1.1---2025.1.14
    //���������������2025.2.1---2025.2.14

    list_save(getPackages());
    return 0;
}
