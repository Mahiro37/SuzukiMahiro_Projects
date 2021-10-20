//=============================================================================
//
// �e�̔����G�t�F�N�g���� [effect_explosion_bullet.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _EFFECT_EXPLOSION_BULLET_H_
#define _EFFECT_EXPLOSION_BULLET_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "effect.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CEffectExplosionBullet :public CEffect
{
public:
	CEffectExplosionBullet(OBJTYPE nPriority = CScene::OBJTYPE_EFFECT_EXPLOSION_BULLET);	//�R���X�g���N�^
	~CEffectExplosionBullet();																//�f�X�g���N�^

	static CEffectExplosionBullet *Create(const D3DXVECTOR3 &pos);	//��������

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
};

#endif