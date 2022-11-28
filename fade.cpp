//=============================================================================
//
// �t�F�[�h�ݒ�
// Author : Hamada Ryuuga
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <assert.h>
#include "fade.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFade::CFade() : CObject2d(CTaskGroup::LEVEL_FADE)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CFade::Init(void)
{
	AttachProtect();
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObject2d::Init();
	m_fadeSp = 0.007f;
	m_fadeSet = 0.0f;
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CFade::Uninit(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	 CObject2d::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CFade::NormalUpdate(void)
{
	CObject2d::NormalUpdate();
	if (m_fade != FADENON)
	{
		// ���݂̃��[�V�����ԍ��̕ۊ�
		if (m_fade == FADEOUT)
		{
			AddColorAlpha(-m_fadeSp);
		}

		if (m_fade == FADEIN)
		{
			AddColorAlpha(m_fadeSp);
		}

		if (GetColorAlpha() >= 1.0f)
		{
			m_fade = FADEOUT;
			SetColorAlpha(1.0f);
			CApplication::GetInstance()->SetMode(m_nextMode);

		}
		if (GetColorAlpha() <= 0.0f)
		{
			m_fade = FADENON;
			SetColorAlpha(0.0f);
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void CFade::Draw(void)
{
	 CObject2d::Draw();
}

//=============================================================================
// create
//=============================================================================
CFade* CFade::Create()
{
	CFade * pObject = new CFade;

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->m_nextMode = CApplication::MODE_TITLE;
		pObject->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		pObject->SetSize(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		pObject->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		pObject->SetType(CObject::MODE);
		pObject->m_fade = FADENON;
	}
	return pObject;
}


//=============================================================================
// ���̃��[�h�Ɉڍs
//=============================================================================
void CFade::NextMode(CApplication::MODE nextMode)
{
	if (m_fade != FADENON)
	{
		return;
	}

	/* ���t�F�[�h���ڍs����ꍇ�� */

	Init();
	m_nextMode = nextMode;
	SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_fade = FADEIN;
}
