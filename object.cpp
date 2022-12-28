//=============================================================================
//
// �I�u�W�F�N�g
// Author : Yuda Kaito
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "object.h"
#include "application.h"
#include <assert.h>

//-----------------------------------------------------------------------------
// Summary : �R���X�g���N�^
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
// Summary : �f�X�g���N�^
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
CObject::~CObject()
{
}

//-----------------------------------------------------------------------------
// Summary : �X�V
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
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

	AddPos(GetMove());
}

//-----------------------------------------------------------------------------
// Summary : �w�肳�ꂽ��ʂ�T��
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
// Summary : ���g�Ɠ�����ʂ�object��T��
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
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
