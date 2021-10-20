//=============================================================================
//
// 障害物処理 [block.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

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
class CBlock :public CModel
{
public:
	CBlock(OBJTYPE nPriority = OBJTYPE_BLOCK);
	~CBlock();

	static void Load();
	static void Unload();
	static CBlock *Create(const int nCreateNum);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void GetBlockData(void);								//障害物データの取得処理
	VECT GetVect(void) { return m_vect; }					//ベクトル情報の取得
	CCollision *GetCollision(void) { return m_pCollision; }	//当たり判定インスタンスの取得

private:
	static LPD3DXMESH m_pMesh;			// メッシュ情報のポインタ
	static LPD3DXBUFFER m_pBuffMat;		// マテリアル情報のポインタ
	static DWORD m_nNumMat;				// マテリアル情報の数

	int m_nCreateNum;					//生成順
	VECT m_vect;						//ベクトル情報

	CCollision *m_pCollision;			//当たり判定のポインタ
};

#endif