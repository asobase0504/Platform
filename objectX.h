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
	explicit CObjectX(int nPriority = 2);
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

	// Setter
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }	// ���[���h�}�g���b�N�X�̃Z�b�^�[
	void SetMaxVtx(D3DXVECTOR3 Maxvtx);			// ���_�ő�l�ݒ菈��
	void SetMinVtx(D3DXVECTOR3 Minvtx);			// ���_�ŏ��l�ݒ菈��
	void SetParent(CObjectX* inParent) { m_pParent = inParent; }		// �e���f���̏��
	void SetCollisionFlag(bool inFlag) { m_isCollision = inFlag; }

	// Getter
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }		// ���[���h�}�g���b�N�X�̃Q�b�^�[
	D3DXVECTOR3 GetMaxVtx(void) { return m_MaxVtx; }	// ���_�ő�l�擾����
	D3DXVECTOR3 GetMinVtx(void) { return m_MinVtx; }	// ���_�ŏ��l�擾����
	CObjectX* GetParent(void) { return m_pParent; }		// �e���f���̏��
	bool IsCollision() { return m_isCollision; }

	static CObjectX *Create(D3DXVECTOR3 pos, int nPriority);	// ��������
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
	D3DXCOLOR m_col;			// �F
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;			// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	// �}�e���A�����ւ̃|�C���^
	DWORD m_NumMat;				// �}�e���A�����̐�
								
	CObjectX *m_pParent;		// �e���f���̏��
	bool m_isCollision;			// �����蔻�肪�K�v��
};
#endif