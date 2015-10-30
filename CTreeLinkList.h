/*�ڴ�λ�������Լ������������ṹ*/
#ifndef _CTREELINKLIST_H_
#define _CTREELINKLIST_H_
#endif

#include "stdafx.h"

#define MAX_NODE 1024
#define NODE_MEMORY 640
#define INCREMENT 2
#define MAX_MEMORY_REQUIRE 1000000


/*�ռ�������*/

class TAllocator
{
public:
	TAllocator(){}
	~TAllocator(){}

	static inline void* Allocate(size_t size)
	{
		std::cout << "Allocate " << size << "B memory totally\n" << std::endl;
		return ::operator new(size, ::std::nothrow);
	}

	static inline void deAllocate(void* ptr, size_t size)
	{
		::operator delete(ptr, ::std::nothrow);
		std::cout << "free " << size << "B memory totally\n" << std::endl;
	}

private:

};

struct TreeMemListNode
{
	void* _pMemory;		//�ڴ��ָ��
	TreeMemListNode* _pNext = NULL;
	/*����*/
	/*��ֹ�ڴ�й¶*/
	~TreeMemListNode()
	{
	}
};

/*avl Tree*/
struct TreeNode
{
	size_t _capacity;
	TreeMemListNode* RHeader = NULL;	//��������ͷָ��
	TreeMemListNode* RTail = NULL;	//βָ��
	size_t listNum = 0;

	/*���ݽڵ�ָ��*/
	TreeNode* _pThr = NULL;

	/*��ǰ���߶�*/
	int _height;

	/*children*/
	TreeNode* _LChild = NULL;
	TreeNode* _RChild = NULL;

	/*����*/
	~TreeNode()
	{
		if (RHeader != NULL)
		{
			TreeMemListNode* pcurr = RHeader;
			TreeMemListNode* ppre;
			while (pcurr != NULL)
			{
				ppre = pcurr;
				pcurr = pcurr->_pNext;
				delete ppre;
			}
		}
	}
};

/*linklist*/
struct LinkNode
{
	void* _pMemory;
	size_t _mUsedByte;
	LinkNode* _next = NULL;
	size_t _capacity;
	size_t _itemSize;
	void* _pAlloateInit = NULL;

	LinkNode(size_t size)
	{
		if (size > MAX_NODE)
		{
			throw std::invalid_argument("size is too large,no more memory");
		}
		/*Allocate*/
		_pMemory = TAllocator::Allocate(size);
		if (_pMemory == NULL) throw std::bad_alloc();
		_mUsedByte = 0;
		_capacity = size;
		_pAlloateInit = _pMemory;
	}

	~LinkNode()
	{
		TAllocator::deAllocate(_pMemory, _capacity);
	}
};
