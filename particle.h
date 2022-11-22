//����������������������������������������
//particle.h
// Author : Tanaka Kouta
// Author : Hamada Ryuuga
//����������������������������������������
#ifndef _PARTICLE_H_		//���̃}�N������`����ĂȂ�������
#define _PARTICLE_H_		//2�d�C���N���[�h�h�~�̃}�N����`

#pragma push_macro("new")
#undef new
#include <d3dx9.h>
#pragma pop_macro("new")
#include "task.h"

class CObject;

//-------------------------------------------------
// �p�[�e�B�N���N���X
// Author : Tanaka Kouta
// Author : Yuda Kaito
// Author ; hamada 
// �T�v : �p�[�e�B�N���̏�����S������N���X
//-------------------------------------------------
class CParticle : public CTask
{
public:	// �萔
	static const int maxNumber = 21000;
	static const int numType = 10;
public:	// �ÓI�ϐ�
public: // �\����

	//-------------------------------------------------
	// �e�N�X�`�����
	// Author : 
	// �T�v : �e�N�X�`���Ɋւ���f�[�^�\����
	//-------------------------------------------------
	struct SParticleTex
	{
		D3DXVECTOR3 pos;
		D3DXCOLOR col;
		float size;
	};

	//-------------------------------------------------
	// �G�t�F�N�g�̃J���[�\����
	// Author : �������l
	// Author ; hamada 
	// �T�v : �G�t�F�N�g�̐F�֌W�̍\����
	//-------------------------------------------------
	struct SColor	// ���V�K�ǉ��\����(�t�@�C���ɒǉ�������Ă�������)
	{
		D3DXCOLOR colBigin;			// �n�܂�̐F
		D3DXCOLOR colRandamMax;		// �����_���ȐF�͈̔�(�ő�)
		D3DXCOLOR colRandamMin;		// �����_���ȐF�͈̔�(�ŏ�)
		D3DXCOLOR colTransition;	// �F�̑J�ڗ�
		D3DXCOLOR destCol;			// �ړI�̐F
		int nEndTime;				// �J�ڊ����܂ł̎���			���V�K�ǉ��ϐ�(�t�@�C���ɒǉ�������Ă�������)
		int nCntTransitionTime;		// �J�ڃJ�E���g					���V�K�ǉ��ϐ�(�t�@�C���ɒǉ�������Ă�������)
		bool bColTransition;		// �J���[�J��					���V�K�ǉ��ϐ�(�t�@�C���ɒǉ�������Ă�������)
		bool bColRandom;			// �����_���J���[				���V�K�ǉ��ϐ�(�t�@�C���ɒǉ�������Ă�������)
		bool bRandomTransitionTime;	// �J�ڎ��Ԃ̗���				���V�K�ǉ��ϐ�(�t�@�C���ɒǉ�������Ă�������)
	};

	//-------------------------------------------------
	// �G�t�F�N�g�̃��u�����h�̎�ʂ̗񋓌^
	// Author : �������l
	// Author ; hamada
	// �T�v : ��Z�A���Z�A���Z
	//-------------------------------------------------
	enum EAlphaBlebdType
	{
		TYPE_ADD = 0,		// ���Z
		TYPE_SUB,			// ���Z
		TYPE_NONE,			// ��Z
		MAX_TYPE,			// ��ʂ̍ő吔
	};

	//-------------------------------------------------
	//�G�t�F�N�g�̍\���̂̒�`
	// Author : Tanaka Kouta
	// Author : Yuda Kaito
	// Author : Hamada Ryuga
	// Author : �������l
	//-------------------------------------------------
	struct SInfo
	{
		D3DXVECTOR3 move;				// �ړ���
		D3DXVECTOR3 moveTransition;		// �ړ��ʂ̐��ڗ�
		D3DXVECTOR3 rot;				// ����
		SColor color;					// �J���[
		EAlphaBlebdType alphaBlend;		// ���u�����f�B���O�̎��
		D3DXVECTOR3 scaleTransition;	// �T�C�Y�̐��ڗ�			���V�K�ǉ��ϐ�(�t�@�C���ɒǉ�������Ă�������)
		float fWidth;					// ��
		float fHeight;					// ����
		float fAngle;					// �p�x
		float fAttenuation;				// �����l
		float fRadius;					// ���a
		float fWeight;					// �d��
		float fWeightTransition;		// �d���̐��ڗ�
		float fScale;					// �S�̓I�ȑ傫��
		unsigned int nLife;				// ����
		unsigned int nMaxLife;			// �ő����
		int nMoveTime;					//							�����g�p�ϐ�
		int nIdxTex;					// �e�N�X�`���̔ԍ�
		bool bUseWeight;				// �d�����g�p���邩�ǂ���
		bool bBackrot;					// �t��]�����邩�ǂ���
		bool bTexturerot;				// �e�N�X�`����]�����邩�ǂ���
	};

public:
	CParticle();
	~CParticle();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	static CParticle* Create(CObject* inObject,const SInfo& inParticle, const D3DXVECTOR3& inPos);
	void LoadTex();
	DWORD FloattoDword(float fVal);

private:	// �����o�[�ϐ�
	CObject* m_object;
	SInfo m_data;
	int m_idx;
};
#endif
