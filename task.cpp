//=============================================================================
//
// ªŠ²ƒNƒ‰ƒX
// Author : Yuda Kaito
//
//=============================================================================
#include "task.h"
#include <assert.h>
#include "manager.h"
#include "task_group.h"

CTask::CTask(CTaskGroup::EPushMethod inMethod,int inPriority) :
	m_prev(nullptr),
	m_next(nullptr),
	m_isDeleted(false),
	m_isProtect(false)
{
	switch (inMethod)
	{
	case CTaskGroup::PUSH_CURRENT:
		CManager::GetInstance()->GetTaskGroup()->SetPushCurrent(this, inPriority);
		break;
	case CTaskGroup::PUSH_TOP:
		CManager::GetInstance()->GetTaskGroup()->SetPushTop(this, inPriority);
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
	m_isDeleted = true;
}
