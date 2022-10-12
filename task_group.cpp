//=============================================================================
//
// マネージャー
// Author : Yuda Kaito
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "task_group.h"
#include "task.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTaskGroup::CTaskGroup() :
	m_top(nullptr),
	m_current(nullptr)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTaskGroup::~CTaskGroup()
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CTaskGroup::Init()
{
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CTaskGroup::Uninit()
{
	CTask* current = m_top;

	while (current != nullptr)
	{
		CTask* next = current->GetNext();
		current->Uninit();
		current = next;
	}
}

//=============================================================================
// 更新
//=============================================================================
void CTaskGroup::Update()
{
	CTask* now = m_top;

	while (now != nullptr)
	{
		CTask* next = now->GetNext();
		now->Update();
		now = next;
	}
	
	DeleteTask();	// タスクリストの削除
}

//=============================================================================
// 描画
//=============================================================================
void CTaskGroup::Draw()
{
	CTask* now = m_top;

	while (now != nullptr)
	{
		CTask* next = now->GetNext();
		now->Draw();
		now = next;
	}
}

//=============================================================================
// リストの最後にタスクを入れる
//=============================================================================
void CTaskGroup::SetPushCurrent(CTask * inTask)
{
	if (m_current == nullptr && m_top == nullptr)
	{
		m_top = inTask;
		m_current = inTask;
	}
	else
	{
		CTask* current = m_current;	// 前回の末尾
		m_current = inTask;	// 新しい末尾
		m_current->SetPrev(current);	// 新しい末尾の前を前回の末尾を設定
		current->SetNext(m_current);	// 前回の末尾の後ろに新しい末尾を設定
	}
}

//=============================================================================
// リストの最初にタスクを入れる
//=============================================================================
void CTaskGroup::SetPushTop(CTask * inTask)
{
}

//=============================================================================
// 参照したタスクの次にタスクを入れる
//=============================================================================
void CTaskGroup::SetNextTask(CTask * inReference, CTask * inTask)
{
}

//=============================================================================
// 参照したタスクの前にタスクを入れる
//=============================================================================
void CTaskGroup::SetPrevTask(CTask * inReference, CTask * inTask)
{
}

//=============================================================================
// タスクの削除
//=============================================================================
void CTaskGroup::DeleteTask()
{
	CTask* now = m_top;

	while (now != nullptr)
	{
		// 次のタスクを保存
		CTask* next = now->GetNext();
		CTask* prev = now->GetPrev();

		if (!now->IsDeleted())
		{
			now = next;	// 次のタスクに移る
			continue;
		}

		// 前後の状態を取得
		bool isNextNullptr = (next == nullptr);
		bool isPrevNullptr = (prev == nullptr);

		if (!isNextNullptr && !isPrevNullptr)
		{
			next->SetPrev(prev);
			prev->SetNext(next);
		}
		else if (!isNextNullptr && isPrevNullptr)
		{
			m_top = prev;
			prev->SetNext(next);
		}
		else if (isNextNullptr && !isPrevNullptr)
		{
			m_current = next;
			next->SetPrev(prev);
		}

		delete now;	// 削除
		now = next;	// 次のタスクに移る
	}
}
