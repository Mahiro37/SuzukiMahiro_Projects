//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include <time.h>
#include "game.h"
#include "manager.h"
#include "keyboard.h"
#include "controller.h"
#include "time.h"
#include "enemy.h"
#include "bg.h"
#include "player.h"
#include "score.h"
#include "life.h"
#include "sound.h"
#include "scene.h"
#include "ui.h"
#include "fade.h"
#include "item.h"
#include "pause.h"

//*****************************************************************************
//静的メンバ変数宣言
//*****************************************************************************
int CGame::m_nCntStage = GAME_STAGE_1;

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CGame::CGame()
{
	m_pFade = NULL;
	m_bClear = true;
	m_bStartPush = false;
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
	//背景の生成
	CBg::Create();

	switch (m_nCntStage)
	{
	case GAME_STAGE_1:

		//セカンドボールの生成
		CEnemy::Create(D3DXVECTOR3(800.0f, 200.0f, 0.0f), SECOND_BALL_SIZE, D3DXVECTOR3(3.0f, -2.0f, 0.0f), CScene::OBJTYPE_SECOND_BALL);
		CEnemy::Create(D3DXVECTOR3(400.0f, 200.0f, 0.0f), SECOND_BALL_SIZE, D3DXVECTOR3(-3.0f, -2.0f, 0.0f), CScene::OBJTYPE_SECOND_BALL);

		break;

	case GAME_STAGE_2:

		//ファーストボールの生成
		CEnemy::Create(D3DXVECTOR3(800, 200.0f, 0.0f), FIRST_BALL_SIZE, D3DXVECTOR3(4.0f, -2.0f, 0.0f), CScene::OBJTYPE_FIRST_BALL);
		CEnemy::Create(D3DXVECTOR3(400, 200.0f, 0.0f), FIRST_BALL_SIZE, D3DXVECTOR3(-4.0f, -2.0f, 0.0f), CScene::OBJTYPE_FIRST_BALL);

		break;

	case GAME_STAGE_3:

		//ボスボールの生成
		CEnemy::Create(D3DXVECTOR3(640.0f, 200.0f, 0.0f), BOSS_BALL_SIZE, D3DXVECTOR3(-4.0f, -2.0f, 0.0f), CScene::OBJTYPE_BOSS_BALL);

		break;

	default:

		break;
	}

	//プレイヤーの生成
	CManager::CreatePlayer();

	//残機の生成
	CManager::CreateLife(D3DXVECTOR3(350.0f, 80.0f, 0.0f));

	//残機UIの生成
	CUi::Create(D3DXVECTOR3(260.0f, 80.0f, 0.0f), D3DXVECTOR3(130.0f, 60.0f, 0.0f), CUi::UI_TYPE_ZANKI);

	//残機の設定
	int nLife = CManager::GetPlayer()->GetPlayerLife();
	CManager::GetLife()->SetLife(nLife);

	//フィルムUIの生成
	CUi::Create(D3DXVECTOR3(1000.0f, 80.0f, 0.0f), D3DXVECTOR3(280.0f, 100.0f, 0.0f), CUi::UI_TYPE_FILM);

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CGame::Uninit(void)
{
	//BGMの停止
	CManager::GetSound()->Stop(CSound::SOUND_LABEL_BGM05);

	//全てのメモリの開放処理
	CScene::ReleaseAllOtherThanFade();

	if (m_pFade != NULL)
	{
		m_pFade = NULL;
	}
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CGame::Update(void)
{
	bool bPause = false;		//ポーズが生成されているかの判定
	bool bInstruction = false;	//操作説明が生成されているかの判定
	CPause *pPause = NULL;		//ポーズのポインタ
	CUi *pUi = NULL;			//UIのポインタ

	for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
	{
		//オブジェクトの取得
		CScene *pScene = CScene::GetScene(nCntScene);

		if (bPause == false)
		{ //ポーズが生成されていないとき
			//ダイナミックキャスト
			pPause = dynamic_cast<CPause*>(pScene);

			if (pPause != NULL)
			{
				//フラグを立てる
				bPause = true;
			}
		}

		if (bInstruction == false)
		{ //操作説明が生成されていないとき
			//ダイナミックキャスト
			pUi = dynamic_cast<CUi*>(pScene);

			if (pUi != NULL)
			{
				if (pUi->GetUiType() == CUi::UI_TYPE_DESCRIPTION)
				{
					//フラグを立てる
					bInstruction = true;
				}
			}
		}

		if (bPause == true && bInstruction == true)
		{ //ポーズと操作説明がどちらも生成されているとき
			break;
		}
	}

	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_P) || CManager::GetController()->GetJoypadTrigger(11))
	{ //Pを押したとき または スタートボタンを押したとき
		if (m_bStartPush == false && CManager::GetPlayer()->GetChargeRelease() == true)
		{ //スタートボタンを押していないとき かつ チャージしていないとき
			if (CScene::GetUpdateStop() == false)
			{ //CSceneの更新が止まっていないとき
				if (bPause == false && bInstruction == false)
				{ //ポーズと操作説明が生成されていないとき
					//ポーズの生成
					CPause::Create();
				}
			}
			else
			{ //CSceneの更新が止まっているとき
				if (bPause == true && bInstruction == false)
				{ //ポーズが生成されていて、操作説明が生成されていないとき
					if (pPause != NULL)
					{
						//ポーズの終了処理
						pPause->Uninit();

						//シーンの更新を進める
						CScene::UpdateStop(false);
					}
				}
			}

			//スタートボタンのプッシュフラグを立てる
			m_bStartPush = true;
		}
	}

	if (CManager::GetKeyboard()->GetKeyboardRelease(DIK_P) || CManager::GetController()->GetJoypadRelease(11))
	{ //Pを離したとき または スタートボタンを離したとき
		//スタートボタンのプッシュフラグを下げる
		m_bStartPush = false;
	}

	if (m_bClear == true)
	{ //クリアしている判定のとき
		for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
		{
			//オブジェクトの取得
			CScene *pScene = CScene::GetScene(nCntScene);

			//ダイナミックキャスト
			CEnemy *pEnemy = dynamic_cast<CEnemy*>(pScene);

			if (pEnemy != NULL)
			{ //敵が残っているとき
				//クリアしていない判定にする
				m_bClear = false;
			}
		}

		if (m_bClear == true)
		{ //クリアしている判定のとき
			//判定をfalseにする
			m_bClear = false;

			//SEの停止
			CManager::GetSound()->Stop(CSound::SOUND_LABEL_CHARGE);

			//ステージ番号を一つ進める
			m_nCntStage++;

			switch (m_nCntStage)
			{
			case GAME_STAGE_CLEAR:

				if (m_pFade != NULL)
				{
					m_pFade = NULL;
				}

				if (m_pFade == NULL)
				{
					//フェードの生成
					m_pFade = CFade::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CManager::MODE_GAME_CREAR);
				}

				//ステージカウントの初期化
				m_nCntStage = GAME_STAGE_1;

				break;

			default:

				if (m_pFade != NULL)
				{
					m_pFade = NULL;
				}

				if (m_pFade == NULL)
				{
					//フェードの生成
					m_pFade = CFade::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CManager::MODE_GAME);
				}

				break;
			}
		}
		else if (m_bClear == false)
		{ //クリアしていない判定のとき
			//判定をtrueにする
			m_bClear = true;
		}
	}

	bool bPlayer = false;	//プレイヤーの生存判定

	for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
	{
		//オブジェクトの取得
		CScene *pScene = CScene::GetScene(nCntScene);

		//ダイナミックキャスト
		CPlayer *pPlayer = dynamic_cast<CPlayer*>(pScene);

		if (pPlayer != NULL)
		{ //プレイヤーが生きているとき
			//フラグをtrueにする
			bPlayer = true;
		}
	}

	if (bPlayer == false)
	{ //プレイヤーが死んでいるとき
		if (CManager::GetPlayer() != NULL)
		{
			if (CManager::GetPlayer()->GetPlayerLife() >= 0)
			{ //残機が残っているとき
				if (m_pFade == NULL)
				{
					//フェードの生成
					m_pFade = CFade::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CManager::MODE_GAME);
				}
			}
		}
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CGame::Draw(void)
{
}

//*****************************************************************************
//アイテムストックUIの更新処理
//*****************************************************************************
void CGame::UpdateStock(list<CItem::ITEMTYPE> StockItem)
{
	for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
	{
		//オブジェクトの取得
		CScene *pScene = CScene::GetScene(nCntScene);

		//ダイナミックキャスト
		CUi *pUi = dynamic_cast<CUi*>(pScene);

		if (pUi != NULL)
		{
			//オブジェクトタイプの取得
			CScene::OBJTYPE ObjType = pUi->GetObjType();

			if (ObjType == CScene::OBJTYPE_UI_ITEM)
			{ //オブジェクトタイプがアイテムUIのとき
				//UIの終了処理
				pUi->Uninit();
			}
		}
	}

	//イテレータに代入
	auto itr = StockItem.begin();

	for (int nCount = 0; nCount < (int)StockItem.size(); nCount++)
	{ //nCountが要素数に達するまでまわる
		switch (*itr)
		{
			//自機の移動スピードアップだったとき
		case CItem::ITEMTYPE_PLAYER_SPEED_UP:

			//UIの生成
			CUi::Create(D3DXVECTOR3(910.0f + (90.0f * nCount), 80.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CUi::UI_TYPE_PLAYER_SPEED_UP);

			break;

			//弾のチャージスピードアップだったとき
		case CItem::ITEMTYPE_CHARGE_SPEED_UP:

			//UIの生成
			CUi::Create(D3DXVECTOR3(910.0f + (90.0f * nCount), 80.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CUi::UI_TYPE_BULLET_SPEED_UP);

			break;

			//バリアだったとき
		case CItem::ITEMTYPE_BARRIER:

			//UIの生成
			CUi::Create(D3DXVECTOR3(910.0f + (90.0f * nCount), 80.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CUi::UI_TYPE_BARRIER);

			break;

		default:

			break;
		}

		//イテレータを進める
		itr++;
	}
}

//*****************************************************************************
//ステージ番号の設定
//*****************************************************************************
void CGame::SetStageNum(int nStageNum)
{
	m_nCntStage = nStageNum;
}

//*****************************************************************************
//ステージ番号の取得
//*****************************************************************************
int CGame::GetStageNum(void)
{
	return m_nCntStage;
}