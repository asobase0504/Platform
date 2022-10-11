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
#include "manager.h"
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
	m_gameCount = 0;
	m_speedUp = 300;

	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����

	// �p�[�e�B�N��
	m_pPaticleManager = new CParticleManager;
	if (FAILED(m_pPaticleManager->Init()))
	{
		return E_FAIL;
	}

	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetUp(CObject::PLAYER);

	SetBossPop(false);
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_GAME);

	m_pPause = new CPause;
	m_pPause->Init();
	m_pPause->SetUp(CObject::PAUSE);

	return S_OK;
}

//=============================================================================
// �Q�[���̏I������
//=============================================================================
void CGame::Uninit(void)
{
	CManager::GetInstance()->GetSound()->Stop();
	CModelManager::ReleaseAll();
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
}

//=============================================================================
// �Q�[���̍X�V����
//=============================================================================
void CGame::Update(void)
{
	m_gameCount++;
	// �X�V����
	if (m_gameCount == m_speedUp&&!GetMaxBoss())
	{
		m_gameCount = 0;
		m_speedUp += 250;
	}

	CInput *CInputpInput = CInput::GetKey();

	
	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//���[�h�̐ݒ�
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_RESULT);
		return;
	}
	if (CInputpInput->Trigger(CInput::KEY_F2))
	{
	
		//CText::Create(CText::GON,120, 10, "�����n�����̂���...");
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_NAMESET);
		return;
	}
	if (GetMaxEnemy() <= 0)
	{
		if (GetMaxBoss())
		{
		}
		else
		{
			
		}
	}
	m_pPaticleManager->Update();
}

//=============================================================================
// �Q�[���̕`�揈��
//=============================================================================
void CGame::Draw(void)
{

}

