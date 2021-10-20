//=============================================================================
//
// 床処理 [floor.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _FLOOR_H_
#define _FLOOR_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "scene3d.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CFloor :public CScene3D
{
public:
	CFloor(OBJTYPE Priority = CScene::OBJTYPE_FLOOR);	//コンストラクタ
	~CFloor();											//デストラクタ

	static void Load();		//ロード処理
	static void Unload();	//アンロード処理

	static CFloor *Create(const int &nCreateNum);	//生成処理

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	void GetFloorData(void);	//床データの取得処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ

	int m_nCreateNum;	//生成順
};

#endif