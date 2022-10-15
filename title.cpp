//=============================================================================
//
// ���� ( �^�C�g�� )
// Author : hamada ryuuga
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "manager.h"
#include "Bg.h"
#include "player.h"
#include "fade.h"
#include "sound.h"
#include "ranking.h"
#include "2dpolygontemplate.h"
#include "camera.h"
#include "light.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^�[
//=============================================================================
CTitle::CTitle()
{
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	m_pCamera[0] = CRenderer::GetInstance()->SetCamera(new CCamera);
	m_pCamera[1] = CRenderer::GetInstance()->SetCamera(new CCamera);

	m_pLight = new CLight;
	m_pLight->Init();

	D3DXVECTOR3 BGPos;
	BGPos.x = 0.0f;
	BGPos.y = 0.0f;
	BGPos.z -= 30.0f;
	D3DXVECTOR3 EnemyPos = CManager::CENTER_POS;
	m_alpha = 1.2f;

	m_addX = 0;
	m_addY = 0;
	ModeSelect = false;
	NextMode = MODE::MODE_GAME;

	m_pPlayer = nullptr;
	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetUp(CObject::PLAYER);

	EnemyPos.z -= 30.0f;

	D3DXVECTOR3 Size(3.8f, 3.8f, 3.8f);
	D3DXVECTOR3 Rot(0.0f, 1.57f, 0.0f);

	//���̔w�i
	m_pBg[0] = CBg::Create();
	m_pBg[0]->SetTexture(CTexture::TEXTURE_STARRY);
	m_pBg[0]->SetSize(CManager::CENTER_POS);
	m_pBg[0]->SetPos(BGPos);
	m_pBg[0]->SetBgType(CBg::MOVE);
	m_pBg[0]->SetMove(D3DXVECTOR3(0.0001f, 0.0f, 0.0f));
	m_pBg[0]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//GonFox��TITLE����
	m_pBg[1] = CBg::Create();
	m_pBg[1]->SetTexture(CTexture::TEXTURE_GAME);
	m_pBg[1]->SetSize(CManager::CENTER_POS*0.8f);
	m_pBg[1]->SetPos(BGPos);
	m_pBg[1]->SetBgType(CBg::STOP);
	m_pBg[1]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));

	//GonFox��TITLE����
	m_list[0] = CObject2d::Create(1);
	m_list[0]->SetTexture(CTexture::TEXTURE_TITLE);
	m_list[0]->SetSize(CManager::CENTER_POS);
	m_list[0]->SetPos(CManager::CENTER_POS);
	m_list[0]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�Q�[���X�^�[�g�̕���
	m_list[1] = CObject2d::Create(1);
	m_list[1]->SetTexture(CTexture::TEXTURE_FOXTITLE);
	m_list[1]->SetSize(CManager::CENTER_POS);
	m_list[1]->SetPos(CManager::CENTER_POS);
	m_list[1]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//���[�h�I�����̔w�i����������
	m_fade = CObject2d::Create(2);
	m_fade->SetTexture(CTexture::TEXTURE_NONE);
	m_fade->SetSize(CManager::CENTER_POS);
	m_fade->SetPos(CManager::CENTER_POS);
	m_fade->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	float y = 120.0f;

	//�Q�[���̕���
	m_text[0] = CObject2d::Create(2);
	m_text[0]->SetTexture(CTexture::TEXTURE_TITLEGAME);
	m_text[0]->SetSize(CManager::CENTER_POS);
	m_text[0]->SetPos(D3DXVECTOR3(CManager::CENTER_POS.x, CManager::CENTER_POS.y - y, 0.0f));
	m_text[0]->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	//�`���[�g���A���̕���
	m_text[1] = CObject2d::Create(2);
	m_text[1]->SetTexture(CTexture::TEXTURE_TITLETUTORIAL);
	m_text[1]->SetSize(CManager::CENTER_POS);
	m_text[1]->SetPos(D3DXVECTOR3(CManager::CENTER_POS.x, CManager::CENTER_POS.y, 0.0f));
	m_text[1]->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	//�����L���O�̕���
	m_text[2] = CObject2d::Create(2);
	m_text[2]->SetTexture(CTexture::TEXTURE_TITLERANKIN);
	m_text[2]->SetSize(CManager::CENTER_POS);
	m_text[2]->SetPos(D3DXVECTOR3(CManager::CENTER_POS.x, CManager::CENTER_POS.y + y, 0.0f));
	m_text[2]->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	y += 120.0f;

	//�����̕���
	m_text[3] = CObject2d::Create(2);
	m_text[3]->SetTexture(CTexture::TEXTURE_TITLEEND);
	m_text[3]->SetSize(CManager::CENTER_POS);
	m_text[3]->SetPos(D3DXVECTOR3(CManager::CENTER_POS.x, CManager::CENTER_POS.y + y, 0.0f));
	m_text[3]->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_TITLE);

	CRanking::SetScore(0);

	CTest::Create(D3DXVECTOR3(0.0f, 1.57f, 0.0f) , true);

	return S_OK;
}

//=============================================================================
// �j��
//=============================================================================
void CTitle::Uninit(void)
{
	CManager::GetInstance()->GetSound()->Stop();
	CModelManager::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	//���˂�����������������
	if (!ModeSelect)
	{//��񉟂��ꂽ	
		if (m_addY <= 10)
		{
			Sizcontroller = true;
		}

		if (m_addY >= 50)
		{
			Sizcontroller = false;
		}

		float a;

		if (Sizcontroller)
		{
			m_addY++;
			m_addX--;
			a = sinf((float)m_alpha);
			m_alpha -= 1.0f / 60;
		}
		else
		{
			m_addY--;
			m_addX++;
			a = sinf((float)m_alpha);
			m_alpha += 1.0f / 60;
		}

		//���˂�����������������
		D3DXVECTOR3 addPos = D3DXVECTOR3(1.0f + (float)m_addX, 1.0f + (float)m_addY, 0.0f);
		m_pBg[1]->SetSize(CManager::CENTER_POS *0.8f + addPos);

		//�_�ł�����
		m_list[1]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, a));
	}
	CInput *CInputpInput = CInput::GetKey();

	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		CManager* maneger = CManager::GetInstance();
		maneger->GetSound()->Play(CSound::LABEL_SE_ON);
		if (ModeSelect)
		{//��񉟂��ꂽ	
			switch (NextMode)
			{
			case MODE::MODE_GAME:
				//���[�h�̐ݒ�
				maneger->GetFade()->NextMode(CManager::MODE_GAME);
				break;
			case MODE::MODE_TUTORIAL:
				//���[�h�̐ݒ�
				maneger->GetFade()->NextMode(CManager::MODE_TUTORIAL);
				break;
			case MODE::MODE_RANKING:
				//���[�h�̐ݒ�
				maneger->GetFade()->NextMode(CManager::MODE_RANKING);
				break;
			case MODE::MODE_END:
				//�Q�[���̏I��
				PostQuitMessage(0);
				break;
			default:
				break;
			}		
		}
		else
		{
			//��ʍ�������
			m_fade->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

			//�������o��
			for (int i = 0; i < 4; i++)
			{
				m_text[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
			}

			//���g���Ă��𖾂邭
			m_text[NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			ModeSelect = true;
		}

	}
	if (ModeSelect)
	{
		if (CInputpInput->Trigger(CInput::KEY_UP))
		{
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_NO);
			//���[�h�I��
			m_text[NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));

			NextMode = (MODE)(NextMode - 1);

			if (NextMode < MODE::MODE_GAME)
			{
				NextMode = MODE::MODE_END;
			}

			m_text[NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (CInputpInput->Trigger(CInput::KEY_DOWN))
		{
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_NO);
			//���[�h�I��
			m_text[NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));

			NextMode = (MODE)(NextMode + 1);

			if (NextMode >= MODE::MODE_MAX)
			{
				NextMode = MODE::MODE_GAME;
			}

			m_text[NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
#ifdef _DEBUG

	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//���[�h�̐ݒ�
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_GAME);
	}
	if (CInputpInput->Trigger(CInput::KEY_F2))
	{
		//���[�h�̐ݒ�
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_NAMESET);
	}

#endif // DEBUG
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}