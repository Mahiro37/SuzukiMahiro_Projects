#pragma once
//================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//================================================
#ifndef _PLAYER_H_			// 2�d�C���N���[�h�t�@�C��
#define _PLAYER_H_

#define _CRT_SECURE_NO_WARNINGS

//================================================
//�C���N���[�h�t�@�C��
//================================================
#include "main.h" 

//=====================================================
//�}�N����`
//=====================================================
#define	PLAYER_SIZE (45) //�v���C���[�̃T�C�Y
#define PLAYER_LIFE (1) //�v���C���[�̎���
#define	PLAYER_POS_X (200) //�v���C���[�̏����ʒu
#define	PLAYER_POS_Y (200) //�v���C���[�̏����ʒu

//=====================================================
//�\���̒�`
//=====================================================
//�G�̏��
typedef enum
{
	PLAYERSTATE_NORMAL = 0,//�ʏ�
	PLAYERSTATE_DAMAGE,//�_���[�W
	PLAYERSTATE_MAX//��Ԃ̍ő吔
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;//���݂̈ʒu
	D3DXVECTOR3 posOld;//�O��̈ʒu
	D3DXVECTOR3 move;//�ړ���
	PLAYERSTATE state;
	bool bUse;//�g�p���Ă��邩�ǂ���
	int nLife;//�̗�
	bool bJump;//�W�����v�����ǂ���
	int nCounterState;//��Ԃ̃J�E���^
}PLAYER;

//=====================================================
// �v���g�^�C�v�錾
//=====================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);
PLAYER *GetPlayer(void);

#endif