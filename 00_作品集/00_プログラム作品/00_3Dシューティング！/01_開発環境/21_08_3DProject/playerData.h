//=============================================================================
//
// プレイヤーデータ管理 [playerData.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _PLAYER_DATA_H_
#define _PLAYER_DATA_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "character.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CPlayerData
{
public:
	//プレイヤー情報の構造体
	struct CreateInfo
	{
		CCharacter::TYPE type;		//種類
		D3DXVECTOR3 pos;			//位置
		D3DXVECTOR3 modelSize;		//モデルの大きさ
		D3DXVECTOR3 collisionSize;	//当たり判定の大きさ
		D3DXVECTOR3 rot;			//角度
		float fMove;				//移動量
		int nBulletType;			//弾の種類
	};

	CPlayerData();	//コンストラクタ
	~CPlayerData();	//デストラクタ

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理

	CreateInfo* GetCreateInfo(const CCharacter::TYPE &type);	//生成情報の取得

private:
	CreateInfo m_aCreateInfo[CCharacter::TYPE_MAX];	// 生成情報
};

#endif