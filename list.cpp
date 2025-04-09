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
	node->next = NULL;
	list->tail = list->tail->next = node;
	list->elementCount++;
}

void list_add(List* list, void* data)
{
	void* newData = memoryAlloc(list->dataPool);
	memcpy_s(newData, list->dataSize, data, list->dataSize);
	list_basicAdd(list, newData);
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