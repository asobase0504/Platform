//=============================================================================
//
// オブジェクト
// Author : Hamada Ryuuga
//
//=============================================================================
#ifndef _OBJECT_H_			// このマクロ定義がされてなかったら
#define _OBJECT_H_			// 二重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "renderer.h"
#include "task.h"

//=============================================================================
// オブジェクトクラス
//=============================================================================
class CObject : public CTask
{
public:
	enum EType
	{
		ENEMY = 0,
		PLAYER,
		BULLET,
		GON,
		MAGIC,
		CRYSTAL,
		BG,
		SORCERY,
		BELL,
		MODE,
		RANKUPBULLET,
		PAUSE,
		MAX,
		NONE
	};

public:
	CObject(int inList = 0);
	virtual ~CObject() override;

	// Setter
	virtual void SetPos(const D3DXVECTOR3 &inPos) { m_pos = inPos; }
	void SumPos(const D3DXVECTOR3 &inPos) { SetPos(m_pos + inPos); }
	void MulPos(const float inRatio) { SetPos(m_pos * inRatio); }

	virtual void SetMove(const D3DXVECTOR3 &inMove) { m_move = inMove; }
	void SumMove(const D3DXVECTOR3 &inMove) { SumMove(m_move += inMove); }
	void MulMove(const float &inRatio) { SumMove(m_move * inRatio); }

	void SetUp(const EType inType);

	// Getter
	const D3DXVECTOR3 *GetPos() const { return &m_pos; }
	const D3DXVECTOR3 *GetMove() const { return &m_move; }

	EType GetType();

protected:
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_move;	// 移動量
private:
	EType m_type;
	static int m_allMember;
};
#endif