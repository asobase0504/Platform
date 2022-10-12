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

CTask::CTask() :
	m_prev(nullptr),
	m_next(nullptr),
	m_isDeleted(false)
{
	CManager::GetInstance()->GetTaskGroup()->SetPushCurrent(this);
}

CTask::~CTask()
{
}

void CTask::Uninit()
{
	m_isDeleted = true;
}
