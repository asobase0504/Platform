//=============================================================================
//
// �I�u�W�F�N�g
// Author : Hamada Ryuuga
//
//=============================================================================
#ifndef _OBJECT_H_			// ���̃}�N����`������ĂȂ�������
#define _OBJECT_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "renderer.h"
#include "task.h"

//=============================================================================
// �I�u�W�F�N�g�N���X
//=============================================================================
class CObject : public CTask
{
public:
	enum EType
	{
		ENEMY = 0,
		PLAYER,
		MODEL,
		BULLET,
		GON,
		MAGIC,
		CRYSTAL,
		BG,
		SORCERY,
		BELL,
		MODE,
		RANKUPBULLET,
		PAUSE,
		MAX,
		NONE
	};

	// �X�V��Ԃ̗�
	enum class EUpdateStatus
	{
		POP = 0,
		NORMAL,
		END,
		MAX
	};

public:
	CObject(CTaskGroup::EPriority inPriority = CTaskGroup::LEVEL_2D_BG, CTaskGroup::EPushMethod inMethod = CTaskGroup::EPushMethod::PUSH_CURRENT);
	virtual ~CObject() override;

	void Update() override final;
	void SetUpdateStatus(const EUpdateStatus inStatus) { m_updateStatus = inStatus; }

	/* �ʒu�n */
	virtual void SetPos(const D3DXVECTOR3 &inPos) { m_pos = inPos; }
	void AddPos(const D3DXVECTOR3 &inPos) { SetPos(m_pos + inPos); }
	void MulPos(const float inRatio) { SetPos(m_pos * inRatio); }
	const D3DXVECTOR3 &GetPos() const { return m_pos; }

	/* �ړ��n */
	virtual void SetMove(const D3DXVECTOR3 &inMove) { m_move = inMove; }
	void AddMove(const D3DXVECTOR3 &inMove) { SetMove(m_move + inMove); }
	void MulMove(const float &inRatio) { SetMove(m_move * inRatio); }
	const D3DXVECTOR3 &GetMove() const { return m_move; }

	/* ��]�n */
	virtual void SetRot(const D3DXVECTOR3 &inRot) { m_rot = inRot; }
	void AddRot(const D3DXVECTOR3 &inRot) { SetRot(m_rot + inRot); }
	void MulRot(const float &inRatio) { SetRot(m_rot * inRatio); }
	const D3DXVECTOR3 &GetRot() const { return m_rot; }

	/* �傫���n */
	virtual void SetSize(const D3DXVECTOR3 &inSize) { m_size = inSize; }
	void AddSize(const D3DXVECTOR3 &inSize) { SetSize(m_size + inSize); }
	void MulSize(const float &inRatio) { SetSize(m_size * inRatio); }
	const D3DXVECTOR3 &GetSize() const { return m_size; }

	/* �F�n */
	virtual void SetColor(const D3DXCOLOR &inColor) { m_color = inColor; }
	void AddColor(const D3DXCOLOR &inColor) { SetColor(m_color + inColor); }
	void MulColor(const float &inRatio) { SetColor(m_color * inRatio); }
	const D3DXCOLOR &GetColor() const { return m_color; }
	// �����x
	virtual void SetColorAlpha(float inAlpha) { m_color.a = inAlpha; }
	void AddColorAlpha(float inAlpha) { SetColorAlpha(m_color.a + inAlpha); }
	void MulColorAlpha(float inRatio) { SetColorAlpha(m_color.a * inRatio); }
	float GetColorAlpha() const { return m_color.a; }

	// ���
	void SetType(const EType inType) { m_type = inType; }
	EType GetType() { return m_type; }
	static CObject* SearchType(EType inType, int inPriority);
	CObject* NextSameType();

	/* �e�X�N�`���n */
	void SetTexture(std::string inKey) { m_textureKey = inKey; }
	std::string GetTexture() { return m_textureKey; }

protected:
	virtual void PopUpdate();
	virtual void NormalUpdate();
	virtual void EndUpdate();

protected:
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXVECTOR3 m_rot;	// ��]��
	D3DXVECTOR3 m_size;	// �傫��
	D3DXCOLOR m_color;	// �F

	EType m_type;	// ���
	std::string m_textureKey;	// �e�N�X�`���ɃA�N�Z�X����L�[
	
	EUpdateStatus m_updateStatus;	// �X�V���
	bool m_isPopInNormalUpdate;		// �o�����ɒʏ�X�V���s����
	bool m_isEndInNormalUpdate;		// �I�����ɒʏ�X�V���s����
};
#endif