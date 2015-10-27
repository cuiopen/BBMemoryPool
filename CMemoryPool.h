
#ifndef _CMEMORYPOOL_H_
#define _CMEMORYPOOL_H_
#endif

#include "CMemoryManager.h"

class CMemoryPool
{
public:
	~CMemoryPool();
	/*����*/
	static inline CMemoryPool* getDefaultMemoryPool()
	{
		return new CMemoryPool;
	}
	void InitPool(size_t nSize = NODE_MEMORY, size_t itemSize = MEMORY_UNIT_SIZE);
	void newNode(size_t nSize = NODE_MEMORY, size_t itemSize = MEMORY_UNIT_SIZE);
	void destroyPool();
	void* getNewMemory(size_t size);

	template<typename T>
	void recyleMemory(T* ptr);
	void addNewRecycleNode(void);

	void* requireMemoryFromRecycle(size_t);

private:
	CMemoryPool();
	/*�ڴ�����*/
	LinkNode* QHeaher = NULL;
	LinkNode* QTail = NULL;
	int mListNodeNums;
	CMemoryManager* pMProxy = NULL;
	/*��������*/
	RecycleLinkNode* RHeader = NULL;
	RecycleLinkNode* RTail = NULL;
};
