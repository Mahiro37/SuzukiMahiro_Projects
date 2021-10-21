//=============================================================================
//
// �`���[�g���A������(�Q�[�����[�h) [tutorial_game.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "tutorial_game.h"
#include "manager.h"
#include "keyboard.h"
#include "controller.h"
#include "bg.h"
#include "enemy.h"
#include "fade.h"
#include "door.h"
#include "ui.h"
#include "player.h"
#include "scene.h"
#include "bullet.h"
#include "sound.h"

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CTutorialGame::CTutorialGame()
{
	m_pDescriptionUi = NULL;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CTutorialGame::~CTutorialGame()
{
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CTutorialGame::Init(void)
{
	//BGM�̍Đ�
	CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM06);

	//�w�i�̐���
	CBg::Create();

	//�v���C���[�̐���
	CManager::CreatePlayer();

	//�Q�[�����[�hUI�̐���
	CUi::Create(D3DXVECTOR3(300.0f, 105.0f, 0.0f), D3DXVECTOR3(300.0f, 150.0f, 0.0f), CUi::UI_TYPE_TUTORIAL_GAME);

	//�t�B������UI�̐���
	CUi::Create(D3DXVECTOR3(1000.0f, 80.0f, 0.0f), D3DXVECTOR3(280.0f, 100.0f, 0.0f), CUi::UI_TYPE_FILM);

	//�{�[���̐����ʒu��UI�̐���
	CUi::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), 210.0f, 0.0f), D3DXVECTOR3(120.0f, 120.0f, 0.0f), CUi::UI_TYPE_BALL_CREATE);

	//�h�A�̐���
	CDoor::Create(D3DXVECTOR3(229.8f, 520.0f, 0.0f), DOOR_SIZE, CManager::MODE_SELECT);

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CTutorialGame::Uninit(void)
{
	//BGM�̒�~
	CManager::GetSound()->Stop(CSound::SOUND_LABEL_BGM06);

	//�S�Ẵ������̊J������
	CScene::ReleaseAllOtherThanFade();
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CTutorialGame::Update(void)
{
	if (CScene::GetUpdateStop() == false)
	{ //�V�[���̍X�V���~�܂��Ă��Ȃ��Ƃ�
		bool bBall = false;	//�G�̗L���̔���

		for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
		{
			//�I�u�W�F�N�g�̎擾
			CScene *pScene = CScene::GetScene(nCntScene);

			//�_�C�i�~�b�N�L���X�g
			CEnemy *pEnemy = dynamic_cast<CEnemy*>(pScene);

			if (pEnemy != NULL)
			{ //�G�������Ƃ�
				//�����true�ɂ���
				bBall = true;

				break;
			}
		}

		bool bPlayer = false;	//�v���C���[�̐�������

		for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
		{
			//�I�u�W�F�N�g�̎擾
			CScene *pScene = CScene::GetScene(nCntScene);

			//�_�C�i�~�b�N�L���X�g
			CPlayer *pPlayer = dynamic_cast<CPlayer*>(pScene);

			if (pPlayer != NULL)
			{ //�v���C���[�������Ă����Ƃ�
				//�����true�ɂ���
				bPlayer = true;

				break;
			}
		}

		//�L�[�{�[�h�̃|�C���^�̎擾
		CKeyboard *pKeyboard = CManager::GetKeyboard();

		if (pKeyboard->GetKeyboardTrigger(DIK_LEFT) || pKeyboard->GetKeyboardTrigger(DIK_RIGHT) || CManager::GetController()->GetJoypadTrigger(CController::BUTTON_L1) || CManager::GetController()->GetJoypadTrigger(CController::BUTTON_R1))
		{ //����� �܂��� �E��� �܂��� L1 �܂��� R1���������Ƃ�
			//�t�F�[�h�̐���
			CFade::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CManager::MODE_TUTORIAL_SCORE_ATTACK);
		}
		else if (pKeyboard->GetKeyboardTrigger(DIK_R) || CManager::GetController()->GetJoypadTrigger(CController::BUTTON_Y) || bPlayer == false)
		{ //R�L�[ �܂��� Y�{�^�����������Ƃ� �܂��� �v���C���[�����񂾂Ƃ�
			//�t�F�[�h�̐���
			CFade::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CManager::MODE_TUTORIAL_GAME);
		}
		else if (pKeyboard->GetKeyboardTrigger(DIK_B) || CManager::GetController()->GetJoypadTrigger(CController::BUTTON_L2))
		{ //B�L�[ �܂��� L2���������Ƃ�
			if (bBall == false)
			{ //�G����������Ă��Ȃ��Ƃ�
				//�G�̐���
				CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), 210.0f, 0.0f), THIRD_BALL_SIZE, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CScene::OBJTYPE_THIRD_BALL);
			}
		}
		else if (pKeyboard->GetKeyboardTrigger(DIK_N) || CManager::GetController()->GetJoypadTrigger(CController::BUTTON_R2))
		{ //N�L�[ �܂��� R2���������Ƃ�
			if (bBall == false)
			{ //�G����������Ă��Ȃ��Ƃ�
				//�G�̐���
				CEnemy::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), 210.0f, 0.0f), SECOND_BALL_SIZE, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CScene::OBJTYPE_SECOND_BALL);
			}
		}
		else if (pKeyboard->GetKeyboardTrigger(DIK_X) || CManager::GetController()->GetJoypadTrigger(CController::BUTTON_X))
		{ //X�L�[ �܂��� X�{�^�����������Ƃ�
			if (CManager::GetPlayer()->GetChargeRelease() == true)
			{ //�`���[�W���Ă��Ȃ��Ƃ�
				if (m_pDescriptionUi == NULL)
				{
					//�������UI�̐���
					m_pDescriptionUi = CUi::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CUi::UI_TYPE_DESCRIPTION);

					//SE�̒�~
					CManager::GetSound()->Stop(CSound::SOUND_LABEL_CHARGE);
					CManager::GetSound()->Stop(CSound::SOUND_LABEL_DOOR_OPEN);

					//�V�[���̍X�V���~�߂�
					CScene::UpdateStop(true);
				}
			}
		}
	}
	else
	{
		if (m_pDescriptionUi != NULL)
		{
			if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_X) || CManager::GetController()->GetJoypadTrigger(0))
			{ //X�L�[ �܂��� X�{�^�����������Ƃ�
				//��������̏I������
				m_pDescriptionUi->Uninit();
				m_pDescriptionUi = NULL;

				//SE�̍Đ�
				CManager::GetSound()->Play(CSound::SOUND_LABEL_PAPER_CLOSE);

				//�V�[���̍X�V��i�߂�
				CScene::UpdateStop(false);
			}
		}
	}
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CTutorialGame::Draw(void)
{
}