//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "game.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "fade.h"
#include "sound.h"
#include "mode.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#include "player.h"
#include "playerData.h"
#include "wall.h"
#include "wallData.h"
#include "block.h"
#include "blockData.h"
#include "ui_start.h"
#include "ui_win_player1.h"
#include "ui_win_player2.h"
#include "ui_draw.h"
#include "floor.h"
#include "floorData.h"

//*****************************************************************************
//静的メンバ変数宣言
//*****************************************************************************
CCharacter::TYPE CGame::m_loser = CCharacter::TYPE_NONE;
CPlayer* CGame::m_apPlayer[CCharacter::TYPE_MAX] = {};

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CGame::CGame()
{
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CGame::~CGame()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CGame::Init(void)
{
	//カメラ生成
	CManager::CreateCamera();

	//ライト生成
	CManager::CreateLight();

	for (int nCount = 0; nCount < CCharacter::TYPE_MAX; nCount++)
	{
		//プレイヤーデータの取得
		CPlayerData::CreateInfo* pPlayerData = CManager::GetPlayerData()->GetCreateInfo((CCharacter::TYPE)nCount);

		if (pPlayerData != nullptr)
		{
			if (pPlayerData->type != CCharacter::TYPE_NONE)
			{
				//プレイヤー生成
				m_apPlayer[nCount] = CPlayer::Create(pPlayerData->type);
			}
		}
	}

	//壁の生成数の取得
	int nCreateNumWall = CManager::GetWallData()->GetCreateNum();

	for (int nCount = 0; nCount < nCreateNumWall; nCount++)
	{
		//壁生成
		CWall::Create(nCount);
	}

	//障害物の生成数の取得
	int nCreateNumBlock = CManager::GetBlockData()->GetCreateNum();

	for (int nCount = 0; nCount < nCreateNumBlock; nCount++)
	{
		//障害物生成
		CBlock::Create(nCount);
	}

	//床の生成数の取得
	int nCreateNumFloor = CManager::GetFloorData()->GetCreateNum();

	for (int nCount = 0; nCount < nCreateNumFloor; nCount++)
	{
		//床生成
		CFloor::Create(nCount);
	}

	//UI生成
	CUiStart::Create(SCREEN_CENTER, SCREEN_SIZE);

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CGame::Uninit(void)
{
	//サウンドの終了
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_GAME);

	//指定したオブジェクト以外のメモリの開放処理
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CGame::Update(void)
{
	switch (m_loser)
	{
	case CCharacter::TYPE_PLAYER_1:

		//プレイヤー2勝利UIの生成
		CUiWinPlayer2::Create(SCREEN_CENTER, SCREEN_SIZE);

		break;

	case CCharacter::TYPE_PLAYER_2:

		//プレイヤー1勝利UIの生成
		CUiWinPlayer1::Create(SCREEN_CENTER, SCREEN_SIZE);

		break;
	}

	//敗者判定の初期化
	m_loser = CCharacter::TYPE_NONE;
}

//*****************************************************************************
//敗者判定の設定
//*****************************************************************************
void CGame::SetLoser(const CCharacter::TYPE &loser)
{
	if (m_loser != CCharacter::TYPE_NONE)
	{
		//引き分けUIの生成
		CUiDraw::Create(SCREEN_CENTER, SCREEN_SIZE);
	}
	else
	{
		m_loser = loser;
	}
}

//*****************************************************************************
//プレイヤーポインタの取得
//*****************************************************************************
CPlayer * CGame::GetPlayer(const CCharacter::TYPE &type)
{
	for (int nCount = 0; nCount < CCharacter::TYPE_MAX; nCount++)
	{
		if (m_apPlayer[nCount]->GetType() == type)
		{
			return m_apPlayer[nCount];
		}
	}

	return nullptr;
}