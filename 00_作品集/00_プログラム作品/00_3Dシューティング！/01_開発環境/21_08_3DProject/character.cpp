//=============================================================================
//
// キャラクタークラス [character.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "character.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "collision.h"
#include "player.h"
#include "playerData.h"
#include "wall.h"
#include "block.h"
#include "effect_explosion_player.h"
#include "keyboard.h"
#include "bulletData.h"
#include "bullet.h"

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CCharacter::CCharacter(OBJTYPE Priority) : CModel(Priority)
{
	m_bInput = false;

	m_fPlayerMove = FLOAT_ZERO;
	m_MoveVect = ZeroVector3;
	m_fVectLength = FLOAT_ZERO;
	m_SlideVect = ZeroVector3;

	m_BulletDistance = ZeroVector3;
	m_nBulletType = CBullet::TYPE_NONE;

	m_nCntHit = 0;
	m_pCollision = nullptr;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CCharacter::~CCharacter()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CCharacter::Init(void)
{
	//モデルの初期化処理
	CModel::Init();

	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CCharacter::Uninit()
{
	if (m_pCollision != nullptr)
	{
		//当たり判定の生成
		m_pCollision->Uninit();
		m_pCollision = nullptr;
	}

	//モデルの終了処理
	CModel::Uninit();
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CCharacter::Update()
{
	//衝突後の処理
	AfterHit();

	//モデルの更新処理
	CModel::Update();
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CCharacter::Draw()
{
	//モデルの描画処理
	CModel::Draw();
}

//*****************************************************************************
//プレイヤーデータの設定処理
//*****************************************************************************
void CCharacter::InitPlayer(const TYPE &type)
{
	//〇---------------〇
	// プレイヤーの設定
	//〇---------------〇

	//プレイヤーデータの取得
	CPlayerData::CreateInfo* pPlayerData = CManager::GetPlayerData()->GetCreateInfo(type);

	if (pPlayerData != nullptr)
	{
		//移動量
		SetPlayerMove(pPlayerData->fMove);

		//方向ベクトル
		SetMoveVect(VectorCalculation(
			pPlayerData->pos,
			D3DXVECTOR3((pPlayerData->fMove * cosf(pPlayerData->rot.y)) + pPlayerData->pos.x,
				0.0f,
				(-pPlayerData->fMove * sinf(pPlayerData->rot.y)) + pPlayerData->pos.z)));

		//ベクトルの長さ
		SetVectLength(D3DXVec3Length(&GetMoveVect()));

		if (GetVectLength() > GetPlayerMove())
		{ //移動量が規定値より大きいとき
		  //正しい移動量を計算
			SetMoveVect(GetMoveVect() / GetVectLength() * GetPlayerMove());
		}

		//モデル情報の設定
		SetPos(pPlayerData->pos);
		SetSize(pPlayerData->modelSize);
		SetRot(pPlayerData->rot);

		if (m_pCollision == nullptr)
		{
			//当たり判定の生成
			m_pCollision = CCollision::Create(pPlayerData->pos, pPlayerData->collisionSize, pPlayerData->rot, CCollision::TYPE_BOX);
		}
	}

	//〇-------〇
	// 弾の設定
	//〇-------〇

	//弾の種類用変数
	CBullet::TYPE BulletType = CBullet::TYPE_NONE;

	if (pPlayerData != nullptr)
	{
		//弾の種類の代入
		BulletType = (CBullet::TYPE)pPlayerData->nBulletType;
	}

	//弾データの取得用変数
	CBulletData::CreateInfo* pBulletData = nullptr;

	//弾データの取得
	pBulletData = CManager::GetBulletData()->GetCreateInfo(BulletType);

	if (pBulletData != nullptr)
	{
		//弾の生成位置(プレイヤーの中心からの距離)
		SetBulletDistance(pBulletData->distance);

		//弾の種類
		SetBulletType((CBullet::TYPE)pBulletData->nType);
	}
}

//*****************************************************************************
//プレイヤーごとの当たり判定のポインタを返す処理
//*****************************************************************************
CCollision * CCharacter::SelectCollisionPointer(const TYPE &type)
{
	if (type != TYPE_NONE)
	{ //オブジェタイプがTYPE_NONEではないとき
		//プレイヤー情報の取得
		return CGame::GetPlayer(type)->GetCollision();
	}
	else
	{
		return nullptr;
	}
}

//*****************************************************************************
//移動処理
//*****************************************************************************
void CCharacter::Move(const TYPE &type)
{
	//キーボードとコントローラのポインタの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	//過去の座標の設定
	SetPosOld(GetPos());

	//移動量用変数の設定
	D3DXVECTOR3 move = ZeroVector3;
	SetMove(move);

	//入力状態の設定
	SetInputState(false);

	//キーボードの移動処理
	if (type == TYPE_PLAYER_1)
	{ //オブジェタイプがプレイヤー１のとき
		if (pInputKeyboard->GetKeyPress(DIK_A))
		{ //Aを押したとき
			move.x -= m_fPlayerMove;
			SetInputState(true);
		}
		if (pInputKeyboard->GetKeyPress(DIK_D))
		{ //Dを押したとき
			move.x += m_fPlayerMove;
			SetInputState(true);
		}
		if (pInputKeyboard->GetKeyPress(DIK_W))
		{ //Wを押したとき
			move.z += m_fPlayerMove;
			SetInputState(true);
		}
		if (pInputKeyboard->GetKeyPress(DIK_S))
		{ //Sを押したとき
			move.z -= m_fPlayerMove;
			SetInputState(true);
		}
	}
	else if (type == TYPE_PLAYER_2)
	{ //オブジェタイプがプレイヤー２のとき
		if (pInputKeyboard->GetKeyPress(DIK_LEFT))
		{ //右矢印を押したとき
			move.x -= m_fPlayerMove;
			SetInputState(true);
		}
		if (pInputKeyboard->GetKeyPress(DIK_RIGHT))
		{ //左矢印を押したとき
			move.x += m_fPlayerMove;
			SetInputState(true);
		}
		if (pInputKeyboard->GetKeyPress(DIK_UP))
		{ //上矢印を押したとき
			move.z += m_fPlayerMove;
			SetInputState(true);
		}
		if (pInputKeyboard->GetKeyPress(DIK_DOWN))
		{ //下矢印を押したとき
			move.z -= m_fPlayerMove;
			SetInputState(true);
		}
	}

	if (GetInputState() == true)
	{ //入力されているとき
	  //ベクトルの計算
		SetMoveVect(VectorCalculation(GetPos() - GetPosOld(), move));

		//ベクトルの長さの計算
		m_fVectLength = D3DXVec3Length(&GetMoveVect());

		if (m_fVectLength > m_fPlayerMove)
		{ //移動量が規定値より大きいとき
		  //正しい移動量を計算して代入
			SetMoveVect(GetMoveVect() / D3DXVec3Length(&GetMoveVect()) * m_fPlayerMove);
			move = GetMoveVect();
		}

		//移動量の設定
		SetMove(move);

		//なす角θを計算し、ラジアンに変換して角度を設定
		SetRot(D3DXVECTOR3(
			GetRot().x,
			D3DXToRadian(AngleOf2Vector(D3DXVECTOR3(m_fPlayerMove, 0.0f, 0.0f), GetMoveVect())),
			GetRot().z));

		if (SelectCollisionPointer(type) != NULL)
		{
			//当たり判定モデル情報の設定
			SelectCollisionPointer(type)->SetPos(GetPos());
			SelectCollisionPointer(type)->SetRot(GetRot());
		}
	}
}

//*****************************************************************************
//発射処理
//*****************************************************************************
void CCharacter::Shot(const TYPE &type)
{
	//キーボードとコントローラのポインタの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	if (type == TYPE_PLAYER_1)
	{ //オブジェタイプがプレイヤー１のとき
		if (pInputKeyboard->GetKeyTrigger(DIK_SPACE))
		{ //SPACEを押したとき
			//弾の発射
			CBullet::Create(BulletPosition(GetPos(), GetRot(), m_BulletDistance), GetRot(), GetMoveVect(), (CBullet::TYPE)m_nBulletType, type);
		}
	}
	else if (type == TYPE_PLAYER_2)
	{ //オブジェタイプがプレイヤー２のとき
		if (pInputKeyboard->GetKeyTrigger(DIK_NUMPADENTER))
		{ //テンキーのENTERを押したとき
			//弾の発射
			CBullet::Create(BulletPosition(GetPos(), GetRot(), m_BulletDistance), GetRot(), GetMoveVect(), (CBullet::TYPE)m_nBulletType, type);
		}
	}
}

//*****************************************************************************
// ベクトル計算
//*****************************************************************************
D3DXVECTOR3 CCharacter::VectorCalculation(const D3DXVECTOR3 &Va, const D3DXVECTOR3 &Vb)
{
	//ベクトルの計算
	D3DXVECTOR3 Vab = Vb - Va;

	if (Vab != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{ //ベクトルが存在するとき
	  //過去のベクトルを上書き
		SetVectOld(Vab);
	}
	else
	{ //ベクトルが存在しないとき
	  //一番最近のベクトルを代入
		Vab = GetVectOld();
	}

	return Vab;
}

//*****************************************************************************
// ２つのベクトルABのなす角度θを求める計算
//*****************************************************************************
float CCharacter::AngleOf2Vector(const D3DXVECTOR3 &VectorA, const D3DXVECTOR3 &VectorB)
{
	//ベクトルAとBの長さを計算する
	float fLengthA = D3DXVec3Length(&VectorA);
	float fLengthB = D3DXVec3Length(&VectorB);

	//内積とベクトル長さを使ってcosθを求める
	float fCosSita = D3DXVec3Dot(&VectorA, &VectorB) / (fLengthA * fLengthB);

	//cosθからθを求める
	float fSita = (float)D3DXToDegree(acos(fCosSita));

	if (VectorB.z > 0)
	{ //ベクトルのZ座標がプラスのとき
	  //角度を×-１する
		fSita = 360.0f - fSita;
	}

	return fSita;
}

//*****************************************************************************
// 弾の生成位置の計算
//*****************************************************************************
D3DXVECTOR3 CCharacter::BulletPosition(const D3DXVECTOR3 &PlayerPos, const D3DXVECTOR3 &PlayerRot, const D3DXVECTOR3 &BulletDistance)
{
	//弾の位置用変数
	D3DXVECTOR3 BulletPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//プレイヤーが回転した時の弾の発生座標(X,Z)を求める
	BulletPos = D3DXVECTOR3(
		(BulletDistance.x * cosf(PlayerRot.y)) + PlayerPos.x,
		0.0f,
		(-BulletDistance.z * sinf(PlayerRot.y)) + PlayerPos.z);

	return BulletPos;
}

//*****************************************************************************
//衝突後の処理
//*****************************************************************************
void CCharacter::AfterHit(void)
{
	if (m_nCntHit > 0)
	{ //一度でも障害物に当たっていたとき
		//障害物に当たる前の位置を代入
		SetPos(GetPosOld());
		if (m_pCollision != nullptr)
		{
			m_pCollision->SetPos(GetPosOld());
		}

		if (m_nCntHit == 1)
		{ //カウントが１のとき
			if (GetInputState() == true)
			{ //入力されていたら
				//壁ずりベクトルを設定
				SetMove(m_SlideVect);
			}
		}
		else
		{
			//壁ずりベクトルを設定
			SetMove(ZeroVector3);
		}

		//何かにあったった数のカウントの初期化
		m_nCntHit = 0;
	}
	else
	{
		//壁ずりベクトルの初期化
		m_SlideVect = ZeroVector3;
	}
}

//*****************************************************************************
//壁の当たり判定
//*****************************************************************************
void CCharacter::HitWall(const TYPE &type)
{
	CCollision* pCollision = nullptr;		//プレイヤーの当たり判定ポインタ用

	//当たり判定のポインタを取得
	pCollision = SelectCollisionPointer(type);

	CWall *pWall = nullptr;	//壁ポインタの受け取り用

	do
	{
		pWall = dynamic_cast<CWall*>(GetScene(OBJTYPE_WALL));

		if (pWall != nullptr)
		{
			if (pCollision != nullptr && pWall->GetCollision() != nullptr)
			{
				if (pCollision->WallCollision(pWall->GetVect(), GetPos(), pCollision->GetSize(), GetRot().y) == true)
				{ //当たり判定(矩形と矩形)
				  //当たった回数をカウント
					m_nCntHit++;

					if (m_nCntHit == 1)
					{ //カウントが１のとき
						//当たった壁の壁ずりベクトルを取得
						m_SlideVect = pCollision->SlideVect(GetMoveVect(), pWall->GetVect().dc);
					}
				}
			}
		}
	} while (pWall != nullptr);
}

//*****************************************************************************
//障害物の当たり判定
//*****************************************************************************
void CCharacter::HitBlock(const TYPE &type)
{
	CCollision* pCollision = nullptr;		//プレイヤーの当たり判定ポインタ用

	//当たり判定のポインタを取得
	pCollision = SelectCollisionPointer(type);

	VECT dirVect;							//最も近い２点の方向ベクトル取得用
	memset(&dirVect, 0, sizeof(dirVect));
	CBlock *pBlock = nullptr;				//障害物ポインタの受け取り用

	do
	{
		pBlock = dynamic_cast<CBlock*>(GetScene(OBJTYPE_BLOCK));

		if (pBlock != nullptr)
		{
			//当たり判定用変数
			bool bHit = false;

			if (pCollision != nullptr)
			{
				//当たり判定(矩形と矩形)
				pCollision->BlockCollision(bHit, dirVect, pBlock->GetRot(), pBlock->GetVect(), GetPos(), pCollision->GetSize(), GetRot().y, m_SlideVect);

				if (bHit == true)
				{ //当たっているとき
					//当たった回数をカウント
					m_nCntHit++;

					if (m_nCntHit == 1 && dirVect.direction != ZeroVector3)
					{ //カウントが１のとき
						//当たった障害物の壁ずりベクトルを取得
						m_SlideVect = pCollision->SlideVect(GetMoveVect(), dirVect.direction);
					}
				}

				//最も近い２点の方向ベクトル取得用変数の初期化
				memset(&dirVect, 0, sizeof(dirVect));
			}
		}
	} while (pBlock != nullptr);
}

//*****************************************************************************
//弾の当たり判定
//*****************************************************************************
HRESULT CCharacter::HitBullet(const TYPE &type)
{
	CCollision* pCollision = nullptr;		//プレイヤーの当たり判定ポインタ用

	//当たり判定のポインタを取得
	pCollision = SelectCollisionPointer(type);

	CBullet *pBullet = NULL;
	do
	{
		pBullet = dynamic_cast<CBullet*>(GetScene(OBJTYPE_BULLET));

		if (pBullet != nullptr && pBullet->GetCollision() != nullptr)
		{
			D3DXVECTOR3 BulletPos = pBullet->GetCollision()->GetPos();
			D3DXVECTOR3 BulletSize = pBullet->GetCollision()->GetSize();

			if (pCollision != nullptr)
			{
				if (CCollision::RectangleCircularCollision(GetPos(), pCollision->GetSize(), GetRot().y, BulletPos, (BulletSize.x / 2)) == true)
				{ //当たり判定(矩形と円形)
					//爆発エフェクトの生成
					CEffectExplosionPlayer::Create(GetPos());

					//弾の終了処理
					pBullet->Uninit();
					return S_FALSE;
				}
			}
		}
	} while (pBullet != nullptr);

	return S_OK;
}