//=============================================================================
//
// ���� ( �^�C�g�� )
// Author : Yuda Kaito
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
	// �J�ڐ�
	enum ESelectMode
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

	CParticleManager* GetPaticleManager() { return m_pPaticleManager; }

private:
	CCamera* m_pCamera;
	CLight* m_pLight;
	CParticleManager* m_pPaticleManager;	// �p�[�e�B�N���}�l�W���[
};
#endif