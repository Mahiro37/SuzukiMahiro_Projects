#pragma once
//================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//================================================
#ifndef _BLOCK_H_			// 2�d�C���N���[�h�h�~�̃}�N����`
#define _BLOCK_H_

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
	
}BLOCKSTATE;

typedef struct
{
	BLOCKSTATE state;
	D3DXVECTOR3 pos;	//���݂̈ʒu
	D3DXVECTOR3 move;	//�ړ���
	float fWidth;		//��
	float fHeight;		//����
	int nType;			//�^�C�v
	bool bUse;			//���p�\���ǂ���
}BLOCK;
//=====================================================
// �v���g�^�C�v�錾
//=====================================================
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
bool CollisionBlock(D3DXVECTOR3*pPos,	//�ʒu
	D3DXVECTOR3*pPosOld,				//��
	D3DXVECTOR3*pMove,					//����
	D3DXVECTOR3 size);					//�T�C�Y
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos,D3DXVECTOR3 move,int nType);
BLOCK * GetBlock(int nCntBlock);
BLOCKSTATE * GetBlockState(int nCntBlock);

#endif