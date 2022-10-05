//=============================================================================
//
// �I�u�W�F�N�g
// Author : Hamada Ryuuga
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "object.h"
#include "object2d.h"
#include "player.h"
#include "manager.h"

#include "score.h"
#include "bg.h"
#include "life.h"
#include <assert.h>
#include "game.h"
#include "pause.h"

//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------
CObject *CObject::m_pObject[MAX_LIST][MAX_OBJECT] = {};
int CObject::m_allMember = 0; 
int CObject::m_allEnemy = 0;
CScore * CObject::pScore;
bool CObject::m_notBoss = false;
CBg * CObject::pBg[3];

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject::CObject(int list)
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[list][i] == nullptr)
		{
			m_type = NONE;
			m_list = list;
			m_id = i;
			m_pObject[list][i] = this;
			m_allMember++;
			break;
		}
	}
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
// �S�Ă̍X�V
//=============================================================================
void CObject::AllUpdate()
{
	for (int i= 0; i < MAX_LIST; i++)
	{
		for (int j = 0; j < MAX_OBJECT; j++)
		{

			if (m_pObject[i][j] != nullptr)
			{
				m_pObject[i][j]->Update();
			}
		}
	}
}

//=============================================================================
// ��ނ̍X�V
//=============================================================================
void CObject::TypeUpdate(EObjectType Type)
{
	for (int i= 0; i < MAX_LIST; i++)
	{
		for (int j = 0; j < MAX_OBJECT; j++)
		{
			if (m_pObject[i][j] != nullptr)
			{
				if (m_pObject[i][j]->m_type == Type)
				{
					m_pObject[i][j]->Update();
				}
			}
		}
	}
}

//=============================================================================
// �S�Ă̕`��
//=============================================================================
void CObject::AllDraw()
{
	for (int i = 0; i < MAX_LIST; i++)
	{
		for (int j = 0; j < MAX_OBJECT; j++)
		{
			if (m_pObject[i][j] != nullptr)
			{
				m_pObject[i][j]->Draw();
			}
		}
	}
}

//=============================================================================
// ��ނ̕`��
//=============================================================================
void CObject::TypeDraw(EObjectType Type)
{
	for (int i = 0; i < MAX_LIST; i++)
	{
		for (int j = 0; j < MAX_OBJECT; j++)
		{
			if (m_pObject[i][j] != nullptr)
			{
				if (m_pObject[i][j]->m_type == Type)
				{
					m_pObject[i][j]->Draw();
				}
			}
		}
	}
}

//=============================================================================
// �S�Ă̏I��
//=============================================================================
void CObject::AllUninit()
{
	for (int i = 0; i < MAX_LIST; i++)
	{
		for (int j = 0; j < MAX_OBJECT; j++)
		{
			if (m_pObject[i][j] != nullptr)
			{
				m_pObject[i][j]->Uninit();
				delete m_pObject[i][j];
				m_pObject[i][j] = nullptr;
			}

		}
	}
	m_allMember = 0;
}

//=============================================================================
// ���[�h�ȊO�̏I��
//=============================================================================
void CObject::ModeNotUninit()
{
	for (int i = 0; i < MAX_LIST; i++)
	{
		for (int j = 0; j < MAX_OBJECT; j++)
		{
			if (m_pObject[i][i] != nullptr)
			{
				if (m_pObject[i][j]->m_type != MODE)
				{
					m_pObject[i][j]->Uninit();
					delete m_pObject[i][j];
					m_pObject[i][j] = nullptr;
				}
			}
		}
	}
	m_allMember = 1;
}
//=============================================================================
// �S�Ă̐���
//=============================================================================
void CObject::AllCreate()
{
	pBg[0] = CBg::Create();
	pBg[0]->SetMove(D3DXVECTOR3(0.0001f, 0.0f, 0.0f));
	pBg[0]->SetTexture(CTexture::TEXTURE_STARRY);
	pBg[0]->SetBgType(CBg::MOVE);

	pBg[1] = CBg::Create();
	pBg[1]->SetMove(D3DXVECTOR3(0.001f, 0.0f, 0.0f));
	pBg[1]->SetTexture(CTexture::TEXTURE_TOWN);
	pBg[1]->SetBgType(CBg::MOVE);

	pBg[2] = CBg::Create();
	pBg[2]->SetTexture(CTexture::TEXTURE_MOON);
	pBg[2]->SetBgType(CBg::STOP);
	

	pScore = CScore::Create(D3DXVECTOR3(500.0f, 30.0f, 0.0f));
	pScore->Set(0);
}

//=============================================================================
// �^�C�v�̐ݒ�
//=============================================================================
void CObject::SetUp(EObjectType inType)
{
	switch (inType)
	{
	case EObjectType::ENEMY:
		m_type = ENEMY;
		m_allEnemy++;
		break;
	case EObjectType::PLAYER:
		m_type = PLAYER;
		break;
	case EObjectType::BULLET:
		m_type = BULLET;
		break;
	case EObjectType::GON:
		m_type = GON;
		break;
	case EObjectType::MAGIC:
		m_type = MAGIC;
		break;
	case EObjectType::CRYSTAL:
		m_type = CRYSTAL;
		break;
	case EObjectType::BG:
		m_type = BG;
		break;
	case EObjectType::MODE:
		m_type = MODE;
		break;
	case EObjectType::PAUSE:
		m_type = PAUSE;
		break;
	default:
		assert(false);
		break;
	}
}

//=============================================================================
// ���
//=============================================================================
void CObject::Release()
{
	if (m_pObject[m_list][m_id] != nullptr)
	{
		const int nID = m_id;
		const int nlist = m_list;
		delete m_pObject[nlist][nID];
		m_pObject[nlist][nID] = nullptr;
		m_allMember--;
	}
}

//=============================================================================
// �I�u�W�F�N�g�̎擾
//=============================================================================
CObject** CObject::GetObjectData(int inCount)
{
	return m_pObject[inCount];
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
CScore* CObject::GetScore()
{
	return pScore;
}

//=============================================================================
// �ԍ��̎擾
//=============================================================================
int* CObject::GetId()
{
	return &m_id;
}

//=============================================================================
// �^�C�v�̎擾
//=============================================================================
CObject::EObjectType CObject::GetType()
{
	return m_type;
}
