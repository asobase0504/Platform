//============================
//
//  フェード
// Author:hamada ryuuga
//
//============================
#ifndef _FADE_H_
#define _FADE_H_

#include "manager.h"
#include "renderer.h"
#include "object2d.h"

class  CMotion;

class CFade : public CObject2d
{

public:
	CFade();
	~CFade();


	//画面(モード)の種類
	enum FADE
	{
		FADEIN = 0,		
		FADEOUT,			
		FADENON,
		FADEMAX
	};

	HRESULT Init()override;	// 初期化
	void Uninit()override;	// 破棄
	void Update()override;	// 更新
	void Draw()override;	// 描画
	static CFade* Create();
	void CFade::NextMode(CManager::MODE nextMode);
	FADE * GetFade() { return&fade; };
private:

	float m_FadeSp;
	float m_FadeSet;
	bool m_Bake;
	CManager::MODE m_NextMode;
	FADE fade;

};
#endif