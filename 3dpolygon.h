//=============================================================================
//
// 3dpolygon
// Author : �l�c����
//
//=============================================================================
#ifndef _3DPOLYGON_H_			// ���̃}�N����`������ĂȂ�������
#define _3DPOLYGON_H_			// ��d�C���N���[�h�h�~�̃}�N����`

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
class  C3dpolygon : public CObject
{
public:
	const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

protected:
	//polygon�̊�T�C�Y
	static const D3DXVECTOR3 m_Vtx[4];

public:

	static C3dpolygon *Create(int list = 0);

	C3dpolygon(int list = 0);
	~C3dpolygon() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// Setter
	virtual void SetPos(const D3DXVECTOR3& inPos);
	virtual void SetMove(const D3DXVECTOR3& inMove) { m_move = inMove; };
	void SetTexture(CTexture::TEXTURE inTexture);
	void SetTex(PositionVec4 Tex);
	void SetSize(const D3DXVECTOR3& inSize);
	void SetCollar(D3DXCOLOR inCollar);
	void SetRot(D3DXVECTOR3 inRot) { m_rot = inRot; }

	// Getter
	virtual const D3DXVECTOR3* GetPos() const;
	LPDIRECT3DVERTEXBUFFER9 GetVtx();

	static void PolygonReset() { m_maxPolygon = 0; }

protected:
	float m_scale;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_pos;		// polygon�̈ʒu
	D3DXVECTOR3 m_size;
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	int  m_time;
	D3DXVECTOR3  m_move;
private:
	static int m_maxPolygon;
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;
	CTexture::TEXTURE m_texture;	// �e�N�X�`���̗񋓌^

};

#endif
