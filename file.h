//=============================================================================
//
// �t�@�C��
// Author : Hamada Ryuuga
//
//=============================================================================
#ifndef _FILE_H_			// ���̃}�N����`������ĂȂ�������
#define _FILE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <windows.h>
#include "nlohmann/json.hpp"
#include <string>

#include <stdio.h>
#include <tchar.h>
#include <locale.h>
#include <windows.h>
#include <sstream>

#include "main.h"

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void OutputStatus();
void LoadJson(const char* cUrl);
nlohmann::json LoadJsonStage(const wchar_t* cUrl);

#endif		// _FILE_H_
