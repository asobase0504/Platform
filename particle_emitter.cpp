//=========================================
// 
// �p�[�e�B�N���G�~�b�^
// Author YudaKaito
// 
//=========================================
//=========================================
// include
//=========================================
#include "particle_emitter.h"
#include "utility.h"
#include "particle.h"
#include "object2d.h"
#include "object_polygon3d.h"

//=========================================
// �ÓI�����o�[�ϐ�
//=========================================

//-----------------------------------------
// �R���X�g���N�^
// Author YudaKaito
//-----------------------------------------
CParticleEmitter::CParticleEmitter() :
	CObject(CTaskGroup::LEVEL_2D_1),
	m_info({}),
	m_particleInfo({}),
	m_objectType(EObjectType::POLIGON2D)
{

}

//-----------------------------------------
// �f�X�g���N�^
// Author YudaKaito
//-----------------------------------------
CParticleEmitter::~CParticleEmitter()
{

}

//-----------------------------------------
// ������
// Author YudaKaito
//-----------------------------------------
HRESULT CParticleEmitter::Init()
{
	return S_OK;
}

//-----------------------------------------
// �I��
// Author YudaKaito
//-----------------------------------------
void CParticleEmitter::Uninit()
{
}

//-----------------------------------------
// �X�V
// Author YudaKaito
//-----------------------------------------
void CParticleEmitter::NormalUpdate()
{
	int popNumber = 5;
	for (int i = 0; i < popNumber; i++)
	{
		PopParticle();
	}
}

//-----------------------------------------
// �o��
// Author YudaKaito
//-----------------------------------------
void CParticleEmitter::PopParticle(void)
{
	CParticle::SInfo popInfo = m_particleInfo;
	popInfo.nMaxLife = popInfo.nLife;
	popInfo.fWidth = popInfo.fScale;
	popInfo.fHeight = popInfo.fScale;

	D3DXVECTOR3 myPos = m_pos;
	// �����ʒu�̎Z�o
	myPos.x += FloatRandam(m_info.maxPopPos.x, -m_info.minPopPos.x);
	myPos.y += FloatRandam(m_info.maxPopPos.y, -m_info.minPopPos.y);
	myPos.z += FloatRandam(m_info.maxPopPos.z, -m_info.minPopPos.z);

	// �F�̎Z�o
	CParticle::SColor& popColor = popInfo.color;
	popColor.nCntTransitionTime = 0;
	if (popColor.bColRandom)
	{// �����_���J���[���g�p
		popColor.colBigin.r = FloatRandam(popColor.colRandamMax.r, popColor.colRandamMin.r);
		popColor.colBigin.g = FloatRandam(popColor.colRandamMax.g, popColor.colRandamMin.g);
		popColor.colBigin.b = FloatRandam(popColor.colRandamMax.b, popColor.colRandamMin.b);

		if (popColor.bColTransition)
		{// �ړI�̐F�̐ݒ�
			if (popColor.bRandomTransitionTime)
			{
				popColor.nEndTime = rand() % popInfo.nLife + 1;
			}

			popColor.destCol.r = FloatRandam(popColor.colRandamMax.r, popColor.colRandamMin.r);
			popColor.destCol.g = FloatRandam(popColor.colRandamMax.g, popColor.colRandamMin.g);
			popColor.destCol.b = FloatRandam(popColor.colRandamMax.b, popColor.colRandamMin.b);
		}
	}

	if (popColor.bColTransition)
	{// �g���f�B�V�I���J���[���g�p
		if (popColor.bRandomTransitionTime)
		{
			popColor.nEndTime = rand() % popInfo.nLife + 1;
		}

		popColor.colTransition.r = (popColor.destCol.r - popColor.colBigin.r) / popColor.nEndTime;
		popColor.colTransition.g = (popColor.destCol.g - popColor.colBigin.g) / popColor.nEndTime;
		popColor.colTransition.b = (popColor.destCol.b - popColor.colBigin.b) / popColor.nEndTime;
	}

	static float ImAngle = 30.0f;
	float fRad = 0.0f;
	float fGRad = 0.0f;

	if (popInfo.bBackrot)
	{
		// float fRad = (popData.fAngle) * (D3DX_PI / 180);
		fGRad = (popInfo.rot.z - m_info.fAngle);
	}
	else
	{
		fRad = (popInfo.fAngle) * (D3DX_PI / 180);
		fGRad = (popInfo.rot.z + m_info.fAngle);
	}

	// ����
	{
		// ������������
		m_info.fAngle += ImAngle;
		popInfo.move.x += (popInfo.fRadius * sinf(fGRad)) * popInfo.fAttenuation;
		popInfo.move.y += (popInfo.fRadius * cosf(fGRad)) * popInfo.fAttenuation;
	}

	// ======================
	// ���K��
	// ======================
	NormalizeAngle(popInfo.fRadius);
	NormalizeAngle(m_info.fAngle);

	switch (m_objectType)
	{
	case CParticleEmitter::POLIGON2D:
		CParticle::Create(new CObject2d, popInfo, myPos);
		break;
	case CParticleEmitter::POLIGON3D:
		CParticle::Create(new CObjectPolygon3D, popInfo, myPos);
		break;
	case CParticleEmitter::BILLBOARD:
		CParticle::Create(new CObject2d, popInfo, myPos);
		break;
	case CParticleEmitter::MODEL:
		CParticle::Create(new CObject2d, popInfo, myPos);
		break;
	default:
		break;
	}
}

//-----------------------------------------
// �ݒ�
// Author YudaKaito
//-----------------------------------------
void CParticleEmitter::SetParticle(const CParticle::SInfo& inParticle)
{
	m_particleInfo = inParticle;
}
