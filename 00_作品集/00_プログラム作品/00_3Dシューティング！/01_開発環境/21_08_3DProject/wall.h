//=============================================================================
//
// 壁処理 [wall.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "model.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CCollision;

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CWall :public CModel
{
public:
	//壁の種類の列挙型
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_BACK,		//奥
		TYPE_RIGHT,		//右
		TYPE_FRONT,		//手前
		TYPE_LEFT,		//左
		TYPE_MAX
	}TYPE;

	CWall(OBJTYPE nPriority = OBJTYPE_WALL);	//コンストラクタ
	~CWall();									//デストラクタ

	static void Load();		//ロード処理
	static void Unload();	//アンロード処理

	static CWall *Create(const int &nCreateNum);	//生成処理

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	void GetWallData(void);									//壁データの取得処理
	TYPE GetType(void) { return m_type; }					//種類の取得
	VECT GetVect(void) { return m_vect; }					//ベクトル情報の取得
	CCollision *GetCollision(void) { return m_pCollision; }	//当たり判定インスタンスの取得

private:
	static LPD3DXMESH m_pMesh;			// メッシュ情報のポインタ
	static LPD3DXBUFFER m_pBuffMat;		// マテリアル情報のポインタ
	static DWORD m_nNumMat;				// マテリアル情報の数

	TYPE m_type;						//種類
	int m_nCreateNum;					//生成順
	VECT m_vect;						//ベクトル情報

	CCollision *m_pCollision;			//当たり判定のポインタ
};

#endif