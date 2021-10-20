#pragma once
//================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#define _CRT_SECURE_NO_WARNINGS

//================================================
//�C���N���[�h�t�@�C��
//================================================
#include "main.h"

//=====================================================
//�}�N����`
//=====================================================
#define MAX_EXPLOSION (128)//�����̍ő吔
#define EXPLOSION_SIZE (20)//�����̃T�C�Y

//================================================
//�v���g�^�C�v�錾
//================================================
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col);

#endif