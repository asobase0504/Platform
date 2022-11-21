//=========================================
// 
// �p�[�e�B�N���G�~�b�^
// Author YudaKaito
// Author HamadaRyuuga
//=========================================
#ifndef _PARTICLE_EMITTER_H_
#define _PARTICLE_EMITTER_H_

//=========================================
// include
//=========================================
#include <d3dx9.h>
#include "particle.h"
#include "object.h"

//=========================================
// �O���錾
//=========================================
class CParticle;

//=========================================
// �p�[�e�B�N���G�~�b�^
//=========================================
class CParticleEmitter : public CObject
{
public: // �񋓌^
	enum EObjectType
	{
		POLIGON2D = 0,
		POLIGON3D,
		BILLBOARD,
		MODEL
	};

public: // �\����
	struct Info
	{
		float fAngle;
	};
public: // �ÓI�����o�[�֐�
public: // �����o�[�֐�
	CParticleEmitter();
	~CParticleEmitter();

	HRESULT Init();
	void Uninit();
	void Update();

	void PopParticle(void);
	void SetParticle(const CParticle::Info& inParticle);
	void SetEmitter(const Info& inEmitter) { m_info = inEmitter; }
	CParticle::Info* GetParticle() { return &m_particleInfo; }

	void SetObjectType(const EObjectType inType) { m_objectType = inType; }

private: // �����o�[�ϐ�
	Info m_info;					// �G�~�b�^�[���Ǘ�������ꗗ
	CParticle::Info m_particleInfo;	// ���̃G�~�b�^�[����o��p�[�e�B�N���̃f�[�^
	EObjectType m_objectType;		// �o�����̂̌`��
};

#endif // !_PARTICLE_EMITTER_H_
