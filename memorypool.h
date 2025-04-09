#pragma once
#include "common.h"

#define MEMPOOL_ALIGNMENT 8 //64-bit system 

// �ڴ��ṹ��
typedef struct MemoryBlock 
{
    struct MemoryBlock* next;  // ָ����һ���ڴ��
    unsigned int freeNum;      // ��ǰ�ڴ���еĿ��ж�������
    unsigned int firstFree;    // ��һ�����ж��������
    unsigned int num;          // �ڴ���еĶ�������
    char mData[1];             // �ڴ��������ʼλ��
} MemoryBlock;

// �ڴ�ؽṹ��
typedef struct MemoryPool 
{
    MemoryBlock* firstBlock;   // ָ���һ���ڴ��
    unsigned int initSize;     // ��ʼ�ڴ��Ĵ�С
    unsigned int growSize;     // �����ڴ��Ĵ�С
    unsigned int objSize;      // ÿ������Ĵ�С
} MemoryPool;

/**
 * @brief ��ȫ�ش��ļ�
 *
 * @param path �ļ�·��
 * @param mode ��ģʽ
 * @return FILE* �ļ�ָ��
 */
FILE* safeFopen(const char* path, const char* mode);

/**
 * @brief ��ȫ�ط����ڴ�
 *
 * @param size Ҫ������ڴ��С
 * @param context ��������Ϣ�����ڴ�����ʾ
 * @return void* ������ڴ�ָ��
 */
void* safeMalloc(size_t size, const char* context);

/**
 * @brief �����ڴ��
 *
 * @param initsize ��ʼ�ڴ���С
 * @param growsize �����ڴ���С
 * @param size ÿ������Ĵ�С
 * @return MemoryPool* �ڴ��ָ��
 */
MemoryPool* memoryPoolCreate(unsigned int initsize, unsigned int growsize, unsigned int size);

/**
 * @brief ���ڴ���з����ڴ�
 *
 * @param mp �ڴ��ָ��
 * @return void* ������ڴ�ָ��
 */
void* memoryAlloc(MemoryPool* mp);

/**
 * @brief �ͷ��ڴ���е��ڴ�
 *
 * @param mp �ڴ��ָ��
 * @param pfree Ҫ�ͷŵ��ڴ�ָ��
 */
void memoryFree(MemoryPool* mp, void* pfree);

/**
 * @brief �ͷ������ڴ��
 *
 * @param mp �ڴ��ָ��
 */
void freeMemoryPool(MemoryPool* mp);
