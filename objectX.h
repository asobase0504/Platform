//=============================================================================
//
// オブジェクトX処理 [objectX.h]
// Author : KADO TAKUMA
// Author : Yuda Kaito
//
//=============================================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CObjectX : public CObject
{
public:
	//-------------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//-------------------------------------------------------------------------
	explicit CObjectX(int nPriority = 2);
	~CObjectX() override;

	//-------------------------------------------------------------------------
	// メンバー関数
	//-------------------------------------------------------------------------
	HRESULT Init() override;			// 初期化処理
	void Uninit() override;				// 終了処理
	void Update() override;				// 更新処理
	void Draw() override;				// 描画処理
	void Draw(D3DXMATRIX mtxParent);	// 描画処理

	void CalculationVtx();				// 頂点最大小値の計算処理

	// Setter
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }	// ワールドマトリックスのセッター
	void SetMaxVtx(D3DXVECTOR3 Maxvtx);			// 頂点最大値設定処理
	void SetMinVtx(D3DXVECTOR3 Minvtx);			// 頂点最小値設定処理
	void SetParent(CObjectX* inParent) { m_pParent = inParent; }		// 親モデルの情報
	void SetCollisionFlag(bool inFlag) { m_isCollision = inFlag; }

	// Getter
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }		// ワールドマトリックスのゲッター
	D3DXVECTOR3 GetMaxVtx(void) { return m_MaxVtx; }	// 頂点最大値取得処理
	D3DXVECTOR3 GetMinVtx(void) { return m_MinVtx; }	// 頂点最小値取得処理
	CObjectX* GetParent(void) { return m_pParent; }		// 親モデルの情報
	bool IsCollision() { return m_isCollision; }

	static CObjectX *Create(D3DXVECTOR3 pos, int nPriority);	// 生成処理
	void LoadModel(const char *aFileName);						// モデルの読み込み処理
	void Projection(void);										// 平行投影処理

	// Collision
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pSize);	// 当たり判定 (左右, 奥, 手前)
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *inMaxVtx, D3DXVECTOR3 *inMinVtx);	// 当たり判定 (左右, 奥, 手前)
	bool UpCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pSize, D3DXVECTOR3 *pMove);	// 当たり判定 (上側)
	bool UpCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *inMaxVtx, D3DXVECTOR3 *inMinVtx, D3DXVECTOR3 *pMove);	// 当たり判定 (上側)

private:
	//-------------------------------------------------------------------------
	// メンバー変数
	//-------------------------------------------------------------------------
	D3DXVECTOR3 m_MinVtx;		// モデルの頂点最小値
	D3DXVECTOR3 m_MaxVtx;		// モデルの頂点最大値
	D3DXCOLOR m_col;			// 色
	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス
	LPD3DXMESH m_pMesh;			// メッシュ情報へのポインタ
	LPD3DXBUFFER m_pBuffMat;	// マテリアル情報へのポインタ
	DWORD m_NumMat;				// マテリアル情報の数
								
	CObjectX *m_pParent;		// 親モデルの情報
	bool m_isCollision;			// 当たり判定が必要か
};
#endif