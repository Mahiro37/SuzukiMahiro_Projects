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
#include "title.h"
#include "input.h"

//****************************************************************
// �O���[�o���ϐ�
//****************************************************************
//VERTEX_2D g_aVertex[NUM_VERTEX];					// ���_���i�[
LPDIRECT3DTEXTURE9 g_pTexturePolygonTitle = NULL;		// �e�N�X�`���ւ̃|�C���^		Title�ɕύX���K�v
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygonTitle = NULL;	// ���_�o�b�t�@�ւ̃|�C���^		Title�ɕύX���K�v
int nCntState; //�^�C�g����ʂő�����󂯕t���Ȃ�����

//****************************************************************
// ����������
//****************************************************************
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	nCntState = 10;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "�e�N�X�`��/title.png",		// �t�@�C���̖��O
		&g_pTexturePolygonTitle);	// �ϐ������ς��ƕύX

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// �o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				// (�Œ�)
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// (�Œ�)
		&g_pVtxBuffPolygonTitle,		// �ϐ������ς��ƕύX���K�v
		NULL);
	VERTEX_2D * pVtx;		// ���_���ւ̃|�C���^

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���擾
	g_pVtxBuffPolygonTitle->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

	// ���_���W�̐ݒ�( Z�̌`�ɔz�u����)  / �l�p�`�̒��_�̈ʒu
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	// rhw�̐ݒ�(�l��1.0�ŌŒ�)		/ ���܂�ς��邱�Ƃ͂Ȃ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	// ���_�J���[�̐ݒ�(0�`255�̐��l�Őݒ�)	/ �S�̂̐F
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �������_�̐F	�����x255
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�㒸�_�̐F	�����x255
	// �e�N�X�`�����W�̐ݒ�		��ʂɑ΂��Ă̕�����
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffPolygonTitle->Unlock();
}

//****************************************************************
// �I������
//****************************************************************
void UninitTitle(void)
{
	// �e�N�X�`���̊J��
	if (g_pTexturePolygonTitle != NULL)
	{
		g_pTexturePolygonTitle->Release();
		g_pTexturePolygonTitle = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPolygonTitle != NULL)
	{
		g_pVtxBuffPolygonTitle->Release();
		g_pVtxBuffPolygonTitle = NULL;
	}
}

//****************************************************************
// �X�V����
//****************************************************************
void UpdateTitle(void)
{
	nCntState--;
	if (nCntState <= 0)
	{
		if (GetKeyboardPress(DIK_SPACE))
		{
			SetMode(MODE_TUTORIAL);
		}
	}
}

//****************************************************************
// �`�揈��
//****************************************************************
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffPolygonTitle, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePolygonTitle);
	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,
		NUM_POLYGON);				// �v���~�e�B�u�̐�
}