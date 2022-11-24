//=============================================================================
//
// ªŠ²ƒNƒ‰ƒX
// Author : Yuda Kaito
//
//=============================================================================
#include "task.h"
#include <assert.h>
#include "application.h"
#include "task_group.h"

CTask::CTask(CTaskGroup::EPriority inPriority, CTaskGroup::EPushMethod inMethod) :
	m_prev(nullptr),
	m_next(nullptr),
	m_isDeleted(false),
	m_isProtect(false)
{
	switch (inMethod)
	{
	case CTaskGroup::PUSH_CURRENT:
		CApplication::GetInstance()->GetTaskGroup()->SetPushCurrent(this, inPriority);
		break;
	case CTaskGroup::PUSH_TOP:
		CApplication::GetInstance()->GetTaskGroup()->SetPushTop(this, inPriority);
		break;
	default:
		assert(false);
		break;
	}
}

CTask::~CTask()
{
}

void CTask::Uninit()
{
	Release();
}
