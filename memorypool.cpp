#include "memorypool.h"

// 安全文件操作
FILE* safeFopen(const char* path, const char* mode)
{
    FILE* fp = fopen(path, mode);
    if (!fp)
    {
        perror(path);
        exit(EXIT_FAILURE);
    }
    return fp;
}

// 安全内存分配
void* safeMalloc(size_t size, const char* context)
{
    void* ptr = malloc(size);
    if (!ptr)
    {
        perror(context);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// 创建内存池
MemoryPool* memoryPoolCreate(unsigned int initsize, unsigned int growsize, unsigned int size)
{

    MemoryPool* mp = (MemoryPool*)safeMalloc(sizeof(MemoryPool), "MemoryPool Creation");

    mp->firstBlock = NULL;
    mp->initSize = initsize;
    mp->growSize = growsize;
    if (size < sizeof(unsigned int))
    {
        size = sizeof(unsigned int);
    }
    mp->objSize = (size + (MEMPOOL_ALIGNMENT - 1)) & ~(MEMPOOL_ALIGNMENT - 1);

    return mp;
}

// 内存分配
void* memoryAlloc(MemoryPool* mp)
{
    if (!mp)
    {
        return NULL;
    }

    MemoryBlock* currentBlock = mp->firstBlock;
    while (currentBlock && currentBlock->freeNum == 0)
    {
        currentBlock = currentBlock->next;
    }
    // 当前不存在内存块或全部内存块已满，新建第一个内存块
    if (!currentBlock)
    {
        unsigned int blockSize = mp->initSize;
        currentBlock = (MemoryBlock*)safeMalloc(sizeof(MemoryBlock) + blockSize * mp->objSize, "MemoryBlock Allocation");

        currentBlock->num = blockSize * mp->objSize;
        currentBlock->freeNum = blockSize - 1;
        currentBlock->firstFree = 1; // 索引0是即将返回的对象
        currentBlock->next = mp->firstBlock; // 头插
        mp->firstBlock = currentBlock;

        char* data = currentBlock->mData;
        for (unsigned int i = 1; i < blockSize; ++i) // 索引链表
        {
            *(uintptr_t*)data = i;
            data += mp->objSize;
        }

        return (void*)currentBlock->mData;
    }

    char* pfree = currentBlock->mData + currentBlock->firstFree * mp->objSize;
    currentBlock->firstFree = (unsigned int)*((uintptr_t*)pfree);
    currentBlock->freeNum--;
    return (void*)pfree;
}

// 释放内存
void memoryFree(MemoryPool* mp, void* pfree)
{
    if (!mp || !pfree)
    {
        return;
    }

    MemoryBlock* currentBlock = mp->firstBlock;
    while (currentBlock && ((uintptr_t)pfree < (uintptr_t)currentBlock->mData ||
        (uintptr_t)pfree >= (uintptr_t)currentBlock->mData + currentBlock->num))
    {
        currentBlock = currentBlock->next;
    }

    if (!currentBlock)
    {
        return;
    }

    uintptr_t offset = (uintptr_t)pfree - (uintptr_t)currentBlock->mData;
    if (offset % mp->objSize != 0)
    {
        return;
    }

    currentBlock->freeNum++;
    *((uintptr_t*)pfree) = currentBlock->firstFree;
    currentBlock->firstFree = (unsigned int)(offset / mp->objSize);
}

// 释放整个内存池
void freeMemoryPool(MemoryPool* mp)
{
    if (!mp)
    {
        return;
    }
    MemoryBlock* mb = mp->firstBlock;
    while (mb)
    {
        MemoryBlock* nextBlock = mb->next;
        free(mb);
        mb = nextBlock;
    }
    free(mp);
}