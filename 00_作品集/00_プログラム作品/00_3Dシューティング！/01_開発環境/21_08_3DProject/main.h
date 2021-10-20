//=============================================================================
//
// ���C������ [main.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
#define _CRT_SECURE_NO_WARNINGS 
#define DIRECTINPUT_VERSION 0x0800

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"
#include <dinput.h>
#include <time.h>
#include <stdio.h>

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "strmiids.lib")

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CManager;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME "AppClass"	//�E�C���h�E�̃N���X��
#define WINDOW_NAME "3D Shooting!"	//�E�C���h�E�̃L���v�V������

#define SCREEN_CENTER (D3DXVECTOR3(640.0f, 360.00f, 0.0f))	//�E�B���h�E�̒��S���W
#define SCREEN_SIZE (D3DXVECTOR3(1280, 720, 0.0f))			//�E�B���h�E�T�C�Y

#define PRIORITY		(10)
#define NUM_VERTEX		(4)
#define NUM_POLYGON		(2)

#define MAX_TEXTURE		(256)
#define MAX_POLYGON		(1024)
#define MAX_NUMBER		(4)

#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//�������p�}�N���ϐ�
#define ZeroVector3 (D3DXVECTOR3(0.0f, 0.0f, 0.0f))		//D3DXVECTOR3�̏�����
#define ZeroColor (D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))	//D3DXCOLOR�̏�����
#define FLOAT_ZERO (0.0f)								//float��0.0f
#define FLOAT_ONE (1.0f)								//float��1.0f

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct VERTEX_2D
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
};

struct VERTEX_3D
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

//*****************************************************************************
//�v���g�^�C�v�錾
//*****************************************************************************
CManager *GetManager(void);

#endif