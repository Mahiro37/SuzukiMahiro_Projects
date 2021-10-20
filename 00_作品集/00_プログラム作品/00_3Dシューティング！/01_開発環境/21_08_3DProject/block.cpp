//=============================================================================
//
// 障害物処理 [block.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "block.h"
#include "blockData.h"
#include "renderer.h"
#include "manager.h"
#include "collision.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
LPD3DXMESH CBlock::m_pMesh = nullptr;
LPD3DXBUFFER CBlock::m_pBuffMat = nullptr;
DWORD CBlock::m_nNumMat = NULL;

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CBlock::CBlock(OBJTYPE nPriority) :CModel(nPriority)
{
	m_nCreateNum = 0;

	m_pCollision = NULL;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CBlock::~CBlock()
{
}

//*****************************************************************************
//ロード
//*****************************************************************************
void CBlock::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX("Data/Models/block.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh
	);
}

//*****************************************************************************
//アンロード
//*****************************************************************************
void CBlock::Unload()
{
	if (m_pMesh != nullptr)
	{ //メッシュの開放
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	if (m_pBuffMat != nullptr)
	{ //バッファの開放
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}
}

//*****************************************************************************
//生成処理
//*****************************************************************************
CBlock * CBlock::Create(const int nCreateNum)
{
	CBlock *pWall = new CBlock;

	if (pWall != nullptr)
	{
		//障害物の設定
		pWall->m_nCreateNum = nCreateNum;

		//障害物の初期化処理
		pWall->Init();

		return pWall;
	}

	return nullptr;
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CBlock::Init(void)
{
	//障害物データの取得処理
	GetBlockData();

	//モデルの初期化処理
	CModel::Init();

	return E_NOTIMPL;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CBlock::Uninit(void)
{
	//モデルの終了処理
	CModel::Uninit();

	if (m_pCollision != NULL)
	{
		//当たり判定の終了処理
		m_pCollision->Uninit();
	}
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CBlock::Update(void)
{
	//モデルの更新処理
	CModel::Update();
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CBlock::Draw(void)
{
	//モデルの描画処理
	CModel::Draw();
}

//*****************************************************************************
//障害物データの取得処理
//*****************************************************************************
void CBlock::GetBlockData(void)
{
	//壁データの取得
	CBlockData::CreateInfo* pBlockData = CManager::GetBlockData()->GetCreateInfo(m_nCreateNum);

	if (pBlockData != NULL)
	{
		//〇-------〇
		// 壁の設定
		//〇-------〇

		//モデル情報の設定
		SetPos(pBlockData->pos);
		SetSize(pBlockData->size);
		SetRot(pBlockData->rot);
		BindModel(m_pMesh, m_pBuffMat, m_nNumMat);

		if (m_pCollision == NULL)
		{
			//当たり判定の大きさの取得
			D3DXVECTOR3 CollisionSize = pBlockData->collisionSize;

			//当たり判定の生成
			m_pCollision = CCollision::Create(
				pBlockData->pos,
				CollisionSize,
				pBlockData->rot,
				CCollision::TYPE_BOX);

			//座標を求める
			m_vect.a = VertexRotate(pBlockData->pos, CollisionSize, pBlockData->rot, VER_A);	//A座標
			m_vect.b = VertexRotate(pBlockData->pos, CollisionSize, pBlockData->rot, VER_B);	//B座標
			m_vect.c = VertexRotate(pBlockData->pos, CollisionSize, pBlockData->rot, VER_C);	//C座標
			m_vect.d = VertexRotate(pBlockData->pos, CollisionSize, pBlockData->rot, VER_D);	//D座標

			//壁の当たり判定の方向ベクトルを求める
			m_vect.ad = m_vect.d - m_vect.a;	//ADベクトル
			m_vect.dc = m_vect.c - m_vect.d;	//DCベクトル
			m_vect.cb = m_vect.b - m_vect.c;	//CBベクトル
			m_vect.ba = m_vect.a - m_vect.b;	//BAベクトル
		}
	}
}