//=============================================================================
//
// ���� ( �^�C�g�� )
// Author : hamada ryuuga
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "pause.h"
#include "input.h"
#include "application.h"
#include "Bg.h"
#include "player.h"
#include "fade.h"
#include "sound.h"
#include "ranking.h"
#include "application.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPause::CPause()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPause::Init(void)
{
	m_nextMode = MODE_GAME;
	m_onPause = false;

	//���[�h�I�����̔w�i����������
	m_pBg = CObject2d::Create(2);
	m_pBg->SetTexture(CTexture::GetInstance()->SetTexture("PAUSEBG"));
	m_pBg->SetSize(D3DXVECTOR3(450.0f, CApplication::CENTER_POS.y, 0.0f));
	m_pBg->SetPos(CApplication::CENTER_POS);
	m_pBg->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	//�Q�[���̕���
	m_pObject2d[0] = CObject2d::Create(2);
	m_pObject2d[0]->SetTexture(CTexture::GetInstance()->SetTexture("PAUSEGAME"));
	m_pObject2d[0]->SetSize(D3DXVECTOR3(150.0f, 50.0f, 0.0f));
	m_pObject2d[0]->SetPos(CApplication::CENTER_POS);
	m_pObject2d[0]->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	float y = 100.0f;

	//�`���[�g���A���̕���
	m_pObject2d[1] = CObject2d::Create(2);
	m_pObject2d[1]->SetTexture(CTexture::GetInstance()->SetTexture("PAUSERETURN"));
	m_pObject2d[1]->SetSize(D3DXVECTOR3(150.0f, 50.0f, 0.0f));
	m_pObject2d[1]->SetPos(D3DXVECTOR3(CApplication::CENTER_POS.x, CApplication::CENTER_POS.y + y, 0.0f));
	m_pObject2d[1]->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	y += 100.0f;

	//�����L���O�̕���
	m_pObject2d[2] = CObject2d::Create(2);
	m_pObject2d[2]->SetTexture(CTexture::GetInstance()->SetTexture("PAUSETITLE"));
	m_pObject2d[2]->SetSize(D3DXVECTOR3(150.0f, 50.0f, 0.0f));
	m_pObject2d[2]->SetPos(D3DXVECTOR3(CApplication::CENTER_POS.x, CApplication::CENTER_POS.y + y, 0.0f));
	m_pObject2d[2]->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	//�����L���O�̕���
	m_pObject2d[3] = CObject2d::Create(2);
	m_pObject2d[3]->SetTexture(CTexture::GetInstance()->SetTexture("PAUSEMENU"));
	m_pObject2d[3]->SetSize(D3DXVECTOR3(300.0f, 100.0f, 0.0f));
	m_pObject2d[3]->SetPos(D3DXVECTOR3(CApplication::CENTER_POS.x, CApplication::CENTER_POS.y - y, 0.0f));
	m_pObject2d[3]->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	return S_OK;
}

//=============================================================================
// �j��
//=============================================================================
void CPause::Uninit(void)
{
	
}

//=============================================================================
// �X�V
//=============================================================================
void CPause::Update(void)
{
	CInput *CInputpInput = CInput::GetKey();

	if (CInputpInput->Trigger(CInput::KEY_PAUSE)&& *CApplication::GetInstance()->GetFade()->GetFade() == CFade::FADENON)
	{
		if (m_onPause)
		{
			Set();
			m_pBg->SetColar(D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.0f));
			for (int i = 0; i < 4; i++)
			{
				m_pObject2d[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
		
		}
		else
		{
			m_nextMode = 0;
			Set();
			//�w�i
			m_pBg->SetColar(D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.8f));
			for (int i = 0; i < 4; i++)
			{//�S�����ς���
				m_pObject2d[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
			}
			//�I�����Ă���
			m_pObject2d[m_nextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

	}
	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		if (m_onPause)
		{
			switch (m_nextMode)
			{
			case EMode::MODE_GAME:
				//���[�h�̐ݒ�
				CApplication::GetInstance()->GetFade()->NextMode(CApplication::MODE_GAME);
				break;
			case EMode::MODE_RETURN:
				//���[�h�̐ݒ�
				m_pBg->SetColar(D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.0f));
				for (int i = 0; i < 4; i++)
				{
					m_pObject2d[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				}
				break;
			case EMode::MODE_TITLE:
				//���[�h�̐ݒ�
				CApplication::GetInstance()->GetFade()->NextMode(CApplication::MODE_TITLE);
				break;
			default:
				break;
			}
			m_onPause = false;
		}

		if (m_onPause)
		{
			m_pBg->SetColar(D3DXCOLOR(0.3f, 0.3f, 0.30f, 0.5f));
			for (int i = 0; i < 3; i++)
			{
				m_pObject2d[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
			}
			m_pObject2d[m_nextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			m_pBg->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			for (int i = 0; i < 3; i++)
			{

				m_pObject2d[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}

		}

	}
	if (m_onPause)
	{
		if (CInputpInput->Trigger(CInput::KEY_UP))
		{
			//���[�h�I��
			m_pObject2d[m_nextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));

			m_nextMode = (EMode)(m_nextMode - 1);


			if (m_nextMode < EMode::MODE_GAME)
			{
				m_nextMode = EMode::MODE_TITLE;
			}

			m_pObject2d[m_nextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (CInputpInput->Trigger(CInput::KEY_DOWN))
		{
			//���[�h�I��
			m_pObject2d[m_nextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));

			m_nextMode = (EMode)(m_nextMode + 1);

			if (m_nextMode >= EMode::MODE_END)
			{
				m_nextMode = EMode::MODE_GAME;
			}

			m_pObject2d[m_nextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
#ifdef _DEBUG


#endif // DEBUG
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPause::Draw(void)
{

}