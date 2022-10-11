//=============================================================================
//
// 根幹クラス
// Author : Yuda Kaito
//
//=============================================================================
#ifndef _TASK_H_			// このマクロ定義がされてなかったら
#define _TASK_H_			// 二重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include <Windows.h>
#include <list>

//=============================================================================
// タスククラス
//=============================================================================
class CTask
{
public:
	CTask() {}
	virtual ~CTask() {}

	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() {}
	virtual void Draw() {}

	// Getter
	CTask* GetParent() { return m_parent; }
	std::list<CTask*> GetChildrens() { return m_childrens; }

private:

	CTask* m_parent;
	std::list<CTask*> m_childrens;
};

#endif
