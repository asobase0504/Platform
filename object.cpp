//=============================================================================
//
// オブジェクト
// Author : Hamada Ryuuga
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "object.h"
#include "object2d.h"
#include "player.h"
#include "manager.h"

#include "score.h"
#include "bg.h"
#include "life.h"
#include <assert.h>
#include "game.h"
#include "pause.h"

//-----------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------
CObject *CObject::m_pObject[MAX_LIST][MAX_OBJECT] = {};
int CObject::m_allMember = 0; 
int CObject::m_allEnemy = 0;
bool CObject::m_notBoss = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CObject::CObject(int list)
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[list][i] == nullptr)
		{
			m_type = NONE;
			m_list = list;
			m_id = i;
			m_pObject[list][i] = this;
			m_allMember++;
			break;
		}
	}
}
//=============================================================================
// デストラクタ
//=============================================================================
CObject::~CObject()
{
}

////=============================================================================
//// 全ての更新
////=============================================================================
//void CObject::AllUpdate()
//{
//	for (int i= 0; i < MAX_LIST; i++)
//	{
//		for (int j = 0; j < MAX_OBJECT; j++)
//		{
//
//			if (m_pObject[i][j] != nullptr)
//			{
//				m_pObject[i][j]->Update();
//			}
//		}
//	}
//}
//
////=============================================================================
//// 種類の更新
////=============================================================================
//void CObject::TypeUpdate(EType Type)
//{
//	for (int i= 0; i < MAX_LIST; i++)
//	{
//		for (int j = 0; j < MAX_OBJECT; j++)
//		{
//			if (m_pObject[i][j] != nullptr)
//			{
//				if (m_pObject[i][j]->m_type == Type)
//				{
//					m_pObject[i][j]->Update();
//				}
//			}
//		}
//	}
//}
//
////=============================================================================
//// 全ての描画
////=============================================================================
//void CObject::AllDraw()
//{
//	for (int i = 0; i < MAX_LIST; i++)
//	{
//		for (int j = 0; j < MAX_OBJECT; j++)
//		{
//			if (m_pObject[i][j] != nullptr)
//			{
//				m_pObject[i][j]->Draw();
//			}
//		}
//	}
//}
//
////=============================================================================
//// 種類の描画
////=============================================================================
//void CObject::TypeDraw(EType Type)
//{
//	for (int i = 0; i < MAX_LIST; i++)
//	{
//		for (int j = 0; j < MAX_OBJECT; j++)
//		{
//			if (m_pObject[i][j] != nullptr)
//			{
//				if (m_pObject[i][j]->m_type == Type)
//				{
//					m_pObject[i][j]->Draw();
//				}
//			}
//		}
//	}
//}

////=============================================================================
//// 全ての終了
////=============================================================================
//void CObject::AllUninit()
//{
//	for (int i = 0; i < MAX_LIST; i++)
//	{
//		for (int j = 0; j < MAX_OBJECT; j++)
//		{
//			if (m_pObject[i][j] != nullptr)
//			{
//				m_pObject[i][j]->Uninit();
//				delete m_pObject[i][j];
//				m_pObject[i][j] = nullptr;
//			}
//
//		}
//	}
//	m_allMember = 0;
//}
//
////=============================================================================
//// モード以外の終了
////=============================================================================
//void CObject::ModeNotUninit()
//{
//	for (int i = 0; i < MAX_LIST; i++)
//	{
//		for (int j = 0; j < MAX_OBJECT; j++)
//		{
//			if (m_pObject[i][i] != nullptr)
//			{
//				if (m_pObject[i][j]->m_type != MODE)
//				{
//					m_pObject[i][j]->Uninit();
//					delete m_pObject[i][j];
//					m_pObject[i][j] = nullptr;
//				}
//			}
//		}
//	}
//	m_allMember = 1;
//}

//=============================================================================
// タイプの設定
//=============================================================================
void CObject::SetUp(EType inType)
{
	switch (inType)
	{
	case EType::ENEMY:
		m_type = ENEMY;
		m_allEnemy++;
		break;
	case EType::PLAYER:
		m_type = PLAYER;
		break;
	case EType::BULLET:
		m_type = BULLET;
		break;
	case EType::GON:
		m_type = GON;
		break;
	case EType::MAGIC:
		m_type = MAGIC;
		break;
	case EType::CRYSTAL:
		m_type = CRYSTAL;
		break;
	case EType::BG:
		m_type = BG;
		break;
	case EType::MODE:
		m_type = MODE;
		break;
	case EType::PAUSE:
		m_type = PAUSE;
		break;
	default:
		assert(false);
		break;
	}
}

//=============================================================================
// オブジェクトの取得
//=============================================================================
CObject** CObject::GetObjectData(int inCount)
{
	return m_pObject[inCount];
}

//=============================================================================
// 番号の取得
//=============================================================================
int* CObject::GetId()
{
	return &m_id;
}

//=============================================================================
// タイプの取得
//=============================================================================
CObject::EType CObject::GetType()
{
	return m_type;
}
