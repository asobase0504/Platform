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
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		if (m_list.count(i) == 0)
		{
			continue;
		}

		CTask* now = m_list.at(i).top;

		while (now != nullptr)
		{
			CTask* next = now->GetNext();
			now->Update();
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

		CTask* now = m_list.at(i).top;

		while (now != nullptr)
		{
			CTask* next = now->GetNext();
			now->Draw();
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
void CTaskGroup::PriorityRelease(const int inPriotity)
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
		m_priorityNumber = inPriority;
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
// �^�X�N�̍폜
//=============================================================================
void CTaskGroup::DeleteTask()
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
				m_list.at(i).top = next;
				next->SetPrev(nullptr);
			}
			else if (isNextNullptr && !isPrevNullptr)
			{
				m_list.at(i).current = prev;
				prev->SetNext(nullptr);
			}
			else
			{
				m_list.at(i).current = nullptr;
				m_list.at(i).top = nullptr;
			}

			now->Uninit();
			delete now;	// �폜
			now = next;	// ���̃^�X�N�Ɉڂ�
		}
	}
}
