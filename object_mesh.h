//=============================================================================
//
// メッシュ設定ヘッター
// Author:hamada ryuuga
//
//=============================================================================
#ifndef _MESH_H_
#define _MESH_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "main.h"
#include "object_polygon3d.h"

//-----------------------------------------------------------------------------
// 定数
//-----------------------------------------------------------------------------
#define	EMESHX	(1)
#define	EMESHY	(5)
#define MAX_SIZEMESH (100.0f)
#define MAX_EMESH (10)
#define MOUNTAIN (50.0f)
#define MAXMOVE (10)

#define EMESHMAX (12800)

//-----------------------------------------------------------------------------
// メッシュ
//-----------------------------------------------------------------------------
class CMesh : public CObjectPolygon3D
{
public:
	virtual void OnHit() {}	// メッシュの当たった時の判定

	CMesh(CTaskGroup::EPriority nPriority = CTaskGroup::EPriority::LEVEL_3D_1);
	~CMesh() override;

	HRESULT Init() override;		// 初期化
	void Uninit() override;			// 破棄
	void NormalUpdate() override;	// 更新
	void Draw() override;			// 描画

	static CMesh* Create();

	bool CreateMesh(D3DXVECTOR3 *pPos);			// メッシュの凸凹つける
	bool CollisionMesh(D3DXVECTOR3 *pPos);		// メッシュの当たり判定つける

	void Loadfile(const char * pFileName);	// メッシュの読み込み
	void Savefile(const char * pFileName);	// メッシュの書き出し
	
	//セッター
	void SetPos(const D3DXVECTOR3 &pos);
	void SetMove(float ismove) { m_move = ismove; }
	void SetMesh(const int Size);
	void SetNumber(int IsNumber) { m_Number = IsNumber; }
	void SetType(int IsType) { m_Type = IsType; }
	void SetTexture(const char * pFileName);

	void SetOneMeshSize(D3DXVECTOR3 IsSize) 
	{
		m_MeshSize = IsSize; 
		CMesh::SetMesh(m_NowMesh);
	}

	void SwitchCollision(bool onCollision) { IsCollision = onCollision; };

	//ゲッター
	const D3DXVECTOR3 * CMesh::GetPos() const;
	D3DXVECTOR3 GetOneMeshSize() { return m_MeshSize; }
	D3DXVECTOR3 GetMeshSize() { return D3DXVECTOR3(m_X *m_MeshSize.x, 0.0f, m_Z *m_MeshSize.z); }
	D3DXVECTOR3 * GetPos() { return &m_pos; }
	float GetMove() { return m_move; }
	int GetNumber() { return m_Number; }
	int GetMeshType() { return m_Type; }

	int GetMeshSizeX() { return m_X; }

	std::string GetDataNeme() { return DataName; }

private:
	void SetVtxMesh(VERTEX_3D* pVtx, WORD* pIdx, int nCnt, bool isUp);
	void SetVtxMeshSize(int Size);
	void SetVtxMeshLight();

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファーへのポインタ
	LPDIRECT3DTEXTURE9 m_pTextureEmesh;	// テクスチャのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// インデックスバッファ

	D3DXVECTOR3 m_pos;			// 頂点座標
	D3DXVECTOR3 m_rot;			// 回転座標
	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス
	int m_xsiz;					// 面数
	int m_zsiz;					// 面数
	int m_X;					// 辺の頂点数
	int m_Z;					// 辺の頂点数
	int m_nVtx;					// 頂点数
	int m_Index;				// インデックス
	int m_por;
	int m_NowMesh;
	int m_Number;
	int m_Type;
	float m_move;
	D3DXVECTOR3 m_MeshSize;
	D3DXVECTOR3* m_nPosMesh;
	std::string  m_pFileName;
	std::string  DataName;
	bool IsCollision;
};
#endif

