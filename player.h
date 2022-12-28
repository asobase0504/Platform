//=============================================================================
//
// プレイヤー設定ヘッター
// Author:hamada ryuuga
// Author: Yuda Kaito
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "motion_model3D.h"

//-----------------------------------------------------------------------------
// プレイヤーが操作出来るモデル
//-----------------------------------------------------------------------------
class CPlayer : public CMotionModel3D
{
public:	// 定数
	static const float ATTENUATION;		// 減衰係数
	static const float SPEED;			// スピード
	static const float WIDTH;			// モデルの半径
	static const int MAX_PRAYER;		// 最大数
	static const int MAX_MOVE;			// アニメーションの最大数
	static const int INVINCIBLE;		// 無敵時間
	
public:
	CPlayer();
	~CPlayer();

	HRESULT Init() override;		// 初期化
	void Uninit() override;			// 破棄
	void NormalUpdate() override;	// 更新
	void Draw() override;			// 描画

	static CPlayer *Create();

private: // プライベート関数
	void Move();		// 移動

private: // メンバー変数
	float m_MoveSpeed;
};
#endif
