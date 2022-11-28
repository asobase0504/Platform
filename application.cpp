//=============================================================================
//
// �}�l�[�W���[
// Author : �l�c����
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "application.h"
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "task_group.h"
#include "objectX_group.h"
#include "texture.h"
#include "fade.h"

/* �V�[�����[�h */
#include "title.h"
#include "game.h"
#include "result.h"
#include "nameset.h"
#include "ranking.h"
#include "tutorial.h"
#include "multiply.h"

//-----------------------------------------------------------------------------
// �ÓI�����o�[�ϐ��̏�����
//-----------------------------------------------------------------------------
CApplication * CApplication::m_pApplication = nullptr;
const D3DXVECTOR3 CApplication::CENTER_POS = D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f);

//=============================================================================
// �V���O���g���ł̃C���X�^���X�̎擾
//=============================================================================
CApplication * CApplication::GetInstance()
{
	if (m_pApplication == nullptr)
	{
		m_pApplication = new CApplication;
	}
	return m_pApplication;
}

//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CApplication::CApplication() :
	m_pTexture(nullptr),
	m_pRenderer(nullptr),
	m_pTaskGroup(nullptr),
	m_pFade(nullptr),
	m_pGame(nullptr),
	m_pSound(nullptr)
{
}

//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
CApplication::~CApplication()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CApplication::Init(HWND hWnd, HINSTANCE hInstance)
{
	// �����O���[�v�̏���������
	m_pTaskGroup = new CTaskGroup;
	if (FAILED(m_pTaskGroup->Init()))
	{
		return E_FAIL;
	}

	// �����_���[�̏���������
	m_pRenderer = CRenderer::GetInstance();
	if (FAILED(m_pRenderer->Init(hWnd, true)))
	{
		return E_FAIL;
	}

	// ���͏����̏���������
	m_pInput = CInput::Create();
	if (FAILED(m_pInput->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// ���y�����̏���������
	m_pSound = new CSound;
	if (FAILED(m_pSound->Init(hWnd)))
	{
		return E_FAIL;
	}

	// ���y�����̏���������
	m_pObjectXGroup = new CObjectXGroup;
	m_pObjectXGroup->LoadAll();

	m_pTexture = nullptr;
	m_pTexture = CTexture::GetInstance();
	
	m_mode = CApplication::MODE_TITLE;	//���݂̃��[�h

	//���[�h�̐ݒ�
	SetMode(m_mode);

	m_pFade = CFade::Create();

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CApplication::Uninit()
{
	if (m_pTaskGroup != nullptr)
	{// �I������
		m_pTaskGroup->Uninit();
		delete m_pTaskGroup;
		m_pTaskGroup = nullptr;
	}

	if (m_pObjectXGroup != nullptr)
	{// �I������
		m_pObjectXGroup->UnloadAll();
		delete m_pObjectXGroup;
		m_pObjectXGroup = nullptr;
	}
	
	if (m_pTexture != nullptr)
	{// �I������
		m_pTexture->UnloadAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pRenderer != nullptr)
	{// �I������

		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pSound != nullptr)
	{// �I������

		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	//���͏����̏I������
	m_pInput->Uninit();

}

//=============================================================================
// �X�V
//=============================================================================
void CApplication::Update()
{
	//���͏����̍X�V����
	m_pInput->Update();
	m_pGame->Update();
	m_pRenderer->Update();
}

//=============================================================================
// �`��
//=============================================================================
void CApplication::Draw()
{
	m_pRenderer->Draw();	// �`�揈��
}

//=============================================================================
// GetRenderer
//=============================================================================
CRenderer *CApplication::GetRenderer()
{
	return m_pRenderer;
}

//=============================================================================
// GetTexture
//=============================================================================
CTexture *CApplication::GetTexture()
{
	return m_pTexture;
}

//=============================================================================
// GetFade
//=============================================================================
CFade * CApplication::GetFade()
{
	return m_pFade;
}


//=============================================================================
// GetMode
//=============================================================================
CApplication::MODE * CApplication::GetMode()
{
	return &m_mode;
}

//=============================================================================
// GetSound
//=============================================================================
CSound * CApplication::GetSound()
{
	return m_pSound;
}


//=============================================================================
// ���[�h�̐ݒ�
//=============================================================================
void CApplication::SetMode(MODE mode)
{
	m_mode = mode;
	m_pTaskGroup->AllRelease();

	// �|���S���̏I������
	//CObject::ModeNotUninit();
	
	switch (mode)
	{
	case CApplication::MODE_TITLE:
		m_pGame = new CTitle;
		break;
	case CApplication::MODE_GAME:
		m_pGame = new CGame;
		break;
	case CApplication::MODE_RESULT:
		m_pGame = new CResult;
		break;
	case CApplication::MODE_RANKING:
		m_pGame = new CRanking;
		break;
	case CApplication::MODE_NAMESET:
		m_pGame = new CNameSet;
		break;
	case CApplication::MODE_TUTORIAL:
		m_pGame = new CTutorial;
		break;
	default:
		break;
	}

	// ����������
	if (FAILED(m_pGame->Init()))	//��ʃT�C�Y
	{//���������������s�����ꍇ
		return ;
	}
}



