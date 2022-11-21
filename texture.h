//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// Author  : Yuda Kaito
// 
//**************************************************
#ifndef _TEXTURE_H_	//���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include <vector>
#include <unordered_map>
#include <string>

//==================================================
// ��`
//==================================================
class CTexture
{
private: // �ÓI�����o�[�ϐ�
	static CTexture* m_pTexture;

public: // �ÓI�֐�
	static CTexture* GetInstance();

private: // �V���O���g��
	CTexture();

public:
	~CTexture();	// �f�X�g���N�^

public: /* �p�u���b�N�֐� */
	void LoadAll();					// �S�Ă̓ǂݍ���
	void UnloadAll();				// �S�Ă̔j��
	void Load(std::string inKey, std::string inFileName);	// �w��̓ǂݍ���
	void Load(std::vector<std::string> inTexture);			// �w��̓ǂݍ���
	void Unload(std::string inKey);	// �w��̔j��
	LPDIRECT3DTEXTURE9 GetTexture(std::string inKey);	// ���̎擾
	LPDIRECT3DTEXTURE9 GetTexture(int inKey);	// ���̎擾
	int SetTexture(std::string inKey);	// ���̎擾

private: /* �v���C�x�[�g�֐� */
	bool ExistsPath(std::string inKey) { return m_texturePath.count(inKey) != 0; }	// Map���Ɏw�肳�ꂽKey�����݂��邩�ۂ�
	bool ExistsKey(std::string inKey) { return m_texture.count(inKey) != 0; }		// Map���Ɏw�肳�ꂽKey�����݂��邩�ۂ�

private: /* �����o�ϐ� */
	std::unordered_map<std::string, std::string> m_texturePath;		// �p�X
	std::unordered_map<std::string, LPDIRECT3DTEXTURE9> m_texture;	// ���
	std::unordered_map<int, std::string > m_createIndex;			// ������
	int m_maxIndex;	// �ő吶����
};

#endif // !_TEXTURE_H_
