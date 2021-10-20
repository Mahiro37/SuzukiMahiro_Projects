//=============================================================================
//
// 弾処理 [bullet.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "model.h"
#include "character.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CCollision;

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CBullet : public CModel
{
public:
	//弾の種類の列挙型
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_BULLET1,	//プレイヤー１
		TYPE_BULLET2,	//プレイヤー２
		TYPE_MAX
	}TYPE;

	CBullet(OBJTYPE Priority = OBJTYPE_BULLET);	//コンストラクタ
	~CBullet();									//デストラクタ

	static void Load();		//ロード処理
	static void Unload();	//アンロード処理

	static CBullet *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const D3DXVECTOR3 &vect, const TYPE &type, const CCharacter::TYPE &PlayerType);	//生成処理

	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	void Move(void);	//移動処理

	HRESULT HitInit(void);		//初期値の衝突処理
	HRESULT HitBullet(void);	//弾の衝突処理
	HRESULT HitWall(void);		//壁の衝突処理
	HRESULT HitBlock(void);		//障害物の衝突処理

	D3DXVECTOR3 ReflectVector(const D3DXVECTOR3 &front, const D3DXVECTOR3 &normal);	//弾の反射処理

	void GetBulletData(void);								//弾データの取得処理
	CCollision *GetCollision(void) { return m_pCollision; }	//当たり判定ポインタの取得

private:
	static LPD3DXMESH m_pMesh[TYPE_MAX];		// メッシュ情報のポインタ
	static LPD3DXBUFFER m_pBuffMat[TYPE_MAX];	// マテリアル情報のポインタ
	static DWORD m_NumMat[TYPE_MAX];			// マテリアル情報の数

	TYPE m_type;					//種類
	CCharacter::TYPE m_PlayerType;	//弾を生成したオブジェクト情報
	D3DXVECTOR3 m_vect;				//方向ベクトル
	float m_fMove;					//移動量
	int m_nLife;					//反射数
	int m_nCntLife;					//反射数のカウント
	bool m_bHit;					//初期位置で当たっているかの判定

	CCollision *m_pCollision;		//当たり判定のポインタ
};
#endif