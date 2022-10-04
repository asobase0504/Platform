//============================
//
// プレイヤー設定
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "player.h"
#include "input.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "motion.h"
#include "object3d.h"
#include "particle_manager.h"
#include "utility.h"
#include "game.h"
#include "tutorial.h"

//------------------------------------
// static変数
//------------------------------------
const float CPlayer::ATTENUATION = 0.5f;	// 
const float CPlayer::SPEED = 1.0f;			// 移動量
const float CPlayer::WIDTH = 10.0f;			// モデルの半径
const int CPlayer::MAX_PRAYER = 16;			// 最大数
const int CPlayer::MAX_MOVE = 9;			// アニメーションの最大数
const int CPlayer::INVINCIBLE = 30;		// 無敵時間
CPlayer::NOWMAGIC CPlayer::m_NowMagic = NOW_NON;		// 無敵時間
CPlayer::NOWMAGIC CPlayer::m_CastMagic = NOW_NON;		// 無敵時間


//------------------------------------
// コンストラクタ
//------------------------------------
CPlayer::CPlayer()
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CPlayer::~CPlayer()
{

}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CPlayer::Init()
{
	// 現在のモーション番号の保管
	CObject3d::Init();
	CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Data/system/Gon/Fox.txt");
	m_motionTypeOld = m_motionType;
	D3DXVECTOR3	Size(2.0f, 2.0f, 2.0f);
	m_MoveSpeed = 7.0f;
	m_rot.y += (-D3DX_PI*0.5f);
	SetSize(Size);
	SetLife(CPlayer::MAXLIFE);
	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CPlayer::Uninit()
{
	// 現在のモーション番号の保管
	CObject3d::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CPlayer::Update()
{

	switch (*CManager::GetInstance()->GetMode())
	{
	case CManager::MODE_TITLE:
		TitleMove();	//動きセット
		break;
	case CManager::MODE_GAME:
		Move();	//動きセット	
		break;
	case CManager::MODE_RESULT:
		ResetMove();
		break;
	case CManager::MODE_RANKING:
		break;
	case CManager::MODE_TUTORIAL:
		TutorialMove();
		break;
	default:
		break;
	}

	// 現在のモーション番号の保管
	CObject3d::Update();
}

//------------------------------------
// 描画
//------------------------------------
void CPlayer::Draw()
{
	CObject3d::Draw();
}

//------------------------------------
// create
//------------------------------------
CPlayer *CPlayer::Create()
{
	CPlayer * pObject = nullptr;
	pObject = new CPlayer;

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

//------------------------------------
// Move
//------------------------------------
void CPlayer::Move()	//動きセット
{



	CInput *CInputpInput = CInput::GetKey();
	D3DXVECTOR3 *Camerarot = CRenderer::GetCamera()->GetRot();
	float consumption = 0.0f;

	if (CInputpInput->Press(CInput::KEY_RIGHT))
	{
		m_move.x += sinf(D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		consumption = m_rotMove.x + (D3DX_PI*0.5f) - m_rot.y + Camerarot->y;
	}
	if (CInputpInput->Press(CInput::KEY_LEFT))
	{
		m_move.x += sinf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_DOWN))
	{	
		m_move.y -= m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_UP))
	{	
		m_move.y += m_MoveSpeed;
	}
	
	//弾のクリエイト
	if (CInputpInput->Press(CInput::KEY_SHOT))
	{
		
	}


 	else
	{
		m_Pow = 20;
	}

	if (m_pos.y <= -SCREEN_HEIGHT / 2 + 20.0f)
	{
		m_pos.y = (-SCREEN_HEIGHT / 2)+20.0f;
	}

	if (m_pos.y >= SCREEN_HEIGHT / 2 - 100.0f)
	{
		m_pos.y = SCREEN_HEIGHT / 2 - 100.0f;
	}
	if (m_pos.x <= -SCREEN_WIDTH / 2 + 100.0f)
	{
		m_pos.x = -SCREEN_WIDTH*0.5f + 100.0f;
	}
	if (m_pos.x >= SCREEN_WIDTH / 2 - 80.0f)
	{
		m_pos.x = SCREEN_WIDTH*0.5f - 80.0f;
	}

	//	必殺技
	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		//	particleManagerの取得
		CParticleManager* particleManager = CGame::GetParticleManager();

		if (particleManager->GetEmitter().size() == 0)
		{
			
			D3DXVECTOR3 Pos = ScreenCastWorld(
				&m_pos,			// スクリーン座標
				D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));
			
			//CastMagicの中につかった情報を入れる
			m_CastMagic = m_NowMagic;
		
			switch (m_NowMagic)
			{	
			case CPlayer::NOW_FIRE:
				particleManager->Create(Pos, 0, CParticleManager::NOW_FIRE);
				break;
			case CPlayer::NOW_ICE:
				particleManager->Create(Pos, 0, CParticleManager::NOW_ICE);
				break;
			case CPlayer::NOW_STORM:

				particleManager->Create(Pos, 0, CParticleManager::NOW_STORM);
				break;
			case CPlayer::NOW_SUN:
				particleManager->Create(Pos, 0, CParticleManager::NOW_SUN);
				break;
			case CPlayer::NOW_NON:
				break;
			default:
				break;
			}

			
		}
	}

	m_move.x += (0.0f - m_move.x)*ATTENUATION;//（目的の値-現在の値）＊減衰係数
	m_move.z += (0.0f - m_move.z)*ATTENUATION;
	m_move.y += (0.0f - m_move.y)*ATTENUATION;

	m_pos += m_move;//移動を加算

	//正規化
	if ( consumption > D3DX_PI)
	{
		 consumption += D3DX_PI * 2.0f;
	}
	if ( consumption < -D3DX_PI)
	{
		 consumption += -D3DX_PI * 2.0f;
	}

	//減算設定（感性）
	m_rot.y += (consumption)* ATTENUATION;//目的の値-現在の値）＊減衰係数

	 //正規化
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
}

//------------------------------------
// SetMagic
//------------------------------------
void CPlayer::SetMagic(CPlayer::NOWMAGIC NextMagic)
{
	if (NOW_MAX >= NextMagic)
	{
 		m_NowMagic = NextMagic;
	}
	else
	{
		m_NowMagic = NOW_NON;
	}
}

//------------------------------------
// GetMagic 
//------------------------------------
CPlayer::NOWMAGIC * CPlayer::GetMagic()
{
	return &m_NowMagic;
}


//------------------------------------
// GetMagic 
//------------------------------------
CPlayer::NOWMAGIC * CPlayer::GetCastMagic()
{
	return &m_CastMagic;
}

//------------------------------------
// TitleのときのMove
//------------------------------------
void CPlayer::TitleMove()
{

	D3DXVECTOR3 *Camerarot = CRenderer::GetCamera()->GetRot();
	float consumption = 0.0f;
	
	m_move.x += sinf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	m_move.z += cosf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	consumption = m_rotMove.x + -(D3DX_PI*0.5f) - m_rot.y + Camerarot->y;
	
	m_pos.y = 250.0f;

	m_move.x += (0.0f - m_move.x)*ATTENUATION;//（目的の値-現在の値）＊減衰係数
	m_move.z += (0.0f - m_move.z)*ATTENUATION;
	m_move.y += (0.0f - m_move.y)*ATTENUATION;

	m_pos += m_move;//移動を加算

					//正規化
	if (consumption > D3DX_PI)
	{
		consumption += D3DX_PI * 2.0f;
	}
	if (consumption < -D3DX_PI)
	{
		consumption += -D3DX_PI * 2.0f;
	}

	//減算設定（感性）
	m_rot.y += (consumption)* ATTENUATION;//目的の値-現在の値）＊減衰係数

										  //正規化
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}



	if (m_pos.x <= -SCREEN_WIDTH*0.5f-100.0f)
	{
		m_pos.x = SCREEN_WIDTH*0.5f;
	}
	
	
}

//------------------------------------
// ResetのときのMove
//------------------------------------
void CPlayer::ResetMove()
{

	D3DXVECTOR3 *Camerarot = CRenderer::GetCamera()->GetRot();
	float consumption = 0.0f;



	m_move.x += sinf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	m_move.z += cosf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	consumption = m_rotMove.x + -(D3DX_PI*0.5f) - m_rot.y + Camerarot->y;

	m_pos.y = 250.0f;

	m_move.x += (0.0f - m_move.x)*ATTENUATION;//（目的の値-現在の値）＊減衰係数
	m_move.z += (0.0f - m_move.z)*ATTENUATION;
	m_move.y += (0.0f - m_move.y)*ATTENUATION;

	m_pos += m_move;//移動を加算

					//正規化
	if (consumption > D3DX_PI)
	{
		consumption += D3DX_PI * 2.0f;
	}
	if (consumption < -D3DX_PI)
	{
		consumption += -D3DX_PI * 2.0f;
	}

	//減算設定（感性）
	m_rot.y += (consumption)* ATTENUATION;//目的の値-現在の値）＊減衰係数

										  //正規化
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}



	if (m_pos.x <= -SCREEN_WIDTH*0.5f - 100.0f)
	{
		m_pos.x = SCREEN_WIDTH*0.5f;
	}


}

//------------------------------------
// Move
//------------------------------------
void CPlayer::TutorialMove()	//動きセット
{
	CInput *CInputpInput = CInput::GetKey();
	D3DXVECTOR3 *Camerarot = CRenderer::GetCamera()->GetRot();
	float consumption = 0.0f;

	if (CInputpInput->Press(CInput::KEY_RIGHT))
	{
		m_move.x += sinf(D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		consumption = m_rotMove.x + (D3DX_PI*0.5f) - m_rot.y + Camerarot->y;
	}
	if (CInputpInput->Press(CInput::KEY_LEFT))
	{
		m_move.x += sinf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_DOWN))
	{
		m_move.y -= m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_UP))
	{
		m_move.y += m_MoveSpeed;
	}

	//弾のクリエイト
	if (CInputpInput->Press(CInput::KEY_SHOT))
	{
	
	}


	else
	{
		m_Pow = 20;
	}

	if (m_pos.y <= -SCREEN_HEIGHT / 2 + 20.0f)
	{
		m_pos.y = (-SCREEN_HEIGHT / 2) + 20.0f;
	}

	if (m_pos.y >= SCREEN_HEIGHT / 2 - 100.0f)
	{
		m_pos.y = SCREEN_HEIGHT / 2 - 100.0f;
	}
	if (m_pos.x <= -SCREEN_WIDTH / 2 + 100.0f)
	{
		m_pos.x = -SCREEN_WIDTH*0.5f + 100.0f;
	}
	if (m_pos.x >= SCREEN_WIDTH / 2 - 80.0f)
	{
		m_pos.x = SCREEN_WIDTH*0.5f - 80.0f;
	}

	//	必殺技
	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		//	particleManagerの取得
		CParticleManager* particleManager = CTutorial::GetParticleManager();

		if (particleManager->GetEmitter().size() == 0)
		{

			D3DXVECTOR3 Pos = ScreenCastWorld(
				&m_pos,			// スクリーン座標
				D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));

			//CastMagicの中につかった情報を入れる
			m_CastMagic = m_NowMagic;

			switch (m_NowMagic)
			{
			case CPlayer::NOW_FIRE:
				particleManager->Create(Pos, 0, CParticleManager::NOW_FIRE);
				break;
			case CPlayer::NOW_ICE:
				particleManager->Create(Pos, 0, CParticleManager::NOW_ICE);
				break;
			case CPlayer::NOW_STORM:

				particleManager->Create(Pos, 0, CParticleManager::NOW_STORM);
				break;
			case CPlayer::NOW_SUN:
				particleManager->Create(Pos, 0, CParticleManager::NOW_SUN);
				break;
			case CPlayer::NOW_NON:
				break;
			default:
				break;
			}

		}
	}

	m_move.x += (0.0f - m_move.x)*ATTENUATION;//（目的の値-現在の値）＊減衰係数
	m_move.z += (0.0f - m_move.z)*ATTENUATION;
	m_move.y += (0.0f - m_move.y)*ATTENUATION;

	m_pos += m_move;//移動を加算

					//正規化
	if (consumption > D3DX_PI)
	{
		consumption += D3DX_PI * 2.0f;
	}
	if (consumption < -D3DX_PI)
	{
		consumption += -D3DX_PI * 2.0f;
	}

	//減算設定（感性）
	m_rot.y += (consumption)* ATTENUATION;//目的の値-現在の値）＊減衰係数

										  //正規化
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}


}