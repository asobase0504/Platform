//=============================================================================
//
// �}�l�W���[
// Author : �l�c����
// AUthor : Yuda Kaito
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
class CMode;
class CFade;
class CSound;
class CTaskGroup;

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
	static CManager* m_pManager;

public: // �ÓI�֐�
	static CManager* GetInstance();

private: // �V���O���g��
	CManager();

public:	// �����o�[�֐�
	~CManager();

	HRESULT Init(HWND hWnd, HINSTANCE hInstance);
	void Uninit();
	void Update();
	void Draw();

	CRenderer* GetRenderer();
	CTexture* GetTexture();
	CTaskGroup* GetTaskGroup() { return m_pTaskGroup; }
	CFade* GetFade();
	MODE* GetMode();
	void SetMode(CManager::MODE inMode);
	CSound* GetSound();

private:
	CTexture* m_pTexture;
	CRenderer* m_pRenderer;
	CTaskGroup* m_pTaskGroup;
	CFade* m_pFade;
	CMode* m_pGame;
	CSound* m_pSound;
	MODE m_mode;
	CInput* m_pInput;
};
#endif
