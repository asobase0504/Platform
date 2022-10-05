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

//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------
class CScore;
class CBg;

//=============================================================================
// オブジェクトクラス
//=============================================================================
class CObject
{
public:
	enum EObjectType
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
	CObject(int inList = 0);
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static void AllUpdate();
	static void TypeUpdate(const EObjectType inType);
	static void AllDraw();
	static void AllUninit();
	static void AllCreate();
	static void ModeNotUninit();
	static void TypeDraw(const EObjectType inType);

	static int& GetMaxEnemy() { return m_allEnemy; };
	static bool& GetMaxBoss() { return m_notBoss; };
	static CBg* GetBg(int inNumber) { return pBg[inNumber]; };
	static void SetBossPop(bool inBoss) { m_notBoss = inBoss; };
	int* GetId();
	CObject** GetObjectData(int inCount);
	void SetUp(const EObjectType inType);

	void Release();

	EObjectType GetType();
	CScore* GetScore();

protected:
	static CObject *m_pObject[MAX_LIST][MAX_OBJECT];
	int	m_id;
	int m_list;
	static int m_allEnemy;
	static bool m_notBoss;
private:
	EObjectType m_type;
	static int m_allMember;
	static CScore* pScore;
	static CBg* pBg[3];
};
#endif