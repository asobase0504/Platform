//=============================================================================
//
// オブジェクト
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _OBJECT_H_			// このマクロ定義がされてなかったら
#define _OBJECT_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"

class CScore;
class CBg;

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
	CObject(int list = 0);
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;


	static void AllUpdate();
	static void TypeUpdate(EObjectType Type);
	static void AllDraw();
	static void AllUninit();
	static void AllCreate();
	static void ModeNotUninit();
	static void TypeDraw(EObjectType Type);

	static int& GetMaxEnemy() { return m_AllEnemy; };
	static bool& GetMaxBoss() { return notBoss; };
	static CBg* GetBg(int number) { return  Bg[number]; };
	static void SetBossPop(bool Boss) { notBoss = Boss; };
	int * GetId();
	CObject ** GetObjectData(int nCount);
	void SetUp(EObjectType Type);

	void Release();
	EObjectType GetType();

	CScore*GetScore();

protected:
	static CObject *m_pObject[MAX_LIST][MAX_OBJECT];
	int	m_nID;
	int m_list;
	static int m_AllEnemy;
	static bool notBoss;
private:
	//int	m_nID;
	EObjectType m_Type;
	static int m_AllMember;
	static CScore * pScore;
	static CBg * Bg[3];


};
#endif