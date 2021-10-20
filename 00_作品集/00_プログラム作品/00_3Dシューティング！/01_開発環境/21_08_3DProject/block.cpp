//=============================================================================
//
// ��Q������ [block.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "block.h"
#include "blockData.h"
#include "renderer.h"
#include "manager.h"
#include "collision.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPD3DXMESH CBlock::m_pMesh = nullptr;
LPD3DXBUFFER CBlock::m_pBuffMat = nullptr;
DWORD CBlock::m_nNumMat = NULL;

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CBlock::CBlock(OBJTYPE nPriority) :CModel(nPriority)
{
	m_nCreateNum = 0;

	m_pCollision = NULL;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CBlock::~CBlock()
{
}

//*****************************************************************************
//���[�h
//*****************************************************************************
void CBlock::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("Data/Models/block.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh
	);
}

//*****************************************************************************
//�A�����[�h
//*****************************************************************************
void CBlock::Unload()
{
	if (m_pMesh != nullptr)
	{ //���b�V���̊J��
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	if (m_pBuffMat != nullptr)
	{ //�o�b�t�@�̊J��
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}
}

//*****************************************************************************
//��������
//*****************************************************************************
CBlock * CBlock::Create(const int nCreateNum)
{
	CBlock *pWall = new CBlock;

	if (pWall != nullptr)
	{
		//��Q���̐ݒ�
		pWall->m_nCreateNum = nCreateNum;

		//��Q���̏���������
		pWall->Init();

		return pWall;
	}

	return nullptr;
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CBlock::Init(void)
{
	//��Q���f�[�^�̎擾����
	GetBlockData();

	//���f���̏���������
	CModel::Init();

	return E_NOTIMPL;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CBlock::Uninit(void)
{
	//���f���̏I������
	CModel::Uninit();

	if (m_pCollision != NULL)
	{
		//�����蔻��̏I������
		m_pCollision->Uninit();
	}
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CBlock::Update(void)
{
	//���f���̍X�V����
	CModel::Update();
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CBlock::Draw(void)
{
	//���f���̕`�揈��
	CModel::Draw();
}

//*****************************************************************************
//��Q���f�[�^�̎擾����
//*****************************************************************************
void CBlock::GetBlockData(void)
{
	//�ǃf�[�^�̎擾
	CBlockData::CreateInfo* pBlockData = CManager::GetBlockData()->GetCreateInfo(m_nCreateNum);

	if (pBlockData != NULL)
	{
		//�Z-------�Z
		// �ǂ̐ݒ�
		//�Z-------�Z

		//���f�����̐ݒ�
		SetPos(pBlockData->pos);
		SetSize(pBlockData->size);
		SetRot(pBlockData->rot);
		BindModel(m_pMesh, m_pBuffMat, m_nNumMat);

		if (m_pCollision == NULL)
		{
			//�����蔻��̑傫���̎擾
			D3DXVECTOR3 CollisionSize = pBlockData->collisionSize;

			//�����蔻��̐���
			m_pCollision = CCollision::Create(
				pBlockData->pos,
				CollisionSize,
				pBlockData->rot,
				CCollision::TYPE_BOX);

			//���W�����߂�
			m_vect.a = VertexRotate(pBlockData->pos, CollisionSize, pBlockData->rot, VER_A);	//A���W
			m_vect.b = VertexRotate(pBlockData->pos, CollisionSize, pBlockData->rot, VER_B);	//B���W
			m_vect.c = VertexRotate(pBlockData->pos, CollisionSize, pBlockData->rot, VER_C);	//C���W
			m_vect.d = VertexRotate(pBlockData->pos, CollisionSize, pBlockData->rot, VER_D);	//D���W

			//�ǂ̓����蔻��̕����x�N�g�������߂�
			m_vect.ad = m_vect.d - m_vect.a;	//AD�x�N�g��
			m_vect.dc = m_vect.c - m_vect.d;	//DC�x�N�g��
			m_vect.cb = m_vect.b - m_vect.c;	//CB�x�N�g��
			m_vect.ba = m_vect.a - m_vect.b;	//BA�x�N�g��
		}
	}
}