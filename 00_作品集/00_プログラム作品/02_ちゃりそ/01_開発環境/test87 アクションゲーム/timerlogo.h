//================================================
//DirectXシューティングゲーム
//Author:鈴木聖大
//================================================
#ifndef _TIMERLOGO_H_			// 2重インクルード防止のマクロ定義
#define _TIMERLOGO_H_

#define _CRT_SECURE_NO_WARNINGS

//================================================
//インクルードファイル
//================================================
#include "main.h"

//================================================
//マクロ定義
//================================================
#define TIMERLOGO_SIZE_X (130)
#define TIMERLOGO_SIZE_Y (310)

//================================================
//プロトタイプ宣言
//================================================
void InitTimerLogo(void);
void UninitTimerLogo(void);
void DrawTimerLogo(void);

#endif