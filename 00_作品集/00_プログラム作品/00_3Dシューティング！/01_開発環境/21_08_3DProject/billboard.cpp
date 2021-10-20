//=============================================================================
//
// �r���{�[�h���� [billboard.cpp]
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
#include "billboard.h"

//*****************************************************************************
//���I�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBillboard::m_apTexture[CBillboard::TYPE_MAX] = {};
CBillboard::TYPE CBillboard::m_type = CBillboard::TYPE_NONE;

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CBillboard::CBillboard(OBJTYPE nPriority) :  CScene(nPriority)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f,1.0f,1.0f);
	m_fTexX = 0.0f;
	m_fTexX2 = 1.0f;
	m_fTexY = 0.0f;
	m_fTexY2 = 1.0f;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CBillboard::~CBillboard()
{
}

//*****************************************************************************
//�e�N�X�`���̓ǂݍ���
//*****************************************************************************
HRESULT CBillboard::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Textures/KingSlime.png", &m_apTexture[TYPE_PLAYER1_BULLET]);
	D3DXCreateTextureFromFile(pDevice, "Data/Textures/KingSlime.png", &m_apTexture[TYPE_PLAYER2_BULLET]);

	return S_OK;
}

//*****************************************************************************
//�e�N�X�`���̔j��
//*****************************************************************************
void CBillboard::Unload(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//*****************************************************************************
//������
//*****************************************************************************
HRESULT CBillboard::Init(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	//���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			//���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_3D,				//�g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			//���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,				//���_�o�b�t�@�ւ̃|�C���^
		NULL)))						//NULL�ɐݒ�
	{
		return E_FAIL;
	}

	//���_����ݒ�
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�ꏊ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-(m_size.x / 2), +(m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+(m_size.x / 2), +(m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-(m_size.x / 2), -(m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+(m_size.x / 2), -(m_size.y / 2), 0.0f);

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col ;
	pVtx[2].col = m_col ;
	pVtx[3].col = m_col ;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}
//*****************************************************************************
//�I������
//*****************************************************************************
void CBillboard::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�j��
	Release();
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CBillboard::Update(void)
{
	//���_����ݒ�
	VERTEX_3D *pVtx = NULL;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�ꏊ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-(m_size.x / 2), +(m_size.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+(m_size.x / 2), +(m_size.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-(m_size.x / 2), -(m_size.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+(m_size.x / 2), -(m_size.y / 2), 0.0f);

	//�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_fTexX, m_fTexY);
	pVtx[1].tex = D3DXVECTOR2(m_fTexX2, m_fTexY);
	pVtx[2].tex = D3DXVECTOR2(m_fTexX, m_fTexY2);
	pVtx[3].tex = D3DXVECTOR2(m_fTexX2, m_fTexY2);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CBillboard::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	//�s��v�Z�p�̃}�g���N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���C�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Z�o�b�t�@�𖳌���
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�Z�b�g�e�N�X�`��
	pDevice->SetTexture(0, m_apTexture[m_type]);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//��]�̋t�s��
	pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxRot);
	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;

	//�������f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x,
		m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld,
		&mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�A���t�@�e�X�g������
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//Z�o�b�t�@��L����
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//���C�g�L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}