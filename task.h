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

//=============================================================================
// �^�X�N�N���X
//=============================================================================
class CTask
{
public:
	CTask() {}
	virtual ~CTask() {}

	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() {}
	virtual void Draw() {}

	// Getter
	CTask* GetParent() { return m_parent; }
	std::list<CTask*> GetChildrens() { return m_childrens; }

private:

	CTask* m_parent;
	std::list<CTask*> m_childrens;
};

#endif
