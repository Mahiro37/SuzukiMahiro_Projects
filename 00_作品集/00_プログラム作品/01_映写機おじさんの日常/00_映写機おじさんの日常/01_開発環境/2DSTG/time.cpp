//=============================================================================
//
// タイム処理 [time.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "time.h"
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
CNumber *CTime::m_pNumber[TIME_NUM] = {};

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CTime::CTime()
{
	m_nTime = TIME_START_NUM;
	m_nTotalTime = 0;
	m_nSaveTime = m_nTime;
	m_nTimeCounter = 0;
	m_bTimeStop = false;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CTime::~CTime()
{
}

HRESULT CTime::Init(void)
{
	return S_OK;
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CTime::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTime, CNumber::TYPE type)
{
	//開始タイムの設定
	m_nTime = nTime;

	for (int nCount = 0; nCount < TIME_NUM; nCount++)
	{
		//数字の設定
		int nNum = (nTime / (int)(pow(10, nCount))) % 10;

		//数字のメモリ確保
		m_pNumber[nCount] = CNumber::Create(pos, size, nNum, type);

		//オブジェクトの種類の設定
		SetObjType(OBJTYPE_NUMBER);

		//数字の間隔をあける
		pos.x -= NUMBER_INTERVAL;
	}

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CTime::Uninit(void)
{
	for (int nCount = 0; nCount < TIME_NUM; nCount++)
	{
		if (m_pNumber[nCount] != NULL)
		{
			//数字の終了処理
			m_pNumber[nCount]->Uninit();
			delete m_pNumber[nCount];
			m_pNumber[nCount] = NULL;
		}
	}
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CTime::Update(void)
{
	if (m_bTimeStop == false)
	{ //タイムが止まっていないとき
		//タイムが０じゃないとき
		if (m_nTime != 0)
		{
			//カウントを進める
			m_nTimeCounter++;

			//６０フレーム経ったとき
			if (m_nTimeCounter == 60)
			{
				//カウントをリセットする
				m_nTimeCounter = 0;

				//タイムを減らす
				m_nTime--;

				//総合タイムを増やす
				m_nTotalTime++;

				//タイムの設定処理
				SetTime(m_nTime);
			}
		}
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CTime::Draw(void)
{
	for (int nCount = 0; nCount < TIME_NUM; nCount++)
	{
		if (m_pNumber[nCount] != NULL)
		{
			//数字の描画処理
			m_pNumber[nCount]->Draw();
		}
	}
}

//*****************************************************************************
//タイムの設定処理
//*****************************************************************************
void CTime::SetTime(int nTime)
{
	m_nTime = nTime;

	for (int nCount = 0; nCount < TIME_NUM; nCount++)
	{
		int nNum = (nTime / (int)(pow(10, nCount))) % 10;

		if (m_pNumber[nCount] != NULL)
		{
			//数字の設定
			m_pNumber[nCount]->SetNumber(nNum);
		}
	}
}

//*****************************************************************************
//タイムのセーブ
//*****************************************************************************
void CTime::SaveTime(int nTime)
{
	m_nSaveTime = nTime;
}

//*****************************************************************************
//タイムを止める
//*****************************************************************************
void CTime::SetStopTime(bool bTimeStop)
{
	m_bTimeStop = bTimeStop;
}

//*****************************************************************************
//総合タイムの初期化
//*****************************************************************************
void CTime::ResetTotalTime(void)
{
	m_nTotalTime = 0;
}

//*****************************************************************************
//タイムの取得
//*****************************************************************************
int CTime::GetTime(void)
{
	return m_nTime;
}

//*****************************************************************************
//総合タイムの取得
//*****************************************************************************
int CTime::GetTotalTime(void)
{
	return m_nTotalTime;
}

//*****************************************************************************
//セーブしたタイムの取得
//*****************************************************************************
int CTime::GetSaveTime(void)
{
	return m_nSaveTime;
}