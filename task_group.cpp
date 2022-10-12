//=============================================================================
//
// �}�l�[�W���[
// Author : Yuda Kaito
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "task_group.h"
#include "task.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTaskGroup::CTaskGroup() :
	m_top(nullptr),
	m_current(nullptr)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTaskGroup::~CTaskGroup()
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CTaskGroup::Init()
{
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CTaskGroup::Uninit()
{
	CTask* current = m_top;

	while (current != nullptr)
	{
		CTask* next = current->GetNext();
		current->Uninit();
		current = next;
	}
}

//=============================================================================
// �X�V
//=============================================================================
void CTaskGroup::Update()
{
	CTask* now = m_top;

	while (now != nullptr)
	{
		CTask* next = now->GetNext();
		now->Update();
		now = next;
	}
	
	DeleteTask();	// �^�X�N���X�g�̍폜
}

//=============================================================================
// �`��
//=============================================================================
void CTaskGroup::Draw()
{
	CTask* now = m_top;

	while (now != nullptr)
	{
		CTask* next = now->GetNext();
		now->Draw();
		now = next;
	}
}

//=============================================================================
// ���X�g�̍Ō�Ƀ^�X�N������
//=============================================================================
void CTaskGroup::SetPushCurrent(CTask * inTask)
{
	if (m_current == nullptr && m_top == nullptr)
	{
		m_top = inTask;
		m_current = inTask;
	}
	else
	{
		CTask* current = m_current;	// �O��̖���
		m_current = inTask;	// �V��������
		m_current->SetPrev(current);	// �V���������̑O��O��̖�����ݒ�
		current->SetNext(m_current);	// �O��̖����̌��ɐV����������ݒ�
	}
}

//=============================================================================
// ���X�g�̍ŏ��Ƀ^�X�N������
//=============================================================================
void CTaskGroup::SetPushTop(CTask * inTask)
{
}

//=============================================================================
// �Q�Ƃ����^�X�N�̎��Ƀ^�X�N������
//=============================================================================
void CTaskGroup::SetNextTask(CTask * inReference, CTask * inTask)
{
}

//=============================================================================
// �Q�Ƃ����^�X�N�̑O�Ƀ^�X�N������
//=============================================================================
void CTaskGroup::SetPrevTask(CTask * inReference, CTask * inTask)
{
}

//=============================================================================
// �^�X�N�̍폜
//=============================================================================
void CTaskGroup::DeleteTask()
{
	CTask* now = m_top;

	while (now != nullptr)
	{
		// ���̃^�X�N��ۑ�
		CTask* next = now->GetNext();
		CTask* prev = now->GetPrev();

		if (!now->IsDeleted())
		{
			now = next;	// ���̃^�X�N�Ɉڂ�
			continue;
		}

		// �O��̏�Ԃ��擾
		bool isNextNullptr = (next == nullptr);
		bool isPrevNullptr = (prev == nullptr);

		if (!isNextNullptr && !isPrevNullptr)
		{
			next->SetPrev(prev);
			prev->SetNext(next);
		}
		else if (!isNextNullptr && isPrevNullptr)
		{
			m_top = prev;
			prev->SetNext(next);
		}
		else if (isNextNullptr && !isPrevNullptr)
		{
			m_current = next;
			next->SetPrev(prev);
		}

		delete now;	// �폜
		now = next;	// ���̃^�X�N�Ɉڂ�
	}
}
