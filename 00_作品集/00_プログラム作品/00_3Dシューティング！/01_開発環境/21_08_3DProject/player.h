//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "character.h"
#include "bullet.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CPlayer :public CCharacter
{
public:
	CPlayer(OBJTYPE Priority = OBJTYPE_PLAYER);	//コンストラクタ
	~CPlayer();									//デストラクタ

	static void Load();		//ロード処理
	static void Unload();	//アンロード処理

	static CPlayer *Create(const TYPE &type);	//生成処理

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	TYPE GetType(void) { return m_type; }	//種類の取得

private:
	static LPD3DXMESH m_apMesh[TYPE_MAX];		//メッシュ情報のポインタ
	static LPD3DXBUFFER m_apBuffMat[TYPE_MAX];	//マテリアル情報のポインタ
	static DWORD m_NumMat[TYPE_MAX];			//マテリアル情報の数

	TYPE m_type;	//プレイヤータイプ
};

#endif