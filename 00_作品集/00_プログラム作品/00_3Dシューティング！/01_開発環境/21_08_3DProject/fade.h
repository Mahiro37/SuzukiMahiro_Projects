//=============================================================================
//
// フェード処理 [fade.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "renderer.h"
#include "manager.h"
#include "mode.h"
#include "scene2d.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CFade :public CScene2D
{
public:
	//フェード状態の列挙型
	enum FADE
	{
		FADE_NONE = 0,
		FADE_IN,		//フェードイン
		FADE_OUT		//フェードアウト
	};

	CFade(OBJTYPE Priority = OBJTYPE_FADE);	//コンストラクタ
	~CFade();									//デストラクタ

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理	
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	void FadeIn(void);	//フェードイン処理
	void FadeOut(void);	//;フェードアウト処理

	void SetFade(CManager::MODE mode);	//フェード状態の設定

	FADE GetFadeStatus(void) { return m_FadeStatus; }	//フェード状態の取得

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファポインタ

	static CManager::MODE m_mode;
	static FADE m_FadeStatus;
};
#endif
