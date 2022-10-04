//============================
//
// カメラ設定ヘッター
// Author:hamada ryuuga
//
//============================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "renderer.h"

class CCamera
{


public:
	CCamera();
	~CCamera();

	void Init(void);//初期化
	void Uninit(void);//破棄
	void Update(void);//更新
	void Set(int Type);//画面設定
	D3DXMATRIX *GetMtxProje();
	D3DXMATRIX *GetMtxView();
	D3DXVECTOR3 *GetPos();
	D3DXVECTOR3 *GetRot();
private:

	 float m_Speed = 1.0f;

	 float m_rotSpeed = 0.05f;
	 float m_rotSpeed2 = D3DX_PI / 2;

	 D3DXVECTOR3 m_posV;	//位置
	 D3DXVECTOR3 m_posR;	//注視点
	 D3DXVECTOR3 m_vecU;	//ベクトル
	 D3DXVECTOR3 m_directionV; //回転の向き位置
	 D3DXVECTOR3 m_directionR;//回転の向き注視点
	 D3DXVECTOR3 m_rot;//位置回転
	 float m_fDistance;//距離
	 float m_fDistanceY;
	 D3DVIEWPORT9 m_viewport;
	 D3DXVECTOR3 posVDest, m_posRDest;
	 D3DXMATRIX m_MtxProje; //プロジェクションマトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
	 D3DXMATRIX m_MtxView; //ビューマトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
	 int m_Type;

};
#endif

