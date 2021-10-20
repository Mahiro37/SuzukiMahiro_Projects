//=============================================================================
//
// �e�ƕǂ̏Փ˃G�t�F�N�g���� [effect_wall_hit.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _EFFECT_WALL_HIT_H_
#define _EFFECT_WALL_HIT_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "effect.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CEffectWallHit :public CEffect
{
public:
	CEffectWallHit(OBJTYPE nPriority = CScene::OBJTYPE_EFFECT_EXPLOSION_BULLET);	//�R���X�g���N�^
	~CEffectWallHit();																//�f�X�g���N�^

	static CEffectWallHit *Create(const D3DXVECTOR3 &pos);	//��������

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��
};

#endif