//=============================================================================
//
// �v���C���[�ݒ�w�b�^�[
// Author:hamada ryuuga
// Author: Yuda Kaito
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "motion_model3D.h"

//-----------------------------------------------------------------------------
// �v���C���[������o���郂�f��
//-----------------------------------------------------------------------------
class CPlayer : public CMotionModel3D
{
public:	// �萔
	static const float ATTENUATION;		// �����W��
	static const float SPEED;			// �X�s�[�h
	static const float WIDTH;			// ���f���̔��a
	static const int MAX_PRAYER;		// �ő吔
	static const int MAX_MOVE;			// �A�j���[�V�����̍ő吔
	static const int INVINCIBLE;		// ���G����
	
public:
	CPlayer();
	~CPlayer();

	HRESULT Init() override;		// ������
	void Uninit() override;			// �j��
	void NormalUpdate() override;	// �X�V
	void Draw() override;			// �`��

	static CPlayer *Create();

private: // �v���C�x�[�g�֐�
	void Move();		// �ړ�

private: // �����o�[�ϐ�
	float m_MoveSpeed;
};
#endif
