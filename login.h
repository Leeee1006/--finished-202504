#pragma once

#include "common.h"
#include "list.h"
#include "user.h"

/**************************** ���ߺ��� *******************************/
int validatePassword(const char* password, int flag);
int validateUserName(const char* userName);
int isChineseChar(const unsigned char* str);
int isChineseString(char* str, int flag);
int validatePhoneNumber(const char* phoneNumber);

/************************** �û������� **************************/
void loadUsers();
void saveUsers();
void freeUsers();
int isPhoneNumberExist(const char* phoneNumber);
int userRegister(const char* name, const char* phoneNumber, const char* password);
User* userLogin(const char* phoneNumber, const char* password);