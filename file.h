//============================
//
// ファイル設定ヘッター
// Author:hamada ryuuga
//
//============================
#ifndef _FILE_H_			// このマクロ定義がされてなかったら
#define _FILE_H_			// 二重インクルード防止のマクロ定義

//=====================================
// インクルード
//=====================================
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
#include "particle.h"


//=====================================
// プロトタイプ宣言
//=====================================
// 制御関数


void OutputStatus();
void LoadJson(const char* cUrl);

#endif
