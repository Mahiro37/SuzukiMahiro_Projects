//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "game.h"
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "fade.h"
#include "sound.h"
#include "mode.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#include "player.h"
#include "playerData.h"
#include "wall.h"
#include "wallData.h"
#include "block.h"
#include "blockData.h"
#include "ui_start.h"
#include "ui_win_player1.h"
#include "ui_win_player2.h"
#include "ui_draw.h"
#include "floor.h"
#include "floorData.h"

//*****************************************************************************
//�ÓI�����o�ϐ��錾
//*****************************************************************************
CCharacter::TYPE CGame::m_loser = CCharacter::TYPE_NONE;
CPlayer* CGame::m_apPlayer[CCharacter::TYPE_MAX] = {};

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CGame::CGame()
{
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
	//�J��������
	CManager::CreateCamera();

	//���C�g����
	CManager::CreateLight();

	for (int nCount = 0; nCount < CCharacter::TYPE_MAX; nCount++)
	{
		//�v���C���[�f�[�^�̎擾
		CPlayerData::CreateInfo* pPlayerData = CManager::GetPlayerData()->GetCreateInfo((CCharacter::TYPE)nCount);

		if (pPlayerData != nullptr)
		{
			if (pPlayerData->type != CCharacter::TYPE_NONE)
			{
				//�v���C���[����
				m_apPlayer[nCount] = CPlayer::Create(pPlayerData->type);
			}
		}
	}

	//�ǂ̐������̎擾
	int nCreateNumWall = CManager::GetWallData()->GetCreateNum();

	for (int nCount = 0; nCount < nCreateNumWall; nCount++)
	{
		//�ǐ���
		CWall::Create(nCount);
	}

	//��Q���̐������̎擾
	int nCreateNumBlock = CManager::GetBlockData()->GetCreateNum();

	for (int nCount = 0; nCount < nCreateNumBlock; nCount++)
	{
		//��Q������
		CBlock::Create(nCount);
	}

	//���̐������̎擾
	int nCreateNumFloor = CManager::GetFloorData()->GetCreateNum();

	for (int nCount = 0; nCount < nCreateNumFloor; nCount++)
	{
		//������
		CFloor::Create(nCount);
	}

	//UI����
	CUiStart::Create(SCREEN_CENTER, SCREEN_SIZE);

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CGame::Uninit(void)
{
	//�T�E���h�̏I��
	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_GAME);

	//�w�肵���I�u�W�F�N�g�ȊO�̃������̊J������
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CGame::Update(void)
{
	switch (m_loser)
	{
	case CCharacter::TYPE_PLAYER_1:

		//�v���C���[2����UI�̐���
		CUiWinPlayer2::Create(SCREEN_CENTER, SCREEN_SIZE);

		break;

	case CCharacter::TYPE_PLAYER_2:

		//�v���C���[1����UI�̐���
		CUiWinPlayer1::Create(SCREEN_CENTER, SCREEN_SIZE);

		break;
	}

	//�s�Ҕ���̏�����
	m_loser = CCharacter::TYPE_NONE;
}

//*****************************************************************************
//�s�Ҕ���̐ݒ�
//*****************************************************************************
void CGame::SetLoser(const CCharacter::TYPE &loser)
{
	if (m_loser != CCharacter::TYPE_NONE)
	{
		//��������UI�̐���
		CUiDraw::Create(SCREEN_CENTER, SCREEN_SIZE);
	}
	else
	{
		m_loser = loser;
	}
}

//*****************************************************************************
//�v���C���[�|�C���^�̎擾
//*****************************************************************************
CPlayer * CGame::GetPlayer(const CCharacter::TYPE &type)
{
	for (int nCount = 0; nCount < CCharacter::TYPE_MAX; nCount++)
	{
		if (m_apPlayer[nCount]->GetType() == type)
		{
			return m_apPlayer[nCount];
		}
	}

	return nullptr;
}