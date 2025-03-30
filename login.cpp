#include "login.h"
User* userHead = NULL; // ȫ�� �û�����ͷָ��

/**************************** �����������ÿ��� *******************************/
int validatePassword(const char* password, int flag)
{
    //���ֳ����޶�����
    if (!password || strlen(password) != flag) return 0;
    for (int i = 0; i < flag; i++)
    {
        if (!isdigit((unsigned char)password[i])) return 0;
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
    if (!str || str[0] == '\0' || str[1] == '\0') return 0; // �����ָ���Խ�����

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
    if (!phoneNumber || strlen(phoneNumber) != 11) return 0;
    for (int i = 0; i < 11; i++)
    {
        if (!isdigit((unsigned char)phoneNumber[i])) return 0;
    }
    return 1;
}

// ��ȫ�ڴ����
void* safeMalloc(size_t size, const char* context)
{
    void* ptr = malloc(size);
    if (!ptr)
    {
        perror(context);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// ��ȫ�ļ�����
FILE* safeFopen(const char* path, const char* mode)
{
    FILE* fp = fopen(path, mode);
    if (!fp)
    {
        perror(path);
        exit(EXIT_FAILURE);
    }
    return fp;
}

/**************************** ���ߺ��� *******************************/

// ���ļ����������û����� �����û�����
void loadUsers() {
    FILE* fp = safeFopen(USER_FILE, "rb");
    if (!fp) return;

    User* prev = NULL;
    User tempUser;
    while (fread(&tempUser, sizeof(User), 1, fp) == 1) {
        User* newUser = (User*)safeMalloc(sizeof(User), "loadUsers");
        memcpy(newUser, &tempUser, sizeof(User));
        newUser->nextUser = NULL;

        if (!userHead) {
            userHead = newUser;
        }
        else {
            if (prev) {
                prev->nextUser = newUser;
            }
        }
        prev = newUser;
    }
    fclose(fp);
}

// ���������û����ݵ��ļ�
void saveUsers() {
    FILE* fp = safeFopen(USER_FILE, "wb");

    User* current = userHead;
    while (current) {
        fwrite(current, sizeof(User), 1, fp);
        current = current->nextUser;
    }
    fclose(fp);
}

// �ͷ��û�����
void freeUsers() {
    while (userHead) {
        User* temp = userHead;
        userHead = userHead->nextUser;
        free(temp);
    }
}

// ����ֻ����Ƿ��Ѿ�ע���
int isPhoneNumberExist(const char* phoneNumber) {
    User* current = userHead;
    while (current) {
        if (strcmp(current->phoneNumber, phoneNumber) == 0) {
            return 1;
        }
        current = current->nextUser;
    }
    return 0;
}

// ����Ψһ�û�ID ���д��
long long generateUserId() {
    static int counter = 0;
    return time(NULL) * 1000 + (counter++ % 1000);
}

/**************************** �û������� *******************************/

// �û�ע�ắ��
// ����ֵ: 1 - ע��ɹ� 0 - ע��ʧ��
// ������name - �û��� phoneNumber - �ֻ��� password - ����
int userRegister(const char* name, const char* phoneNumber, const char* password) {
    if (isPhoneNumberExist(phoneNumber)) {
        return 0; // �ֻ����Ѵ��ڣ�ע��ʧ��
    }

    User* newUser = (User*)safeMalloc(sizeof(User), "userRegister");
    newUser->userId = generateUserId();
    strncpy(newUser->userName, name, sizeof(newUser->userName) - 1);
	newUser->userName[sizeof(newUser->userName) - 1] = '\0';
    strncpy(newUser->phoneNumber, phoneNumber, sizeof(newUser->phoneNumber) - 1);
	newUser->phoneNumber[sizeof(newUser->phoneNumber) - 1] = '\0';
    strncpy(newUser->password, password, sizeof(newUser->password) - 1);
    newUser->password[sizeof(newUser->password) - 1] = '\0';
    strncpy(newUser->identityCode, phoneNumber, sizeof(newUser->identityCode) - 1);
	newUser->identityCode[sizeof(newUser->identityCode) - 1] = '\0';
    newUser->discount = 0;
    newUser->userType = Regular;
    newUser->couponCount = 0;
    newUser->experience = 0;
    newUser->nextUser = userHead;
    userHead = newUser;

    saveUsers(); // ���浽�ļ�
    return 1;
}

// �û���¼����
// ����ֵ: ��¼�ɹ�����Ŀ���û��ṹ��ָ�룬ʧ�ܷ���NULL
// ������phoneNumber - �ֻ��� password - ����
User* userLogin(const char* phoneNumber, const char* password) {
    loadUsers();
    User* current = userHead;
    while (current) {
        if (strcmp(current->phoneNumber, phoneNumber) == 0 &&
            strcmp(current->password, password) == 0) {
            User* found = (User*)safeMalloc(sizeof(User), "userLogin");
            memcpy(found, current, sizeof(User));
            found->nextUser = NULL;
            return found;
        }
        current = current->nextUser;
    }
    return NULL;
}
