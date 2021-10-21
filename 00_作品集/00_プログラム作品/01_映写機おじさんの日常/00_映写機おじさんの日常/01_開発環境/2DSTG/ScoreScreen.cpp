//=============================================================================
//
// �X�R�A���ʏ��� [ScoreScreen.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "ScoreScreen.h"
#include "manager.h"
#include "keyboard.h"
#include "controller.h"
#include "bg.h"
#include "fade.h"
#include "score.h"
#include "score_attack.h"
#include "protocol_ranking.h"
#include "ui.h"
#include "time.h"
#include "ranking.h"
#include "sound.h"
#include "player.h"

//*****************************************************************************
//�ÓI�����o�ϐ��錾
//*****************************************************************************
int CScoreScreen::m_nScore = 0;
int CScoreScreen::m_nTotalTime = 0;
int CScoreScreen::m_nRanking = 0;
int CScoreScreen::m_nScoreBonus = 0;
int CScoreScreen::m_nPlayerLife = 0;

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CScoreScreen::CScoreScreen()
{
	memset(m_pScore, 0, sizeof(m_pScore));
	m_nTotalScore = 0;
	m_fAddNum = 0;
	memset(m_bSet, false, sizeof(m_bSet));
	m_nPlayerLifeBonus = 0;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CScoreScreen::~CScoreScreen()
{
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CScoreScreen::Init(void)
{
	//BGM�̍Đ�
	CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM02);

	//�w�i�̐���
	CBg::Create();

	//�X�R�A�X�N���[��UI�̐���
	CUi::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CUi::UI_TYPE_GAME_SCORE_SCREEN);

	//�Q�[���X�R�A�̐���
	m_pScore[SCORE_TYPE_0] = CScore::Create(D3DXVECTOR3(850.0f, 238.0f, 0.0f), D3DXVECTOR3(45.0f, 55.0f, 0.0f), 28.0f, 0, CNumber::TYPE_2);

	//�^�C���{�[�i�X�̐���
	m_pScore[SCORE_TYPE_1] = CScore::Create(D3DXVECTOR3(850.0f, 308.0f, 0.0f), D3DXVECTOR3(45.0f, 55.0f, 0.0f), 28.0f, 0, CNumber::TYPE_2);

	//�c�@�{�[�i�X�̐���
	m_pScore[SCORE_TYPE_2] = CScore::Create(D3DXVECTOR3(850.0f, 381.0f, 0.0f), D3DXVECTOR3(45.0f, 55.0f, 0.0f), 28.0f, 0, CNumber::TYPE_2);

	//�����X�R�A�̐���
	m_pScore[SCORE_TYPE_3] = CScore::Create(D3DXVECTOR3(850.0f, 470.0f, 0.0f), D3DXVECTOR3(60.0f, 80.0f, 0.0f), 35.0f, 0, CNumber::TYPE_1);

	//�^�C���{�[�i�X�̌v�Z
	double dScoreBonus = ((double)m_nTotalTime / TIME_START_NUM);
	if (dScoreBonus < 1.0)
	{
		dScoreBonus = 0.0;
	}
	double dScoreBonusNum = m_nScore * dScoreBonus;
	if (dScoreBonusNum - (int)dScoreBonusNum >= 0.5)
	{
		dScoreBonusNum += 1;
	}
	m_nScoreBonus = (int)dScoreBonusNum;

	//�c�@�{�[�i�X�̌v�Z
	if (m_nPlayerLife > 0)
	{
		double dPlayerLifeBonus = ((double)m_nPlayerLife / 10) + 1;

		dPlayerLifeBonus = m_nScore * dPlayerLifeBonus;

		if (dPlayerLifeBonus - (int)dPlayerLifeBonus >= 0.5)
		{
			dPlayerLifeBonus += 1;
		}

		m_nPlayerLifeBonus = (int)dPlayerLifeBonus;
	}
	else
	{
		m_nPlayerLifeBonus = 0;
	}

	//�����X�R�A�̌v�Z
	m_nTotalScore = m_nScoreBonus + m_nPlayerLifeBonus + m_nScore;

	//�����L���O�̐ݒ�
	m_nRanking = CRanking::SetRanking(m_nTotalScore);

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CScoreScreen::Uninit(void)
{
	//BGM�̒�~
	CManager::GetSound()->Stop(CSound::SOUND_LABEL_BGM02);

	//SE�̒�~
	CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);
	CManager::GetSound()->Stop(CSound::SOUND_LABEL_RANK_IN);

	for (int nCount = 0; nCount < SCORE_TYPE_MAX; nCount++)
	{
		if (m_pScore[nCount] != NULL)
		{
			//�X�R�A�̏I������
			m_pScore[nCount]->SetScore(0);
			m_pScore[nCount]->Uninit();
			m_pScore[nCount] = NULL;
		}
	}

	//�S�Ẵ������̊J������
	CScene::ReleaseAllOtherThanFade();
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CScoreScreen::Update(void)
{
	if (CScene::GetUpdateStop() == false)
	{ //�V�[���̍X�V���~�܂��Ă��Ȃ��Ƃ�
		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RETURN) || CManager::GetController()->GetJoypadTrigger(CController::BUTTON_B))
		{ //Enter�L�[ �܂��� B�{�^�����������Ƃ�
			if (m_bSet[SCORE_TYPE_0] == false)
			{ //���Z���o���I����ĂȂ��Ƃ�
				//SE�̒�~
				CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);

				//�Q�[���X�R�A�̐���
				m_pScore[SCORE_TYPE_0]->SetScore(m_nScore);

				//�J�E���g��������
				m_fAddNum = 0;

				//�����true�ɂ���
				m_bSet[SCORE_TYPE_0] = true;
			}
			else if (m_bSet[SCORE_TYPE_1] == false)
			{ //���Z���o���I����ĂȂ��Ƃ�
				//SE�̒�~
				CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);

				//�^�C���{�[�i�X�̐���
				m_pScore[SCORE_TYPE_1]->SetScore(m_nScoreBonus);

				//�J�E���g��������
				m_fAddNum = 0;

				//�����true�ɂ���
				m_bSet[SCORE_TYPE_1] = true;
			}
			else if (m_bSet[SCORE_TYPE_2] == false)
			{ //���Z���o���I����ĂȂ��Ƃ�
				//SE�̒�~
				CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);

				//�c�@�{�[�i�X�̐���
				m_pScore[SCORE_TYPE_2]->SetScore(m_nPlayerLifeBonus);

				//�J�E���g��������
				m_fAddNum = 0;

				//�����true�ɂ���
				m_bSet[SCORE_TYPE_2] = true;
			}
			else if (m_bSet[SCORE_TYPE_3] == false)
			{ //���Z���o���I����ĂȂ��Ƃ�
				//SE�̒�~
				CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);

				//�����X�R�A�̐���
				m_pScore[SCORE_TYPE_3]->SetScore(m_nTotalScore);

				//�J�E���g��������
				m_fAddNum = 0;

				//�����true�ɂ���
				m_bSet[SCORE_TYPE_3] = true;

				if (m_nRanking > 0 && m_nRanking <= MAX_RANKING)
				{
					//SE�̍Đ�
					CManager::GetSound()->Play(CSound::SOUND_LABEL_RANK_IN);

					//�����N�C��UI�̐���
					CUi::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), 600.0f, 0.0f), D3DXVECTOR3(700.0f, 200.0f, 0.0f), CUi::UI_TYPE_RANK_IN);
					CUi::Create(D3DXVECTOR3(380.0f, 570.0f, 0.0f), D3DXVECTOR3(200.0f, 150.0f, 0.0f), CUi::UI_TYPE_FUKIDASHI);
					CUi* pUi = CUi::Create(D3DXVECTOR3(385.0f, 565.0f, 0.0f), D3DXVECTOR3(120.0f, 60.0f, 0.0f), (CUi::UI_TYPE)(CUi::UI_TYPE_RANKING_1 + (m_nRanking - 1)));
					pUi->SetObjType(CScene::OBJTYPE_UI_FRONT);
				}
			}
			else
			{
				//�t�F�[�h�̐���
				CFade::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CManager::MODE_SELECT);
			}
		}

		if (m_bSet[SCORE_TYPE_0] == false)
		{ //���Z���o���I����ĂȂ��Ƃ�
			//SE�̍Đ�
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SCORE);

			//���Z���o�̃J�E���g��i�߂�
			m_fAddNum += ((float)m_nScore / 60);

			//�Q�[���X�R�A�̐���
			m_pScore[SCORE_TYPE_0]->SetScore((int)m_fAddNum);

			if (m_fAddNum >= m_nScore)
			{ //���Z���o�̃J�E���g���Q�[���X�R�A���傫���Ȃ����Ƃ�
				//SE�̒�~
				CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);

				//�Q�[���X�R�A�̐���
				m_pScore[SCORE_TYPE_0]->SetScore(m_nScore);

				//�J�E���g��������
				m_fAddNum = 0;

				//�����true�ɂ���
				m_bSet[SCORE_TYPE_0] = true;
			}
		}
		else if (m_bSet[SCORE_TYPE_1] == false)
		{ //���Z���o���I����ĂȂ��Ƃ�
			//SE�̍Đ�
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SCORE);

			//���Z���o�̃J�E���g��i�߂�
			m_fAddNum += ((float)m_nScoreBonus / 60);

			//�^�C���{�[�i�X�̐���
			m_pScore[SCORE_TYPE_1]->SetScore((int)m_fAddNum);

			if (m_fAddNum >= m_nScoreBonus)
			{ //���Z���o�̃J�E���g���^�C���{�[�i�X���傫���Ȃ����Ƃ�
				//SE�̒�~
				CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);

				//�^�C���{�[�i�X�̐���
				m_pScore[SCORE_TYPE_1]->SetScore(m_nScoreBonus);

				//�J�E���g��������
				m_fAddNum = 0;

				//�����true�ɂ���
				m_bSet[SCORE_TYPE_1] = true;
			}
		}
		else if (m_bSet[SCORE_TYPE_2] == false)
		{ //���Z���o���I����ĂȂ��Ƃ�
			//SE�̍Đ�
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SCORE);

			//���Z���o�̃J�E���g��i�߂�
			m_fAddNum += ((float)m_nPlayerLifeBonus / 60);

			//�c�@�{�[�i�X�̐���
			m_pScore[SCORE_TYPE_2]->SetScore((int)m_fAddNum);

			if (m_fAddNum >= m_nPlayerLifeBonus)
			{ //���Z���o�̃J�E���g���c�@�{�[�i�X���傫���Ȃ����Ƃ�
				//SE�̒�~
				CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);

				//�c�@�{�[�i�X�̐���
				m_pScore[SCORE_TYPE_2]->SetScore(m_nPlayerLifeBonus);

				//�J�E���g��������
				m_fAddNum = 0;

				//�����true�ɂ���
				m_bSet[SCORE_TYPE_2] = true;
			}
		}
		else if (m_bSet[SCORE_TYPE_3] == false)
		{ //���Z���o���I����ĂȂ��Ƃ�
			//SE�̍Đ�
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SCORE);

			//���Z���o�̃J�E���g��i�߂�
			m_fAddNum += ((float)m_nTotalScore / 60);

			//�����X�R�A�̐���
			m_pScore[SCORE_TYPE_3]->SetScore((int)m_fAddNum);

			if (m_fAddNum >= m_nTotalScore)
			{ //���Z���o�̃J�E���g�������X�R�A���傫���Ȃ����Ƃ�
				//SE�̒�~
				CManager::GetSound()->Stop(CSound::SOUND_LABEL_SCORE);

				//�����X�R�A�̐���
				m_pScore[SCORE_TYPE_3]->SetScore(m_nTotalScore);

				//�J�E���g��������
				m_fAddNum = 0;

				//�����true�ɂ���
				m_bSet[SCORE_TYPE_3] = true;

				if (m_nRanking > 0 && m_nRanking <= MAX_RANKING)
				{
					//SE�̍Đ�
					CManager::GetSound()->Play(CSound::SOUND_LABEL_RANK_IN);

					//�����N�C��UI�̐���
					CUi::Create(D3DXVECTOR3((SCREEN_WIDTH / 2), 600.0f, 0.0f), D3DXVECTOR3(700.0f, 200.0f, 0.0f), CUi::UI_TYPE_RANK_IN);
					CUi::Create(D3DXVECTOR3(380.0f, 570.0f, 0.0f), D3DXVECTOR3(200.0f, 150.0f, 0.0f), CUi::UI_TYPE_FUKIDASHI);
					CUi* pUi = CUi::Create(D3DXVECTOR3(385.0f, 565.0f, 0.0f), D3DXVECTOR3(120.0f, 60.0f, 0.0f), (CUi::UI_TYPE)(CUi::UI_TYPE_RANKING_1 + (m_nRanking - 1)));
					pUi->SetObjType(CScene::OBJTYPE_UI_FRONT);
				}
			}
		}
	}
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CScoreScreen::Draw(void)
{
}

//*****************************************************************************
//�X�R�A�̕ۑ�
//*****************************************************************************
void CScoreScreen::SaveScore(int nScore)
{
	m_nScore = nScore;
}

//*****************************************************************************
//�����^�C���̕ۑ�
//*****************************************************************************
void CScoreScreen::SaveTotalTime(int nTotalTime)
{
	m_nTotalTime = nTotalTime;
}

//*****************************************************************************
//�c�@�̕ۑ�
//*****************************************************************************
void CScoreScreen::SavePlayerLife(int nPlayerLife)
{
	m_nPlayerLife = nPlayerLife;
}