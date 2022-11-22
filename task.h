//=============================================================================
//
// �����N���X
// Author : Yuda Kaito
//
//=============================================================================
#ifndef _TASK_H_			// ���̃}�N����`������ĂȂ�������
#define _TASK_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include <Windows.h>
#include "task_group.h"

//=============================================================================
// �^�X�N�N���X
//=============================================================================
class CTask
{
public:
	CTask(unsigned int inPriority = 2, CTaskGroup::EPushMethod inMethod = CTaskGroup::EPushMethod::PUSH_CURRENT);
	virtual ~CTask();

	virtual HRESULT Init() = 0;
	virtual void Uninit();
	virtual void Update() {}
	virtual void Draw() {}

	void Release() { m_isDeleted = true; }

	// ���X�g�\��
	void SetPrev(CTask* inTask) { m_prev = inTask; }
	CTask* GetPrev() { return m_prev; }
	void SetNext(CTask* inTask) { m_next = inTask; }
	CTask* GetNext() { return m_next; }

	// �j���\��
	bool IsDeleted() { return m_isDeleted; }

	// �j����ی삷��
	void AttachProtect() { m_isProtect = true; }
	bool IsProtect() { return m_isProtect; }

private:
	CTask* m_prev;		// �O�̃^�X�N
	CTask* m_next;		// ��̃^�X�N

	// �e�q�֌W
	CTask* m_pearent;	// �e
	std::list<CTask*> m_childrens;	// �q

	bool m_isDeleted;	// �j���\��
	bool m_isProtect;	// �S�̔j������ی삷��
};
#endif
