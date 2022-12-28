//=============================================================================
//
// �I�u�W�F�N�gX���� [objectX.cpp]
// Author : KADO TAKUMA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "objectX.h"
#include "objectX_group.h"
#include "application.h"
#include "renderer.h"
#include "main.h"
#include "texture.h"
#include <assert.h>

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObjectX::CObjectX(CTaskGroup::EPriority nPriority) :
	CObject(nPriority),
	m_pParent(nullptr)
{
	//�I�u�W�F�N�g�̃^�C�v�Z�b�g����
	CObject::SetType(CObject::MODEL);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObjectX::~CObjectX()
{
}

//=============================================================================
// �I�u�W�F�N�g�̏�����
//=============================================================================
HRESULT CObjectX::Init()
{
	//���f���̓ǂݍ���
	LoadModel("BOX");
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I��
//=============================================================================
void CObjectX::Uninit()
{
	//�C���X�^���X�̉������
	Release();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V
//=============================================================================
void CObjectX::NormalUpdate()
{
}

//=============================================================================
// �I�u�W�F�N�g�̕`��
//=============================================================================
void CObjectX::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxParent;		// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXVECTOR3 rot = GetRot();
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXVECTOR3 pos = GetPos();
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);	// (���s��ړ��֐�(��1������x,y,z�����̈ړ��s����쐬))
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{
		mtxParent = m_pParent->GetMtxWorld();

		// �s��|���Z�֐�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
	}

	Projection();

	// ���[���h�}�g���b�N�X�̐ݒ�i���[���h���W�s��̐ݒ�j
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// ���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	// �ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �`��
// Author : �������l
// �T�v : �`����s��
//=============================================================================
void CObjectX::Draw(D3DXMATRIX mtxParent)
{
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScaling;

	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����̔��f
	D3DXVECTOR3 rot = GetRot();
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);	// �s���]�֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);			// �s��|���Z�֐� 

	// �ʒu�𔽉f
	D3DXVECTOR3 pos = GetPos();
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);		// �s��ړ��֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);	// �s��|���Z�֐�

	// �s��|���Z�֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	// �e�N�X�`���|�C���^�̎擾
	CTexture *pTexture = CApplication::GetInstance()->GetTexture();

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	if (m_pBuffMat != nullptr)
	{// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
		{// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->GetTexture("NULL"));

			// ���f���p�[�c�̕`��
			m_pMesh->DrawSubset(nCntMat);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, nullptr);
		}
	}

	// �ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// ���_�ő召�l�̌v�Z����
//=============================================================================
void CObjectX::CalculationVtx()
{
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;

	D3DXMatrixIdentity(&mtxWorld);

	// �����̔��f
	D3DXVECTOR3 rot = GetRot();
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);	// �s���]�֐�
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);					// �s��|���Z�֐�

	D3DXVec3TransformCoord(&m_MaxVtx, &m_MaxVtx, &mtxWorld);
	D3DXVec3TransformCoord(&m_MinVtx, &m_MinVtx, &mtxWorld);


	if (m_MaxVtx.x < m_MinVtx.x)
	{
		float change = m_MaxVtx.x;
		m_MaxVtx.x = m_MinVtx.x;
		m_MinVtx.x = change;
	}

	if (m_MaxVtx.y < m_MinVtx.y)
	{
		float change = m_MaxVtx.y;
		m_MaxVtx.y = m_MinVtx.y;
		m_MinVtx.y = change;
	}

	if (m_MaxVtx.z < m_MinVtx.z)
	{
		float change = m_MaxVtx.z;
		m_MaxVtx.z = m_MinVtx.z;
		m_MinVtx.z = change;
	}
}

//=============================================================================
// ��������
//=============================================================================
CObjectX * CObjectX::Create(D3DXVECTOR3 pos, CTaskGroup::EPriority nPriority)
{
	// �|�C���^�錾
	CObjectX *pObjectX = nullptr;

	// �C���X�^���X����
	pObjectX = new CObjectX(nPriority);

	if (pObjectX != nullptr)
	{// �|�C���^�����݂�������s
		pObjectX->Init();
		pObjectX->SetPos(pos);
		pObjectX->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{// �|�C���^����������������s
		assert(false);
	}

	// �|�C���^��Ԃ�
	return pObjectX;
}

//=============================================================================
// ���f���̓ǂݍ���
//=============================================================================
void CObjectX::LoadModel(const char *aFileName)
{
	CObjectXGroup *xGroup = CApplication::GetInstance()->GetObjectXGroup();
	m_pBuffMat = xGroup->GetBuffMat(aFileName);
	m_MaxVtx = xGroup->GetMaxVtx(aFileName);
	m_pMesh = xGroup->GetMesh(aFileName);
	m_MinVtx = xGroup->GetMinVtx(aFileName);
	m_NumMat = xGroup->GetNumMat(aFileName);
	SetSize(xGroup->GetSize(aFileName));
}

//=============================================================================
// ���s���e����
//=============================================================================
void CObjectX::Projection(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				// �}�e���A���f�[�^�ւ̃|�C���^

	// �ϐ��錾
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;
	D3DMATERIAL9 Material;

	// �V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	vecLight = -D3DXVECTOR4(0.2f, -0.5f, 0.3f, 0.0f);

	if (GetPos().y >= -20.0f)
	{
		pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	}

	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	D3DXMatrixShadow(&mtxShadow,&vecLight, &planeField);

	// ���[���h�}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	// ���[���h�}�g���b�N�X�̐ݒ�i���[���h���W�s��̐ݒ�j
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	// ���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		Material = pMat[nCntMat].MatD3D;

		Material.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		Material.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&Material);

		// ���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	// �ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �����蔻�� (���E,��,��O)
//=============================================================================
bool CObjectX::Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize)
{
	if (!m_isCollision)
	{
		return false;
	}

	D3DXVECTOR3 pos = GetPos();

	// �ϐ��錾
	bool bIsLanding = false;

	// ���f���̍��������蔻��
	if ((pPos->z - pSize->z * 0.5f < pos.z + m_MaxVtx.z) &&
		(pPos->z + pSize->z * 0.5f > pos.z + m_MinVtx.z) &&
		(pPosOld->x + pSize->x * 0.5f <= pos.x + m_MinVtx.x * 0.5f) &&
		(pPos->x + pSize->x * 0.5f > pos.x + m_MinVtx.x * 0.5f) &&
		(pPos->y + pSize->y > pos.y - m_MaxVtx.y * 0.5f) &&
		(pPos->y < pos.y + m_MaxVtx.y * 0.5f))
	{
		bIsLanding = true;
		pPos->x = pos.x + m_MinVtx.x * 0.5f - pSize->x * 0.5f;
	}
	// ���f���̉E�������蔻��
	if ((pPos->z - pSize->z * 0.5f < pos.z + m_MaxVtx.z) &&
		(pPos->z + pSize->z * 0.5f > pos.z + m_MinVtx.z) &&
		(pPosOld->x - pSize->x * 0.5f >= pos.x + m_MaxVtx.x * 0.5f) &&
		(pPos->x - pSize->x * 0.5f < pos.x + m_MaxVtx.x * 0.5f) &&
		(pPos->y + pSize->y > pos.y - m_MaxVtx.y * 0.5f) &&
		(pPos->y < pos.y + m_MaxVtx.y * 0.5f))
	{
		bIsLanding = true;
		pPos->x = pos.x + m_MaxVtx.x * 0.5f + pSize->x * 0.5f;
	}
	// ���f���̉��������蔻��
	if ((pPos->x - pSize->x * 0.5f < pos.x + m_MaxVtx.x) &&
		(pPos->x + pSize->x * 0.5f > pos.x + m_MinVtx.x) &&
		(pPosOld->z - pSize->z * 0.5f >= pos.z + m_MaxVtx.z * 0.5f) &&
		(pPos->z - pSize->z * 0.5f < pos.z + m_MaxVtx.z * 0.5f) &&
		(pPos->y + pSize->y > pos.y - m_MaxVtx.y * 0.5f) &&
		(pPos->y < pos.y + m_MaxVtx.y * 0.5f))
	{
		bIsLanding = true;
		pPos->z = pos.z + m_MaxVtx.z * 0.5f + pSize->z * 0.5f;
	}
	// ���f���̎�O�������蔻��
	if ((pPos->x - pSize->x * 0.5f < pos.x + m_MaxVtx.x) &&
		(pPos->x + pSize->x * 0.5f > pos.x + m_MinVtx.x) &&
		(pPosOld->z + pSize->z * 0.5f <= pos.z + m_MinVtx.z * 0.5f) &&
		(pPos->z + pSize->z * 0.5f > pos.z + m_MinVtx.z * 0.5f) &&
		(pPos->y + pSize->y > pos.y - m_MaxVtx.y * 0.5f) &&
		(pPos->y < pos.y + m_MaxVtx.y * 0.5f))
	{
		bIsLanding = true;
		pPos->z = pos.z + m_MinVtx.z * 0.5f - pSize->z * 0.5f;
	}

	// �l��Ԃ�
	return bIsLanding;
}

//=============================================================================
// �����蔻�� (���E,��,��O)
//=============================================================================
bool CObjectX::Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * inMaxVtx, D3DXVECTOR3 * inMinVtx)
{
	if (!m_isCollision)
	{
		return false;
	}

	D3DXVECTOR3 pos = GetPos();

	// �ϐ��錾
	bool bIsLanding = false;

	// ���f���̏��グ����
	if ((pPos->y + 20.0f > pos.y + m_MaxVtx.y))
	{
		return bIsLanding;
	}

	// ���f���̍��������蔻��
	if ((pPos->z + inMinVtx->z < pos.z + m_MaxVtx.z) &&
		(pPos->z + inMaxVtx->z > pos.z + m_MinVtx.z) &&
		(pPosOld->x + inMaxVtx->x  <= pos.x + m_MinVtx.x) &&
		(pPos->x + inMaxVtx->x > pos.x + m_MinVtx.x) &&
		(pPos->y + inMaxVtx->y > pos.y + m_MinVtx.y) &&
		(pPos->y < pos.y + m_MaxVtx.y))
	{
		bIsLanding = true;
		pPos->x = pos.x + m_MinVtx.x + inMinVtx->x - 5.0f;
	}

	// ���f���̉E�������蔻��
	if ((pPos->z + inMinVtx->z < pos.z + m_MaxVtx.z) &&
		(pPos->z + inMaxVtx->z > pos.z + m_MinVtx.z) &&
		(pPosOld->x + inMinVtx->x >= pos.x + m_MaxVtx.x) &&
		(pPos->x + inMinVtx->x < pos.x + m_MaxVtx.x) &&
		(pPos->y + inMaxVtx->y > pos.y + m_MinVtx.y) &&
		(pPos->y < pos.y + m_MaxVtx.y))
	{
		bIsLanding = true;
		pPos->x = pos.x + m_MaxVtx.x + inMaxVtx->x;
		pPos->x -= 0.1f;
	}

	// ���f���̉��������蔻��
	if ((pPos->x + inMinVtx->x < pos.x + m_MaxVtx.x) &&
		(pPos->x + inMaxVtx->x > pos.x + m_MinVtx.x) &&
		(pPosOld->z + inMinVtx->z >= pos.z + m_MaxVtx.z) &&
		(pPos->z + inMinVtx->z < pos.z + m_MaxVtx.z) &&
		(pPos->y + inMaxVtx->y > pos.y + m_MinVtx.y) &&
		(pPos->y < pos.y + m_MaxVtx.y))
	{
		bIsLanding = true;
		pPos->z = pos.z + m_MaxVtx.z + inMaxVtx->z;
	}

	// ���f���̎�O�������蔻��
	if ((pPos->x + inMinVtx->x < pos.x + m_MaxVtx.x) &&
		(pPos->x + inMaxVtx->x > pos.x + m_MinVtx.x) &&
		(pPosOld->z + inMaxVtx->z <= pos.z + m_MinVtx.z) &&
		(pPos->z + inMaxVtx->z > pos.z + m_MinVtx.z) &&
		(pPos->y + inMaxVtx->y > pos.y + m_MinVtx.y) &&
		(pPos->y < pos.y + m_MaxVtx.y))
	{
		bIsLanding = true;
		pPos->z = pos.z + m_MinVtx.z + inMinVtx->z - 5.0f;
		pPos->z -= 0.1f;
	}

	// �l��Ԃ�
	return bIsLanding;
}

//=============================================================================
// �����蔻�� (�㑤)
//=============================================================================
bool CObjectX::UpCollision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize, D3DXVECTOR3 * pMove)
{
	if (!m_isCollision)
	{
		return false;
	}

	// �ϐ��錾
	bool bIsLanding = false;

	D3DXVECTOR3 pos = GetPos();
	// ���f���̏㑤�����蔻��
	if ((pPos->z - pSize->z * 0.5f < pos.z + m_MaxVtx.z) &&
		(pPos->z + pSize->z * 0.5f > pos.z + m_MinVtx.z) &&
		(pPos->x - pSize->x * 0.5f < pos.x + m_MaxVtx.x) &&
		(pPos->x + pSize->x * 0.5f > pos.x + m_MinVtx.x) &&
		(pPos->y <= pos.y + m_MaxVtx.y))
	{
		bIsLanding = true;
		pPos->y = pos.y + m_MaxVtx.y;
		if (pPos->y == pPosOld->y)
		{
			pMove->y = 0.0f;
		}
	}

	// �l��Ԃ�
	return bIsLanding;
}

bool CObjectX::UpCollision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * inMaxVtx, D3DXVECTOR3 * inMinVtx, D3DXVECTOR3 * pMove)
{
	if (!m_isCollision)
	{
		return false;
	}

	// �ϐ��錾
	bool bIsLanding = false;

	D3DXVECTOR3 pos = GetPos();
	// ���f���̏㑤�����蔻��
	if ((pPos->z + inMinVtx->z < pos.z + m_MaxVtx.z) &&
		(pPos->z + inMaxVtx->z > pos.z + m_MinVtx.z) &&
		(pPos->x + inMinVtx->x < pos.x + m_MaxVtx.x) &&
		(pPos->x + inMaxVtx->x > pos.x + m_MinVtx.x) &&
		(pPos->y <= pos.y + m_MaxVtx.y))
	{
		bIsLanding = true;
		pPos->y = pos.y + m_MaxVtx.y;
		if (pPos->y == pPosOld->y)
		{
			pMove->y = 0.0f;
		}
	}

	// �l��Ԃ�
	return bIsLanding;
}
