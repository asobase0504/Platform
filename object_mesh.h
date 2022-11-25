//=============================================================================
//
// ���b�V���ݒ�w�b�^�[
// Author:hamada ryuuga
//
//=============================================================================
#ifndef _MESH_H_
#define _MESH_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "main.h"
#include "object_polygon3d.h"

//-----------------------------------------------------------------------------
// �萔
//-----------------------------------------------------------------------------
#define	EMESHX	(1)
#define	EMESHY	(5)
#define MAX_SIZEMESH (100.0f)
#define MAX_EMESH (10)
#define MOUNTAIN (50.0f)
#define MAXMOVE (10)

#define EMESHMAX (12800)

//-----------------------------------------------------------------------------
// ���b�V��
//-----------------------------------------------------------------------------
class CMesh : public CObjectPolygon3D
{
public:
	virtual void OnHit() {}	// ���b�V���̓����������̔���

	CMesh(CTaskGroup::EPriority nPriority = CTaskGroup::EPriority::LEVEL_3D_1);
	~CMesh() override;

	HRESULT Init() override;		// ������
	void Uninit() override;			// �j��
	void NormalUpdate() override;	// �X�V
	void Draw() override;			// �`��

	static CMesh* Create();

	bool CreateMesh(D3DXVECTOR3 *pPos);			// ���b�V���̓ʉ�����
	bool CollisionMesh(D3DXVECTOR3 *pPos);		// ���b�V���̓����蔻�����

	void Loadfile(const char * pFileName);	// ���b�V���̓ǂݍ���
	void Savefile(const char * pFileName);	// ���b�V���̏����o��
	
	//�Z�b�^�[
	void SetPos(const D3DXVECTOR3 &pos);
	void SetMove(float ismove) { m_move = ismove; }
	void SetMesh(const int Size);
	void SetNumber(int IsNumber) { m_Number = IsNumber; }
	void SetType(int IsType) { m_Type = IsType; }
	void SetTexture(const char * pFileName);

	void SetOneMeshSize(D3DXVECTOR3 IsSize) 
	{
		m_MeshSize = IsSize; 
		CMesh::SetMesh(m_NowMesh);
	}

	void SwitchCollision(bool onCollision) { IsCollision = onCollision; };

	//�Q�b�^�[
	const D3DXVECTOR3 * CMesh::GetPos() const;
	D3DXVECTOR3 GetOneMeshSize() { return m_MeshSize; }
	D3DXVECTOR3 GetMeshSize() { return D3DXVECTOR3(m_X *m_MeshSize.x, 0.0f, m_Z *m_MeshSize.z); }
	D3DXVECTOR3 * GetPos() { return &m_pos; }
	float GetMove() { return m_move; }
	int GetNumber() { return m_Number; }
	int GetMeshType() { return m_Type; }

	int GetMeshSizeX() { return m_X; }

	std::string GetDataNeme() { return DataName; }

private:
	void SetVtxMesh(VERTEX_3D* pVtx, WORD* pIdx, int nCnt, bool isUp);
	void SetVtxMeshSize(int Size);
	void SetVtxMeshLight();

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�[�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTextureEmesh;	// �e�N�X�`���̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@

	D3DXVECTOR3 m_pos;			// ���_���W
	D3DXVECTOR3 m_rot;			// ��]���W
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	int m_xsiz;					// �ʐ�
	int m_zsiz;					// �ʐ�
	int m_X;					// �ӂ̒��_��
	int m_Z;					// �ӂ̒��_��
	int m_nVtx;					// ���_��
	int m_Index;				// �C���f�b�N�X
	int m_por;
	int m_NowMesh;
	int m_Number;
	int m_Type;
	float m_move;
	D3DXVECTOR3 m_MeshSize;
	D3DXVECTOR3* m_nPosMesh;
	std::string  m_pFileName;
	std::string  DataName;
	bool IsCollision;
};
#endif

