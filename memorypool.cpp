#include "memorypool.h"

// ��ȫ�ļ�����
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

// ��ȫ�ڴ����
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

// �����ڴ��
MemoryPool* memoryPoolCreate(unsigned int initsize, unsigned int growsize, unsigned int objsize)
{

    MemoryPool* mp = (MemoryPool*)safeMalloc(sizeof(MemoryPool), "MemoryPool Creation");

    mp->firstBlock = NULL;
    mp->initSize = initsize;
    mp->growSize = growsize;
    if (objsize < sizeof(unsigned int))//��ÿ������Ĵ�С�����ܴ洢һ��ָ�루���ڿ��������������
    {
        objsize = sizeof(unsigned int);
    }
    mp->objSize = (objsize + (MEMPOOL_ALIGNMENT - 1)) & ~(MEMPOOL_ALIGNMENT - 1);//�� size �����ڴ���룬ȷ������Ķ����С objSize �ǰ��� MEMPOOL_ALIGNMENT �ı��������

    return mp;
}

// �ڴ����
void* memoryAlloc(MemoryPool* mp)
{
    if (!mp) {
        return NULL;
    }

    // ���ҵ�һ���п��пռ���ڴ�� ��·��
    MemoryBlock* currentBlock = mp->firstBlock;
    while (currentBlock && currentBlock->freeNum == 0) {
        currentBlock = currentBlock->next;
    }

    // ���û���ҵ��п��пռ���ڴ�飬����һ���¿�
    if (!currentBlock) {
        unsigned int blockSize = (mp->firstBlock == NULL) ? mp->initSize : mp->growSize;

        // �����µ��ڴ��
        currentBlock = (MemoryBlock*)safeMalloc(sizeof(MemoryBlock) + blockSize * mp->objSize, "MemoryBlock Allocation");

        // ��ʼ�����ڴ��
        currentBlock->num = blockSize;
        currentBlock->freeNum = blockSize - 1; // ���˵�һ�������⣬���������ǿ��е� ��Ϊ��Ȼ��һ�������Ǽ������صĶ���
        currentBlock->firstFree = 1; // ����0�Ǽ������صĶ��� 

        // ͷ�巨�����¿��������ͷ�� ��Ϊ�������Ǵ�����ͷ�������ڴ�飬�������ͷ�������ϸ�����
        currentBlock->next = mp->firstBlock;
        mp->firstBlock = currentBlock;

        // ��ʼ�����С����������ܽ������� ��ʵ��һ������ ����������
        char* data = currentBlock->mData;
        for (unsigned int i = 1; i < blockSize; ++i) {
            *(uintptr_t*)data = i; // �������洢�����ж�����
            data += mp->objSize;
        }

        // ���ص�һ������
        return (void*)currentBlock->mData;
    }

    // �������ڴ���������ڴ�
    char* pfree = currentBlock->mData + currentBlock->firstFree * mp->objSize;
    currentBlock->firstFree = (unsigned int)(*(uintptr_t*)pfree); // ���¿�������ͷ
    currentBlock->freeNum--;

    return (void*)pfree;
}



// �ͷ��ڴ�  
void memoryFree(MemoryPool* mp, void* pfree)
{
    // �����������Ƿ���Ч  
    if (!mp || !pfree)
    {
        printf("Invalid parameters for memoryFree.\n");
        return;
    }

    // ��Ҫ�ͷŵ�ָ��ת��Ϊ�ַ�ָ�룬�������  
    char* freePtr = (char*)pfree;

    // �����ڴ���е������ڴ��  
    MemoryBlock* currentBlock = mp->firstBlock;
    while (currentBlock)
    {
        // ���㵱ǰ�ڴ�����ʼ��ַ�ͽ�����ַ  
        char* blockStart = currentBlock->mData;
        char* blockEnd = blockStart + currentBlock->num * mp->objSize;

        // ���Ҫ�ͷŵ�ָ���Ƿ����ڵ�ǰ�ڴ��  
        if (freePtr >= blockStart && freePtr < blockEnd)
        {
            // ����ָ�����ڴ���е�ƫ����  
            size_t offset = freePtr - blockStart;

            // ȷ��ƫ�����Ƕ����С��������������˵��ָ�벻�Ϸ�  
            if (offset % mp->objSize != 0)
            {
                return; // ���ָ�벻���룬ֱ�ӷ���  
            }

            // ����ƫ�������㱻�ͷŶ��������
            unsigned int objIndex = (unsigned int)(offset / mp->objSize);

            // ���������¼����������  
            *(uintptr_t*)freePtr = (uintptr_t)(currentBlock->firstFree);  // ����ǰ��������ͷ�������洢�����ͷŶ�����
            currentBlock->firstFree = objIndex; // ���¿�������ͷΪ��ǰ���������  
            currentBlock->freeNum++;

            return;
        }

        // ���������һ���ڴ��  
        currentBlock = currentBlock->next;
    }
}



// �ͷ������ڴ��
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