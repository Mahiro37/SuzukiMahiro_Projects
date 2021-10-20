//=============================================================================
//
// 入力処理 [input.h]
// Author : 
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CInput
{
public:
	CInput();			//コンストラクタ
	virtual ~CInput();	//デストラクタ

	virtual HRESULT Init(HINSTANCE hInstance,HWND hWnd);	//初期化処理
	virtual void Uninit(void);								//終了処理
	virtual void Update(void) = 0;							//更新処理

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pInputDevice;

};

#endif // !_INPUT_H_
