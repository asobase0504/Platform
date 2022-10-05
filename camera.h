//=============================================================================
//
// カメラ
// Author : Hamada Ryuuga
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "renderer.h"

//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------

//=============================================================================
// フェードクラス
//=============================================================================
class CCamera
{

public:
	CCamera();
	~CCamera();

	void Init();
	void Uninit();
	void Update();

	void Set(int Type);

	D3DXMATRIX *GetMtxProje();
	D3DXMATRIX *GetMtxView();
	D3DXVECTOR3 *GetPos();
	D3DXVECTOR3 *GetRot();

private:
	D3DXVECTOR3 m_posV;					// 位置
	D3DXVECTOR3 m_posVDest;
	D3DXVECTOR3 m_posR;					// 注視点
	D3DXVECTOR3 m_posRDest;
	D3DXVECTOR3 m_vecU;					// ベクトル
	D3DXVECTOR3 m_directionV;			// 回転の向き位置
	D3DXVECTOR3 m_directionR;			// 回転の向き注視点
	D3DXVECTOR3 m_rot;					// 位置回転
	D3DVIEWPORT9 m_viewport;			   
	D3DXMATRIX m_MtxProject;			// プロジェクションマトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
	D3DXMATRIX m_MtxView;				// ビューマトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
	float m_Speed;
	float m_rotSpeed;
	float m_rotSpeed2;
	float m_fDistance;					// 距離
	float m_fDistanceY;
	int m_Type;

};

#endif		// _CAMERA_H_
