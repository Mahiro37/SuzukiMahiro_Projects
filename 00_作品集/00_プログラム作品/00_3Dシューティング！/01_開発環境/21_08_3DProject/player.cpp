//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPD3DXMESH CPlayer::m_apMesh[TYPE_MAX] = {};
LPD3DXBUFFER CPlayer::m_apBuffMat[TYPE_MAX] = {};
DWORD CPlayer::m_NumMat[TYPE_MAX] = {};

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CPlayer::CPlayer(OBJTYPE Priority) :CCharacter(Priority)
{
	m_type = TYPE_NONE;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CPlayer::~CPlayer()
{
}

//*****************************************************************************
//���[�h
//*****************************************************************************
void CPlayer::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�Z------------------�Z
	// X�t�@�C���̓ǂݍ���
	//�Z------------------�Z

	//�v���C���[�P
	D3DXLoadMeshFromX("Data/Models/player1.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_apBuffMat[TYPE_PLAYER_1],
		NULL,
		&m_NumMat[TYPE_PLAYER_1],
		&m_apMesh[TYPE_PLAYER_1]
	);

	//�v���C���[�Q
	D3DXLoadMeshFromX("Data/Models/player2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_apBuffMat[TYPE_PLAYER_2],
		NULL,
		&m_NumMat[TYPE_PLAYER_2],
		&m_apMesh[TYPE_PLAYER_2]
	);
}

//*****************************************************************************
//�A�����[�h
//*****************************************************************************
void CPlayer::Unload()
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_apMesh[nCount] != nullptr)
		{ //���b�V���̊J��
			m_apMesh[nCount]->Release();
			m_apMesh[nCount] = nullptr;
		}

		if (m_apBuffMat[nCount] != nullptr)
		{ //�o�b�t�@�̊J��
			m_apBuffMat[nCount]->Release();
			m_apBuffMat[nCount] = nullptr;
		}
	}
}

//*****************************************************************************
//��������
//*****************************************************************************
CPlayer * CPlayer::Create(const TYPE &type)
{
	CPlayer *pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{
		//�^�C�v�̑��
		pPlayer->m_type = type;

		//�v���C���[�̏���������
		pPlayer->Init();

		return pPlayer;
	}

	return nullptr;
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CPlayer::Init(void)
{
	//���f�����̐ݒ�
	BindModel(m_apMesh[m_type], m_apBuffMat[m_type], m_NumMat[m_type]);

	//�v���C���[�f�[�^�̐ݒ菈��
	InitPlayer(m_type);

	//�L�����N�^�[�̏���������
	CCharacter::Init();

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CPlayer::Uninit(void)
{
	//�s�Ҕ���̐ݒ�
	CGame::SetLoser(m_type);

	//�L�����N�^�[�̏I������
	CCharacter::Uninit();
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CPlayer::Update(void)
{
	HRESULT Hit = S_OK;

	if (Hit == S_OK)
	{
		//�ړ�����
		Move(m_type);
	}

	if (Hit == S_OK)
	{
		//�v���C���[�ƕǂ̓����蔻��
		HitWall(m_type);
	}

	if (Hit == S_OK)
	{
		//�v���C���[�Ə�Q���̓����蔻��
		HitBlock(m_type);
	}

	if (Hit == S_OK)
	{
		//�v���C���[�ƒe�̓����蔻��
		Hit = HitBullet(m_type);
	}

	if (Hit == S_OK)
	{
		//���ˏ���
		Shot(m_type);
	}

	if (Hit == S_OK)
	{
		//�L�����N�^�[�̍X�V����
		CCharacter::Update();
	}

	if (Hit != S_OK)
	{
		//�I������
		Uninit();
	}
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CPlayer::Draw(void)
{
	//�L�����N�^�[�̕`�揈��
	CCharacter::Draw();
}