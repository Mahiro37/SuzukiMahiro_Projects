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
#include "player.h"
#include "input.h"
#include "game.h"
#include "explosion.h"
#include "block.h"
#include "timer.h"

//****************************************************************
// �}�N����`
//****************************************************************
#define VALUE_MOVE (10.0f) //�|���S���̈ړ���
#define VALUE_JUMP (20.0f) //�W�����v�� 20
#define GRAVITY (1.2f) //�d�� 1.2

//****************************************************************
// �O���[�o���ϐ�
//****************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
int g_nCounterAnim;			// �A�j���[�V�����J�E���^�[
int g_nPatternAnim;			// �A�j���[�V�����p�^�[��No.
bool g_bScondJump;
int g_aNumPlayer;
PLAYER g_player;//�v���C���[�̏��

//****************************************************************
// ����������
//****************************************************************
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_player.pos = D3DXVECTOR3(0.0f, BLOCK_SIZE_Y_0, 0.0f);//�v���C���[�̏����ʒu
	g_nCounterAnim = 0;		// �A�j���[�V�����J�E���^�[�̏�����
	g_nPatternAnim = 0;		// �A�j���[�V�����p�^�[��No.�̏�����
	g_aNumPlayer = 1;

	g_bScondJump = false;
	g_player.bUse = true;
	g_player.nLife = PLAYER_LIFE;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "�e�N�X�`��/player.png",&g_pTexturePlayer);

	// ���_�o�b�t�@����
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,	// �o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				// (�Œ�)
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// (�Œ�)
		&g_pVtxBuffPlayer,				// �ϐ������ς��ƕύX���K�v
		NULL);
	VERTEX_2D * pVtx;		// ���_���ւ̃|�C���^

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

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

	// ���_���W�̍X�V
	//pVtx[0].pos = D3DXVECTOR3(g_player.pos.x + (80.0f / 2), g_player.pos.y - (80.0f / 2), 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + (80.0f / 2), g_player.pos.y + (80.0f / 2), 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - (80.0f / 2), g_player.pos.y - (80.0f / 2), 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_player.pos.x - (80.0f / 2), g_player.pos.y + (80.0f / 2), 0.0f);

	g_player.pos = D3DXVECTOR3(PLAYER_POS_X, PLAYER_POS_Y, 0.0f);

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//****************************************************************
// �|���S���I������
//****************************************************************
void UninitPlayer(void)
{
	// �e�N�X�`���̊J��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//****************************************************************
// �X�V����
//****************************************************************
void UpdatePlayer(void)
{
	// ���_���ւ̃|�C���^		�ʒu��F������Ƃ��̍ŏ��ɓ����(&pVtx)
	VERTEX_2D *pVtx;
	int nCntBlock = 0;
	BLOCK * pBlock = GetBlock(nCntBlock);
	//�錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCounterAnim++;				// �J�E���^�[���Z
	if (g_nCounterAnim == 8)		// 8fps�Ŏ��̃A�j���[�V����	�� �A�j���[�V�����̑���
	{
		g_nCounterAnim = 0;			// �J�E���^�[�������l�ɖ߂�
		g_nPatternAnim++;

		if (g_nPatternAnim == 4)	// �����������摜�̖���
		{
			g_nPatternAnim = 0;		// �J�E���^�[�������n�ɖ߂�
		}
	}

	// ���_�o�b�t�@�̃��b�N		�ʒu��F������Ƃ��̍ŏ��ɕK�v
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_player.bUse == true)
	{
		switch (g_player.state)
		{
		case PLAYERSTATE_NORMAL:
			break;
		case PLAYERSTATE_DAMAGE:
			g_player.nCounterState--;
			if (g_player.nCounterState <= 0)
			{
				g_player.state = PLAYERSTATE_NORMAL;

				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
		}

	// �ړ��̏���
		//�O��̈ʒu��ۑ�
		g_player.posOld = g_player.pos;

		//�d��
		g_player.move.y += GRAVITY;

		//�ʒu�X�V
		g_player.pos.y += g_player.move.y;

		//�Q�i�W�����v
		if (g_bScondJump == true)
		{
			//�X�y�[�X�L�[�������ꂽ��
			if (GetKeyboardTrigger(DIK_SPACE))
			{
				g_player.move.y = 0;
				g_player.move.y -= VALUE_JUMP-2;	//�W�����v�̋���
				g_bScondJump = false;
			}
			//����L�[�������ꂽ�Ƃ�
			else if (GetKeyboardTrigger(DIK_UP))
			{
				g_player.move.y = 0;
				g_player.move.y -= VALUE_JUMP + 3;	//�W�����v�̋���
				g_bScondJump = false;
			}
			//�����L�[�������ꂽ�Ƃ�
			else if (GetKeyboardTrigger(DIK_DOWN))
			{
				g_player.move.y = 0;
				g_player.move.y -= VALUE_JUMP - 5;	//�W�����v�̋���
				g_bScondJump = false;
			}
		}

		//�u���b�N��ɂ���Ƃ�
		if (CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, D3DXVECTOR3(PLAYER_WIDTH_COLLISION, PLAYER_HEIGHT_COLLISION, 0.0f)))
		{
			g_player.bJump = false;
			g_bScondJump = true;

			g_player.move.y += GRAVITY;

			// �e�N�X�`�����W���X�V
			pVtx[0].tex = D3DXVECTOR2(g_nPatternAnim * 0.251f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_nPatternAnim * 0.251f + 0.251f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_nPatternAnim * 0.251f, 0.51f);
			pVtx[3].tex = D3DXVECTOR2(g_nPatternAnim * 0.251f + 0.251f, 0.51f);

			if (g_player.bJump == false)
			{
				//�X�y�[�X�L�[�������ꂽ��
				if (GetKeyboardTrigger(DIK_SPACE))
				{
					g_player.move.y -= VALUE_JUMP;	//�W�����v�̋���
				}
			}
		}
		else
		{
			g_player.bJump = false;
			// �e�N�X�`�����W���X�V
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(0.251f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.251f, 1.0f);
		}
		if (g_player.pos.y < SCREEN_HEIGHT)
		{
			HitPlayer(100);
		}

		//// A�̃L�[�������ꂽ��
		//if (GetKeyboardPress(DIK_A) && g_player.pos.x >= 0+50)
		//{
		//	g_player.pos.x -= VALUE_MOVE;	// �ړ��̑���
		//}

		//// D�̃L�[�������ꂽ��
		//if (GetKeyboardPress(DIK_D) && g_player.pos.x <= SCREEN_WIDTH - 50)
		//{
		//	g_player.pos.x += VALUE_MOVE;	// �ړ��̑���
		//}

		//// W�̃L�[�������ꂽ��
		//if (GetKeyboardPress(DIK_W) && g_player.pos.y >= 0 + 50)
		//{
		//	g_player.pos.y -= VALUE_MOVE;	// �ړ��̑���
		//}

		//// S�̃L�[�������ꂽ��
		//if (GetKeyboardPress(DIK_S) && g_player.pos.y <= SCREEN_HEIGHT - 50)
		//{
		//	g_player.pos.y += VALUE_MOVE;	// �ړ��̑���
		//}

		// ���_���W�̍X�V
		pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - (PLAYER_SIZE / 2), g_player.pos.y - (PLAYER_SIZE / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + (PLAYER_SIZE / 2), g_player.pos.y - (PLAYER_SIZE / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - (PLAYER_SIZE / 2), g_player.pos.y + (PLAYER_SIZE / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + (PLAYER_SIZE / 2), g_player.pos.y + (PLAYER_SIZE / 2), 0.0f);
	}
	// ���_�o�b�t�@���A�����b�N		�Ō�ɕK�v
	g_pVtxBuffPlayer->Unlock();
}

//****************************************************************
// �`�揈��
//****************************************************************
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �|���S���̕`��
	if (g_player.bUse == true)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
			0,
			NUM_POLYGON);				// �v���~�e�B�u�̐�
	}
}

//****************************************************************
//�G�̎擾
//****************************************************************
PLAYER*GetPlayer(void)
{
	return&g_player;
}

//****************************************************************
//�_���[�W����
//****************************************************************
void HitPlayer(int nDamage)
{
	VERTEX_2D*pVtx;//���_���̃|�C���^
	PLAYER*pPlayer = GetPlayer();//�v���C���[�̏����擾

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);	// ���̏����͕ς��Ȃ�����

	g_player.nLife -= nDamage;

	if (g_player.nLife <= 0)
	{
		g_aNumPlayer--;
		if (g_aNumPlayer <= 0)
		{
			SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 0, 0, 0.5f));
			g_player.bUse = true;
			SetGameState(GAMESTATE_END);

			////��������
			//g_player.bUse = false;

			//// ���_�J���[�̐ݒ�
			//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
	else
	{
		//�_���[�W��Ԃ�
		g_player.state = PLAYERSTATE_DAMAGE;
		g_player.nCounterState = 5;
		if (g_player.state == PLAYERSTATE_DAMAGE)
		{
			////���_�J���[�̐ݒ�
			//pVtx[0].col = D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f);
			//pVtx[1].col = D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f);
			//pVtx[2].col = D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f);
			//pVtx[3].col = D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f);
		}
	}

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}