//=============================================================================
//
// �t�F�[�h
// Author : Hamada Ryuuga
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "object2d.h"

//-----------------------------------------------------------------------------
// �O���錾
//-----------------------------------------------------------------------------
class  CMotion;

//=============================================================================
// �t�F�[�h�N���X
//=============================================================================
class CFade : public CObject2d
{

public:
	CFade();
	~CFade();

	//���(���[�h)�̎��
	enum FADE
	{
		FADEIN = 0,
		FADEOUT,
		FADENON,
		FADEMAX
	};

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CFade* Create();
	void CFade::NextMode(CManager::MODE nextMode);
	FADE* GetFade() { return& fade; }

private:
	float m_fadeSp;
	float m_fadeSet;
	bool m_bake;
	CManager::MODE m_nextMode;
	FADE fade;
};
#endif