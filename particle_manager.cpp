//=========================================
// 
// �p�[�e�B�N���G�~�b�^
// Author YudaKaito
// Author HamadaRyuuga
//=========================================
//=========================================
// include
//=========================================
#include "particle_manager.h"
#include "file.h"

#include <assert.h>

//-----------------------------------------
// �ÓI�����o�[�ϐ�
//-----------------------------------------
int CParticleManager::m_MaxIndex = 0;

//-----------------------------------------
// �R���X�g���N�^
//-----------------------------------------
CParticleManager::CParticleManager() :
	CTask(0),
	m_numAll(0),
	m_particleEmitter({})
{
}

//-----------------------------------------
// �f�X�g���N�^
//-----------------------------------------
CParticleManager::~CParticleManager()
{
}

//-----------------------------------------
// ������
//-----------------------------------------
HRESULT CParticleManager::Init()
{
	LoadJson("data/FILE/Effect.json");
	LoadJson("data/FILE/Sand.json");
	LoadJson("data/FILE/Flare.json");
	LoadJson("data/FILE/ice.json");
	return S_OK;
}

//-----------------------------------------
// �I��
//-----------------------------------------
void CParticleManager::Uninit()
{
	for (CParticleEmitter* emitter : m_particleEmitter)
	{
		if (emitter != nullptr)
		{
			emitter->Release();
		}
	}
}

//-----------------------------------------
// �X�V
//-----------------------------------------
void CParticleManager::Update()
{
	for (CParticleEmitter* i : m_particleEmitter)
	{
		if (i == nullptr)
		{
			continue;
		}

		i->Update();
	}
}

//-----------------------------------------
// ����
//-----------------------------------------
int CParticleManager::Create(CParticleEmitter::EObjectType inObject,const D3DXVECTOR3& pos, const int& index)
{
	CParticleEmitter* emitter = new CParticleEmitter();

	emitter->Init();		// ������
	emitter->SetPos(pos);	// �ʒu�X�V

	if ((int)m_bundledData.size() <= index)
	{
		assert(false);
		return 0;
	}

	emitter->SetParticle(m_bundledData.at(index).particleData);	// �w�肳��Ă��p�[�e�B�N���f�[�^�̑}��
	emitter->SetEmitter(m_bundledData.at(index).emitterData);
	emitter->SetObjectType(inObject);

	m_numAll++;
	m_particleEmitter.push_back(emitter);

	return m_particleEmitter.size();
}

//-----------------------------------------
// �ݒ�
//-----------------------------------------
void CParticleManager::SetBundledData(const BundledData& inData)
{
	m_bundledData.push_back(inData);
}

//-----------------------------------------
// �`�F���W�@�\
//-----------------------------------------
void CParticleManager::ChangeBundledData(const int idx, const BundledData& inData)
{
	m_bundledData.at(idx) = inData;
}

//-----------------------------------------
// �w�肳�ꂽ�ԍ��̈ʒu��ύX����
//-----------------------------------------
void CParticleManager::SetEmitterPos(const int idx, const D3DXVECTOR3 & inPos)
{
	m_particleEmitter.at(idx)->SetPos(inPos);
}
