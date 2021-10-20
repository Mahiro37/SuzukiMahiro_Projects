//=============================================================================
//
// プレイヤー２の勝利UI処理 [ui_win_player2.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _UI_WIN_PLAYER2_H_
#define _UI_WIN_PLAYER2_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "ui.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CUiWinPlayer2 :public CUi
{
public:
	CUiWinPlayer2(OBJTYPE nPriority = CScene::OBJTYPE_UI_WIN_PLAYER_2);	//コンストラクタ
	~CUiWinPlayer2();													//デストラクタ

	static CUiWinPlayer2 *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);	//生成処理

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

private:
	int m_nCntUi;	//UIの更新用カウント
};

#endif