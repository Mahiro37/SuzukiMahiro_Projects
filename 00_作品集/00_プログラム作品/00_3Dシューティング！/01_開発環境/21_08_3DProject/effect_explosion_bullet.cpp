//=============================================================================
//
// 弾の爆発エフェクト処理 [effect_explosion_bullet.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "effect_explosion_bullet.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define ANIM_LINE (8)							//アニメーションの行数
#define ANIM_COLUMN (1)							//アニメーションの列数
#define ANIM_SPEED (3)							//アニメーションの切り替え速度
#define SIZE (D3DXVECTOR3(20.0f, 20.0f, 20.0f))	//エフェクトの大きさ

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CEffectExplosionBullet::CEffectExplosionBullet(OBJTYPE nPriority) :CEffect(nPriority)
{
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CEffectExplosionBullet::~CEffectExplosionBullet()
{
}

//*****************************************************************************
//弾の爆発エフェクトの生成
//*****************************************************************************
CEffectExplosionBullet* CEffectExplosionBullet::Create(const D3DXVECTOR3 &pos)
{
	//弾の爆発エフェクトのメモリ確保
	CEffectExplosionBullet *pEffectExplosionBullet = new CEffectExplosionBullet;

	if (pEffectExplosionBullet != nullptr)
	{
		//弾の爆発エフェクト情報の設定
		pEffectExplosionBullet->SetPos(pos);

		//初期化処理
		pEffectExplosionBullet->Init();

		return pEffectExplosionBullet;
	}

	return nullptr;
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CEffectExplosionBullet::Init(void)
{
	//テクスチャの種類の設定
	BindTexture(GetTexture(TYPE_EXPLOSION_BULLET));

	//テクスチャ情報の設定
	SetTex(ANIM_LINE, ANIM_COLUMN, ANIM_SPEED);

	//リピート設定
	SetRepeat(REP_UNREPEAT);

	//サイズの設定
	SetSize(SIZE);

	//エフェクトの初期化処理
	CEffect::Init();

	//サウンドの再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BULLET_EXPLOSION);

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CEffectExplosionBullet::Uninit(void)
{
	//エフェクトの終了処理
	CEffect::Uninit();
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CEffectExplosionBullet::Update(void)
{
	//エフェクトの更新処理
	CEffect::Update();
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CEffectExplosionBullet::Draw(void)
{
	//エフェクトの描画処理
	CEffect::Draw();
}