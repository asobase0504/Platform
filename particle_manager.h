//=========================================
// 
// �p�[�e�B�N���G�~�b�^
// Author YudaKaito
// Author HamadaRyuuga
//=========================================
#ifndef _PARTICLE_MANAGER_H_
#define _PARTICLE_MANAGER_H_

//=========================================
// include
//=========================================
#include <vector>
#include "particle.h"
#include "particle_emitter.h"
#include "task.h"

//=========================================
// �O���錾
//=========================================
class CParticleEmitter;

//=========================================
// �p�[�e�B�N���̊Ǘ�
//=========================================
class CParticleManager : public CTask
{
public:	// �񋓌^
public:	// �\����
	struct BundledData
	{
		CParticle::SInfo particleData;
		CParticleEmitter::SInfo emitterData;
	};

public:
	CParticleManager();
	~CParticleManager();

	HRESULT Init();
	void Uninit();
	void Update();
	CParticleEmitter* Create(CParticleEmitter::EObjectType inObject,const D3DXVECTOR3& pos, const int& idx);
	void SetBundledData(const BundledData&inData);
	void ChangeBundledData(const int idx, const BundledData&inData);

	// Getter
	std::vector<BundledData>& GetBundledData() { return m_bundledData; }
	std::list<CParticleEmitter*> GetEmitter() { return m_particleEmitter; }

	// �O���Ǎ���
	void LoadBundledData(const wchar_t* cUrl);

private:
	int m_numAll;	// ������
	std::vector<BundledData> m_bundledData;	// ����
	std::list<CParticleEmitter*> m_particleEmitter;	// �G�~�b�^�\���
	int m_Index;
	static int m_MaxIndex;
};

#endif // !_PARTICLE_FACTORY_H_
