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
#include "block.h"
#include "player.h"

//****************************************************************
// �}�N����`
//****************************************************************
#define MAX_TYPE_BLOCK (3)
#define VALUE_MOVE (8.0f)

//****************************************************************
// �O���[�o���ϐ�
//****************************************************************
LPDIRECT3DTEXTURE9 g_pTextureBlock[MAX_TYPE_BLOCK] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
BLOCKSTATE g_BlockState;
BLOCK g_aBlock[MAX_BLOCK];//�u���b�N�̏��

//****************************************************************
//����������
//****************************************************************
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntBlock;

	//�u���b�N�̏��̏�����
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//g_moveBlock = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, "�e�N�X�`��/b.png", &g_pTextureBlock[0]);
		D3DXCreateTextureFromFile(pDevice, "�e�N�X�`��/yuka1.png", &g_pTextureBlock[1]);
		D3DXCreateTextureFromFile(pDevice, "�e�N�X�`��/yuka2.png", &g_pTextureBlock[2]);

	// ���_�o�b�t�@���� 
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX*MAX_BLOCK,	// �o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				// (�Œ�)
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// (�Œ�)
		&g_pVtxBuffBlock,				// �ϐ������ς��ƕύX���K�v
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

	//�u���b�N�̐���
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_0 / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_0 / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_0 / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_0 / 2), 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffBlock->Unlock(); 
}

//****************************************************************
//�I������
//****************************************************************
void UninitBlock(void)
{
	// �e�N�X�`���̊J��
	for (int nCountBlock = 0; nCountBlock < MAX_TYPE_BLOCK; nCountBlock++)
	{
		if (g_pTextureBlock[nCountBlock] != NULL)
		{
			g_pTextureBlock[nCountBlock]->Release();
			g_pTextureBlock[nCountBlock] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//****************************************************************
//�X�V����
//****************************************************************
void UpdateBlock(void)
{
	// ���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	int nCntBlock;

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock <= MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//�ړ�
			g_aBlock[nCntBlock].pos += g_aBlock[nCntBlock].move;

			if (g_aBlock[nCntBlock].nType == 0)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_0 / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_0 / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_0 / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_0 / 2), 0.0f);

				if (g_aBlock[nCntBlock].pos.x < -(BLOCK_SIZE_X_0 / 2))
				{
					//g_aBlock[nCntBlock].bUse = false;
				}
			}
			if (g_aBlock[nCntBlock].nType == 1)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_1 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_1 / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_1 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_1 / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_1 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_1 / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_1 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_1 / 2), 0.0f);

				if (g_aBlock[nCntBlock].pos.x < -(BLOCK_SIZE_X_1 / 2))
				{
					g_aBlock[nCntBlock].bUse = false;
				}
			}
			if (g_aBlock[nCntBlock].nType == 2)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_2 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_2 / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_2 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_2 / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_2 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_2 / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_2 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_2 / 2), 0.0f);

				if (g_aBlock[nCntBlock].pos.x < -(BLOCK_SIZE_X_2 / 2))
				{
					g_aBlock[nCntBlock].bUse = false;
				}
			}
		}
		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBlock->Unlock();
}

//****************************************************************
//
//****************************************************************
bool CollisionBlock(D3DXVECTOR3*pPos, D3DXVECTOR3*pPosOld, D3DXVECTOR3*pMove, D3DXVECTOR3 size)
{
	//VERTEX_2D *pVtx;						// ���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�錾
	PLAYER*pPlayer = GetPlayer();			//�G�̏����擾
	bool bLand = false;
	int nCntBlock;
	int sizeX;
	int sizeY;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (g_aBlock[nCntBlock].nType == 0)
			{
				sizeX = BLOCK_SIZE_X_0;
				sizeY = BLOCK_SIZE_Y_0;
			}
			else if (g_aBlock[nCntBlock].nType == 1)
			{
				sizeX = BLOCK_SIZE_X_1;
				sizeY = BLOCK_SIZE_Y_1;
			}
			else if (g_aBlock[nCntBlock].nType == 2)
			{
				sizeX = BLOCK_SIZE_X_2;
				sizeY = BLOCK_SIZE_Y_2;
			}

			//�u���b�N�̓����蔻��
			if (pPlayer->pos.y<g_aBlock[nCntBlock].pos.y + (sizeY / 2) + (PLAYER_SIZE / 2) &&
				pPlayer->pos.y>g_aBlock[nCntBlock].pos.y - (sizeY / 2) - (PLAYER_SIZE / 2) &&
				pPlayer->pos.x<g_aBlock[nCntBlock].pos.x + (sizeX / 2) + (PLAYER_SIZE / 2) &&
				pPlayer->pos.x>g_aBlock[nCntBlock].pos.x - (sizeX / 2) - (PLAYER_SIZE / 2))
			{
				////��
				//if (pPlayer->pos.y < g_aBlock[nCntBlock].pos.y + (sizeY / 2) + (PLAYER_SIZE / 2) &&
				//	pPlayer->posOld.y >= g_aBlock[nCntBlock].pos.y + (sizeY / 2) + (PLAYER_SIZE / 2))
				//{
				//	pPos->y = g_aBlock[nCntBlock].pos.y + (sizeY / 2) + (PLAYER_SIZE / 2);
				//	pMove->y = 0;
				//}
				//��
				if (pPlayer->pos.y > g_aBlock[nCntBlock].pos.y - (sizeY / 2) - (PLAYER_SIZE / 2) &&
					pPlayer->posOld.y <= g_aBlock[nCntBlock].pos.y - (sizeY / 2) - (PLAYER_SIZE / 2))
				{
					pPos->y = g_aBlock[nCntBlock].pos.y - (sizeY / 2) - (PLAYER_SIZE / 2);
					pMove->y = 0;
					bLand = true;
					pPlayer->bJump = true;
				}
				////�E
				//else if (pPlayer->pos.x <= g_aBlock[nCntBlock].pos.x + (sizeX / 2) + (PLAYER_SIZE) &&
				//	pPlayer->posOld.x >= g_aBlock[nCntBlock].pos.x + (sizeX / 2) + (PLAYER_SIZE / 2))
				//{
				//	pPos->x = g_aBlock[nCntBlock].pos.x + (sizeX / 2) + (PLAYER_SIZE / 2);
				//	pMove->x = 0.0f;
				//}
				//��
				else if (pPlayer->pos.x >= g_aBlock[nCntBlock].pos.x - (sizeX / 2) - (PLAYER_SIZE) &&
					pPlayer->pos.x < g_aBlock[nCntBlock].pos.x + (sizeX / 2) -(PLAYER_SIZE / 2))
				{
					pPos->x = g_aBlock[nCntBlock].pos.x - (sizeX / 2) - (PLAYER_SIZE / 2);
					pMove->x = 0.0f;
					HitPlayer(100);
				}
			}
		}
	}
	return bLand;
}

//****************************************************************
//�`�揈��
//****************************************************************
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntBlock;

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̕`��
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].nType]);
			//�u���b�N���g�p���Ȃ�`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	}
}

//****************************************************************
//�ݒ菈��
//****************************************************************
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nType)
{
	VERTEX_2D*pVtx;
	int nCntBlock;
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)//���g�p�̎�
		{
			//�ʒu�ݒ�
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].move = move;
			g_aBlock[nCntBlock].bUse = true;//�g�p���Ă����Ԃɂ���
			g_aBlock[nCntBlock].nType = nType;

			if (g_aBlock[nCntBlock].nType == 0)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_0 / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_0 / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_0 / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_0 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_0 / 2), 0.0f);
			}
			if (g_aBlock[nCntBlock].nType == 1)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_1 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_1 / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_1/ 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_1 / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_1 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_1 / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_1/ 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_1 / 2), 0.0f);
			}
			if (g_aBlock[nCntBlock].nType == 2)
			{
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_2 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_2 / 2), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_2 / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y_2 / 2), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X_2 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_2 / 2), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X_2 / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y_2 / 2), 0.0f);
			}
			break;
		} 
		//���_�f�[�^�̃|�C���^��4���i�߂�
		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//****************************************************************
//
//****************************************************************
BLOCK * GetBlock(int nCntBlock)
{
	return &g_aBlock[nCntBlock];
}
