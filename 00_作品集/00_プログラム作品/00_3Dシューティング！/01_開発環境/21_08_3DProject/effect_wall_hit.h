//=============================================================================
//
// 弾と壁の衝突エフェクト処理 [effect_wall_hit.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _EFFECT_WALL_HIT_H_
#define _EFFECT_WALL_HIT_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "effect.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CEffectWallHit :public CEffect
{
public:
	CEffectWallHit(OBJTYPE nPriority = CScene::OBJTYPE_EFFECT_EXPLOSION_BULLET);	//コンストラクタ
	~CEffectWallHit();																//デストラクタ

	static CEffectWallHit *Create(const D3DXVECTOR3 &pos);	//生成処理

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理
};

#endif