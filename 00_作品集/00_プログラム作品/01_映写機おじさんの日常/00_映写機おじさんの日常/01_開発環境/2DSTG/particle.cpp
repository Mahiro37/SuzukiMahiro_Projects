//=============================================================================
//
// �p�[�e�B�N������ [particle.h]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "particle.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define PARTICLE_GRAVITY (0.3f)
#define PARTICLE_DISTANCE (30)
#define PARTICLE_SIZE (D3DXVECTOR3(20.0f,20.0f,0.0f))
#define PARTICLE_MOVE (6)

//*****************************************************************************
//�ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CParticle::m_pTexture = {};

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CParticle::CParticle()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fGravity = 0.0f;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CParticle::~CParticle()
{
}

//*****************************************************************************
//�p�[�e�B�N���̐���(�P��)
//*****************************************************************************
CParticle * CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CParticle *pParticle = new CParticle;

	//����������
	pParticle->Init(pos, move);

	return pParticle;
}

//*****************************************************************************
//�p�[�e�B�N���̐���(����)
//*****************************************************************************
void CParticle::Create(D3DXVECTOR3 pos, int nNum)
{
	for (int nCount = 0; nCount < nNum; nCount++)
	{
		//�p�x�̌v�Z
		float fAngle = D3DXToRadian(360 / nNum) * nCount;

		//�����̌v�Z
		int nDistance = rand() % PARTICLE_DISTANCE + 1;

		//�ړ��ʂ̌v�Z
		int nMove = rand() % PARTICLE_MOVE + 1;

		//�p�[�e�B�N���̐���(�P��)
		Create(D3DXVECTOR3(pos.x + cosf(fAngle) * nDistance, pos.y + sinf(fAngle) * nDistance, 0.0f), D3DXVECTOR3(cosf(fAngle) * nMove, sinf(fAngle) * nMove, 0.0f));
	}
}

//*****************************************************************************
//���[�h����
//*****************************************************************************
HRESULT CParticle::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Textures/popcorn.png", &m_pTexture);

	return S_OK;
}

//*****************************************************************************
//�A�����[�h����
//*****************************************************************************
void CParticle::Unload(void)
{
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j��
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CParticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	//�V�[��2D�̏�����
	CScene2D::Init();

	//�ʒu�̐ݒ�
	SetPos(pos);

	//�ړ��ʂ̐ݒ�
	m_move = move;

	//�T�C�Y�̐ݒ�
	SetSize(PARTICLE_SIZE);

	//�����d�͗ʂ̐ݒ�
	m_fGravity = PARTICLE_GRAVITY;

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(OBJTYPE_PARTICLE);

	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CParticle::Uninit(void)
{
	//�V�[��2D�̏I������
	CScene2D::Uninit();
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CParticle::Update(void)
{
	//�V�[��2D�̍X�V����
	CScene2D::Update();

	//�|�W�V�����̎擾
	D3DXVECTOR3 pos = GetPos();

	pos += m_move;

	//�d�͂����Z
	m_fGravity += PARTICLE_GRAVITY;
	pos.y += m_fGravity;

	//��]����
	Rotation(pos, PARTICLE_SIZE, ROTATION_RIGHT);

	//�ʒu�̍X�V
	SetPos(pos);

	//��ʂ�艺�ɏo���Ƃ�
	if (pos.y >= SCREEN_HEIGHT + (PARTICLE_SIZE.y / 2))
	{
		//�A�C�e���̏I������
		Uninit();
	}
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CParticle::Draw(void)
{
	//�V�[��2D�̕`�揈��
	CScene2D::Draw();
}