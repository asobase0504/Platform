//=============================================================================
//
// 制作 ( タイトル )
// Author : hamada ryuuga
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "application.h"
#include "Bg.h"
#include "player.h"
#include "fade.h"
#include "sound.h"
#include "ranking.h"
#include "camera.h"
#include "light.h"
#include "renderer.h"

#include "particle_manager.h"
#include "particle_emitter.h"
#include "particle.h"

CParticleManager* CTitle::m_pPaticleManager = nullptr;

//=============================================================================
// コンストラクター
//=============================================================================
CTitle::CTitle()
{
}

//=============================================================================
// デストラクト
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	m_pCamera = CRenderer::GetInstance()->SetCamera(new CCamera);

	m_pLight = new CLight;
	m_pLight->Init();

	m_pPaticleManager = new CParticleManager;
	if (FAILED(m_pPaticleManager->Init()))
	{
		return E_FAIL;
	}

	CObject2d* test = CObject2d::Create(2);
	test->Init();
	test->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	test->SetPos(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	test->SetMove(D3DXVECTOR3(25.0f, 25.0f, 0.0f));
	test->SetSize(D3DXVECTOR3(20.0f, 20.0f, 0.0f));

	return S_OK;
}

//=============================================================================
// 破棄
//=============================================================================
void CTitle::Uninit(void)
{
	CApplication::GetInstance()->GetSound()->Stop();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	if (CInput::GetKey()->Trigger(CInput::KEY_UP))
	{
		m_pPaticleManager->Create(CParticleEmitter::EObjectType::POLIGON2D,D3DXVECTOR3(70.0f,70.0f,0.0f), 1);
	}

	m_pPaticleManager->Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{

}