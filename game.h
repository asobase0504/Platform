//=============================================================================
//
// �Q�[����ʂ̃w�b�_�[
// Author:Hamada Ryuuga
//
//=============================================================================
#ifndef _GAME_H_		//���̃}�N������`����ĂȂ�������
#define _GAME_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "mode.h"

//-----------------------------------------------------------------------------
// �O���錾
//-----------------------------------------------------------------------------
class CMagicBox;
class CParticleManager;
class CPlayer;
class CPause; 

//=============================================================================
// �Q�[���N���X
//=============================================================================
class CGame : public CMode
{
public:
	CGame();
	~CGame();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// Getter
	static CMagicBox* GetMagicBox() { return m_pMagicBox; };
	static CParticleManager* GetParticleManager() { return m_pPaticleManager; }
	static CPlayer* GetPlayer() { return m_pPlayer; };
	static CPause* GetPause() { return m_pPause; };

private:
	static CMagicBox* m_pMagicBox;
	static CPlayer* m_pPlayer;
	static CParticleManager* m_pPaticleManager;	// �p�[�e�B�N���}�l�W���[
	static CPause *m_pPause;

	int m_gameCount;
	int m_speedUp;
};
#endif