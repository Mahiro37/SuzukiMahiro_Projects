//=============================================================================
//
// スタートUI処理 [ui_start.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _UI_START_H_
#define _UI_START_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "ui.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CUiStart :public CUi
{
public:
	CUiStart(OBJTYPE nPriority = CScene::OBJTYPE_UI_START);	//コンストラクタ
	~CUiStart();											//デストラクタ

	static CUiStart *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);	//生成処理

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

private:
	int m_nCntUi;			//UIの更新用カウント
	int m_nCntGameBGM;		//ゲームBGMをかけ始めるまでのカウント
	bool m_bFirstUpdate;	//1フレーム目の更新処理用
};

#endif