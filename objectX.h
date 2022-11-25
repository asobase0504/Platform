//=============================================================================
//
// �I�u�W�F�N�gX���� [objectX.h]
// Author : KADO TAKUMA
// Author : Yuda Kaito
//
//=============================================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "object.h"

//=============================================================================
// �N���X�̒�`
//=============================================================================
class CObjectX : public CObject
{
public:
	//-------------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//-------------------------------------------------------------------------
	explicit CObjectX(CTaskGroup::EPriority nPriority = CTaskGroup::LEVEL_3D_1);
	~CObjectX() override;

	//-------------------------------------------------------------------------
	// �����o�[�֐�
	//-------------------------------------------------------------------------
	HRESULT Init() override;			// ����������
	void Uninit() override;				// �I������
	void Update() override;				// �X�V����
	void Draw() override;				// �`�揈��
	void Draw(D3DXMATRIX mtxParent);	// �`�揈��

	void CalculationVtx();				// ���_�ő召�l�̌v�Z����

	// ���[���h�}�g���b�N�X
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }	// �ݒ�
	const D3DXMATRIX& GetMtxWorld() { return m_mtxWorld; }				// �擾

	// ���_�ʒu
	void SetMaxVtx(const D3DXVECTOR3& Maxvtx) { m_MaxVtx = Maxvtx; }	// ���_�ő�l�ݒ�
	const D3DXVECTOR3& GetMaxVtx(void) { return m_MaxVtx; }				// ���_�ő�l�擾
	void SetMinVtx(const D3DXVECTOR3& Minvtx) { m_MaxVtx = Minvtx; }	// ���_�ő�l�ݒ�
	const D3DXVECTOR3& GetMinVtx(void) { return m_MinVtx; }				// ���_�ŏ��l�擾

	void SetParent(CObjectX* inParent) { m_pParent = inParent; }		// �e���f���̏��

	void SetCollisionFlag(bool inFlag) { m_isCollision = inFlag; }
	bool IsCollision() { return m_isCollision; }

	CObjectX* GetParent(void) const { return m_pParent; }		// �e���f���̏��

	static CObjectX *Create(D3DXVECTOR3 pos, CTaskGroup::EPriority nPriority = CTaskGroup::LEVEL_3D_1);	// ��������
	void LoadModel(const char *aFileName);						// ���f���̓ǂݍ��ݏ���
	void Projection(void);										// ���s���e����

	// Collision
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pSize);	// �����蔻�� (���E, ��, ��O)
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *inMaxVtx, D3DXVECTOR3 *inMinVtx);	// �����蔻�� (���E, ��, ��O)
	bool UpCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pSize, D3DXVECTOR3 *pMove);	// �����蔻�� (�㑤)
	bool UpCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *inMaxVtx, D3DXVECTOR3 *inMinVtx, D3DXVECTOR3 *pMove);	// �����蔻�� (�㑤)

private:
	//-------------------------------------------------------------------------
	// �����o�[�ϐ�
	//-------------------------------------------------------------------------
	D3DXVECTOR3 m_MinVtx;		// ���f���̒��_�ŏ��l
	D3DXVECTOR3 m_MaxVtx;		// ���f���̒��_�ő�l
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;			// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	// �}�e���A�����ւ̃|�C���^
	DWORD m_NumMat;				// �}�e���A�����̐�
								
	CObjectX *m_pParent;		// �e���f���̏��
	bool m_isCollision;			// �����蔻�肪�K�v��
};
#endif