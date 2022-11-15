////============================
////
//// object3d�ݒ�
//// Author:hamada ryuuga
////
////============================
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <assert.h>
//
//#include "object3d.h"
//#include "camera.h"
//#include "motion.h"
//#include "application.h"
//#include "motion.h"
//
//#include "multiply.h"
//
//#include "fade.h"
//
////------------------------------------
//// const�����o�[�ϐ��̐錾
////------------------------------------
//int CObject3d::m_drop = 0;
//
////------------------------------------
//// �R���X�g���N�^
////------------------------------------
//CObject3d::CObject3d() :
//	m_posOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
//	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
//	m_rotMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
//	m_modelMin(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
//	m_modelMax(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
//	m_motionType(ANIME_NORMAL),
//	m_motionTypeOld(ANIME_NORMAL),
//	m_nMaxModelType(0),
//	m_nMaxModelParts(0),
//	m_nMaxMotion(0),
//	m_type(0),
//	m_shadow(0),
//	m_invincible(0),
//	m_consumption(0.0f),
//	m_bMotionBlend(false),
//	m_bMotion(false),
//	m_isLoop(false),
//	m_time(0),
//	m_nparts(0),
//	m_pow(0),
//	m_nMotion(0),
//	m_Damegeis(DAMEGE_NORMAL)
//{
//	//memset(&s_Player, NULL, sizeof(s_Player));
//	/*memset(&m_motion, 0, sizeof(m_motion));*/
//	// ���[���h�}�g���b�N�X�̏�����
//	// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
//
//}
//
////------------------------------------
//// �f�X�g���N�^
////------------------------------------
//CObject3d::~CObject3d()
//{
//	assert(m_pMotion == nullptr);
//}
//
////------------------------------------
//// ������
////------------------------------------
//HRESULT CObject3d::Init(void)
//{
//	D3DXVECTOR3 *Camerarot = CRenderer::GetInstance()->GetCamera()->GetRot();
//
//	m_ModelCollar = CMotion::NON;
//	m_damagecollar = 0;
//
//	//�J�����̃f�[�^�擾
//	m_rotMove = D3DXVECTOR3(D3DX_PI + Camerarot->y, D3DX_PI * 0.5f + Camerarot->y, 0.0f);
//
//	m_modelMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
//	m_modelMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
//
//	return S_OK;
//}
//
////------------------------------------
//// �I��
////------------------------------------
//void CObject3d::Uninit(void)
//{
//	m_pMotion->Uninit();
//	if (m_pMotion != nullptr)
//	{
//		delete m_pMotion;
//		m_pMotion = nullptr;
//	}
//	Release();
//}
//
////------------------------------------
//// �X�V
////------------------------------------
//void CObject3d::NormalUpdate(void)
//{
//	// ���݂̃��[�V�����ԍ��̕ۊ�
//	m_motionTypeOld = m_motionType;
//
//	if (m_motionTypeOld != m_motionType)
//	{// ���[�V�����^�C�v���ύX���ꂽ��
//		m_pMotion->CntReset((int)(m_motionTypeOld));
//		m_bMotionBlend = true;
//	}
//
//	if (m_bMotionBlend)
//	{// ���[�V�����u�����h���g�p���Ă�
//		m_bMotionBlend = m_pMotion->MotionBlend((int)(m_motionType));
//	}
//	else if (!m_bMotionBlend)
//	{// ���[�V�����u�����h���g�p���ĂȂ��ꍇ
//		m_bMotion = m_pMotion->PlayMotion((int)(m_motionType));
//	}
//
//	if (!m_bMotion)
//	{// �g�p���Ă郂�[�V�������Ȃ��ꍇ
//		m_motionType = ANIME_NORMAL;
//		m_isLoop = false;
//	}
//}
//
////------------------------------------
//// �`��
////------------------------------------
//void CObject3d::Draw(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
//	D3DXMATRIX mtxScale, mtxTrans, mtxRot;	// �v�Z�p�}�g���b�N�X
//	D3DMATERIAL9 marDef;
//
//	// ���[���h�}�g���b�N�X�̏�����
//	// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
//	D3DXMatrixIdentity(&m_mtxWorld);
//
//	// �傫���̔��f
//	// �s��g�k�֐�
//	D3DXMatrixScaling(&mtxScale, m_nScale.x, m_nScale.y, m_nScale.z);
//	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);
//
//	// �����𔽉f
//	// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
//	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
//	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
//
//	// �ʒu�𔽉f
//	// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
//	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
//	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
//
//	// �e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, NULL);
//
//	if (m_pMotion)
//	{
//		// �p�[�c�̕`��ݒ�
//		m_pMotion->SetParts(m_mtxWorld, m_ModelCollar);
//	}
//
//	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
//	pDevice->SetMaterial(&marDef);
//}
//
////------------------------------------
//// POS�����Z�b�g
////------------------------------------
//void CObject3d::SetPos(const D3DXVECTOR3 &pos)
//{
//	m_pos = pos;
//}
//
////------------------------------------
//// �ݒ�
////------------------------------------
//void CObject3d::Set(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot,  char * pFileName)
//{
//	// ���̏�����
//	m_pos = pos;											// �ʒu�̏�����
//	m_posOld = m_pos;										// �ߋ��ʒu�̏�����
//	m_rot = rot;											// �����̏�����
//	m_modelMin = D3DXVECTOR3(100.0f, 100.0f, 100.0f);		// ���_���W�̍ŏ��l
//	m_modelMax = D3DXVECTOR3(-100.0f, -100.0f, -100.0f);	// ���_���W�̍ő�l
//	m_mtxWorld = {};										// ���[���h�}�g���b�N�X
//	//m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړI�̌���
//	m_motionType = ANIME_NORMAL;							// �j���[�g�������[�V����
//	m_motionTypeOld = m_motionType;							// �j���[�g�������[�V����
//	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ړ���
//	m_bMotionBlend = false;									// ���[�V�����u�����h�̎g�p��
//
//	// ���[�V�������
//	m_pMotion = new CMotion(pFileName);
//	m_pMotion->Init();
//	assert(m_pMotion != nullptr);
//}
//
////------------------------------------
//// GetSize
////------------------------------------
//const D3DXVECTOR3 * CObject3d::GetSize() const
//{
//	return &m_nScale;
//}
//
////------------------------------------
////GetRot
////------------------------------------
//const D3DXVECTOR3 * CObject3d::GetRot() const
//{
//	return nullptr;
//}
//
////------------------------------------
//// SetSize
////------------------------------------
//void CObject3d::SetSize(D3DXVECTOR3 &Size)
//{
//	m_nScale = Size;
//}
//
////------------------------------------
//// SetRot
////------------------------------------
//void CObject3d::SetRot(D3DXVECTOR3 &Rot)
//{
//	m_rot = Rot;
//}
