//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
LPD3DXMESH CPlayer::m_apMesh[TYPE_MAX] = {};
LPD3DXBUFFER CPlayer::m_apBuffMat[TYPE_MAX] = {};
DWORD CPlayer::m_NumMat[TYPE_MAX] = {};

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CPlayer::CPlayer(OBJTYPE Priority) :CCharacter(Priority)
{
	m_type = TYPE_NONE;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CPlayer::~CPlayer()
{
}

//*****************************************************************************
//ロード
//*****************************************************************************
void CPlayer::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//〇------------------〇
	// Xファイルの読み込み
	//〇------------------〇

	//プレイヤー１
	D3DXLoadMeshFromX("Data/Models/player1.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_apBuffMat[TYPE_PLAYER_1],
		NULL,
		&m_NumMat[TYPE_PLAYER_1],
		&m_apMesh[TYPE_PLAYER_1]
	);

	//プレイヤー２
	D3DXLoadMeshFromX("Data/Models/player2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_apBuffMat[TYPE_PLAYER_2],
		NULL,
		&m_NumMat[TYPE_PLAYER_2],
		&m_apMesh[TYPE_PLAYER_2]
	);
}

//*****************************************************************************
//アンロード
//*****************************************************************************
void CPlayer::Unload()
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_apMesh[nCount] != nullptr)
		{ //メッシュの開放
			m_apMesh[nCount]->Release();
			m_apMesh[nCount] = nullptr;
		}

		if (m_apBuffMat[nCount] != nullptr)
		{ //バッファの開放
			m_apBuffMat[nCount]->Release();
			m_apBuffMat[nCount] = nullptr;
		}
	}
}

//*****************************************************************************
//生成処理
//*****************************************************************************
CPlayer * CPlayer::Create(const TYPE &type)
{
	CPlayer *pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{
		//タイプの代入
		pPlayer->m_type = type;

		//プレイヤーの初期化処理
		pPlayer->Init();

		return pPlayer;
	}

	return nullptr;
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CPlayer::Init(void)
{
	//モデル情報の設定
	BindModel(m_apMesh[m_type], m_apBuffMat[m_type], m_NumMat[m_type]);

	//プレイヤーデータの設定処理
	InitPlayer(m_type);

	//キャラクターの初期化処理
	CCharacter::Init();

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CPlayer::Uninit(void)
{
	//敗者判定の設定
	CGame::SetLoser(m_type);

	//キャラクターの終了処理
	CCharacter::Uninit();
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CPlayer::Update(void)
{
	HRESULT Hit = S_OK;

	if (Hit == S_OK)
	{
		//移動処理
		Move(m_type);
	}

	if (Hit == S_OK)
	{
		//プレイヤーと壁の当たり判定
		HitWall(m_type);
	}

	if (Hit == S_OK)
	{
		//プレイヤーと障害物の当たり判定
		HitBlock(m_type);
	}

	if (Hit == S_OK)
	{
		//プレイヤーと弾の当たり判定
		Hit = HitBullet(m_type);
	}

	if (Hit == S_OK)
	{
		//発射処理
		Shot(m_type);
	}

	if (Hit == S_OK)
	{
		//キャラクターの更新処理
		CCharacter::Update();
	}

	if (Hit != S_OK)
	{
		//終了処理
		Uninit();
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CPlayer::Draw(void)
{
	//キャラクターの描画処理
	CCharacter::Draw();
}