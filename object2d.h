//=============================================================================
//
// 2D�I�u�W�F�N�g
// Author : �l�c����
//
//=============================================================================
#ifndef _OBJECT2D_H_			// ���̃}�N����`������ĂȂ�������
#define _OBJECT2D_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "renderer.h"
#include "object.h"
#include "texture.h"

// 4�_�̒��_
struct PositionVec4
{
	float     P0, P1, P2, P3;
	constexpr PositionVec4() : P0(0.0f), P1(0.0f), P2(0.0f), P3(0.0f) { }
	constexpr PositionVec4(float _P0, float _P1, float _P2, float _P3) : P0(_P0), P1(_P1), P2(_P2), P3(_P3) { }
};

//=============================================================================
// 2D�I�u�W�F�N�g�N���X
//=============================================================================
class CObject2d : public CObject
{
public:
	// ���_�t�H�[�}�b�g
	const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	// ���_�f�[�^
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;
		float rhw;
		D3DCOLOR col;
		D3DXVECTOR2 tex;	// �e�N�X�`�����W(���x��1)
	};

private:
	//polygon�̊g��T�C�Y
	static const D3DXVECTOR3 m_Vtx[4];

public:
	static CObject2d *Create(int list = 0);

	CObject2d(int list = 0);
	~CObject2d() override;
	HRESULT Init() override;
	void Uninit() override;
	void NormalUpdate() override;
	void Draw() override;

	// Setter
	virtual void SetPos(const D3DXVECTOR3 &pos) override;
	virtual void SetMove(const D3DXVECTOR3 &move) override;
	void SetRot(D3DXVECTOR3 Rot) { m_rot = Rot; };
	void SetSize(D3DXVECTOR3 Size) { m_size = Size; };
	void SetTexture(int texture);
	void SetTex(PositionVec4 Tex);
	void SetColar(const D3DXCOLOR& inColar);
	void SetAnimation(const int U, const int V, const int Speed, const int Drawtimer, const bool loop);

	int GetTexture();
	D3DXCOLOR GetCollar() { return m_col; }
	D3DXVECTOR3 GetSize() { return m_size; }
	LPDIRECT3DVERTEXBUFFER9 &GetVtx() { return m_pVtxBuff; }

private:
	void Animation();

protected:
	int  m_nTimer;
	float m_nScale;
	D3DXVECTOR3 m_size;	// �傫��
	D3DXVECTOR3 m_rot;	// �p�x
	D3DXCOLOR m_col;	// �F
	D3DXMATRIX m_mtxWorld;	// �}�g���b�N�X

private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;
	int m_texture;	// �e�N�X�`���̗񋓌^

	/* �A�j���[�V�����n�� */
	// ���݂̃A�j���[�V������
	int m_CounterAnim;
	int m_PatternAnimX;
	int m_PatternAnimY;

	// ������
	int m_DivisionX;
	int m_DivisionY;
	int m_DivisionMAX;

	// �A�j���[�V�������x
	int m_AnimationSpeed;
	int m_AnimationSpeedCount;
	
	// �A�j���[�V��������
	int m_Timar;
	int m_TimaCount;

	bool m_OnAnimation;	// �A�j���[�V�����g�p�̗L��
	bool m_Loop;		// ���[�v�A�j���[�V�������ۂ�
};
#endif
