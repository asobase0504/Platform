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
	{
		CObject2d* test = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
		test->Init();
		test->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));
		test->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		test->SetMove(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		test->SetSize(D3DXVECTOR3(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.25f, 0.0f));
	}

	{
		CObject2d* test = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_2);
		test->Init();
		test->SetColor(D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f));
		test->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		test->SetSize(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	return S_OK;
}

//=============================================================================
// �Q�[���̏I������
//=============================================================================
void CGame::Uninit(void)
{
	CApplication::GetInstance()->GetSound()->Stop();

	if (m_pPaticleManager != nullptr)
	{
		m_pPaticleManager->Uninit();
		delete m_pPaticleManager;
		m_pPaticleManager = nullptr;
	}
	Release();
}

//=============================================================================
// �Q�[���̍X�V����
//=============================================================================
void CGame::Update(void)
{
	if (CInput::GetKey()->Trigger(CInput::KEY_DOWN))
	{
		CApplication::GetInstance()->GetFade()->NextMode(CApplication::MODE_RESULT);
	}
}

//=============================================================================
// �Q�[���̕`�揈��
//=============================================================================
void CGame::Draw(void)
{

}
