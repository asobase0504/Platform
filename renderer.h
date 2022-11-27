//=============================================================================
//
// �����_���[
// Author : �l�c����
//
//=============================================================================
#ifndef _RENDERER_H_			// ���̃}�N����`������ĂȂ�������
#define _RENDERER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------------------------
// ���C�u�����[�����N
//-----------------------------------------------------------------------------
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include <Windows.h>
#include <tchar.h> // _T
#include <string>

#pragma push_macro("new")
#undef new
#include <d3dx9.h>
#pragma pop_macro("new")

//*****************************************************************************
// �萔��`
//*****************************************************************************
namespace
{
	// �E�C���h�E�̃N���X��
	LPCTSTR CLASS_NAME = _T("AppClass");
	// �E�C���h�E�̃L���v�V������
	LPCTSTR WINDOW_NAME = _T("Fox");
}

const int SCREEN_WIDTH = 1280;	// �X�N���[���̕�
const int SCREEN_HEIGHT = 720;	// �X�N���[���̍���

int GetTime(void);

//=============================================================================
// �O���錾
//=============================================================================
class CCamera;

//=============================================================================
// �`��̐ݒ�
//=============================================================================
class CRenderer
{
public:	// �V���O���g���p�̃C���X�^���X
	static CRenderer* GetInstance();
	static CRenderer* m_renderer;
private:
	CRenderer();
public:
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	// Setter
	CCamera* SetCamera(CCamera* inCamera);

	// Getter
	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }
	CCamera* GetCamera() { return m_camera; }

private:	// �v���C�x�[�g�֐�
#ifdef _DEBUG
	void DrawFPS();
#endif // _DEBUG

private:	// �����o�[�ϐ�
	LPDIRECT3D9 m_pD3D;				// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Device�I�u�W�F�N�g

	CCamera* m_camera;	// �J����

#ifdef _DEBUG
	// �t�H���g
	LPD3DXFONT m_pFont = nullptr;
#endif // _DEBUG
};
#endif