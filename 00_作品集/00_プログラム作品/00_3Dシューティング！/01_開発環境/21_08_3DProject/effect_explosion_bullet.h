//=============================================================================
//
// 弾の爆発エフェクト処理 [effect_explosion_bullet.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _EFFECT_EXPLOSION_BULLET_H_
#define _EFFECT_EXPLOSION_BULLET_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "effect.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CEffectExplosionBullet :public CEffect
{
public:
	CEffectExplosionBullet(OBJTYPE nPriority = CScene::OBJTYPE_EFFECT_EXPLOSION_BULLET);	//コンストラクタ
	~CEffectExplosionBullet();																//デストラクタ

	static CEffectExplosionBullet *Create(const D3DXVECTOR3 &pos);	//生成処理

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理
};

#endif