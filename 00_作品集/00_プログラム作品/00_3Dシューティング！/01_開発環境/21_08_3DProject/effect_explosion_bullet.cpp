//=============================================================================
//
// �e�̔����G�t�F�N�g���� [effect_explosion_bullet.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "effect_explosion_bullet.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define ANIM_LINE (8)							//�A�j���[�V�����̍s��
#define ANIM_COLUMN (1)							//�A�j���[�V�����̗�
#define ANIM_SPEED (3)							//�A�j���[�V�����̐؂�ւ����x
#define SIZE (D3DXVECTOR3(20.0f, 20.0f, 20.0f))	//�G�t�F�N�g�̑傫��

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CEffectExplosionBullet::CEffectExplosionBullet(OBJTYPE nPriority) :CEffect(nPriority)
{
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CEffectExplosionBullet::~CEffectExplosionBullet()
{
}

//*****************************************************************************
//�e�̔����G�t�F�N�g�̐���
//*****************************************************************************
CEffectExplosionBullet* CEffectExplosionBullet::Create(const D3DXVECTOR3 &pos)
{
	//�e�̔����G�t�F�N�g�̃������m��
	CEffectExplosionBullet *pEffectExplosionBullet = new CEffectExplosionBullet;

	if (pEffectExplosionBullet != nullptr)
	{
		//�e�̔����G�t�F�N�g���̐ݒ�
		pEffectExplosionBullet->SetPos(pos);

		//����������
		pEffectExplosionBullet->Init();

		return pEffectExplosionBullet;
	}

	return nullptr;
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CEffectExplosionBullet::Init(void)
{
	//�e�N�X�`���̎�ނ̐ݒ�
	BindTexture(GetTexture(TYPE_EXPLOSION_BULLET));

	//�e�N�X�`�����̐ݒ�
	SetTex(ANIM_LINE, ANIM_COLUMN, ANIM_SPEED);

	//���s�[�g�ݒ�
	SetRepeat(REP_UNREPEAT);

	//�T�C�Y�̐ݒ�
	SetSize(SIZE);

	//�G�t�F�N�g�̏���������
	CEffect::Init();

	//�T�E���h�̍Đ�
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BULLET_EXPLOSION);

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CEffectExplosionBullet::Uninit(void)
{
	//�G�t�F�N�g�̏I������
	CEffect::Uninit();
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CEffectExplosionBullet::Update(void)
{
	//�G�t�F�N�g�̍X�V����
	CEffect::Update();
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CEffectExplosionBullet::Draw(void)
{
	//�G�t�F�N�g�̕`�揈��
	CEffect::Draw();
}