//=============================================================================
//
// 爆発エフェクト処理 [effect_explosion_player.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _EFFECT_EXPLOSION_PLAYER_H_
#define _EFFECT_EXPLOSION_PLAYER_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "effect.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CEffectExplosionPlayer :public CEffect
{
public:
	CEffectExplosionPlayer(OBJTYPE nPriority = CScene::OBJTYPE_EFFECT_EXPLOSION);	//コンストラクタ
	~CEffectExplosionPlayer();														//デストラクタ

	static CEffectExplosionPlayer *Create(const D3DXVECTOR3 &pos);	//生成処理

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理
};

#endif