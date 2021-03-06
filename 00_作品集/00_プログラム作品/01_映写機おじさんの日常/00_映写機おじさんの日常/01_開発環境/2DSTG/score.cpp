//=============================================================================
//
// スコア処理 [score.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "score.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define NUMBER_INTERVAL		(40.0f)		//数字の間隔

//*****************************************************************************
//静的メンバ変数宣言
//*****************************************************************************
int CScore::m_nScore = 0;

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CScore::CScore()
{
	memset(m_apNumber, 0, sizeof(m_apNumber));
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CScore::~CScore()
{
}

//*****************************************************************************
//スコアの生成
//*****************************************************************************
CScore *CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fInterval, int nScore, CNumber::TYPE type)
{
	//スコアのメモリ確保
	CScore *pScore = new CScore;

	if (pScore != NULL)
	{
		//スコアの初期化処理
		pScore->Init(pos, size, fInterval, nScore, type);
	}

	return pScore;
}

HRESULT CScore::Init(void)
{
	return S_OK;
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fInterval, int nScore, CNumber::TYPE type)
{
	for (int nCount = 0; nCount < SCORE_NUM; nCount++)
	{
		//数字のメモリ確保
		m_apNumber[nCount] = CNumber::Create(pos, size, 0, type);

		//数字の設定
		int nNum = (nScore / (int)(pow(10, nCount))) % 10;
		m_apNumber[nCount]->SetNumber(nNum);

		//オブジェクトの種類の設定
		SetObjType(OBJTYPE_SCORE);

		//数字の間隔をあける
		pos.x -= fInterval;
	}

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < SCORE_NUM; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			//数字の終了処理
			m_apNumber[nCount]->Uninit();
			delete m_apNumber[nCount];
			m_apNumber[nCount] = NULL;
		}
	}
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CScore::Update(void)
{
	for (int nCount = 0; nCount < SCORE_NUM; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			//数字の更新処理
			m_apNumber[nCount]->Update();
		}
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CScore::Draw(void)
{
	for (int nCount = 0; nCount < SCORE_NUM; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			//数字の描画処理
			m_apNumber[nCount]->Draw();
		}
	}
}

//*****************************************************************************
//スコアの加算処理
//*****************************************************************************
void CScore::AddScore(int nScore)
{
	//スコアの加算
	m_nScore += nScore;

	for (int nCount = 0; nCount < SCORE_NUM; nCount++)
	{
		int nNum = (m_nScore / (int)(pow(10, nCount))) % 10;

		//数字の設定
		m_apNumber[nCount]->SetNumber(nNum);
	}
}

//*****************************************************************************
//スコアの設定処理
//*****************************************************************************
void CScore::SetScore(int nScore)
{
	//スコアの設定
	m_nScore = nScore;

	for (int nCount = 0; nCount < SCORE_NUM; nCount++)
	{
		int nNum = (m_nScore / (int)(pow(10, nCount))) % 10;

		if (m_apNumber[nCount] != NULL)
		{
			//数字の設定
			m_apNumber[nCount]->SetNumber(nNum);
		}
	}
}

//*****************************************************************************
//スコアの取得
//*****************************************************************************
int CScore::GetScore(void)
{
	return m_nScore;
}

//*****************************************************************************
//数字の取得
//*****************************************************************************
CNumber *CScore::GetNumber(int nNum)
{
	return m_apNumber[nNum];
}