//=============================================================================
//
// �I�u�W�F�N�g
// Author : Hamada Ryuuga
// Author : Yuda Kaito
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "object.h"
#include "application.h"
#include <assert.h>

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject::CObject(CTaskGroup::EPriority inPriority, CTaskGroup::EPushMethod inMethod) :
	CTask(inPriority, inMethod),
	m_updateStatus(EUpdateStatus::POP),
	m_pos(D3DXVECTOR3(0.0f,0.0f,0.0f)),		// �ʒu
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),	// �ړ���
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),	// ��]��
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),	// �傫��
	m_color(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))	// �F
{
	SetRole(ROLE_OBJECT);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
// �X�V
//=============================================================================
void CObject::Update()
{
	switch (m_updateStatus)
	{
	case EUpdateStatus::POP:
		PopUpdate();
		break;
	case EUpdateStatus::NORMAL:
		NormalUpdate();
		break;
	case EUpdateStatus::END:
		EndUpdate();
		break;
	default:
		assert(false);
		break;
	}
}

//=============================================================================
// �w�肳�ꂽ��ʂ�T��
//=============================================================================
CObject * CObject::SearchType(EType inType, int inPriority)
{
	CTaskGroup* taskGroup = CApplication::GetInstance()->GetTaskGroup();

	// �w�肵��priority���ɂ���擪CObject���擾
	CObject* now = (CObject*)taskGroup->SearchRoleTop(CTask::ERole::ROLE_OBJECT, inPriority);

	while (now != nullptr)
	{
		CObject* next = (CObject*)taskGroup->SearchSameRoleNext(now);	// now���玟��CObject��T���B
		if (now->GetType() == inType)
		{// �\�肵���^�C�v���`�F�b�N
			return now;	// �����Ă�����Ԃ��B
		}
		now = next;
	}
	return nullptr;
}

//=============================================================================
// ���g�Ɠ�����ʂ�object��T��
//=============================================================================
CObject * CObject::NextSameType()
{
	CTaskGroup* taskGroup = CApplication::GetInstance()->GetTaskGroup();
	CObject* now = (CObject*)taskGroup->SearchSameRoleNext(this);
	EType type = this->GetType();

	while (now != nullptr)
	{
		CObject* next = (CObject*)taskGroup->SearchSameRoleNext(now);
		if (now->GetType() == type)
		{
			return now;
		}
		now = next;
	}
	return nullptr;
}

//=============================================================================
// �o�����̍X�V
//=============================================================================
void CObject::PopUpdate()
{
	m_updateStatus = EUpdateStatus::NORMAL;
}

//=============================================================================
// �ʏ풆�̍X�V
//=============================================================================
void CObject::NormalUpdate()
{
}

//=============================================================================
// �I�����̍X�V
//=============================================================================
void CObject::EndUpdate()
{
	Release();
}
