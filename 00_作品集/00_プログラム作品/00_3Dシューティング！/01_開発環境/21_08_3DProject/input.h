//=============================================================================
//
// ���͏��� [input.h]
// Author : 
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CInput
{
public:
	CInput();			//�R���X�g���N�^
	virtual ~CInput();	//�f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance,HWND hWnd);	//����������
	virtual void Uninit(void);								//�I������
	virtual void Update(void) = 0;							//�X�V����

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pInputDevice;

};

#endif // !_INPUT_H_
