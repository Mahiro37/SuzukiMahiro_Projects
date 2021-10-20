//=============================================================================
//
// アニメーション処理 [animation.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "manager.h"
#include "renderer.h"
#include "joystick.h"
#include "animation.h"

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CAnimation::CAnimation(OBJTYPE nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nAnimLine = 0;
	m_nAnimColumn = 0;
	m_nAnimSpeed = 0;
	m_nCntLine = 0;
	m_nCntColumn = 0;
	m_nCntAnim = 0;
	m_repeat = REP_REPEAT;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CAnimation::~CAnimation()
{
}

//*****************************************************************************
//初期化
//*****************************************************************************
HRESULT CAnimation::Init(void)
{
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	//頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,													//頂点バッファの使用法
		FVF_VERTEX_3D,														//使用する頂点フォーマット
		D3DPOOL_MANAGED,													//リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,														//頂点バッファへのポインタ
		NULL)))																//NULLに設定
	{
		return E_FAIL;
	}

	//頂点情報を設定
	VERTEX_3D *pVtx;

	//頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//場所の設定
	pVtx[0].pos = D3DXVECTOR3(-(m_size.x / 2), +(m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+(m_size.x / 2), +(m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-(m_size.x / 2), -(m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+(m_size.x / 2), -(m_size.y / 2), 0.0f);

	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2((float)m_nCntLine * (float)(1.0f / m_nAnimLine),								(float)m_nCntColumn * (1.0f / (float)m_nAnimColumn));
	pVtx[1].tex = D3DXVECTOR2((float)m_nCntLine * (float)(1.0f / m_nAnimLine) + (float)(1.0f / m_nAnimLine),(float)m_nCntColumn * (1.0f / (float)m_nAnimColumn));
	pVtx[2].tex = D3DXVECTOR2((float)m_nCntLine * (float)(1.0f / m_nAnimLine),								(float)m_nCntColumn * (1.0f / (float)m_nAnimColumn) + (float)(1.0f / m_nAnimColumn));
	pVtx[3].tex = D3DXVECTOR2((float)m_nCntLine * (float)(1.0f / m_nAnimLine) + (float)(1.0f / m_nAnimLine),(float)m_nCntColumn * (1.0f / (float)m_nAnimColumn) + (float)(1.0f / m_nAnimColumn));

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}
//*****************************************************************************
//終了処理
//*****************************************************************************
void CAnimation::Uninit(void)
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
void CAnimation::Update(void)
{
	//アニメーションカウントを進める
	m_nCntAnim++;

	//頂点情報を設定
	VERTEX_3D *pVtx = NULL;

	//頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//場所の設定
	pVtx[0].pos = D3DXVECTOR3(-(m_size.x / 2), +(m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+(m_size.x / 2), +(m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-(m_size.x / 2), -(m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+(m_size.x / 2), -(m_size.y / 2), 0.0f);

	//法線の設定(どこから見ても暗くならないようにしてます)
	pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(1.0f, 1.0f, -1.0f);

	//カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	if (m_nCntAnim >= m_nAnimSpeed)
	{ //アニメーションカウントが規定値を超えたとき
		//アニメーションカウントを初期化
		m_nCntAnim = 0;

		//行数カウントを進める
		m_nCntLine++;

		if (m_nCntLine >= m_nAnimLine)
		{ //行数カウントが規定値を超えたとき
			//行数カウントを初期化
			m_nCntLine = 0;

			//列数カウントを進める
			m_nCntColumn++;
		}

		if (m_nCntColumn >= m_nAnimColumn)
		{ //列数カウントが規定値を超えたとき
			//列数カウントを初期化
			m_nCntColumn = 0;

			if (m_repeat == REP_REPEAT)
			{ //リピートが必要なとき
				//行数と列数のカウントを初期化
				m_nCntLine = 0;
				m_nCntColumn = 0;
			}
			else if (m_repeat == REP_UNREPEAT)
			{ //リピートが必要ないとき
				//終了処理
				Uninit();
				return;
			}
		}

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((float)m_nCntLine * (float)(1.0f / m_nAnimLine),								(float)m_nCntColumn * (1.0f / (float)m_nAnimColumn));
		pVtx[1].tex = D3DXVECTOR2((float)m_nCntLine * (float)(1.0f / m_nAnimLine) + (float)(1.0f / m_nAnimLine),(float)m_nCntColumn * (1.0f / (float)m_nAnimColumn));
		pVtx[2].tex = D3DXVECTOR2((float)m_nCntLine * (float)(1.0f / m_nAnimLine),								(float)m_nCntColumn * (1.0f / (float)m_nAnimColumn) + (float)(1.0f / m_nAnimColumn));
		pVtx[3].tex = D3DXVECTOR2((float)m_nCntLine * (float)(1.0f / m_nAnimLine) + (float)(1.0f / m_nAnimLine),(float)m_nCntColumn * (1.0f / (float)m_nAnimColumn) + (float)(1.0f / m_nAnimColumn));
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CAnimation::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//行列計算用のマトリクス
	D3DXMATRIX mtxRot, mtxTrans;

	//ライト無効
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Zバッファを無効化
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//アルファテストの比較方法の設定（GREATERは基準値より大きい場合)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//セットテクスチャ
	pDevice->SetTexture(0, m_pTexture);

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//回転の逆行列
	pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxRot);
	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;

	//向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//アルファテスト無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//Zバッファを有効化
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//ライト有効
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}