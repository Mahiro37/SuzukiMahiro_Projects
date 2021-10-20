//=============================================================================
//
// 3Dオブジェクト処理 [scene3D.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CScene3D :public CScene
{
public:
	CScene3D(OBJTYPE nPriority);	//コンストラクタ
	~CScene3D();					//デストラクタ

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }							//位置の設定
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }							//角度の設定
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }						//サイズの設定
	void BindTexture(const LPDIRECT3DTEXTURE9 &pTexture) { m_pTexture = pTexture; }	//テクスチャの設定

private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファポインタ

	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_size;		//大きさ
	D3DXVECTOR3 m_rot;		//角度
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
};
#endif