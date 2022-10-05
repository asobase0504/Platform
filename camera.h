//=============================================================================
//
// �J����
// Author : Hamada Ryuuga
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "renderer.h"

//-----------------------------------------------------------------------------
// �O���錾
//-----------------------------------------------------------------------------

//=============================================================================
// �t�F�[�h�N���X
//=============================================================================
class CCamera
{

public:
	CCamera();
	~CCamera();

	void Init();
	void Uninit();
	void Update();

	void Set(int Type);

	D3DXMATRIX *GetMtxProje();
	D3DXMATRIX *GetMtxView();
	D3DXVECTOR3 *GetPos();
	D3DXVECTOR3 *GetRot();

private:
	D3DXVECTOR3 m_posV;					// �ʒu
	D3DXVECTOR3 m_posVDest;
	D3DXVECTOR3 m_posR;					// �����_
	D3DXVECTOR3 m_posRDest;
	D3DXVECTOR3 m_vecU;					// �x�N�g��
	D3DXVECTOR3 m_directionV;			// ��]�̌����ʒu
	D3DXVECTOR3 m_directionR;			// ��]�̌��������_
	D3DXVECTOR3 m_rot;					// �ʒu��]
	D3DVIEWPORT9 m_viewport;			   
	D3DXMATRIX m_MtxProject;			// �v���W�F�N�V�����}�g���b�N�X//�|���S���̈ʒu���]�s�񂷂ׂĂ��߂Ă�i�j�J
	D3DXMATRIX m_MtxView;				// �r���[�}�g���b�N�X//�|���S���̈ʒu���]�s�񂷂ׂĂ��߂Ă�i�j�J
	float m_Speed;
	float m_rotSpeed;
	float m_rotSpeed2;
	float m_fDistance;					// ����
	float m_fDistanceY;
	int m_Type;

};

#endif		// _CAMERA_H_
