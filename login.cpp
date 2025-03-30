#include "login.h"
User* userHead = NULL; // 全局 用户链表头指针

/**************************** 辅助函数不用看了 *******************************/
int validatePassword(const char* password, int flag)
{
    //数字长度限定函数
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

    size_t len = strlen(userName); // 只计算一次长度
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
    if (!str || str[0] == '\0' || str[1] == '\0') return 0; // 避免空指针和越界访问

    unsigned char high = str[0];
    unsigned char low = str[1];

    return (high >= 0xB0 && high <= 0xF7 && low >= 0xA1 && low <= 0xFE);
}

int isChineseString(char* str, int flag)
{
    int i = 0;
    while (str[i] != '\0')
    {
        // 如果当前字符是中文字符，跳过两个字节
        if (isChineseChar((unsigned char*)&str[i]))
        {
            i += 2; // 中文字符由两个字节组成
        }
        else
        {
            return 0; // 如果遇到非中文字符，返回0
        }
    }
    if (i > flag || i == 0)
    {
        return 0;
    }
    return 1; // 如果整个字符串都是中文字符，返回1
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

// 安全内存分配
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

// 安全文件操作
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

/**************************** 工具函数 *******************************/

// 从文件载入所有用户数据 更新用户链表
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

// 保存所有用户数据到文件
void saveUsers() {
    FILE* fp = safeFopen(USER_FILE, "wb");

    User* current = userHead;
    while (current) {
        fwrite(current, sizeof(User), 1, fp);
        current = current->nextUser;
    }
    fclose(fp);
}

// 释放用户链表
void freeUsers() {
    while (userHead) {
        User* temp = userHead;
        userHead = userHead->nextUser;
        free(temp);
    }
}

// 检查手机号是否已经注册过
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

// 生成唯一用户ID 随便写的
long long generateUserId() {
    static int counter = 0;
    return time(NULL) * 1000 + (counter++ % 1000);
}

/**************************** 用户管理功能 *******************************/

// 用户注册函数
// 返回值: 1 - 注册成功 0 - 注册失败
// 参数：name - 用户名 phoneNumber - 手机号 password - 密码
int userRegister(const char* name, const char* phoneNumber, const char* password) {
    if (isPhoneNumberExist(phoneNumber)) {
        return 0; // 手机号已存在，注册失败
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

    saveUsers(); // 保存到文件
    return 1;
}

// 用户登录函数
// 返回值: 登录成功返回目标用户结构体指针，失败返回NULL
// 参数：phoneNumber - 手机号 password - 密码
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
