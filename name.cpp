//============================
//
// NUME
// Author:hamada ryuuga
//
//============================

#include "name.h"
#include "manager.h"
#include "input.h"


//=============================================================================
// コンストラクト関数
//=============================================================================
CName::CName(int list) : CObject2d(list)
{
}

//=============================================================================
// デストラクト関数
//=============================================================================
CName::~CName()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CName::Init()
{
	CObject2d::Init();
	CObject2d::SetTexture(CTexture::TEXTURE_ALPHABET);
	color = PositionVec4(1.0f, 1.0f, 1.0f, 1.0f);

	m_divisionX = 7;
	m_divisionY = 4;
	m_divisionMAX = m_divisionX*m_divisionY;
	m_type = A;
	SetColar(D3DXCOLOR(0.8f, 0.0f, 0.0f, 1.0f));
	int X = m_type%m_divisionX;
	int Y = m_type/m_divisionX;
	float DivisionX = (1.0f / m_divisionX);
	float DivisionY = (1.0f / m_divisionY);

	m_isMove = true;

	SetTex(PositionVec4(
		DivisionX*X,
		DivisionX*X + DivisionX,
		DivisionY*Y,
		DivisionY*Y + DivisionY));

	

	return S_OK;
}

//=============================================================================
// 破棄関数
//=============================================================================
void CName::Uninit()
{
	CObject2d::Uninit();
}


//=============================================================================
// 更新関数
//=============================================================================
void CName::Update()
{
	CObject2d::Update();

	CInput *CInputpInput = CInput::GetKey();

	if (m_isMove)
	{
		if (CInputpInput->Trigger(CInput::KEY_RIGHT))
		{
			int nextType = m_type + 1;
			if (nextType > MAX)
			{
				nextType = 0;
			}
		
			switch (nextType/4)
			{
			case 0:
				SetColar(D3DXCOLOR(0.8f, 0.0f, 0.0f, 1.0f));
				break;
			case 1:
				SetColar(D3DXCOLOR(0.8f, 0.0f, 0.8f, 1.0f));
				break;
			case 2:
				SetColar(D3DXCOLOR(0.0f, 0.0f, 0.8f, 1.0f));
				
				break;
			case 3:
				SetColar(D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f));
				break;
			case 4:
				SetColar(D3DXCOLOR(0.0f, 0.8f, 0.0f, 1.0f));
				break;
			case 5:
				SetColar(D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f));
				break;
			case 6:
				SetColar(D3DXCOLOR(0.8f, 0.8f, 0.0f, 1.0f));
				break;
			default:
				SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}
			SetAlphabet((EAlphabet)nextType);

		}
		if (CInputpInput->Trigger(CInput::KEY_LEFT))
		{
			int nextType = m_type - 1;
			if (nextType <= -1)
			{
				nextType = 26;
			}
			switch (nextType / 4)
			{
			case 0:
				SetColar(D3DXCOLOR(0.8f, 0.0f, 0.0f, 1.0f));
				break;
			case 1:
				SetColar(D3DXCOLOR(0.8f, 0.0f, 0.8f, 1.0f));
				break;
			case 2:
				SetColar(D3DXCOLOR(0.0f, 0.0f, 0.8f, 1.0f));

				break;
			case 3:
				SetColar(D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f));
				break;
			case 4:
				SetColar(D3DXCOLOR(0.0f, 0.8f, 0.0f, 1.0f));
				break;
			case 5:
				SetColar(D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f));
				break;
			case 6:
				SetColar(D3DXCOLOR(0.8f, 0.8f, 0.0f, 1.0f));
				break;
			default:
				SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}
			SetAlphabet((EAlphabet)nextType);
		}
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void CName::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2d::Draw();

	// 新規深度値 <= Zバッファ深度値 (初期設定)
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// αテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 生成関数
//=============================================================================
CName *CName::Create()
{
	CName * pObject = nullptr;
	pObject = new CName(1);

	if (pObject != nullptr)
	{
		pObject->Init();

		pObject->SetTexture(CTexture::TEXTURE_ALPHABET);
	}

	return pObject;
}

//=============================================================================
// EAlphabet変更する関数
//=============================================================================
void CName::SetAlphabet(const EAlphabet Alphabet)
{
	m_type = Alphabet;

	switch (m_type / 4)
	{
	case 0:
		SetColar(D3DXCOLOR(0.8f, 0.0f, 0.0f, 1.0f));
		break;
	case 1:
		SetColar(D3DXCOLOR(0.8f, 0.0f, 0.8f, 1.0f));
		break;
	case 2:
		SetColar(D3DXCOLOR(0.0f, 0.0f, 0.8f, 1.0f));
		break;
	case 3:
		SetColar(D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f));
		break;
	case 4:
		SetColar(D3DXCOLOR(0.0f, 0.8f, 0.0f, 1.0f));
		break;
	case 5:
		SetColar(D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f));
		break;
	case 6:
		SetColar(D3DXCOLOR(0.8f, 0.8f, 0.0f, 1.0f));
		break;
	default:
		SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	}
	int X = m_type%m_divisionX;
	int Y = m_type / m_divisionX;
	float DivisionX = (1.0f / m_divisionX);
	float DivisionY = (1.0f / m_divisionY);

	SetTex(PositionVec4(
		DivisionX*X,
		DivisionX*X + DivisionX,
		DivisionY*Y,
		DivisionY*Y + DivisionY));
}

//=============================================================================
// 動くか動くかないか
//=============================================================================
void CName::SetMoveSwitch(bool move)
{
	m_isMove = move;
}

//=============================================================================
// Alphabet取得する関数
//=============================================================================
CName::EAlphabet CName::GetAlphabet()
{
	return m_type;
}
