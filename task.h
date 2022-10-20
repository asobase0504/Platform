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
	CTask(CTaskGroup::EPushMethod inMethod = CTaskGroup::EPushMethod::PUSH_CURRENT, int inPriority = 2);
	virtual ~CTask();

	virtual HRESULT Init() = 0;
	virtual void Uninit();
	virtual void Update() {}
	virtual void Draw() {}

	void Release() { m_isDeleted = true; }

	// Setter
	void SetPrev(CTask* inTask) { m_prev = inTask; }
	void SetNext(CTask* inTask) { m_next = inTask; }
	void AttachProtect() { m_isProtect = true; }

	// Getter
	CTask* GetPrev() { return m_prev; }
	CTask* GetNext() { return m_next; }
	bool IsDeleted() { return m_isDeleted; }
	bool IsProtect() { return m_isProtect; }

private:
	CTask* m_prev;		// �O�̃^�X�N
	CTask* m_next;		// ��̃^�X�N

	bool m_isDeleted;	// �j���\��
	bool m_isProtect;	// �S�̔j������ی삷��
};
#endif
