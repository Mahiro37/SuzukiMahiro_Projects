//================================================================
//
//DirectX�V���[�e�B���O�Q�[��
//Author:��ؐ���
//
//================================================================

//****************************************************************
//�C���N���[�h�t�@�C��
//****************************************************************
#include "timer.h"

//****************************************************************
//�O���[�o���ϐ��錾
//****************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTimer = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;//���_�o�b�t�@�ւ̃|�C���^
int g_nTimer;
int g_nCounterAnimTimer = 0, g_nPatternAnimTimer = 0;
bool g_TimerUse;

//****************************************************************
// ����������
//****************************************************************
void InitTimer(void)
{
	//�ϐ��錾
	VERTEX_2D*pVtx;//���_���̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_nTimer = 0; //�^�C�}�[�̏�����
	g_TimerUse = true;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "�e�N�X�`��/number.png", &g_pTextureTimer);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_TIMER, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTimer, NULL);

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�����

	for (int nScore = 0; nScore < MAX_TIMER; nScore++)
	{
		//���W�̐ݒ�i�E���Őݒ肷��j
		pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH - (nScore*NUMBER_SIZE_X + NUMBER_SIZE_X / 2) - (NUMBER_SIZE_X / 2) - 595, (NUMBER_SIZE_Y / 2) - (NUMBER_SIZE_Y / 2) + 80.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH - (nScore*NUMBER_SIZE_X + NUMBER_SIZE_X / 2) + (NUMBER_SIZE_X / 2) - 595, (NUMBER_SIZE_Y / 2) - (NUMBER_SIZE_Y / 2) + 80.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH - (nScore*NUMBER_SIZE_X + NUMBER_SIZE_X / 2) - (NUMBER_SIZE_X / 2) - 595, (NUMBER_SIZE_Y / 2) + (NUMBER_SIZE_Y / 2) + 80.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH - (nScore*NUMBER_SIZE_X + NUMBER_SIZE_X / 2) + (NUMBER_SIZE_X / 2) - 595, (NUMBER_SIZE_Y / 2) + (NUMBER_SIZE_Y / 2) + 80.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 230);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 230);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 230);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 230);

		//�e�N�X�`���̍��W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�f�[�^�A�����b�N
	g_pVtxBuffTimer->Unlock();

}

//****************************************************************
// �I������
//****************************************************************
void UninitTimer(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}

//****************************************************************
// �X�V����
//****************************************************************
void UpdateTimer(void)
{
	//�ϐ��錾
	VERTEX_2D*pVtx;//���_���̃|�C���^
	float fIndex;  //�w���@(�X�R�A�\���p)
	float fRadix = 10.0f; //��@(�X�R�A�\���p)

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);//���̏����͕ς��Ȃ�����

	for (fIndex = 0; fIndex < MAX_TIMER; fIndex++)
	{
		int nScore = (int)powf(fRadix, MAX_TIMER - fIndex);
		int nScore2 = (int)powf(fRadix, MAX_TIMER - fIndex - 1);
		int nAnswer = g_nTimer % nScore / nScore2;

		//�e�N�X�`���̍��W
		pVtx[8].tex = D3DXVECTOR2(0.0f + (0.1f* nAnswer), 0.0f);
		pVtx[9].tex = D3DXVECTOR2(0.1f + (0.1f* nAnswer), 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f + (0.1f* nAnswer), 1.0f);
		pVtx[11].tex = D3DXVECTOR2(0.1f + (0.1f* nAnswer), 1.0f);

		pVtx -= 4;//���_�f�[�^�̃|�C���^��4���i�߂�

	}

	g_nCounterAnimTimer++;
	if (g_nCounterAnimTimer == 59) //�t���[��
	{
		g_nCounterAnimTimer = 0;
		g_nPatternAnimTimer++;
		if (g_nPatternAnimTimer == 1) //1�b�Ԍo������^�C��+1
		{
			if (g_TimerUse == true)
			{
				g_nTimer++;
			}
				g_nPatternAnimTimer = 0;
		}
	}

	//���_�f�[�^�A�����b�N
	g_pVtxBuffTimer->Unlock();
}

//****************************************************************
// �`�揈��
//****************************************************************
void DrawTimer(void)
{

	//���_�t�H�[�}�b�g�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�

	//�X�R�A�̐����̕`��
	for (int nScore = 0; nScore < MAX_TIMER; nScore++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTimer);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nScore * 4, NUM_POLYGON);
	}

}

//****************************************************************
// �X�R�A���̑��M
//****************************************************************
int GetTimer(void)
{
	return g_nTimer;
}

//****************************************************************
//
//****************************************************************
void StopTimer(void)
{
	g_TimerUse = false;
}