/*�ڴ�λ�������Լ������������ṹ*/
#ifndef _CTREELINKLIST_H_
#define _CTREELINKLIST_H_
#endif

#include "stdafx.h"

#define MAX_NODE 1024
#define NODE_MEMORY 640
#define MAX_ITEM_SIZE 16


/*�ռ�������*/

class TAllocator
{
public:
	TAllocator(){}
	~TAllocator(){}

	static inline void* Allocate(size_t size)
	{
		return ::operator new(size, ::std::nothrow);
	}

	static inline void deAllocate(void* ptr, size_t size)
	{
		::operator delete(ptr, ::std::nothrow);
	}

private:

};

/*avl Tree*/
struct TreeNode
{
	size_t _capacity;
	TreeMemListNode* RTail = NULL;	//��������ͷָ��
	TreeMemListNode* RHeader = NULL;	//βָ��
	size_t listNum = 0;

	/*���ݽڵ�ָ��*/
	TreeNode* _pThr = NULL;

	/*��ǰ���߶�*/
	int _height;

	/*children*/
	TreeNode* _LChild = NULL;
	TreeNode* _RChild = NULL;
};

struct TreeMemListNode
{
	void* _pMemory;		//�ڴ��ָ��
	TreeMemListNode* _pNext = NULL;
	/*����*/
	/*��ֹ�ڴ�й¶*/
	~TreeMemListNode()
	{
		delete _pMemory;
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
