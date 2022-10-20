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
	CTask(CTaskGroup::EPushMethod inMethod = CTaskGroup::EPushMethod::PUSH_CURRENT, int inPriority = 2);
	virtual ~CTask();

	virtual HRESULT Init() = 0;
	virtual void Uninit();
	virtual void Update() {}
	virtual void Draw() {}

	void Release() { m_isDeleted = true; }

	// Setter
	void SetPrev(CTask* inTask) { m_prev = inTask; }
	void SetNext(CTask* inTask) { m_next = inTask; }
	void AttachProtect() { m_isProtect = true; }

	// Getter
	CTask* GetPrev() { return m_prev; }
	CTask* GetNext() { return m_next; }
	bool IsDeleted() { return m_isDeleted; }
	bool IsProtect() { return m_isProtect; }

private:
	CTask* m_prev;		// 前のタスク
	CTask* m_next;		// 後のタスク

	bool m_isDeleted;	// 破棄予定
	bool m_isProtect;	// 全体破棄から保護する
};
#endif
