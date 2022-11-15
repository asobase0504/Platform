//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// Author  : Yuda Kaito
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "application.h"
#include "renderer.h"
#include "texture.h"
#include "file.h"

#include <assert.h>

CTexture* CTexture::m_pTexture = nullptr;

//--------------------------------------------------
// �C���X�^���X�̎擾
//--------------------------------------------------
CTexture * CTexture::GetInstance()
{
	if (m_pTexture == nullptr)
	{
		m_pTexture = new CTexture;
	}
	return m_pTexture;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTexture::CTexture()
{
	m_texturePath.clear();
	m_texture.clear();
	m_createIndex.clear();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void CTexture::LoadAll()
{
	nlohmann::json list = LoadJsonStage(L"Data/FILE/texture.json");
	
	for (int i = 0; i < (int)list["TEXTURE"].size(); ++i)
	{
		m_texturePath.insert(std::make_pair(list["TEXTURE"].at(i)[0], list["TEXTURE"].at(i)[1]));
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CTexture::Load(std::string inKey, std::string inFileName)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	LPDIRECT3DTEXTURE9 texture = nullptr;
	std::string fileName = inFileName;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, &fileName.front(), &texture);

	assert(texture != nullptr);	// �e�N�X�`����URL���Ȃ����L�[���Ԉ���Ă�B


	if (!ExistsKey(inKey))
	{
		m_texture.insert(std::make_pair(inKey, texture));
	}
	else
	{
		m_texture[inKey] = texture;
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CTexture::Load(std::vector<std::string> inTexture)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	LPDIRECT3DTEXTURE9 texture = nullptr;
	std::string fileName = inTexture[1];

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, &fileName.front(), &texture);

	assert(texture != nullptr);	// �e�N�X�`����URL���Ȃ����L�[���Ԉ���Ă�B

	if (!ExistsKey(inTexture[0]))
	{
		m_texture.insert(std::make_pair(inTexture[0], texture));
	}
	else
	{
		m_texture[inTexture[0]] = texture;
	}
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CTexture::UnloadAll()
{
	m_texture.clear();
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CTexture::Unload(std::string inKey)
{
	m_texture.erase(inKey);
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTexture(std::string inKey)
{
	// Key�����݂��邩�ۂ��B
	if (!ExistsPath(inKey))
	{
		// Key���Ȃ������ꍇ
		return nullptr;
	}

	// Key�����݂��邩�ۂ��B
	if (!ExistsKey(inKey))
	{
		Load(inKey, m_texturePath[inKey]);
	} 

	/* ��Key���������ꍇ�� */

	return m_texture[inKey];
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture(int inKey)
{
	if (m_createIndex.count(inKey) == 0)
	{
		return nullptr;
	}

	return GetTexture(m_createIndex.at(inKey));
}

int CTexture::SetTexture(std::string inKey)
{
	for (int i = 0; i < m_maxIndex; i++)
	{
		// Key�����݂��邩
		if (m_createIndex.count(i) == 0)
		{
			continue;
		}

		// �����ƈ�v���邩
		if (m_createIndex.at(i) == inKey)
		{
			return i;
		}
	}

	// ������Ȃ������ꍇ�B
	return -1;
}
