//=============================================================================
//
// キーボード処理 [keyboard.h]
// Author : 
//
//=============================================================================
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "input.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define NUM_KEY_MAX (256)//キーボードの最大数

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CInputKeyboard :public CInput
{
public:
	CInputKeyboard();	//コンストラクタ
	~CInputKeyboard();	//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//初期化処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理

	bool GetKeyPress(int nKey);
	bool GetKeyTrigger(int nKey);
	bool GetKeyRelease(int nKey);

private:
	BYTE m_akeyState[NUM_KEY_MAX];			//キーボードの入力情報ワーク
	BYTE m_akeyStateTrigger[NUM_KEY_MAX];
	BYTE m_akeyStateRelease[NUM_KEY_MAX];
};

#endif