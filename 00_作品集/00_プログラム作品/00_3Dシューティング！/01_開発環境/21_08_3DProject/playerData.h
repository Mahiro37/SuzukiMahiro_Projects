//=============================================================================
//
// �v���C���[�f�[�^�Ǘ� [playerData.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _PLAYER_DATA_H_
#define _PLAYER_DATA_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "character.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CPlayerData
{
public:
	//�v���C���[���̍\����
	struct CreateInfo
	{
		CCharacter::TYPE type;		//���
		D3DXVECTOR3 pos;			//�ʒu
		D3DXVECTOR3 modelSize;		//���f���̑傫��
		D3DXVECTOR3 collisionSize;	//�����蔻��̑傫��
		D3DXVECTOR3 rot;			//�p�x
		float fMove;				//�ړ���
		int nBulletType;			//�e�̎��
	};

	CPlayerData();	//�R���X�g���N�^
	~CPlayerData();	//�f�X�g���N�^

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������

	CreateInfo* GetCreateInfo(const CCharacter::TYPE &type);	//�������̎擾

private:
	CreateInfo m_aCreateInfo[CCharacter::TYPE_MAX];	// �������
};

#endif