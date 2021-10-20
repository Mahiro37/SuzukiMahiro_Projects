//=============================================================================
//
// マネージャー処理 [manager.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CRenderer;
class CInputKeyboard;
class CInputMouse;
class CInputJoystick;
class CCamera;
class CLight;
class CFade;
class CPlayer;
class CModel;
class CDebugProc;
class CMode;
class CSound;
class CPlayerData;
class CBulletData;
class CWallData;
class CBlockData;
class CFloorData;

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CManager
{
public:
	//画面遷移の列挙型
	enum MODE
	{
		MODE_NONE = 0,
		MODE_TITLE,		//タイトル
		MODE_GAME,		//ゲーム
		MODE_MAX
	};

	CManager();		//コンストラクタ
	~CManager();	//デストラクタ

	HRESULT Init(HINSTANCE hInstance,HWND hWnd);	//初期化処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理
	void Draw(void);								//描画処理

	void LoadAll(void);		//テクスチャの読み込みまとめ
	void UnloadAll(void);	//テクスチャの破棄まとめ

	void SetMode(MODE mode);	//モードの設定
	
	static void CreateCamera(void);		//カメラの生成処理
	static void CreateLight(void);		//ライトの生成処理
	static void CreateFade(MODE mode);	//フェードの生成処理

	void SetNumFPS(const int &nCountFPS) { m_nCountFPS = nCountFPS; }

	static CRenderer* GetRenderer(void) { return m_pRenderer; }					//レンダラー
	static CInputKeyboard* GetInputKeyboard(void) { return m_pInputKeyboard; }	//キーボード
	static CInputMouse* GetInputMouse(void) { return m_pInputMouse; }			//マウス
	static CInputJoystick* GetInputJoystick(void) { return m_pInputJoystick; }	//ゲームパッド
	static CCamera* GetCamera(void) { return m_pCamera; }						//カメラ
	static CLight* GetLight(void) { return m_pLight; }							//ライト
	static CFade* GetFade(void) { return m_pFade; }								//フェード
	static CDebugProc* GetDebug(void) { return m_pDebugProc; }					//デバッグ
	static MODE GetMode(void) { return m_mode; }								//モード
	static CSound* GetSound(void) { return m_pSound; }							//サウンド
	static CPlayerData* GetPlayerData(void) { return m_pPlayerData; }			//プレイヤーデータ
	static CBulletData* GetBulletData(void) { return m_pBulletData; }			//弾データ
	static CWallData* GetWallData(void) { return m_pWallData; }					//壁データ
	static CBlockData* GetBlockData(void) { return m_pBlockData; }				//障害物データ
	static CFloorData* GetFloorData(void) { return m_pFloorData; }				//床データ

private:								  
	static CRenderer* m_pRenderer;				//レンダラー
	static CInputKeyboard* m_pInputKeyboard;	//キーボード
	static CInputMouse* m_pInputMouse;			//マウス
	static CInputJoystick* m_pInputJoystick;	//ゲームパッド
	static CCamera* m_pCamera;					//カメラ
	static CLight* m_pLight;					//ライト
	static CFade* m_pFade;						//フェード
	static CSound* m_pSound;					//サウンド
	static CPlayerData* m_pPlayerData;			//プレイヤーデータ
	static CBulletData* m_pBulletData;			//弾データ
	static CWallData* m_pWallData;				//壁データ
	static CBlockData* m_pBlockData;			//障害物データ
	static CFloorData* m_pFloorData;			//床データ
	static CDebugProc* m_pDebugProc;			//デバッグ
	static CMode* m_pMode;						//モードのポインタ
	static MODE m_mode;							//現在のモード
	int m_nCountFPS;							// FPSの値
};	

#endif