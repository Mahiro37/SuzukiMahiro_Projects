//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "bullet.h"
#include "collision.h"
#include "manager.h"
#include "renderer.h"
#include "wall.h"
#include "block.h"
#include "bulletData.h"
#include "effect_explosion_bullet.h"
#include "effect_wall_hit.h"
#include "player.h"
#include "game.h"
#include "effect_explosion_player.h"

//*****************************************************************************
//静的メンバ変数宣言
//*****************************************************************************
LPD3DXMESH CBullet::m_pMesh[TYPE_MAX] = {};
LPD3DXBUFFER CBullet::m_pBuffMat[TYPE_MAX] = {};
DWORD CBullet::m_NumMat[TYPE_MAX] = {};

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define BULLET_COLLISION_ROT (D3DXVECTOR3(D3DXToRadian(90), 0.0f, 0.0f))	//弾の当たり判定の角度

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CBullet::CBullet(OBJTYPE Priority) :CModel(Priority)
{
	m_type = TYPE_NONE;
	m_PlayerType = CCharacter::TYPE_NONE;
	m_vect = ZeroVector3;
	m_fMove = 0.0f;
	m_nLife = 0;
	m_nCntLife = 0;
	m_bHit = false;

	m_pCollision = nullptr;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CBullet::~CBullet()
{
}

//*****************************************************************************
//ロード
//*****************************************************************************
void CBullet::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//〇------------------〇
	// Xファイルの読み込み
	//〇------------------〇

	//弾１(プレイヤー１)
	D3DXLoadMeshFromX("Data/Models/bullet1.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat[TYPE_BULLET1],
		NULL,
		&m_NumMat[TYPE_BULLET1],
		&m_pMesh[TYPE_BULLET1]);

	//弾２(プレイヤー２)
	D3DXLoadMeshFromX("Data/Models/bullet2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat[TYPE_BULLET2],
		NULL,
		&m_NumMat[TYPE_BULLET2],
		&m_pMesh[TYPE_BULLET2]);
}

//*****************************************************************************
//アンロード
//*****************************************************************************
void CBullet::Unload()
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_pMesh[nCount] != NULL)
		{
			//メッシュの破棄
			m_pMesh[nCount]->Release();
			m_pMesh[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_pBuffMat[nCount] != NULL)
		{
			//バッファの破棄
			m_pBuffMat[nCount]->Release();
			m_pBuffMat[nCount] = NULL;
		}
	}
}

//*****************************************************************************
//弾の生成
//*****************************************************************************
CBullet * CBullet::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const D3DXVECTOR3 &vect, const TYPE &type, const CCharacter::TYPE &PlayerType)
{
	CBullet *pBullet = new CBullet;

	if (pBullet != nullptr)
	{
		//弾の情報の設定
		pBullet->SetPos(pos);
		pBullet->SetRot(rot);
		pBullet->m_vect = vect;
		pBullet->m_type = type;
		pBullet->m_PlayerType = PlayerType;

		//弾の初期化処理
		pBullet->Init();

		return pBullet;
	}

	return nullptr;
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CBullet::Init()
{
	//弾データの取得処理
	GetBulletData();

	HRESULT Hit = S_OK;

	//初期値の衝突処理
	Hit = HitInit();
	if (Hit != S_OK)
	{
		//終了処理
		Uninit();
	}

	//モデルの初期化処理
	CModel::Init();

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CBullet::Uninit(void)
{
	if (m_pCollision != nullptr)
	{
		//当たり判定の終了処理
		m_pCollision->Uninit();
		m_pCollision = nullptr;
	}

	//モデルの終了処理
	CModel::Uninit();
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CBullet::Update(void)
{
	HRESULT Hit = S_OK;

	if (Hit == S_OK)
	{
		//移動処理
		Move();
	}

	if (Hit == S_OK)
	{
		//弾と弾の当たり判定
		Hit = HitBullet();
	}

	if (Hit == S_OK)
	{
		//弾と壁の当たり判定
		Hit = HitWall();
	}

	if (Hit == S_OK)
	{
		//弾と障害物の当たり判定
		Hit = HitBlock();
	}

	if (Hit == S_OK)
	{
		//モデルの更新処理
		CModel::Update();
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
void CBullet::Draw(void)
{
	//モデルの描画処理
	CModel::Draw();
}

//*****************************************************************************
//移動処理
//*****************************************************************************
void CBullet::Move(void)
{
	//過去の座標を設定
	SetPosOld(GetPos());

	if (D3DXVec3Length(&m_vect) != m_fMove)
	{ //移動量が規定値より大きいとき
	  //正しい移動量を計算し代入
		m_vect = m_vect / D3DXVec3Length(&m_vect) * m_fMove;
	}

	//弾を移動させる
	SetMove(m_vect);

	if (m_pCollision != NULL)
	{
		//当たり判定モデル情報の設定
		m_pCollision->SetPos(GetPos());
	}
}

//*****************************************************************************
//初期値の衝突処理
//*****************************************************************************
HRESULT CBullet::HitInit(void)
{
	//弾と壁の当たり判定
	CWall *pWall = NULL;
	do
	{
		pWall = dynamic_cast<CWall*>(GetScene(OBJTYPE_WALL));

		if (pWall != NULL)
		{
			if (pWall->GetCollision() != NULL)
			{
				D3DXVECTOR3 WallPos = pWall->GetCollision()->GetPos();
				D3DXVECTOR3 WallSize = pWall->GetCollision()->GetSize();
				D3DXVECTOR3 WallRot = pWall->GetCollision()->GetRot();

				if (CCollision::RectangleCircularCollision(WallPos, WallSize, WallRot.y, GetPos(), (m_pCollision->GetSize().x / 2)) == true)
				{ //当たり判定(矩形と円形)
				  //判定をtrueにする
					m_bHit = true;
				}
			}
		}
	} while (pWall != NULL);

	//弾と障害物の当たり判定
	CBlock* pBlock = NULL;
	do
	{
		pBlock = dynamic_cast<CBlock*>(GetScene(OBJTYPE_BLOCK));

		if (pBlock != NULL)
		{
			if (pBlock->GetCollision() != NULL)
			{
				D3DXVECTOR3 BlockPos = pBlock->GetCollision()->GetPos();
				D3DXVECTOR3 BlockSize = pBlock->GetCollision()->GetSize();
				D3DXVECTOR3 BlockRot = pBlock->GetCollision()->GetRot();

				if (CCollision::RectangleCircularCollision(BlockPos, BlockSize, BlockRot.y, GetPos(), (m_pCollision->GetSize().x / 2)) == true)
				{ //当たり判定(矩形と円形)
				  //判定をtrueにする
					m_bHit = true;
				}
			}
		}
	} while (pBlock != NULL);

	if (m_bHit == true)
	{ //判定がtrueのとき
	  //判定を初期化
		m_bHit = false;

		if (CGame::GetPlayer(m_PlayerType) != NULL)
		{ //ポインタがNULLじゃないとき
			//爆発エフェクトの生成
			CEffectExplosionPlayer::Create(CGame::GetPlayer(m_PlayerType)->GetPos());

			//プレイヤーの終了処理
			CGame::GetPlayer(m_PlayerType)->Uninit();
		}

		return S_FALSE;
	}

	return S_OK;
}

//*****************************************************************************
//弾の衝突処理
//*****************************************************************************
HRESULT CBullet::HitBullet(void)
{
	CBullet *pBullet = NULL;
	do
	{
		pBullet = dynamic_cast<CBullet*>(GetScene(OBJTYPE_BULLET));
		if (pBullet != NULL)
		{
			if (this != pBullet)
			{
				if (pBullet->GetCollision() != NULL)
				{
					D3DXVECTOR3 BulletPos = pBullet->GetCollision()->GetPos();
					D3DXVECTOR3 BulletSize = pBullet->GetCollision()->GetSize();

					if (CCollision::SphereCollision(BulletPos, BulletSize.x / 2, GetPos(), m_pCollision->GetSize().x / 2) == true)
					{ //当たり判定(矩形と円形)
					  //弾の爆発エフェクトの生成
						CEffectExplosionBullet::Create(GetPos());

						//当った弾の終了処理
						pBullet->Uninit();
						return S_FALSE;
					}
				}
			}
		}
	} while (pBullet != NULL);

	return S_OK;
}

//*****************************************************************************
//壁の衝突処理
//*****************************************************************************
HRESULT CBullet::HitWall(void)
{
	CWall *pWall = NULL;
	do
	{
		pWall = dynamic_cast<CWall*>(GetScene(OBJTYPE_WALL));

		if (pWall != NULL)
		{
			if (pWall->GetCollision() != NULL)
			{
				D3DXVECTOR3 WallPos = pWall->GetCollision()->GetPos();
				D3DXVECTOR3 WallSize = pWall->GetCollision()->GetSize();
				D3DXVECTOR3 WallRot = pWall->GetCollision()->GetRot();

				if (CCollision::RectangleCircularCollision(WallPos, WallSize, WallRot.y, GetPos(), (m_pCollision->GetSize().x / 2)) == true)
				{ //当たり判定(矩形と円形)
				  //弾と壁の衝突エフェクトの生成
					CEffectWallHit::Create(GetPos());

					//反射回数をカウント
					m_nCntLife++;

					if (m_nCntLife >= m_nLife)
					{//反射回数が規定値(BULLET_LIFE)になったら
						return S_FALSE;
					}

					//１フレーム前の位置に戻す
					SetPos(GetPosOld());

					//反射ベクトルの計算
					m_vect = m_pCollision->ReflectionVect(m_vect, pWall->GetVect().dc, WallRot);

					//正しい方向に移動させる
					SetMove(m_vect);

					if (m_pCollision != NULL)
					{
						//当たり判定モデル情報の設定
						m_pCollision->SetPos(GetPos());
					}
				}
			}
		}
	} while (pWall != NULL);

	return S_OK;
}

//*****************************************************************************
//障害物の衝突処理
//*****************************************************************************
HRESULT CBullet::HitBlock(void)
{
	CBlock *pBlock = NULL;
	do
	{
		pBlock = dynamic_cast<CBlock*>(GetScene(OBJTYPE_BLOCK));

		if (pBlock != NULL)
		{
			if (pBlock->GetCollision() != NULL)
			{
				D3DXVECTOR3 BlockPos = pBlock->GetCollision()->GetPos();
				D3DXVECTOR3 BlockSize = pBlock->GetCollision()->GetSize();
				D3DXVECTOR3 BlockRot = pBlock->GetCollision()->GetRot();

				if (CCollision::RectangleCircularCollision(BlockPos, BlockSize, BlockRot.y, GetPos(), (m_pCollision->GetSize().x / 2)) == true)
				{ //当たり判定(矩形と円形)
					//弾と壁の衝突エフェクトの生成
					CEffectWallHit::Create(GetPos());

					//反射回数をカウント
					m_nCntLife++;

					if (m_nCntLife >= m_nLife)
					{//反射回数が規定値(BULLET_LIFE)になったら
						return S_FALSE;
					}

					//１フレーム前の位置に戻す
					SetPos(GetPosOld());

					//弾と頂点との距離
					CCollision::DISTANCE Distance[VER_MAX];

					//各頂点の位置を代入
					Distance[VER_A].pos = pBlock->GetVect().a;
					Distance[VER_B].pos = pBlock->GetVect().b;
					Distance[VER_C].pos = pBlock->GetVect().c;
					Distance[VER_D].pos = pBlock->GetVect().d;

					//各頂点から弾の中心までの距離を計算する
					Distance[VER_A].length = D3DXVec3Length(&(GetPos() - pBlock->GetVect().a));
					Distance[VER_B].length = D3DXVec3Length(&(GetPos() - pBlock->GetVect().b));
					Distance[VER_C].length = D3DXVec3Length(&(GetPos() - pBlock->GetVect().c));
					Distance[VER_D].length = D3DXVec3Length(&(GetPos() - pBlock->GetVect().d));

					//昇順の設定(仮)
					Distance[VER_A].rank = 1;
					Distance[VER_B].rank = 2;
					Distance[VER_C].rank = 3;
					Distance[VER_D].rank = 4;

					//方向ベクトル取得用(使わない)
					VECT V;

					//方向ベクトルの計算(m_vectをポインタで渡すことで、返り値無しでm_vectの値を変えることができる)
					m_pCollision->DirectionVect(GetPos(), m_vect, Distance, V);

					//正しい方向に移動させる
					SetMove(m_vect);

					if (m_pCollision != NULL)
					{
						//当たり判定モデル情報の設定
						m_pCollision->SetPos(GetPos());
					}
				}
			}
		}
	} while (pBlock != NULL);

	return S_OK;
}

//*****************************************************************************
//弾の反射処理
//*****************************************************************************
D3DXVECTOR3 CBullet::ReflectVector(const D3DXVECTOR3 &front, const D3DXVECTOR3 &normal)
{
	//〇----------------------------------〇
	// front : 進行ベクトル
	// normal: 衝突点での法線ベクトル
	//〇----------------------------------〇
	D3DXVECTOR3 Vect = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3Normalize(&Vect, &(front - 2.0f * D3DXVec3Dot(&front, &normal) * normal));//D3DXVec3Dot:内積の算出
	
	return Vect;
}

//*****************************************************************************
//弾データの取得処理
//*****************************************************************************
void CBullet::GetBulletData(void)
{
	//弾データの取得
	CBulletData::CreateInfo* CBulletData = CManager::GetBulletData()->GetCreateInfo(m_type);

	if (CBulletData != NULL)
	{
		//〇-------〇
		// 弾の設定
		//〇-------〇

		//移動量
		m_fMove = CBulletData->fMove;

		//反射数
		m_nLife = CBulletData->nLife;

		//方向ベクトル
		m_vect = m_vect / D3DXVec3Length(&m_vect) * m_fMove;

		//モデル情報
		SetSize(CBulletData->modelSize);
		BindModel(m_pMesh[m_type], m_pBuffMat[m_type], m_NumMat[m_type]);

		if (m_pCollision == NULL)
		{
			//当たり判定の生成
			m_pCollision = CCollision::Create(
				GetPos(),
				CBulletData->collisionSize,
				ZeroVector3,
				CCollision::TYPE_SPHERE);
		}
	}
}