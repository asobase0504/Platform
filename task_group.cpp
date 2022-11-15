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
	m_priorityNumber(0)
{
	m_list.clear();
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
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		if (m_list.count(i) == 0)
		{
			continue;
		}

		CTask* current = m_list.at(i).top;

		while (current != nullptr)
		{
			CTask* next = current->GetNext();
			current->Uninit();
			current = next;
		}
	}

	DeleteTask();	// タスクリストの削除
}

//=============================================================================
// 更新
//=============================================================================
void CTaskGroup::Update()
{
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		if (m_list.count(i) == 0)
		{
			continue;
		}

		CTask* now = m_list.at(i).top;

		while (now != nullptr)
		{
			CTask* next = now->GetNext();
			now->Update();
			now = next;
		}

		DeleteTask();	// タスクリストの削除
	}
}

//=============================================================================
// 描画
//=============================================================================
void CTaskGroup::Draw()
{
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		if (m_list.count(i) == 0)
		{
			continue;
		}

		CTask* now = m_list.at(i).top;

		while (now != nullptr)
		{
			CTask* next = now->GetNext();
			now->Draw();
			now = next;
		}
	}
}

//=============================================================================
// 所持しているタスクの破棄
//=============================================================================
void CTaskGroup::AllRelease()
{
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		if (m_list.count(i) == 0)
		{
			continue;
		}

		CTask* now = m_list.at(i).top;

		while (now != nullptr)
		{
			if (!now->IsProtect())
			{
				now->Release();
			}
			now = now->GetNext();
		}
	}

	// 死亡予定のタスクの破棄
	DeleteTask();
}

//=============================================================================
// 絶対にタスクを破棄
//=============================================================================
void CTaskGroup::AbsolutelyRelease()
{
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		if (m_list.count(i) == 0)
		{
			continue;
		}

		CTask* now = m_list.at(i).top;

		while (now != nullptr)
		{
			now->Release();
			now = now->GetNext();
		}
	}

	// 死亡予定のタスクの破棄
	DeleteTask();
}

//=============================================================================
// 指定したpriorityのタスクを破棄
//=============================================================================
void CTaskGroup::PriorityRelease(const int inPriotity)
{
	if (m_list.count(inPriotity) == 0)
	{
		return;
	}

	CTask* now = m_list.at(inPriotity).top;

	while (now != nullptr)
	{
		if (!now->IsProtect())
		{
			now->Release();
		}
		now = now->GetNext();
	}
}

//=============================================================================
// リストの最後にタスクを入れる
//=============================================================================
void CTaskGroup::SetPushCurrent(CTask * inTask, int inPriority)
{
	if (m_list.count(inPriority) == 0)
	{
		SList inList;
		inList.top = nullptr;
		inList.current = nullptr;
		m_list.insert(std::make_pair(inPriority, inList));
		m_priorityNumber = inPriority;
	}

	SList* list = &m_list.at(inPriority);

	if (list->current == nullptr && list->top == nullptr)
	{
		list->top = inTask;
		list->current = inTask;
	}
	else
	{
		CTask* current = list->current;		// 前回末尾
		list->current = inTask;				// 新規末尾
		list->current->SetPrev(current);	// 新規末尾の前に前回末尾を設定
		current->SetNext(list->current);	// 前回末尾の後に新規末尾を設定
	}
}

//=============================================================================
// リストの最初にタスクを入れる
//=============================================================================
void CTaskGroup::SetPushTop(CTask * inTask, int inPriority)
{
	if (m_list.count(inPriority) == 0)
	{
		SList inList;
		m_list.insert(std::make_pair(inPriority, inList));
		m_list.at(inPriority).top = nullptr;
		m_list.at(inPriority).current = nullptr;
	}

	if (m_list.at(inPriority).current == nullptr && m_list.at(inPriority).top == nullptr)
	{
		m_list.at(inPriority).top = inTask;
		m_list.at(inPriority).current = inTask;
	}
	else
	{
		CTask* top = m_list.at(inPriority).top;		// 前回先頭
		m_list.at(inPriority).top = inTask;			// 新規先頭
		m_list.at(inPriority).top->SetNext(top);	// 新規先頭の次に前回先頭を設定
		top->SetPrev(m_list.at(inPriority).top);	// 新規先頭の後に新規先頭を設定
	}
}

//=============================================================================
// 参照したタスクの次にタスクを入れる
//=============================================================================
void CTaskGroup::SetNextTask(CTask * inReference, CTask * inTask)
{
	if (inReference == nullptr)
	{
		SetPushCurrent(inTask, 0);
		return;
	}
}

//=============================================================================
// 参照したタスクの前にタスクを入れる
//=============================================================================
void CTaskGroup::SetPrevTask(CTask * inReference, CTask * inTask)
{
	if (inReference == nullptr)
	{
		SetPushCurrent(inTask);
		return;
	}
}

//=============================================================================
// タスクの削除
//=============================================================================
void CTaskGroup::DeleteTask()
{
	for (int i = 0; i <= m_priorityNumber; i++)
	{
		if (m_list.count(i) == 0)
		{
			continue;
		}

		CTask* now = m_list.at(i).top;

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
				m_list.at(i).top = next;
				next->SetPrev(nullptr);
			}
			else if (isNextNullptr && !isPrevNullptr)
			{
				m_list.at(i).current = prev;
				prev->SetNext(nullptr);
			}
			else
			{
				m_list.at(i).current = nullptr;
				m_list.at(i).top = nullptr;
			}

			now->Uninit();
			delete now;	// 削除
			now = next;	// 次のタスクに移る
		}
	}
}
