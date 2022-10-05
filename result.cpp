//=============================================================================
//
// リザルト画面
// Author:Hamada Ryuuga
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "result.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"
#include "player.h"
#include "motion.h"
#include "bg.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CResult::CResult()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CResult::Init(void)
{
	D3DXVECTOR3 BGPos;
	BGPos.x = 0.0f;
	BGPos.y = 0.0f;
	BGPos.z -= 30.0f;
	D3DXVECTOR3 Rot(0.0f, 1.57f, 0.0f);

	D3DXVECTOR3 Size(3.8f, 3.8f, 3.8f);

	m_pBg[0] = CBg::Create();
	m_pBg[0]->SetTexture(CTexture::TEXTURE_ENDBG);
	m_pBg[0]->SetSize(CManager::CENTER_POS);
	m_pBg[0]->SetPos(BGPos);

	m_pBg[1] = CBg::Create();
	m_pBg[1]->SetTexture(CTexture::TEXTURE_GAME);
	m_pBg[1]->SetSize(CManager::CENTER_POS*0.8f);
	m_pBg[1]->SetPos(BGPos);

	m_pObject2d[0] = CObject2d::Create(2);
	m_pObject2d[0]->SetTexture(CTexture::TEXTURE_CLEAR);
	m_pObject2d[0]->SetSize(D3DXVECTOR3(500.0f, 200.0f, 0.0f));
	m_pObject2d[0]->SetPos(CManager::CENTER_POS);
	m_pObject2d[0]->SetMove(D3DXVECTOR3(1.0f, -1.0f, 0.0f));
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RESET);

	m_pPlayer = nullptr;
	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetUp(CObject::PLAYER);

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CResult::Uninit(void)
{
	CManager::GetInstance()->GetSound()->Stop();
	//for (int i = 0; i < 4; i++)
	//{
	//	if (m_pBg[i] != nullptr)
	//	{
	//		m_pBg[i]->Uninit();
	//		
	//	}
	//}
	CModelManager::ReleaseAll();
}

//=============================================================================
// 更新
//=============================================================================
void CResult::Update(void)
{
	D3DXVECTOR3 DataPos = *m_pObject2d[0]->GetPos();
	D3DXVECTOR3 DataMove = m_pObject2d[0]->GetMove();
	D3DXVECTOR3 DataSize = m_pObject2d[0]->GetSize();

	if (DataPos.x < 0.0f + DataSize.x)
	{
		DataMove.x *= -1.0f;
	}
	if (DataPos.x > 1280.0f - DataSize.x)
	{
		DataMove.x *= -1.0f;
	}

	if (DataPos.y > 0.0f + DataSize.y)
	{
		DataMove.y *= -1.0f;
	}
	if (DataPos.y < 720.0f - DataSize.y)
	{
		DataMove.y *= -1.0f;
	}

	m_pObject2d[0]->SetPos(DataPos + DataMove);
	m_pObject2d[0]->SetMove(DataMove);
	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		//モードの設定
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_TITLE);
	}
#ifdef _DEBUG

	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//モードの設定
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_TITLE);
	}

#endif // DEBUG
}

//=============================================================================
// 描画
//=============================================================================
void CResult::Draw(void)
{

}