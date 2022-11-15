//=============================================================================
//
// 3dpolygon
// Author : 浜田琉雅
//
//=============================================================================
#ifndef _3DPOLYGON_H_	// このマクロ定義がされてなかったら
#define _3DPOLYGON_H_	// 二重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "renderer.h"
#include "texture.h"
#include "object2d.h"

//-----------------------------------------------------------------------------
// マクロ宣言
//-----------------------------------------------------------------------------
#define TIMER (m_time + 90)

//=============================================================================
// 3Dポリゴンクラス
//=============================================================================
class  C3dpolygon : public CObject
{
public:
	const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	//頂点情報「3D」の構造体を定義
	struct VERTEX_3D
	{
		D3DXVECTOR3 pos;//頂点座標
		D3DXVECTOR3 nor;//ベクトル
		D3DCOLOR col;//カラー
		D3DXVECTOR2 tex;//テクスチャ
	};
protected:
	//polygonの基準サイズ
	static const D3DXVECTOR3 m_Vtx[4];

public:

	static C3dpolygon *Create(int list = 0);

	C3dpolygon(int list = 0);
	~C3dpolygon() override;
	HRESULT Init() override;
	void Uninit() override;
	void NormalUpdate() override;
	void Draw() override;

	// Setter
	virtual void SetPos(const D3DXVECTOR3& inPos) override;
	void SetTexture(int inTexture);
	void SetTex(PositionVec4 inTex);
	void SetSize(const D3DXVECTOR3& inSize);
	void SetCollar(D3DXCOLOR inCollar);
	void SetRot(D3DXVECTOR3 inRot) { m_rot = inRot; }

	// Getter
	LPDIRECT3DVERTEXBUFFER9 GetVtx();

	static void PolygonReset() { m_maxPolygon = 0; }

protected:
	float m_scale;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	int  m_time;
private:
	static int m_maxPolygon;
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;
	int m_texture;	// テクスチャの列挙型
};
#endif
