//============================
//
// ファイル設定
// Author:hamada ryuuga
//
//============================

#include "file.h"
#include "letter.h"
#include "particle.h"
#include "manager.h"
#include "texture.h"
#include "particle_manager.h"
#include "game.h"
#include "tutorial.h"

static int index = 0;
namespace nl = nlohmann;

nl::json Effect;//リストの生成

//============================
// 全部出力（置くだけ）
//============================
void OutputStatus()
{
	/*DataEffect = GetImguiParticle();

	Effect["POS"] = {{ "X", DataEffect.pos.x} ,{ "Y", DataEffect.pos.y} ,{ "Z", DataEffect.pos.z } };
	Effect["POSMAX"] = {{ "X", DataEffect.maxPopPos.x } ,{ "Y", DataEffect.maxPopPos.y } ,{ "Z", DataEffect.maxPopPos.z } };
	Effect["POSMIN"] = {{ "X", DataEffect.minPopPos.x } ,{ "Y", DataEffect.minPopPos.y } ,{ "Z", DataEffect.minPopPos.z } };
	Effect["MOVE"] = { { "X", DataEffect.move.x } ,{ "Y", DataEffect.move.y } ,{ "Z", DataEffect.move.z } };
	Effect["MOVETRANSITION"] = { { "X", DataEffect.moveTransition.x } ,{ "Y", DataEffect.moveTransition.y } ,{ "Z", DataEffect.moveTransition.z } };
	Effect["ROT"] = { {"X", DataEffect.rot.x} ,{ "Y", DataEffect.rot.y },{ "Z", DataEffect.rot.z } };

	Effect["COL"] = { { "R", DataEffect.color.col.r }, {"G" ,DataEffect.color.col.g} ,{ "B", DataEffect.color.col.b } ,{ "A", DataEffect.color.col.a } };
	Effect["COLRANDAMMAX"] = { { "R", DataEffect.color.colRandamMax.r },{ "G" ,DataEffect.color.colRandamMax.g } ,{ "B", DataEffect.color.colRandamMax.b } ,{ "A", DataEffect.color.colRandamMax.a } };
	Effect["COLRANDAMMIN"] = { { "R", DataEffect.color.colRandamMin.r },{ "G" ,DataEffect.color.colRandamMin.g } ,{ "B", DataEffect.color.colRandamMin.b } ,{ "A", DataEffect.color.colRandamMin.a } };
	Effect["COLTRANSITION"] = { { "R", DataEffect.color.colTransition.r },{ "G" ,DataEffect.color.colTransition.g } ,{ "B", DataEffect.color.colTransition.b } ,{ "A", DataEffect.color.colTransition.a } };
	Effect["DESTCOL"] = { { "R", DataEffect.color.destCol.r },{ "G" ,DataEffect.color.destCol.g } ,{ "B", DataEffect.color.destCol.b } ,{ "A", DataEffect.color.destCol.a } };
	Effect["ENDTIME"] = DataEffect.color.nEndTime;
	Effect["CNTTRANSITIONTIME"] = DataEffect.color.nCntTransitionTime;
	Effect["BCOLTRANSITION"] = DataEffect.color.bColTransition;
	Effect["COLRANDOM"] = DataEffect.color.bColRandom;
	Effect["RANDOMTRANSITIONTIME"] = DataEffect.color.bRandomTransitionTime;

	Effect["TYPE"] = DataEffect.type;
	Effect["WIDTH"] = DataEffect.fWidth;
	Effect["HEIGHT"] = DataEffect.fHeight;
	Effect["ANGLE"] = DataEffect.fAngle;
	Effect["ATTENUATION"] = DataEffect.fAttenuation;
	Effect["RADIUS"] = DataEffect.fRadius;
	Effect["WEIGHT"] = DataEffect.fWeight;
	Effect["WEIGHTTRANSITION"] = DataEffect.fWeightTransition;
	Effect["LIFE"] = DataEffect.nLife;
	Effect["BACKROT"] = DataEffect.bBackrot;
	Effect["SCALE"] = DataEffect.fScale;

	auto jobj = Effect.dump();
	std::ofstream writing_file;
	const std::string pathToJSON = "data/FILE/DataEffectOutput.json";
	writing_file.open(pathToJSON, std::ios::out);
	writing_file << jobj << std::endl;
	writing_file.close();*/
}

void LoadJson(const char* cUrl)
{
	std::ifstream ifs(cUrl);

	if (ifs)
	{
		CParticleManager::BundledData loadData = {};
		CParticle::Info& particleInfo = loadData.particleData;

		//StringToWString(UTF8toSjis(j["name"]));
		//DataSet.unionsname = StringToWString(UTF8toSjis(j["unions"] ["name"]));
		ifs >> Effect;

		particleInfo.maxPopPos = D3DXVECTOR3(Effect["POSMAX"]["X"], Effect["POSMAX"]["Y"], Effect["POSMAX"]["Z"]);
		particleInfo.minPopPos = D3DXVECTOR3(Effect["POSMIN"]["X"], Effect["POSMIN"]["Y"], Effect["POSMIN"]["Z"]);
		//こっちで構造体にデータを入れてます//文字は変換つけないとばぐるぞ＾＾これ-＞UTF8toSjis()
		particleInfo.move = D3DXVECTOR3(Effect["MOVE"]["X"], Effect["MOVE"]["Y"], Effect["MOVE"]["Z"]);
		particleInfo.rot = D3DXVECTOR3(Effect["ROT"]["X"], Effect["ROT"]["Y"], Effect["ROT"]["Z"]);
		particleInfo.moveTransition = D3DXVECTOR3(Effect["MOVETRANSITION"]["X"], Effect["MOVETRANSITION"]["Y"], Effect["MOVETRANSITION"]["Z"]);;

		particleInfo.color.colBigin = D3DXCOLOR(Effect["COL"]["R"], Effect["COL"]["G"], Effect["COL"]["B"], Effect["COL"]["A"]);
		particleInfo.color.colRandamMax = D3DXCOLOR(Effect["COLRANDAMMAX"]["R"], Effect["COLRANDAMMAX"]["G"], Effect["COLRANDAMMAX"]["B"], Effect["COLRANDAMMAX"]["A"]);
		particleInfo.color.colRandamMin = D3DXCOLOR(Effect["COLRANDAMMIN"]["R"], Effect["COLRANDAMMIN"]["G"], Effect["COLRANDAMMIN"]["B"], Effect["COLRANDAMMIN"]["A"]);
		particleInfo.color.colTransition = D3DXCOLOR(Effect["COLTRANSITION"]["R"], Effect["COLTRANSITION"]["G"], Effect["COLTRANSITION"]["B"], Effect["COLTRANSITION"]["A"]);
		particleInfo.color.destCol = D3DXCOLOR(Effect["DESTCOL"]["R"], Effect["DESTCOL"]["G"], Effect["DESTCOL"]["B"], Effect["DESTCOL"]["A"]);
		particleInfo.color.nEndTime = Effect["ENDTIME"];
		particleInfo.color.nCntTransitionTime = Effect["CNTTRANSITIONTIME"];
		particleInfo.color.bColTransition = Effect["BCOLTRANSITION"];
		particleInfo.color.bColRandom = Effect["COLRANDOM"];
		particleInfo.color.bRandomTransitionTime = Effect["RANDOMTRANSITIONTIME"];

		particleInfo.type = Effect["TYPE"];
		particleInfo.fWidth = Effect["WIDTH"];
		particleInfo.fHeight = Effect["HEIGHT"];
		particleInfo.fRadius = Effect["RADIUS"];
		particleInfo.fAngle = Effect["ANGLE"];
		particleInfo.fWeight = Effect["WEIGHT"];
		particleInfo.nLife = Effect["LIFE"];
		particleInfo.fAttenuation = Effect["ATTENUATION"];
		particleInfo.fWeightTransition = Effect["WEIGHTTRANSITION"];
		particleInfo.nLife = Effect["LIFE"];
		particleInfo.bBackrot = Effect["BACKROT"];
		particleInfo.fScale = Effect["SCALE"];

		static bool chack = true;

		if (chack)
		{
			if (index >= 4)
			{
				index = 0;
			}
			switch (*CManager::GetInstance()->GetMode())
			{
			case CManager::MODE_TITLE:
			
				break;
			case CManager::MODE_GAME:
				CGame::GetParticleManager()->SetBundledData(loadData, index);			
				break;
			case CManager::MODE_RESULT:
			
				break;
			case CManager::MODE_RANKING:
				break;
			case CManager::MODE_TUTORIAL:
				CTutorial::GetParticleManager()->SetBundledData(loadData, index);
				break;
			default:
				break;
			}
			index++;
		}
		else
		{
			CGame::GetParticleManager()->ChangeBundledData(0, loadData);
		}
	}

}

