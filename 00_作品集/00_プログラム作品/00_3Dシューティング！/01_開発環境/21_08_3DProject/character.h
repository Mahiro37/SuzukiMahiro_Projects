//=============================================================================
//
// キャラクター処理 [character.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

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
class CCharacter : public CModel
{
public:
	//キャラクタータイプの列挙型
	enum TYPE
	{
		TYPE_NONE = -1,
		TYPE_PLAYER_1,	//プレイヤー1
		TYPE_PLAYER_2,	//プレイヤー2
		TYPE_MAX
	};

	CCharacter(OBJTYPE Priority);	//コンストラクタ
	virtual ~CCharacter();			//デストラクタ

	virtual HRESULT Init(void);	//初期化処理
	virtual void Uninit(void);	//終了処理
	virtual void Update(void);	//更新処理
	virtual void Draw(void);	//描画処理

	bool GetInputState(void) { return m_bInput; }					//入力しているかの取得
	float GetPlayerMove(void) { return m_fPlayerMove; }				//プレイヤーの移動量の取得
	D3DXVECTOR3 GetMoveVect(void) { return m_MoveVect; }			//移動ベクトルの取得
	float GetVectLength(void) { return m_fVectLength; }				//移動ベクトルの長さの取得
	D3DXVECTOR3 GetBulletDistance(void) {return m_BulletDistance;}	//弾の生成位置の設定
	int GetBulletType(void) {return m_nBulletType;}					//弾の種類の設定
	CCollision *GetCollision(void) { return m_pCollision; }			//当たり判定インスタンスの取得

protected:
	void InitPlayer(const TYPE &type);						//プレイヤーデータの設定処理
	CCollision* SelectCollisionPointer(const TYPE &type);	//プレイヤーごとの当たり判定を返す処理
	void Move(const TYPE &type);							//移動処理
	void Shot(const TYPE &type);							//発射処理

	D3DXVECTOR3 VectorCalculation(const D3DXVECTOR3 &Va, const D3DXVECTOR3 &Vb);
	float AngleOf2Vector(const D3DXVECTOR3 &VectorA, const D3DXVECTOR3 &VectorB);
	D3DXVECTOR3 BulletPosition(const D3DXVECTOR3 &PlayerPos, const D3DXVECTOR3 &PlayerRot, const D3DXVECTOR3 &BulletDistance);

	void AfterHit(void);					//衝突後の処理
	void HitWall(const TYPE &type);			//壁の当たり判定
	void HitBlock(const TYPE &type);		//障害物の当たり判定
	HRESULT HitBullet(const TYPE &type);	//弾の当たり判定

	void SetInputState(const bool &bInputState) { m_bInput = bInputState; }			//入力状態の設定
	void SetPlayerMove(const float &fPlayerMove) { m_fPlayerMove = fPlayerMove; }	//プレイヤーの移動量の設定
	void SetMoveVect(const D3DXVECTOR3 &MoveVect) { m_MoveVect = MoveVect; }		//移動ベクトルの設定
	void SetVectLength(const float &fVectLength) { m_fVectLength = fVectLength; }	//移動ベクトルの長さの設定
	void SetBulletDistance(const D3DXVECTOR3 &BulletDistance)
	{ m_BulletDistance = BulletDistance; }										//弾の生成位置の設定
	void SetBulletType(const int &nBulletType) { m_nBulletType = nBulletType; }	//弾の種類の設定

private:
	bool m_bInput;	//入力状態

	float m_fPlayerMove;		//プレイヤーの移動量
	D3DXVECTOR3 m_MoveVect;		//移動ベクトル
	float m_fVectLength;		//移動ベクトルの長さ
	D3DXVECTOR3 m_SlideVect;	//壁ずりベクトル

	D3DXVECTOR3 m_BulletDistance;	//弾の生成位置(プレイヤーの中心からの距離)
	int m_nBulletType;				//弾の種類

	int m_nCntHit = 0;			//何かに当たった数のカウント
	CCollision *m_pCollision;	//当たり判定のポインタ
};
#endif