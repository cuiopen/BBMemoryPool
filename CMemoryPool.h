
#ifndef _CMEMORYPOOL_H_
#define _CMEMORYPOOL_H_
#endif

#include "CMemoryManager.h"

/*������*/
class Traii
{
public:
	Traii() {}
	Traii(int val) { _val = val; }
	~Traii()
	{
		std::cout << "object destroyed.." << std::endl;
	}

private:
	int _val;
};


class CMemoryPool
{
public:
	~CMemoryPool();
	/*����*/
	static inline CMemoryPool* getDefaultMemoryPool()
	{
		if (mPool == NULL)
			mPool = new CMemoryPool;
		return mPool;
	}
	void InitPool(size_t nSize = NODE_MEMORY);
	void destroyPool();
	void* getNewMemory(size_t size);

	template<typename T>
	void recyleMemory(T*);
	void* requireMemoryFromRecycle(size_t);

private:
	CMemoryPool();
	static CMemoryPool* mPool;
	/*�ڴ�����*/
	LinkNode* QHeaher = NULL;
	LinkNode* QTail = NULL;
	int mListNodeNums;
	CMemoryManager* pMProxy = NULL;
	void newNode(size_t nSize = NODE_MEMORY);
	/*��Ƕ˽����*/
	/*RAII����*/
	class GCWorker
	{
	public:
		/*�������յ���*/
		~GCWorker()
		{
			if (CMemoryPool::getDefaultMemoryPool() != NULL)
			{
				delete CMemoryPool::mPool;
			}
		}
	};
	/*�������ʱ��������������*/
	static GCWorker mGcWorker;
};
