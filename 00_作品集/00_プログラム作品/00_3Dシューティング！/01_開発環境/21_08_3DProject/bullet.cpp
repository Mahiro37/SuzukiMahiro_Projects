//=============================================================================
//
// �e���� [bullet.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "bullet.h"
#include "collision.h"
#include "manager.h"
#include "renderer.h"
#include "wall.h"
#include "block.h"
#include "bulletData.h"
#include "effect_explosion_bullet.h"
#include "effect_wall_hit.h"
#include "player.h"
#include "game.h"
#include "effect_explosion_player.h"

//*****************************************************************************
//�ÓI�����o�ϐ��錾
//*****************************************************************************
LPD3DXMESH CBullet::m_pMesh[TYPE_MAX] = {};
LPD3DXBUFFER CBullet::m_pBuffMat[TYPE_MAX] = {};
DWORD CBullet::m_NumMat[TYPE_MAX] = {};

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define BULLET_COLLISION_ROT (D3DXVECTOR3(D3DXToRadian(90), 0.0f, 0.0f))	//�e�̓����蔻��̊p�x

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CBullet::CBullet(OBJTYPE Priority) :CModel(Priority)
{
	m_type = TYPE_NONE;
	m_PlayerType = CCharacter::TYPE_NONE;
	m_vect = ZeroVector3;
	m_fMove = 0.0f;
	m_nLife = 0;
	m_nCntLife = 0;
	m_bHit = false;

	m_pCollision = nullptr;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CBullet::~CBullet()
{
}

//*****************************************************************************
//���[�h
//*****************************************************************************
void CBullet::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�Z------------------�Z
	// X�t�@�C���̓ǂݍ���
	//�Z------------------�Z

	//�e�P(�v���C���[�P)
	D3DXLoadMeshFromX("Data/Models/bullet1.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat[TYPE_BULLET1],
		NULL,
		&m_NumMat[TYPE_BULLET1],
		&m_pMesh[TYPE_BULLET1]);

	//�e�Q(�v���C���[�Q)
	D3DXLoadMeshFromX("Data/Models/bullet2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat[TYPE_BULLET2],
		NULL,
		&m_NumMat[TYPE_BULLET2],
		&m_pMesh[TYPE_BULLET2]);
}

//*****************************************************************************
//�A�����[�h
//*****************************************************************************
void CBullet::Unload()
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_pMesh[nCount] != NULL)
		{
			//���b�V���̔j��
			m_pMesh[nCount]->Release();
			m_pMesh[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_pBuffMat[nCount] != NULL)
		{
			//�o�b�t�@�̔j��
			m_pBuffMat[nCount]->Release();
			m_pBuffMat[nCount] = NULL;
		}
	}
}

//*****************************************************************************
//�e�̐���
//*****************************************************************************
CBullet * CBullet::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const D3DXVECTOR3 &vect, const TYPE &type, const CCharacter::TYPE &PlayerType)
{
	CBullet *pBullet = new CBullet;

	if (pBullet != nullptr)
	{
		//�e�̏��̐ݒ�
		pBullet->SetPos(pos);
		pBullet->SetRot(rot);
		pBullet->m_vect = vect;
		pBullet->m_type = type;
		pBullet->m_PlayerType = PlayerType;

		//�e�̏���������
		pBullet->Init();

		return pBullet;
	}

	return nullptr;
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CBullet::Init()
{
	//�e�f�[�^�̎擾����
	GetBulletData();

	HRESULT Hit = S_OK;

	//�����l�̏Փˏ���
	Hit = HitInit();
	if (Hit != S_OK)
	{
		//�I������
		Uninit();
	}

	//���f���̏���������
	CModel::Init();

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CBullet::Uninit(void)
{
	if (m_pCollision != nullptr)
	{
		//�����蔻��̏I������
		m_pCollision->Uninit();
		m_pCollision = nullptr;
	}

	//���f���̏I������
	CModel::Uninit();
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CBullet::Update(void)
{
	HRESULT Hit = S_OK;

	if (Hit == S_OK)
	{
		//�ړ�����
		Move();
	}

	if (Hit == S_OK)
	{
		//�e�ƒe�̓����蔻��
		Hit = HitBullet();
	}

	if (Hit == S_OK)
	{
		//�e�ƕǂ̓����蔻��
		Hit = HitWall();
	}

	if (Hit == S_OK)
	{
		//�e�Ə�Q���̓����蔻��
		Hit = HitBlock();
	}

	if (Hit == S_OK)
	{
		//���f���̍X�V����
		CModel::Update();
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
void CBullet::Draw(void)
{
	//���f���̕`�揈��
	CModel::Draw();
}

//*****************************************************************************
//�ړ�����
//*****************************************************************************
void CBullet::Move(void)
{
	//�ߋ��̍��W��ݒ�
	SetPosOld(GetPos());

	if (D3DXVec3Length(&m_vect) != m_fMove)
	{ //�ړ��ʂ��K��l���傫���Ƃ�
	  //�������ړ��ʂ��v�Z�����
		m_vect = m_vect / D3DXVec3Length(&m_vect) * m_fMove;
	}

	//�e���ړ�������
	SetMove(m_vect);

	if (m_pCollision != NULL)
	{
		//�����蔻�胂�f�����̐ݒ�
		m_pCollision->SetPos(GetPos());
	}
}

//*****************************************************************************
//�����l�̏Փˏ���
//*****************************************************************************
HRESULT CBullet::HitInit(void)
{
	//�e�ƕǂ̓����蔻��
	CWall *pWall = NULL;
	do
	{
		pWall = dynamic_cast<CWall*>(GetScene(OBJTYPE_WALL));

		if (pWall != NULL)
		{
			if (pWall->GetCollision() != NULL)
			{
				D3DXVECTOR3 WallPos = pWall->GetCollision()->GetPos();
				D3DXVECTOR3 WallSize = pWall->GetCollision()->GetSize();
				D3DXVECTOR3 WallRot = pWall->GetCollision()->GetRot();

				if (CCollision::RectangleCircularCollision(WallPos, WallSize, WallRot.y, GetPos(), (m_pCollision->GetSize().x / 2)) == true)
				{ //�����蔻��(��`�Ɖ~�`)
				  //�����true�ɂ���
					m_bHit = true;
				}
			}
		}
	} while (pWall != NULL);

	//�e�Ə�Q���̓����蔻��
	CBlock* pBlock = NULL;
	do
	{
		pBlock = dynamic_cast<CBlock*>(GetScene(OBJTYPE_BLOCK));

		if (pBlock != NULL)
		{
			if (pBlock->GetCollision() != NULL)
			{
				D3DXVECTOR3 BlockPos = pBlock->GetCollision()->GetPos();
				D3DXVECTOR3 BlockSize = pBlock->GetCollision()->GetSize();
				D3DXVECTOR3 BlockRot = pBlock->GetCollision()->GetRot();

				if (CCollision::RectangleCircularCollision(BlockPos, BlockSize, BlockRot.y, GetPos(), (m_pCollision->GetSize().x / 2)) == true)
				{ //�����蔻��(��`�Ɖ~�`)
				  //�����true�ɂ���
					m_bHit = true;
				}
			}
		}
	} while (pBlock != NULL);

	if (m_bHit == true)
	{ //���肪true�̂Ƃ�
	  //�����������
		m_bHit = false;

		if (CGame::GetPlayer(m_PlayerType) != NULL)
		{ //�|�C���^��NULL����Ȃ��Ƃ�
			//�����G�t�F�N�g�̐���
			CEffectExplosionPlayer::Create(CGame::GetPlayer(m_PlayerType)->GetPos());

			//�v���C���[�̏I������
			CGame::GetPlayer(m_PlayerType)->Uninit();
		}

		return S_FALSE;
	}

	return S_OK;
}

//*****************************************************************************
//�e�̏Փˏ���
//*****************************************************************************
HRESULT CBullet::HitBullet(void)
{
	CBullet *pBullet = NULL;
	do
	{
		pBullet = dynamic_cast<CBullet*>(GetScene(OBJTYPE_BULLET));
		if (pBullet != NULL)
		{
			if (this != pBullet)
			{
				if (pBullet->GetCollision() != NULL)
				{
					D3DXVECTOR3 BulletPos = pBullet->GetCollision()->GetPos();
					D3DXVECTOR3 BulletSize = pBullet->GetCollision()->GetSize();

					if (CCollision::SphereCollision(BulletPos, BulletSize.x / 2, GetPos(), m_pCollision->GetSize().x / 2) == true)
					{ //�����蔻��(��`�Ɖ~�`)
					  //�e�̔����G�t�F�N�g�̐���
						CEffectExplosionBullet::Create(GetPos());

						//�������e�̏I������
						pBullet->Uninit();
						return S_FALSE;
					}
				}
			}
		}
	} while (pBullet != NULL);

	return S_OK;
}

//*****************************************************************************
//�ǂ̏Փˏ���
//*****************************************************************************
HRESULT CBullet::HitWall(void)
{
	CWall *pWall = NULL;
	do
	{
		pWall = dynamic_cast<CWall*>(GetScene(OBJTYPE_WALL));

		if (pWall != NULL)
		{
			if (pWall->GetCollision() != NULL)
			{
				D3DXVECTOR3 WallPos = pWall->GetCollision()->GetPos();
				D3DXVECTOR3 WallSize = pWall->GetCollision()->GetSize();
				D3DXVECTOR3 WallRot = pWall->GetCollision()->GetRot();

				if (CCollision::RectangleCircularCollision(WallPos, WallSize, WallRot.y, GetPos(), (m_pCollision->GetSize().x / 2)) == true)
				{ //�����蔻��(��`�Ɖ~�`)
				  //�e�ƕǂ̏Փ˃G�t�F�N�g�̐���
					CEffectWallHit::Create(GetPos());

					//���ˉ񐔂��J�E���g
					m_nCntLife++;

					if (m_nCntLife >= m_nLife)
					{//���ˉ񐔂��K��l(BULLET_LIFE)�ɂȂ�����
						return S_FALSE;
					}

					//�P�t���[���O�̈ʒu�ɖ߂�
					SetPos(GetPosOld());

					//���˃x�N�g���̌v�Z
					m_vect = m_pCollision->ReflectionVect(m_vect, pWall->GetVect().dc, WallRot);

					//�����������Ɉړ�������
					SetMove(m_vect);

					if (m_pCollision != NULL)
					{
						//�����蔻�胂�f�����̐ݒ�
						m_pCollision->SetPos(GetPos());
					}
				}
			}
		}
	} while (pWall != NULL);

	return S_OK;
}

//*****************************************************************************
//��Q���̏Փˏ���
//*****************************************************************************
HRESULT CBullet::HitBlock(void)
{
	CBlock *pBlock = NULL;
	do
	{
		pBlock = dynamic_cast<CBlock*>(GetScene(OBJTYPE_BLOCK));

		if (pBlock != NULL)
		{
			if (pBlock->GetCollision() != NULL)
			{
				D3DXVECTOR3 BlockPos = pBlock->GetCollision()->GetPos();
				D3DXVECTOR3 BlockSize = pBlock->GetCollision()->GetSize();
				D3DXVECTOR3 BlockRot = pBlock->GetCollision()->GetRot();

				if (CCollision::RectangleCircularCollision(BlockPos, BlockSize, BlockRot.y, GetPos(), (m_pCollision->GetSize().x / 2)) == true)
				{ //�����蔻��(��`�Ɖ~�`)
					//�e�ƕǂ̏Փ˃G�t�F�N�g�̐���
					CEffectWallHit::Create(GetPos());

					//���ˉ񐔂��J�E���g
					m_nCntLife++;

					if (m_nCntLife >= m_nLife)
					{//���ˉ񐔂��K��l(BULLET_LIFE)�ɂȂ�����
						return S_FALSE;
					}

					//�P�t���[���O�̈ʒu�ɖ߂�
					SetPos(GetPosOld());

					//�e�ƒ��_�Ƃ̋���
					CCollision::DISTANCE Distance[VER_MAX];

					//�e���_�̈ʒu����
					Distance[VER_A].pos = pBlock->GetVect().a;
					Distance[VER_B].pos = pBlock->GetVect().b;
					Distance[VER_C].pos = pBlock->GetVect().c;
					Distance[VER_D].pos = pBlock->GetVect().d;

					//�e���_����e�̒��S�܂ł̋������v�Z����
					Distance[VER_A].length = D3DXVec3Length(&(GetPos() - pBlock->GetVect().a));
					Distance[VER_B].length = D3DXVec3Length(&(GetPos() - pBlock->GetVect().b));
					Distance[VER_C].length = D3DXVec3Length(&(GetPos() - pBlock->GetVect().c));
					Distance[VER_D].length = D3DXVec3Length(&(GetPos() - pBlock->GetVect().d));

					//�����̐ݒ�(��)
					Distance[VER_A].rank = 1;
					Distance[VER_B].rank = 2;
					Distance[VER_C].rank = 3;
					Distance[VER_D].rank = 4;

					//�����x�N�g���擾�p(�g��Ȃ�)
					VECT V;

					//�����x�N�g���̌v�Z(m_vect���|�C���^�œn�����ƂŁA�Ԃ�l������m_vect�̒l��ς��邱�Ƃ��ł���)
					m_pCollision->DirectionVect(GetPos(), m_vect, Distance, V);

					//�����������Ɉړ�������
					SetMove(m_vect);

					if (m_pCollision != NULL)
					{
						//�����蔻�胂�f�����̐ݒ�
						m_pCollision->SetPos(GetPos());
					}
				}
			}
		}
	} while (pBlock != NULL);

	return S_OK;
}

//*****************************************************************************
//�e�̔��ˏ���
//*****************************************************************************
D3DXVECTOR3 CBullet::ReflectVector(const D3DXVECTOR3 &front, const D3DXVECTOR3 &normal)
{
	//�Z----------------------------------�Z
	// front : �i�s�x�N�g��
	// normal: �Փ˓_�ł̖@���x�N�g��
	//�Z----------------------------------�Z
	D3DXVECTOR3 Vect = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3Normalize(&Vect, &(front - 2.0f * D3DXVec3Dot(&front, &normal) * normal));//D3DXVec3Dot:���ς̎Z�o
	
	return Vect;
}

//*****************************************************************************
//�e�f�[�^�̎擾����
//*****************************************************************************
void CBullet::GetBulletData(void)
{
	//�e�f�[�^�̎擾
	CBulletData::CreateInfo* CBulletData = CManager::GetBulletData()->GetCreateInfo(m_type);

	if (CBulletData != NULL)
	{
		//�Z-------�Z
		// �e�̐ݒ�
		//�Z-------�Z

		//�ړ���
		m_fMove = CBulletData->fMove;

		//���ː�
		m_nLife = CBulletData->nLife;

		//�����x�N�g��
		m_vect = m_vect / D3DXVec3Length(&m_vect) * m_fMove;

		//���f�����
		SetSize(CBulletData->modelSize);
		BindModel(m_pMesh[m_type], m_pBuffMat[m_type], m_NumMat[m_type]);

		if (m_pCollision == NULL)
		{
			//�����蔻��̐���
			m_pCollision = CCollision::Create(
				GetPos(),
				CBulletData->collisionSize,
				ZeroVector3,
				CCollision::TYPE_SPHERE);
		}
	}
}