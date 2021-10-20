//=============================================================================
//
// ���f������ [model.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "joystick.h"
#include "model.h"

//*****************************************************************************
//�C���N�������g
//*****************************************************************************
CModel::CModel(OBJTYPE nPriority) :CScene(nPriority)
{
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = NULL;
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
	m_nldxModelParent = 0;
	memset(m_pTexture, 0, sizeof(m_pTexture));

	m_pos = ZeroVector3;
	m_posOld = ZeroVector3;
	m_rot = ZeroVector3;
	m_size = ZeroVector3;
	m_VectOld = ZeroVector3;

}

//*****************************************************************************
//�f�N�������g
//*****************************************************************************
CModel::~CModel()
{
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CModel::Init()
{
	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CModel::Uninit(void)
{
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = NULL;

	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));

	Release();
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CModel::Update(void)
{
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CModel::Draw(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;
	D3DMATERIAL9 matDef;					//���݂̃}�e���A���ێ��p

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �g�嗦�𔽉f
	D3DXMatrixScaling(&mtxScale, m_size.x, m_size.y, m_size.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾����
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL*pMat;

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
		pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		if (m_pMesh != NULL)
		{
			//���f���p�[�c�̕`��
			m_pMesh->DrawSubset(nCntMat);
		}

		pDevice->SetTexture(0, nullptr);
	}

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
}

//*****************************************************************************
// ��]��̍��W�v�Z
//*****************************************************************************
D3DXVECTOR3 CModel::VertexRotate(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, const CModel::VERTEX &vertexType)
{
	//���_���W�p�̕ϐ�
	D3DXVECTOR3 vertex = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (vertexType)
	{
	case VER_A:

		vertex = D3DXVECTOR3(
			(-(size.x / 2) * cosf(rot.y)) + ((size.z / 2) * sinf(rot.y)) + pos.x,
			pos.y,
			((size.x / 2) * sinf(rot.y)) + ((size.z / 2) * cosf(rot.y)) + pos.z);

		break;

	case VER_B:

		vertex = D3DXVECTOR3(
			((size.x / 2) * cosf(rot.y)) + ((size.z / 2) * sinf(rot.y)) + pos.x,
			pos.y,
			(-(size.x / 2) * sinf(rot.y)) + ((size.z / 2) * cosf(rot.y)) + pos.z);

		break;

	case VER_C:

		vertex = D3DXVECTOR3(
			((size.x / 2) * cosf(rot.y)) + (-(size.z / 2) * sinf(rot.y)) + pos.x,
			pos.y,
			(-(size.x / 2) * sinf(rot.y)) + (-(size.z / 2) * cosf(rot.y)) + pos.z);

		break;

	case VER_D:

		vertex = D3DXVECTOR3(
			(-(size.x / 2) * cosf(rot.y)) + (-(size.z / 2) * sinf(rot.y)) + pos.x,
			pos.y,
			((size.x / 2) * sinf(rot.y)) + (-(size.z / 2) * cosf(rot.y)) + pos.z);

		break;
	}

	return vertex;
}