//=============================================================================
//
// レンダリング処理 [renderer.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CRenderer
{
public:

	CRenderer();	//コンストラクタ
	~CRenderer();	//デストラクタ

	HRESULT Init(HWND hWnd, bool bWindow);	//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	void SetUpdateStop(const bool bUpdateStop) { m_bUpdateStop = bUpdateStop; }	//更新処理の切り替え処理

#ifdef _DEBUG
	void SetNumFPS(const int &nCountFPS) { m_nCountFPS = nCountFPS; }
#endif

	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	//デバイスの取得

private:
	void DrawFPS(void);	// FPS表示

	LPDIRECT3D9				m_pD3D = NULL;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)

	bool m_bUpdateStop;								//更新処理の切り替え

#ifdef _DEBUG
	LPD3DXFONT				m_pFont = NULL;			// フォントへのポインタ
	int						m_nCountFPS;			// FPSカウンタ
#endif
};
#endif
