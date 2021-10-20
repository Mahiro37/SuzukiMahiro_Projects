//=============================================================================
//
// �����G�t�F�N�g���� [effect_explosion_player.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _EFFECT_EXPLOSION_PLAYER_H_
#define _EFFECT_EXPLOSION_PLAYER_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "effect.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CEffectExplosionPlayer :public CEffect
{
public:
	CEffectExplosionPlayer(OBJTYPE nPriority = CScene::OBJTYPE_EFFECT_EXPLOSION);	//�R���X�g���N�^
	~CEffectExplosionPlayer();														//�f�X�g���N�^

	static CEffectExplosionPlayer *Create(const D3DXVECTOR3 &pos);	//��������

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
};

#endif