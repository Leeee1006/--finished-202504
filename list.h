#pragma once
#include "common.h"
#include "memorypool.h"

// �����ɸ����������͵�ͨ�õ������ڱ�����ṹ��
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

// ������ṹ��
typedef struct ListNode
{
	void* data;
	struct ListNode* next;
}ListNode;

// ���ܣ���ʼ������ (���ļ�Ԥ��ȡ)��
// ����1��Ԫ�ش�С��
// ����2���ļ�����
// ����3���ļ����ֽ���
// ���أ�������ָ�룻
List* list_init(unsigned int initSize, unsigned int growSize, unsigned int dataSize, const char* fileName, unsigned int fileNameSize);

// ���ܣ��������� (�ļ�д��)��
// ����������ָ�룻
void list_save(List* list);

// ���ԣ�˽�У�������ʹ�ã�
// ���ܣ���ӽ���Ӻ��� (β��)��
// ����1������ָ�룻
// ����2������ָ�� (�־�)��
void list_basicAdd(List* list, void* data);

// ���ܣ���ӽ�� (β��)��
// ����1������ָ�룻
// ����2������ָ�� (����������)��
void list_add(List* list, void* data);

// ���ܣ��������
// ����������ָ�룻
void list_clear(List* list);

// ���ܣ��ͷ����� (�ͷź���������)��
// ����������ָ�룻
void list_free(List* list);
