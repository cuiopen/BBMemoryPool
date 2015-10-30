// MemoryPool.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "CMemoryPool.h"

/*����ʽ����*/
CMemoryPool* CMemoryPool::mPool;

CMemoryPool::CMemoryPool()
{
	/*��ʼ���ڴ��*/
	InitPool();
}

CMemoryPool::~CMemoryPool()
{
	/*�����ڴ��*/
	destroyPool();
}

void CMemoryPool::InitPool(size_t nSize)
{
	if (QHeaher == NULL)
	{
		QHeaher = new LinkNode(nSize);
		if (QHeaher == NULL) throw std::bad_alloc();
		QTail = QHeaher;
		mListNodeNums = 1;
	}
	if (pMProxy == NULL)
	{
		pMProxy = new CMemoryManager;
		if (pMProxy == NULL)
			throw std::bad_alloc();
	}
}

void* CMemoryPool::getNewMemory(size_t size)
{
	void* result = QTail->_pAlloateInit;
	char* addr = (char*)result;
	///���ڴ�ߵ�ַ����
	addr += size;
	/*���ָ��Խ��*/
	if (addr - QTail->_pMemory >= QTail->_capacity)
	{
		/*Խ��*/
		/*�����ڴ�*/
		_ASSERT(pMProxy != NULL);
		std::cout << "no more space at current node,allocate new node...\n" << std::endl;
		pMProxy->recycleToPool(QTail->_capacity - QTail->_mUsedByte, QTail->_pAlloateInit);
		/*�����½ڵ�*/
		newNode();
		return getNewMemory(size);
	}
	QTail->_pAlloateInit = addr;
	QTail->_mUsedByte = addr - QTail->_pMemory;
	std::cout <<"alloacte "<<size<<"B memory at current linknode...\n"<<std::endl;
	return result;
}

/*export*/
/*���ն���*/
///export �ⲿ�ӿ�
template<class T>
void CMemoryPool::recyleMemory(T* ptr)
{
	/*��������*/
	ptr->~T();
	_ASSERT(pMProxy != NULL);
	pMProxy->recycleToPool(sizeof(T),ptr);
}

/*��ȡ�ڴ�*/
///export �ⲿ�ӿ�
void* CMemoryPool::requireMemoryFromRecycle(size_t size)
{
	_ASSERT(pMProxy != NULL);
	void* result = pMProxy->getMemoryFromRecycledPool(size);
	if (result == NULL)
	{
		std::cout << "need " << size << "B memory from main block\n" << std::endl;
		return getNewMemory(size);
	}
	else
		return result;
}

void CMemoryPool::newNode(size_t nSize)
{
	if (QTail == NULL || pMProxy == NULL)
	{
		std::cerr << "LinkList should be inited.." << std::endl;
		InitPool(nSize);
		return;
	}
	std::cout << "allocate " << nSize << "B memory to new linknode\n" << std::endl;
	LinkNode* pnode = new LinkNode(nSize);
	if (pnode == NULL) throw std::bad_alloc();
	QTail->_next = pnode;
	QTail = pnode;
	pMProxy->setMemoryAddr(QTail->_pMemory);
	mListNodeNums++;
}

void CMemoryPool::destroyPool()
{
	std::cout << "destroying memoryPool....\n" << std::endl;
	if (QHeaher == NULL) return;
	LinkNode* p = QHeaher;
	LinkNode* q = p;
	while (p->_next != NULL)
	{
		p = p->_next;
		delete q;
		q = p;
	}
	delete q;
}

///���Ժ���
void MemoryFactory(int num)
{
	std::vector<Traii*> objList;
	CMemoryPool* myPool = CMemoryPool::getDefaultMemoryPool();
	for (int i = 0; i < 10; i++)
	{
		Traii* myobj = (Traii*)myPool->requireMemoryFromRecycle(sizeof(Traii));
		objList.push_back(myobj);
	}
	while (!objList.empty())
	{
		Traii* objToRecycle = objList.back();
		objList.pop_back();
		myPool->recyleMemory(objToRecycle);
	}
}

///�ڴ���亯���ӿ�
void* MyAlloate(size_t size)
{
	/*�߽���*/
	///����һ���Է����ڴ泬����ֵ
	if (size >= MAX_MEMORY_REQUIRE)
		throw std::invalid_argument("out of memory threshold!");
	/*��ȡ����*/
	CMemoryPool* myPool = CMemoryPool::getDefaultMemoryPool();
	return myPool->requireMemoryFromRecycle(size);
}

///�ڴ���պ����ӿ�
template<typename T>
void MyRecycle(T* ptr)
{
	if (ptr == NULL)
		throw std::invalid_argument("the pointer can not be NULL!");
	/*��ȡ����*/
	CMemoryPool* myPool = CMemoryPool::getDefaultMemoryPool();
	myPool->recyleMemory(ptr);
}

///�����ڴ��

int _tmain(int argc, _TCHAR* argv[])
{
	Traii* myObj = (Traii*)MyAlloate(sizeof(Traii));
	Sleep(1500);
	MyRecycle(myObj);
	system("pause");
	return 0;
}

