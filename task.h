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
#include "task_group.h"

//=============================================================================
// タスククラス
//=============================================================================
class CTask
{
public:
	CTask(unsigned int inPriority = 2, CTaskGroup::EPushMethod inMethod = CTaskGroup::EPushMethod::PUSH_CURRENT);
	virtual ~CTask();

	virtual HRESULT Init() = 0;
	virtual void Uninit();
	virtual void Update() {}
	virtual void Draw() {}

	void Release() { m_isDeleted = true; }

	// リスト構造
	void SetPrev(CTask* inTask) { m_prev = inTask; }
	CTask* GetPrev() { return m_prev; }
	void SetNext(CTask* inTask) { m_next = inTask; }
	CTask* GetNext() { return m_next; }

	// 破棄予定
	bool IsDeleted() { return m_isDeleted; }

	// 破棄を保護する
	void AttachProtect() { m_isProtect = true; }
	bool IsProtect() { return m_isProtect; }

private:
	CTask* m_prev;		// 前のタスク
	CTask* m_next;		// 後のタスク

	// 親子関係
	CTask* m_pearent;	// 親
	std::list<CTask*> m_childrens;	// 子

	bool m_isDeleted;	// 破棄予定
	bool m_isProtect;	// 全体破棄から保護する
};
#endif
