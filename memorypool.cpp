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
MemoryPool* memoryPoolCreate(unsigned int initsize, unsigned int growsize, unsigned int objsize)
{

    MemoryPool* mp = (MemoryPool*)safeMalloc(sizeof(MemoryPool), "MemoryPool Creation");

    mp->firstBlock = NULL;
    mp->initSize = initsize;
    mp->growSize = growsize;
    if (objsize < sizeof(unsigned int))//保每个对象的大小至少能存储一个指针（用于空闲链表的索引）
    {
        objsize = sizeof(unsigned int);
    }
    mp->objSize = (objsize + (MEMPOOL_ALIGNMENT - 1)) & ~(MEMPOOL_ALIGNMENT - 1);//对 size 进行内存对齐，确保分配的对象大小 objSize 是按照 MEMPOOL_ALIGNMENT 的倍数对齐的

    return mp;
}

// 内存分配
void* memoryAlloc(MemoryPool* mp)
{
    if (!mp) {
        return NULL;
    }

    // 查找第一个有空闲空间的内存块 短路！
    MemoryBlock* currentBlock = mp->firstBlock;
    while (currentBlock && currentBlock->freeNum == 0) {
        currentBlock = currentBlock->next;
    }

    // 如果没有找到有空闲空间的内存块，创建一个新块
    if (!currentBlock) {
        unsigned int blockSize = (mp->firstBlock == NULL) ? mp->initSize : mp->growSize;

        // 分配新的内存块
        currentBlock = (MemoryBlock*)safeMalloc(sizeof(MemoryBlock) + blockSize * mp->objSize, "MemoryBlock Allocation");

        // 初始化新内存块
        currentBlock->num = blockSize;
        currentBlock->freeNum = blockSize - 1; // 除了第一个对象外，其他对象都是空闲的 因为显然第一个对象是即将返回的对象
        currentBlock->firstFree = 1; // 索引0是即将返回的对象 

        // 头插法，将新块插入链表头部 因为我们总是从链表头部分配内存块，所以这个头插理论上更合理
        currentBlock->next = mp->firstBlock;
        mp->firstBlock = currentBlock;

        // 初始化空闲“链表”，这能叫链表吗？ 其实是一个数组 （索引法）
        char* data = currentBlock->mData;
        for (unsigned int i = 1; i < blockSize; ++i) {
            *(uintptr_t*)data = i; // 将索引存储到空闲对象中
            data += mp->objSize;
        }

        // 返回第一个对象
        return (void*)currentBlock->mData;
    }

    // 从已有内存块分配对象内存
    char* pfree = currentBlock->mData + currentBlock->firstFree * mp->objSize;
    currentBlock->firstFree = (unsigned int)(*(uintptr_t*)pfree); // 更新空闲链表头
    currentBlock->freeNum--;

    return (void*)pfree;
}



// 释放内存  
void memoryFree(MemoryPool* mp, void* pfree)
{
    // 检查输入参数是否有效  
    if (!mp || !pfree)
    {
        printf("Invalid parameters for memoryFree.\n");
        return;
    }

    // 将要释放的指针转换为字符指针，方便计算  
    char* freePtr = (char*)pfree;

    // 遍历内存池中的所有内存块  
    MemoryBlock* currentBlock = mp->firstBlock;
    while (currentBlock)
    {
        // 计算当前内存块的起始地址和结束地址  
        char* blockStart = currentBlock->mData;
        char* blockEnd = blockStart + currentBlock->num * mp->objSize;

        // 检查要释放的指针是否属于当前内存块  
        if (freePtr >= blockStart && freePtr < blockEnd)
        {
            // 计算指针在内存块中的偏移量  
            size_t offset = freePtr - blockStart;

            // 确保偏移量是对象大小的整数倍，否则说明指针不合法  
            if (offset % mp->objSize != 0)
            {
                return; // 如果指针不对齐，直接返回  
            }

            // 根据偏移量计算被释放对象的索引
            unsigned int objIndex = (unsigned int)(offset / mp->objSize);

            // 将对象重新加入空闲链表  
            *(uintptr_t*)freePtr = (uintptr_t)(currentBlock->firstFree);  // 将当前空闲链表头的索引存储到被释放对象中
            currentBlock->firstFree = objIndex; // 更新空闲链表头为当前对象的索引  
            currentBlock->freeNum++;

            return;
        }

        // 继续检查下一个内存块  
        currentBlock = currentBlock->next;
    }
}



// 释放整个内存池
void freeMemoryPool(MemoryPool* mp)
{
    if (!mp)
    {
        return;
    }

    while (mp->firstBlock)
    {
        MemoryBlock* nextBlock = mp->firstBlock->next;
        free(mp->firstBlock);
        mp->firstBlock = nextBlock;
    }

    free(mp);
}