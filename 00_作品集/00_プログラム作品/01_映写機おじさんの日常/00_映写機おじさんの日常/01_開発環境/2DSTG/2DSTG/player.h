//=============================================================================
//
// �v���C���[���� [player.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2d.h"
#include "item.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define PLAYER_TEXTURE			(1)										//�e�N�X�`���̎��
#define PLAYER_LIFE				(3)										//�v���C���[�̎c�@��
#define PLAYER_SIZE				(D3DXVECTOR3(150.0f,150.0f,0.0f))		//�v���C���[�̃T�C�Y
#define PLAYER_COLLISION_SIZE	(D3DXVECTOR3(60.0f,100.0f,0.0f))		//�v���C���[�̓����蔻��T�C�Y
#define PLAYER_RADIUS			(45.0f)									//�v���C���[�̔��a

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CBarrier;
class CBullet;
class CEffect;
class CMessage;

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CPlayer :public CScene2D
{
public:
	//�v���C���[�̏�Ԃ̗񋓌^
	typedef enum
	{
		PLAYER_STATE_NONE = 0,		//�ʏ�
		PLAYER_STATE_INVINCIBLE,	//���G
		PLAYER_STATE_DEATH,			//���S
		PLAYER_STATE_MAX
	}PLAYER_STATE;
	
	CPlayer();
	~CPlayer();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void PlayerReset(void);

	void SetItemStock(CItem::ITEMTYPE ItemType);
	void SetPlayerAbility(void);
	void DeleteBarrierAbility(void);
	void SetLife(int nLife);
	void SetPlayerState(PLAYER_STATE state);

	D3DXVECTOR3 GetPos(void);
	CBarrier *GetBarrier(void);
	CBullet *GetBullet(void);
	int GetPlayerLife(void);
	int GetChargeSpeed(void);
	list<CItem::ITEMTYPE> GetStockItem(void);
	PLAYER_STATE GetPlayerState(void);
	bool GetChargeRelease(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[PLAYER_TEXTURE];	//�e�N�X�`���̃|�C���^�z��
	D3DXVECTOR3 m_pos;										//�ʒu
	static int m_nLife;										//���C�t
	float m_fPlayerSpeed;									//�ړ��X�s�[�h
	int m_nChargeSpeed;										//�`���[�W�X�s�[�h

	static CBarrier *m_pBarrier;							//�o���A�̃|�C���^
	CBullet *m_pBullet;										//�e�̃|�C���^
	CEffect *m_pEffect;										//�G�t�F�N�g�̃|�C���^
	CMessage *m_pMessage;									//���b�Z�[�W�̃|�C���^

	list<CItem::ITEMTYPE> m_StockItem;						//�A�C�e���X�g�b�N�̃��X�g

	PLAYER_STATE m_PlayerState;								//�v���C���[�̏��

	int m_nCntInvincible;									//���G�J�E���g
	int m_nInvincibleTime;									//���G���Ԓ��̓_�ŉ�
	int m_nCntPress;										//�`���[�W�̃v���X����
	int m_nCntCharge;										//�}�b�N�X�`���[�W��Ԃł̃v���X����
	static bool m_bRelease;									//�`���[�W���Ă��邩�̔���
};

#endif