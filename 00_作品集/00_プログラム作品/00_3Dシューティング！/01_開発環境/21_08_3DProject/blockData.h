//=============================================================================
//
// 障害物データ管理 [blockData.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _BLOCK_DATA_H_
#define _BLOCK_DATA_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BLOCK_MAX (32)	//障害物の最大数

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CBlockData
{
public:
	//壁情報の構造体
	struct CreateInfo
	{
		D3DXVECTOR3 pos;				//位置
		D3DXVECTOR3 size;				//大きさ
		D3DXVECTOR3 rot;				//角度
		D3DXVECTOR3 collisionSize;		//当たり判定の大きさ
	};

	CBlockData();	//コンストラクタ
	~CBlockData();	//デストラクタ

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理

	CreateInfo* GetCreateInfo(const int &nCount) { return &m_aCreateInfo[nCount]; }	//生成情報の取得
	int GetCreateNum(void) { return m_nCreateNum; }									//生成順の取得

private:
	CreateInfo m_aCreateInfo[BLOCK_MAX];	//生成情報
	int m_nCreateNum;						//生成順のカウント＆生成数用
};

#endif