//=============================================================================
//
// object_polygon3d
// Author : �l�c����
//
//=============================================================================
#ifndef _3DPOLYGON_H_	// ���̃}�N����`������ĂȂ�������
#define _3DPOLYGON_H_	// ��d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "renderer.h"
#include "texture.h"
#include "object2d.h"

//-----------------------------------------------------------------------------
// �}�N���錾
//-----------------------------------------------------------------------------
#define TIMER (m_time + 90)

//=============================================================================
// 3D�|���S���N���X
//=============================================================================
class  CObjectPolygon3D : public CObject
{
public:
	const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	//���_���u3D�v�̍\���̂��`
	struct VERTEX_3D
	{
		D3DXVECTOR3 pos;//���_���W
		D3DXVECTOR3 nor;//�x�N�g��
		D3DCOLOR col;//�J���[
		D3DXVECTOR2 tex;//�e�N�X�`��
	};

protected:
	//polygon�̊�T�C�Y
	static const D3DXVECTOR3 m_Vtx[4];

public:

	static CObjectPolygon3D *Create(CTaskGroup::EPriority list = CTaskGroup::LEVEL_3D_1);

	CObjectPolygon3D(CTaskGroup::EPriority list = CTaskGroup::LEVEL_3D_1);
	~CObjectPolygon3D() override;
	HRESULT Init() override;
	void Uninit() override;
	void NormalUpdate() override;
	void Draw() override;

	// Setter
	virtual void SetPos(const D3DXVECTOR3& inPos) override;
	void SetTex(PositionVec4 inTex);
	void SetSize(const D3DXVECTOR3& inSize);
	void SetCollar(D3DXCOLOR inCollar);

	// Getter
	LPDIRECT3DVERTEXBUFFER9 GetVtx();

	static void PolygonReset() { m_maxPolygon = 0; }

protected:
	float m_scale;
	D3DXVECTOR3 m_size;
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	int  m_time;
private:
	static int m_maxPolygon;
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;
};
#endif
