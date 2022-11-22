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
#include <unordered_map>

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
	// ���X�g�\����
	struct SList
	{
		CTask* top;
		CTask* current;
	};

	// �ǉ����@
	enum EPushMethod
	{
		PUSH_CURRENT = 0,
		PUSH_TOP
	};

public:
	CTaskGroup();
	~CTaskGroup();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// Release
	void AllRelease();
	void AbsolutelyRelease();
	void PriorityRelease(const int inPriotity);

	// Setter
	void SetPushCurrent(CTask* inTask, int inPriority = 0);
	void SetPushTop(CTask* inTask, int inPriority = 0);
	void SetNextTask(CTask* inReference, CTask* inTask);
	void SetPrevTask(CTask* inReference, CTask* inTask);

	// Getter
	CTask* GetTop(int priority = 0) { return m_list.at(priority).top; }
	CTask* GetCurrent(int priority = 0) { return m_list.at(priority).current; }

private:
	void DeleteTask();

private:
	std::unordered_map<int,SList> m_list;	// ���X�g�ꗗ
	unsigned int m_createNumber;	// ������
	int m_priorityNumber;			// �`�揇��
};

#endif
