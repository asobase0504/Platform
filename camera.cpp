//=============================================================================
//
// �J����
// Author : Hamada Ryuuga
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "application.h"

#include "camera.h"
#include "input.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera(CTaskGroup::EPriority inPriority) :
	CTask(inPriority,CTaskGroup::EPushMethod::PUSH_TOP)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CCamera::Init(void)
{
	// ���_�@�����_�@������@�ݒ�
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
	m_posR = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_directionR = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	m_directionV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Speed = 1.0f;
	m_rotSpeed = 0.05f;

	D3DXVECTOR3 distPos = m_posR - m_posV;
	m_fDistance = sqrtf(distPos.x * distPos.x + distPos.z * distPos.z);
	m_fDistance = sqrtf(distPos.y * distPos.y + (m_fDistance * m_fDistance));

	m_rot.x = atan2f(distPos.z, distPos.y);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �X�V
//=============================================================================
void CCamera::Update(void)
{
}

//=============================================================================
// �X�V
//=============================================================================
void CCamera::Draw()
{
	Set(0);
}

//=============================================================================
// �`��
//=============================================================================
void CCamera::Set(int Type)
{
	m_Type = Type;
	LPDIRECT3DDEVICE9  pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̃|�C���^

	// �r���[�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_MtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_MtxView, &m_posV, &m_posR, &m_vecU);

	// �K�p
	pDevice->SetTransform(D3DTS_VIEW, &m_MtxView);

	// �v���W�F�N�V�����}�g���b�N�X��������
	D3DXMatrixIdentity(&m_MtxProject);

	//if (Type == 0)
	//{
	//	//�v���W�F�N�V�����}�g���b�N�X�쐬
	//	D3DXMatrixPerspectiveFovLH(&m_MtxProje,
	//		D3DXToRadian(90.0f),
	//		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
	//		10.0f,
	//		10000.0f);
	//}
	//else
	{
		// �v���W�F�N�V�����}�g���b�N�X�̍쐬(���s���e)
		D3DXMatrixOrthoLH(&m_MtxProject,					// �v���W�F�N�V�����}�g���b�N�X
			(float)SCREEN_WIDTH,							// ��
			(float)SCREEN_HEIGHT,							// ����
			-100.0f,										// �j�A
			2000.0f);										// �t�@�[
	}

	// �K�p
	pDevice->SetTransform(D3DTS_PROJECTION, &m_MtxProject);
}

//=============================================================================
// MtxProje
//=============================================================================
D3DXMATRIX* CCamera::GetMtxProje()
{
	return &m_MtxProject;
}

//=============================================================================
// MtxView
//=============================================================================
D3DXMATRIX* CCamera::GetMtxView()
{
	return &m_MtxView;
}
