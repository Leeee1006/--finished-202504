#pragma once
#include "common.h"
#include "memorypool.h"

// 通用链表结构体
typedef struct List
{
	struct ListNode* head;
	struct ListNode* tail;
	size_t elementCount;
	size_t dataSize;
	char* fileName;
	MemoryPool* nodePool;
	MemoryPool* dataPool;
}List;

// 链表结点结构体
typedef struct ListNode
{
	void* data;
	struct ListNode* next;
}ListNode;

// @brief 读取文件, 创建链表
// @param initSize 内存池初始大小
// @param growSize 内存池增长大小
// @param dataSize 数据大小
// @param fileName 文件名
// @param fileNameSize 文件名大小
// @return 新链表指针
List* list_init(unsigned int initSize, unsigned int growSize, unsigned int dataSize, const char* fileName, unsigned int fileNameSize);

// @brief 写入文件, 保存链表
// @param 链表指针
void list_save(List* list);

// @brief 基础函数
// @brief 添加结点 (头插)
// @param list 链表指针
// @param data 数据指针 (持久生存期)
void list_basicAdd(List* list, void* data);

// @brief 添加结点 (头插)
// @param list 链表指针
// @param data 数据指针 (任意生存期)
void list_add(List* list, void* data);

// @brief 删除结点
// @param list 链表指针
// @param ref 参考对象
// @param mode 匹配模式
// @param cmp 比较函数
void list_delete(List* list, const void* ref, int mode, bool cmp(const void* d1, const void* d2, int mode));

// @brief 删除结点 (一般条件)
// @param list 链表指针
// @param condition 条件函数
void list_delete_ex(List* list, bool condition(const void* d));

// @brief 查找结点
// @param list 链表指针
// @param ref 参考对象
// @param mode 匹配模式
// @param cmp 比较函数
// @return 目标结点数据
void* list_find(List* list, const void* ref, int mode, bool cmp(const void* d1, const void* d2, int mode));

// @brief 查找结点 (一般条件)
// @param list 链表指针
// @param condition 条件函数
// @return 目标结点数据
void* list_find_ex(List* list, bool condition(const void* d));

// @brief 清空链表
// @param list 链表指针
void list_clear(List* list);

// @brief 释放链表
// @param list 链表指针
void list_free(List* list);

// @brief 基础函数
// @brief 链表排序 (归并排序算法)
// @param head 头指针
// @param tail 尾指针
// @param elementCount 结点数量
// @param cmp 比较函数
// @param 排序后的尾指针
ListNode* list_mergeSort(ListNode* head, ListNode* tail, size_t elementCount, bool cmp(const void* d1, const void* d2));

// @brief 链表排序
// @param list 链表指针
// @param cmp 比较函数指针
void list_sort(List* list, bool cmp(const void* d1, const void* d2));
