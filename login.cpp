#include "login.h"

List* userList = NULL; // 全局用户列表

/**************************** 工具函数 *******************************/
int validatePassword(const char* password, int flag)
{
    // 数字长度限定函数
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
    if (!str || str[0] == '\0' || str[1] == '\0')
    {
        return 0; // 避免空指针和越界访问
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

/************************** 用户管理 **************************/

// 载入用户数据
void loadUsers()
{
    userList = list_init(25000, 47000, sizeof(User), USER_FILE, strlen(USER_FILE) + 1);
    if (!userList)
    {
        fprintf(stderr, "[错误] 初始化用户链表失败\n");
        return;
    }
}

// 保存用户数据
void saveUsers()
{
    list_save(userList);
}

// 释放用户数据
void freeUsers()
{
    list_free(userList);
}

// 检查手机号是否已经注册过
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


// 注册用户
// 返回值: 
// 参数：
int userRegister(const char* name, const char* phoneNumber, const char* password)
{
    if (isPhoneNumberExist(phoneNumber))
    {
        return 0; // 手机号已注册
    }

    User* newUser = (User*)safeMalloc(sizeof(User), "tempnewuser");
    if (!newUser)
    {
        return 0; // 内存分配失败
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
// 用户登录函数
// 返回值: 登录成功返回目标用户结构体指针，失败返回NULL
// 参数：phoneNumber - 手机号 password - 密码
User* userLogin(const char* phoneNumber, const char* password)
{
    if (!userList || !userList->head->next)
    {
        return NULL; // 用户列表未初始化或为空
    }

    ListNode* current = userList->head->next;
    while (current)
    {
        User* user = (User*)current->data;
        if (user && user->phoneNumber && user->password && phoneNumber && password &&
            strcmp(user->phoneNumber, phoneNumber) == 0 &&
            strcmp(user->password, password) == 0)
        {
            return user; // 直接返回找到的用户指针
        }
        current = current->next;
    }
    return NULL;
}


