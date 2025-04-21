#include "list.h"

List* list_init(unsigned int initSize, unsigned int growSize, unsigned int dataSize, const char* fileName, unsigned int fileNameSize)
{
	List* list = (List*)safeMalloc(sizeof(List), "list_init");
	list->tail = list->head = (ListNode*)safeMalloc(sizeof(ListNode), "list_init");
	list->head->data = NULL;
	list->head->next = NULL;
	list->elementCount = 0;
	list->dataSize = dataSize;
	list->fileName = (char*)safeMalloc(fileNameSize, "list_init");
	strcpy_s(list->fileName, fileNameSize, fileName);
	list->nodePool = memoryPoolCreate(initSize, growSize, sizeof(ListNode));
	list->dataPool = memoryPoolCreate(initSize, growSize, dataSize);
	FILE* fp = NULL;
	fopen_s(&fp, fileName, "rb");
	if (fp == NULL)
	{
		return list;
	}
	size_t count = 0;
	fread(&count, sizeof(size_t), 1, fp);
	for (int i = 0; i < count; i++)
	{
		void* data = memoryAlloc(list->dataPool);
		fread(data, dataSize, 1, fp);
		list_basicAdd(list, data);
	}
	fclose(fp);
	return list;
}

void list_save(List* list)
{
	FILE* fp = safeFopen(list->fileName, "wb");
	fwrite(&list->elementCount, sizeof(size_t), 1, fp);
	for (ListNode* cur = list->head; cur != list->tail; cur = cur->next)
	{
		fwrite(cur->next->data, list->dataSize, 1, fp);
	}
	fclose(fp);
}

void list_basicAdd(List* list, void* data)
{
	ListNode* node = (ListNode*)memoryAlloc(list->nodePool);
	node->data = data;
	if (list->head == list->tail)
	{
		list->tail = node;
	}
	node->next = list->head->next;
	list->head->next = node;
	list->elementCount++;
}

void list_add(List* list, void* data)
{
	void* newData = memoryAlloc(list->dataPool);
	memcpy_s(newData, list->dataSize, data, list->dataSize);
	list_basicAdd(list, newData);
}

void list_delete(List* list, const void* ref, unsigned long long mode, bool cmp(const void* d1, const void* d2, int mode))
{
	for (ListNode* node = list->head; node->next != NULL;)
	{
		if (cmp(node->next->data, ref, mode))
		{
			ListNode* tmpNode = node->next;
			node->next = tmpNode->next;
			memoryFree(list->dataPool, tmpNode->data);
			memoryFree(list->nodePool, tmpNode);
			list->elementCount--;
		}
		else
		{
			node = node->next;
		}
	}
}

void list_delete_ex(List* list, bool condition(const void* d))
{
	for (ListNode* node = list->head; node->next != NULL;)
	{
		if (condition(node->next->data))
		{
			ListNode* tmpNode = node->next;
			node->next = tmpNode->next;
			memoryFree(list->dataPool, tmpNode->data);
			memoryFree(list->nodePool, tmpNode);
			list->elementCount--;
		}
		else
		{
			node = node->next;
		}
	}
}

void* list_find(List* list, const void* ref, unsigned long long mode, bool cmp(const void* d1, const void* d2, int mode))
{
	for (ListNode* node = list->head; node->next != NULL; node = node->next)
	{
		if (cmp(node->next->data, ref, mode))
		{
			return node->next->data;
		}
	}
	return NULL;
}

void* list_find_ex(List* list, bool condition(const void* d))
{
	for (ListNode* node = list->head; node->next != NULL; node = node->next)
	{
		if (condition(node->next->data))
		{
			return node->next->data;
		}
	}
	return NULL;
}

void list_clear(List* list)
{
	while (list->head->next != NULL)
	{
		ListNode* temp = list->head->next;
		list->head->next = temp->next;
		if (temp->data != NULL)
		{
			memoryFree(list->dataPool, temp->data);
		}
		memoryFree(list->nodePool, temp);
	}
	list->tail = list->head;
	list->elementCount = 0;
}

void list_free(List* list)
{
	list_clear(list);
	freeMemoryPool(list->nodePool);
	freeMemoryPool(list->dataPool);
	free(list->head);
	free(list->fileName);
	free(list);
	list = NULL;
}
ListNode* list_mergeSort(ListNode* head, ListNode* tail, size_t elementCount, bool cmp(const void* d1, const void* d2))
{
	if (elementCount <= 1)
	{
		return tail;
	}
	ListNode* pivot = head;
	for (int i = 0; i < elementCount / 2; i++)
	{
		pivot = pivot->next;
	}
	pivot = list_mergeSort(head, pivot, elementCount / 2, cmp);
	tail = list_mergeSort(pivot, tail, elementCount - elementCount / 2, cmp);
	ListNode* p1 = head, * p2 = pivot;
	while (p1 != pivot && p2 != tail)
	{
		if (!cmp(p1->next->data, p2->next->data))
		{
			if (p2->next == tail)
			{
				tail = p2;
			}
			ListNode* temp = p2->next;
			p2->next = temp->next;
			temp->next = p1->next;
			p1->next = temp;
		}
		p1 = p1->next;
	}
	return tail;
}

void list_sort(List* list, bool cmp(const void* d1, const void* d2))
{
	list->tail = list_mergeSort(list->head, list->tail, list->elementCount, cmp);
}