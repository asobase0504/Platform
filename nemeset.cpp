//**************************************************
//
// 制作 ( 名まえ )
// Author : hamada ryuuga
//
//**************************************************
#include "nemeset.h"
#include "input.h"
#include "manager.h"
#include "object2d.h"
#include "ranking.h"
#include "fade.h"
std::string  CNemeSet::m_PlayName;

//========================
// コンストラクター
//========================
CNemeSet::CNemeSet()
{

	if (m_object2d[0] != nullptr)
	{
		m_object2d[0] = nullptr;
	}

	for (int i = 0; i < 3; i++)
	{
		if (m_ListName[i] != nullptr)
		{
			m_ListName[i] = nullptr;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (m_PlayNameSet[i] != nullptr)
		{
			m_PlayNameSet[i] = nullptr;
		}
	}
}
//========================
// デストラクト
//========================
CNemeSet::~CNemeSet()
{
}

//================
//初期化処理
//================
HRESULT CNemeSet::Init(void)
{
	m_PlayName = "";
	m_NowPlay = 0;
	m_NemePos = D3DXVECTOR3(CManager::Pos.x-300.0f, 100.0f, 0.0f);

	m_object2d[0] = CObject2d::Create();
	m_object2d[0]->SetTexture(CTexture::TEXTURE_TITLEBG);
	m_object2d[0]->SetSize(CManager::Pos);
	m_object2d[0]->SetPos(CManager::Pos);

	m_object2d[1] = CObject2d::Create();
	m_object2d[1]->SetTexture(CTexture::TEXTURE_NAMETITLE);
	m_object2d[1]->SetSize(D3DXVECTOR3(500.0f, 175.0f, 0.0f));
	m_object2d[1]->SetPos(D3DXVECTOR3(CManager::Pos.x, 575.0f, 0.0f));

	m_ListName[0] = CName::Create();
	m_ListName[0]->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	m_ListName[0]->SetPos(D3DXVECTOR3(CManager::Pos.x -125.0f, 375.0f, 0.0f));
	m_ListName[0]->SetAlphabet(CName::MAX);

	m_ListName[1] = CName::Create();
	m_ListName[1]->SetSize(D3DXVECTOR3(75.0f, 75.0f, 0.0f));
	m_ListName[1]->SetPos(D3DXVECTOR3(CManager::Pos.x, 350.0f, 0.0f));

	m_ListName[2] = CName::Create();
	m_ListName[2]->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	m_ListName[2]->SetPos(D3DXVECTOR3(CManager::Pos.x + 125.0f, 375.0f, 0.0f));
	m_ListName[2]->SetAlphabet(CName::B);


	return S_OK;
}

//================
//破棄
//================
void CNemeSet::Uninit(void)
{


}

//==================
//更新処理
//==================
void CNemeSet::Update(void)
{
	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DELETE))
	{
		if (m_NowPlay > 0)
		{
			if (m_PlayNameSet[m_NowPlay-1] != nullptr)
			{
				m_NowPlay--;
				m_PlayNameSet[m_NowPlay]->Uninit();
				m_PlayName = m_PlayName.substr(0, m_PlayName.length() - 1);
				m_NemePos.x -= 120.0f;
			}
		}
	}

	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		if (m_NowPlay >= 7)
		{
			//モードの設定
			CRanking::SetPlayNeme(m_PlayName);

			CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_RANKING);
			return;
		}

		CNemeSet::RankingNeme();
	}	
}
//==================
//描画処理
//==================
void CNemeSet::Draw(void)
{
}

//========================
//rankingに名まえをねじ込む
//========================
void CNemeSet::RankingNeme()
{
	CName::ALPHABET Type = m_ListName[1]->GetAlphabet();

	if (Type >= CName::A && Type <= CName::Z)
	{
		m_PlayName += ('A' + (char)Type);
	}
	else if (Type == CName::MAX)
	{
		//モードの設定
		if (m_PlayName != "")
		{
			CRanking::SetPlayNeme(m_PlayName);

			CManager::GetInstance()->SetMode(CManager::MODE_RANKING);
			return;
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}

	m_PlayNameSet[m_NowPlay] = CName::Create();
	m_PlayNameSet[m_NowPlay]->SetSize(D3DXVECTOR3(60.0f, 60.0f, 0.0f));
	m_PlayNameSet[m_NowPlay]->SetPos(m_NemePos);
	m_PlayNameSet[m_NowPlay]->SetAlphabet(Type);
	m_PlayNameSet[m_NowPlay]->SetMoveSwitch(false);

	m_NemePos.x += 120.0f;
	m_NowPlay++;
}
