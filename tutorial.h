//============================
//
// TUTORIAL画面のヘッダー
// Author:hamada ryuuga
//
//============================
#ifndef _TUTORIAL_H_		//このマクロが定義されてなかったら
#define _TUTORIAL_H_		//2重インクルード防止のマクロ定義

#include "main.h"
#include "object.h"
#include "object2d.h"


class CPlayer;
class CEnemy;
class CBg;
class CMagicBox;
class CParticleManager;
class CMultiply;

class CTutorial :public CObject
{
public:
	CTutorial();
	~CTutorial();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CParticleManager* GetParticleManager() { return m_PaticleManager; }
	static CMagicBox*GetMagicBox() { return m_MagicBox; };
	static CPlayer * GetPlayer() { return m_Player; };



private:
	CObject2d *m_object2d[4];
	CEnemy * m_Enemy;
	CBg *m_Bg[4];
	CScore*pScore;

	static CParticleManager* m_PaticleManager;	// パーティクルマネジャー
	static CMagicBox* m_MagicBox;
	static CPlayer * m_Player;
	int m_Magic;
	int m_NextTaskCount;//次のタスクまでのカウント

	//CLEARタスク一覧表
	bool m_MoveClear;
	bool m_AttackClear;
	bool m_MagicClear;
	
};

#endif
