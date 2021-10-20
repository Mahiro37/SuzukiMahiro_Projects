//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "playerData.h"
#include "bulletData.h"
#include "wallData.h"
#include "blockData.h"
#include "floorData.h"
#include "keyboard.h"
#include "mouse.h"
#include "joystick.h"
#include "scene.h"
#include "scene2d.h"
#include "scene3d.h"
#include "camera.h"
#include "light.h"
#include "title.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include "movie.h"
#include "player.h"
#include "billboard.h"
#include "bullet.h"
#include "ui.h"
#include "wall.h"
#include "collision.h"
#include "bullet.h"
#include "block.h"
#include "effect.h"
#include "floor.h"

//=============================================================================
//性的メンバ変数宣言
//=============================================================================
CRenderer *CManager::m_pRenderer = nullptr;
CInputKeyboard *CManager::m_pInputKeyboard = nullptr;
CInputMouse *CManager::m_pInputMouse = nullptr;
CInputJoystick *CManager::m_pInputJoystick = nullptr;
CCamera *CManager::m_pCamera = nullptr;
CLight *CManager::m_pLight = nullptr;
CSound *CManager::m_pSound = nullptr;
CFade *CManager::m_pFade = nullptr;
CDebugProc *CManager::m_pDebugProc = nullptr;
CMode *CManager::m_pMode = nullptr;
CManager::MODE CManager::m_mode = CManager::MODE_NONE;
CPlayerData* CManager::m_pPlayerData = nullptr;
CBulletData* CManager::m_pBulletData = nullptr;
CWallData* CManager::m_pWallData = nullptr;
CBlockData* CManager::m_pBlockData = nullptr;
CFloorData* CManager::m_pFloorData = nullptr;

//=============================================================================
//コンストラクタ
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd)
{
	//更新するオブジェクトタイプの設定
	CScene::SetUpdateType(CScene::OBJTYPE_MAX, nullptr);

	//--------------------
	//クラス生成,初期化
	//--------------------
	if (m_pRenderer == nullptr)
	{ //レンダラー
		m_pRenderer = new CRenderer;
		m_pRenderer->Init(hWnd, TRUE);
	}
	if (m_pInputKeyboard == nullptr)
	{ //キーボード
		m_pInputKeyboard = new CInputKeyboard;
		m_pInputKeyboard->Init(hInstance, hWnd);
	}
	if (m_pInputMouse == nullptr)
	{ //マウスの生成
		m_pInputMouse = new CInputMouse;
		m_pInputMouse->Init(hInstance, hWnd);
	}
	if (m_pInputJoystick == nullptr)
	{ //ゲームパッド
		m_pInputJoystick = new CInputJoystick;
		m_pInputJoystick->Init(hInstance, hWnd);
	}
	if (m_pSound == nullptr)
	{ //サウンド
		m_pSound = new CSound;
		// 初期化処理
		if (FAILED(m_pSound->Init(hWnd)))
		{
			return -1;
		}
	}
	if (m_pFade == nullptr)
	{ //フェード
		m_pFade = new CFade(CScene::OBJTYPE_FADE);
		m_pFade->Init();
	}
	if (m_pPlayerData == nullptr)
	{ //プレイヤーデータ
		m_pPlayerData = new CPlayerData;
		m_pPlayerData->Init();
	}
	if (m_pBulletData == nullptr)
	{ //弾データ
		m_pBulletData = new CBulletData;
		m_pBulletData->Init();
	}
	if (m_pWallData == nullptr)
	{ //壁データ
		m_pWallData = new CWallData;
		m_pWallData->Init();
	}
	if (m_pBlockData == nullptr)
	{ //障害物データ
		m_pBlockData = new CBlockData;
		m_pBlockData->Init();
	}
	if (m_pFloorData == nullptr)
	{ //床データ
		m_pFloorData = new CFloorData;
		m_pFloorData->Init();
	}

	//テクスチャの読み込み
	LoadAll();

	//モードの設定
	SetMode(MODE_TITLE);

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleaseAll();

	//テクスチャの破棄
	UnloadAll();
	
	if (m_pLight != nullptr)
	{
		//ライトの終了
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}
	
	if (m_pCamera != nullptr)
	{
		//カメラの終了
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	
	if (m_pInputJoystick != nullptr)
	{
		//ゲームパッドの終了
		m_pInputJoystick->Uninit();
		delete m_pInputJoystick;
		m_pInputJoystick = nullptr;
	}
	
	if (m_pInputKeyboard != nullptr)
	{
		//キーボードの終了
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}
	
	if (m_pInputMouse != nullptr)
	{
		//マウスの終了
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = nullptr;
	}

	if (m_pMode != nullptr)
	{
		//その時のモードの終了
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	if (m_pSound != nullptr)
	{
		//サウンド終了
		m_pSound->CSound::StopSound();
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = nullptr;
	}
	if (m_pPlayerData != nullptr)
	{
		//プレイヤーデータの終了
		m_pPlayerData->Uninit();
		delete m_pPlayerData;
		m_pPlayerData = nullptr;
	}
	if (m_pPlayerData != nullptr)
	{
		//弾データの終了
		m_pBulletData->Uninit();
		delete m_pBulletData;
		m_pBulletData = nullptr;
	}
	if (m_pWallData != nullptr)
	{
		//壁データの終了
		m_pWallData->Uninit();
		delete m_pWallData;
		m_pWallData = nullptr;
	}
	if (m_pBlockData != nullptr)
	{
		//障害物データの終了
		m_pBlockData->Uninit();
		delete m_pBlockData;
		m_pBlockData = nullptr;
	}
	if (m_pFloorData != nullptr)
	{
		//床データの終了
		m_pFloorData->Uninit();
		delete m_pFloorData;
		m_pFloorData = nullptr;
	}

	if (m_pRenderer != nullptr)
	{
		//レンダラーの終了
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	if (m_pInputJoystick != nullptr)
	{
		//キーボードの更新処理
		m_pInputKeyboard->Update();
	}

	if (m_pInputJoystick != nullptr)
	{
		//ジョイスティックの更新処理
		m_pInputJoystick->Update();
	}

	if (m_pRenderer != nullptr)
	{
#ifdef _DEBUG
		// FPSのセット
		m_pRenderer->SetNumFPS(m_nCountFPS);
#endif
		//レンダラーの更新処理
		m_pRenderer->Update();
	}

	if (m_pCamera != nullptr)
	{
		//カメラのの更新処理
		m_pCamera->Update();
	}

	if (m_pMode != nullptr)
	{
		//その時のモードの更新処理
		m_pMode->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	if (m_pCamera != nullptr)
	{
		//カメラの設定
		m_pCamera->SetCamera();
	}

	if (m_pRenderer != nullptr)
	{
		//描画処理
		m_pRenderer->Draw();
	}
}

//=============================================================================
//テクスチャの読み込みまとめ
//=============================================================================
void CManager::LoadAll(void)
{
	//プレイヤー
	CPlayer::Load();

	//ビルボード
	CBillboard::Load();

	//エフェクト
	CEffect::Load();

	//UI
	CUi::Load();

	//壁
	CWall::Load();

	//当たり判定
	CCollision::Load();

	//弾
	CBullet::Load();

	//障害物
	CBlock::Load();

	//床
	CFloor::Load();
}

//=============================================================================
//テクスチャの破棄まとめ
//=============================================================================
void CManager::UnloadAll(void)
{	
	//プレイヤー
	CPlayer::Unload();

	//ビルボード
	CBillboard::Unload();

	//エフェクト
	CEffect::Unload();

	//UI
	CUi::Unload();

	//壁
	CWall::Unload();

	//当たり判定
	CCollision::Unload();

	//弾
	CBullet::Unload();

	//障害物
	CBlock::Unload();

	//床
	CFloor::Unload();
}

//=============================================================================
//モードの設定
//=============================================================================
void CManager::SetMode(MODE mode)
{
	if (m_pMode != nullptr)
	{
		//その時のモードの終了処理
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	if (m_pMode == nullptr)
	{
		m_mode = mode;

		CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);

		switch (m_mode)
		{
		case MODE_TITLE:

			//タイトルの生成
			m_pMode = new CTitle;

			//タイトルの初期化処理
			m_pMode->Init();

			break;

		case MODE_GAME:

			//ゲームの生成
			m_pMode = new CGame;

			//ゲームの初期化処理
			m_pMode->Init();

			break;
		}
	}
}

//=============================================================================
//カメラの生成
//=============================================================================
void CManager::CreateCamera(void)
{
	if (m_pCamera == nullptr)
	{
		m_pCamera = new CCamera;
		if (m_pCamera != nullptr)
		{
			m_pCamera->Init();
		}
	}
}

//=============================================================================
//ライトの生成
//=============================================================================
void CManager::CreateLight(void)
{
	if (m_pLight == nullptr)
	{
		m_pLight = new CLight;
		if (m_pLight != nullptr)
		{
			m_pLight->Init();
		}
	}
}

//=============================================================================
//フェードの生成
//=============================================================================
void CManager::CreateFade(MODE mode)
{
	if (m_pFade != nullptr)
	{
		m_pFade->SetFade(mode);
	}
}