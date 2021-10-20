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
#include "bg.h"

//****************************************************************
// �O���[�o���ϐ�
//****************************************************************
//VERTEX_2D g_aVertex[NUM_VERTEX];					// ���_���i�[
LPDIRECT3DTEXTURE9 g_pTexturePolygonBg = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygonBg = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
int g_nCounterAnimBg;
int g_nPatternAnimBg;

//****************************************************************
// ����������
//****************************************************************
void InitBg(void)
{
	VERTEX_2D * pVtx;		// ���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "�e�N�X�`��/bg1.png",&g_pTexturePolygonBg);	// �ϐ������ς��ƕύX

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// �o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				// (�Œ�)
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// (�Œ�)
		&g_pVtxBuffPolygonBg,			// �ϐ������ς��ƕύX���K�v
		NULL);

	// ���_�f�[�^�͈̔͂����b�N
	g_pVtxBuffPolygonBg->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, -120.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, -120.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT - 120.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT - 120.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 180);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^���A�����b�N
	g_pVtxBuffPolygonBg->Unlock();
}

//****************************************************************
// �I������
//****************************************************************
void UninitBg(void)
{
	// �e�N�X�`���̊J��
	if (g_pTexturePolygonBg != NULL)
	{
		g_pTexturePolygonBg->Release();
		g_pTexturePolygonBg = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPolygonBg != NULL)
	{
		g_pVtxBuffPolygonBg->Release();
		g_pVtxBuffPolygonBg = NULL;
	}
}

//****************************************************************
// �X�V����
//****************************************************************
void UpdateBg(void)
{
	VERTEX_2D * pVtx;	// ���_���ւ̃|�C���^
	g_nCounterAnimBg++;	//�J�E���^���Z

	if (g_nCounterAnimBg == 1)//�����̑���
	{
		g_nCounterAnimBg = 0;
		g_nPatternAnimBg++;

		if (g_nPatternAnimBg == 3333)//�����������摜�̖���
		{
			g_nPatternAnimBg = 0;
		}
	}
	  
	// ���_�f�[�^�͈̔͂����b�N
	g_pVtxBuffPolygonBg->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimBg*-0.9997f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_nPatternAnimBg*-0.9997f+0.9997f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimBg*-0.9997f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_nPatternAnimBg*-0.9997f+0.9997f, 1.0f);

	// ���_�f�[�^���A�����b�N
	g_pVtxBuffPolygonBg->Unlock();
}

//****************************************************************
// �`�揈��
//****************************************************************
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffPolygonBg, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePolygonBg);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);	// �v���~�e�B�u�̎�� , �擪�̒l , �v���~�e�B�u�̐�
}