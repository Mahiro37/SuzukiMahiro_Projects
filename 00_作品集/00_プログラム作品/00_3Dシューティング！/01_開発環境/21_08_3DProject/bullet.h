//=============================================================================
//
// �e���� [bullet.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "model.h"
#include "character.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CCollision;

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CBullet : public CModel
{
public:
	//�e�̎�ނ̗񋓌^
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_BULLET1,	//�v���C���[�P
		TYPE_BULLET2,	//�v���C���[�Q
		TYPE_MAX
	}TYPE;

	CBullet(OBJTYPE Priority = OBJTYPE_BULLET);	//�R���X�g���N�^
	~CBullet();									//�f�X�g���N�^

	static void Load();		//���[�h����
	static void Unload();	//�A�����[�h����

	static CBullet *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, const D3DXVECTOR3 &vect, const TYPE &type, const CCharacter::TYPE &PlayerType);	//��������

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	void Move(void);	//�ړ�����

	HRESULT HitInit(void);		//�����l�̏Փˏ���
	HRESULT HitBullet(void);	//�e�̏Փˏ���
	HRESULT HitWall(void);		//�ǂ̏Փˏ���
	HRESULT HitBlock(void);		//��Q���̏Փˏ���

	D3DXVECTOR3 ReflectVector(const D3DXVECTOR3 &front, const D3DXVECTOR3 &normal);	//�e�̔��ˏ���

	void GetBulletData(void);								//�e�f�[�^�̎擾����
	CCollision *GetCollision(void) { return m_pCollision; }	//�����蔻��|�C���^�̎擾

private:
	static LPD3DXMESH m_pMesh[TYPE_MAX];		// ���b�V�����̃|�C���^
	static LPD3DXBUFFER m_pBuffMat[TYPE_MAX];	// �}�e���A�����̃|�C���^
	static DWORD m_NumMat[TYPE_MAX];			// �}�e���A�����̐�

	TYPE m_type;					//���
	CCharacter::TYPE m_PlayerType;	//�e�𐶐������I�u�W�F�N�g���
	D3DXVECTOR3 m_vect;				//�����x�N�g��
	float m_fMove;					//�ړ���
	int m_nLife;					//���ː�
	int m_nCntLife;					//���ː��̃J�E���g
	bool m_bHit;					//�����ʒu�œ������Ă��邩�̔���

	CCollision *m_pCollision;		//�����蔻��̃|�C���^
};
#endif