//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include <time.h>
#include "game.h"
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
#include "item.h"
#include "pause.h"

//*****************************************************************************
//�ÓI�����o�ϐ��錾
//*****************************************************************************
int CGame::m_nCntStage = GAME_STAGE_1;

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CGame::CGame()
{
	m_pFade = NULL;
	m_bClear = true;
	m_bStartPush = false;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CGame::~CGame()
{
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CGame::Init(void)
{
	//�w�i�̐���
	CBg::Create();

	switch (m_nCntStage)
	{
	case GAME_STAGE_1:

		//�Z�J���h�{�[���̐���
		CEnemy::Create(D3DXVECTOR3(800.0f, 200.0f, 0.0f), SECOND_BALL_SIZE, D3DXVECTOR3(3.0f, -2.0f, 0.0f), CScene::OBJTYPE_SECOND_BALL);
		CEnemy::Create(D3DXVECTOR3(400.0f, 200.0f, 0.0f), SECOND_BALL_SIZE, D3DXVECTOR3(-3.0f, -2.0f, 0.0f), CScene::OBJTYPE_SECOND_BALL);

		break;

	case GAME_STAGE_2:

		//�t�@�[�X�g�{�[���̐���
		CEnemy::Create(D3DXVECTOR3(800, 200.0f, 0.0f), FIRST_BALL_SIZE, D3DXVECTOR3(4.0f, -2.0f, 0.0f), CScene::OBJTYPE_FIRST_BALL);
		CEnemy::Create(D3DXVECTOR3(400, 200.0f, 0.0f), FIRST_BALL_SIZE, D3DXVECTOR3(-4.0f, -2.0f, 0.0f), CScene::OBJTYPE_FIRST_BALL);

		break;

	case GAME_STAGE_3:

		//�{�X�{�[���̐���
		CEnemy::Create(D3DXVECTOR3(640.0f, 200.0f, 0.0f), BOSS_BALL_SIZE, D3DXVECTOR3(-4.0f, -2.0f, 0.0f), CScene::OBJTYPE_BOSS_BALL);

		break;

	default:

		break;
	}

	//�v���C���[�̐���
	CManager::CreatePlayer();

	//�c�@�̐���
	CManager::CreateLife(D3DXVECTOR3(350.0f, 80.0f, 0.0f));

	//�c�@UI�̐���
	CUi::Create(D3DXVECTOR3(260.0f, 80.0f, 0.0f), D3DXVECTOR3(130.0f, 60.0f, 0.0f), CUi::UI_TYPE_ZANKI);

	//�c�@�̐ݒ�
	int nLife = CManager::GetPlayer()->GetPlayerLife();
	CManager::GetLife()->SetLife(nLife);

	//�t�B����UI�̐���
	CUi::Create(D3DXVECTOR3(1000.0f, 80.0f, 0.0f), D3DXVECTOR3(280.0f, 100.0f, 0.0f), CUi::UI_TYPE_FILM);

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CGame::Uninit(void)
{
	//BGM�̒�~
	CManager::GetSound()->Stop(CSound::SOUND_LABEL_BGM05);

	//�S�Ẵ������̊J������
	CScene::ReleaseAllOtherThanFade();

	if (m_pFade != NULL)
	{
		m_pFade = NULL;
	}
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CGame::Update(void)
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

	if (m_bClear == true)
	{ //�N���A���Ă��锻��̂Ƃ�
		for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
		{
			//�I�u�W�F�N�g�̎擾
			CScene *pScene = CScene::GetScene(nCntScene);

			//�_�C�i�~�b�N�L���X�g
			CEnemy *pEnemy = dynamic_cast<CEnemy*>(pScene);

			if (pEnemy != NULL)
			{ //�G���c���Ă���Ƃ�
				//�N���A���Ă��Ȃ�����ɂ���
				m_bClear = false;
			}
		}

		if (m_bClear == true)
		{ //�N���A���Ă��锻��̂Ƃ�
			//�����false�ɂ���
			m_bClear = false;

			//SE�̒�~
			CManager::GetSound()->Stop(CSound::SOUND_LABEL_CHARGE);

			//�X�e�[�W�ԍ�����i�߂�
			m_nCntStage++;

			switch (m_nCntStage)
			{
			case GAME_STAGE_CLEAR:

				if (m_pFade != NULL)
				{
					m_pFade = NULL;
				}

				if (m_pFade == NULL)
				{
					//�t�F�[�h�̐���
					m_pFade = CFade::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CManager::MODE_GAME_CREAR);
				}

				//�X�e�[�W�J�E���g�̏�����
				m_nCntStage = GAME_STAGE_1;

				break;

			default:

				if (m_pFade != NULL)
				{
					m_pFade = NULL;
				}

				if (m_pFade == NULL)
				{
					//�t�F�[�h�̐���
					m_pFade = CFade::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CManager::MODE_GAME);
				}

				break;
			}
		}
		else if (m_bClear == false)
		{ //�N���A���Ă��Ȃ�����̂Ƃ�
			//�����true�ɂ���
			m_bClear = true;
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
		{ //�v���C���[�������Ă���Ƃ�
			//�t���O��true�ɂ���
			bPlayer = true;
		}
	}

	if (bPlayer == false)
	{ //�v���C���[������ł���Ƃ�
		if (CManager::GetPlayer() != NULL)
		{
			if (CManager::GetPlayer()->GetPlayerLife() >= 0)
			{ //�c�@���c���Ă���Ƃ�
				if (m_pFade == NULL)
				{
					//�t�F�[�h�̐���
					m_pFade = CFade::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CManager::MODE_GAME);
				}
			}
		}
	}
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CGame::Draw(void)
{
}

//*****************************************************************************
//�A�C�e���X�g�b�NUI�̍X�V����
//*****************************************************************************
void CGame::UpdateStock(list<CItem::ITEMTYPE> StockItem)
{
	for (int nCntScene = 0; nCntScene < MAX_OBJECT; nCntScene++)
	{
		//�I�u�W�F�N�g�̎擾
		CScene *pScene = CScene::GetScene(nCntScene);

		//�_�C�i�~�b�N�L���X�g
		CUi *pUi = dynamic_cast<CUi*>(pScene);

		if (pUi != NULL)
		{
			//�I�u�W�F�N�g�^�C�v�̎擾
			CScene::OBJTYPE ObjType = pUi->GetObjType();

			if (ObjType == CScene::OBJTYPE_UI_ITEM)
			{ //�I�u�W�F�N�g�^�C�v���A�C�e��UI�̂Ƃ�
				//UI�̏I������
				pUi->Uninit();
			}
		}
	}

	//�C�e���[�^�ɑ��
	auto itr = StockItem.begin();

	for (int nCount = 0; nCount < (int)StockItem.size(); nCount++)
	{ //nCount���v�f���ɒB����܂ł܂��
		switch (*itr)
		{
			//���@�̈ړ��X�s�[�h�A�b�v�������Ƃ�
		case CItem::ITEMTYPE_PLAYER_SPEED_UP:

			//UI�̐���
			CUi::Create(D3DXVECTOR3(910.0f + (90.0f * nCount), 80.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CUi::UI_TYPE_PLAYER_SPEED_UP);

			break;

			//�e�̃`���[�W�X�s�[�h�A�b�v�������Ƃ�
		case CItem::ITEMTYPE_CHARGE_SPEED_UP:

			//UI�̐���
			CUi::Create(D3DXVECTOR3(910.0f + (90.0f * nCount), 80.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CUi::UI_TYPE_BULLET_SPEED_UP);

			break;

			//�o���A�������Ƃ�
		case CItem::ITEMTYPE_BARRIER:

			//UI�̐���
			CUi::Create(D3DXVECTOR3(910.0f + (90.0f * nCount), 80.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CUi::UI_TYPE_BARRIER);

			break;

		default:

			break;
		}

		//�C�e���[�^��i�߂�
		itr++;
	}
}

//*****************************************************************************
//�X�e�[�W�ԍ��̐ݒ�
//*****************************************************************************
void CGame::SetStageNum(int nStageNum)
{
	m_nCntStage = nStageNum;
}

//*****************************************************************************
//�X�e�[�W�ԍ��̎擾
//*****************************************************************************
int CGame::GetStageNum(void)
{
	return m_nCntStage;
}