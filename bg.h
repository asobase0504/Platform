//=============================================================================
//
// BG�I�u�W�F�N�g
// Author : �l�c����
//
//=============================================================================
#ifndef _BG_H_			// ���̃}�N����`������ĂȂ�������
#define _BG_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "renderer.h"
#include "object_polygon3d.h"
#include "texture.h"

//=============================================================================
// �w�i�̃N���X
//=============================================================================
class CBg : public CObjectPolygon3D
{
public:
	enum BgType
	{
		MOVE = 0,	// ������[��
		STOP,		// �����Ȃ���[��
		MAX			// ���񂽂����H
	};

	static CBg *CBg::Create();

	CBg(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_BG);
	~CBg() override;

	HRESULT Init() override;
	void Uninit() override;
	void NormalUpdate() override;
	void Draw() override;

	// Setter
	void SetBgType(const BgType &Type) { BgType = Type; };

private:
	D3DXVECTOR3 m_Speed;
	D3DXVECTOR3 m_MoveSpeed;
	D3DXVECTOR3 m_AddSpeed;
	BgType BgType;
};

#endif
