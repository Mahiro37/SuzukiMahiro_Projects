//=============================================================================
//
// �����G�t�F�N�g���� [effect_explosion_player.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "effect_explosion_player.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define ANIM_LINE (3)							//�A�j���[�V�����̍s��
#define ANIM_COLUMN (3)							//�A�j���[�V�����̗�
#define ANIM_SPEED (6)							//�A�j���[�V�����̐؂�ւ����x
#define SIZE (D3DXVECTOR3(50.0f, 50.0f, 50.0f))	//�G�t�F�N�g�̑傫��

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CEffectExplosionPlayer ::CEffectExplosionPlayer (OBJTYPE nPriority) :CEffect(nPriority)
{
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CEffectExplosionPlayer ::~CEffectExplosionPlayer ()
{
}

//*****************************************************************************
//�����G�t�F�N�g�̐���
//*****************************************************************************
CEffectExplosionPlayer * CEffectExplosionPlayer ::Create(const D3DXVECTOR3 &pos)
{
	//�����G�t�F�N�g�̃������m��
	CEffectExplosionPlayer  *pEffectExplosion = new CEffectExplosionPlayer ;

	if (pEffectExplosion != nullptr)
	{
		//�����G�t�F�N�g���̐ݒ�
		pEffectExplosion->SetPos(pos);

		//����������
		pEffectExplosion->Init();

		return pEffectExplosion;
	}

	return nullptr;
}

//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CEffectExplosionPlayer ::Init(void)
{
	//�e�N�X�`���̎�ނ̐ݒ�
	BindTexture(GetTexture(TYPE_EXPLOSION));

	//�e�N�X�`�����̐ݒ�
	SetTex(ANIM_LINE, ANIM_COLUMN, ANIM_SPEED);

	//���s�[�g�ݒ�
	SetRepeat(REP_UNREPEAT);

	//�T�C�Y�̐ݒ�
	SetSize(SIZE);

	//�G�t�F�N�g�̏���������
	CEffect::Init();

	//�T�E���h�̍Đ�
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_PLAYER_EXPLOSION);

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CEffectExplosionPlayer ::Uninit(void)
{
	//�G�t�F�N�g�̏I������
	CEffect::Uninit();
}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CEffectExplosionPlayer ::Update(void)
{
	//�G�t�F�N�g�̍X�V����
	CEffect::Update();
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CEffectExplosionPlayer ::Draw(void)
{
	//�G�t�F�N�g�̕`�揈��
	CEffect::Draw();
}