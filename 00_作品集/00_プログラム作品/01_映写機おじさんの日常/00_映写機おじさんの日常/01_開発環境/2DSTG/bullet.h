//================================================================
//
// �o���b�g���� [bullet.h]
// Author : Suzuki Mahiro
//
//================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//****************************************************************
//�C���N���[�h�t�@�C��
//****************************************************************
#include "scene2d.h"

//****************************************************************
//�}�N����`
//****************************************************************
#define BULLET_SIZE_X			(35.0f)			//�e�̍ő�X�T�C�Y
#define BULLET_SIZE_Y			(70.0f)			//�e�̍ő�Y�T�C�Y
#define BULLET_CHARGE_SPEED		(60)			//�e�̃`���[�W�X�s�[�h
#define BULLET_SPEED_Y			(-10.0f)		//�e�̃X�s�[�h(Y��)
#define BULLET_CREATE_POINT		(D3DXVECTOR3(15.0f, -(PLAYER_SIZE.y / 2), 0.0f))

//****************************************************************
//�N���X��`
//****************************************************************
class CBullet :public CScene2D
{
public:
	//�e�̃`���[�W��Ԃ̗񋓌^
	typedef enum
	{
		BULLET_STATE_NONE = 0,	//�ʏ�
		BULLET_STATE_MAX,		//MAX�`���[�W���
		BULLET_STATE_NOT_SHOOT	//�����Ă��Ȃ�
	}BULLET_STATE;

	CBullet();
	~CBullet();
	static CBullet *Create(D3DXVECTOR3 pos, int nCntCharge);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(D3DXVECTOR3 pos, int nCntCharge);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetMove(D3DXVECTOR3 move);
	void SetSize(int nCntCharge);
	void SetBulletType(BULLET_STATE BulletState);
	void SetPartticle(D3DXVECTOR3 pos);
	
	D3DXVECTOR3 GetBulletSize(void);
	BULLET_STATE GetBulletState(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_move;						//�ړ���
	D3DXVECTOR3 m_size;						//�T�C�Y
	float m_fGravity;						//�d��
	BULLET_STATE m_BulletState;				//�e�̏��
};

#endif