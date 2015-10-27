/*�ڴ�صĹ�����*/

#ifndef _CMEMORYMANAGER_H_
#define _CMEMORYMANAGER_H_
#endif

#include "stdafx.h"
#include "CTreeLinkList.h"

#define MAX_LIST_KEY 6
#define MEMORY_UNIT_SIZE 4

class CManagerTree
{
public:
	CManagerTree();
	virtual ~CManagerTree();
	/*���������*/
	void CreateTree(const size_t mkey[], int length, const size_t size = MEMORY_UNIT_SIZE);

protected:
	void xInit();
	bool xTraveral(TreeNode* pnode,const void(*func)(TreeNode*));
	bool xInsertNode(TreeNode* pre, const size_t element);
	size_t xDepth;
private:
	TreeNode* pManagerTreeRoot;	//���������ڵ�ָ��
};

class CMemoryManager : CManagerTree
{
public:
	CMemoryManager ();
	~CMemoryManager ();
	size_t CaculateFreeMemory();
	void InitMamager(const size_t mkey[], int length, const size_t size = MEMORY_UNIT_SIZE);
	void TInitMemoryUnitForNode(TreeNode* pnode);
	void setMemoryAddr(void* pMemory) { this->pMemory = pMemory; }
private:
	TreeNode* pTroot;
	void* pMemory;	//��ǰ����ڵ��ڴ�����ʼ��ַ
};