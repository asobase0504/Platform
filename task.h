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
#include <list>
#include "task_group.h"

//=============================================================================
// �^�X�N�N���X
//=============================================================================
class CTask
{
public:
	CTask(CTaskGroup::EPushMethod inMethod = CTaskGroup::EPushMethod::PUSH_CURRENT, int inPriority = 0);
	virtual ~CTask();

	virtual HRESULT Init() = 0;
	virtual void Uninit();
	virtual void Update() {}
	virtual void Draw() {}

	void Release() { m_isDeleted = true; }

	// Setter
	void SetPrev(CTask* inTask) { m_prev = inTask; }
	void SetNext(CTask* inTask) { m_next = inTask; }

	// Getter
	CTask* GetPrev() { return m_prev; }
	CTask* GetNext() { return m_next; }
	bool IsDeleted() { return m_isDeleted; }

private:
	CTask* m_prev;
	CTask* m_next;

	bool m_isDeleted;
};
#endif
