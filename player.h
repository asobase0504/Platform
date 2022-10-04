//============================
//
// プレイヤー設定ヘッター
// Author:hamada ryuuga
//
//============================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "motion.h"
#include "renderer.h"
#include "object3d.h"

class  CMotion;
class CMagicBox;
class CPlayer : public CObject3d
{
public:

	enum NOWMAGIC
	{
		NOW_FIRE = 2,		// 火
		NOW_ICE,			// 氷
		NOW_STORM,			// 風
		NOW_SUN,			// 雷
		NOW_NON,
		NOW_MAX
	};

	//modelデータの構造体//
	struct MODELDATAPLAYER
	{
		int key;		// 時間管理
		int nowKey;		// 今のキー
		int loop;		// ループするかどうか[0:ループしない / 1 : ループする]
		int num_key;  	// キー数
		/*MyKeySet KeySet[MAX_KEY];*/
	};

public:
	static const int MAXLIFE = 300;
	static const float ATTENUATION;		// 減衰係数
	static const float SPEED;			// スピード
	static const float WIDTH;			// モデルの半径
	static const int MAX_PRAYER;		// 最大数
	static const int MAX_MOVE;			// アニメーションの最大数
	static const int INVINCIBLE;		// 無敵時間
	static const int MAX_MODELPARTS = 9;
	
public:
	CPlayer();
	~CPlayer();

	HRESULT Init()override;	// 初期化
	void Uninit()override;	// 破棄
	void Update()override;	// 更新
	void Draw()override;	// 描画

	static CPlayer *Create();
	static NOWMAGIC *GetMagic();
	static void SetMagic(CPlayer::NOWMAGIC NextMagic);
	static CPlayer::NOWMAGIC * GetCastMagic();

private:
	
	void Move();		// 移動
	void TitleMove();
	void ResetMove();
	void TutorialMove();	//動きセット
	int m_Pow;
	float m_MoveSpeed;
	static NOWMAGIC m_NowMagic;			//現在の魔法
	static NOWMAGIC m_CastMagic;		//唱えた魔法
private:
};
#endif
