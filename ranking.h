//**************************************************
//
// 制作 ( ランキング )
// Author  : hamada ryuuga
//
//**************************************************
#ifndef _RANKING_H_
#define _RANKING_H_

#include "score.h"
#include <string>       // ヘッダファイルインクルード
//------------------------------------
//マクロ定義
//------------------------------------
#define MAX_RANK	(6)	//ランク数
#define MAX_RANKSCORE	(8)	//桁数

//------------------------------------
//プロトタイプ宣言
//------------------------------------

class CScore;
class CObject2d;
class CName;

class CRanking : public CObject
{
public:
	CRanking();
	~CRanking();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	static void APIUp();
	static void GoScore();
	static void OnlineSetScore();
	static void SetScore(int nScore);
	static void GetScore();
	static int GetMyScore() { return m_Score; };
	static void SetName();
	static void SetPlayNeme(const std::string PlayName) { m_PlayName = PlayName; };
	static std::string GetMACAddr();
	static void SetName(int number, std::string Name) { m_Name[number] = Name; };

private:

	static int m_Score;
	static CScore *m_Ranking[MAX_RANK];
	static std::string m_PlayName;
	static	std::string m_Name[5];
	static bool m_Stop;
	CObject2d *m_Object2d[4];

	CName*m_ListName[3];
	CName*m_PlayNameSet[10];

	D3DXVECTOR3 m_NemePos;

	int m_NowPlay;

	bool m_OnrankingSet;
	bool m_RankingSet;
};



#endif
