//=============================================================================
//
// リザルト画面のヘッダー
// Author:hamada ryuuga
//
//=============================================================================
#ifndef _RESULT_H_		//このマクロが定義されてなかったら
#define _RESULT_H_		//2重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "main.h"
#include "object.h"
#include "object2d.h"

//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------
class CPlayer;
class CEnemy;
class CBg;

//=============================================================================
// リザルトクラス
//=============================================================================
class CResult :public CObject
{
public:
	CResult();
	~CResult();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;	
private:
	CObject2d* m_pObject2d[4];
	CPlayer* m_pPlayer;
	CEnemy* m_pEnemy[10];
	CBg* m_pBg[4];
	int m_addX;
	int m_addY;
	bool isSizeController;
};

#endif