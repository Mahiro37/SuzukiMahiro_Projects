//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "title.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "sound.h"
#include "mode.h"
#include "scene.h"
#include "ui_title.h"
#include "fade.h"

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CTitle::CTitle()
{
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CTitle::~CTitle()
{
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CTitle::Init(void)
{
	//�^�C�g���e�N�X�`���̐���
	CUiTitle::Create(SCREEN_CENTER, SCREEN_SIZE);

	//�T�E���h�̐���
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CTitle::Uninit(void)
{
	//�T�E���h�̏I��
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_TITLE);

	//�w�肵���I�u�W�F�N�g�ȊO�̃������̊J������
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CTitle::Update(void)
{
	//�t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	if (pFade != NULL)
	{
		if (pFade->GetFadeStatus() == CFade::FADE_NONE)
		{
			//Enter�L�[ �܂��� B�{�^�����������Ƃ�
			if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_SPACE) || CManager::GetInputKeyboard()->GetKeyTrigger(DIK_NUMPADENTER) || CManager::GetInputJoystick()->GetJoystickTrigger(CInputJoystick::BUTTON_B))
			{
				//�t�F�[�h�̐���
				CManager::CreateFade(CManager::MODE_GAME);
			}
		}
	}
}