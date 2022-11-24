//=============================================================================
//
// BG�I�u�W�F�N�g
// Author : �l�c����
//
//=============================================================================


#ifndef _3DPOLYGONTEMPLATE_H_			// ���̃}�N����`������ĂȂ�������
#define _3DPOLYGONTEMPLATE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "3dpolygon.h"
#include "texture.h"

class CTest3d : public C3dpolygon
{
public:

	static CTest3d *CTest3d::Create();

	CTest3d(CTaskGroup::EPriority list);
	~CTest3d() override;
	HRESULT Init() override;
	void Uninit() override;
	void NormalUpdate()override;
	void Draw() override;

private:
	void move();
	D3DXVECTOR3 m_Move;

};

#endif

