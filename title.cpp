//**************************************************
//
// 制作 ( タイトル )
// Author : hamada ryuuga
//
//**************************************************
#include "title.h"
#include "input.h"
#include "manager.h"
#include "Bg.h"
#include "player.h"
#include "fade.h"
#include "sound.h"
#include "ranking.h"
#include "2dpolygontemplate.h"
//========================
// コンストラクター
//========================
CTitle::CTitle()
{
}
//========================
// デストラクト
//========================
CTitle::~CTitle()
{
}

//================
//初期化処理
//================
HRESULT CTitle::Init(void)
{
	D3DXVECTOR3 BGPos;
	BGPos.x = 0.0f;
	BGPos.y = 0.0f;
	BGPos.z -= 30.0f;
	D3DXVECTOR3 EnemyPos = CManager::Pos;
	m_alpha = 1.2f;

	
	m_addX = 0;
	m_addY = 0;
	ModeSelect = false;
	NextMode = MODE::MODE_GAME;

	m_Player = nullptr;
	m_Player = CPlayer::Create();
	m_Player->SetUp(CObject::PLAYER);

	EnemyPos.z -= 30.0f;

	D3DXVECTOR3 Size(3.8f, 3.8f, 3.8f);
	D3DXVECTOR3 Rot(0.0f, 1.57f, 0.0f);



	//星の背景
	m_Bg[0] = CBg::Create();
	m_Bg[0]->SetTexture(CTexture::TEXTURE_STARRY);
	m_Bg[0]->SetSize(CManager::Pos);
	m_Bg[0]->SetPos(BGPos);
	m_Bg[0]->SetBgType(CBg::MOVE);
	m_Bg[0]->SetMove(D3DXVECTOR3(0.0001f, 0.0f, 0.0f));
	m_Bg[0]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	
	//GonFoxのTITLE文字
	m_Bg[1] = CBg::Create();
	m_Bg[1]->SetTexture(CTexture::TEXTURE_GAME);
	m_Bg[1]->SetSize(CManager::Pos*0.8f);
	m_Bg[1]->SetPos(BGPos);
	m_Bg[1]->SetBgType(CBg::STOP);
	m_Bg[1]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));

	
	//GonFoxのTITLE文字
	m_list[0] = CObject2d::Create(1);
	m_list[0]->SetTexture(CTexture::TEXTURE_TITLE);
	m_list[0]->SetSize(CManager::Pos);
	m_list[0]->SetPos(CManager::Pos);
	m_list[0]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	
	//ゲームスタートの文字
	m_list[1] = CObject2d::Create(1);
	m_list[1]->SetTexture(CTexture::TEXTURE_FOXTITLE);
	m_list[1]->SetSize(CManager::Pos);
	m_list[1]->SetPos(CManager::Pos);
	m_list[1]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	//モード選択時の背景黒くするやつ
	fade = CObject2d::Create(2);
	fade->SetTexture(CTexture::TEXTURE_NONE);
	fade->SetSize(CManager::Pos);
	fade->SetPos(CManager::Pos);
	fade->SetCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	float y = 120.0f;

	//ゲームの文字
	m_object2d[0] = CObject2d::Create(2);
	m_object2d[0]->SetTexture(CTexture::TEXTURE_TITLEGAME);
	m_object2d[0]->SetSize(CManager::Pos);
	m_object2d[0]->SetPos(D3DXVECTOR3(CManager::Pos.x, CManager::Pos.y - y, 0.0f));
	m_object2d[0]->SetCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));


	//チュートリアルの文字
	m_object2d[1] = CObject2d::Create(2);
	m_object2d[1]->SetTexture(CTexture::TEXTURE_TITLETUTORIAL);
	m_object2d[1]->SetSize(CManager::Pos);
	m_object2d[1]->SetPos(D3DXVECTOR3(CManager::Pos.x, CManager::Pos.y, 0.0f));
	m_object2d[1]->SetCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));



	//ランキングの文字
	m_object2d[2] = CObject2d::Create(2);
	m_object2d[2]->SetTexture(CTexture::TEXTURE_TITLERANKIN);
	m_object2d[2]->SetSize(CManager::Pos);
	m_object2d[2]->SetPos(D3DXVECTOR3(CManager::Pos.x, CManager::Pos.y + y, 0.0f));
	m_object2d[2]->SetCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	y += 120.0f;

	//おわりの文字
	m_object2d[3] = CObject2d::Create(2);
	m_object2d[3]->SetTexture(CTexture::TEXTURE_TITLEEND);
	m_object2d[3]->SetSize(CManager::Pos);
	m_object2d[3]->SetPos(D3DXVECTOR3(CManager::Pos.x, CManager::Pos.y + y, 0.0f));
	m_object2d[3]->SetCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_TITLE);

	CRanking::SetScore(0);

	CTest::Create(D3DXVECTOR3(0.0f, 1.57f, 0.0f) , true);

	return S_OK;
}

//================
//破棄
//================
void CTitle::Uninit(void)
{
	CManager::GetInstance()->GetSound()->Stop();
	/*for (int i = 0; i < 4; i++)
	{
		if (m_Bg[i] !=nullptr)
		{
			m_Bg[i]->Uninit();
			m_Bg[i] = nullptr;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (m_object2d[i] != nullptr)
		{
			m_object2d[i]->Uninit();
			m_object2d[i] = nullptr;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (m_list[i] != nullptr)
		{
			m_list[i]->Uninit();
			m_list[i] = nullptr;
		}
	}

	if (m_Player != nullptr)
	{
		m_Player->Uninit();
		m_Player = nullptr;
	}

	for (int i = 0; i < 10; i++)
	{
		if (m_Enemy[i] != nullptr)
		{
			m_Enemy[i]->Uninit();
			m_Enemy[i] = nullptr;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (m_3dpolygon[i] != nullptr)
		{
			m_3dpolygon[i]->Uninit();
			m_3dpolygon[i] = nullptr;
		}
	}*/
	CModelManager::ReleaseAll();
}

//==================
//更新処理
//==================
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
		m_Bg[1]->SetSize(CManager::Pos *0.8f + addPos);

		//点滅させる
		m_list[1]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, a));
	}
	CInput *CInputpInput = CInput::GetKey();

	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		CManager* maneger = CManager::GetInstance();
		maneger->GetSound()->Play(CSound::LABEL_SE_ON);
		if (ModeSelect)
		{//一回押された	
			switch (NextMode)
			{
			case MODE::MODE_GAME:
				//モードの設定
				maneger->GetFade()->NextMode(CManager::MODE_GAME);
				break;
			case MODE::MODE_TUTORIAL:
				//モードの設定
				maneger->GetFade()->NextMode(CManager::MODE_TUTORIAL);
				break;
			case MODE::MODE_RANKING:
				//モードの設定
				maneger->GetFade()->NextMode(CManager::MODE_RANKING);
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
			fade->SetCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

			//文字を出し
			for (int i = 0; i < 4; i++)
			{
				m_object2d[i]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
			}

			//今使ってるやつを明るく
			m_object2d[NextMode]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			ModeSelect = true;
		}

	}
	if (ModeSelect)
	{
		if (CInputpInput->Trigger(CInput::KEY_UP))
		{
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_NO);
			//モード選択
			m_object2d[NextMode]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));

			NextMode = (MODE)(NextMode - 1);


			if (NextMode < MODE::MODE_GAME)
			{
				NextMode = MODE::MODE_END;
			}

	
			m_object2d[NextMode]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (CInputpInput->Trigger(CInput::KEY_DOWN))
		{
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_NO);
			//モード選択
			m_object2d[NextMode]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));

			NextMode = (MODE)(NextMode + 1);

			if (NextMode >= MODE::MODE_MAX)
			{
				NextMode = MODE::MODE_GAME;
			}

			m_object2d[NextMode]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
#ifdef _DEBUG

	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//モードの設定
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_GAME);
	}
	if (CInputpInput->Trigger(CInput::KEY_F2))
	{
		//モードの設定
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_NAMESET);
	}

#endif // DEBUG
}
//==================
//描画処理
//==================
void CTitle::Draw(void)
{

}