//================================================================
//
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//
//================================================================

//****************************************************************
//�C���N���[�h�t�@�C��
//****************************************************************
#include "bg.h"
#include "bg2.h"
#include "bg3.h"
#include "explosion.h"
#include "player.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "block.h"
#include "timer.h"
#include "timerlogo.h"

//****************************************************************
// �}�N����`
//****************************************************************
#define BLOCK_SPEED (-10.0f)//�u���b�N�̗����X�s�[�h
#define SPEEDUP_NUM (0.3f)//�X�s�[�h�A�b�v��

//****************************************************************
// �O���[�o���ϐ�
//****************************************************************
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;
int g_nCounterState;
float g_aBlockSpeed;//���񂾂񑁂��Ȃ�
int g_nHelloBlockTime;//�u���b�N����������鎞��
int g_nA;

//****************************************************************
//����������
//****************************************************************
void InitGame(void)
{
	//bg�̏���������
	InitBg();
	InitBg2();
	InitBg3();
	//�u���b�N�̏���������
	InitBlock();
	SetBlock(D3DXVECTOR3(800, BLOCK_POS_Y, 0),D3DXVECTOR3(BLOCK_SPEED, 0, 0.0f),0);
	// �|���S���̏���������
	InitPlayer();
	//�^�C�}�[�̏���������
	InitTimer();
	//�^�C�}�[���S�̏���������
	InitTimerLogo();
	////�e�̏���������
	//InitBullet();
	//�����̏���������
	InitExplosion();

	g_gameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_nCounterState = 370;
	g_nHelloBlockTime = 400;
	g_nA = 2;
}

//****************************************************************
//�I������
//****************************************************************
void UninitGame(void)
{
	//bg�̏I������
	UninitBg();
	UninitBg2();
	UninitBg3();
	//�u���b�N�̏I������
	UninitBlock();
	// �|���S���̏I������
	UninitPlayer();
	//�^�C�}�[�̏I������
	UninitTimer();
	//�^�C�}�[���S�̏I������
	UninitTimerLogo();
	//�����̏I������
	UninitExplosion();
}

//****************************************************************
//�X�V����
//****************************************************************
void UpdateGame(void)
{
	g_nCounterState++;
	//BLOCK_SPEED;

	UpdateBg();
	UpdateBg2();
	UpdateExplosion();
	UpdatePlayer();
	UpdateTimer();
	UpdateBlock();

	srand((unsigned int)time(NULL));
	int num = rand() % 5 + 1;

	if (g_nCounterState == g_nHelloBlockTime)
	{
		if (num==1)
		{
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH, 600, 0.0f), D3DXVECTOR3(BLOCK_SPEED+ g_aBlockSpeed, 0, 0.0f), 1);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 800, 900, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 2);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 1400, 700, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 1);
			g_nCounterState = 220;
			g_aBlockSpeed -= SPEEDUP_NUM;
			g_nHelloBlockTime -= g_nA;
		}
		else if (num == 2)
		{
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH, 950, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 2);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 800, 600, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 1);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 1400, 1000, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 2);
			g_nCounterState = 220;
			g_aBlockSpeed -= SPEEDUP_NUM;
			g_nHelloBlockTime -= g_nA;
		}
		else if (num == 3)
		{
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH, 850, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 2);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 700, 900, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 2);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 1400, 950, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 2);
			g_nCounterState = 220;
			g_aBlockSpeed -= SPEEDUP_NUM;
			g_nHelloBlockTime -= g_nA;
		}
		else if (num == 4)
		{
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH, 650, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 1);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 800, 600, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 1);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 1400, 700, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 2);
			g_nCounterState = 220;
			g_aBlockSpeed -= SPEEDUP_NUM;
			g_nHelloBlockTime -= g_nA;
		}
		else if (num == 5)
		{
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH, 850, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 2);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 800, 750, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 1);
			SetBlock(D3DXVECTOR3((BLOCK_POS_X / 2) + SCREEN_WIDTH + 1400, 600, 0.0f), D3DXVECTOR3(BLOCK_SPEED + g_aBlockSpeed, 0, 0.0f), 1);
			g_nCounterState = 220;
			g_aBlockSpeed -= SPEEDUP_NUM;
			g_nHelloBlockTime -= g_nA;
		}
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= COUNT_WAIT_FINISH_GAME)
		{
			g_aBlockSpeed = 0;
			g_nHelloBlockTime = 0;
			g_nA = 0;
			g_gameState = GAMESTATE_NONE;
			StopTimer();
			//��ʃ��[�h�̐ݒ�
			SetMode(MODE_RESULT);
		}
		break;
	}
}

//****************************************************************
//�`�揈��
//****************************************************************
void DrawGame(void)
{
	// bg�̕`�揈��
	DrawBg();
	DrawBg2();
	DrawBg3();
	//�u���b�N�̕`�揈��
	DrawBlock();
	//�����̕`�揈��
	DrawExplosion();
	// �|���S���̕`�揈��
	DrawPlayer();
	//�^�C�}�[���S�̕`�揈��
	DrawTimerLogo();
	//�^�C�}�[�̕`�揈��
	DrawTimer();
}

//****************************************************************
//�ݒ菈��
//****************************************************************
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//****************************************************************
//�f�o�C�X�̎擾
//****************************************************************
GAMESTATE GetGameState(void)
{
	return g_gameState;
}