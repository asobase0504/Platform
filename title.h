//=============================================================================
//
// ���� ( �^�C�g�� )
// Author : hamada ryuuga
//
//=============================================================================
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
class CCamera;
class CLight;
class CParticleManager;

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

	static CParticleManager* GetPaticleManager() { return m_pPaticleManager; }

private:
	CCamera* m_pCamera;
	CLight* m_pLight;
	//CPlayer* m_pPlayer;
	//CEnemy* m_pEnemy[10];
	CBg* m_pBg[4];
	CObject2d* m_text[4];
	CObject2d* m_list[2];
	CObject2d* m_fade;
	int m_addX;
	int m_addY;
	MODE NextMode;
	bool Sizcontroller;
	bool ModeSelect;
	float m_alpha;

	static CParticleManager* m_pPaticleManager;	// �p�[�e�B�N���}�l�W���[

};

#endif