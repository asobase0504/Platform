//=============================================================================
//
// �^�X�N�̏W�܂�
// Author : Yuda Kaito
//
//=============================================================================
#ifndef _TASK_GROUP_H_			// ���̃}�N����`������ĂȂ�������
#define _TASK_GROUP_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include <Windows.h>

//-----------------------------------------------------------------------------
// �O���錾
//-----------------------------------------------------------------------------
class CTask;

//=============================================================================
// �^�X�N�N���X
//=============================================================================
class CTaskGroup
{
public:
	CTaskGroup();
	~CTaskGroup();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// Setter
	void SetPushCurrent(CTask* inTask);
	void SetPushTop(CTask* inTask);
	void SetNextTask(CTask* inReference, CTask* inTask);
	void SetPrevTask(CTask* inReference, CTask* inTask);

	// Getter
	CTask* GetTop() { return m_top; }
	CTask* GetCurrent() { return m_current; }

private:
	void DeleteTask();

private:
	CTask* m_top;
	CTask* m_current;
};

#endif
