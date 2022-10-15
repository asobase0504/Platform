//=============================================================================
//
// �}�l�[�W���[
// Author : �l�c����
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "nameset.h"
#include "sound.h"
#include "texture.h"
#include "ranking.h"
#include "tutorial.h"
#include "multiply.h"
#include "task_group.h"

//-----------------------------------------------------------------------------
// �ÓI�����o�[�ϐ��̏�����
//-----------------------------------------------------------------------------
CManager * CManager::m_pManager = nullptr;
const D3DXVECTOR3 CManager::CENTER_POS = D3DXVECTOR3(1280.0f * 0.5f, 720.0f * 0.5f, 0.0f);

//=============================================================================
// �V���O���g���ł̃C���X�^���X�̎擾
//=============================================================================
CManager * CManager::GetInstance()
{
	if (m_pManager == nullptr)
	{
		m_pManager = new CManager;
	}
	return m_pManager;
}

//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CManager::CManager() :
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
CManager::~CManager()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CManager::Init(HWND hWnd, HINSTANCE hInstance)
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

	m_pTexture = nullptr;
	m_pTexture = new CTexture;
	
	m_mode = CManager::MODE_TITLE;	//���݂̃��[�h

	//���[�h�̐ݒ�
	SetMode(m_mode);

	m_pFade = CFade::Create();

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CManager::Uninit()
{
	if (m_pTexture != nullptr)
	{// �I������
		m_pTexture->ReleaseAll();
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
void CManager::Update()
{
	//���͏����̍X�V����
	m_pInput->Update();
	m_pGame->Update();
	m_pRenderer->Update();
}

//=============================================================================
// �`��
//=============================================================================
void CManager::Draw()
{
	m_pRenderer->Draw();	// �`�揈��
}

//=============================================================================
// GetRenderer
//=============================================================================
CRenderer *CManager::GetRenderer()
{
	return m_pRenderer;
}

//=============================================================================
// GetTexture
//=============================================================================
CTexture *CManager::GetTexture()
{
	return m_pTexture;
}

//=============================================================================
// GetFade
//=============================================================================
CFade * CManager::GetFade()
{
	return m_pFade;
}


//=============================================================================
// GetMode
//=============================================================================
CManager::MODE * CManager::GetMode()
{
	return &m_mode;
}

//=============================================================================
// GetSound
//=============================================================================
CSound * CManager::GetSound()
{
	return m_pSound;
}


//=============================================================================
// ���[�h�̐ݒ�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	m_mode = mode;
	m_pTaskGroup->Release();

	// �|���S���̏I������
	//CObject::ModeNotUninit();
	
	switch (mode)
	{
	case CManager::MODE_TITLE:
		m_pGame = new CTitle;
		break;
	case CManager::MODE_GAME:
		m_pGame = new CGame;
		break;
	case CManager::MODE_RESULT:
		m_pGame = new CResult;
		break;
	case CManager::MODE_RANKING:
		m_pGame = new CRanking;
		break;
	case CManager::MODE_NAMESET:
		m_pGame = new CNameSet;
		break;
	case CManager::MODE_TUTORIAL:
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



