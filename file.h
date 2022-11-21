//=============================================================================
//
// ファイル
// Author : Hamada Ryuuga
//
//=============================================================================
#ifndef _FILE_H_			// このマクロ定義がされてなかったら
#define _FILE_H_			// 二重インクルード防止のマクロ定義

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
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void OutputStatus();
void LoadJson(const char* cUrl);
nlohmann::json LoadJsonStage(const wchar_t* cUrl);

#endif		// _FILE_H_
