//=============================================================================
//
// 当たり判定の処理 [collision.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "collision.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
//静的メンバ変数宣言
//*****************************************************************************
LPD3DXMESH CCollision::m_apMesh[TYPE_MAX] = {};
LPD3DXBUFFER CCollision::m_apBuffMat[TYPE_MAX] = {};

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CCollision::CCollision(OBJTYPE nPriority) :CModel(nPriority)
{
	m_CollisionType = TYPE_NONE;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CCollision::~CCollision()
{
}

//*****************************************************************************
//ロード
//*****************************************************************************
void CCollision::Load()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ポリゴンの作成
	D3DXCreatePolygon(
		pDevice,						//デバイス情報
		10.0f,							//辺の長さ
		4,								//辺の数
		&m_apMesh[TYPE_POLYGON],		//メッシュ情報
		&m_apBuffMat[TYPE_POLYGON]);	//バッファ情報

	//箱の作成
	D3DXCreateBox(
		pDevice,					//デバイス情報
		1.0f,						//横幅
		1.0f,						//立幅
		1.0f,						//奥幅
		&m_apMesh[TYPE_BOX],		//メッシュ情報
		&m_apBuffMat[TYPE_BOX]);	//バッファ情報

	//球の作成
	D3DXCreateSphere(
		pDevice,					//デバイス情報
		1.0f,						//手前の円の半径
		10,							//スライスの数
		10,							//スタック数
		&m_apMesh[TYPE_SPHERE],		//メッシュ情報
		&m_apBuffMat[TYPE_SPHERE]);	//バッファ情報

	//円柱の作成
	D3DXCreateCylinder(
		pDevice,						//デバイス情報
		1.0f,							//手前の円の半径
		1.0f,							//奥の円の半径
		1.0f,							//円柱の長さ
		10,								//スライス(円の超点数)
		1,								//スタック(円柱の分割数)
		&m_apMesh[TYPE_CYLINDER],		//メッシュ情報
		&m_apBuffMat[TYPE_CYLINDER]);	//バッファ情報
}

//*****************************************************************************
//アンロード
//*****************************************************************************
void CCollision::Unload()
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_apMesh[nCount] != NULL)
		{
			//メッシュの破棄
			m_apMesh[nCount]->Release();
			m_apMesh[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_apBuffMat[nCount] != NULL)
		{
			//バッファの破棄
			m_apBuffMat[nCount]->Release();
			m_apBuffMat[nCount] = NULL;
		}
	}
}

//*****************************************************************************
//当たり判定の生成
//*****************************************************************************
CCollision * CCollision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, TYPE type)
{
	CCollision *pCollision = new CCollision;

	if (pCollision != NULL)
	{
		//当たり判定情報の設定
		pCollision->m_CollisionType = type;
		pCollision->SetPos(pos);
		pCollision->SetSize(size);
		pCollision->SetRot(rot);

		//当たり判定の初期化処理
		pCollision->Init();

		return pCollision;
	}

	return nullptr;
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CCollision::Init()
{
	//モデル情報の設定
	BindModel(m_apMesh[m_CollisionType], m_apBuffMat[m_CollisionType], 1);

	//モデル情報の初期化
	CModel::Init();

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CCollision::Uninit(void)
{
	CModel::Uninit();
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CCollision::Update(void)
{
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CCollision::Draw(void)
{
#ifdef _DEBUG
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//色の設定
	D3DXMATERIAL* mat = (D3DXMATERIAL*)m_apBuffMat[m_CollisionType]->GetBufferPointer();
	mat->MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mat->MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mat->MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mat->MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	//ワイヤーフレームで描画
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//描画
	CModel::Draw();

	//ワイヤーフレームをもどす
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
#endif
}

//*****************************************************************************
//矩形の当たり判定
//*****************************************************************************
bool CCollision::RectangleCollision(const D3DXVECTOR3 &pPos1, const D3DXVECTOR3 &size1, const D3DXVECTOR3 &pPos2, const D3DXVECTOR3 &size2)
{
	//〇----------------------------------〇
	// pPos1    : 当たる側の位置
	// size1    : 当たる側のサイズ
	// pPos2    : 当てられる側の位置
	// size2    : 当てられる側のサイズ
	// 戻り値   : 当たったかどうかを返す
	//〇----------------------------------〇

	bool bHit = false;

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y, size1.z / 2) + pPos1;          //ぶつかる側の最大値
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, -size1.y, -size1.z / 2) + pPos1;       //ぶつかる側の最小値
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y / 2, size2.z / 2) + pPos2;      //ぶつかられる側の最大値
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, -size2.y / 2, -size2.z / 2) + pPos2;   //ぶつかられる側の最小値

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x&&
		box1Max.z > box2Min.z&&
		box1Min.z < box2Max.z)
	{
		bHit = true;
	}

	// 当たったかどうかを返す
	return bHit;
}

//*****************************************************************************
//球の当たり判定
//*****************************************************************************
bool CCollision::SphereCollision(const D3DXVECTOR3 &pos1, const float &size1, const D3DXVECTOR3 &pos2, const float &size2)
{
	//〇-------------------------------------------------〇
	// pos1     : ぶつかる側の位置
	// size1    : ぶつかる側のサイズ
	// pos2     : ぶつかられる側の位置
	// size2    : ぶつかられる側のサイズ
	// 戻り値   : ぶつかる側が円の中に入っているかどうか
	//〇-------------------------------------------------〇

	float distance = powf(pos1.x - pos2.x, 2.0f) + powf(pos1.y - pos2.y, 2.0f) + powf(pos1.z - pos2.z, 2.0f); //位置
	float radius = powf(size1 + size2, 2.0f); //半径

	if (distance < radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//*****************************************************************************
//当たり判定(矩形と円形)
//*****************************************************************************
bool CCollision::RectangleCircularCollision(const D3DXVECTOR3 &RectanglePos, const D3DXVECTOR3 &RectangleSize, const float &RectangleRadian, const D3DXVECTOR3 &CircularPos, const float &CircularRadius)
{
	//矩形の角度を０にした時の円形の座標を求める
	D3DXVECTOR3 NewCircularPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	NewCircularPos.x = (float)(cos(RectangleRadian) * (CircularPos.x - RectanglePos.x) -
		sin(RectangleRadian) * (CircularPos.z - RectanglePos.z) + RectanglePos.x);
	NewCircularPos.z = (float)(sin(RectangleRadian) * (CircularPos.x - RectanglePos.x) +
		cos(RectangleRadian) * (CircularPos.z - RectanglePos.z) + RectanglePos.z);

	if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2) - CircularRadius) ||
		NewCircularPos.x >(RectanglePos.x + (RectangleSize.x / 2) + CircularRadius) ||
		NewCircularPos.z < (RectanglePos.z - (RectangleSize.z / 2) - CircularRadius) ||
		NewCircularPos.z >(RectanglePos.z + (RectangleSize.z / 2) + CircularRadius))
	{ //「矩形の外枠 + 円の半径」の範囲に入っていないとき
		return false;
	}
	if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2)) &&
		NewCircularPos.z < (RectanglePos.z - (RectangleSize.z / 2)) &&
		!(pow((RectanglePos.x - (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.z - (RectangleSize.z / 2)) - NewCircularPos.z, 2)
			< pow(CircularRadius, 2)))
	{ //矩形の左上の判定
		return false;
	}
	if (NewCircularPos.x > (RectanglePos.x + (RectangleSize.x / 2)) &&
		NewCircularPos.z < (RectanglePos.z - (RectangleSize.z / 2)) &&
		!(pow((RectanglePos.x + (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.z - (RectangleSize.z / 2)) - NewCircularPos.z, 2)
			< pow(CircularRadius, 2)))
	{ //矩形の右上の判定
		return false;
	}
	if (NewCircularPos.x < (RectanglePos.x - (RectangleSize.x / 2)) &&
		NewCircularPos.z >(RectanglePos.z + (RectangleSize.z / 2)) &&
		!(pow((RectanglePos.x - (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.z + (RectangleSize.z / 2)) - NewCircularPos.z, 2)
			< pow(CircularRadius, 2)))
	{ //矩形の左下の判定
		return false;
	}
	if (NewCircularPos.x > (RectanglePos.x + (RectangleSize.x / 2)) &&
		NewCircularPos.z > (RectanglePos.z + (RectangleSize.z / 2)) &&
		!(pow((RectanglePos.x + (RectangleSize.x / 2)) - NewCircularPos.x, 2)
			+ pow((RectanglePos.z + (RectangleSize.z / 2)) - NewCircularPos.z, 2)
			< pow(CircularRadius, 2)))
	{ //矩形の右下の判定
		return false;
	}

	return true;
}

//*****************************************************************************
//壁専用の当たり判定(矩形と矩形)
//*****************************************************************************
bool CCollision::WallCollision(const VECT &WallVect, const D3DXVECTOR3 &PlayerPos, const D3DXVECTOR3 &PlayerSize, const float &fPlayerRot)
{
	//４頂点の座標用変数
	D3DXVECTOR3 ver[MAX_VERTEX_SQUARE];
	memset(&ver, 0, sizeof(ver));

	//プレイヤーの2頂点の座標(X,Z)を求める
	ver[0] = D3DXVECTOR3(
		((PlayerSize.x / 2) * cosf(fPlayerRot)) + ((PlayerSize.z / 2) * sinf(fPlayerRot)) + PlayerPos.x,
		0.0f,
		(-(PlayerSize.x / 2) * sinf(fPlayerRot)) + ((PlayerSize.z / 2) * cosf(fPlayerRot)) + PlayerPos.z);
	ver[1] = D3DXVECTOR3(
		((PlayerSize.x / 2) * cosf(fPlayerRot)) + (-(PlayerSize.z / 2) * sinf(fPlayerRot)) + PlayerPos.x,
		0.0f,
		(-(PlayerSize.x / 2) * sinf(fPlayerRot)) + (-(PlayerSize.z / 2) * cosf(fPlayerRot)) + PlayerPos.z);

	//D地点から各頂点(P地点)へのベクトル用変数(DPベクトル)
	D3DXVECTOR3 Vdp[VERTEX_COLLISION_NUM];
	memset(&Vdp, 0, sizeof(Vdp));

	for (int nCount = 0; nCount < VERTEX_COLLISION_NUM; nCount++)
	{
		//DPベクトルを求める
		Vdp[nCount] = ver[nCount] - WallVect.d;
	}

	//DCベクトルとDPベクトルの外積取得用変数
	D3DXVECTOR3 vCross[VERTEX_COLLISION_NUM];
	memset(&vCross, 0, sizeof(vCross));

	for (int nCount = 0; nCount < VERTEX_COLLISION_NUM; nCount++)
	{
		//DCベクトルとDPベクトルの外積を求める
		D3DXVec3Cross(&vCross[nCount], &WallVect.dc, &Vdp[nCount]);
	}

	for (int nCount = 0; nCount < VERTEX_COLLISION_NUM; nCount++)
	{
		//外積が正ならば右側、負ならば左側、0なら直線上
		if (vCross[nCount].y <= 0)
		{ //外積が０以下のとき
			return true;
		}
	}

	return false;
}

//*****************************************************************************
//障害物専用の当たり判定(矩形と矩形)
//*****************************************************************************
void CCollision::BlockCollision(bool &pbHit, VECT &dirVect, const D3DXVECTOR3 &BlockRot, const VECT &BlockVect, const D3DXVECTOR3 &PlayerPos, const D3DXVECTOR3 &PlayerSize, const float &fPlayerRot, const D3DXVECTOR3 &SlideVect)
{
	//４頂点の座標用変数
	D3DXVECTOR3 ver[VERTEX_COLLISION_NUM] = {};
	memset(&ver, 0, sizeof(ver));

	//プレイヤーの2頂点の座標(X,Z)を求める
	ver[0] = D3DXVECTOR3(
		((PlayerSize.x / 2) * cosf(fPlayerRot)) + ((PlayerSize.z / 2) * sinf(fPlayerRot)) + PlayerPos.x,
		0.0f,
		(-(PlayerSize.x / 2) * sinf(fPlayerRot)) + ((PlayerSize.z / 2) * cosf(fPlayerRot)) + PlayerPos.z);
	ver[1] = D3DXVECTOR3(
		((PlayerSize.x / 2) * cosf(fPlayerRot)) + (-(PlayerSize.z / 2) * sinf(fPlayerRot)) + PlayerPos.x,
		0.0f,
		(-(PlayerSize.x / 2) * sinf(fPlayerRot)) + (-(PlayerSize.z / 2) * cosf(fPlayerRot)) + PlayerPos.z);

	//弾と頂点との距離用
	CCollision::DISTANCE DistanceData[VER_MAX];
	memset(&DistanceData, 0, sizeof(DistanceData));

	//各頂点の位置を代入
	DistanceData[VER_A].pos = BlockVect.a;
	DistanceData[VER_B].pos = BlockVect.b;
	DistanceData[VER_C].pos = BlockVect.c;
	DistanceData[VER_D].pos = BlockVect.d;

	//各頂点から弾の中心までの距離を計算する
	DistanceData[VER_A].length = D3DXVec3Length(&(PlayerPos - BlockVect.a));
	DistanceData[VER_B].length = D3DXVec3Length(&(PlayerPos - BlockVect.b));
	DistanceData[VER_C].length = D3DXVec3Length(&(PlayerPos - BlockVect.c));
	DistanceData[VER_D].length = D3DXVec3Length(&(PlayerPos - BlockVect.d));

	//昇順の設定(仮)
	DistanceData[VER_A].rank = 1;
	DistanceData[VER_B].rank = 2;
	DistanceData[VER_C].rank = 3;
	DistanceData[VER_D].rank = 4;

	//プレイヤーの２頂点を繋いだベクトルの計算
	D3DXVECTOR3 PlayerVerVect = ZeroVector3;
	PlayerVerVect.x = roundf(ver[1].x) - roundf(ver[0].x);
	PlayerVerVect.y = roundf(ver[1].y) - roundf(ver[0].y);
	PlayerVerVect.z = roundf(ver[1].z) - roundf(ver[0].z);

	//プレイヤーの２頂点のうちの１頂点と障害物の１頂点を繋いだベクトルの代入用
	D3DXVECTOR3 PlayerBlockVect[MAX_VERTEX_SQUARE];
	memset(&PlayerBlockVect, 0, sizeof(PlayerBlockVect));

	for (int nCount = 0; nCount < MAX_VERTEX_SQUARE; nCount++)
	{
		//プレイヤーの２頂点のうちの１頂点と障害物の１頂点を繋いだベクトルの計算
		PlayerBlockVect[nCount] = DistanceData[nCount].pos - ver[0];

		float a = D3DXVec3Dot(&PlayerVerVect, &PlayerBlockVect[nCount]);

		//プレイヤーの２頂点を繋いだベクトルの長さを計算
		float fPlayerVerVectLength = D3DXVec3Length(&PlayerVerVect);

		//プレイヤーの２頂点のうちの１頂点と障害物の１頂点を繋いだベクトルの長さの計算
		float fPlayerBlockVectLength = D3DXVec3Length(&PlayerBlockVect[nCount]);

		if (a <= fPlayerVerVectLength * fPlayerBlockVectLength + 1.5f && a >= fPlayerVerVectLength * fPlayerBlockVectLength - 1.5f)
		{ //２つのベクトルの内積が０のとき
			if (fPlayerVerVectLength >= fPlayerBlockVectLength && SlideVect == ZeroVector3)
			{ //プレイヤーの２頂点を繋いだベクトルの長さより、プレイヤーの２頂点のうちの１頂点と障害物の１頂点を繋いだベクトルの長さのほうが短いとき				
				pbHit = true;
				return;
			}
		}
	}

	//一番近い２頂点の方向ベクトルを算出
	DirectionVect(BlockRot, ZeroVector3, DistanceData, dirVect);

	//X地点(方向ベクトルの始点)から各頂点(P地点)へのベクトル用変数(XPベクトル)
	D3DXVECTOR3 Vxp[MAX_VERTEX_SQUARE];
	memset(&Vxp, 0, sizeof(Vxp));

	//方向ベクトルとXPベクトルの外積取得用変数
	D3DXVECTOR3 vCross[MAX_VERTEX_SQUARE];
	memset(&vCross, 0, sizeof(vCross));

	//方向ベクトル格納用
	D3DXVECTOR3 DirVec[MAX_VERTEX_SQUARE];
	memset(&DirVec, 0, sizeof(DirVec));

	for (int nCount = 0; nCount < VERTEX_COLLISION_NUM; nCount++)
	{
		//XPベクトルを求める
		Vxp[0] = ver[nCount] - BlockVect.a;
		Vxp[1] = ver[nCount] - BlockVect.d;
		Vxp[2] = ver[nCount] - BlockVect.c;
		Vxp[3] = ver[nCount] - BlockVect.b;

		//方向ベクトルの代入
		DirVec[0] = BlockVect.ad;
		DirVec[1] = BlockVect.dc;
		DirVec[2] = BlockVect.cb;
		DirVec[3] = BlockVect.ba;

		int nCntHit = 0;	//４辺それぞれの外積が０より小さいときの回数カウント用

		for (int nCnt = 0; nCnt < MAX_VERTEX_SQUARE; nCnt++)
		{
			//方向ベクトルとXPベクトルの外積を求める
			D3DXVec3Cross(&vCross[nCnt], &DirVec[nCnt], &Vxp[nCnt]);

			//外積が正ならば右側、負ならば左側、0なら直線上
			if (vCross[nCnt].y <= 0)
			{ //外積が０より小さいとき
				//カウントを進める
				nCntHit++;
			}
		}

		if (nCntHit >= MAX_VERTEX_SQUARE)
		{ //外積が０より小さいときがMAX_VERTEX_SQUARE以上だったとき
			pbHit = true;
			return;
		}
	}
}

//*****************************************************************************
// プレイヤーの壁ずりベクトル計算
//*****************************************************************************
D3DXVECTOR3 CCollision::SlideVect(const D3DXVECTOR3 &PlayerMove, const D3DXVECTOR3 &WallVect)
{
	//法線ベクトルの計算
	D3DXVECTOR3 vCross = ZeroVector3;
	D3DXVECTOR3 vect = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Cross(&vCross, &vect, &WallVect);

	//法線ベクトルを正規化
	D3DXVECTOR3 NormalizedNormalVect = ZeroVector3;
	D3DXVec3Normalize(&NormalizedNormalVect, &vCross);

	//壁ずりベクトルを返す
	return PlayerMove - (D3DXVec3Dot(&PlayerMove, &NormalizedNormalVect)) * NormalizedNormalVect;
}

//*****************************************************************************
// 反射ベクトル計算
//*****************************************************************************
D3DXVECTOR3 CCollision::ReflectionVect(const D3DXVECTOR3 &MoveVect, const D3DXVECTOR3 &DirectionVect, const D3DXVECTOR3 &rot)
{
	//法線ベクトルの計算
	D3DXVECTOR3 vCross = ZeroVector3;
	D3DXVECTOR3 vect = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Cross(&vCross, &vect, &DirectionVect);

	//法線ベクトルを正規化
	D3DXVECTOR3 NormalizedNormalVect = ZeroVector3;
	D3DXVec3Normalize(&NormalizedNormalVect, &vCross);

	//反射ベクトルを返す
	return MoveVect - 2 * (D3DXVec3Dot(&MoveVect, &NormalizedNormalVect)) * NormalizedNormalVect;
}

//*****************************************************************************
// ４頂点ポリゴンの方向ベクトル計算
//*****************************************************************************
void CCollision::DirectionVect(const D3DXVECTOR3 &rot, D3DXVECTOR3 &pVect, DISTANCE* distanceData, VECT &dirVect)
{
	DISTANCE Distance[VER_MAX];
	memset(Distance, 0, sizeof(Distance));

	for (int nCount = 0; nCount < VER_MAX; nCount++)
	{
		Distance[nCount] = distanceData[nCount];
	}

	//距離を昇順にする(２回同じ処理をする)
	for (int nCnt = 0; nCnt < VER_MAX; nCnt++)
	{
		for (int nCount = 0; nCount < VER_MAX; nCount++)
		{
			if (Distance[nCnt].length > Distance[nCount].length)
			{
				if (Distance[nCnt].rank < Distance[nCount].rank)
				{
					int nKeep = Distance[nCnt].rank;
					Distance[nCnt].rank = Distance[nCount].rank;
					Distance[nCount].rank = nKeep;
				}
			}
		}
	}
	for (int nCnt = 0; nCnt < VER_MAX; nCnt++)
	{
		for (int nCount = 0; nCount < VER_MAX; nCount++)
		{
			if (Distance[nCnt].length > Distance[nCount].length)
			{
				if (Distance[nCnt].rank < Distance[nCount].rank)
				{
					int nKeep = Distance[nCnt].rank;
					Distance[nCnt].rank = Distance[nCount].rank;
					Distance[nCount].rank = nKeep;
				}
			}
		}
	}

	//各順位ごとの位置代入用変数
	D3DXVECTOR3 Pos1 = D3DXVECTOR3(0.0f, 0.0f, 0.0);
	D3DXVECTOR3	Pos2 = D3DXVECTOR3(0.0f, 0.0f, 0.0);
	D3DXVECTOR3	Pos3 = D3DXVECTOR3(0.0f, 0.0f, 0.0);

	//各順位ごとの距離代入用変数
	float fLength1 = 0.0f;
	float fLength2 = 0.0f;
	float fLength3 = 0.0f;

	//各順位ごとの配列番号取得用変数
	int nType1 = 0;
	int nType2 = 0;
	int nType3 = 0;

	for (int nCount = 0; nCount < VER_MAX; nCount++)
	{
		if (Distance[nCount].rank == 1)
		{
			Pos1 = Distance[nCount].pos;
			fLength1 = Distance[nCount].length;
			nType1 = nCount;
		}
		else if (Distance[nCount].rank == 2)
		{
			Pos2 = Distance[nCount].pos;
			fLength2 = Distance[nCount].length;
			nType2 = nCount;
		}
		else if (Distance[nCount].rank == 3)
		{
			Pos3 = Distance[nCount].pos;
			fLength3 = Distance[nCount].length;
			nType3 = nCount;
		}
	}

	if (fLength2 == fLength3)
	{
		dirVect.direction = ZeroVector3;
		dirVect.x1 = Pos1;
		dirVect.x2 = ZeroVector3;
	}
	else if (nType1 == VER_A && nType2 == VER_D)
	{
		dirVect.direction = Pos2 - Pos1;
		dirVect.x1 = Pos1;
		dirVect.x2 = Pos2;
	}
	else if (nType1 == VER_D && nType2 == VER_A)
	{
		dirVect.direction = Pos1 - Pos2;
		dirVect.x1 = Pos2;
		dirVect.x2 = Pos1;
	}
	else if (nType1 > nType2)
	{
		dirVect.direction = Pos2 - Pos1;
		dirVect.x1 = Pos1;
		dirVect.x2 = Pos2;
	}
	else if (nType1 < nType2)
	{
		dirVect.direction = Pos1 - Pos2;
		dirVect.x1 = Pos2;
		dirVect.x2 = Pos1;
	}

	//反射ベクトルの計算
	pVect = ReflectionVect(pVect, dirVect.direction, rot);
}