#pragma once
#define USER_FILE "users.dat"
#include "common.h"

// 校验密码是否合法
int validatePassword(const char* password, int flag);

// 校验用户名是否合法
int validateUserName(const char* userName);

// 判断是否为中文字符
int isChineseChar(const unsigned char* str);

// 判断字符串是否为中文字符串
int isChineseString(char* str, int flag);

// 校验手机号是否合法
int validatePhoneNumber(const char* phoneNumber);

// 安全内存分配
void* safeMalloc(size_t size, const char* context);

// 安全文件操作
FILE* safeFopen(const char* path, const char* mode);

// 加载用户数据
void loadUsers();

// 保存用户数据
void saveUsers();

// 释放用户链表
void freeUsers();


// 检查手机号是否已存在
int isPhoneNumberExist(const char* phoneNumber);

// 生成用户ID
long long generateUserId();

// 用户注册
int userRegister(const char* name, const char* phoneNumber, const char* password);

// 用户登录
User* userLogin(const char* phoneNumber, const char* password);