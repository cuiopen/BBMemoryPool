
#include "CMemoryManager.h"



CManagerTree::CManagerTree()
{
}

CManagerTree::~CManagerTree()
{
	/*�����ڴ�*/
	std::cout << "destroying our Manager Tree...\n" << std::endl;
	DestroyedTree(pManagerTreeRoot);
}

CMemoryManager::CMemoryManager()
{
}

CMemoryManager ::~CMemoryManager()
{
	std::cout << "invoking the base class deconstructor..." << std::endl;
}

void CMemoryManager::InitMamager(int length, const size_t size)
{
	std::cout << "Manager starting....." << "\n" << std::endl;
}

int calcHeight(TreeNode* tnode)
{
	if (tnode == NULL) return 0;
	return tnode->_height;
}

int maxHeight(int a, int b)
{
	return (a > b) ? a : b;
}

///TODO: avl������ڵ�
TreeNode* CManagerTree::xInsertNode(TreeNode* pre, const size_t element,void* pMemory,TreeNode* pthr)
{
	/*����*/
	/*�����������ڵ�*/
	if (pre == NULL)
	{
		pre = new TreeNode;
		if (pre == NULL) throw std::bad_alloc();
		pre->_capacity = element;
		/*�����*/
		/*��ʼ������*/
		std::cout << "initializing the memoryList on Treenode...\n" << std::endl;
		if (pre->RHeader == NULL)
		{
			TreeMemListNode* mnode = new TreeMemListNode;
			if (mnode == NULL) throw std::bad_alloc();
			pre->RHeader = mnode;
			pre->RTail = pre->RHeader;
			pre->listNum++;
			pre->RTail->_pMemory = pMemory;
			xCurrNode = pre;
		}
		std::cout << "first node for recycled memory has been built\n" << std::endl;
		///����ݹ鵼�¶�ջ���
		pre->_height = maxHeight(calcHeight(pre->_LChild), calcHeight(pre->_RChild));
		return pre;
	}
	if (pre->_capacity == element)
	{
		if (pre->RHeader == NULL)
		{
			std::cerr << "�����ָ���쳣" << std::endl;
			throw std::nullptr_t();
		}
		/*�������ڵ�*/
		TreeMemListNode* mnode = new TreeMemListNode;
		if (mnode == NULL) throw std::bad_alloc();
		_ASSERT(pre->RTail != NULL);
		pre->RTail->_pNext = mnode;
		pre->RTail = mnode;
		pre->RTail->_pMemory = pMemory;
		pre->listNum++;
		std::cout << "new memory node has been inserted\n" << std::endl;
	}
	/*�������ݹ�*/
	if (pre->_capacity > element)
	{
		pre->_RChild = xInsertNode(pre->_RChild, element, pMemory, pre);
		if (!xCheckTreeBalance(pre, 0))
		{
			/*�ع�����*/
			std::cout << "reconstructing the managerTree....\n" << std::endl;
			pre = xReconstructTree(pre, element, 0);
		}
	}
	else
	{
		pre->_LChild = xInsertNode(pre->_LChild, element, pMemory, pre);
		if (!xCheckTreeBalance(pre, 1))
		{
			std::cout << "reconstructing the managerTree....\n" << std::endl;
			pre = xReconstructTree(pre, element, 1);
		}
	}
	/*���¼���߶�*/
	pre->_height = maxHeight(calcHeight(pre->_LChild), calcHeight(pre->_RChild));
	return pre;
	/*avl����ƽ��*/
	/*����ת����ƽ��*/
}

/*������Ƿ�ƽ��*/
///flag:1(����������)
bool CManagerTree::xCheckTreeBalance(TreeNode* &tnode,int flag)
{
	int delta = calcHeight(tnode->_LChild) - calcHeight(tnode->_RChild);
	delta = (flag == 1) ? delta : (-delta);
	if (delta == 2) return false;
	return true;
}

/*�ؽ�����������*/
///flag:1����������
TreeNode* CManagerTree::xReconstructTree(TreeNode* &tnode,size_t key,int flag)
{
	/*��������ƽ��*/
	/*�жϹ���*/
	_ASSERT(tnode->_LChild != NULL && tnode->_RChild != NULL);
	/*����������*/
	if (flag == 1)
	{
		_ASSERT(key != tnode->_LChild->_capacity);
		if (key < tnode->_LChild->_capacity)
		{
			/*LL��*/
			/*����*/
			std::cout << "reconstructing LL...." << std::endl;
			return SingleRotateTree(tnode, 0);
		}
		else
		{
			/*LR��*/
			/*������*/
			std::cout << "reconstructing LR...." << std::endl;
			return DoubleRoatateTree(tnode, 1);
		}
	}
	/*����������*/
	if (flag == 0)
	{
		_ASSERT(key != tnode->_RChild->_capacity);
		if (key < tnode->_RChild->_capacity)
		{
			/*RL��*/
			/*������*/
			std::cout << "reconstructing RL...." << std::endl;
			return DoubleRoatateTree(tnode, 0);
		}
		else
		{
			/*RR��*/
			/*����*/
			std::cout << "reconstructing RR...." << std::endl;
			return SingleRotateTree(tnode, 1);
		}
	}
	else
	{
		throw std::invalid_argument("error flag to reconstruct the tree");
		exit(1);
	}
}

/*����ת*/
///flag:1���� flag:0����
TreeNode* CManagerTree::SingleRotateTree(TreeNode* &tnode, int flag)
{
	/*����*/
	if (flag == 1)
	{
		TreeNode* porigin = tnode->_LChild;
		tnode->_LChild = porigin->_RChild;
		porigin->_RChild = tnode;
		/*������������߶�*/
		std::cout << "recaculate the height of current node...\n" << std::endl;
		tnode->_height = maxHeight(calcHeight(tnode->_LChild), calcHeight(tnode->_RChild));
		porigin->_height = maxHeight(calcHeight(porigin->_LChild),calcHeight(porigin->_RChild));
		return porigin;
	}
	/*����*/
	if (flag == 0)
	{
		TreeNode* porigin = tnode->_RChild;
		tnode->_RChild = porigin->_LChild;
		porigin->_LChild = tnode;
		std::cout << "recaculate the height of current node...\n" << std::endl;
		tnode->_height = maxHeight(calcHeight(tnode->_LChild), calcHeight(tnode->_RChild));
		porigin->_height = maxHeight(calcHeight(porigin->_LChild), calcHeight(porigin->_RChild));
		return porigin;
	}
	else
	{
		throw std::invalid_argument("error flag to reconstruct the tree");
		exit(1);
	}
}

/*˫��ת*/
///flag:1������ flag:0������
TreeNode* CManagerTree::DoubleRoatateTree(TreeNode* &tnode, int flag)
{
	/*������*/
	if (flag == 1)
	{
		/*����*/
		tnode->_LChild = SingleRotateTree(tnode->_LChild, 1);
		/*����*/
		return SingleRotateTree(tnode, 0);
	}
	if (flag == 0)
	{
		/*����*/
		tnode->_RChild = SingleRotateTree(tnode->_RChild, 0);
		/*����*/
		return SingleRotateTree(tnode, 1);
	}
	else
	{
		throw std::invalid_argument("error flag to reconstruct the tree");
		exit(1);
	}
}

//TODO: ������ǰ�����
bool CManagerTree::xTraveral(TreeNode* &pnode,const void(*func)(TreeNode*))
{
	if (pnode == NULL)
	{
		std::cout << "NULL Tree...Constructing...\n" << std::endl;
		return false;
	}
	if (pnode->_LChild == NULL)
	{
		func(pnode);
		if (pnode->_RChild != NULL) xTraveral(pnode->_RChild, func);
		else return true;
	}
	/*�������ݹ�*/
	else xTraveral(pnode->_LChild, func);
	_ASSERT(pnode != NULL);
	func(pnode);
	/*�������ݹ�*/
	if (pnode->_RChild != NULL) xTraveral(pnode->_RChild, func);
	else return true;
}

/*���һ��ճ�*/
///�ӻ��ճ��л�ȡ�ڴ�
void* CManagerTree::xSearchNode(size_t size,TreeNode* tnode)
{
	std::cout << "searching for available memory node....\n" << std::endl;
	/*�������ջ�û�ж�Ӧ�ڴ�ڵ�*/
	if (tnode == NULL)
		return NULL;
	if (size == tnode->_capacity)
	{
		/*�������ȡ�ڴ�ָ��*/
		if (tnode->RTail == NULL)
			/*�޸����ڴ�*/
			return NULL;
		/*ǰ��ָ��*/
		TreeMemListNode* proip = tnode->RHeader;
		while (proip->_pNext != tnode->RTail)
			proip = proip->_pNext;
		void* result = tnode->RTail->_pMemory;
		delete tnode->RTail;
		proip->_pNext = NULL;
		tnode->RTail = proip;
		tnode->listNum--;
		std::cout << "get " << size << "B memory\n" << std::endl;
		return result;
	}
	/*�������ݹ�*/
	if (size > tnode->_capacity)
		return xSearchNode(size, tnode->_RChild);
	/*�������ݹ�*/
	else
		return xSearchNode(size, tnode->_LChild);
}

/*export*/
/*���������ӽڵ�*/
void CMemoryManager::recycleToPool(size_t size,void* ptr)
{
	std::cout << "recycle " <<size<<"B memory\n"<<std::endl;
	pManagerTreeRoot = xInsertNode(pManagerTreeRoot, size, ptr, NULL);
}

/*�ڻ������л�ȡ�ڴ�*/
void* CMemoryManager::getMemoryFromRecycledPool(size_t size)
{
	std::cout << "search " << size << "B memory\n" << std::endl;
	return xSearchNode(size, pManagerTreeRoot);
}

/*������*/
void CManagerTree::DestroyedTree(TreeNode* &tnode)
{
	if (tnode == NULL)
		return;
	/*������*/
	DestroyedTree(tnode->_LChild);
	/*������*/
	DestroyedTree(tnode->_RChild);
	delete tnode;
}
