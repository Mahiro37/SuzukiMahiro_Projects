//=============================================================================
//
// �`���[�g���A������(�X�R�A�A�^�b�N���[�h) [tutorial_score_attack.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "tutorial_score_attack.h"
#include "manager.h"
#include "keyboard.h"
#include "controller.h"
#include "bg.h"
#include "enemy.h"
#include "bullet.h"
#include "fade.h"
#include "door.h"
#include "time.h"
#include "ui.h"
#include "score.h"
#include "player.h"
#include "scene.h"
#include "explosion.h"

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CTutorialScoreAttack::CTutorialScoreAttack()
{
	m_pScore = NULL;
	m_pDescriptionUi = NULL;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CTutorialScoreAttack::~CTutorialScoreAttack()
{
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CTutorialScoreAttack::Init(void)
{
	//BGM�̍Đ�
	CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM06);

	//�w�i�̐���
	CBg::Create();

	//�v���C���[�̐���
	CManager::CreatePlayer();

	//�X�R�A�A�^�b�N���[�hUI�̐���
	CUi::Create(D3DXVECTOR3(320.0f, 105.0f, 0.0f), D3DXVECTOR3(350.0f, 150.0f, 0.0f), CUi::UI_TYPE_TUTORIAL_SCORE_ATTACK);

	//�^�C���̐���
	CManager::CreateTime(D3DXVECTOR3((SCREEN_WIDTH / 2) + 20.0f, 80.0f, 0.0f), D3DXVECTOR3(40.0f, 50.0f, 0.0f), TIME_START_NUM, CNumber::TYPE_2);
	CManager::GetTime()->SetStopTime(false);

	//�^�C�}�[UI�̐���
	CUi::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), 70.0f, 0.0f), D3DXVECTOR3(110.0f, 130.0f, 0.0f), CUi::UI_TYPE_TIMER);

	//�h�A�̐���
	CDoor::Create(D3DXVECTOR3(229.8f, 520.0f, 0.0f), DOOR_SIZE, CManager::MODE_SELECT);

	//�X�R�A�̐���
	if (m_pScore == NULL)
	{
		m_pScore = CScore::Create(D3DXVECTOR3(1070.0f, 80.0f, 0.0f), D3DXVECTOR3(50.0f, 60.0f, 0.0f), 30.0f, 0, CNumber::TYPE_2);
	}

	//�X�R�AUI�̐���
	CUi::Create(D3DXVECTOR3(880.0f, 80.0f, 0.0f), D3DXVECTOR3(90.0f, 50.0f, 0.0f), CUi::UI_TYPE_SCORE);

	//�{�[���̐����ʒu��UI�̐���
	CUi::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), 210.0f, 0.0f), D3DXVECTOR3(120.0f, 120.0f, 0.0f), CUi::UI_TYPE_BALL_CREATE);

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CTutorialScoreAttack::Uninit(void)
{
	//BGM�̒�~
	CManager::GetSound()->Stop(CSound::SOUND_LABEL_BGM06);

	if (m_pScore != NULL)
	{
		//�X�R�A�̏I������
		m_pScore->SetScore(0);
		m_pScore->Uninit();
		m_pScore = NULL;
	}

	//�S�Ẵ������̊J������
	CScene::ReleaseAllOtherThanFade();
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CTutorialScoreAttack::Update(void)
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

		bool bPlayer = false;

		for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
		{
			//�I�u�W�F�N�g�̎擾
			CScene *pScene = CScene::GetScene(nCntScene);

			//�_�C�i�~�b�N�L���X�g
			CPlayer *pPlayer = dynamic_cast<CPlayer*>(pScene);

			if (pPlayer != NULL)
			{
				bPlayer = true;

				break;
			}
		}

		//�L�[�{�[�h�̃|�C���^�̎擾
		CKeyboard *pKeyboard = CManager::GetKeyboard();

		//���݂̃^�C���̎擾
		int nTime = CManager::GetTime()->GetTime();

		if (pKeyboard->GetKeyboardTrigger(DIK_LEFT) || pKeyboard->GetKeyboardTrigger(DIK_RIGHT) || CManager::GetController()->GetJoypadTrigger(CController::BUTTON_L1) || CManager::GetController()->GetJoypadTrigger(CController::BUTTON_R1))
		{ //����� �܂��� �E��� �܂��� L1 �܂��� R1���������Ƃ�
			//�t�F�[�h�̐���
			CFade::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CManager::MODE_TUTORIAL_GAME);
		}
		else if (pKeyboard->GetKeyboardTrigger(DIK_R) || CManager::GetController()->GetJoypadTrigger(CController::BUTTON_Y) || bPlayer == false)
		{ //R�L�[ �܂��� Y�{�^�����������Ƃ� �܂��� �^�C����0�ɂȂ����Ƃ� �܂��� �v���C���[�����񂾂Ƃ�
			//SE�̒�~
			CManager::GetSound()->Stop(CSound::SOUND_LABEL_CHARGE);

			//�t�F�[�h�̐���
			CFade::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CManager::MODE_TUTORIAL_SCORE_ATTACK);
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
void CTutorialScoreAttack::Draw(void)
{
}

//*****************************************************************************
//�X�R�A�̉��Z
//*****************************************************************************
void CTutorialScoreAttack::AddScore(int nNum)
{
	if (m_pScore != NULL)
	{
		//�X�R�A�̉��Z
		m_pScore->AddScore(nNum);
	}
}