//=============================================================================
//
// �W���C�X�e�B�b�N���� [joystick.h]
// Author : 
//
//=============================================================================
#ifndef _INPUT_JOYSTICK_H_
#define _INPUT_JOYSTICK_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "input.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define JS_X 0
#define JS_Y 1
#define JS_A 2
#define JS_B 3
#define	NUM_JS_MAX (256)

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CInputJoystick : public CInput
{
public:
	//�{�^���̎�ނ̗񋓌^
	typedef enum
	{
		BUTTON_X = 0,	//X
		BUTTON_Y,		//Y
		BUTTON_A,		//A
		BUTTON_B,		//B
		BUTTON_L1,		//LB
		BUTTON_R1,		//RB
		BUTTON_L2,		//LT
		BUTTON_R2,		//RT
		BUTTON_L3,		//L��������
		BUTTON_R3,		//R��������
		BUTTON_BACK,	//BACK
		BUTTON_START,	//START
		BUTTON_M,
		MAX_BUTTON
	}BUTTON;

	CInputJoystick();	//�R���X�g���N�^
	~CInputJoystick();	//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����

	bool GetJoystickPress(int nKey);
	bool GetJoystickTrigger(int nKey);
	bool GetJoystickRelease(int nKey);

	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);
	static LPDIRECTINPUTDEVICE8 GetDevice(void) { return m_pJDevice; }

private:
	static LPDIRECTINPUTDEVICE8 m_pJDevice;
	DIDEVCAPS	m_diDevCaps;				//Caps
	BYTE m_aJoyState[NUM_JS_MAX];			// �L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_aJoyStateTrigger[NUM_JS_MAX];	//�L�[�{�[�h�g���K�[���
	BYTE m_aJoyStateRelease[NUM_JS_MAX];	// �L�[�{�[�h�̃����[�X���
};
#endif