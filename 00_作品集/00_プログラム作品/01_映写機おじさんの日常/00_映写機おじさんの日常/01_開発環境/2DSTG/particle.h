//================================================================
//
// �p�[�e�B�N������ [particle.h]
// Author : Suzuki Mahiro
//
//================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//****************************************************************
//�C���N���[�h�t�@�C��
//****************************************************************
#include "scene2d.h"

//****************************************************************
//�}�N����`
//****************************************************************
#define PARTICLE_NONE (2)	//�ʏ��
#define PARTICLE_MAX (12)	//�ő��

//****************************************************************
//�N���X��`
//****************************************************************
class CParticle :public CScene2D
{
public:
	CParticle();
	~CParticle();
	static CParticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);
	static void Create(D3DXVECTOR3 pos, int nNum);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_move;						//�ړ���
	float m_fGravity;						//�d��
};

#endif