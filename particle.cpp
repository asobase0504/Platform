// ����������������������������������������
// effect.cpp
// ����������������������������������������
#include "particle.h"
#include "main.h"

#include "utility.h"
#include "renderer.h"
#include "application.h"
#include <assert.h>
#include "object.h"

//==================================================
// �ÓI�����o�[�ϐ�
//==================================================

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CParticle::CParticle() : 
	m_data({})
{

}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CParticle::~CParticle()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CParticle::Init()
{
	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CParticle::Uninit()
{
	CTask::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CParticle::Update()
{
	CTask::Update();

	/* ���g�p���Ă���Ȃ火 */

	// �G�t�F�N�g�̈ړ�

	m_object->AddPos(m_data.move);

	// ����
	m_data.nLife--;							// �̗͂̌���
	m_data.move.y += m_data.fWeight;			// �d��
	m_data.move *= m_data.fAttenuation;			// �ړ��ʂ̐���
	m_data.fWeight += m_data.fWeightTransition;	// �d���̐���
	m_data.move.x -= 0.1f;

	if (m_data.color.bColTransition)
	{// �F�̐���
		if (m_data.color.nEndTime >= m_data.color.nCntTransitionTime)
		{
			m_data.color.nCntTransitionTime++;
			m_object->AddColor(m_data.color.colTransition);
			//myColor.a += m_data.color.colTransition.a;
		}
	}

	m_object->AddColorAlpha(-(1.0f / m_data.nMaxLife));
	m_object->SetSize(D3DXVECTOR3(m_data.fWidth, m_data.fWidth,0.0f));

	if (m_data.nLife <= 0)
	{// �G�t�F�N�g�̎���
		Release();
		m_object->Release();
	}
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CParticle* CParticle::Create(CObject* inObject,const SInfo& inParticle, const D3DXVECTOR3& inPos)
{
	CParticle* particle = nullptr;
	if (particle == nullptr)
	{
		particle = new CParticle;
		particle->Init();
		
		particle->m_object = inObject;
		particle->m_object->Init();
		particle->m_object->SetSize(D3DXVECTOR3(inParticle.fScale, inParticle.fScale,0.0f));
		particle->m_object->SetPos(inPos);
		particle->m_data = inParticle;
		//particle->SetTexture(particle->m_data.nIdxTex);
		particle->m_object->SetColor(D3DXCOLOR(particle->m_data.color.colBigin.r, particle->m_data.color.colBigin.g, particle->m_data.color.colBigin.b, particle->m_data.color.colBigin.a));
		
		particle->m_object->SetTexture("SMOKE");

		return particle;
	}
	return nullptr;
}

//--------------------------------------------------
// �e�N�X�`���̓Ǎ���
//--------------------------------------------------
void CParticle::LoadTex()
{

}

//--------------------------------------------------
// float �� DWORD �ɕϊ�
//--------------------------------------------------
DWORD CParticle::FloattoDword(float fVal)
{
	return *((DWORD*)&fVal);
}
