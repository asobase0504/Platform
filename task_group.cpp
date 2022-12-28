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
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTaskGroup::CTaskGroup() :
	m_priorityNumber(0)
{
	m_list.clear();
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
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		if (m_list.count(i) == 0)
		{
			continue;
		}

		CTask* current = m_list.at(i).top;

		while (current != nullptr)
		{
			CTask* next = current->GetNext();
			current->Uninit();
			current->Release();
			current = next;
		}
	}

	DeleteTask();	// �^�X�N���X�g�̍폜
}

//=============================================================================
// �X�V
//=============================================================================
void CTaskGroup::Update()
{
	m_createNumber = 0;
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		if (m_list.count(i) == 0)
		{
			continue;
		}

		CTask* now = m_list.at(i).top;

		while (now != nullptr)
		{
			m_createNumber++;
			CTask* next = now->GetNext();
			if (!now->IsDeleted())
			{
				now->Update();
			}
			now = next;
		}

		DeleteTask();	// �^�X�N���X�g�̍폜
	}
}

//=============================================================================
// �`��
//=============================================================================
void CTaskGroup::Draw()
{
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		if (m_list.count(i) == 0)
		{
			continue;
		}

		// ��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
		CRenderer::GetInstance()->GetDevice()->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

		CTask* now = m_list.at(i).top;	// �`�悷��^�X�N��\��

		while (now != nullptr)
		{
			CTask* next = now->GetNext();	// ���̃^�X�N

			// ���ʗ\�肪�Ȃ���Ε`��
			if (!now->IsDeleted())
			{
				now->Draw();
			}
			now = next;
		}
	}
}

//=============================================================================
// �������Ă���^�X�N�̔j��
//=============================================================================
void CTaskGroup::AllRelease()
{
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		if (m_list.count(i) == 0)
		{
			continue;
		}

		CTask* now = m_list.at(i).top;

		while (now != nullptr)
		{
			if (!now->IsProtect())
			{
				now->Release();
			}
			now = now->GetNext();
		}
	}

	// ���S�\��̃^�X�N�̔j��
	DeleteTask();
}

//=============================================================================
// ��΂Ƀ^�X�N��j��
//=============================================================================
void CTaskGroup::AbsolutelyRelease()
{
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		if (m_list.count(i) == 0)
		{
			continue;
		}

		CTask* now = m_list.at(i).top;

		while (now != nullptr)
		{
			now->Release();
			now = now->GetNext();
		}
	}

	// ���S�\��̃^�X�N�̔j��
	DeleteTask();
}

//=============================================================================
// �w�肵��priority�̃^�X�N��j��
//=============================================================================
void CTaskGroup::PriorityRelease(const EPriority inPriotity)
{
	if (m_list.count(inPriotity) == 0)
	{
		return;
	}

	CTask* now = m_list.at(inPriotity).top;

	while (now != nullptr)
	{
		if (!now->IsProtect())
		{
			now->Release();
		}
		now = now->GetNext();
	}
}

//=============================================================================
// ���X�g�̍Ō�Ƀ^�X�N������
//=============================================================================
void CTaskGroup::SetPushCurrent(CTask * inTask, int inPriority)
{
	if (m_list.count(inPriority) == 0)
	{
		SList inList;
		inList.top = nullptr;
		inList.current = nullptr;
		m_list.insert(std::make_pair(inPriority, inList));

		if (m_priorityNumber < inPriority)
		{
			m_priorityNumber = inPriority;
		}
	}

	SList* list = &m_list.at(inPriority);

	if (list->current == nullptr && list->top == nullptr)
	{
		list->top = inTask;
		list->current = inTask;
	}
	else
	{
		CTask* current = list->current;		// �O�񖖔�
		list->current = inTask;				// �V�K����
		list->current->SetPrev(current);	// �V�K�����̑O�ɑO�񖖔���ݒ�
		current->SetNext(list->current);	// �O�񖖔��̌�ɐV�K������ݒ�
	}
}

//=============================================================================
// ���X�g�̍ŏ��Ƀ^�X�N������
//=============================================================================
void CTaskGroup::SetPushTop(CTask * inTask, int inPriority)
{
	if (m_list.count(inPriority) == 0)
	{
		SList inList;
		m_list.insert(std::make_pair(inPriority, inList));
		m_list.at(inPriority).top = nullptr;
		m_list.at(inPriority).current = nullptr;

		if (m_priorityNumber < inPriority)
		{
			m_priorityNumber = inPriority;
		}
	}

	if (m_list.at(inPriority).current == nullptr && m_list.at(inPriority).top == nullptr)
	{
		m_list.at(inPriority).top = inTask;
		m_list.at(inPriority).current = inTask;
	}
	else
	{
		CTask* top = m_list.at(inPriority).top;		// �O��擪
		m_list.at(inPriority).top = inTask;			// �V�K�擪
		m_list.at(inPriority).top->SetNext(top);	// �V�K�擪�̎��ɑO��擪��ݒ�
		top->SetPrev(m_list.at(inPriority).top);	// �V�K�擪�̌�ɐV�K�擪��ݒ�
	}
}

//=============================================================================
// �Q�Ƃ����^�X�N�̎��Ƀ^�X�N������
//=============================================================================
void CTaskGroup::SetNextTask(CTask * inReference, CTask * inTask)
{
	if (inReference == nullptr)
	{
		SetPushCurrent(inTask, 0);
		return;
	}
}

//=============================================================================
// �Q�Ƃ����^�X�N�̑O�Ƀ^�X�N������
//=============================================================================
void CTaskGroup::SetPrevTask(CTask * inReference, CTask * inTask)
{
	if (inReference == nullptr)
	{
		SetPushCurrent(inTask);
		return;
	}
}

//=============================================================================
// �^�X�N�̖������Ƃ̌���(Top�����猟�����Č��������擪��Ԃ�)
//=============================================================================
CTask * CTaskGroup::SearchRoleTop(int inRole, int inPriority)
{
	if (m_list.count(inPriority) == 0)
	{
		// ������̃��X�g���Ȃ������ꍇ
		assert(false);
		return nullptr;
	}

	CTask* now = m_list.at(inPriority).top;

	while (now != nullptr)
	{
		CTask* next = now->GetNext();
		if (now->GetRole() == inRole)
		{
			return now;
		}
		now = next;
	}
	return nullptr;
}

//=============================================================================
// �^�X�N�̖������Ƃ̌���(Current�����猟�����Č��������擪��Ԃ�)
//=============================================================================
CTask * CTaskGroup::SearchRoleCurrent(int inRole, int inPriority)
{
	if (m_list.count(inPriority) == 0)
	{
		// ������̃��X�g���Ȃ������ꍇ
		assert(false);
		return nullptr;
	}

	CTask* now = m_list.at(inPriority).current;

	while (now != nullptr)
	{
		CTask* prev = now->GetPrev();
		if (now->GetRole() == inRole)
		{
			return now;
		}
		now = prev;
	}
	return nullptr;
}

//=============================================================================
// �󂯂Ƃ����^�X�N�Ɠ��������̃^�X�N������(Next�����猟��)
//=============================================================================
CTask * CTaskGroup::SearchSameRoleNext(CTask* inTask)
{
	CTask* now = inTask;
	CTask::ERole role = inTask->GetRole();

	while (now != nullptr)
	{
		CTask* next = now->GetNext();
		if (now->GetRole() == role)
		{
			return now;
		}
		now = next;
	}
	return nullptr;
}

//=============================================================================
// �󂯂Ƃ����^�X�N�Ɠ��������̃^�X�N������(Prev�����猟��)
//=============================================================================
CTask * CTaskGroup::SearchSameRolePrev(CTask * inTask)
{
	CTask* now = inTask;
	CTask::ERole role = inTask->GetRole();

	while (now != nullptr)
	{
		CTask* prev = now->GetPrev();
		if (now->GetRole() == role)
		{
			return now;
		}
		now = prev;
	}
	return nullptr;
}

//=============================================================================
// �^�X�N�̍폜
//=============================================================================
void CTaskGroup::DeleteTask()
{
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		if (m_list.count(i) <= 0)
		{
			continue;
		}

		CTask* now = m_list.at(i).top;

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
			{ // �O��Ƀ^�X�N�������Ă���ꍇ
				next->SetPrev(prev);
				prev->SetNext(next);
			}
			else if (!isNextNullptr && isPrevNullptr)
			{ // ��̂݃^�X�N�������Ă���ꍇ
				m_list.at(i).top = next;
				next->SetPrev(nullptr);
			}
			else if (isNextNullptr && !isPrevNullptr)
			{ // �O�̂݃^�X�N�������Ă���ꍇ
				m_list.at(i).current = prev;
				prev->SetNext(nullptr);
			}
			else
			{ // �O��Ƀ^�X�N�������Ă��Ȃ��ꍇ
				m_list.at(i).current = nullptr;
				m_list.at(i).top = nullptr;
				m_list.erase(i);
			}

			now->Uninit();	// �I��
			delete now;		// �폜
			now = next;		// ���̃^�X�N�Ɉڂ�
		}
	}
}
