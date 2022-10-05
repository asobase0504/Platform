//=============================================================================
//
// 制作 ( タイトル )
// Author : hamada ryuuga
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "pause.h"
#include "input.h"
#include "manager.h"
#include "Bg.h"
#include "player.h"
#include "fade.h"
#include "sound.h"
#include "ranking.h"
#include "manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPause::CPause()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPause::Init(void)
{
	m_nextMode = MODE_GAME;
	m_onPause = false;

	//モード選択時の背景黒くするやつ
	m_pBg = CObject2d::Create(2);
	m_pBg->SetTexture(CTexture::TEXTURE_PAUSEBG);
	m_pBg->SetSize(D3DXVECTOR3(450.0f, CManager::CENTER_POS.y, 0.0f));
	m_pBg->SetPos(CManager::CENTER_POS);
	m_pBg->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	//ゲームの文字
	m_pObject2d[0] = CObject2d::Create(2);
	m_pObject2d[0]->SetTexture(CTexture::TEXTURE_PAUSEGAME);
	m_pObject2d[0]->SetSize(D3DXVECTOR3(150.0f, 50.0f, 0.0f));
	m_pObject2d[0]->SetPos(CManager::CENTER_POS);
	m_pObject2d[0]->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	float y = 100.0f;

	//チュートリアルの文字
	m_pObject2d[1] = CObject2d::Create(2);
	m_pObject2d[1]->SetTexture(CTexture::TEXTURE_PAUSERETURN);
	m_pObject2d[1]->SetSize(D3DXVECTOR3(150.0f, 50.0f, 0.0f));
	m_pObject2d[1]->SetPos(D3DXVECTOR3(CManager::CENTER_POS.x, CManager::CENTER_POS.y + y, 0.0f));
	m_pObject2d[1]->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	y += 100.0f;

	//ランキングの文字
	m_pObject2d[2] = CObject2d::Create(2);
	m_pObject2d[2]->SetTexture(CTexture::TEXTURE_PAUSETITLE);
	m_pObject2d[2]->SetSize(D3DXVECTOR3(150.0f, 50.0f, 0.0f));
	m_pObject2d[2]->SetPos(D3DXVECTOR3(CManager::CENTER_POS.x, CManager::CENTER_POS.y + y, 0.0f));
	m_pObject2d[2]->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	//ランキングの文字
	m_pObject2d[3] = CObject2d::Create(2);
	m_pObject2d[3]->SetTexture(CTexture::TEXTURE_PAUSEMENU);
	m_pObject2d[3]->SetSize(D3DXVECTOR3(300.0f, 100.0f, 0.0f));
	m_pObject2d[3]->SetPos(D3DXVECTOR3(CManager::CENTER_POS.x, CManager::CENTER_POS.y - y, 0.0f));
	m_pObject2d[3]->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	return S_OK;
}

//=============================================================================
// 破棄
//=============================================================================
void CPause::Uninit(void)
{
	
}

//=============================================================================
// 更新
//=============================================================================
void CPause::Update(void)
{
	CInput *CInputpInput = CInput::GetKey();

	if (CInputpInput->Trigger(CInput::KEY_PAUSE)&& *CManager::GetInstance()->GetFade()->GetFade() == CFade::FADENON)
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
			//背景
			m_pBg->SetColar(D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.8f));
			for (int i = 0; i < 4; i++)
			{//全部一回変える
				m_pObject2d[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
			}
			//選択してるやつ
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
				//モードの設定
				CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_GAME);
				break;
			case EMode::MODE_RETURN:
				//モードの設定
				m_pBg->SetColar(D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.0f));
				for (int i = 0; i < 4; i++)
				{
					m_pObject2d[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				}
				break;
			case EMode::MODE_TITLE:
				//モードの設定
				CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_TITLE);
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
			//モード選択
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
			//モード選択
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
// 描画処理
//=============================================================================
void CPause::Draw(void)
{

}