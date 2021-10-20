//=============================================================================
//
// エフェクト処理 [effect.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "animation.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CEffect :public CAnimation
{
public:
	//エフェクトの種類の列挙型
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_EXPLOSION,			//プレイヤーの爆発
		TYPE_EXPLOSION_BULLET,	//弾の爆発
		TYPE_WALL_HIT,			//弾と壁の衝突
		TYPE_MAX
	};

	CEffect(OBJTYPE nPriority);	//コンストラクタ
	~CEffect();					//デストラクタ

	static HRESULT Load(void);	//ロード処理
	static void Unload(void);	//アンロード処理

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	LPDIRECT3DTEXTURE9 GetTexture(const TYPE &type) { return m_apTexture[type]; }	//テクスチャ情報の取得

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];	//テクスチャのポインタ配列
};

#endif