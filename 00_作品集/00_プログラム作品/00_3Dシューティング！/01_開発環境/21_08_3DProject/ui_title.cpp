//=============================================================================
//
// タイトルUI処理 [ui_title.h]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "ui_title.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CUiTitle::CUiTitle(OBJTYPE nPriority) :CUi(nPriority)
{
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CUiTitle::~CUiTitle()
{
}

//*****************************************************************************
//タイトルUIの生成
//*****************************************************************************
CUiTitle* CUiTitle::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	//タイトルUIのメモリ確保
	CUiTitle *pUiTitle = new CUiTitle;

	if (pUiTitle != nullptr)
	{
		//タイトルUI情報の設定
		pUiTitle->SetPos(pos);
		pUiTitle->SetSize(size);

		//UIの初期化処理
		pUiTitle->Init();

		return pUiTitle;
	}

	return nullptr;
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CUiTitle::Init(void)
{
	//テクスチャの設定
	BindTexture(GetTexture(TYPE_TITLE));

	//UIの初期化
	CUi::Init();

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CUiTitle::Uninit(void)
{
	//UIの終了処理
	CUi::Uninit();
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CUiTitle::Update(void)
{
	//UIの更新処理
	CUi::Update();
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CUiTitle::Draw(void)
{
	//UIの描画処理
	CUi::Draw();
}