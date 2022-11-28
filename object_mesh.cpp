//=============================================================================
//
// ���b�V���ݒ�(�܂�����)
// Author:hamada ryuuga
//
//=============================================================================

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "object_mesh.h"
#include "application.h"
#include "utility.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <nlohmann/json.hpp>
#include <string>
#include <stdio.h>
#include <tchar.h>
#include <locale.h>
#include <sstream>

nlohmann::json JMesh;//���X�g�̐���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMesh::CMesh(CTaskGroup::EPriority nPriority) :
	CObjectPolygon3D(nPriority),
	m_xsiz(0),						// �ʐ�
	m_zsiz(0),						// �ʐ�
	m_vtxCountX(0),					// �ӂ̒��_��
	m_vtxCountZ(0),					// �ӂ̒��_��
	m_vtx(0),						// ���_��
	m_index(0),						// �C���f�b�N�X
	m_polygonCount(0),
	m_NowMesh(0),
	m_Number(0),
	m_Type(0),
	m_move(5.0f),
	IsCollision(true)
{
	m_MeshSize = { 100.0f,0.0f,100.0f };
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMesh::~CMesh()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMesh::Init(void)
{
	// ����������
	m_pVtxBuff = nullptr;		// ���_�o�b�t�@�[�ւ̃|�C���^
	m_pIdxBuff = nullptr;		// �C���f�b�N�X�o�b�t�@
	
	//m_pFileName = nullptr;

	//�e�N�X�`���̓ǂݍ���

	SetMesh(10);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMesh::Uninit(void)
{
	// ���_�o�b�t�@�[�̉��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMesh::NormalUpdate(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CMesh::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	//���C�g�ݒ�false�ɂ���ƃ��C�g�ƐH���Ȃ�
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h���W�s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@�ݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̎擾
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(GetTexture()));

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_vtx, 0, m_polygonCount);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// Create�֐�
//=============================================================================
CMesh* CMesh::Create()
{
	CMesh * pObject = nullptr;
	pObject = new CMesh;

	if (pObject != nullptr)
	{
		
		pObject->Init();

	}
	return pObject;
}


//=============================================================================
// �����蔻��
// Author: hamada ryuuga
// Aythor: Yuda Kaito
//=============================================================================
bool CMesh::CollisionMesh(D3DXVECTOR3 *pPos)
{

	bool bIsLanding = false;
	const int nTri = 3;
	// ���_���W�����b�N
	VERTEX_3D* pVtx = NULL;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxWorld;

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
	D3DXMatrixIdentity(&mtxWorld);

	// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	// �s��|���Z�֐�(��2�����~��3�������P�����Ɋi�[)
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	for (int nCnt = 0; nCnt < m_polygonCount; nCnt++)
	{
		D3DXVECTOR3 posLineVec[nTri];

		posLineVec[0] = pVtx[pIdx[nCnt + 0]].pos;
		posLineVec[1] = pVtx[pIdx[nCnt + 1]].pos;
		posLineVec[2] = pVtx[pIdx[nCnt + 2]].pos;

		if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
			(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
			(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
		{//�k�ރ|���S�����Ȃ�
			continue;
		}

		for (int i = 0; i < nTri; i++)
		{//�x�N�g���R���W���}�g���b�N�X�ŕϊ�����i��Z�j
			D3DXVec3TransformCoord(&posLineVec[i], &posLineVec[i], &mtxWorld);
		}

		int  LineCout = 0;

		for (int i = 0; i < nTri; i++)
		{
			//�x�N�g��S2 V2												
			D3DXVECTOR3 vecWall = posLineVec[(i + 1) % nTri] - posLineVec[i];

			//�x�N�g�����݂�POS�Ǝn�_�܂ł̋���
			D3DXVECTOR3 vecPos = *pPos - posLineVec[i];

			//�O�όv�Z//�ӂP
			float vecLine = Vec2Cross(&vecPos, &vecWall);

			//�O�p�̒��ɓ����Ă�Ƃ��̔�������ɂ���ĉE�����������Ⴄ���ߔ�����p�ӂ���
			if ((nCnt % 2 == 0 && vecLine >= 0.0f) || (nCnt % 2 != 0 && vecLine <= 0.0f))
			{
				LineCout++;
			}
			else
			{
				break;
			}
		}
		if (LineCout == nTri)
		{
			D3DXVECTOR3 V1 = posLineVec[1] - posLineVec[0];
			D3DXVECTOR3 V2 = posLineVec[2] - posLineVec[0];

			D3DXVECTOR3 Normal;
			//A��B�̖@�������߂���
			D3DXVec3Cross(&Normal, &V1, &V2);

			//vecB ���m�[�}���C�Y���āA���� 1�ɂ���B
			D3DXVec3Normalize(&Normal, &Normal);

			D3DXVECTOR3 VecA = *pPos - posLineVec[0];
			//�v���C���[�̈ʒu�␳
			SwitchCollision(true);
			OnHit();

			if (IsCollision)
			{
				pPos->y = (posLineVec[0].y - (Normal.x*(pPos->x - posLineVec[0].x) + Normal.z*(pPos->z - posLineVec[0].z)) / Normal.y) + 10.0f;
			}
		}
	}
	// ���_���W���A�����b�N
	m_pVtxBuff->Unlock();
	// ���_�C���f�b�N�X���A�����b�N
	m_pIdxBuff->Unlock();

	return bIsLanding;
}

//=============================================================================
// ���b�V���̍쐬
// Author:hamada ryuuga
//=============================================================================
bool CMesh::CreateMesh(D3DXVECTOR3 *pPos)
{
	bool bIsLanding = false;

	VERTEX_3D* pVtx = NULL;

	const int nTri = 3;

	// ���_���W�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxWorld;

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
	D3DXMatrixIdentity(&mtxWorld);

	// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	// �s��|���Z�֐�(��2�����~��3�������P�����Ɋi�[)
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	for (int nCnt = 0; nCnt < m_polygonCount; nCnt++)
	{
		D3DXVECTOR3 posLineVec[nTri];

		posLineVec[0] = pVtx[pIdx[nCnt + 0]].pos;
		posLineVec[1] = pVtx[pIdx[nCnt + 1]].pos;
		posLineVec[2] = pVtx[pIdx[nCnt + 2]].pos;

		if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
			(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
			(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
		{//�k�ރ|���S�����Ȃ�
			continue;
		}

		for (int i = 0; i < nTri; i++)
		{//�x�N�g���R���W���}�g���b�N�X�ŕϊ�����i��Z�j
			D3DXVec3TransformCoord(&posLineVec[i], &posLineVec[i], &mtxWorld);
		}

		int  LineCout = 0;

		for (int i = 0; i < nTri; i++)
		{
			//�x�N�g��S2 V2												
			D3DXVECTOR3 vecWall = posLineVec[(i + 1) % nTri] - posLineVec[i];

			//�x�N�g�����݂�POS�Ǝn�_�܂ł̋���
			D3DXVECTOR3 vecPos = *pPos - posLineVec[i];

			//�O�όv�Z//�ӂP
			float vecLine = Vec2Cross(&vecPos, &vecWall);

			//�O�p�̒��ɓ����Ă�Ƃ��̔���
			if ((nCnt % 2 == 0 && vecLine > 0.0f) ||
				(nCnt % 2 != 0 && vecLine < 0.0f))
			{
				LineCout++;
			}
			else
			{
				break;
			}
		}
		if (LineCout == nTri)
		{
			/*
			CInput *CInputpInput = CInput::GetKey();

			if (CInputpInput->Trigger(CInput::KEY_MESHUP))
			{			
				SetVtxMesh(pVtx, pIdx, nCnt, true);
			}
			if (CInputpInput->Trigger(CInput::KEY_MESHDOWN))
			{
				SetVtxMesh(pVtx, pIdx, nCnt, false);
			}
			*/
		}
	}

	// ���_���W���A�����b�N
	m_pVtxBuff->Unlock();
	// ���_���W���A�����b�N
	m_pIdxBuff->Unlock();

	CMesh::SetVtxMeshLight();
	

	return bIsLanding;
}

//=============================================================================
// ���b�V���̍쐬
// Author:hamada ryuuga
//=============================================================================
void CMesh::SetVtxMesh(VERTEX_3D* pVtx, WORD* pIdx,int nCnt,bool isUp)
{
	int sign = isUp ? 1 : -1;

	for (int i = 0; i < 3; i++)
	{
		int index = pIdx[nCnt + i];

		pVtx[index].pos.y += (MOUNTAIN * sign);
	}
}

//=============================================================================
//������I�u�W�F�N�g�̓ǂݍ���
//=============================================================================
void CMesh::Loadfile(const char * pFileName)
{
	Uninit();
	//NotRelease();
	std::ifstream ifs(pFileName);

	int nIndex = 0;
	VERTEX_3D* pVtx = NULL;
	// ���_���W�����b�N	
	std::string str;
	if (ifs)
	{
		ifs >> JMesh;
		nIndex = JMesh["INDEX"];
		m_move = JMesh["MOVE"];
		D3DXVECTOR3 pos;
		D3DXVECTOR3 size;
		D3DXVECTOR3 rot;
		std::string Type;

		//������
		if (JMesh["MESHSIZE"] == NULL)
		{
			CMesh::SetVtxMeshSize(0);
		}
		else
		{
			CMesh::SetVtxMeshSize(JMesh["MESHSIZE"]);
		}

		str = JMesh["TEXPASS"];
		CMesh::SetTexture(str.c_str());

		m_pos = D3DXVECTOR3(JMesh["POSORIGIN"]["X"], JMesh["POSORIGIN"]["Y"], JMesh["POSORIGIN"]["Z"]);
		m_MeshSize = D3DXVECTOR3(JMesh["MESHDATASIZE"]["X"], JMesh["MESHDATASIZE"]["Y"], JMesh["MESHDATASIZE"]["Z"]);
		
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < m_vtx; nCnt++)
		{
			float posx = ((nCnt % m_vtxCountX) - 1.0f);
			float posz = ((nCnt / m_vtxCountZ) - 1.0f) * -1.0f;

			//�߂������^�񒆂ɂ���␳
			//m_pos = D3DXVECTOR3(-(posx - 1)*MAX_SIZEMESH * 0.5f, 0.0f, -posz * MAX_SIZEMESH * 0.5f) + m_pos;

			std::string name = "MESH";
			std::string Number = std::to_string(nCnt);
			name += Number;

			pos = D3DXVECTOR3(JMesh[name]["POS"]["X"], JMesh[name]["POS"]["Y"], JMesh[name]["POS"]["Z"]);

			//���W�̕␳
			pVtx[nCnt].pos = D3DXVECTOR3(pos.x, pos.y, pos.z);

			// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			// ���_�J���[�̐ݒ�
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		// ���_���W���A�����b�N
		m_pVtxBuff->Unlock();
		CMesh::SetVtxMeshLight();
	}
}

//=============================================================================
//������I�u�W�F�N�g�̕ۑ�
//=============================================================================
void CMesh::Savefile(const char * pFileName)
{
	VERTEX_3D* pVtx = NULL;

	// ���_���W�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	int nIndex = 0;
	
	for (int i = 0; i < m_vtx; i++)
	{
		std::string name = "MESH";
		std::string Number = std::to_string(nIndex);
		name += Number;

		JMesh[name] = {
			{ "POS",{
				{ "X", pVtx[i].pos.x } ,
				{ "Y", pVtx[i].pos.y } ,
				{ "Z", pVtx[i].pos.z } } } ,};

		nIndex++;
	}

	// ���_���W���A�����b�N
	m_pVtxBuff->Unlock();

	JMesh["INDEX"] = nIndex;
	JMesh["MOVE"] = m_move;
	JMesh["MESHDATASIZE"] = {
		{ "X", m_MeshSize.x } ,
		{ "Y", m_MeshSize.y } ,
		{ "Z", m_MeshSize.z } };
	
	JMesh["TEXPASS"] = m_pFileName;
	JMesh["MESHSIZE"] = m_xsiz;
	JMesh["POSORIGIN"] = {
			{ "X", m_pos.x } ,
			{ "Y", m_pos.y } ,
			{ "Z", m_pos.z } };

	JMesh["ANIMATION"] = false;

	auto jobj = JMesh.dump();
	std::ofstream writing_file;
	const std::string pathToJSON = pFileName;
	writing_file.open(pathToJSON, std::ios::out);
	writing_file << jobj << std::endl;
	writing_file.close();
}

//=============================================================================
//�T�C�Y������
//=============================================================================
void CMesh::SetVtxMeshSize(int Size)
{
	//CMesh::Uninit();
	//NotRelease();

	m_xsiz = Size;
	m_zsiz = Size;
	m_vtxCountX = m_xsiz + 1;	// 1��������
	m_vtxCountZ = m_zsiz + 1;	// 1��������

	// ���_��
	m_vtx = m_vtxCountX* m_vtxCountZ;	// ���_�����g���Ă��

	// �C���f�b�N�X��
	m_index = (2 * m_vtxCountX * m_zsiz + 2 * (m_zsiz - 1));

	m_polygonCount = m_index - 2;

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_vtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@����
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_index,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// ���_���W�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	for (int i = 0; i < m_vtx; i++)
	{
		pVtx[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		float posx = ((i % m_vtxCountX) - 1.0f);
		float posz = ((i / m_vtxCountZ) - 1.0f) * -1.0f;

		float texU = 1.0f / m_xsiz * (i % m_vtxCountX);
		float texV = 1.0f / m_zsiz * (i / m_vtxCountZ);

		// ���b�V����^�񒆂ɂ���␳
		m_pos = (D3DXVECTOR3(-(posx - 1) * m_MeshSize.x * 0.5f, 0.0f, -posz * m_MeshSize.z * 0.5f)) + m_pos;

		// ���W�̕␳
		pVtx[i].pos += D3DXVECTOR3(posx*m_MeshSize.x, 0.0f, posz * m_MeshSize.z);


		// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[i].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ���_�J���[�̐ݒ�
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[i].tex = D3DXVECTOR2(texU, texV);

	}

	// ���_���W���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
//�@����Index�̐���
//=============================================================================
void CMesh::SetVtxMeshLight()
{
	VERTEX_3D* pVtx = NULL;
	//�C���f�b�N�X�o�b�t�@�̃��b�N
	WORD* pIdx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int z = 0; z < m_zsiz; z++)
	{
		int linetop = z * (m_vtxCountX * 2 + 2);
		for (int x = 0; x < m_vtxCountX; x++)
		{
			int nIdxData = x * 2 + linetop;
			pIdx[nIdxData + 1] = (WORD)(x + (z * m_vtxCountX));
			pIdx[nIdxData] = (WORD)(pIdx[nIdxData + 1] + m_vtxCountX);
		}
		//�k�ރ|���S���ݒ�
		if (z < m_xsiz - 1)
		{
			pIdx[m_vtxCountX * 2 + 0 + linetop] = (WORD)(m_xsiz + m_vtxCountX*z);
			pIdx[m_vtxCountX * 2 + 1 + linetop] = (WORD)(m_vtxCountX * 2 + m_vtxCountX * z);
		}
	}

	//---------------------------------------
	//��������@��
	//---------------------------------------

	//�O�p�̒��_��
	const int nTri = 3;

	D3DXVECTOR3 posLineVec[nTri];//�x�N�g��

	for (int nCnt = 0; nCnt < m_polygonCount; nCnt++) // �v���~�e�B�u�̐������܂킷�B
	{
		//�x�N�g�������߂�
		posLineVec[0] = pVtx[pIdx[nCnt + 0]].pos;
		posLineVec[1] = pVtx[pIdx[nCnt + 1]].pos;
		posLineVec[2] = pVtx[pIdx[nCnt + 2]].pos;

		if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
			(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
			(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
		{
			continue;
		}

		D3DXVECTOR3 V1 = posLineVec[1] - posLineVec[0];
		D3DXVECTOR3 V2 = posLineVec[2] - posLineVec[0];

		D3DXVECTOR3 Normal;

		if (nCnt % 2 == 0)
		{
			//A��B�̖@�������߂���
			D3DXVec3Cross(&Normal, &V1, &V2);
		}
		else
		{
			//B��A�̖@�������߂���
			D3DXVec3Cross(&Normal, &V2, &V1);
		}

		//Normal���m�[�}���C�Y���āA���� 1�ɂ���B
		D3DXVec3Normalize(&Normal, &Normal);

		for (int i = 0; i < nTri; i++)
		{//�@���v�Z
			pVtx[pIdx[nCnt + i]].nor += Normal;
		}
	}

	for (int nCnt = 0; nCnt < m_vtx; nCnt++)
	{
		//nor���m�[�}���C�Y���āA���� 1�ɂ���B
		D3DXVec3Normalize(&pVtx[nCnt].nor, &pVtx[nCnt].nor);
	}

	// ���_���W���A�����b�N
	m_pVtxBuff->Unlock();
	m_pIdxBuff->Unlock();
}

//=============================================================================
// ���b�V���̖������߂���
//=============================================================================
void CMesh::SetMesh(const int Size)
{
	m_NowMesh = Size;//�����ۑ�
	SetVtxMeshSize(Size);//�T�C�Y����
	SetVtxMeshLight();//�@���ݒ�
}
