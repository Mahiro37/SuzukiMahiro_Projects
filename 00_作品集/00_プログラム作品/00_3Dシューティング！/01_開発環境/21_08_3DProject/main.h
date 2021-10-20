//=============================================================================
//
// メイン処理 [main.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
#define _CRT_SECURE_NO_WARNINGS 
#define DIRECTINPUT_VERSION 0x0800

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"
#include <dinput.h>
#include <time.h>
#include <stdio.h>

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "strmiids.lib")

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CManager;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME "AppClass"	//ウインドウのクラス名
#define WINDOW_NAME "3D Shooting!"	//ウインドウのキャプション名

#define SCREEN_CENTER (D3DXVECTOR3(640.0f, 360.00f, 0.0f))	//ウィンドウの中心座標
#define SCREEN_SIZE (D3DXVECTOR3(1280, 720, 0.0f))			//ウィンドウサイズ

#define PRIORITY		(10)
#define NUM_VERTEX		(4)
#define NUM_POLYGON		(2)

#define MAX_TEXTURE		(256)
#define MAX_POLYGON		(1024)
#define MAX_NUMBER		(4)

#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//初期化用マクロ変数
#define ZeroVector3 (D3DXVECTOR3(0.0f, 0.0f, 0.0f))		//D3DXVECTOR3の初期化
#define ZeroColor (D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))	//D3DXCOLORの初期化
#define FLOAT_ZERO (0.0f)								//floatの0.0f
#define FLOAT_ONE (1.0f)								//floatの1.0f

//*****************************************************************************
// 構造体定義
//*****************************************************************************
struct VERTEX_2D
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標変換用係数(1.0fで固定)
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
};

struct VERTEX_3D
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

//*****************************************************************************
//プロトタイプ宣言
//*****************************************************************************
CManager *GetManager(void);

#endif