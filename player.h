//============================
//
// �v���C���[�ݒ�w�b�^�[
// Author:hamada ryuuga
//
//============================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "motion.h"
#include "renderer.h"
#include "motion_model3D.h"

class CMotion;

class CPlayer : public CMotionModel3D
{
public:
	//model�f�[�^�̍\����//
	struct MODELDATAPLAYER
	{
		int key;		// ���ԊǗ�
		int nowKey;		// ���̃L�[
		int loop;		// ���[�v���邩�ǂ���[0:���[�v���Ȃ� / 1 : ���[�v����]
		int num_key;  	// �L�[��
		/*MyKeySet KeySet[MAX_KEY];*/
	};

public:
	static const int MAXLIFE = 300;
	static const float ATTENUATION;		// �����W��
	static const float SPEED;			// �X�s�[�h
	static const float WIDTH;			// ���f���̔��a
	static const int MAX_PRAYER;		// �ő吔
	static const int MAX_MOVE;			// �A�j���[�V�����̍ő吔
	static const int INVINCIBLE;		// ���G����
	static const int MAX_MODELPARTS = 9;
	
public:
	CPlayer();
	~CPlayer();

	HRESULT Init()override;	// ������
	void Uninit()override;	// �j��
	void NormalUpdate()override;	// �X�V
	void Draw()override;	// �`��

	static CPlayer *Create();

private:
	
	void Move();		// �ړ�
	void TitleMove();
	void ResetMove();
	void TutorialMove();	//�����Z�b�g
	int m_Pow;
	float m_MoveSpeed;
private:
};
#endif
