//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "title.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "sound.h"
#include "mode.h"
#include "scene.h"
#include "ui_title.h"
#include "fade.h"

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CTitle::CTitle()
{
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CTitle::~CTitle()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CTitle::Init(void)
{
	//タイトルテクスチャの生成
	CUiTitle::Create(SCREEN_CENTER, SCREEN_SIZE);

	//サウンドの生成
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CTitle::Uninit(void)
{
	//サウンドの終了
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_TITLE);

	//指定したオブジェクト以外のメモリの開放処理
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CTitle::Update(void)
{
	//フェードの取得
	CFade *pFade = CManager::GetFade();

	if (pFade != NULL)
	{
		if (pFade->GetFadeStatus() == CFade::FADE_NONE)
		{
			//Enterキー または Bボタンを押したとき
			if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_SPACE) || CManager::GetInputKeyboard()->GetKeyTrigger(DIK_NUMPADENTER) || CManager::GetInputJoystick()->GetJoystickTrigger(CInputJoystick::BUTTON_B))
			{
				//フェードの生成
				CManager::CreateFade(CManager::MODE_GAME);
			}
		}
	}
}