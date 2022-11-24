//============================
//
// �v���C���[�ݒ�
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "player.h"
#include "input.h"
#include "camera.h"
#include "motion.h"
#include "application.h"
#include "motion.h"
#include "particle_manager.h"
#include "utility.h"
#include "game.h"
#include "tutorial.h"

//------------------------------------
// static�ϐ�
//------------------------------------
const float CPlayer::ATTENUATION = 0.5f;	// 
const float CPlayer::SPEED = 1.0f;			// �ړ���
const float CPlayer::WIDTH = 10.0f;			// ���f���̔��a
const int CPlayer::MAX_PRAYER = 16;			// �ő吔
const int CPlayer::MAX_MOVE = 9;			// �A�j���[�V�����̍ő吔
const int CPlayer::INVINCIBLE = 30;		// ���G����

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CPlayer::CPlayer()
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CPlayer::~CPlayer()
{

}

//------------------------------------
// ������
//------------------------------------
HRESULT CPlayer::Init()
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObjectX::Init();
	//CObjectX::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Data/system/Gon/Fox.txt");
	D3DXVECTOR3	Size(2.0f, 2.0f, 2.0f);
	m_MoveSpeed = 7.0f;
	m_rot.y += (-D3DX_PI*0.5f);
	SetSize(Size);
	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CPlayer::Uninit()
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObjectX::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CPlayer::NormalUpdate()
{
	switch (*CApplication::GetInstance()->GetMode())
	{
	case CApplication::MODE_TITLE:
		TitleMove();	//�����Z�b�g
		break;
	case CApplication::MODE_GAME:
		Move();	//�����Z�b�g	
		break;
	case CApplication::MODE_RESULT:
		ResetMove();
		break;
	case CApplication::MODE_RANKING:
		break;
	case CApplication::MODE_TUTORIAL:
		TutorialMove();
		break;
	default:
		break;
	}

	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObjectX::Update();
}

//------------------------------------
// �`��
//------------------------------------
void CPlayer::Draw()
{
	CObjectX::Draw();
}

//------------------------------------
// create
//------------------------------------
CPlayer *CPlayer::Create()
{
	CPlayer * pObject = nullptr;
	pObject = new CPlayer;

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

//------------------------------------
// �����Z�b�g
//------------------------------------
void CPlayer::Move()
{
	CInput *CInputpInput = CInput::GetKey();
	D3DXVECTOR3 *Camerarot = CRenderer::GetInstance()->GetCamera()->GetRot();
	float consumption = 0.0f;

	if (CInputpInput->Press(CInput::KEY_RIGHT))
	{
		m_move.x += sinf(D3DX_PI * 0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(D3DX_PI * 0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		//consumption = m_rotMove.x + (D3DX_PI*0.5f) - m_rot.y + Camerarot->y;
	}
	if (CInputpInput->Press(CInput::KEY_LEFT))
	{
		m_move.x += sinf(-D3DX_PI * 0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(-D3DX_PI * 0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_DOWN))
	{	
		m_move.y -= m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_UP))
	{	
		m_move.y += m_MoveSpeed;
	}
	
	//�e�̃N���G�C�g
	if (CInputpInput->Press(CInput::KEY_SHOT))
	{
		
	}


 	else
	{
		m_Pow = 20;
	}

	if (m_pos.y <= -SCREEN_HEIGHT / 2 + 20.0f)
	{
		m_pos.y = (-SCREEN_HEIGHT / 2)+20.0f;
	}

	if (m_pos.y >= SCREEN_HEIGHT / 2 - 100.0f)
	{
		m_pos.y = SCREEN_HEIGHT / 2 - 100.0f;
	}
	if (m_pos.x <= -SCREEN_WIDTH / 2 + 100.0f)
	{
		m_pos.x = -SCREEN_WIDTH*0.5f + 100.0f;
	}
	if (m_pos.x >= SCREEN_WIDTH / 2 - 80.0f)
	{
		m_pos.x = SCREEN_WIDTH*0.5f - 80.0f;
	}

	m_move.x += (0.0f - m_move.x)*ATTENUATION;	//�i�ړI�̒l-���݂̒l�j�������W��
	m_move.z += (0.0f - m_move.z)*ATTENUATION;
	m_move.y += (0.0f - m_move.y)*ATTENUATION;

	m_pos += m_move;//�ړ������Z

	//���K��
	if ( consumption > D3DX_PI)
	{
		 consumption += D3DX_PI * 2.0f;
	}
	if ( consumption < -D3DX_PI)
	{
		 consumption += -D3DX_PI * 2.0f;
	}

	//���Z�ݒ�i�����j
	m_rot.y += (consumption)* ATTENUATION;//�ړI�̒l-���݂̒l�j�������W��

	 //���K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
}

//------------------------------------
// Title�̂Ƃ���Move
//------------------------------------
void CPlayer::TitleMove()
{

	D3DXVECTOR3 *Camerarot = CRenderer::GetInstance()->GetCamera()->GetRot();
	float consumption = 0.0f;
	
	m_move.x += sinf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	m_move.z += cosf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	//consumption = m_rotMove.x + -(D3DX_PI*0.5f) - m_rot.y + Camerarot->y;
	
	m_pos.y = 250.0f;

	m_move.x += (0.0f - m_move.x)*ATTENUATION;//�i�ړI�̒l-���݂̒l�j�������W��
	m_move.z += (0.0f - m_move.z)*ATTENUATION;
	m_move.y += (0.0f - m_move.y)*ATTENUATION;

	m_pos += m_move;//�ړ������Z

					//���K��
	if (consumption > D3DX_PI)
	{
		consumption += D3DX_PI * 2.0f;
	}
	if (consumption < -D3DX_PI)
	{
		consumption += -D3DX_PI * 2.0f;
	}

	//���Z�ݒ�i�����j
	m_rot.y += (consumption)* ATTENUATION;//�ړI�̒l-���݂̒l�j�������W��

										  //���K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}



	if (m_pos.x <= -SCREEN_WIDTH*0.5f-100.0f)
	{
		m_pos.x = SCREEN_WIDTH*0.5f;
	}
	
	
}

//------------------------------------
// Reset�̂Ƃ���Move
//------------------------------------
void CPlayer::ResetMove()
{

	D3DXVECTOR3 *Camerarot = CRenderer::GetInstance()->GetCamera()->GetRot();
	float consumption = 0.0f;

	m_move.x += sinf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	m_move.z += cosf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	//consumption = m_rotMove.x + -(D3DX_PI*0.5f) - m_rot.y + Camerarot->y;

	m_pos.y = 250.0f;

	m_move.x += (0.0f - m_move.x)*ATTENUATION;//�i�ړI�̒l-���݂̒l�j�������W��
	m_move.z += (0.0f - m_move.z)*ATTENUATION;
	m_move.y += (0.0f - m_move.y)*ATTENUATION;

	m_pos += m_move;//�ړ������Z

					//���K��
	if (consumption > D3DX_PI)
	{
		consumption += D3DX_PI * 2.0f;
	}
	if (consumption < -D3DX_PI)
	{
		consumption += -D3DX_PI * 2.0f;
	}

	//���Z�ݒ�i�����j
	m_rot.y += (consumption)* ATTENUATION;//�ړI�̒l-���݂̒l�j�������W��

										  //���K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}



	if (m_pos.x <= -SCREEN_WIDTH*0.5f - 100.0f)
	{
		m_pos.x = SCREEN_WIDTH*0.5f;
	}


}

//------------------------------------
// Move
//------------------------------------
void CPlayer::TutorialMove()	//�����Z�b�g
{
	CInput *CInputpInput = CInput::GetKey();
	D3DXVECTOR3 *Camerarot = CRenderer::GetInstance()->GetCamera()->GetRot();
	float consumption = 0.0f;

	if (CInputpInput->Press(CInput::KEY_RIGHT))
	{
		m_move.x += sinf(D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		//consumption = m_rotMove.x + (D3DX_PI*0.5f) - m_rot.y + Camerarot->y;
	}
	if (CInputpInput->Press(CInput::KEY_LEFT))
	{
		m_move.x += sinf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_DOWN))
	{
		m_move.y -= m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_UP))
	{
		m_move.y += m_MoveSpeed;
	}

	//�e�̃N���G�C�g
	if (CInputpInput->Press(CInput::KEY_SHOT))
	{
	
	}

	if (m_pos.y <= -SCREEN_HEIGHT / 2 + 20.0f)
	{
		m_pos.y = (-SCREEN_HEIGHT / 2) + 20.0f;
	}

	if (m_pos.y >= SCREEN_HEIGHT / 2 - 100.0f)
	{
		m_pos.y = SCREEN_HEIGHT / 2 - 100.0f;
	}
	if (m_pos.x <= -SCREEN_WIDTH / 2 + 100.0f)
	{
		m_pos.x = -SCREEN_WIDTH*0.5f + 100.0f;
	}
	if (m_pos.x >= SCREEN_WIDTH / 2 - 80.0f)
	{
		m_pos.x = SCREEN_WIDTH*0.5f - 80.0f;
	}

	m_move.x += (0.0f - m_move.x)*ATTENUATION;//�i�ړI�̒l-���݂̒l�j�������W��
	m_move.z += (0.0f - m_move.z)*ATTENUATION;
	m_move.y += (0.0f - m_move.y)*ATTENUATION;

	m_pos += m_move;//�ړ������Z

	//���K��
	if (consumption > D3DX_PI)
	{
		consumption += D3DX_PI * 2.0f;
	}
	if (consumption < -D3DX_PI)
	{
		consumption += -D3DX_PI * 2.0f;
	}

	//���Z�ݒ�i�����j
	m_rot.y += (consumption)* ATTENUATION;//�ړI�̒l-���݂̒l�j�������W��

	//���K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}


}