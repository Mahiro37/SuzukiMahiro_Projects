//================================================================
//
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//
//================================================================

//****************************************************************
//�C���N���[�h�t�@�C��
//****************************************************************
#include "main.h"
#include "timerlogo.h"

//****************************************************************
// �O���[�o���ϐ�
//****************************************************************
//VERTEX_2D g_aVertex[NUM_VERTEX];					// ���_���i�[
LPDIRECT3DTEXTURE9 g_pTextureTimerLogoBg = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimerLogoBg = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

//****************************************************************
// ����������
//****************************************************************
void InitTimerLogo(void)
{
	VERTEX_2D * pVtx;		// ���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "�e�N�X�`��/timer.png", &g_pTextureTimerLogoBg);	// �ϐ������ς��ƕύX

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// �o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				// (�Œ�)
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// (�Œ�)
		&g_pVtxBuffTimerLogoBg,				// �ϐ������ς��ƕύX���K�v
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���擾
	g_pVtxBuffTimerLogoBg->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

	// ���_���W�̐ݒ�( Z�̌`�ɔz�u����)  / �l�p�`�̒��_�̈ʒu
	pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (TIMERLOGO_SIZE_X / 2)-1.5f, 25.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (TIMERLOGO_SIZE_X / 2)-1.5f, 25.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - (TIMERLOGO_SIZE_X / 2)-1.5f, 25.0f + (TIMERLOGO_SIZE_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) + (TIMERLOGO_SIZE_X / 2)-1.5f, 25.0f + (TIMERLOGO_SIZE_Y / 2), 0.0f);

	// rhw�̐ݒ�(�l��1.0�ŌŒ�)		/ ���܂�ς��邱�Ƃ͂Ȃ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)	/ �S�̂̐F
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 220);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 220);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 220);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 220);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffTimerLogoBg->Unlock();
}

//****************************************************************
// �I������
//****************************************************************
void UninitTimerLogo(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureTimerLogoBg != NULL)
	{
		g_pTextureTimerLogoBg->Release();
		g_pTextureTimerLogoBg = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTimerLogoBg != NULL)
	{
		g_pVtxBuffTimerLogoBg->Release();
		g_pVtxBuffTimerLogoBg = NULL;
	}
}

//****************************************************************
// �X�V����
//****************************************************************
void UpdateTimerLogo(void)
{
}

//****************************************************************
// �`�揈��
//****************************************************************
void DrawTimerLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTimerLogoBg, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTimerLogoBg);
	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,
		NUM_POLYGON);				// �v���~�e�B�u�̐�
}