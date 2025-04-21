#include "login.h"

List* userList = NULL; // ȫ���û��б�

/**************************** ���ߺ��� *******************************/
int validatePassword(const char* password, int flag)
{
    // ���ֳ����޶�����
    if (!password || strlen(password) != flag)
    {
        return 0;
    }
    for (int i = 0; i < flag; i++)
    {
        if (!isdigit((unsigned char)password[i]))
        {
            return 0;
        }
    }
    return 1;
}

int validateUserName(const char* userName)
{
    if (!userName || *userName == '\0' || strlen(userName) > 8)
    {
        return 0;
    }

    size_t len = strlen(userName); // ֻ����һ�γ���
    for (size_t i = 0; i < len; i++)
    {
        if (!isalnum((unsigned char)userName[i]))
        {
            return 0;
        }
    }
    return 1;
}

int isChineseChar(const unsigned char* str)
{
    if (!str || str[0] == '\0' || str[1] == '\0')
    {
        return 0; // �����ָ���Խ�����
    }

    unsigned char high = str[0];
    unsigned char low = str[1];

    return (high >= 0xB0 && high <= 0xF7 && low >= 0xA1 && low <= 0xFE);
}

int isChineseString(char* str, int flag)
{
    int i = 0;
    while (str[i] != '\0')
    {
        // �����ǰ�ַ��������ַ������������ֽ�
        if (isChineseChar((unsigned char*)&str[i]))
        {
            i += 2; // �����ַ��������ֽ����
        }
        else
        {
            return 0; // ��������������ַ�������0
        }
    }
    if (i > flag || i == 0)
    {
        return 0;
    }
    return 1; // ��������ַ������������ַ�������1
}

int validatePhoneNumber(const char* phoneNumber)
{
    if (!phoneNumber || strlen(phoneNumber) != 11)
    {
        return 0;
    }
    for (int i = 0; i < 11; i++)
    {
        if (!isdigit((unsigned char)phoneNumber[i]))
        {
            return 0;
        }
    }
    return 1;
}

/************************** �û����� **************************/

// �����û�����
void loadUsers()
{
    userList = list_init(25000, 47000, sizeof(User), USER_FILE, strlen(USER_FILE) + 1);
    if (!userList)
    {
        fprintf(stderr, "[����] ��ʼ���û�����ʧ��\n");
        return;
    }
}

// �����û�����
void saveUsers()
{
    list_save(userList);
}

// �ͷ��û�����
void freeUsers()
{
    list_free(userList);
}

// ����ֻ����Ƿ��Ѿ�ע���
int isPhoneNumberExist(const char* phoneNumber)
{
    ListNode* current = userList->head->next;
    while (current)
    {
        User* user = (User*)current->data;
        if (user && user->phoneNumber && phoneNumber && strcmp(user->phoneNumber, phoneNumber) == 0)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}


// ע���û�
// ����ֵ: 
// ������
int userRegister(const char* name, const char* phoneNumber, const char* password)
{
    if (isPhoneNumberExist(phoneNumber))
    {
        return 0; // �ֻ�����ע��
    }

    User* newUser = (User*)safeMalloc(sizeof(User), "tempnewuser");
    if (!newUser)
    {
        return 0; // �ڴ����ʧ��
    }

    strncpy(newUser->userName, name, sizeof(newUser->userName) - 1);
    newUser->userName[sizeof(newUser->userName) - 1] = '\0';
    strncpy(newUser->phoneNumber, phoneNumber, sizeof(newUser->phoneNumber) - 1);
    newUser->phoneNumber[sizeof(newUser->phoneNumber) - 1] = '\0';
    strncpy(newUser->password, password, sizeof(newUser->password) - 1);
    newUser->password[sizeof(newUser->password) - 1] = '\0';
    newUser->discount = 100;
    newUser->userType = Regular;
    newUser->couponCount = 0;
    newUser->experience = 10;
    strncpy(newUser->identityCode,generateIdentityCode(phoneNumber), ID_CODE);
    list_add(userList, newUser);
    saveUsers();
    return 1;
}
// �û���¼����
// ����ֵ: ��¼�ɹ�����Ŀ���û��ṹ��ָ�룬ʧ�ܷ���NULL
// ������phoneNumber - �ֻ��� password - ����
User* userLogin(const char* phoneNumber, const char* password)
{
    if (!userList || !userList->head->next)
    {
        return NULL; // �û��б�δ��ʼ����Ϊ��
    }

    ListNode* current = userList->head->next;
    while (current)
    {
        User* user = (User*)current->data;
        if (user && user->phoneNumber && user->password && phoneNumber && password &&
            strcmp(user->phoneNumber, phoneNumber) == 0 &&
            strcmp(user->password, password) == 0)
        {
            return user; // ֱ�ӷ����ҵ����û�ָ��
        }
        current = current->next;
    }
    return NULL;
}


