//=============================================================================
//
// 制作 ( タイトル )
// Author : hamada ryuuga
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "main.h"
#include "object2d.h"
#include "mode.h"

//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------
class CBg;
class CPlayer;
class CEnemy;
class CCamera;
class CLight;
class CParticleManager;

//=============================================================================
// タイトルクラス
//=============================================================================
class CTitle :public CMode
{
	// 画面(モード)の種類
	enum MODE
	{
		MODE_GAME = 0,		// ゲーム画面	
		MODE_TUTORIAL,		// チュートリアル画面
		MODE_RANKING,		// ランキング画面
		MODE_END,			// 終了
		MODE_MAX
	};

public:
	CTitle();
	~CTitle() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	CParticleManager* GetPaticleManager() { return m_pPaticleManager; }

private:
	CCamera* m_pCamera;
	CLight* m_pLight;
	CBg* m_pBg[4];
	CObject2d* m_fade;
	int m_addX;
	int m_addY;
	MODE NextMode;
	bool Sizcontroller;
	bool ModeSelect;
	float m_alpha;

	CParticleManager* m_pPaticleManager;	// パーティクルマネジャー

};

#endif