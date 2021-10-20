//=============================================================================
//
// オブジェクト処理 [scene.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define MAX_OBJECT (256)			//オブジェクトの最大数
#define MAX_VERTEX_SQUARE (4)		//矩形の頂点数
#define VERTEX_COLLISION_NUM (2)	//当たり判定時の頂点数

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CScene
{
public:
	//オブジェクトタイプの列挙型
	enum OBJTYPE
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_BULLET,						//バレット
		OBJTYPE_PLAYER,						//プレイヤー
		OBJTYPE_WALL,						//壁
		OBJTYPE_BLOCK,						//障害物
		OBJTYPE_FLOOR,						//床
		OBJTYPE_COLLISION,					//当たり判定
		OBJTYPE_EFFECT_EXPLOSION,			//爆発エフェクト
		OBJTYPE_EFFECT_EXPLOSION_BULLET,	//弾の爆発エフェクト
		OBJTYPE_UI_START,					//スタートUI
		OBJTYPE_UI_WIN_PLAYER_1,			//プレイヤー１勝利UI
		OBJTYPE_UI_WIN_PLAYER_2,			//プレイヤー２勝利UI
		OBJTYPE_UI_DRAW,					//引き分けUI
		OBJTYPE_UI_TITLE,					//タイトルUI
		OBJTYPE_FADE,						//フェード
		OBJTYPE_MAX
	};

	CScene(OBJTYPE nPriority = OBJTYPE_NONE);	//コンストラクタ
	virtual ~CScene();							//デストラクタ

	virtual HRESULT Init(void) = 0;	//初期化処理
	virtual void Uninit(void) = 0;	//終了処理
	virtual void Update(void) = 0;	//更新処理
	virtual void Draw(void) = 0;	//描画処理

	static void ReleaseAll(void);							//全てのメモリの開放処理
	static void DesignationReleaseAll(OBJTYPE type);		//選択したもの以外の解放処理
	static void UpdateAll(void);							//全ての更新処理
	static void DesignationUpdateAll(const OBJTYPE* type);	//選択したOBJTYPEのみの更新処理
	static void DrawAll(void);								//全ての描画処理

	void SetObjType(const OBJTYPE &objType){ m_objType = objType; }	//オブジェクトタイプの設定
	static void SetUpdateType(const OBJTYPE type, ...);				//更新するオブジェクトタイプの設定(最後の引数には絶対にNULLを入れる)

	OBJTYPE GetObjType(void) { return m_objType; }	//オブジェクトタイプの取得
	static CScene *GetScene(const int &nPriority);	//シーンの取得
	static void GetUpdateType(OBJTYPE* type);		//更新するオブジェクトタイプの取得

protected:
	void Release(void) { m_bDeath = true; }	//メモリの開放処理

private:
	OBJTYPE m_objType;								//オブジェクトの種類
	static CScene *m_pTop[OBJTYPE_MAX];				//先頭のオブジェクトへのポインタ
	static CScene *m_pCur[OBJTYPE_MAX];				//現在のオブジェクトへのポインタ
	CScene *m_pPrev;								//前のオブジェクトへのポインタ
	CScene *m_pNext;								//次のオブジェクトへのポインタ
	int m_nPriority;								//描画順番
	bool m_bDeath;									//死亡フラグ
	static int m_nCntList;							//リストのカウント
	static OBJTYPE m_UpdateTypeList[OBJTYPE_MAX];	//更新するオブジェクトタイプ
};

#endif