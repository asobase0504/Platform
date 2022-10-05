//=============================================================================
// 
// �|�[�Y�̍쐬(�w�b�_�[�t�@�C��)
// Author Hamada Ryuuga
// 
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "object.h"
#include "object2d.h"

//=============================================================================
// �|�[�Y�N���X
//=============================================================================
class CPause :public CObject
{
public:
	//���(���[�h)�̎��
	enum EMode
	{
		MODE_GAME = 0,			//�Q�[�����	
		MODE_RETURN,
		MODE_TITLE,
		MODE_END,
		MODE_MAX
	};

	CPause();
	~CPause();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// Setter
	void Set() { m_onPause = !m_onPause; };

	// Getter
	bool Get() { return m_onPause; };

private:
	bool m_onPause;
	int m_nextMode;
	CObject2d* m_pBg;
	CObject2d* m_pObject2d[4];
};

#endif 
