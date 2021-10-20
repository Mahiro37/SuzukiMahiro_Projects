//=============================================================================
//
// 当たり判定の処理 [collision.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "model.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CCollision :public CModel
{
public:
	//当たり判定タイプの列挙型
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_POLYGON,	//ポリゴン
		TYPE_BOX,		//箱
		TYPE_SPHERE,	//球
		TYPE_CYLINDER,	//円柱
		TYPE_MAX
	};

	//弾と頂点との距離に使う構造体
	struct DISTANCE
	{
		D3DXVECTOR3 pos;	//位置
		float length;		//距離
		int rank;			//順位
	};

	CCollision(OBJTYPE nPriority = OBJTYPE_COLLISION);	//コンストラクタ
	~CCollision();										//デストラクタ

	static void Load();		//ロード処理
	static void Unload();	//アンロード処理

	static CCollision *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, TYPE type);	//生成処理

	HRESULT Init();		//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

	static bool RectangleCollision(const D3DXVECTOR3 &pPos1, const D3DXVECTOR3 &size1, const D3DXVECTOR3 &pPos2, const D3DXVECTOR3 &size2);
	static bool SphereCollision(const D3DXVECTOR3 &pos1, const float &size1, const D3DXVECTOR3 &pos2, const float &size2);
	static bool RectangleCircularCollision(const D3DXVECTOR3 &RectanglePos, const D3DXVECTOR3 &RectangleSize, const float &RectangleRadian, const D3DXVECTOR3 &CircularPos, const float &CircularRadius);
	bool WallCollision(const VECT &WallVect, const D3DXVECTOR3 &PlayerPos, const D3DXVECTOR3 &PlayerSize, const float &fPlayerRot);
	void BlockCollision(bool &pbHit, VECT &dirVect, const D3DXVECTOR3 &BlockRot, const VECT &BlockVect, const D3DXVECTOR3 &PlayerPos, const D3DXVECTOR3 &PlayerSize, const float &PlayerRot, const D3DXVECTOR3 &SlideVect);
	D3DXVECTOR3 SlideVect(const D3DXVECTOR3 &PlayerMove, const D3DXVECTOR3 &WallVect);
	D3DXVECTOR3 ReflectionVect(const D3DXVECTOR3 &MoveVect, const D3DXVECTOR3 &DirectionVect, const D3DXVECTOR3 &rot);
	void DirectionVect(const D3DXVECTOR3 &rot, D3DXVECTOR3 &pVect, DISTANCE* distanceData, VECT &dirVect);

private:
	static LPD3DXMESH m_apMesh[TYPE_MAX];		//メッシュ情報のポインタ
	static LPD3DXBUFFER m_apBuffMat[TYPE_MAX];	//マテリアル情報のポインタ
	TYPE m_CollisionType;						//当たり判定のタイプ
};
#endif