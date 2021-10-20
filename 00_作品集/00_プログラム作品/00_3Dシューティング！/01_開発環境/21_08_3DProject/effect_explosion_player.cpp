//=============================================================================
//
// 爆発エフェクト処理 [effect_explosion_player.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "effect_explosion_player.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define ANIM_LINE (3)							//アニメーションの行数
#define ANIM_COLUMN (3)							//アニメーションの列数
#define ANIM_SPEED (6)							//アニメーションの切り替え速度
#define SIZE (D3DXVECTOR3(50.0f, 50.0f, 50.0f))	//エフェクトの大きさ

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CEffectExplosionPlayer ::CEffectExplosionPlayer (OBJTYPE nPriority) :CEffect(nPriority)
{
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CEffectExplosionPlayer ::~CEffectExplosionPlayer ()
{
}

//*****************************************************************************
//爆発エフェクトの生成
//*****************************************************************************
CEffectExplosionPlayer * CEffectExplosionPlayer ::Create(const D3DXVECTOR3 &pos)
{
	//爆発エフェクトのメモリ確保
	CEffectExplosionPlayer  *pEffectExplosion = new CEffectExplosionPlayer ;

	if (pEffectExplosion != nullptr)
	{
		//爆発エフェクト情報の設定
		pEffectExplosion->SetPos(pos);

		//初期化処理
		pEffectExplosion->Init();

		return pEffectExplosion;
	}

	return nullptr;
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CEffectExplosionPlayer ::Init(void)
{
	//テクスチャの種類の設定
	BindTexture(GetTexture(TYPE_EXPLOSION));

	//テクスチャ情報の設定
	SetTex(ANIM_LINE, ANIM_COLUMN, ANIM_SPEED);

	//リピート設定
	SetRepeat(REP_UNREPEAT);

	//サイズの設定
	SetSize(SIZE);

	//エフェクトの初期化処理
	CEffect::Init();

	//サウンドの再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_PLAYER_EXPLOSION);

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CEffectExplosionPlayer ::Uninit(void)
{
	//エフェクトの終了処理
	CEffect::Uninit();
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CEffectExplosionPlayer ::Update(void)
{
	//エフェクトの更新処理
	CEffect::Update();
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CEffectExplosionPlayer ::Draw(void)
{
	//エフェクトの描画処理
	CEffect::Draw();
}