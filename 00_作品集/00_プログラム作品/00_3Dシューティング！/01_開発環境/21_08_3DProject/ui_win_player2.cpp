//=============================================================================
//
// プレイヤー２の勝利UI処理 [ui_win_player2.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "ui_win_player2.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CUiWinPlayer2::CUiWinPlayer2(OBJTYPE nPriority) :CUi(nPriority)
{
	m_nCntUi = 0;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CUiWinPlayer2::~CUiWinPlayer2()
{
}

//*****************************************************************************
//プレイヤー２勝利UIの生成
//*****************************************************************************
CUiWinPlayer2* CUiWinPlayer2::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	//プレイヤー２勝利UIのメモリ確保
	CUiWinPlayer2 *pUiWinPlayer2 = new CUiWinPlayer2;

	if (pUiWinPlayer2 != nullptr)
	{
		//プレイヤー２勝利UI情報の設定
		pUiWinPlayer2->SetPos(pos);
		pUiWinPlayer2->SetSize(size);

		//初期化処理
		pUiWinPlayer2->Init();

		return pUiWinPlayer2;
	}

	return nullptr;
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CUiWinPlayer2::Init(void)
{
	//指定したOBJTYPEのみを更新する
	SetUpdateType(OBJTYPE_UI_WIN_PLAYER_2, OBJTYPE_EFFECT_EXPLOSION, NULL);

	//テクスチャの設定
	BindTexture(GetTexture(TYPE_WIN_PLAYER_2));

	//UIの初期化処理
	CUi::Init();

	//サウンドの再生
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_FINISH);

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CUiWinPlayer2::Uninit(void)
{
	//UIの終了処理
	CUi::Uninit();
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CUiWinPlayer2::Update(void)
{
	//カウントを進める
	m_nCntUi++;

	if (m_nCntUi >= INIT_FINISH_UI_TIME)
	{ //カウントが規定値を超えたとき
		//フェードの生成
		CManager::CreateFade(CManager::MODE_TITLE);
	}

	//UIの更新処理
	CUi::Update();
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CUiWinPlayer2::Draw(void)
{
	//UIの描画処理
	CUi::Draw();
}