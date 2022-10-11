//**************************************************
//
// ���� ( �^�C�g�� )
// Author : hamada ryuuga
//
//**************************************************
#ifndef _TITLE_H_
#define _TITLE_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "main.h"
#include "object2d.h"
#include "mode.h"

//-----------------------------------------------------------------------------
// �O���錾
//-----------------------------------------------------------------------------
class CBg;
class CPlayer;
class CEnemy;
class C3dpolygon;

//=============================================================================
// �^�C�g���N���X
//=============================================================================
class CTitle :public CMode
{
	// ���(���[�h)�̎��
	enum MODE
	{
		MODE_GAME = 0,		// �Q�[�����	
		MODE_TUTORIAL,		// �`���[�g���A�����
		MODE_RANKING,		// �����L���O���
		MODE_END,			// �I��
		MODE_MAX
	};

public:
	CTitle();
	~CTitle() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	
private:
	CPlayer* m_pPlayer;
	CEnemy* m_pEnemy[10];
	CBg* m_pBg[4];
	C3dpolygon* m_p3dpolygon[4];
	CObject2d* m_object2d[4];
	CObject2d* m_list[2];
	CObject2d* fade;
	int m_addX;
	int m_addY;
	MODE NextMode;
	bool Sizcontroller;
	bool ModeSelect;
	float m_alpha;
};

#endif