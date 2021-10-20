//=============================================================================
//
// �X�R�A�A�^�b�N���� [score_attack.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include <time.h>
#include "score_attack.h"
#include "manager.h"
#include "keyboard.h"
#include "controller.h"
#include "time.h"
#include "enemy.h"
#include "bg.h"
#include "player.h"
#include "score.h"
#include "life.h"
#include "sound.h"
#include "scene.h"
#include "ui.h"
#include "fade.h"
#include "ranking.h"
#include "message.h"
#include "pause.h"

//*****************************************************************************
//�ÓI�����o�ϐ��錾
//*****************************************************************************
CScore *CScoreAttack::m_pScore = NULL;

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CScoreAttack::CScoreAttack()
{
	m_pMessage = NULL;
	m_pFade = NULL;
	m_bStartPush = false;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CScoreAttack::~CScoreAttack()
{
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CScoreAttack::Init(void)
{
	//�w�i�̐���
	CBg::Create();

	//�t�@�[�X�g�{�[���̐���
	CEnemy::Create(D3DXVECTOR3(800.0f, 200.0f, 0.0f), FIRST_BALL_SIZE, D3DXVECTOR3(3.0f, -2.0f, 0.0f), CScene::OBJTYPE_FIRST_BALL);
	CEnemy::Create(D3DXVECTOR3(400.0f, 200.0f, 0.0f), FIRST_BALL_SIZE, D3DXVECTOR3(-3.0f, -2.0f, 0.0f), CScene::OBJTYPE_FIRST_BALL);

	//�v���C���[�̐���
	CManager::CreatePlayer();

	//�^�C���̐���
	CManager::CreateTime(D3DXVECTOR3((SCREEN_WIDTH / 2) + 20.0f, 80.0f, 0.0f), D3DXVECTOR3(40.0f, 50.0f, 0.0f), TIME_START_NUM, CNumber::TYPE_2);
	CManager::GetTime()->SetTime(CManager::GetTime()->GetSaveTime());
	CManager::GetTime()->SetStopTime(false);

	//�^�C�}�[UI�̐���
	CUi::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), 70.0f, 0.0f), D3DXVECTOR3(110.0f, 130.0f, 0.0f), CUi::UI_TYPE_TIMER);

	//�c�@�̐���
	CManager::CreateLife(D3DXVECTOR3(350.0f, 80.0f, 0.0f));
	int nLife = CManager::GetPlayer()->GetPlayerLife();
	CManager::GetLife()->SetLife(nLife);

	//�c�@UI�̐���
	CUi::Create(D3DXVECTOR3(260.0f, 80.0f, 0.0f), D3DXVECTOR3(130.0f, 60.0f, 0.0f), CUi::UI_TYPE_ZANKI);

	if (m_pScore == NULL)
	{
		//�X�R�A�̐���
		m_pScore = CScore::Create(D3DXVECTOR3(1070.0f, 80.0f, 0.0f), D3DXVECTOR3(50.0f, 60.0f, 0.0f), 30.0f, 0, CNumber::TYPE_2);

		if (m_pScore != NULL)
		{
			//�X�R�A�̐ݒ�
			m_pScore->SetScore(m_pScore->GetScore());
		}
	}

	//�X�R�AUI�̐���
	CUi::Create(D3DXVECTOR3(880.0f, 80.0f, 0.0f), D3DXVECTOR3(90.0f, 50.0f, 0.0f), CUi::UI_TYPE_SCORE);

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CScoreAttack::Uninit(void)
{
	//BGM�̒�~
	CManager::GetSound()->Stop(CSound::SOUND_LABEL_BGM05);

	//�S�Ẵ������̊J������
	CScene::ReleaseAllOtherThanFade();

	if (m_pScore != NULL)
	{
		//�X�R�A�̏I������
		m_pScore->Uninit();
		m_pScore = NULL;
	}

	if (m_pMessage != NULL)
	{
		m_pMessage = NULL;
	}

	if (m_pFade != NULL)
	{
		m_pFade = NULL;
	}
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CScoreAttack::Update(void)
{
	bool bPause = false;		//�|�[�Y����������Ă��邩�̔���
	bool bInstruction = false;	//�����������������Ă��邩�̔���
	CPause *pPause = NULL;		//�|�[�Y�̃|�C���^
	CUi *pUi = NULL;			//UI�̃|�C���^

	for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
	{
		//�I�u�W�F�N�g�̎擾
		CScene *pScene = CScene::GetScene(nCntScene);

		if (bPause == false)
		{ //�|�[�Y����������Ă��Ȃ��Ƃ�
		  //�_�C�i�~�b�N�L���X�g
			pPause = dynamic_cast<CPause*>(pScene);

			if (pPause != NULL)
			{
				//�t���O�𗧂Ă�
				bPause = true;
			}
		}

		if (bInstruction == false)
		{ //�����������������Ă��Ȃ��Ƃ�
		  //�_�C�i�~�b�N�L���X�g
			pUi = dynamic_cast<CUi*>(pScene);

			if (pUi != NULL)
			{
				if (pUi->GetUiType() == CUi::UI_TYPE_DESCRIPTION)
				{
					//�t���O�𗧂Ă�
					bInstruction = true;
				}
			}
		}

		if (bPause == true && bInstruction == true)
		{ //�|�[�Y�Ƒ���������ǂ������������Ă���Ƃ�
			break;
		}
	}

	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_P) || CManager::GetController()->GetJoypadTrigger(11))
	{ //P���������Ƃ� �܂��� �X�^�[�g�{�^�����������Ƃ�
		if (m_bStartPush == false && CManager::GetPlayer()->GetChargeRelease() == true)
		{ //�X�^�[�g�{�^���������Ă��Ȃ��Ƃ� ���� �`���[�W���Ă��Ȃ��Ƃ�
			if (CScene::GetUpdateStop() == false)
			{ //CScene�̍X�V���~�܂��Ă��Ȃ��Ƃ�
				if (bPause == false && bInstruction == false)
				{ //�|�[�Y�Ƒ����������������Ă��Ȃ��Ƃ�
				  //�|�[�Y�̐���
					CPause::Create();
				}
			}
			else
			{ //CScene�̍X�V���~�܂��Ă���Ƃ�
				if (bPause == true && bInstruction == false)
				{ //�|�[�Y����������Ă��āA�����������������Ă��Ȃ��Ƃ�
					if (pPause != NULL)
					{
						//�|�[�Y�̏I������
						pPause->Uninit();

						//�V�[���̍X�V��i�߂�
						CScene::UpdateStop(false);
					}
				}
			}

			//�X�^�[�g�{�^���̃v�b�V���t���O�𗧂Ă�
			m_bStartPush = true;
		}
	}

	if (CManager::GetKeyboard()->GetKeyboardRelease(DIK_P) || CManager::GetController()->GetJoypadRelease(11))
	{ //P�𗣂����Ƃ� �܂��� �X�^�[�g�{�^���𗣂����Ƃ�
	  //�X�^�[�g�{�^���̃v�b�V���t���O��������
		m_bStartPush = false;
	}

	int nTimeNow = 0;	//���̃^�C��

	if (CManager::GetTime() != NULL)
	{
		//�^�C���̎擾
		nTimeNow = CManager::GetTime()->GetTime();
	}

	if (nTimeNow != 0)
	{ //�^�C�����O�ł͂Ȃ��Ƃ�
		bool bEnemy = false;	//�G�̗L������

		for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
		{
			//�I�u�W�F�N�g�̎擾
			CScene *pScene = CScene::GetScene(nCntScene);

			//�_�C�i�~�b�N�L���X�g
			CEnemy *pEnemy = dynamic_cast<CEnemy*>(pScene);

			if (pEnemy != NULL)
			{ //�G������Ƃ�
				//�����true�ɂ���
				bEnemy = true;

				break;
			}
		}

		if (bEnemy == false)
		{ //�G�����Ȃ��Ƃ�
			//�t�@�[�X�g�{�[���̐���
			CEnemy::Create(D3DXVECTOR3(640.0f, -100.0f, 0.0f), FIRST_BALL_SIZE, D3DXVECTOR3(3.0f, -2.0f, 0.0f), CScene::OBJTYPE_FIRST_BALL);
			CEnemy::Create(D3DXVECTOR3(640.0f, -100.0f, 0.0f), FIRST_BALL_SIZE, D3DXVECTOR3(-3.0f, -2.0f, 0.0f), CScene::OBJTYPE_FIRST_BALL);
		}

		bool bPlayer = false;	//�v���C���[�̐�������

		for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
		{
			//�I�u�W�F�N�g�̎擾
			CScene *pScene = CScene::GetScene(nCntScene);

			//�_�C�i�~�b�N�L���X�g
			CPlayer *pPlayer = dynamic_cast<CPlayer*>(pScene);

			if (pPlayer != NULL)
			{ //�v���C���[�������Ă���Ƃ�
				//�����true�ɂ���
				bPlayer = true;

				break;
			}
		}

		if (bPlayer == false)
		{ //�v���C���[������ł���Ƃ�
			if (CManager::GetTime() != NULL)
			{
				//���Ԃ��~�߂�
				CManager::GetTime()->SetStopTime(true);

				//���Ԃ̕ۊ�
				CManager::GetTime()->SaveTime(nTimeNow);
			}

			if (CManager::GetPlayer()->GetPlayerLife() >= 0)
			{ //�c�@���c���Ă���Ƃ�
				if (m_pFade == NULL)
				{
					//�t�F�[�h�̐���
					m_pFade = CFade::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CManager::MODE_SCORE_ATTACK);
				}
			}
		}
	}
	else
	{
		//SE�̒�~
		CManager::GetSound()->Stop(CSound::SOUND_LABEL_CHARGE);

		if (m_pMessage == NULL)
		{
			//���b�Z�[�W�̐���
			m_pMessage = CMessage::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(400.0f, 200.0f, 0.0f), 60, CUi::UI_TYPE_FINISH, CManager::MODE_SCORE_SCREEN);
		}
	}
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CScoreAttack::Draw(void)
{
}

//*****************************************************************************
//�X�R�A�̉��Z����
//*****************************************************************************
void CScoreAttack::AddScore(int nNum)
{
	m_pScore->AddScore(nNum);
}

//*****************************************************************************
//�X�R�A�̎擾
//*****************************************************************************
CScore *CScoreAttack::GetScore(void)
{
	return m_pScore;
}