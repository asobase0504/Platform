//=============================================================================
//
// ゲーム画面
// Author : Hamada Ryuuga
//
//=============================================================================

//-----------------------------------------------------------------------------
// インクルード
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
#include "camera.h"

#include "text.h"


//-----------------------------------------------------------------------------
// 静的メンバ変数の宣言
//-----------------------------------------------------------------------------
CMagicBox* CGame::m_pMagicBox = nullptr;
CParticleManager*CGame::m_pPaticleManager = nullptr;
CPlayer*CGame::m_pPlayer = nullptr;
CPause *CGame::m_pPause = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// ゲームの初期化処理
//=============================================================================
HRESULT CGame::Init(void)
{
	m_pCamera[0] = CRenderer::GetInstance()->SetCamera(new CCamera(2));
	m_pCamera[1] = CRenderer::GetInstance()->SetCamera(new CCamera(1));
	m_gameCount = 0;

	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化

	// パーティクル
	m_pPaticleManager = new CParticleManager;
	if (FAILED(m_pPaticleManager->Init()))
	{
		return E_FAIL;
	}

	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetUp(CObject::PLAYER);

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_GAME);

	m_pPause = new CPause;
	m_pPause->Init();
	m_pPause->SetUp(CObject::PAUSE);

	return S_OK;
}

//=============================================================================
// ゲームの終了処理
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
	Release();
}

//=============================================================================
// ゲームの更新処理
//=============================================================================
void CGame::Update(void)
{
	CInput *CInputpInput = CInput::GetKey();

	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//モードの設定
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_RESULT);
		return;
	}
	if (CInputpInput->Trigger(CInput::KEY_F2))
	{
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_NAMESET);
		return;
	}
	m_pPaticleManager->Update();
}

//=============================================================================
// ゲームの描画処理
//=============================================================================
void CGame::Draw(void)
{

}

