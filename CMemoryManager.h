/*�ڴ�صĹ�����*/

#ifndef _CMEMORYMANAGER_H_
#define _CMEMORYMANAGER_H_
#endif

#include "CTreeLinkList.h"

#define MAX_LIST_KEY 6
#define MEMORY_UNIT_SIZE 4

class CManagerTree
{
public:
	CManagerTree();
	virtual ~CManagerTree();
	/*���������*/
	TreeNode* getMemoryPtr() { return pManagerTreeRoot; }
protected:
	void xInit();
	bool xTraveral(TreeNode*&,const void(*)(TreeNode*));
	TreeNode* xInsertNode(TreeNode*, const size_t,void*,TreeNode*);
	void* xSearchNode(const size_t,TreeNode*);
	bool xCheckTreeBalance(TreeNode*&,int);	//���avl���Ƿ�ƽ��
	TreeNode* xReconstructTree(TreeNode*&, size_t, int);	//��������
	TreeNode* pManagerTreeRoot = NULL;	//���������ڵ�ָ��
	size_t xDepth;
	TreeNode* xCurrNode = NULL;
private:
	TreeNode* DoubleRoatateTree(TreeNode*&, int);	//��˫��ת
	TreeNode* SingleRotateTree(TreeNode*&, int);	//������ת
	void DestroyedTree(TreeNode*&);	//����ʱ������
};

class CMemoryManager : public CManagerTree
{
public:
	CMemoryManager ();
	~CMemoryManager ();
	void InitMamager(int, const size_t size = MEMORY_UNIT_SIZE);
	void setMemoryAddr(void* pMemory) { this->pMemory = pMemory; }
	void recycleToPool(size_t,void*);
	void* getMemoryFromRecycledPool(size_t);
private:
	void* pMemory;	//��ǰ����ڵ��ڴ�����ʼ��ַ
};