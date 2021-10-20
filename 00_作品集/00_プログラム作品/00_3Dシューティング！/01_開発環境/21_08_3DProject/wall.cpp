//=============================================================================
//
// 壁処理 [wall.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "wall.h"
#include "renderer.h"
#include "manager.h"
#include "collision.h"
#include "wallData.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
LPD3DXMESH CWall::m_pMesh = NULL;
LPD3DXBUFFER CWall::m_pBuffMat = NULL;
DWORD CWall::m_nNumMat = NULL;

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CWall::CWall(OBJTYPE nPriority) :CModel(nPriority)
{
	m_type = TYPE_NONE;
	m_nCreateNum = 0;
	memset(&m_vect, 0, sizeof(m_vect));
	m_pCollision = NULL;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CWall::~CWall()
{
}

//*****************************************************************************
//ロード
//*****************************************************************************
void CWall::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX("Data/Models/wall.x",
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
void CWall::Unload()
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
CWall * CWall::Create(const int &nCreateNum)
{
	CWall *pWall = new CWall;

	if (pWall != nullptr)
	{
		//壁の生成順の設定
		pWall->m_nCreateNum = nCreateNum;

		//壁の初期化処理
		pWall->Init();

		return pWall;
	}

	return nullptr;
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CWall::Init(void)
{
	//WallDataの取得処理
	GetWallData();

	//モデルの初期化処理
	CModel::Init();

	return E_NOTIMPL;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CWall::Uninit(void)
{
	if (m_pCollision != NULL)
	{
		m_pCollision->Uninit();
	}

	CModel::Uninit();
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CWall::Update(void)
{
	CModel::Update();
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CWall::Draw(void)
{
	CModel::Draw();
}

//*****************************************************************************
//WallDataの取得処理
//*****************************************************************************
void CWall::GetWallData(void)
{
	//壁データの取得
	CWallData::CreateInfo* pWallData = CManager::GetWallData()->GetCreateInfo(m_nCreateNum);

	if (pWallData != NULL)
	{
		//〇-------〇
		// 壁の設定
		//〇-------〇

		//モデル情報の取得
		D3DXVECTOR3 ModelPos = pWallData->pos;
		D3DXVECTOR3 ModelSize = pWallData->size;
		D3DXVECTOR3 ModelRot = pWallData->rot;

		//モデル情報の設定
		SetPos(ModelPos);
		SetSize(ModelSize);
		SetRot(ModelRot);
		BindModel(m_pMesh, m_pBuffMat, m_nNumMat);

		//種類の設定
		m_type = (CWall::TYPE)pWallData->nType;

		if (m_pCollision == NULL)
		{
			//当たり判定の大きさの取得
			D3DXVECTOR3 CollisionSize = pWallData->collisionSize;

			//当たり判定の生成
			m_pCollision = CCollision::Create(
				ModelPos,
				CollisionSize,
				ModelRot,
				CCollision::TYPE_BOX);

			//D座標を求める
			m_vect.d = VertexRotate(ModelPos, CollisionSize, ModelRot, VER_D);

			//C座標を求める
			m_vect.c = VertexRotate(ModelPos, CollisionSize, ModelRot, VER_C);

			//壁の当たり判定の方向ベクトル(DCベクトル)を求める
			m_vect.dc = m_vect.c - m_vect.d;

			//方向ベクトルとして保存
			m_vect.direction = m_vect.dc;
		}
	}
}