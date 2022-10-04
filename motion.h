//**************************************************************************************************
//
// モーション処理(motion.h)
// Auther：唐﨑結斗
// 概要 : モーションクラスの設定
//
//**************************************************************************************************
#ifndef _MOTION_H_			// このマクロ定義がされてなかったら
#define _MOTION_H_			// 二重インクルード防止のマクロ定義

//***************************************************************************
// インクルード
//***************************************************************************
#include"main.h"
#include "renderer.h"



//=============================================================================
// モーションクラス
// Author : 唐﨑結斗
// 概要 : モーション設定を行うクラス
//=============================================================================
class CMotion
{
public:

	enum MODELCOLLAR
	{
		LET = 0,
		BLUE,
		YELLOW,
		GREEN,
		NON,
		MAX
	};
	//***************************************************************************
	// 定数定義
	//***************************************************************************
	static const unsigned int MAX_MOTION = (7);					// モーション数の最大数
	static const unsigned int MAX_MODEL_PARTS = (30);				// モデル数の最大数
	static const unsigned int MAX_KEY = (64);						// キーの最大数
	static const unsigned int MAX_KEYSET = (64);					// キー設定の最大数
	static const unsigned int MOTION_BLEND_FRAM = (12);				// モーションブレンドのフレーム数	

	//***************************************************************
	// パーツファイル構造体を定義
	//***************************************************************
	struct PartsFile
	{
		char	aName[MAX_MODEL_PARTS];		// 名前
	};

	//***************************************************************
	// キー構造体を定義
	//***************************************************************
	struct MyKey
	{
		D3DXVECTOR3		pos;	// 現在位置
		D3DXVECTOR3		rot;	// 現在の向き
	};

	//***************************************************************
	// キー設定構造体を定義
	//***************************************************************
    struct MyKeySet
	{
		int		nFrame;			// フレーム数
		MyKey	key[MAX_KEY];	// キー情報
	};

	//***************************************************************
	// モーション設定構造体を定義
	//***************************************************************
	struct MyMotion
	{
		int				nNumKey;				// キー数
		int				nCntKeySet;				// キーセットカウント
		int				nCntFrame;				// フレームカウント
		bool			bLoop;					// ループ使用状況
		MyKeySet		keySet[MAX_KEYSET];		// キー設定情報
	};

	//***************************************************************
	// モデルパーツ構造体を定義
	//***************************************************************
	struct Parts
	{
		LPD3DXMESH		pMesh;					// メッシュ情報へのポインタ
		LPD3DXBUFFER	pBuffer;				// マテリアル情報へのポインタ
		DWORD			nNumMat;				// マテリアル情報の数
		D3DXMATRIX		mtxWorld;				// ワールドマトリックス
		D3DXVECTOR3		posOrigin;				// 元の位置
		D3DXVECTOR3		rotOrigin;				// 元の向き
		D3DXVECTOR3		pos;					// 現在の位置
		D3DXVECTOR3		rot;					// 現在の向き
		D3DXVECTOR3		posDest;				// 目的の位置
		D3DXVECTOR3		rotDest;				// 目的の向き
		int				nIdxModelParent;		// 親モデルのインデックス数
		int				nType;					// パーツのタイプ
	};

	//--------------------------------------------------------------------
	// コンストラクタとデストラクタ
	//--------------------------------------------------------------------
	CMotion(char *pFileName);
	~CMotion();

	//--------------------------------------------------------------------
	// メンバ関数
	//--------------------------------------------------------------------
	// 初期化
	void Init(void);

	// パーツの設定
	void SetParts(D3DXMATRIX mtxWorld, CMotion::MODELCOLLAR Type);							// マテリアルデータ

	// モーションの再生
	bool PlayMotion(const int nCntMotionSet);

	// モーションブレンド
	bool MotionBlend(const int nCntMotionSet);	

	// モーション読み込み
	void LoodSetMotion(char *pFileName);

	// 終了
	void Uninit(void);

	// カウントリセット
	void CntReset(const int nNumMotionOld);

private:
	//--------------------------------------------------------------------
	// メンバ変数
	//--------------------------------------------------------------------
	MyMotion	*m_motion;							// モーション
	Parts		*m_parts;							// パーツ
	PartsFile	m_partsFile[MAX_MODEL_PARTS];		// パーツのXファイル名
	int			m_nMaxParts;						// パーツ数
	int			m_nType;
};

class CModel
{
public: /* 定義 */

	CModel();
	~CModel() {};

	// 終了処理
	void Uninit() 
	{
		if (pBuffer != NULL)
		{// 頂点バッファーの解放
			pBuffer->Release();
			pBuffer = NULL;
		}

		if (pMesh != NULL)
		{// メッシュの解放
			pMesh->Release();
			pMesh = NULL;
		}
	}

	int				nType;					// パーツのタイプ
	LPD3DXMESH		pMesh;					// メッシュ情報へのポインタ
	LPD3DXBUFFER	pBuffer;				// マテリアル情報へのポインタ
	DWORD			nNumMat;				// マテリアル情報の数
	char		    m_xFilename[256];
};

//=============================================================================
// モデルマネージャー　
// Author : 浜田琉雅
// 概要 : モデルのデータを保存しておく
//=============================================================================
class CModelManager
{
public: /* 定義 */


	static const int MODEL_MAX = 100;

private:
	static CModelManager * ms_ModelManager;

public:
	CModelManager();		// デフォルトコンストラクタ
	~CModelManager();	// デストラクタ

public: /* メンバ関数 */
	static CModelManager *GetManager();
	CModel* Load(const char *pXFileName);	
	CModel* LoadXfile(const char *pXFileName);	// 指定の読み込み
	static void ReleaseAll();
public: /* メンバ変数 */
	CModel* m_apModel[MODEL_MAX];
};





#endif

