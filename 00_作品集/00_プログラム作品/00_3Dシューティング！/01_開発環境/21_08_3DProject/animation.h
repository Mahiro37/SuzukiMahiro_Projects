//=============================================================================
//
// アニメーション処理 [animation.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _ANIMATION_H_
#define _ANIMATION_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CAnimation : public CScene
{
public:
	//リピートするかどうかの列挙型
	typedef enum
	{
		REP_REPEAT = 0,	//リピートする
		REP_UNREPEAT	//リピートしない
	}REP;

	CAnimation(OBJTYPE nPriority);	//コンストラクタ
	~CAnimation();					//デストラクタ

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	//各種設定
	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }									//位置の設定
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }								//大きさの設定
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }									//角度の設定
	void SetCol(const D3DXCOLOR &col) { m_col = col; }										//色の設定
	void SetTex(const int &nAnimLine, const int &nAnimColumn, const int &nAnimSpeed)
	{ m_nAnimLine = nAnimLine; m_nAnimColumn = nAnimColumn; m_nAnimSpeed = nAnimSpeed; }	//テクスチャ座標の設定
	void BindTexture(const LPDIRECT3DTEXTURE9 &pTexture) { m_pTexture = pTexture; }			//テクスチャの種類の設定
	void SetRepeat(const REP &repeat) { m_repeat = repeat; }								//リピートするかの設定

	D3DXVECTOR3 GetPos(void) { return m_pos; }		//位置の取得
	D3DXVECTOR3 GetSize(void) { return m_size; }	//大きさの取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }		//角度の取得
	D3DXCOLOR GetCol(void) { return m_col; }		//色の取得

private:
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ

	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_size;		//大きさ
	D3DXVECTOR3 m_rot;		//角度
	D3DXCOLOR m_col;		//色

	int m_nAnimLine;	//アニメーションの行数
	int m_nAnimColumn;	//アニメーションの列数
	int m_nAnimSpeed;	//アニメーションの切り替え速度
	int m_nCntLine;		//アニメーションの行数カウント
	int m_nCntColumn;	//アニメーションの列数カウント
	int m_nCntAnim;		//アニメーションのカウント

	REP m_repeat;		//リピート判定
};
#endif