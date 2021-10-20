//================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//================================================
#ifndef _GAME_H_			// 2�d�C���N���[�h�h�~�̃}�N����`
#define _GAME_H_

#define _CRT_SECURE_NO_WARNINGS

//================================================
//�C���N���[�h�t�@�C��
//================================================
#include "main.h"

//=====================================================
//�\���̒�`
//=====================================================
typedef enum
{
	GAMESTATE_NONE = 0,
	GAMESTATE_NORMAL,
	GAMESTATE_END,
	GAMESTATE_MAX
}GAMESTATE;

//=====================================================
// �v���g�^�C�v�錾
//=====================================================
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);

#endif