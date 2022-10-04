//============================
//
// カメラ設定
// Author:hamada ryuuga
//
//============================
#include "camera.h"
#include "input.h"

#include "manager.h"

//----------------------------
//コンストラクト
//----------------------------
CCamera::CCamera()
{
}

//----------------------------
//デストラクト
//----------------------------
CCamera::~CCamera()
{
}
//----------------------------
//初期化処理
//----------------------------
void CCamera::Init(void)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//視点　注視点　上方向　設定
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
	m_posR = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_directionR = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	m_directionV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fDistance = sqrtf((m_posR.x - m_posV.x) *
		(m_posR.x - m_posV.x) +
		(m_posR.z - m_posV.z) *
		(m_posR.z - m_posV.z));

	m_fDistance = sqrtf((m_posR.y - m_posV.y)*
		(m_posR.y - m_posV.y) +
		(m_fDistance*m_fDistance));

	m_rot.x = atan2f((m_posR.z - m_posV.z),
		(m_posR.y - m_posV.y));
}

//----------------------------
//終了処理
//----------------------------
void CCamera::Uninit(void)
{
}

//----------------------------
//更新処理
//----------------------------
void CCamera::Update(void)
{
	if (m_Type == 0)
	{
		m_posV.x += 1.1f;
		m_posR.x += 1.1f;
	}
}

//----------------------------
//描画処理
//----------------------------
void CCamera::Set(int Type)
{
	m_Type = Type;
	LPDIRECT3DDEVICE9  pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスのポインタ

	//ビューマトリックスを初期化
	D3DXMatrixIdentity(&m_MtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_MtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//適用
	pDevice->SetTransform(D3DTS_VIEW, &m_MtxView);

	//プロジェクションマトリックスを初期化
	D3DXMatrixIdentity(&m_MtxProje);

	//if (Type == 0)
	//{
	//	//プロジェクションマトリックス作成
	//	D3DXMatrixPerspectiveFovLH(&m_MtxProje,
	//		D3DXToRadian(90.0f),
	//		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
	//		10.0f,
	//		10000.0f);
	//}
	//else
	{
		// プロジェクションマトリックスの作成(平行投影)
		D3DXMatrixOrthoLH(&m_MtxProje,					// プロジェクションマトリックス
			(float)SCREEN_WIDTH,								// 幅
			(float)SCREEN_HEIGHT,								// 高さ
			-100.0f,											// ニア
			2000.0f);											// ファー
	}
	//適用
	pDevice->SetTransform(D3DTS_PROJECTION, &m_MtxProje);
}


//----------------------------
//GetPos
//----------------------------
D3DXVECTOR3 *CCamera::GetPos()
{
	return &m_posV;
}

//----------------------------
//GetRot
//----------------------------
D3DXVECTOR3 * CCamera::GetRot()
{
	return &m_rot;
}

D3DXMATRIX  *CCamera::GetMtxProje()
{
	return &m_MtxProje;
}
D3DXMATRIX *CCamera::GetMtxView()
{
	return &m_MtxView;
}