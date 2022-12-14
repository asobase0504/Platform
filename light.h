//=============================================================================
// 
// ライトの作成(ヘッダーファイル)
// Author HAMAD
// 
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "task.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define LIGTH_MAX	(5)

//=============================================================================
// ライトクラス
//=============================================================================
class CLight : public CTask
{
public:
	CLight();
	~CLight();
	HRESULT Init();
	void Uninit();
	void Update();
		
	void Set(D3DLIGHTTYPE type, D3DXCOLOR col, D3DXVECTOR3 vec, int nNum);
private:
	 D3DLIGHT9 m_light[LIGTH_MAX];	//ライト情報
};
#endif // !_LIGHT_H_
