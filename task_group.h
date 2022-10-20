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
#include <unordered_map>

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
	// リスト構造体
	struct SList
	{
		CTask* top;
		CTask* current;
	};

	// 追加方法
	enum EPushMethod
	{
		PUSH_CURRENT = 0,
		PUSH_TOP
	};

public:
	CTaskGroup();
	~CTaskGroup();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// Release
	void SecureRelease();
	void AllRelease();
	void PriorityRelease(const int inPriotity);

	// Setter
	void SetPushCurrent(CTask* inTask, int inPriority = 0);
	void SetPushTop(CTask* inTask, int inPriority = 0);
	void SetNextTask(CTask* inReference, CTask* inTask);
	void SetPrevTask(CTask* inReference, CTask* inTask);

	// Getter
	CTask* GetTop(int priority = 0) { return m_list.at(priority).top; }
	CTask* GetCurrent(int priority = 0) { return m_list.at(priority).current; }

private:
	void DeleteTask();

private:
	std::unordered_map<int,SList> m_list;	// リスト一覧
	int m_priorityNumber;	// レイヤー数
};

#endif
