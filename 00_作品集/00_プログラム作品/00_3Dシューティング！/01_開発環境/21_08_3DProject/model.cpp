//=============================================================================
//
// モデル処理 [model.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "joystick.h"
#include "model.h"

//*****************************************************************************
//インクリメント
//*****************************************************************************
CModel::CModel(OBJTYPE nPriority) :CScene(nPriority)
{
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = NULL;
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
	m_nldxModelParent = 0;
	memset(m_pTexture, 0, sizeof(m_pTexture));

	m_pos = ZeroVector3;
	m_posOld = ZeroVector3;
	m_rot = ZeroVector3;
	m_size = ZeroVector3;
	m_VectOld = ZeroVector3;

}

//*****************************************************************************
//デクリメント
//*****************************************************************************
CModel::~CModel()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CModel::Init()
{
	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CModel::Uninit(void)
{
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = NULL;

	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));

	Release();
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CModel::Update(void)
{
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CModel::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	D3DMATERIAL9 matDef;					//現在のマテリアル保持用

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 拡大率を反映
	D3DXMatrixScaling(&mtxScale, m_size.x, m_size.y, m_size.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得する
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタ
	D3DXMATERIAL*pMat;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//マテリアルのアンビエントにディフューズカラーを設定
		pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		if (m_pMesh != NULL)
		{
			//モデルパーツの描画
			m_pMesh->DrawSubset(nCntMat);
		}

		pDevice->SetTexture(0, nullptr);
	}

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
}

//*****************************************************************************
// 回転後の座標計算
//*****************************************************************************
D3DXVECTOR3 CModel::VertexRotate(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, const CModel::VERTEX &vertexType)
{
	//頂点座標用の変数
	D3DXVECTOR3 vertex = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (vertexType)
	{
	case VER_A:

		vertex = D3DXVECTOR3(
			(-(size.x / 2) * cosf(rot.y)) + ((size.z / 2) * sinf(rot.y)) + pos.x,
			pos.y,
			((size.x / 2) * sinf(rot.y)) + ((size.z / 2) * cosf(rot.y)) + pos.z);

		break;

	case VER_B:

		vertex = D3DXVECTOR3(
			((size.x / 2) * cosf(rot.y)) + ((size.z / 2) * sinf(rot.y)) + pos.x,
			pos.y,
			(-(size.x / 2) * sinf(rot.y)) + ((size.z / 2) * cosf(rot.y)) + pos.z);

		break;

	case VER_C:

		vertex = D3DXVECTOR3(
			((size.x / 2) * cosf(rot.y)) + (-(size.z / 2) * sinf(rot.y)) + pos.x,
			pos.y,
			(-(size.x / 2) * sinf(rot.y)) + (-(size.z / 2) * cosf(rot.y)) + pos.z);

		break;

	case VER_D:

		vertex = D3DXVECTOR3(
			(-(size.x / 2) * cosf(rot.y)) + (-(size.z / 2) * sinf(rot.y)) + pos.x,
			pos.y,
			((size.x / 2) * sinf(rot.y)) + (-(size.z / 2) * cosf(rot.y)) + pos.z);

		break;
	}

	return vertex;
}