//=============================================================================
//
// �}�E�X���� [mouse.cpp]
// Author : 
//
//=============================================================================
#ifndef	_INPUTMOUSE_H_
#define _INPUTMOUSE_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "input.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CInputMouse : public CInput 
{
public:
	typedef struct _MSTATE {
		RECT    moveRect;     // ��ʏ�œ�����͈�
		int     x;            // X���W
		int     y;            // Y���W
		bool    lButton;      // ���{�^��
		bool    rButton;      // �E�{�^��
		bool    cButton;      // �^�񒆃{�^��
		int     moveAdd;      // �ړ���
		RECT    imgRect;      // �}�E�X�p�摜��`
		int     imgWidth;     // �}�E�X�摜��
		int     imgHeight;    // �}�E�X�摜����
	} MSTATE;

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����

	static MSTATE *GetMouse(void);
	bool GetMouseTriggerLeft(void);
	bool GetMouseTriggerRight(void);

private:
	DIMOUSESTATE2 m_dIMouseState;
	static CInputMouse::MSTATE m_MState;
};

#endif