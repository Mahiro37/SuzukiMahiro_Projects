//=============================================================================
//
// ビルボード処理 [billboard.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CBillboard : public CScene
{
public:
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_PLAYER1_BULLET,	//弾(プレイヤー１)
		TYPE_PLAYER1_BOMB,		//ボム(プレイヤー１)
		TYPE_PLAYER2_BULLET,	//弾(プレイヤー２)
		TYPE_PLAYER2_BOMB,		//ボム(プレイヤー２)
		TYPE_MAX
	};

	CBillboard(OBJTYPE nPriority);	//コンストラクタ
	~CBillboard();					//デストラクタ

	static HRESULT Load(void);	//ロード処理
	static void Unload(void);	//アンロード処理

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	//各種設定
	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }												//位置の設定
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }											//大きさの設定
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }												//角度の設定
	void SetCol(const D3DXCOLOR &col) { m_col = col; }													//色の設定
	void SetType(const TYPE &pTexture) { m_type = pTexture; }											//テクスチャの種類の設定
	void SetTexture(const float &fTexX, const float &fTexY, const float &fTexX2, const float &fTexY2)
	{ m_fTexX = fTexX; m_fTexX2 = fTexX2; m_fTexY = fTexY; m_fTexY2 = fTexY2; }							//テクスチャ座標の設定

	D3DXVECTOR3 GetPos(void) { return m_pos; }		//位置の取得
	D3DXVECTOR3 GetSize(void) { return m_size; }	//大きさの取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }		//角度の取得
	D3DXCOLOR GetCol(void) { return m_col; }		//色の取得
	TYPE GetType(void) { return m_type; }			//種類の取得

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// 頂点バッファへのポインタ

	static TYPE m_type;		//種類
	D3DXVECTOR3 m_pos;		//位置座標
	D3DXVECTOR3 m_size;		//サイズ
	D3DXVECTOR3 m_rot;		//角度
	D3DXCOLOR m_col;		//色
	float m_fTexX;			//テクスチャX座標
	float m_fTexX2;			//テクスチャX2座標
	float m_fTexY;			//テクスチャY座標
	float m_fTexY2;			//テクスチャY2座標
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
};
#endif