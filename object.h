//=============================================================================
//
// オブジェクト
// Author : Hamada Ryuuga
//
//=============================================================================
#ifndef _OBJECT_H_			// このマクロ定義がされてなかったら
#define _OBJECT_H_			// 二重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "renderer.h"
#include "task.h"

//=============================================================================
// オブジェクトクラス
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

	const static int MAX_OBJECT = 2560;
	const static int MAX_LIST = 4;

public:
	CObject(int inList = 0);
	virtual ~CObject() override;

	virtual HRESULT Init() override = 0;
	virtual void Uninit() override = 0;
	virtual void Update() override = 0;
	virtual void Draw() override = 0;

	// Setter
	static void SetBossPop(bool inBoss) { m_notBoss = inBoss; };
	void SetUp(const EType inType);

	// Getter
	static int& GetMaxEnemy() { return m_allEnemy; };
	static bool& GetMaxBoss() { return m_notBoss; };
	int* GetId();
	CObject** GetObjectData(int inCount);
	EType GetType();

protected:
	static CObject *m_pObject[MAX_LIST][MAX_OBJECT];
	int	m_id;
	int m_list;
	static int m_allEnemy;
	static bool m_notBoss;
private:
	EType m_type;
	static int m_allMember;
};
#endif