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
	enum EUpdateStatus
	{
		POP = 0,
		NORMAL,
		END,
		Max
	};

public:
	CObject(int inList = 0);
	virtual ~CObject() override;

	void Update() override;

	// Setter
	/* �ʒu�n */
	virtual void SetPos(const D3DXVECTOR3 &inPos) { m_pos = inPos; }
	void SumPos(const D3DXVECTOR3 &inPos) { SetPos(m_pos + inPos); }
	void MulPos(const float inRatio) { SetPos(m_pos * inRatio); }

	/* �ړ��n */
	virtual void SetMove(const D3DXVECTOR3 &inMove) { m_move = inMove; }
	void SumMove(const D3DXVECTOR3 &inMove) { SumMove(m_move += inMove); }
	void MulMove(const float &inRatio) { SumMove(m_move * inRatio); }

	void SetUp(const EType inType);
	void SetUpdateStatus(const EUpdateStatus inStatus) { m_updateStatus = inStatus; }

	// Getter
	const D3DXVECTOR3 *GetPos() const { return &m_pos; }
	const D3DXVECTOR3 *GetMove() const { return &m_move; }

	EType GetType();

private:
	virtual void PopUpdate();
	virtual void NormalUpdate();
	virtual void EndUpdate();

protected:
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_move;	// �ړ���
private:
	EType m_type;	// ���
	
	EUpdateStatus m_updateStatus;	// �X�V���
	bool m_isPopInNormalUpdate;		// �o�����ɒʏ�X�V���s����
	bool m_isEndInNormalUpdate;		// �I�����ɒʏ�X�V���s����
};
#endif