//=============================================================================
//
// モデル処理 [model.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define EDGE_NUM (4)	//辺の数

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CModel:public CScene
{
public:
	//頂点位置用の列挙型
	typedef enum
	{
		VER_A=0,	//左奥
		VER_B,		//右奥
		VER_C,		//右下
		VER_D,		//左下
		VER_MAX
	}VERTEX;

	//方向ベクトル用の構造体
	typedef struct
	{
		D3DXVECTOR3 a;	//左上
		D3DXVECTOR3 b;	//右上
		D3DXVECTOR3 c;	//右下
		D3DXVECTOR3 d;	//左下
		D3DXVECTOR3 ab;	//ABベクトル
		D3DXVECTOR3 bc;	//BC方向ベクトル
		D3DXVECTOR3 cd;	//CD方向ベクトル
		D3DXVECTOR3 da;	//DA方向ベクトル
		D3DXVECTOR3 ad;	//AD方向ベクトル
		D3DXVECTOR3 dc;	//DC方向ベクトル
		D3DXVECTOR3 cb;	//CB方向ベクトル
		D3DXVECTOR3 ba;	//BA方向ベクトル
		D3DXVECTOR3 x1;	//方向ベクトルの始点
		D3DXVECTOR3 x2;	//方向ベクトルの終点
		D3DXVECTOR3 direction;	//方向ベクトル
	}VECT;

	// メッシュ情報の構造体
	typedef struct
	{
		D3DXVECTOR3 pos, nor;
		FLOAT tu, tv;
	}MESHVERTEX;

	CModel(OBJTYPE nPriority);
	~CModel();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	D3DXVECTOR3 VertexRotate(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, const VERTEX &vertexType);

	void BindModel(const LPD3DXMESH &pMesh, const LPD3DXBUFFER &pBuffMat, const DWORD &nNumMat, const int &nldxModelParent = 0)
	{ m_pMesh = pMesh; m_pBuffMat = pBuffMat; m_nNumMat = nNumMat; m_nldxModelParent = nldxModelParent; }						//モデルのテクスチャ設定
	void BindTexture(const LPDIRECT3DTEXTURE9 &Texture, const int &nCount) { m_pTexture[nCount] = Texture; }					//テクスチャの設定
	void SetPos(const D3DXVECTOR3 &pos) { m_pos = pos; }																		//座標の設定
	void SetPosOld(const D3DXVECTOR3 &posOld) { m_posOld = posOld; }															//過去の座標の設定
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }																	//大きさの設定
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = rot; }																		//角度の設定
	void SetVectOld(const D3DXVECTOR3 &vectOld) { m_VectOld = vectOld; }														//過去のベクトルの設定
	void SetMove(const D3DXVECTOR3 &move) { m_pos += move; }																	//移動量の設定
	void SetWorldMatrix(const D3DXMATRIX &mtxWorld) { m_mtxWorld = mtxWorld; }													//ワールド座標の設定

	D3DXVECTOR3 GetPos(void) { return m_pos; }			//現在の座標情報
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }	//古い座標情報
 	D3DXVECTOR3 GetSize(void) { return m_size; }		//大きさの取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }			//角度情報
	D3DXVECTOR3 GetVectOld(void) { return m_VectOld; }	//角度情報
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }	//ワールド座標の取得

private:
	LPD3DXMESH m_pMesh;							//メッシュ情報のポインタ
	MESHVERTEX *m_MeshVertices;					//メッシュの情報
	WORD *m_pIndices;							//インデックス数
	DWORD m_dwNumFaces;							//メッシュの面の数
	WORD *m_pEdges;								//エッジの数
	LPD3DXBUFFER m_pBuffMat;					//マテリアル情報のポインタ
	DWORD m_nNumMat;							//マテリアル情報の数
	D3DXMATRIX m_mtxWorld;						//行列計算用
	int m_nldxModelParent;						//親モデルのインデックス
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//テクスチャの情報

	D3DXVECTOR3 m_pos;		//座標
	D3DXVECTOR3 m_posOld;	//古い座標
	D3DXVECTOR3 m_size;		//大きさ
	D3DXVECTOR3 m_rot;		//角度
	D3DXVECTOR3 m_VectOld;	//過去のベクトル
};

#endif