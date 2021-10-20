//=============================================================================
//
// �L�����N�^�[�N���X [character.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "character.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "collision.h"
#include "player.h"
#include "playerData.h"
#include "wall.h"
#include "block.h"
#include "effect_explosion_player.h"
#include "keyboard.h"
#include "bulletData.h"
#include "bullet.h"

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CCharacter::CCharacter(OBJTYPE Priority) : CModel(Priority)
{
	m_bInput = false;

	m_fPlayerMove = FLOAT_ZERO;
	m_MoveVect = ZeroVector3;
	m_fVectLength = FLOAT_ZERO;
	m_SlideVect = ZeroVector3;

	m_BulletDistance = ZeroVector3;
	m_nBulletType = CBullet::TYPE_NONE;

	m_nCntHit = 0;
	m_pCollision = nullptr;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CCharacter::~CCharacter()
{
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CCharacter::Init(void)
{
	//���f���̏���������
	CModel::Init();

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CCharacter::Uninit()
{
	if (m_pCollision != nullptr)
	{
		//�����蔻��̐���
		m_pCollision->Uninit();
		m_pCollision = nullptr;
	}

	//���f���̏I������
	CModel::Uninit();
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CCharacter::Update()
{
	//�Փˌ�̏���
	AfterHit();

	//���f���̍X�V����
	CModel::Update();
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CCharacter::Draw()
{
	//���f���̕`�揈��
	CModel::Draw();
}

//*****************************************************************************
//�v���C���[�f�[�^�̐ݒ菈��
//*****************************************************************************
void CCharacter::InitPlayer(const TYPE &type)
{
	//�Z---------------�Z
	// �v���C���[�̐ݒ�
	//�Z---------------�Z

	//�v���C���[�f�[�^�̎擾
	CPlayerData::CreateInfo* pPlayerData = CManager::GetPlayerData()->GetCreateInfo(type);

	if (pPlayerData != nullptr)
	{
		//�ړ���
		SetPlayerMove(pPlayerData->fMove);

		//�����x�N�g��
		SetMoveVect(VectorCalculation(
			pPlayerData->pos,
			D3DXVECTOR3((pPlayerData->fMove * cosf(pPlayerData->rot.y)) + pPlayerData->pos.x,
				0.0f,
				(-pPlayerData->fMove * sinf(pPlayerData->rot.y)) + pPlayerData->pos.z)));

		//�x�N�g���̒���
		SetVectLength(D3DXVec3Length(&GetMoveVect()));

		if (GetVectLength() > GetPlayerMove())
		{ //�ړ��ʂ��K��l���傫���Ƃ�
		  //�������ړ��ʂ��v�Z
			SetMoveVect(GetMoveVect() / GetVectLength() * GetPlayerMove());
		}

		//���f�����̐ݒ�
		SetPos(pPlayerData->pos);
		SetSize(pPlayerData->modelSize);
		SetRot(pPlayerData->rot);

		if (m_pCollision == nullptr)
		{
			//�����蔻��̐���
			m_pCollision = CCollision::Create(pPlayerData->pos, pPlayerData->collisionSize, pPlayerData->rot, CCollision::TYPE_BOX);
		}
	}

	//�Z-------�Z
	// �e�̐ݒ�
	//�Z-------�Z

	//�e�̎�ޗp�ϐ�
	CBullet::TYPE BulletType = CBullet::TYPE_NONE;

	if (pPlayerData != nullptr)
	{
		//�e�̎�ނ̑��
		BulletType = (CBullet::TYPE)pPlayerData->nBulletType;
	}

	//�e�f�[�^�̎擾�p�ϐ�
	CBulletData::CreateInfo* pBulletData = nullptr;

	//�e�f�[�^�̎擾
	pBulletData = CManager::GetBulletData()->GetCreateInfo(BulletType);

	if (pBulletData != nullptr)
	{
		//�e�̐����ʒu(�v���C���[�̒��S����̋���)
		SetBulletDistance(pBulletData->distance);

		//�e�̎��
		SetBulletType((CBullet::TYPE)pBulletData->nType);
	}
}

//*****************************************************************************
//�v���C���[���Ƃ̓����蔻��̃|�C���^��Ԃ�����
//*****************************************************************************
CCollision * CCharacter::SelectCollisionPointer(const TYPE &type)
{
	if (type != TYPE_NONE)
	{ //�I�u�W�F�^�C�v��TYPE_NONE�ł͂Ȃ��Ƃ�
		//�v���C���[���̎擾
		return CGame::GetPlayer(type)->GetCollision();
	}
	else
	{
		return nullptr;
	}
}

//*****************************************************************************
//�ړ�����
//*****************************************************************************
void CCharacter::Move(const TYPE &type)
{
	//�L�[�{�[�h�ƃR���g���[���̃|�C���^�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	//�ߋ��̍��W�̐ݒ�
	SetPosOld(GetPos());

	//�ړ��ʗp�ϐ��̐ݒ�
	D3DXVECTOR3 move = ZeroVector3;
	SetMove(move);

	//���͏�Ԃ̐ݒ�
	SetInputState(false);

	//�L�[�{�[�h�̈ړ�����
	if (type == TYPE_PLAYER_1)
	{ //�I�u�W�F�^�C�v���v���C���[�P�̂Ƃ�
		if (pInputKeyboard->GetKeyPress(DIK_A))
		{ //A���������Ƃ�
			move.x -= m_fPlayerMove;
			SetInputState(true);
		}
		if (pInputKeyboard->GetKeyPress(DIK_D))
		{ //D���������Ƃ�
			move.x += m_fPlayerMove;
			SetInputState(true);
		}
		if (pInputKeyboard->GetKeyPress(DIK_W))
		{ //W���������Ƃ�
			move.z += m_fPlayerMove;
			SetInputState(true);
		}
		if (pInputKeyboard->GetKeyPress(DIK_S))
		{ //S���������Ƃ�
			move.z -= m_fPlayerMove;
			SetInputState(true);
		}
	}
	else if (type == TYPE_PLAYER_2)
	{ //�I�u�W�F�^�C�v���v���C���[�Q�̂Ƃ�
		if (pInputKeyboard->GetKeyPress(DIK_LEFT))
		{ //�E�����������Ƃ�
			move.x -= m_fPlayerMove;
			SetInputState(true);
		}
		if (pInputKeyboard->GetKeyPress(DIK_RIGHT))
		{ //�������������Ƃ�
			move.x += m_fPlayerMove;
			SetInputState(true);
		}
		if (pInputKeyboard->GetKeyPress(DIK_UP))
		{ //������������Ƃ�
			move.z += m_fPlayerMove;
			SetInputState(true);
		}
		if (pInputKeyboard->GetKeyPress(DIK_DOWN))
		{ //�������������Ƃ�
			move.z -= m_fPlayerMove;
			SetInputState(true);
		}
	}

	if (GetInputState() == true)
	{ //���͂���Ă���Ƃ�
	  //�x�N�g���̌v�Z
		SetMoveVect(VectorCalculation(GetPos() - GetPosOld(), move));

		//�x�N�g���̒����̌v�Z
		m_fVectLength = D3DXVec3Length(&GetMoveVect());

		if (m_fVectLength > m_fPlayerMove)
		{ //�ړ��ʂ��K��l���傫���Ƃ�
		  //�������ړ��ʂ��v�Z���đ��
			SetMoveVect(GetMoveVect() / D3DXVec3Length(&GetMoveVect()) * m_fPlayerMove);
			move = GetMoveVect();
		}

		//�ړ��ʂ̐ݒ�
		SetMove(move);

		//�Ȃ��p�Ƃ��v�Z���A���W�A���ɕϊ����Ċp�x��ݒ�
		SetRot(D3DXVECTOR3(
			GetRot().x,
			D3DXToRadian(AngleOf2Vector(D3DXVECTOR3(m_fPlayerMove, 0.0f, 0.0f), GetMoveVect())),
			GetRot().z));

		if (SelectCollisionPointer(type) != NULL)
		{
			//�����蔻�胂�f�����̐ݒ�
			SelectCollisionPointer(type)->SetPos(GetPos());
			SelectCollisionPointer(type)->SetRot(GetRot());
		}
	}
}

//*****************************************************************************
//���ˏ���
//*****************************************************************************
void CCharacter::Shot(const TYPE &type)
{
	//�L�[�{�[�h�ƃR���g���[���̃|�C���^�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	if (type == TYPE_PLAYER_1)
	{ //�I�u�W�F�^�C�v���v���C���[�P�̂Ƃ�
		if (pInputKeyboard->GetKeyTrigger(DIK_SPACE))
		{ //SPACE���������Ƃ�
			//�e�̔���
			CBullet::Create(BulletPosition(GetPos(), GetRot(), m_BulletDistance), GetRot(), GetMoveVect(), (CBullet::TYPE)m_nBulletType, type);
		}
	}
	else if (type == TYPE_PLAYER_2)
	{ //�I�u�W�F�^�C�v���v���C���[�Q�̂Ƃ�
		if (pInputKeyboard->GetKeyTrigger(DIK_NUMPADENTER))
		{ //�e���L�[��ENTER���������Ƃ�
			//�e�̔���
			CBullet::Create(BulletPosition(GetPos(), GetRot(), m_BulletDistance), GetRot(), GetMoveVect(), (CBullet::TYPE)m_nBulletType, type);
		}
	}
}

//*****************************************************************************
// �x�N�g���v�Z
//*****************************************************************************
D3DXVECTOR3 CCharacter::VectorCalculation(const D3DXVECTOR3 &Va, const D3DXVECTOR3 &Vb)
{
	//�x�N�g���̌v�Z
	D3DXVECTOR3 Vab = Vb - Va;

	if (Vab != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{ //�x�N�g�������݂���Ƃ�
	  //�ߋ��̃x�N�g�����㏑��
		SetVectOld(Vab);
	}
	else
	{ //�x�N�g�������݂��Ȃ��Ƃ�
	  //��ԍŋ߂̃x�N�g������
		Vab = GetVectOld();
	}

	return Vab;
}

//*****************************************************************************
// �Q�̃x�N�g��AB�̂Ȃ��p�x�Ƃ����߂�v�Z
//*****************************************************************************
float CCharacter::AngleOf2Vector(const D3DXVECTOR3 &VectorA, const D3DXVECTOR3 &VectorB)
{
	//�x�N�g��A��B�̒������v�Z����
	float fLengthA = D3DXVec3Length(&VectorA);
	float fLengthB = D3DXVec3Length(&VectorB);

	//���ςƃx�N�g���������g����cos�Ƃ����߂�
	float fCosSita = D3DXVec3Dot(&VectorA, &VectorB) / (fLengthA * fLengthB);

	//cos�Ƃ���Ƃ����߂�
	float fSita = (float)D3DXToDegree(acos(fCosSita));

	if (VectorB.z > 0)
	{ //�x�N�g����Z���W���v���X�̂Ƃ�
	  //�p�x���~-�P����
		fSita = 360.0f - fSita;
	}

	return fSita;
}

//*****************************************************************************
// �e�̐����ʒu�̌v�Z
//*****************************************************************************
D3DXVECTOR3 CCharacter::BulletPosition(const D3DXVECTOR3 &PlayerPos, const D3DXVECTOR3 &PlayerRot, const D3DXVECTOR3 &BulletDistance)
{
	//�e�̈ʒu�p�ϐ�
	D3DXVECTOR3 BulletPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�v���C���[����]�������̒e�̔������W(X,Z)�����߂�
	BulletPos = D3DXVECTOR3(
		(BulletDistance.x * cosf(PlayerRot.y)) + PlayerPos.x,
		0.0f,
		(-BulletDistance.z * sinf(PlayerRot.y)) + PlayerPos.z);

	return BulletPos;
}

//*****************************************************************************
//�Փˌ�̏���
//*****************************************************************************
void CCharacter::AfterHit(void)
{
	if (m_nCntHit > 0)
	{ //��x�ł���Q���ɓ������Ă����Ƃ�
		//��Q���ɓ�����O�̈ʒu����
		SetPos(GetPosOld());
		if (m_pCollision != nullptr)
		{
			m_pCollision->SetPos(GetPosOld());
		}

		if (m_nCntHit == 1)
		{ //�J�E���g���P�̂Ƃ�
			if (GetInputState() == true)
			{ //���͂���Ă�����
				//�ǂ���x�N�g����ݒ�
				SetMove(m_SlideVect);
			}
		}
		else
		{
			//�ǂ���x�N�g����ݒ�
			SetMove(ZeroVector3);
		}

		//�����ɂ������������̃J�E���g�̏�����
		m_nCntHit = 0;
	}
	else
	{
		//�ǂ���x�N�g���̏�����
		m_SlideVect = ZeroVector3;
	}
}

//*****************************************************************************
//�ǂ̓����蔻��
//*****************************************************************************
void CCharacter::HitWall(const TYPE &type)
{
	CCollision* pCollision = nullptr;		//�v���C���[�̓����蔻��|�C���^�p

	//�����蔻��̃|�C���^���擾
	pCollision = SelectCollisionPointer(type);

	CWall *pWall = nullptr;	//�ǃ|�C���^�̎󂯎��p

	do
	{
		pWall = dynamic_cast<CWall*>(GetScene(OBJTYPE_WALL));

		if (pWall != nullptr)
		{
			if (pCollision != nullptr && pWall->GetCollision() != nullptr)
			{
				if (pCollision->WallCollision(pWall->GetVect(), GetPos(), pCollision->GetSize(), GetRot().y) == true)
				{ //�����蔻��(��`�Ƌ�`)
				  //���������񐔂��J�E���g
					m_nCntHit++;

					if (m_nCntHit == 1)
					{ //�J�E���g���P�̂Ƃ�
						//���������ǂ̕ǂ���x�N�g�����擾
						m_SlideVect = pCollision->SlideVect(GetMoveVect(), pWall->GetVect().dc);
					}
				}
			}
		}
	} while (pWall != nullptr);
}

//*****************************************************************************
//��Q���̓����蔻��
//*****************************************************************************
void CCharacter::HitBlock(const TYPE &type)
{
	CCollision* pCollision = nullptr;		//�v���C���[�̓����蔻��|�C���^�p

	//�����蔻��̃|�C���^���擾
	pCollision = SelectCollisionPointer(type);

	VECT dirVect;							//�ł��߂��Q�_�̕����x�N�g���擾�p
	memset(&dirVect, 0, sizeof(dirVect));
	CBlock *pBlock = nullptr;				//��Q���|�C���^�̎󂯎��p

	do
	{
		pBlock = dynamic_cast<CBlock*>(GetScene(OBJTYPE_BLOCK));

		if (pBlock != nullptr)
		{
			//�����蔻��p�ϐ�
			bool bHit = false;

			if (pCollision != nullptr)
			{
				//�����蔻��(��`�Ƌ�`)
				pCollision->BlockCollision(bHit, dirVect, pBlock->GetRot(), pBlock->GetVect(), GetPos(), pCollision->GetSize(), GetRot().y, m_SlideVect);

				if (bHit == true)
				{ //�������Ă���Ƃ�
					//���������񐔂��J�E���g
					m_nCntHit++;

					if (m_nCntHit == 1 && dirVect.direction != ZeroVector3)
					{ //�J�E���g���P�̂Ƃ�
						//����������Q���̕ǂ���x�N�g�����擾
						m_SlideVect = pCollision->SlideVect(GetMoveVect(), dirVect.direction);
					}
				}

				//�ł��߂��Q�_�̕����x�N�g���擾�p�ϐ��̏�����
				memset(&dirVect, 0, sizeof(dirVect));
			}
		}
	} while (pBlock != nullptr);
}

//*****************************************************************************
//�e�̓����蔻��
//*****************************************************************************
HRESULT CCharacter::HitBullet(const TYPE &type)
{
	CCollision* pCollision = nullptr;		//�v���C���[�̓����蔻��|�C���^�p

	//�����蔻��̃|�C���^���擾
	pCollision = SelectCollisionPointer(type);

	CBullet *pBullet = NULL;
	do
	{
		pBullet = dynamic_cast<CBullet*>(GetScene(OBJTYPE_BULLET));

		if (pBullet != nullptr && pBullet->GetCollision() != nullptr)
		{
			D3DXVECTOR3 BulletPos = pBullet->GetCollision()->GetPos();
			D3DXVECTOR3 BulletSize = pBullet->GetCollision()->GetSize();

			if (pCollision != nullptr)
			{
				if (CCollision::RectangleCircularCollision(GetPos(), pCollision->GetSize(), GetRot().y, BulletPos, (BulletSize.x / 2)) == true)
				{ //�����蔻��(��`�Ɖ~�`)
					//�����G�t�F�N�g�̐���
					CEffectExplosionPlayer::Create(GetPos());

					//�e�̏I������
					pBullet->Uninit();
					return S_FALSE;
				}
			}
		}
	} while (pBullet != nullptr);

	return S_OK;
}