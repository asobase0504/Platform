//=============================================================================
//
// ���� ( �^�C�g�� )
// Author : Yuda Kaito
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "title.h"
#include "application.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
// 3D�n��
#include "camera.h"
#include "light.h"
// Object�n��
#include "object2d.h"
#include "objectX.h"
// Particle�n��
#include "particle_manager.h"
#include "particle_emitter.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	m_pCamera = CRenderer::GetInstance()->SetCamera(new CCamera);

	m_pLight = new CLight;
	m_pLight->Init();

	m_pPaticleManager = new CParticleManager;
	if (FAILED(m_pPaticleManager->Init()))
	{
		return E_FAIL;
	}

	CObject2d* test = CObject2d::Create();
	test->Init();
	test->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	test->SetPos(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	test->SetMove(D3DXVECTOR3(2.5f, 2.5f, 0.0f));
	test->SetSize(D3DXVECTOR3(20.0f, 20.0f, 0.0f));

	CObjectX* testX = CObjectX::Create(D3DXVECTOR3(0.0f,0.0f,0.0f));
	testX->LoadModel("FOX_KAO");
	testX->CalculationVtx();

	return S_OK;
}

//=============================================================================
// �j��
//=============================================================================
void CTitle::Uninit(void)
{
	CApplication::GetInstance()->GetSound()->Stop();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	static bool a = false;
	if (CInput::GetKey()->Trigger(CInput::KEY_UP) && !a)
	{
		a = true;
		m_pPaticleManager->Create(CParticleEmitter::EObjectType::POLIGON2D, CApplication::CENTER_POS, 0);
	}
	if (CInput::GetKey()->Trigger(CInput::KEY_DOWN))
	{
		CApplication::GetInstance()->GetFade()->NextMode(CApplication::MODE_GAME);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}