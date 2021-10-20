#pragma once
//================================================
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS

//=====================================================
// �C���N���[�h�t�@�C��
//=====================================================
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	// �x���Ώ��p("dinput.h"�̒��O�ɒ�`)
#include <dinput.h>

//=====================================================
// �}�N����`
//=====================================================
#define SCREEN_WIDTH (1280)		// �E�C���h�E�̕�
#define SCREEN_HEIGHT (720)		// �E�C���h�E�̍���
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define NUM_VERTEX (4)			// ���_��
#define NUM_POLYGON (2)			// �|���S�� (�O�p�`�̐�)
#define POLYGON_SIZE_X (150)
#define POLYGON_SIZE_Y (150)
#define MAX_TYPE_ENEMY (128)
#define MAX_BLOCK (10)
#define BLOCK_SIZE_X_0 (2500)
#define BLOCK_SIZE_Y_0 (300)
#define BLOCK_SIZE_X_1 (600)
#define BLOCK_SIZE_Y_1 (300)
#define BLOCK_SIZE_X_2 (200)
#define BLOCK_SIZE_Y_2 (1000)
#define BLOCK_POS_X (2000)
#define BLOCK_POS_Y (650)
#define PLAYER_WIDTH_COLLISION POLYGON_SIZE_X
#define PLAYER_HEIGHT_COLLISION POLYGON_SIZE_Y
// ���_�t�H�[�}�b�g(���_���W[2D]/���_�J���[/�e�N�X�`�����W)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//=====================================================
// ���C�u�����̃����N
//=====================================================
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")		// ���͏����ɕK�v

//=====================================================
// �\���̒�`
//=====================================================
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_2D;

//���[�h�̑I��
typedef enum
{
	MODE_TITLE = 0,//�^�C�g�����
	MODE_TUTORIAL,//�`���[�g���A�����
	MODE_GAME,//�Q�[�����
	MODE_RESULT,//���U���g���
	MODE_MAX
}MODE;

//=====================================================
// �v���g�^�C�v�錾
//=====================================================
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
#endif