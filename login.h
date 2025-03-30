#pragma once
#define USER_FILE "users.dat"
#include "common.h"

// У�������Ƿ�Ϸ�
int validatePassword(const char* password, int flag);

// У���û����Ƿ�Ϸ�
int validateUserName(const char* userName);

// �ж��Ƿ�Ϊ�����ַ�
int isChineseChar(const unsigned char* str);

// �ж��ַ����Ƿ�Ϊ�����ַ���
int isChineseString(char* str, int flag);

// У���ֻ����Ƿ�Ϸ�
int validatePhoneNumber(const char* phoneNumber);

// ��ȫ�ڴ����
void* safeMalloc(size_t size, const char* context);

// ��ȫ�ļ�����
FILE* safeFopen(const char* path, const char* mode);

// �����û�����
void loadUsers();

// �����û�����
void saveUsers();

// �ͷ��û�����
void freeUsers();


// ����ֻ����Ƿ��Ѵ���
int isPhoneNumberExist(const char* phoneNumber);

// �����û�ID
long long generateUserId();

// �û�ע��
int userRegister(const char* name, const char* phoneNumber, const char* password);

// �û���¼
User* userLogin(const char* phoneNumber, const char* password);