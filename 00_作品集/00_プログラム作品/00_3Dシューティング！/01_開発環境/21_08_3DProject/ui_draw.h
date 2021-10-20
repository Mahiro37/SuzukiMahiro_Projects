//=============================================================================
//
// 引き分けUI処理 [ui_draw.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _UI_DRAW_H_
#define _UI_DRAW_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "ui.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CUiDraw :public CUi
{
public:
	CUiDraw(OBJTYPE nPriority = CScene::OBJTYPE_UI_DRAW);	//コンストラクタ
	~CUiDraw();												//デストラクタ

	static CUiDraw *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);	//生成処理

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

private:
	int m_nCntUi;	//UIの更新用カウント
};

#endif