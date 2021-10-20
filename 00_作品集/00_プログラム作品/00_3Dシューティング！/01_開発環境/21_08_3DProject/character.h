//=============================================================================
//
// �L�����N�^�[���� [character.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "model.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CCollision;

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CCharacter : public CModel
{
public:
	//�L�����N�^�[�^�C�v�̗񋓌^
	enum TYPE
	{
		TYPE_NONE = -1,
		TYPE_PLAYER_1,	//�v���C���[1
		TYPE_PLAYER_2,	//�v���C���[2
		TYPE_MAX
	};

	CCharacter(OBJTYPE Priority);	//�R���X�g���N�^
	virtual ~CCharacter();			//�f�X�g���N�^

	virtual HRESULT Init(void);	//����������
	virtual void Uninit(void);	//�I������
	virtual void Update(void);	//�X�V����
	virtual void Draw(void);	//�`�揈��

	bool GetInputState(void) { return m_bInput; }					//���͂��Ă��邩�̎擾
	float GetPlayerMove(void) { return m_fPlayerMove; }				//�v���C���[�̈ړ��ʂ̎擾
	D3DXVECTOR3 GetMoveVect(void) { return m_MoveVect; }			//�ړ��x�N�g���̎擾
	float GetVectLength(void) { return m_fVectLength; }				//�ړ��x�N�g���̒����̎擾
	D3DXVECTOR3 GetBulletDistance(void) {return m_BulletDistance;}	//�e�̐����ʒu�̐ݒ�
	int GetBulletType(void) {return m_nBulletType;}					//�e�̎�ނ̐ݒ�
	CCollision *GetCollision(void) { return m_pCollision; }			//�����蔻��C���X�^���X�̎擾

protected:
	void InitPlayer(const TYPE &type);						//�v���C���[�f�[�^�̐ݒ菈��
	CCollision* SelectCollisionPointer(const TYPE &type);	//�v���C���[���Ƃ̓����蔻���Ԃ�����
	void Move(const TYPE &type);							//�ړ�����
	void Shot(const TYPE &type);							//���ˏ���

	D3DXVECTOR3 VectorCalculation(const D3DXVECTOR3 &Va, const D3DXVECTOR3 &Vb);
	float AngleOf2Vector(const D3DXVECTOR3 &VectorA, const D3DXVECTOR3 &VectorB);
	D3DXVECTOR3 BulletPosition(const D3DXVECTOR3 &PlayerPos, const D3DXVECTOR3 &PlayerRot, const D3DXVECTOR3 &BulletDistance);

	void AfterHit(void);					//�Փˌ�̏���
	void HitWall(const TYPE &type);			//�ǂ̓����蔻��
	void HitBlock(const TYPE &type);		//��Q���̓����蔻��
	HRESULT HitBullet(const TYPE &type);	//�e�̓����蔻��

	void SetInputState(const bool &bInputState) { m_bInput = bInputState; }			//���͏�Ԃ̐ݒ�
	void SetPlayerMove(const float &fPlayerMove) { m_fPlayerMove = fPlayerMove; }	//�v���C���[�̈ړ��ʂ̐ݒ�
	void SetMoveVect(const D3DXVECTOR3 &MoveVect) { m_MoveVect = MoveVect; }		//�ړ��x�N�g���̐ݒ�
	void SetVectLength(const float &fVectLength) { m_fVectLength = fVectLength; }	//�ړ��x�N�g���̒����̐ݒ�
	void SetBulletDistance(const D3DXVECTOR3 &BulletDistance)
	{ m_BulletDistance = BulletDistance; }										//�e�̐����ʒu�̐ݒ�
	void SetBulletType(const int &nBulletType) { m_nBulletType = nBulletType; }	//�e�̎�ނ̐ݒ�

private:
	bool m_bInput;	//���͏��

	float m_fPlayerMove;		//�v���C���[�̈ړ���
	D3DXVECTOR3 m_MoveVect;		//�ړ��x�N�g��
	float m_fVectLength;		//�ړ��x�N�g���̒���
	D3DXVECTOR3 m_SlideVect;	//�ǂ���x�N�g��

	D3DXVECTOR3 m_BulletDistance;	//�e�̐����ʒu(�v���C���[�̒��S����̋���)
	int m_nBulletType;				//�e�̎��

	int m_nCntHit = 0;			//�����ɓ����������̃J�E���g
	CCollision *m_pCollision;	//�����蔻��̃|�C���^
};
#endif