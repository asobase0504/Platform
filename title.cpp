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
#include "2dpolygontemplate.h"
#include "camera.h"
#include "light.h"
#include "renderer.h"

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
	m_pCamera[0] = CRenderer::GetInstance()->SetCamera(new CCamera);
	m_pCamera[1] = CRenderer::GetInstance()->SetCamera(new CCamera);

	m_pLight = new CLight;
	m_pLight->Init();

	D3DXVECTOR3 BGPos;
	BGPos.x = 0.0f;
	BGPos.y = 0.0f;
	BGPos.z -= 30.0f;
	D3DXVECTOR3 EnemyPos = CApplication::CENTER_POS;
	m_alpha = 1.2f;

	m_addX = 0;
	m_addY = 0;
	ModeSelect = false;
	NextMode = MODE::MODE_GAME;

	//星の背景
	m_pBg[0] = CBg::Create();
	m_pBg[0]->SetTexture(CTexture::GetInstance()->SetTexture("STARRY"));
	m_pBg[0]->SetSize(CApplication::CENTER_POS);
	m_pBg[0]->SetPos(BGPos);
	m_pBg[0]->SetBgType(CBg::MOVE);
	m_pBg[0]->SetMove(D3DXVECTOR3(0.0001f, 0.0f, 0.0f));
	m_pBg[0]->SetCollar(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	//GonFoxのTITLE文字
	m_pBg[1] = CBg::Create();
	m_pBg[1]->SetTexture(CTexture::GetInstance()->SetTexture("GAME"));
	m_pBg[1]->SetSize(CApplication::CENTER_POS*0.8f);
	m_pBg[1]->SetPos(BGPos);
	m_pBg[1]->SetBgType(CBg::STOP);
	m_pBg[1]->SetCollar(D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.7f));

	//GonFoxのTITLE文字
	m_list[0] = CObject2d::Create(1);
	m_list[0]->SetTexture(CTexture::GetInstance()->SetTexture("TITLE"));
	m_list[0]->SetSize(CApplication::CENTER_POS);
	m_list[0]->SetPos(CApplication::CENTER_POS);
	m_list[0]->SetColar(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	//ゲームスタートの文字
	m_list[1] = CObject2d::Create(1);
	m_list[1]->SetTexture(CTexture::GetInstance()->SetTexture("FOXTITLE"));
	m_list[1]->SetSize(CApplication::CENTER_POS);
	m_list[1]->SetPos(CApplication::CENTER_POS);
	m_list[1]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//モード選択時の背景黒くするやつ
	m_fade = CObject2d::Create(2);
	m_fade->SetTexture(CTexture::GetInstance()->SetTexture("NONE"));
	m_fade->SetSize(CApplication::CENTER_POS);
	m_fade->SetPos(CApplication::CENTER_POS);
	m_fade->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	float y = 120.0f;

	//ゲームの文字
	m_text[0] = CObject2d::Create(2);
	m_text[0]->SetTexture(CTexture::GetInstance()->SetTexture("TITLEGAME"));
	m_text[0]->SetSize(CApplication::CENTER_POS);
	m_text[0]->SetPos(D3DXVECTOR3(CApplication::CENTER_POS.x, CApplication::CENTER_POS.y - y, 0.0f));
	m_text[0]->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	//チュートリアルの文字
	m_text[1] = CObject2d::Create(2);
	m_text[1]->SetTexture(CTexture::GetInstance()->SetTexture("TITLETUTORIAL"));
	m_text[1]->SetSize(CApplication::CENTER_POS);
	m_text[1]->SetPos(D3DXVECTOR3(CApplication::CENTER_POS.x, CApplication::CENTER_POS.y, 0.0f));
	m_text[1]->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	//ランキングの文字
	m_text[2] = CObject2d::Create(2);
	m_text[2]->SetTexture(CTexture::GetInstance()->SetTexture("TITLERANKIN"));
	m_text[2]->SetSize(CApplication::CENTER_POS);
	m_text[2]->SetPos(D3DXVECTOR3(CApplication::CENTER_POS.x, CApplication::CENTER_POS.y + y, 0.0f));
	m_text[2]->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	y += 120.0f;

	//おわりの文字
	m_text[3] = CObject2d::Create(2);
	m_text[3]->SetTexture(CTexture::GetInstance()->SetTexture("TITLEEND"));
	m_text[3]->SetSize(CApplication::CENTER_POS);
	m_text[3]->SetPos(D3DXVECTOR3(CApplication::CENTER_POS.x, CApplication::CENTER_POS.y + y, 0.0f));
	m_text[3]->SetColar(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_TITLE);

	CRanking::SetScore(0);

	CTest::Create(D3DXVECTOR3(0.0f, 1.57f, 0.0f) , true);

	return S_OK;
}

//=============================================================================
// 破棄
//=============================================================================
void CTitle::Uninit(void)
{
	CApplication::GetInstance()->GetSound()->Stop();
	//CApplication::GetInstance()->GetTaskGroup()->AllRelease();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	//きつねをもちもちさせるやつ
	if (!ModeSelect)
	{//一回押された	
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

		//きつねをもちもちさせるやつ
		D3DXVECTOR3 addPos = D3DXVECTOR3(1.0f + (float)m_addX, 1.0f + (float)m_addY, 0.0f);
		m_pBg[1]->SetSize(CApplication::CENTER_POS *0.8f + addPos);

		//点滅させる
		m_list[1]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, a));
	}
	CInput *CInputpInput = CInput::GetKey();

	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		CApplication* maneger = CApplication::GetInstance();
		maneger->GetSound()->Play(CSound::LABEL_SE_ON);
		if (ModeSelect)
		{//一回押された	
			switch (NextMode)
			{
			case MODE::MODE_GAME:
				//モードの設定
				maneger->GetFade()->NextMode(CApplication::MODE_GAME);
				break;
			case MODE::MODE_TUTORIAL:
				//モードの設定
				maneger->GetFade()->NextMode(CApplication::MODE_TUTORIAL);
				break;
			case MODE::MODE_RANKING:
				//モードの設定
				maneger->GetFade()->NextMode(CApplication::MODE_RANKING);
				break;
			case MODE::MODE_END:
				//ゲームの終了
				PostQuitMessage(0);
				break;
			default:
				break;
			}		
		}
		else
		{
			//画面黒くする
			m_fade->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

			//文字を出し
			for (int i = 0; i < 4; i++)
			{
				m_text[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
			}

			//今使ってるやつを明るく
			m_text[NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			ModeSelect = true;
		}

	}
	if (ModeSelect)
	{
		if (CInputpInput->Trigger(CInput::KEY_UP))
		{
			CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_NO);
			//モード選択
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
			CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_NO);
			//モード選択
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
		//モードの設定
		CApplication::GetInstance()->GetFade()->NextMode(CApplication::MODE_GAME);
	}
	if (CInputpInput->Trigger(CInput::KEY_F2))
	{
		//モードの設定
		CApplication::GetInstance()->GetFade()->NextMode(CApplication::MODE_NAMESET);
	}

#endif // DEBUG
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{

}