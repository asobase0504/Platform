//=========================================
// 
// パーティクルエミッタ
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
// 前方宣言
//=========================================
class CParticle;

//=========================================
// パーティクルエミッタ
//=========================================
class CParticleEmitter : public CObject
{
public: // 列挙型
	enum EObjectType
	{
		POLIGON2D = 0,
		POLIGON3D,
		BILLBOARD,
		MODEL
	};

public: // 構造体
	struct Info
	{
		float fAngle;
	};
public: // 静的メンバー関数
public: // メンバー関数
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

private: // メンバー変数
	Info m_info;					// エミッターが管理する情報一覧
	CParticle::Info m_particleInfo;	// このエミッターから出るパーティクルのデータ
	EObjectType m_objectType;		// 出す物体の形式
};

#endif // !_PARTICLE_EMITTER_H_
