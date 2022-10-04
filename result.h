//============================
//
// リザルト画面のヘッダー
// Author:hamada ryuuga
//
//============================
#ifndef _RESULT_H_		//このマクロが定義されてなかったら
#define _RESULT_H_		//2重インクルード防止のマクロ定義

#include "main.h"
#include "object.h"
#include "object2d.h"


class CPlayer;
class CEnemy;
class CBg;

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
	CObject2d *m_object2d[4];

	CPlayer * m_Player;
	CEnemy * m_Enemy[10];
	CBg *m_Bg[4];
	int m_addX;
	int m_addY;
	bool Sizcontroller;
};

#endif