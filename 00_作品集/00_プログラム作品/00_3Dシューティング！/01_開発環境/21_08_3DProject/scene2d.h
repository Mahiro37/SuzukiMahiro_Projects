//=============================================================================
//
// 2Dオブジェクト処理 [scene2D.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CScene2D :public CScene
{
public:
	CScene2D(OBJTYPE nPriority);	//コンストラクタ
	~CScene2D();					//デストラクタ

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理


	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }							//位置の設定
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }						//大きさの設定
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }							//角度の設定
	void SetCol(const D3DXCOLOR &color) { m_color = color; }						//色の設定
	void BindTexture(const LPDIRECT3DTEXTURE9 &pTexture) { m_pTexture = pTexture; }	//テクスチャの設定

	D3DXVECTOR3 GetPos(void) { return m_pos; }		//位置の取得
	D3DXVECTOR3 GetSize(void) { return m_size; }	//位置の取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }		//位置の取得
	D3DXCOLOR GetCol(void) { return m_color; }		//色の取得

private:
	LPDIRECT3DTEXTURE9		m_pTexture;	//テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファポインタ

	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_size;	//大きさ
	D3DXVECTOR3 m_rot;	//角度
	D3DXCOLOR m_color;	//色
	float m_fAngle;		//角度
	float m_fLength;	//半径
};

#endif // !_SCENE2D_H_
