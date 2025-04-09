#pragma once
#include "common.h"

#define MEMPOOL_ALIGNMENT 8 //64-bit system 

// 内存块结构体
typedef struct MemoryBlock 
{
    struct MemoryBlock* next;  // 指向下一个内存块
    unsigned int freeNum;      // 当前内存块中的空闲对象数量
    unsigned int firstFree;    // 第一个空闲对象的索引
    unsigned int num;          // 内存块中的对象总数
    char mData[1];             // 内存块数据起始位置
} MemoryBlock;

// 内存池结构体
typedef struct MemoryPool 
{
    MemoryBlock* firstBlock;   // 指向第一个内存块
    unsigned int initSize;     // 初始内存块的大小
    unsigned int growSize;     // 增长内存块的大小
    unsigned int objSize;      // 每个对象的大小
} MemoryPool;

/**
 * @brief 安全地打开文件
 *
 * @param path 文件路径
 * @param mode 打开模式
 * @return FILE* 文件指针
 */
FILE* safeFopen(const char* path, const char* mode);

/**
 * @brief 安全地分配内存
 *
 * @param size 要分配的内存大小
 * @param context 上下文信息，用于错误提示
 * @return void* 分配的内存指针
 */
void* safeMalloc(size_t size, const char* context);

/**
 * @brief 创建内存池
 *
 * @param initsize 初始内存块大小
 * @param growsize 增长内存块大小
 * @param size 每个对象的大小
 * @return MemoryPool* 内存池指针
 */
MemoryPool* memoryPoolCreate(unsigned int initsize, unsigned int growsize, unsigned int size);

/**
 * @brief 从内存池中分配内存
 *
 * @param mp 内存池指针
 * @return void* 分配的内存指针
 */
void* memoryAlloc(MemoryPool* mp);

/**
 * @brief 释放内存池中的内存
 *
 * @param mp 内存池指针
 * @param pfree 要释放的内存指针
 */
void memoryFree(MemoryPool* mp, void* pfree);

/**
 * @brief 释放整个内存池
 *
 * @param mp 内存池指针
 */
void freeMemoryPool(MemoryPool* mp);
