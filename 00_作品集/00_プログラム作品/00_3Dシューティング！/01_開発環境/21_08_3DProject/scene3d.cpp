//=============================================================================
//
// 3Dオブジェクト処理 [scene3d.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CScene3D::CScene3D(OBJTYPE nPriority) :CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CScene3D::~CScene3D()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CScene3D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	if (FAILED(
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_POLYGON,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,				// 頂点バッファへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	// 頂点情報を設定
	VERTEX_3D *pVtx = NULL;

	//頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//場所の設定
	pVtx[0].pos = D3DXVECTOR3(-(m_size.x / 2), +(m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+(m_size.x / 2), +(m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-(m_size.x / 2), -(m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+(m_size.x / 2), -(m_size.y / 2), 0.0f);

	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[1].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[2].nor = D3DXVECTOR3(0, 0, -1);
	pVtx[3].nor = D3DXVECTOR3(0, 0, -1);

	//カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CScene3D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//破棄
	Release();
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CScene3D::Update(void)
{
	// 頂点情報を設定
	VERTEX_3D *pVtx = NULL;

	//頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//場所の設定
	pVtx[0].pos = D3DXVECTOR3(-(m_size.x / 2), +(m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+(m_size.x / 2), +(m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-(m_size.x / 2), -(m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+(m_size.x / 2), -(m_size.y / 2), 0.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CScene3D::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	//行列計算用のマトリクス
	D3DXMATRIX mtxRot, mtxTrans;

	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	
	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	
	//セットテクスチャ
	pDevice->SetTexture(0, m_pTexture);
	
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	
	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}