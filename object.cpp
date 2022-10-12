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
int CObject::m_allMember = 0; 

//=============================================================================
// コンストラクタ
//=============================================================================
CObject::CObject(int inList)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
// タイプの設定
//=============================================================================
void CObject::SetUp(EType inType)
{
	switch (inType)
	{
	case EType::ENEMY:
		m_type = ENEMY;
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
// タイプの取得
//=============================================================================
CObject::EType CObject::GetType()
{
	return m_type;
}
