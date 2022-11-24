//=============================================================================
//
// Object
// Author : �l�c����
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "object.h"
#include "object_polygon3d.h"
#include "application.h"
#include "input.h"
#include "utility.h"
#include "camera.h"

//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------
int CObjectPolygon3D::m_maxPolygon;
const D3DXVECTOR3 CObjectPolygon3D::m_Vtx[4] =
{
	D3DXVECTOR3(-1.0f, +1.0f, 0.0f),
	D3DXVECTOR3(+1.0f, +1.0f, 0.0f),
	D3DXVECTOR3(-1.0f, -1.0f, 0.0f),
	D3DXVECTOR3(+1.0f, -1.0f, 0.0f),
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObjectPolygon3D::CObjectPolygon3D(CTaskGroup::EPriority list) :
	CObject(list,CTaskGroup::EPushMethod::PUSH_CURRENT),
	m_pVtxBuff(nullptr)
{
	
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObjectPolygon3D::~CObjectPolygon3D()
{
}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CObjectPolygon3D::Init()
{
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	m_scale = 10.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_time = 0;
	
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	m_texture = CTexture::GetInstance()->SetTexture("NONE");

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,		//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//rhw�̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CObjectPolygon3D::Uninit()
{
	// �j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	Release();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CObjectPolygon3D::NormalUpdate()
{
	m_time++;
	m_rot.z = -D3DXToRadian(TIMER);

	m_maxPolygon++;

	m_pos.z = -0.01f*m_maxPolygon;
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CObjectPolygon3D::Draw()
{
	// �f�o�C�X�ւ̃|�C���^
	// �f�o�C�X�̎擾
 	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h���W�s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CApplication::GetInstance()->GetTexture()->GetTexture(m_texture));

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);	// �v���~�e�B�u(�|���S��)��

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetTexture(0, NULL);
}




//=============================================================================
// create�֐�
//=============================================================================
CObjectPolygon3D *CObjectPolygon3D::Create(CTaskGroup::EPriority list)
{
	CObjectPolygon3D * pObject = nullptr;
	pObject = new CObjectPolygon3D(list);

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

//=============================================================================
// SetPos�֐�
//=============================================================================
void CObjectPolygon3D::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;
}

//--------------------------------------------------
// �e�N�X�`���̐ݒ�
//--------------------------------------------------
void CObjectPolygon3D::SetTexture(int texture)
{
	m_texture = texture;
}

//---------------------------------------
//�Z�b�g�e�N�X�`��(2d)
//---------------------------------------
void CObjectPolygon3D::SetTex(PositionVec4 Tex)
{
	VERTEX_3D *pVtx; //���_�ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(Tex.P0, Tex.P2);
	pVtx[1].tex = D3DXVECTOR2(Tex.P1, Tex.P2);
	pVtx[2].tex = D3DXVECTOR2(Tex.P0, Tex.P3);
	pVtx[3].tex = D3DXVECTOR2(Tex.P1, Tex.P3);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//---------------------------------------
//�Z�b�g�T�C�Y
//---------------------------------------
void  CObjectPolygon3D::SetSize(const D3DXVECTOR3 &size)
{
	m_size = size;

	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//------------------------
	// ���_���̐ݒ�
	//------------------------
	//���_���W
	for (int i = 0; i < 4; ++i)
	{
		pVtx[i].pos.x = m_Vtx[i].x * m_size.x; // TODO: ����Ȃ����B
		pVtx[i].pos.y = m_Vtx[i].y * m_size.y; // TODO: ����Ȃ����B
		pVtx[i].pos.z = 0.0f;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}
//---------------------------------------
//���_Collar�̐ݒ�
//---------------------------------------
void CObjectPolygon3D::SetCollar(D3DXCOLOR Collar)
{
	VERTEX_3D *pVtx; //���_�ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W�ݒ�
	//���_�J���[�̐ݒ�								  
	pVtx[0].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);
	pVtx[1].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);
	pVtx[2].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);
	pVtx[3].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}

//---------------------------------------
//Vtx�̎擾
//---------------------------------------
LPDIRECT3DVERTEXBUFFER9 CObjectPolygon3D::GetVtx()
{
	return m_pVtxBuff;
}
