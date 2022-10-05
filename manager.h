//=============================================================================
//
// �}�l�W���[
// Author : �l�c����
//
//=============================================================================
#ifndef _MANEAGER_H_			// ���̃}�N����`������ĂȂ�������
#define _MANEAGER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "renderer.h"

//-----------------------------------------------------------------------------
// �O���錾
//-----------------------------------------------------------------------------
class CRenderer;
class CInput;
class CTexture;
class CObject;
class CResult;
class CTitle;
class CFade;
class CSound;

//=============================================================================
// �}�l�W���[�N���X
//=============================================================================
class CManager
{
public:

	static const D3DXVECTOR3 CENTER_POS;	// �����ʒu

	//���(���[�h)�̎��
	enum MODE
	{
		MODE_TITLE = 0,		// �^�C�g�����
		MODE_GAME,			// �Q�[�����
		MODE_RESULT,		// ���U���g���
		MODE_FADE,			// �t�F�[�h���
		MODE_RANKING,		// �����L���O���
		MODE_GAMEOVER,		// �Q�[���I�[�o�[���
		MODE_TUTORIAL,
		MODE_NAMESET,
		MODE_MAX
	};

private: // �ÓI�����o�[�ϐ�
	static CManager* m_manager;

public: // �ÓI�֐�
	static CManager* GetInstance();

private: // �V���O���g��
	CManager();

public:	// �����o�[�֐�
	~CManager();

	HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);
	void Uninit();
	void Update();
	void Draw();

	CRenderer *GetRenderer();
	CTexture* GetTexture();	// �e�N�X�`���̏��̎擾
	CFade* GetFade();	// �t�F�[�h�̎擾
	MODE* GetMode();	// ���[�h�̎擾
	void SetMode(CManager::MODE mode);
	CSound * CManager::GetSound();

private:
	CTexture *m_pTexture;
	CRenderer * m_cRenderer;
	CFade* m_Fade;
	CObject*m_Game;
	CSound*m_Sound;
	MODE m_mode;
	CInput *m_Input;
};



#endif
