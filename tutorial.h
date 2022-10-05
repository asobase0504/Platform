//=============================================================================
//
// TUTORIAL��ʂ̃w�b�_�[
// Author : Hamada Ryuuga
//
//=============================================================================
#ifndef _TUTORIAL_H_		//���̃}�N������`����ĂȂ�������
#define _TUTORIAL_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "main.h"
#include "object.h"
#include "object2d.h"

//-----------------------------------------------------------------------------
// �O���錾
//-----------------------------------------------------------------------------
class CPlayer;
class CEnemy;
class CBg;
class CMagicBox;
class CParticleManager;
class CMultiply;

//=============================================================================
// �`���[�g���A����ʂ̃N���X
//=============================================================================
class CTutorial :public CObject
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// Getter
	static CParticleManager* GetParticleManager() { return m_pPaticleManager; }
	static CMagicBox*GetMagicBox() { return m_pMagicBox; };
	static CPlayer * GetPlayer() { return m_pPlayer; };

private:
	CObject2d* m_pObject2d[4];
	CEnemy* m_pEnemy;
	CBg* m_pBg[4];
	CScore* m_pScore;

	static CParticleManager* m_pPaticleManager;	// �p�[�e�B�N���}�l�W���[
	static CMagicBox* m_pMagicBox;
	static CPlayer * m_pPlayer;
	int m_magic;
	int m_nextTaskCount;	// ���̃^�X�N�܂ł̃J�E���g

	// CLEAR�^�X�N�ꗗ�\
	bool m_isMoveClear;
	bool m_isAttackClear;
	bool m_isMagicClear;
	
};

#endif
