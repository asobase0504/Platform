//=============================================================================
//
// 2Dオブジェクト
// Author : 浜田琉雅
//
//=============================================================================
#ifndef _OBJECT2D_H_			// このマクロ定義がされてなかったら
#define _OBJECT2D_H_			// 二重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "renderer.h"
#include "object.h"
#include "texture.h"

// 4点の頂点
struct PositionVec4
{
	float     P0, P1, P2, P3;
	constexpr PositionVec4() : P0(0.0f), P1(0.0f), P2(0.0f), P3(0.0f) { }
	constexpr PositionVec4(float _P0, float _P1, float _P2, float _P3) : P0(_P0), P1(_P1), P2(_P2), P3(_P3) { }
};

//=============================================================================
// 2Dオブジェクトクラス
//=============================================================================
class CObject2d : public CObject
{
public:
	// 頂点フォーマット
	const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	// 頂点データ
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;
		float rhw;
		D3DCOLOR col;
		D3DXVECTOR2 tex;	// テクスチャ座標(レベル1)
	};

private:
	//polygonの拡大サイズ
	static const D3DXVECTOR3 m_Vtx[4];

public:
	static CObject2d *Create(int list = 0);

	CObject2d(int list = 0);
	~CObject2d() override;
	HRESULT Init() override;
	void Uninit() override;
	void NormalUpdate() override;
	void Draw() override;

	// Setter
	virtual void SetPos(const D3DXVECTOR3 &pos) override;
	virtual void SetMove(const D3DXVECTOR3 &move) override;
	void SetRot(D3DXVECTOR3 Rot) { m_rot = Rot; };
	void SetSize(D3DXVECTOR3 Size) { m_size = Size; };
	void SetTexture(int texture);
	void SetTex(PositionVec4 Tex);
	void SetColar(const D3DXCOLOR& inColar);
	void SetAnimation(const int U, const int V, const int Speed, const int Drawtimer, const bool loop);

	int GetTexture();
	D3DXCOLOR GetCollar() { return m_col; }
	D3DXVECTOR3 GetSize() { return m_size; }
	LPDIRECT3DVERTEXBUFFER9 &GetVtx() { return m_pVtxBuff; }

private:
	void Animation();

protected:
	int  m_nTimer;
	float m_nScale;
	D3DXVECTOR3 m_size;	// 大きさ
	D3DXVECTOR3 m_rot;	// 角度
	D3DXCOLOR m_col;	// 色
	D3DXMATRIX m_mtxWorld;	// マトリックス

private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;
	int m_texture;	// テクスチャの列挙型

	/* アニメーション系統 */
	// 現在のアニメーション状況
	int m_CounterAnim;
	int m_PatternAnimX;
	int m_PatternAnimY;

	// 分割数
	int m_DivisionX;
	int m_DivisionY;
	int m_DivisionMAX;

	// アニメーション速度
	int m_AnimationSpeed;
	int m_AnimationSpeedCount;
	
	// アニメーション時間
	int m_Timar;
	int m_TimaCount;

	bool m_OnAnimation;	// アニメーション使用の有無
	bool m_Loop;		// ループアニメーションか否か
};
#endif
