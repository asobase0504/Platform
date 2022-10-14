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

	// 更新状態の列挙
	enum EUpdateStatus
	{
		POP = 0,
		NORMAL,
		END,
		Max
	};

public:
	CObject(int inList = 0);
	virtual ~CObject() override;

	void Update() override;

	// Setter
	/* 位置系 */
	virtual void SetPos(const D3DXVECTOR3 &inPos) { m_pos = inPos; }
	void SumPos(const D3DXVECTOR3 &inPos) { SetPos(m_pos + inPos); }
	void MulPos(const float inRatio) { SetPos(m_pos * inRatio); }

	/* 移動系 */
	virtual void SetMove(const D3DXVECTOR3 &inMove) { m_move = inMove; }
	void SumMove(const D3DXVECTOR3 &inMove) { SumMove(m_move += inMove); }
	void MulMove(const float &inRatio) { SumMove(m_move * inRatio); }

	void SetUp(const EType inType);
	void SetUpdateStatus(const EUpdateStatus inStatus) { m_updateStatus = inStatus; }

	// Getter
	const D3DXVECTOR3 *GetPos() const { return &m_pos; }
	const D3DXVECTOR3 *GetMove() const { return &m_move; }

	EType GetType();

private:
	virtual void PopUpdate();
	virtual void NormalUpdate();
	virtual void EndUpdate();

protected:
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_move;	// 移動量
private:
	EType m_type;	// 種別
	
	EUpdateStatus m_updateStatus;	// 更新状態
	bool m_isPopInNormalUpdate;		// 出現中に通常更新を行うか
	bool m_isEndInNormalUpdate;		// 終了中に通常更新を行うか
};
#endif