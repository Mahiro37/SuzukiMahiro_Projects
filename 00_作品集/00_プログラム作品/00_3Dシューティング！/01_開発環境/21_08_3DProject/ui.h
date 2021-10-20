//=============================================================================
//
// UI処理 [ui.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "scene2d.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define INIT_FINISH_UI_TIME (120)	//勝利判定UIの表示時間(初期値)

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CUi:public CScene2D
{
public:
	//UIの種類の列挙型
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_TITLE,			//タイトル
		TYPE_RESULT,		//リザルト
		TYPE_START,			//ゲーム開始
		TYPE_WIN_PLAYER_1,	//1Pの勝利
		TYPE_WIN_PLAYER_2,	//2Pの勝利
		TYPE_DRAW,			//引き分け
		TYPE_MAX
	}UI_TYPE;

	CUi(OBJTYPE nPriority);	//コンストラクタ
	~CUi();					//デストラクタ

	static HRESULT Load(void);	//ロード処理
	static void Unload(void);	//アンロード処理

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	LPDIRECT3DTEXTURE9 GetTexture(const UI_TYPE &type) { return m_apTexture[type]; }	//テクスチャ情報の取得
	UI_TYPE GetUiType(void) { return m_type; }											//UIタイプの取得

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];	//テクスチャのポインタ配列
	UI_TYPE m_type;	//UIタイプ
};

#endif