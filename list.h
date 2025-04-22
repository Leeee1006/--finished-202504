#pragma once
#include "common.h"
#include "memorypool.h"

// ͨ������ṹ��
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

// @brief ��ȡ�ļ�, ��������
// @param initSize �ڴ�س�ʼ��С
// @param growSize �ڴ��������С
// @param dataSize ���ݴ�С
// @param fileName �ļ���
// @param fileNameSize �ļ�����С
// @return ������ָ��
List* list_init(unsigned int initSize, unsigned int growSize, unsigned int dataSize, const char* fileName, unsigned int fileNameSize);

// @brief д���ļ�, ��������
// @param ����ָ��
void list_save(List* list);

// @brief ��������
// @brief ��ӽ�� (ͷ��)
// @param list ����ָ��
// @param data ����ָ�� (�־�������)
void list_basicAdd(List* list, void* data);

// @brief ��ӽ�� (ͷ��)
// @param list ����ָ��
// @param data ����ָ�� (����������)
void list_add(List* list, void* data);

// @brief ɾ�����
// @param list ����ָ��
// @param ref �ο�����
// @param mode ƥ��ģʽ
// @param cmp �ȽϺ���
void list_delete(List* list, const void* ref, int mode, bool cmp(const void* d1, const void* d2, int mode));

// @brief ɾ����� (һ������)
// @param list ����ָ��
// @param condition ��������
void list_delete_ex(List* list, bool condition(const void* d));

// @brief ���ҽ��
// @param list ����ָ��
// @param ref �ο�����
// @param mode ƥ��ģʽ
// @param cmp �ȽϺ���
// @return Ŀ��������
void* list_find(List* list, const void* ref, int mode, bool cmp(const void* d1, const void* d2, int mode));

// @brief ���ҽ�� (һ������)
// @param list ����ָ��
// @param condition ��������
// @return Ŀ��������
void* list_find_ex(List* list, bool condition(const void* d));

// @brief �������
// @param list ����ָ��
void list_clear(List* list);

// @brief �ͷ�����
// @param list ����ָ��
void list_free(List* list);

// @brief ��������
// @brief �������� (�鲢�����㷨)
// @param head ͷָ��
// @param tail βָ��
// @param elementCount �������
// @param cmp �ȽϺ���
// @param ������βָ��
ListNode* list_mergeSort(ListNode* head, ListNode* tail, size_t elementCount, bool cmp(const void* d1, const void* d2));

// @brief ��������
// @param list ����ָ��
// @param cmp �ȽϺ���ָ��
void list_sort(List* list, bool cmp(const void* d1, const void* d2));
