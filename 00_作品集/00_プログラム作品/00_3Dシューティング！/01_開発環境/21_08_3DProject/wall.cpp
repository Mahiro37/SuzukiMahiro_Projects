//=============================================================================
//
// �Ǐ��� [wall.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "wall.h"
#include "renderer.h"
#include "manager.h"
#include "collision.h"
#include "wallData.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPD3DXMESH CWall::m_pMesh = NULL;
LPD3DXBUFFER CWall::m_pBuffMat = NULL;
DWORD CWall::m_nNumMat = NULL;

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CWall::CWall(OBJTYPE nPriority) :CModel(nPriority)
{
	m_type = TYPE_NONE;
	m_nCreateNum = 0;
	memset(&m_vect, 0, sizeof(m_vect));
	m_pCollision = NULL;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CWall::~CWall()
{
}

//*****************************************************************************
//���[�h
//*****************************************************************************
void CWall::Load()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("Data/Models/wall.x",
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
void CWall::Unload()
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
CWall * CWall::Create(const int &nCreateNum)
{
	CWall *pWall = new CWall;

	if (pWall != nullptr)
	{
		//�ǂ̐������̐ݒ�
		pWall->m_nCreateNum = nCreateNum;

		//�ǂ̏���������
		pWall->Init();

		return pWall;
	}

	return nullptr;
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CWall::Init(void)
{
	//WallData�̎擾����
	GetWallData();

	//���f���̏���������
	CModel::Init();

	return E_NOTIMPL;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CWall::Uninit(void)
{
	if (m_pCollision != NULL)
	{
		m_pCollision->Uninit();
	}

	CModel::Uninit();
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CWall::Update(void)
{
	CModel::Update();
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CWall::Draw(void)
{
	CModel::Draw();
}

//*****************************************************************************
//WallData�̎擾����
//*****************************************************************************
void CWall::GetWallData(void)
{
	//�ǃf�[�^�̎擾
	CWallData::CreateInfo* pWallData = CManager::GetWallData()->GetCreateInfo(m_nCreateNum);

	if (pWallData != NULL)
	{
		//�Z-------�Z
		// �ǂ̐ݒ�
		//�Z-------�Z

		//���f�����̎擾
		D3DXVECTOR3 ModelPos = pWallData->pos;
		D3DXVECTOR3 ModelSize = pWallData->size;
		D3DXVECTOR3 ModelRot = pWallData->rot;

		//���f�����̐ݒ�
		SetPos(ModelPos);
		SetSize(ModelSize);
		SetRot(ModelRot);
		BindModel(m_pMesh, m_pBuffMat, m_nNumMat);

		//��ނ̐ݒ�
		m_type = (CWall::TYPE)pWallData->nType;

		if (m_pCollision == NULL)
		{
			//�����蔻��̑傫���̎擾
			D3DXVECTOR3 CollisionSize = pWallData->collisionSize;

			//�����蔻��̐���
			m_pCollision = CCollision::Create(
				ModelPos,
				CollisionSize,
				ModelRot,
				CCollision::TYPE_BOX);

			//D���W�����߂�
			m_vect.d = VertexRotate(ModelPos, CollisionSize, ModelRot, VER_D);

			//C���W�����߂�
			m_vect.c = VertexRotate(ModelPos, CollisionSize, ModelRot, VER_C);

			//�ǂ̓����蔻��̕����x�N�g��(DC�x�N�g��)�����߂�
			m_vect.dc = m_vect.c - m_vect.d;

			//�����x�N�g���Ƃ��ĕۑ�
			m_vect.direction = m_vect.dc;
		}
	}
}