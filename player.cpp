//=============================================================================
//
// �v���C���[�ݒ�
// Author:hamada ryuuga
// Author:Yuda Kaito
//
//=============================================================================

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
// static�ϐ�
//-----------------------------------------------------------------------------
const float CPlayer::ATTENUATION = 0.5f;	// �ړ������W��
const float CPlayer::SPEED = 1.0f;			// �ړ���
const float CPlayer::WIDTH = 10.0f;			// ���f���̔��a
const int CPlayer::MAX_PRAYER = 16;			// �ő吔
const int CPlayer::MAX_MOVE = 9;			// �A�j���[�V�����̍ő吔
const int CPlayer::INVINCIBLE = 30;			// ���G����

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
CPlayer::CPlayer()
{
}

//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CPlayer::~CPlayer()
{

}

//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------
HRESULT CPlayer::Init()
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObjectX::Init();
	//CObjectX::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Data/system/Gon/Fox.txt");
	D3DXVECTOR3	Size(2.0f, 2.0f, 2.0f);
	m_MoveSpeed = 7.0f;
	AddRotY(-D3DX_PI * 0.5f);
	SetSize(Size);
	return S_OK;
}

//-----------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------
void CPlayer::Uninit()
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObjectX::Uninit();
}

//-----------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------
void CPlayer::NormalUpdate()
{
	Move();	//�����Z�b�g	

	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObjectX::Update();
}

//-----------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------
void CPlayer::Draw()
{
	CObjectX::Draw();
}

//-----------------------------------------------------------------------------
// create
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
// �ړ�
//-----------------------------------------------------------------------------
void CPlayer::Move()
{
	CInput *CInputpInput = CInput::GetKey();
	D3DXVECTOR3 Camerarot = CRenderer::GetInstance()->GetCamera()->GetRot();
	float consumption = 0.0f;

	D3DXVECTOR3 move = GetMove();

	if (CInputpInput->Press(CInput::KEY_RIGHT))
	{
		move.x += sinf(D3DX_PI * 0.5f + Camerarot.y) * SPEED * m_MoveSpeed;
		move.z += cosf(D3DX_PI * 0.5f + Camerarot.y) * SPEED * m_MoveSpeed;
		//consumption = m_rotMove.x + (D3DX_PI*0.5f) - m_rot.y + Camerarot->y;
	}
	if (CInputpInput->Press(CInput::KEY_LEFT))
	{
		move.x += sinf(-D3DX_PI * 0.5f + Camerarot.y) * SPEED * m_MoveSpeed;
		move.z += cosf(-D3DX_PI * 0.5f + Camerarot.y) * SPEED * m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_DOWN))
	{	
		move.y -= m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_UP))
	{	
		move.y += m_MoveSpeed;
	}

	float posY = GetPos().y;
	float posX = GetPos().x;
	if (posY <= -SCREEN_HEIGHT * 0.5f + 20.0f)
	{
		SetPosY((-SCREEN_HEIGHT * 0.5f) + 20.0f);
	}

	if (posY >= SCREEN_HEIGHT * 0.5f - 100.0f)
	{
		SetPosY(SCREEN_HEIGHT * 0.5f - 100.0f);
	}
	if (posX <= -SCREEN_WIDTH * 0.5f + 100.0f)
	{
		SetPosX(-SCREEN_WIDTH*0.5f + 100.0f);
	}
	if (posX >= SCREEN_WIDTH * 0.5f - 80.0f)
	{
		SetPosX(SCREEN_WIDTH*0.5f - 80.0f);
	}

	move.x += (0.0f - move.x) * ATTENUATION;	//�i�ړI�̒l-���݂̒l�j�������W��
	move.z += (0.0f - move.z) * ATTENUATION;	//�i�ړI�̒l-���݂̒l�j�������W��
	move.y += (0.0f - move.y) * ATTENUATION;	//�i�ړI�̒l-���݂̒l�j�������W��

	//���K��
	NormalizeAngle(consumption);

	//���Z�ݒ�i�����j
	AddRotY(consumption * ATTENUATION);	// (�ړI�̒l-���݂̒l�j�������W��

	//���K��
	float rotY = GetRot().y;
	NormalizeAngle(rotY);
	SetRotY(rotY);
}
