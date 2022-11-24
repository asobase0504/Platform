//=============================================================================
//
// �Q�[�����
// Author : Hamada Ryuuga
//
//=============================================================================

//-----------------------------------------------------------------------------
// �C���N���[�h
//-----------------------------------------------------------------------------
#include "game.h"
#include "input.h"
#include "application.h"
#include "object.h"
#include "light.h"
#include "player.h"
#include "file.h"

#include "fade.h"

#include "multiply.h"
#include "particle_manager.h"
#include "ranking.h"

#include "score.h"
#include "sound.h"
#include "bg.h"

#include "pause.h"
#include "camera.h"

#include "task_group.h"

#include "text.h"


//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ��̐錾
//-----------------------------------------------------------------------------
CMagicBox* CGame::m_pMagicBox = nullptr;
CParticleManager*CGame::m_pPaticleManager = nullptr;
CPlayer*CGame::m_pPlayer = nullptr;
CPause *CGame::m_pPause = nullptr;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// �Q�[���̏���������
//=============================================================================
HRESULT CGame::Init(void)
{
	m_pCamera[0] = CRenderer::GetInstance()->SetCamera(new CCamera(CTaskGroup::LEVEL_3D_1));
	m_pCamera[1] = CRenderer::GetInstance()->SetCamera(new CCamera(CTaskGroup::LEVEL_3D_2));
	m_gameCount = 0;

	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����

	// �p�[�e�B�N��
	m_pPaticleManager = new CParticleManager;
	if (FAILED(m_pPaticleManager->Init()))
	{
		return E_FAIL;
	}

	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetType(CObject::PLAYER);

	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_GAME);

	m_pPause = new CPause;
	m_pPause->Init();
	m_pPause->SetType(CObject::PAUSE);

	return S_OK;
}

//=============================================================================
// �Q�[���̏I������
//=============================================================================
void CGame::Uninit(void)
{
	CApplication::GetInstance()->GetSound()->Stop();
	CApplication::GetInstance()->GetTaskGroup()->AllRelease();
	CRanking::SetScore(CScore::GetScore());

	if (m_pPaticleManager != nullptr)
	{
		m_pPaticleManager->Uninit();
		delete m_pPaticleManager;
		m_pPaticleManager = nullptr;
	}

	if (m_pPause != nullptr)
	{
		m_pPause->Uninit();
		m_pPause = nullptr;
	}
	Release();
}

//=============================================================================
// �Q�[���̍X�V����
//=============================================================================
void CGame::Update(void)
{
	CInput *CInputpInput = CInput::GetKey();

	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//���[�h�̐ݒ�
		CApplication::GetInstance()->GetFade()->NextMode(CApplication::MODE_RESULT);
		return;
	}
	if (CInputpInput->Trigger(CInput::KEY_F2))
	{
		CApplication::GetInstance()->GetFade()->NextMode(CApplication::MODE_NAMESET);
		return;
	}
	m_pPaticleManager->Update();
}

//=============================================================================
// �Q�[���̕`�揈��
//=============================================================================
void CGame::Draw(void)
{

}

