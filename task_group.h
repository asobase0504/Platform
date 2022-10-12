//=============================================================================
//
// タスクの集まり
// Author : Yuda Kaito
//
//=============================================================================
#ifndef _TASK_GROUP_H_			// このマクロ定義がされてなかったら
#define _TASK_GROUP_H_			// 二重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include <Windows.h>

//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------
class CTask;

//=============================================================================
// タスククラス
//=============================================================================
class CTaskGroup
{
public:
	CTaskGroup();
	~CTaskGroup();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// Setter
	void SetPushCurrent(CTask* inTask);
	void SetPushTop(CTask* inTask);
	void SetNextTask(CTask* inReference, CTask* inTask);
	void SetPrevTask(CTask* inReference, CTask* inTask);

	// Getter
	CTask* GetTop() { return m_top; }
	CTask* GetCurrent() { return m_current; }

private:
	void DeleteTask();

private:
	CTask* m_top;
	CTask* m_current;
};

#endif
