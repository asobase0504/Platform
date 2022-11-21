//=============================================================================
//
// �p�[�c�N���X(parts.h)
// Author : �������l
// �T�v : �p�[�c�������s��
//
//=============================================================================
#ifndef _PARTS_H_			// ���̃}�N����`������ĂȂ�������
#define _PARTS_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "objectX.h"
#include "main.h"

//=============================================================================
// �p�[�c�N���X
// Author : �������l
// �T�v : �p�[�c�������s���N���X
//=============================================================================
class CParts : public CObjectX
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CParts *Create();			// �p�[�c�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CParts();
	~CParts();

	// ���̈ʒu
	void SetPosOrigin(const D3DXVECTOR3 &posOrigin) { m_posOrigin = posOrigin; }	// Setter
	D3DXVECTOR3 GetPosOrigin() const { return m_posOrigin; }						// Getter

	// ���̌���
	void SetRotOrigin(const D3DXVECTOR3 &rotOrigin) { m_rotOrigin = rotOrigin; }	// Setter
	const D3DXVECTOR3& GetRotOrigin() { return m_rotOrigin; }						// Getter

	// �ړI�̈ʒu
	void SetPosDest(const D3DXVECTOR3 &posDest) { m_posDest = posDest; }			// Setter
	const D3DXVECTOR3& GetPosDest() { return m_posDest; }							// Getter

	// �ړI�̌���
	void SetRotDest(const D3DXVECTOR3 &rotDest) { m_rotDest = rotDest; }			// Setter
	const D3DXVECTOR3& GetRotDest() { return m_rotDest; }							// Getter

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	D3DXVECTOR3 m_posOrigin;	// ���̈ʒu
	D3DXVECTOR3 m_rotOrigin;	// ���̌���
	D3DXVECTOR3 m_posDest;		// �ړI�̈ʒu
	D3DXVECTOR3 m_rotDest;		// �ړI�̌���
};

#endif
