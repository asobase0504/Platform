//=============================================================================
//
// ���� ( �����L���O )
// Author  : hamada ryuuga
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include <string>
#include <d3dx9.h>
#include "mode.h"

//-----------------------------------------------------------------------------
// �}�N���錾
//-----------------------------------------------------------------------------
#define MAX_RANK	(6)	//�����N��
#define MAX_RANKSCORE	(8)	//����

//-----------------------------------------------------------------------------
// �O���錾
//-----------------------------------------------------------------------------
class CScore;
class CObject2d;
class CName;

//=============================================================================
// �����L���O�N���X
//=============================================================================
class CRanking : public CMode
{
public: /* ��` */

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
	static int GetMyScore() { return m_score; };
	static void SetName();
	static void SetPlayNeme(const std::string PlayName) { m_playName = PlayName; };
	static std::string GetMACAddr();
	static void SetName(int number, std::string Name) { m_name[number] = Name; };

private:

	static int m_score;
	static CScore* m_pRanking[MAX_RANK];
	static std::string m_playName;
	static std::string m_name[5];
	static bool m_isStop;
	CObject2d* m_pObject2d[4];

	CName* m_pListName[3];
	CName* m_pPlayNameSet[10];

	D3DXVECTOR3 m_namePos;

	int m_nowPlay;

	bool m_isOnrankingSet;
	bool m_isRankingSet;
};



#endif
