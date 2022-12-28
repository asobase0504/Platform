//=============================================================================
//
// �I�u�W�F�N�g
// AUthor : Yuda Kaito
//
//=============================================================================
#ifndef _OBJECT_H_			// ���̃}�N����`������ĂȂ�������
#define _OBJECT_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "renderer.h"
#include "task.h"

//-----------------------------------------------------------------------------
// ��ʏ�ɕ\������p���N���X
//-----------------------------------------------------------------------------
class CObject : public CTask
{
public:
	enum EType
	{
		ENEMY = 0,
		PLAYER,
		MODEL,
		BG,
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

	// �X�V
	void Update() override final;
	void SetUpdateStatus(const EUpdateStatus inStatus) { m_updateStatus = inStatus; }

	/* ��ތn */
	void SetType(const EType inType) { m_type = inType; }
	EType GetType() { return m_type; }
	static CObject* SearchType(EType inType, int inPriority);
	CObject* NextSameType();

	/* �ʒu�n */
	virtual void SetPos(const D3DXVECTOR3 &inPos) { m_pos = inPos; }
	void SetPos(const float x, const float y,const float z) { SetPos(D3DXVECTOR3(x,y,z)); }
	void AddPos(const D3DXVECTOR3 &inPos) { SetPos(m_pos + inPos); }
	void AddPos(const float x, const float y, const float z) { SetPos(m_pos + D3DXVECTOR3(x, y, z)); }
	void MulPos(const float inRatio) { SetPos(m_pos * inRatio); }
	const D3DXVECTOR3 &GetPos() const { return m_pos; }
	void SetPosX(const float x) { SetPos(D3DXVECTOR3(x, m_pos.y, m_pos.z)); }
	void AddPosX(const float x) { SetPosX(m_pos.x + x); }
	void MulPosX(const float inRatio) { SetPosX(m_pos.x * inRatio); }
	void SetPosY(const float y) { SetPos(D3DXVECTOR3(m_pos.z, y, m_pos.z)); }
	void AddPosY(const float y) { SetPosY(m_pos.y + y); }
	void MulPosY(const float inRatio) { SetPosY(m_pos.y * inRatio); }
	void SetPosZ(const float z) { SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, z)); }
	void AddPosZ(const float z) { SetPosZ(m_pos.z + z); }
	void MulPosZ(const float inRatio) { SetPosZ(m_pos.z * inRatio); }

	/* �ړ��n */
	virtual void SetMove(const D3DXVECTOR3 &inMove) { m_move = inMove; }
	void SetMove(const float x, const float y, const float z) { SetMove(D3DXVECTOR3(x, y, z)); }
	void AddMove(const D3DXVECTOR3 &inMove) { SetMove(m_move + inMove); }
	void AddMove(const float x, const float y, const float z) { SetMove(m_move + D3DXVECTOR3(x, y, z)); }
	void MulMove(const float &inRatio) { SetMove(m_move * inRatio); }
	const D3DXVECTOR3 &GetMove() const { return m_move; }

	/* ��]�n */
	virtual void SetRot(const D3DXVECTOR3 &inRot) { m_rot = inRot; }
	void SetRot(const float x, const float y, const float z) { SetRot(D3DXVECTOR3(x, y, z)); }
	void AddRot(const D3DXVECTOR3 &inRot) { SetRot(m_rot + inRot); }
	void AddRot(const float x, const float y, const float z) { SetRot(m_rot + D3DXVECTOR3(x, y, z)); }
	void MulRot(const float &inRatio) { SetRot(m_rot * inRatio); }
	const D3DXVECTOR3 &GetRot() const { return m_rot; }
	void SetRotX(const float x) { SetRot(D3DXVECTOR3(x, m_rot.y, m_rot.z)); }
	void AddRotX(const float x) { SetRotX(m_rot.x + x); }
	void MulRotX(const float inRatio) { SetRotX(m_rot.x * inRatio); }
	void SetRotY(const float y) { SetRot(D3DXVECTOR3(m_rot.z, y, m_rot.z)); }
	void AddRotY(const float y) { SetRotY(m_rot.y + y); }
	void MulRotY(const float inRatio) { SetRotY(m_rot.y * inRatio); }
	void SetRotZ(const float z) { SetRot(D3DXVECTOR3(m_rot.x, m_rot.y, z)); }
	void AddRotZ(const float z) { SetRotZ(m_rot.z + z); }
	void MulRotZ(const float inRatio) { SetRotZ(m_rot.z * inRatio); }

	/* �傫���n */
	virtual void SetSize(const D3DXVECTOR3 &inSize) { m_size = inSize; }
	void SetSize(const float x, const float y, const float z) { SetSize(D3DXVECTOR3(x, y, z)); }
	void AddSize(const D3DXVECTOR3 &inSize) { SetSize(m_size + inSize); }
	void AddSize(const float x, const float y, const float z) { SetSize(m_size + D3DXVECTOR3(x, y, z)); }
	void MulSize(const float &inRatio) { SetSize(m_size * inRatio); }
	const D3DXVECTOR3 &GetSize() const { return m_size; }

	/* �F�n */
	virtual void SetColor(const D3DXCOLOR &inColor) { m_color = inColor; }
	void SetColor(const float r, const float g, const float b, const float a) { SetColor(D3DXCOLOR(r, g, b, a)); }
	void AddColor(const D3DXCOLOR &inColor) { SetColor(m_color + inColor); }
	void AddColor(const float r, const float g, const float b, const float a) { SetColor(m_color + D3DXCOLOR(r, g, b, a)); }
	void MulColor(const float &inRatio) { SetColor(m_color * inRatio); }
	const D3DXCOLOR &GetColor() const { return m_color; }
	// �����F�̂�
	virtual void SetColorAlpha(float inAlpha) { SetColor(D3DXCOLOR(m_color.r, m_color.g, m_color.b, inAlpha)); }
	void AddColorAlpha(float inAlpha) { SetColorAlpha(m_color.a + inAlpha); }
	void MulColorAlpha(float inRatio) { SetColorAlpha(m_color.a * inRatio); }
	float GetColorAlpha() const { return m_color.a; }

	/* �e�X�N�`���n */
	void SetTexture(std::string inKey) { m_textureKey = inKey; }
	std::string GetTexture() { return m_textureKey; }

protected:
	virtual void PopUpdate() { SetUpdateStatus(EUpdateStatus::NORMAL); }
	virtual void NormalUpdate() {}
	virtual void EndUpdate() {}

private:
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