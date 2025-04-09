#pragma once
#include "common.h"
#include "memorypool.h"

// 可容纳各种数据类型的通用单向、有哨兵链表结构体
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

// 功能：初始化链表 (含文件预读取)；
// 参数1：元素大小；
// 参数2：文件名；
// 参数3：文件名字节数
// 返回：新链表指针；
List* list_init(unsigned int initSize, unsigned int growSize, unsigned int dataSize, const char* fileName, unsigned int fileNameSize);

// 功能：保存链表 (文件写入)；
// 参数：链表指针；
void list_save(List* list);

// 属性：私有，不建议使用；
// 功能：添加结点子函数 (尾插)；
// 参数1：链表指针；
// 参数2：数据指针 (持久)；
void list_basicAdd(List* list, void* data);

// 功能：添加结点 (尾插)；
// 参数1：链表指针；
// 参数2：数据指针 (任意生存期)；
void list_add(List* list, void* data);

// 功能：清空链表；
// 参数：链表指针；
void list_clear(List* list);

// 功能：释放链表 (释放后链表不可用)；
// 参数：链表指针；
void list_free(List* list);
